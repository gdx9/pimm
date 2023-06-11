#include "pimm_cuda.cuh"
#include <cmath>

using namespace std;

namespace pimm::cuda {
// kernels
__global__
void RgbToGrayMean_kernel(uint8_t* rgb888, uint8_t* gray,
    const size_t kWidth, const size_t kHeight, const size_t kSizeGray){
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int idy = blockDim.y * blockIdx.y + threadIdx.y;

    if (idy < kHeight && idx < kWidth) {
        size_t pos = kWidth * idy + idx;

        int32_t val = (static_cast<int32_t>(rgb888[pos+0])
                    + static_cast<int32_t>(rgb888[pos+kSizeGray])
                    + static_cast<int32_t>(rgb888[pos+(kSizeGray<<1)])) / 3;
        // clip
        gray[pos] = static_cast<uint8_t>((val > 255) ? 255 : (val < 0) ? 0 : val);
    }
}
__global__
void RgbToGrayMean_kernel2(uint8_t* rgb888, uint8_t* gray,
    const size_t kSizeGray){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < kSizeGray) {
        int32_t val = (static_cast<int32_t>(rgb888[tid+0])
                    + static_cast<int32_t>(rgb888[tid+kSizeGray])
                    + static_cast<int32_t>(rgb888[tid+(kSizeGray<<1)])) / 3;
        // clip
        gray[tid] = static_cast<uint8_t>((val > 255) ? 255 : (val < 0) ? 0 : val);
    }
}

__global__
void RgbToGrayWeighted_kernel(uint8_t* rgb888, uint8_t* gray,
    const size_t kWidth, const size_t kHeight, const size_t kSizeGray){
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int idy = blockDim.y * blockIdx.y + threadIdx.y;

    if (idy < kHeight && idx < kWidth) {
        size_t pos = kWidth * idy + idx;

        float val = (static_cast<float>(rgb888[pos+0]) * 0.299f
                    + static_cast<float>(rgb888[pos+kSizeGray]) * 0.587f
                    + static_cast<float>(rgb888[pos+(kSizeGray<<1)]) * 0.144f);
        // clip
        gray[pos] = static_cast<uint8_t>((val > 255) ? 255 : (val < 0) ? 0 : val);
    }
}

__global__
void InvertColor_kernel(uint8_t* rgb, uint8_t* inverted, const size_t kNumElements){
    // int idx = blockDim.x * blockIdx.x + threadIdx.x;
    // int idy = blockDim.y * blockIdx.y + threadIdx.y;
	int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < kNumElements) {
        inverted[tid] = 255 - rgb[tid];// r

    }
}

__global__
void SolariseColor_kernel(uint8_t* rgb888, uint8_t* solarize, const size_t kNumElements, const uint8_t kThreshold){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < kNumElements) {
        uint8_t val = rgb888[tid];
        solarize[tid] = (val < kThreshold) ? (255 - val) : val;
    }

}

__global__
void PrepareGammaLutTable_kernel(uint8_t* gamma_lut_table, const float kGamma){
    // prepare gamma lut table

    const size_t kNumElements = 256;
    for(size_t i = 0; i < kNumElements; ++i){
        float val = pow(static_cast<float>(i) / 255.f, kGamma) * 255.f;

        // clip value
        gamma_lut_table[i] = static_cast<uint8_t>(
            (val < 0.f) ? 0.f : (val > 255.f) ? 255.f : val);
    }
}

__global__
void AdjustGamma_kernel(uint8_t* rgb888_src, uint8_t* rgb888_dst, uint8_t* gamma_lut_table, const size_t kNumElements){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < kNumElements) {
        rgb888_dst[tid] = gamma_lut_table[rgb888_src[tid]];
    }
}

__global__
void PrepareContrastLutTable_kernel(uint8_t* contrast_lut_table, const float kContrast){
    //F = 259*(255+contrast)/(255 *(259-contrast))
    const float kF = 259.f * (255.f + kContrast) / (255.f * (259.f - kContrast));

    const size_t kNumElements = 256;

    for(size_t i = 0; i < kNumElements; ++i){
        float val = (kF * static_cast<float>(i - 128.f)) + 128.f;

        // clip value
        contrast_lut_table[i] = static_cast<uint8_t>((val < 0.f) ? 0.f : (val > 255.f) ? 255.f : val);
    }

}

__global__
void AdjustContrast_kernel(uint8_t* rgb888_src, uint8_t* rgb888_dst, uint8_t* contrast_lut_table, const size_t kNumElements){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < kNumElements) {
        rgb888_dst[tid] = contrast_lut_table[rgb888_src[tid]];
    }
}

