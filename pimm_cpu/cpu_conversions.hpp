#pragma once
#include "pimm_constants.hpp"
#include <cstdint>

namespace pimm::cpu {
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
