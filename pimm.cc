#include "pimm.h"
#include "pimm_utils.h"
#include "pimm_cpu.h"
#include "pimm_cuda.cuh"

using namespace std;

namespace pimm {
void Init(){
    cuda::init();
}
void Close(){
    cuda::close();
}

uint8_t* AllocateImageMemoryBytes(const size_t kWidth, const size_t kHeight,
    const COLOR_MODEL kColorModel, const PROCESSING_DEVICE kDevice){

    if(PROCESSING_DEVICE::CUDA == kDevice){
        // CUDA
        return cuda::AllocateImageMemoryBytes(kWidth, kHeight, kColorModel);

    }else{
        // CPU
        return cpu::AllocateImageMemoryBytes(kWidth, kHeight, kColorModel);
    }
}

void ReleaseImageMemoryBytes(uint8_t* image_bytes, const PROCESSING_DEVICE kDevice){
    if(PROCESSING_DEVICE::CUDA == kDevice){
        // CUDA
        cuda::ReleaseImageMemoryBytes(image_bytes);
    }else{
        // CPU
        cpu::ReleaseImageMemoryBytes(image_bytes);
    }
}

void CopyImageMemoryBytesToDevice(uint8_t* from, uint8_t* to,
    const PROCESSING_DEVICE kDeviceSrc, const PROCESSING_DEVICE kDeviceDst, const size_t kNumBytes){
    // to cpu
    if(PROCESSING_DEVICE::CPU == kDeviceSrc && kDeviceDst == PROCESSING_DEVICE::CPU){
        cpu::CopyCpuToCpu(from, to, kNumBytes);
    }

    if(PROCESSING_DEVICE::CPU == kDeviceSrc && kDeviceDst == PROCESSING_DEVICE::CUDA){
        cuda::CopyCpuToGpu(from, to, kNumBytes);
    }

    if(PROCESSING_DEVICE::CUDA == kDeviceSrc && kDeviceDst == PROCESSING_DEVICE::CUDA){
        cuda::CopyGpuToGpu(from, to, kNumBytes);
    }

    if(PROCESSING_DEVICE::CUDA == kDeviceSrc && kDeviceDst == PROCESSING_DEVICE::CPU){
        cuda::CopyGpuToCpu(from, to, kNumBytes);
    }

}
size_t GetNumElementsForColorModel(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel){
    return pimm::utils::GetNumElementsForColorModel(kWidth, kHeight, kColorModel);
}

void RgbToGray(uint8_t* const rgb888, uint8_t* gray,
    const int kWidth, const int kHeight,
    const PROCESSING_DEVICE kDevice, const GRAYSCALE_CONVERSION_TYPE kGrayConvType){

    if(PROCESSING_DEVICE::CUDA == kDevice){
        if(GRAYSCALE_CONVERSION_TYPE::MEAN == kGrayConvType)
            cuda::RgbToGrayMean(rgb888, gray, kWidth, kHeight);
        else if(GRAYSCALE_CONVERSION_TYPE::WEIGHTED == kGrayConvType)
            cuda::RgbToGrayWeighted(rgb888, gray, kWidth, kHeight);
    }else{
        // CPU
        if(GRAYSCALE_CONVERSION_TYPE::MEAN == kGrayConvType)
            cpu::RgbToGrayMean(rgb888, gray, kWidth*kHeight);
        else if(GRAYSCALE_CONVERSION_TYPE::WEIGHTED == kGrayConvType)
            cpu::RgbToGrayWeighted(rgb888, gray, kWidth*kHeight);
    }
}

void InvertColor(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight, const PROCESSING_DEVICE kDevice){

    if(PROCESSING_DEVICE::CUDA == kDevice){
        cuda::InvertColor(rgb888_src, rgb888_dst, kWidth * kHeight * 3);
    } else {
        // CPU
        cpu::InvertColor(rgb888_src, rgb888_dst, kWidth * kHeight * 3);

    }

}

void SolariseColor(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight, const uint8_t kThreshold, const PROCESSING_DEVICE kDevice){

    if(PROCESSING_DEVICE::CUDA == kDevice){
        cuda::SolariseColor(rgb888_src, rgb888_dst, kWidth * kHeight * 3, kThreshold);
    } else {
        // CPU
        cpu::SolariseColor(rgb888_src, rgb888_dst, kWidth * kHeight * 3, kThreshold);
    }
}

void AdjustGamma(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight,
    const float kGamma, const PROCESSING_DEVICE kDevice){

    if(PROCESSING_DEVICE::CUDA == kDevice){
        cuda::AdjustGamma(rgb888_src, rgb888_dst, kWidth * kHeight * 3, kGamma);
    } else {
        // CPU
        cpu::AdjustGamma(rgb888_src, rgb888_dst, kWidth * kHeight * 3, kGamma);
    }
}

void AdjustContrast(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight, const float kContrast, const PROCESSING_DEVICE kDevice){
    if(PROCESSING_DEVICE::CUDA == kDevice){
        cuda::AdjustContrast(rgb888_src, rgb888_dst, kWidth * kHeight * 3, kContrast);
    } else {
        // CPU
        cpu::AdjustContrast(rgb888_src, rgb888_dst, kWidth * kHeight * 3, kContrast);
    }
}

void AdjustBrightness(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight, const int32_t kBrightness, const PROCESSING_DEVICE kDevice){
    if(PROCESSING_DEVICE::CUDA == kDevice){
        cuda::AdjustBrightness(rgb888_src, rgb888_dst, kWidth * kHeight * 3, kBrightness);
    } else {
        // CPU
        cpu::AdjustBrightness(rgb888_src, rgb888_dst, kWidth * kHeight * 3, kBrightness);
    }
}

void ApplyConvolutionGray(uint8_t* const src_gray, uint8_t* dst_gray, const int32_t kImageCols, const int32_t kImageRows,
    float* const kernel, const int32_t kKernelRows, const int32_t kKernelCols){
    // CPU
    cpu::ApplyConvolutionGray(src_gray, dst_gray, kImageCols, kImageRows, kernel, kKernelRows, kKernelCols);
}

float* CreateGaussianKernel(const size_t kKernelSize, const float kSigma){
    return cpu::CreateGaussianKernel(kKernelSize, kSigma);
}

void Rgb32ToRgb888(uint8_t* const rgb32, uint8_t* rgb888, const size_t kRows, const size_t kCols){
    cpu::Rgb32ToRgb888(rgb32, rgb888, kRows, kCols);
}
void Rgb888ToRgb32(uint8_t* const rgb888, uint8_t* rgb32, const size_t kRows, const size_t kCols){
    cpu::Rgb888ToRgb32(rgb888, rgb32, kRows, kCols);
}

}
