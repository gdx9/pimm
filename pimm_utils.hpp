#pragma once
#include "constants.hpp"

namespace pimm::utils{
size_t get_image_element_number(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel);

float* get_gaussian_kernel(const size_t kKernelSize, const float kSigma);

}
