#undef min
#undef max

#include"cuda_runtime.h"
#include"device_launch_parameters.h"
#include"helper_cuda.h"
#include"thrust/device_vector.h"
#include"thrust/host_vector.h"
#include <thrust/system/cuda/memory.h>        // 常规 pinned allocator 在此

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<algorithm>
#include<float.h>

#define ESC 27

using uchar = unsigned char;
using uint = unsigned int;
using ulong = unsigned long;
using ushort = unsigned short;
using ullong= unsigned long long;
using llong = long long;

using cuchar=const unsigned char;
using cuint = const unsigned int;
using cfloat = const float;
using cdouble = const double;
using culong= const unsigned long;
using csllong=const unsigned long long;

using cchar=const char;
using cshort=const short;
using cint = const int;
using clong = const long;
using cllong= const long long;
using cdouble=const double;
using cfloat=const float;

using  cint3=const int3;
using  cfloat3=const float3;
template<typename T>using r_ptr=T*__restrict__;
template<typename T>using cr_ptr=const T*__restrict__;
template<typename T>using cvr_ptr=const T*__restrict__;
template<typename T>using ccr_ptr=const T*__restrict__;

template<typename T>using thrustHvecPin=thrust::host_vector<T,thrust::cuda::pinned_allocator<T>>;
template<typename T>using thrustDvec=thrust::device_vector<T>;
template<typename T>using thrustHvec=thrust::host_vector<T>;

template<typename T>T*trDptr(thrustDvec<T>&a){
    return a.data().get();
}
namespace cx {// NB these are inside cx namespace
// fancy definition of pi, (default float)81
template<typename T=float> constexpr T pi =
                                    (T) (3.1415926535897932385L) ;
template<typename T=float> constexpr T pi2 =(T) (2.0L*pi<T>);
template<typename T=float> constexpr T piby2 =(T)(0.5L*pi<T>);
// strip path from file name
const char *tail (cchar *s,char c){
const char *pch = strrchr (s,c);
return (pch != nullptr) ? pch+1 : s;}
// Based on NVIDIA checkCudaErrors in helper cuda.h89
inline int codecheck (cudaError_t code, cchar *file,cint line, cchar *call)
{
if(code != cudaSuccess){fprintf (stderr,"cx::ok error: %s at %s:%d %s \n",cudaGetErrorString (code), tail(file,'/'),
line, call);// NB this to quit on error
exit(1);//return 1; // or this to continue on error
}
return 0;
}
#define ok(cuda_call) codecheck(cuda_call,__FILE__,__LINE__,#cuda_call)
}