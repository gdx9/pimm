#include "pimm_cpu.h"
#include <cmath>

using namespace std;

namespace pimm {
void cpu::RgbToGrayMean(uint8_t* const rgb888, uint8_t* gray, const size_t kSizeGray){
    uint8_t* r = rgb888;
    uint8_t* g = r + kSizeGray;
    uint8_t* b = g + kSizeGray;

    for(size_t pos = 0; pos < kSizeGray; ++pos){
        int32_t val = (static_cast<int32_t>(r[pos])
                    + static_cast<int32_t>(g[pos])
                    + static_cast<int32_t>(b[pos])) / 3;
        // clip
        gray[pos] = static_cast<uint8_t>((val > 255) ? 255 : (val < 0) ? 0 : val);
    }
}

void cpu::RgbToGrayWeighted(uint8_t* const rgb888, uint8_t* gray, const size_t kSizeGray){
    uint8_t* r = rgb888;
    uint8_t* g = r + kSizeGray;
    uint8_t* b = g + kSizeGray;

    for(size_t pos = 0; pos < kSizeGray; ++pos){
        float val = (static_cast<float>(r[pos]) * 0.299f
                    + static_cast<float>(g[pos]) * 0.587f
                    + static_cast<float>(b[pos]) * 0.144f);
        // clip
        gray[pos] = static_cast<uint8_t>((val > 255.f) ? 255.f : (val < 0.f) ? 0.f : val);
    }
}

void cpu::InvertColor(uint8_t* const rgb888_src, uint8_t* rgb888_dst, const size_t kSize){
    for(size_t i = 0; i < kSize; ++i){
        rgb888_dst[i] = 255 - rgb888_src[i];
    }
}

void cpu::SolariseColor(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
    const size_t kSize, const uint8_t kThreshold){
    for(size_t i = 0; i < kSize; ++i){
        uint8_t val = rgb888_src[i];
        if(val < kThreshold) val = 255 - val;
        rgb888_dst[i] = val;
    }
}

uint8_t* PrepareGammaLutTable(const float kGamma){
    // prepare gamma lut table
    // increases speed: from approximately 48 ms to 16 ms
    const size_t kNumElements = 256;
    uint8_t* gamma_lut_table = new uint8_t[kNumElements];

    for(size_t i = 0; i < kNumElements; ++i){
        float val = pow(static_cast<float>(i) / 255.f, kGamma) * 255.f;

        // clip value
        gamma_lut_table[i] = static_cast<uint8_t>(
            (val < 0.f) ? 0.f : (val > 255.f) ? 255.f : val);
    }

    return gamma_lut_table;
}
void cpu::AdjustGamma(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
    const size_t kSize, const float kGamma){

    const uint8_t* const gamma_lut_table = PrepareGammaLutTable(kGamma);

    // apply gamma to image
    for(size_t i = 0; i < kSize; ++i){
        rgb888_dst[i] = gamma_lut_table[rgb888_src[i]];
    }

    delete [] gamma_lut_table;
}

uint8_t* PrepareContrastLutTable(const float kContrast){
    // prepare contrast lut table
    // increases speed: from approximately 15 ms to 8 ms
    const size_t kNumElements = 256;
    uint8_t* contrast_lut_table = new uint8_t[kNumElements];

    //F = 259*(255+contrast)/(255 *(259-contrast))
    const float kF = 259.f * (255.f + kContrast) / (255.f * (259.f - kContrast));

    for(size_t i = 0; i < kNumElements; ++i){
        float val = (kF * static_cast<float>(i - 128.f)) + 128.f;

        // clip value
        contrast_lut_table[i] = static_cast<uint8_t>((val < 0.f) ? 0.f : (val > 255.f) ? 255.f : val);
    }

    return contrast_lut_table;
}
void cpu::AdjustContrast(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
    const size_t kSize, const float kContrast){

    const uint8_t* const contrast_lut_table = PrepareContrastLutTable(kContrast);

    for(size_t i = 0; i < kSize; ++i){
        rgb888_dst[i] = contrast_lut_table[rgb888_src[i]];
    }

    delete [] contrast_lut_table;
}

void cpu::AdjustBrightness(uint8_t* const rgb888_src, uint8_t* rgb888_dst,
    const size_t kSize, const int32_t kBrightness){
    for(size_t i = 0; i < kSize; ++i){
        int32_t val = static_cast<int32_t>(rgb888_src[i]) + kBrightness;
        rgb888_dst[i] = static_cast<uint8_t>((val < 0) ? 0 : (val > 255) ? 255 : val);
    }
}

}
