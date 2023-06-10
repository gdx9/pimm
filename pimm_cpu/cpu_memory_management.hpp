#pragma once
#include <cstdint>
#include <cstring>
#include "pimm_constants.hpp"
#include "pimm_utils.hpp"

namespace pimm::cpu {
uint8_t* AllocateImageMemoryBytes(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel);

void ReleaseImageMemoryBytes(uint8_t* image_bytes);

void CopyCpuToCpu(uint8_t* from, uint8_t* to, const size_t kNumBytes);
}
