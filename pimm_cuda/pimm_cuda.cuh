#pragma once
#include "pimm_constants.h"
#include "pimm_utils.h"
#include <cstdint>
#include <cstring>

namespace pimm::cuda {
    // memory management
    void init();
    void close();

    uint8_t* AllocateImageMemoryBytes(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel);
    void ReleaseImageMemoryBytes(uint8_t* image_bytes);

    void CopyCpuToGpu(uint8_t* from, uint8_t* to, const size_t kNumBytes);
    void CopyGpuToGpu(uint8_t* from, uint8_t* to, const size_t kNumBytes);
    void CopyGpuToCpu(uint8_t* from, uint8_t* to, const size_t kNumBytes);

    // conversions
    void RgbToGrayMean(uint8_t* const rgb888, uint8_t* gray, const size_t kWidth, const size_t kHeight);
    void RgbToGrayWeighted(uint8_t* const rgb888, uint8_t* gray, const size_t kWidth, const size_t kHeight);
    void InvertColor(uint8_t* const rgb888_src, uint8_t* rgb888_dst, const size_t kNumElements);
    void SolariseColor(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
        const size_t kNumElements, const uint8_t kThreshold);
    void AdjustGamma(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
        const size_t kNumElements, const float kGamma);
    void AdjustContrast(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
        const size_t kNumElements, const float kContrast);
    void AdjustBrightness(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
        const size_t kNumElements, const int32_t kBrightness);

}
