#pragma once
#include "pimm_constants.h"
#include "pimm_utils.h"
#include <cstdint>
#include <cstring>

namespace pimm::cpu {
    // memory management
    uint8_t* AllocateImageMemoryBytes(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel);
    void ReleaseImageMemoryBytes(uint8_t* image_bytes);
    void CopyCpuToCpu(uint8_t* from, uint8_t* to, const size_t kNumBytes);
    void ApplyConvolutionGray(uint8_t* const src_gray, uint8_t* dst_gray, const int32_t kImageCols, const int32_t kImageRows,
        float* const kernel, const int32_t kKernelRows, const int32_t kKernelCols);
    float* CreateGaussianKernel(const size_t kKernelSize, const float kSigma);

    // utilities
    template<typename T>
    T* CreatePaddedImageZeros(T* const grayImage, const size_t kRows, const size_t kCols, size_t kPadding);

    // convert "rgb rgb rgb" to "rrr ggg bbb"
    void Rgb32ToRgb888(uint8_t* const rgb32, uint8_t* rgb888, const size_t kRows, const size_t kCols);

    // convert "rrr ggg bbb" to "rgb rgb rgb"
    void Rgb888ToRgb32(uint8_t* const rgb888, uint8_t* rgb32, const size_t kRows, const size_t kCols);


    // conversions
    void RgbToGrayMean(uint8_t* const rgb888, uint8_t* gray, const size_t kSizeGray);
    void RgbToGrayWeighted(uint8_t* const rgb888, uint8_t* gray, const size_t kSizeGray);
    void InvertColor(uint8_t* const rgb888_src, uint8_t* rgb888_dst, const size_t kSize);
    void SolariseColor(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
        const size_t kSize, const uint8_t kThreshold);
    void AdjustGamma(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
        const size_t kSize, const float kGamma);
    void AdjustContrast(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
        const size_t kSize, const float kContrast);
    void AdjustBrightness(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
        const size_t kSize, const int32_t kBrightness);
}
