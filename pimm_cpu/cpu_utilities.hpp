#pragma once
#include <cstddef>
#include <cstdint>

namespace pimm::cpu {
template <typename T>
T* flip_kernel(T* kernel, const size_t kKernelRows, const size_t kKernelCols);

void apply_kernel(uint8_t* src, uint8_t* dst, const size_t kImageCols, const size_t kImageRows,
    float* kernel, const size_t kKernelRows, const size_t kKernelCols);

template<typename T>
T* create_padded_image_zeros(T* const grayImage, const size_t kRows, const size_t kCols, size_t kPadding);

// convert "rgb rgb rgb" to "rrr ggg bbb"
//template<typename T>
void Rgb32ToRgb888(uint8_t* const rgb32, uint8_t* rgb888, const size_t kRows, const size_t kCols);


// convert "rrr ggg bbb" to "rgb rgb rgb"
//template<typename T>
void Rgb888ToRgb32(uint8_t* const rgb888, uint8_t* rgb32, const size_t kRows, const size_t kCols);

}
