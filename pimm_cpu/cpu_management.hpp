#pragma once
#include <cstdint>
#include <cstring>
#include "constants.hpp"
#include "pimm_utils.hpp"
#include "constants.hpp"

namespace pimm::cpu {
uint8_t* allocateImageBytes(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel);

void releaseImageBytes(uint8_t* imageBytes);

void copyCpu2Cpu(uint8_t* from, uint8_t* to, const size_t kNumBytes);
}
