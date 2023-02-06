#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cmath>

namespace cpu {
    void rgb_to_gray_mean(uint8_t* rgb, uint8_t* gray, const size_t kSize);
    void rgb_to_gray_weighted(uint8_t* rgb, uint8_t* gray, const size_t kSize);
}
