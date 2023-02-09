#include "pimm.hpp"

using namespace std;

void rgb_to_gray(uint8_t* rgb, uint8_t* gray,
    const int kWidth, const int kHeight,
    const PROCESSING_DEVICE kDevice, const GRAYSCALE_CONVERSION_TYPE kGrayConvType){

    // CPU
    if(GRAYSCALE_CONVERSION_TYPE::MEAN == kGrayConvType)
        cpu::rgb_to_gray_mean(rgb, gray, kWidth*kHeight);
    else if(GRAYSCALE_CONVERSION_TYPE::WEIGHTED == kGrayConvType)
        cpu::rgb_to_gray_weighted(rgb, gray, kWidth*kHeight);
}

void invertColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::invertColor(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3);
}

void solariseColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const uint8_t kThreshold, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::solariseColor(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kThreshold);

}

void adjustGamma(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight,
    const float kGamma, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::adjustGamma(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kGamma);
}

void adjustContrast(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const float kContrast, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::adjustContrast(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kContrast);
}

void adjustBrightness(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const int32_t kBrightness, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::adjustBrightness(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kBrightness);
}
