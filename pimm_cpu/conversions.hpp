#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cmath>
#include "constants.hpp"

namespace pimm::cpu {
    void rgb_to_gray_mean(uint8_t* rgb, uint8_t* gray, const size_t kSize);
    void rgb_to_gray_weighted(uint8_t* rgb, uint8_t* gray, const size_t kSize);

    void invert_color(uint8_t* rgbImageSrc, uint8_t* rgbImageDst, const size_t kSize);

    void solarise_color(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
        const size_t kSize, const uint8_t kThreshold=128);

    void adjust_gamma(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
        const size_t kSize, const float kGamma);

    void adjust_contrast(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
        const size_t kSize, const float kContrast);

    void adjust_brightness(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
        const size_t kSize, const int32_t kBrightness);
}
