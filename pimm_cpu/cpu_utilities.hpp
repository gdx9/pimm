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

}
