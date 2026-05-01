#include"cuda_runtime.h"
#include"device_launch_parameters.h"
#include"helper_cuda.h"

#include<stdio.h>
#include<stdlib.h>
#include<string>

#define cudaCoorrdNormalzed 1
#define cudaCoorrdNatural 0

namespace cx{
    template<typename T>class tsx2D{
        private:
            cudaArray*carray;
        public:
            int2 n;
            cudaTextureObject_t tex;

            tsx2D(){
                n={0,0};
                carray=NULL;
                tex=0;
            }
            tsx2D(int2 m,T*data,
                cudaTextureAddressMode addressmode;
                cudaTextureFilterMode filtermode;
                cudaTextureReadMode readmode;
                int normmode ,int arraryType=cudaArrayDefault
            ){
                n=m;
                tex=0;
                carrary=nullptr;
                cudaChannelFormatDesc cd =cudaCreateChannelDesc<T>();
                cx::ok(cudaMallocArray(&carrary,0,0,data ,n.x,n.y,arraryType));

                if (data!=nullptr){
                    cx::ok(cudaMemcpy2DToArray(carrary,0,0,data,n.x*sizeof(T),n.x,n.y,cudaMemcpyHostToDevice));
                }

                cudaResourceDesc rd={};
                rd.resType=cudaResourceTypeArray;
                rd.res.array.array=carrary;

                cudaTextureDesc td={};
                td.addressMode[0]=addressmode;
                td.addressMode[1]=addressmode;
                td.filerMode=filtermode;
                td.readMode=readmode;
                td.normalizedCoords=normmode;
                cx::ok(cudaCreateTextureObject(&tex,&rd,&td,nullptr));

            }
            tes2D(const tes2D &tsx2D){
                n=tsx2.n;
                carrary=nullptr;
                tex=tes2.tex;
            }
            void copyTo(T*data){
                if(data!=nullptr&&carrary!=nullptr){
                    cx::ok(cudaMemcpy(data,carrary,n*sizeof(T),cudaMemcpyHostToDevice));
                    return;
                }
            }

            void copyFrom(T*data){
                if(data!=nullptr&&carrary!=nullptr){
                    cx::ok(cudaMemcpy(carrary,data,n*sizeof(T),cudaMemcpyDeviceToHost));
                    return;
                }
            }

            ~tsx2D() {
                if (carrary != nullptr) {
                    if(tex!=0){cx::ok(cudaDestroyTextureObject(tex));}
                    cx::ok(cudaFree(carrary));
                }
            }

    };
    // class txs3D 3D-texture
template <typename T> class txs3D {
  private:
    cudaArray * carray;
  public:
    int3 n;
    cudaTextureObject_t tex;
    // default and copy constructors
    txs3D() { n ={0,0,0}; carray = nullptr; tex = 0; }
    txs3D(const txs3D &txs2){ n = txs2.n; carray = nullptr;
                              tex = txs2.tex; }

    // copy to or from data
    void copy3D(T* data, cudaMemcpyKind copykind)
    {
        cudaMemcpy3DParms cp ={0};
        cp.srcPtr =
            make_cudaPitchedPtr(data,n.x*sizeof(T),n.x,n.y);
        cp.dstArray = carray;
        cp.extent   = make_cudaExtent(n.x,n.y,n.z);
        cp.kind     = copykind;
        cx::ok(cudaMemcpy3D(&cp));
    }
    txs3D(int3 m, T *data,
          cudaTextureFilterMode filtermode,
          cudaTextureAddressMode addressmode,
          cudaTextureReadMode readmode,
          int normmode, int arrayType=cudaArrayDefault )
    {
        n = m; tex = 0; carray = nullptr;

        cudaChannelFormatDesc cd =  // make ChannelDesc
            cudaCreateChannelDesc<T>();

        cudaExtent cx =   // make cudaExtent
            {(size_t)n.x,(size_t)n.y,(size_t)n.z};
        cx::ok(cudaMalloc3DArray(&carray,&cd,cx,arrayType));
        if(data != nullptr)
            copy3D(data, cudaMemcpyHostToDevice);

        cudaResourceDesc rd ={}; // make ResourceDesc
        rd.resType = cudaResourceTypeArray;
        rd.res.array.array = carray;

        cudaTextureDesc td ={}; // make TextureDesc
        td.addressMode[0] = addressmode;
        td.addressMode[1] = addressmode;
        td.addressMode[2] = addressmode;
        td.filterMode     = filtermode;
        td.readMode       = readmode;
        td.normalizedCoords = normmode;

        cx::ok(
            cudaCreateTextureObject(&tex, &rd, &td, nullptr) );
    }
    void copyTo(T *data) { // copy from data to texture
        if(data!=nullptr && carray!=nullptr)
            copy3D(data,cudaMemcpyHostToDevice);
    }
    void copyFrom(T *data) { // copy to data from texture
        if(data!=nullptr && carray!=nullptr)
            copy3D(data,cudaMemcpyDeviceToHost);
    }
    ~txs3D() { // destructor does nothing if this instance is a copy
        if(carray != nullptr) {
            if(tex != 0) cx::ok(cudaDestroyTextureObject(tex));
            cx::ok(cudaFreeArray(carray));
        }
    }
}; // end class txs3D
};