#include "constants.hpp"
#include "conversions.hpp"

void rgb_to_gray(uint8_t* rgbImage, uint8_t* gray,
    const int kWidth, const int kHeight,
    const PROCESSING_DEVICE kDevice, const GRAYSCALE_CONVERSION_TYPE kGrayConvType);

void invertColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const PROCESSING_DEVICE kDevice);

void solariseColor(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const uint8_t kThreshold, const PROCESSING_DEVICE kDevice);

void adjustGamma(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const float kGamma, const PROCESSING_DEVICE kDevice);

void adjustContrast(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const float kContrast, const PROCESSING_DEVICE kDevice);

void adjustBrightness(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const int32_t kBrightness, const PROCESSING_DEVICE kDevice);
