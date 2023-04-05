#pragma once
#include <cstdint>
#include <cstring>
#include "constants.hpp"
#include "pimm_utils.hpp"
#include "constants.hpp"

namespace pimm::cpu {
uint8_t* allocate_image_bytes(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel);

void release_image_bytes(uint8_t* imageBytes);

void copy_cpu_2_cpu(uint8_t* from, uint8_t* to, const size_t kNumBytes);
}
