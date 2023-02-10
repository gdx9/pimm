#include "pimm.hpp"
#include "cpu_management.hpp"
#include "conversions.hpp"
#include "pimm_utils.hpp"

using namespace std;
using namespace pimm::utils;

namespace pimm{

uint8_t* allocateImageBytes(const size_t kWidth, const size_t kHeight,
    const COLOR_MODEL kColorModel, const PROCESSING_DEVICE kDevice){
    // CPU
    return cpu::allocateImageBytes(kWidth, kHeight, kColorModel);
}

void releaseImageBytes(uint8_t* imageBytes, const PROCESSING_DEVICE kDevice){
    // CPU
    cpu::releaseImageBytes(imageBytes);
}

void copyImageBytesToDevice(uint8_t* from, uint8_t* to,
    const PROCESSING_DEVICE kDeviceSrc, const PROCESSING_DEVICE kDeviceDst, const size_t kNumBytes){
    // to cpu
    cpu::copyCpu2Cpu(from, to, kNumBytes);
}
size_t getImageElementsNumber(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel){
    return getImageElementsNumber1(kWidth, kHeight, kColorModel);
}




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
}
