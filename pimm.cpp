#include "pimm.hpp"
#include "cpu_memory_management.hpp"
#include "cpu_conversions.hpp"
#include "pimm_utils.hpp"
#include "cpu_utilities.hpp"

using namespace std;

namespace pimm{

uint8_t* AllocateImageMemoryBytes(const size_t kWidth, const size_t kHeight,
    const COLOR_MODEL kColorModel, const PROCESSING_DEVICE kDevice){
    // CPU
    return cpu::AllocateImageMemoryBytes(kWidth, kHeight, kColorModel);
}

void ReleaseImageMemoryBytes(uint8_t* image_bytes, const PROCESSING_DEVICE kDevice){
    // CPU
    cpu::ReleaseImageMemoryBytes(image_bytes);
}

void CopyImageMemoryBytesToDevice(uint8_t* from, uint8_t* to,
    const PROCESSING_DEVICE kDeviceSrc, const PROCESSING_DEVICE kDeviceDst, const size_t kNumBytes){
    // to cpu
    cpu::CopyCpuToCpu(from, to, kNumBytes);
}
size_t GetNumElementsForColorModel(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel){
    return pimm::utils::GetNumElementsForColorModel(kWidth, kHeight, kColorModel);
}




void RgbToGray(uint8_t* const rgb, uint8_t* gray,
    const int kWidth, const int kHeight,
    const PROCESSING_DEVICE kDevice, const GRAYSCALE_CONVERSION_TYPE kGrayConvType){

    // CPU
    if(GRAYSCALE_CONVERSION_TYPE::MEAN == kGrayConvType)
        cpu::RgbToGrayMean(rgb, gray, kWidth*kHeight);
    else if(GRAYSCALE_CONVERSION_TYPE::WEIGHTED == kGrayConvType)
        cpu::RgbToGrayWeighted(rgb, gray, kWidth*kHeight);
}

void InvertColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::InvertColor(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3);
}

void SolariseColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const uint8_t kThreshold, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::SolariseColor(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kThreshold);

}

void AdjustGamma(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight,
    const float kGamma, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::AdjustGamma(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kGamma);
}

void AdjustContrast(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const float kContrast, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::AdjustContrast(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kContrast);
}

void AdjustBrightness(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const int32_t kBrightness, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::AdjustBrightness(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kBrightness);
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
