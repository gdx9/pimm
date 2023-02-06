#include "conversions.hpp"

using namespace std;

void cpu::rgb_to_gray_mean(uint8_t* rgb, uint8_t* gray, const size_t kSize){
    for(size_t i = 0; i < kSize; ++i){
        size_t rpos = i*3;
        int32_t val = (static_cast<int32_t>(rgb[rpos + 0])
            + static_cast<int32_t>(rgb[rpos + 1])
            + static_cast<int32_t>(rgb[rpos + 2])) / 3;
        // clip
        gray[i] = static_cast<uint8_t>((val > 255) ? 255 : (val < 0) ? 0 : val);
    }
}

void cpu::rgb_to_gray_weighted(uint8_t* rgb, uint8_t* gray, const size_t kSize){
    for(size_t i = 0; i < kSize; ++i){
        size_t rpos = i*3;
        float val = (static_cast<float>(rgb[rpos + 0]) * 0.299f
            + static_cast<float>(rgb[rpos + 1]) * 0.587f
            + static_cast<float>(rgb[rpos + 2]) * 0.144f);
        // clip
        gray[i] = static_cast<uint8_t>((val > 255.f) ? 255.f : (val < 0.f) ? 0.f : val);
    }
}