__global__
void AdjustBrightness_kernel(uint8_t* rgb888_src, uint8_t* rgb888_dst, const size_t kNumElements, const int32_t kBrightness){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < kNumElements) {
        int32_t val = static_cast<int32_t>(rgb888_src[tid]) + kBrightness;
        rgb888_dst[tid] = static_cast<uint8_t>((val < 0) ? 0 : (val > 255) ? 255 : val);
    }
}

extern cudaStream_t processing_stream;

void RgbToGrayMean(uint8_t* const rgb888, uint8_t* gray, const size_t kWidth, const size_t kHeight){
    dim3 tpb(32, 8);
    //1200,799
    dim3 nb(kWidth / tpb.x + 1, kHeight / tpb.y + 1);// 'walk' only on half of image - (WIDTH / 2)

    RgbToGrayMean_kernel<<<nb, tpb, 0, processing_stream>>>(rgb888, gray, kWidth, kHeight, kWidth*kHeight);
    cudaStreamSynchronize(processing_stream);

    // size_t kSizeGray = kWidth * kHeight;
    // int num_threads = 256;// 32*8
    // int num_blocks = (kNumElements*3 + num_threads - 1) / num_threads;
    // RgbToGrayMean_kernel2<<<num_blocks, num_threads, 0, processing_stream>>>(rgb888, gray, kSizeGray);
    // cudaStreamSynchronize(processing_stream);

}

void RgbToGrayWeighted(uint8_t* const rgb888, uint8_t* gray, const size_t kWidth, const size_t kHeight){
    dim3 tpb(32, 8);
    //1200,799
    dim3 nb(kWidth / tpb.x + 1, kHeight / tpb.y + 1);// 'walk' only on half of image - (WIDTH / 2)

    RgbToGrayWeighted_kernel<<<nb, tpb, 0, processing_stream>>>(rgb888, gray, kWidth, kHeight, kWidth*kHeight);
    cudaStreamSynchronize(processing_stream);
}

void InvertColor(uint8_t* const rgb888_src, uint8_t* rgb888_dst, const size_t kNumElements){
    int num_threads = 256;// 32*8
    int num_blocks = (kNumElements*3 + num_threads - 1) / num_threads;
	InvertColor_kernel << <num_blocks, num_threads, 0, processing_stream >> > (rgb888_src, rgb888_dst, kNumElements);
    cudaStreamSynchronize(processing_stream);
}

void SolariseColor(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
    const size_t kNumElements, const uint8_t kThreshold){
    int num_threads = 256;// 32*8
	int num_blocks = (kNumElements*3 + num_threads - 1) / num_threads;
	SolariseColor_kernel<<<num_blocks, num_threads, 0, processing_stream>>>(rgb888_src, rgb888_dst, kNumElements, kThreshold);
    cudaStreamSynchronize(processing_stream);
}

void AdjustGamma(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
    const size_t kNumElements, const float kGamma){
    uint8_t* gamma_lut_table;
    cudaMalloc(&gamma_lut_table, 256 * sizeof(uint8_t));

    PrepareGammaLutTable_kernel<<<1, 1, 0, processing_stream>>>(gamma_lut_table, kGamma);

    int num_threads = 256;// 32*8
    int num_blocks = (kNumElements*3 + num_threads - 1) / num_threads;
    AdjustGamma_kernel<<<num_blocks, num_threads, 0, processing_stream>>>(rgb888_src, rgb888_dst, gamma_lut_table, kNumElements);
    cudaStreamSynchronize(processing_stream);

    cudaFree(gamma_lut_table);
    gamma_lut_table = nullptr;
}

void AdjustContrast(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
    const size_t kNumElements, const float kContrast){

    uint8_t* contrast_lut_table;
    cudaMalloc(&contrast_lut_table, 256 * sizeof(uint8_t));

    PrepareContrastLutTable_kernel<<<1, 1, 0, processing_stream>>>(contrast_lut_table, kContrast);

    int num_threads = 256;// 32*8
    int num_blocks = (kNumElements*3 + num_threads - 1) / num_threads;
    AdjustContrast_kernel<<<num_blocks, num_threads, 0, processing_stream>>>(rgb888_src, rgb888_dst, contrast_lut_table, kNumElements);
    cudaStreamSynchronize(processing_stream);

    cudaFree(contrast_lut_table);
    contrast_lut_table = nullptr;
}

void AdjustBrightness(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
    const size_t kNumElements, const int32_t kBrightness){
    int num_threads = 256;// 32*8
    int num_blocks = (kNumElements*3 + num_threads - 1) / num_threads;
    AdjustBrightness_kernel<<<num_blocks, num_threads, 0, processing_stream>>>(rgb888_src, rgb888_dst, kNumElements, kBrightness);
    cudaStreamSynchronize(processing_stream);
}

}
