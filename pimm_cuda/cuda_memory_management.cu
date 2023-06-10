#include "cuda_memory_management.cuh"

using namespace pimm::utils;

namespace pimm::cuda {

cudaStream_t processing_stream;

void init(){
    cudaStreamCreate(&processing_stream);
}

void close(){
    cudaStreamDestroy(processing_stream);
}

uint8_t* AllocateImageMemoryBytes(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel){
    const size_t kNumElements = GetNumElementsForColorModel(kWidth, kHeight, kColorModel);
    if(kNumElements == 0){
        return nullptr;
    }

    uint8_t* dev_image_bytes;
    cudaMalloc(&dev_image_bytes, kNumElements * sizeof(uint8_t));

    return dev_image_bytes;
}

void ReleaseImageMemoryBytes(uint8_t* image_bytes){
    cudaFree(image_bytes);
    image_bytes = nullptr;
}

void CopyCpuToGpu(uint8_t* from, uint8_t* to, const size_t kNumBytes){
    //cudaMemcpy(to, from, kNumBytes, cudaMemcpyHostToDevice);
    cudaMemcpyAsync(to, from, kNumBytes, cudaMemcpyHostToDevice, processing_stream);
    cudaStreamSynchronize(processing_stream);
}

void CopyGpuToGpu(uint8_t* from, uint8_t* to, const size_t kNumBytes){
    //cudaMemcpy(to, from, kNumBytes, cudaMemcpyHostToDevice);
    cudaMemcpyAsync(to, from, kNumBytes, cudaMemcpyDeviceToDevice, processing_stream);
    cudaStreamSynchronize(processing_stream);
}
void CopyGpuToCpu(uint8_t* from, uint8_t* to, const size_t kNumBytes){
    //cudaMemcpy(to, from, kNumBytes, cudaMemcpyHostToDevice);
    cudaMemcpyAsync(to, from, kNumBytes, cudaMemcpyDeviceToHost, processing_stream);
    cudaStreamSynchronize(processing_stream);
}

}
