#pragma once
#include <cstddef>
#include <cstdint>

namespace pimm::cpu {
void ApplyConvolutionGray(uint8_t* const src_gray, uint8_t* dst_gray, const int32_t kImageCols, const int32_t kImageRows,
    float* const kernel, const int32_t kKernelRows, const int32_t kKernelCols);
float* CreateGaussianKernel(const size_t kKernelSize, const float kSigma);

template<typename T>
T* CreatePaddedImageZeros(T* const grayImage, const size_t kRows, const size_t kCols, size_t kPadding);

// convert "rgb rgb rgb" to "rrr ggg bbb"
void Rgb32ToRgb888(uint8_t* const rgb32, uint8_t* rgb888, const size_t kRows, const size_t kCols);

// convert "rrr ggg bbb" to "rgb rgb rgb"
void Rgb888ToRgb32(uint8_t* const rgb888, uint8_t* rgb32, const size_t kRows, const size_t kCols);

}
