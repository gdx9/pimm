#include "conversions.hpp"

using namespace std;

namespace pimm{

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

void cpu::invertColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst, const size_t kSize){
    for(size_t i = 0; i < kSize; ++i){
        rgbImageDst[i] = 255 - rgbImageSrc[i];
    }
}

void cpu::solariseColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const size_t kSize, const uint8_t kThreshold){
    for(size_t i = 0; i < kSize; ++i){
        uint8_t val = rgbImageSrc[i];
        if(val < kThreshold) val = 255 - val;
        rgbImageDst[i] = val;
    }
}

void cpu::adjustGamma(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const size_t kSize, const float kGamma){
    for(size_t i = 0; i < kSize; ++i){
        float val = pow((static_cast<float>(rgbImageSrc[i]) / 255.f), kGamma) * 255.f;
        // clip value
        rgbImageDst[i] = static_cast<uint8_t>((val < 0.f) ? 0.f : (val > 255.f) ? 255.f : val);
    }
}

void cpu::adjustContrast(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const size_t kSize, const float kContrast){
    //F = 259*(255+contrast)/(255 *(259-contrast))
    const float kF = 259.f * (255.f + kContrast) / (255.f * (259.f - kContrast));

    for(size_t i = 0; i < kSize; ++i){
        float val = (kF * (static_cast<float>(rgbImageSrc[i]) - 128.f)) + 128.f;
        // clip value
        rgbImageDst[i] = static_cast<uint8_t>((val < 0.f) ? 0.f : (val > 255.f) ? 255.f : val);
    }
}

void cpu::adjustBrightness(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const size_t kSize, const int32_t kBrightness){
    for(size_t i = 0; i < kSize; ++i){
        int32_t val = static_cast<int32_t>(rgbImageSrc[i]) + kBrightness;
        rgbImageDst[i] = static_cast<uint8_t>((val < 0) ? 0 : (val > 255) ? 255 : val);
    }
}

}
