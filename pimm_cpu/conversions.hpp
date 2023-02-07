#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cmath>

namespace cpu {
    void rgb_to_gray_mean(uint8_t* rgb, uint8_t* gray, const size_t kSize);
    void rgb_to_gray_weighted(uint8_t* rgb, uint8_t* gray, const size_t kSize);

    void invertColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst, const size_t kSize);

    void solariseColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
        const size_t kSize, const uint8_t kThreshold=128);
}
