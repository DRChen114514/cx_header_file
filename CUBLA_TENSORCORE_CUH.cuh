#ifndef CUBLA_TENSORCORE_CUH
#define CUBLA_TENSORCORE_CUH

#include <cuda_runtime.h>
#include <cuda_fp16.h>
#include <mma.h>
#include <cassert>

__global__ void tensorCoreHgemmKernel(
    const __half* A, const __half* B, const __half* C,
    __half* D,
    int m, int n, int k,
    int lda, int ldb, int ldc, int ldd,
    float alpha, float beta)
{
    int row = blockIdx.y * 16;
    int col = blockIdx.x * 16;
    if (row >= m || col >= n) return;
    nvcuda::wmma::fragment<nvcuda::wmma::matrix_a, 16, 16, 16, __half, nvcuda::wmma::col_major> a_frag;
    nvcuda::wmma::fragment<nvcuda::wmma::matrix_b, 16, 16, 16, __half, nvcuda::wmma::row_major> b_frag;
    nvcuda::wmma::fragment<nvcuda::wmma::accumulator, 16, 16, 16, float> acc_frag;

    nvcuda::wmma::fill_fragment(acc_frag, 0.0f);

    for (int i = 0; i < k; i += 16) {
        nvcuda::wmma::load_matrix_sync(a_frag, A + row * lda + i, lda);

        nvcuda::wmma::load_matrix_sync(b_frag, B + i * ldb + col, ldb);
        
        nvcuda::wmma::mma_sync(acc_frag, a_frag, b_frag, acc_frag);
    }

    // 准备输出 fragment
    nvcuda::wmma::fragment<nvcuda::wmma::accumulator, 16, 16, 16, __half> d_frag;
    
    if (beta != 0.0f) {
        nvcuda::wmma::fragment<nvcuda::wmma::matrix_b, 16, 16, 16, __half, nvcuda::wmma::row_major> c_frag;
        nvcuda::wmma::load_matrix_sync(c_frag, C + row * ldc + col, ldc);
        
        for (int i = 0; i < acc_frag.num_elements; ++i) {
            float c_val = __half2float(c_frag.x[i]);
            float res = alpha * acc_frag.x[i] + beta * c_val;
            d_frag.x[i] = __float2half(res);
        }
    } else {
        for (int i = 0; i < acc_frag.num_elements; ++i) {
            float res = alpha * acc_frag.x[i];
            d_frag.x[i] = __float2half(res);
        }
    }

    nvcuda::wmma::store_matrix_sync(D + row * ldd + col, d_frag, ldd, nvcuda::wmma::mem_row_major);
}

inline cudaError_t cublaHgemm(
    cudaStream_t stream,
    int m, int n, int k,
    const __half *A, int lda,
    const __half *B, int ldb,
    const __half *C, int ldc,
    __half *D, int ldd,
    float alpha = 1.0f, float beta = 0.0f)
{
    if (m % 16 != 0 || n % 16 != 0 || k % 16 != 0) {
        return cudaErrorInvalidValue;
    }

    dim3 block(32);                                 
    dim3 grid((n + 15) / 16, (m + 15) / 16);       

    tensorCoreHgemmKernel<<<grid, block, 0, stream>>>(
        A, B, C, D, m, n, k, lda, ldb, ldc, ldd, alpha, beta);

    return cudaGetLastError();
}

#endif 