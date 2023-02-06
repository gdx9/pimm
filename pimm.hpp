#include "constants.hpp"
#include "conversions.hpp"

void rgb_to_gray(uint8_t* rgbImage, uint8_t* gray,
    const int kWidth, const int kHeight,
    const PROCESSING_DEVICE kDevice, const GRAYSCALE_CONVERSION_TYPE kGrayConvType);
