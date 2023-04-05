#include "constants.hpp"
#include <cstddef>
#include <cstdint>

namespace pimm{
uint8_t* allocate_image_bytes(const size_t kWidth, const size_t kHeight,
    const COLOR_MODEL kColorModel, const PROCESSING_DEVICE kDevice);

void release_image_bytes(uint8_t* imageBytes, const PROCESSING_DEVICE kDevice);

void copy_image_bytes_to_device(uint8_t* from, uint8_t* to,
    const PROCESSING_DEVICE kDeviceSrc, const PROCESSING_DEVICE kDeviceDst,
    const size_t kNumBytes);

size_t get_image_element_number(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel);



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

void apply_kernel(uint8_t* src, uint8_t* dst, const size_t kImageCols, const size_t kImageRows,
    float* kernel, const size_t kKernelRows, const size_t kKernelCols);

float* get_gaussian_kernel(const size_t kKernelSize, const float kSigma);

}
