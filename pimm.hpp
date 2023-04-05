#include "constants.hpp"
#include <cstddef>
#include <cstdint>

namespace pimm{
uint8_t* allocateImageBytes(const size_t kWidth, const size_t kHeight,
    const COLOR_MODEL kColorModel, const PROCESSING_DEVICE kDevice);
void releaseImageBytes(uint8_t* imageBytes, const PROCESSING_DEVICE kDevice);
void copyImageBytesToDevice(uint8_t* from, uint8_t* to,
    const PROCESSING_DEVICE kDeviceSrc, const PROCESSING_DEVICE kDeviceDst,
    const size_t kNumBytes);
size_t getImageElementsNumber(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel);



void rgb_to_gray(uint8_t* rgbImage, uint8_t* gray,
    const int kWidth, const int kHeight,
    const PROCESSING_DEVICE kDevice, const GRAYSCALE_CONVERSION_TYPE kGrayConvType);

void invert_color(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const PROCESSING_DEVICE kDevice);

void solarise_color(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const uint8_t kThreshold, const PROCESSING_DEVICE kDevice);

void adjust_gamma(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const float kGamma, const PROCESSING_DEVICE kDevice);

void adjust_contrast(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const float kContrast, const PROCESSING_DEVICE kDevice);

void adjust_brightness(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const int32_t kBrightness, const PROCESSING_DEVICE kDevice);

}
