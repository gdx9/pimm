#include "pimm.hpp"
#include "cpu_management.hpp"
#include "conversions.hpp"
#include "pimm_utils.hpp"
#include "cpu_utilities.hpp"

using namespace std;

namespace pimm{

uint8_t* allocate_image_bytes(const size_t kWidth, const size_t kHeight,
    const COLOR_MODEL kColorModel, const PROCESSING_DEVICE kDevice){
    // CPU
    return cpu::allocate_image_bytes(kWidth, kHeight, kColorModel);
}

void release_image_bytes(uint8_t* imageBytes, const PROCESSING_DEVICE kDevice){
    // CPU
    cpu::release_image_bytes(imageBytes);
}

void copy_image_bytes_to_device(uint8_t* from, uint8_t* to,
    const PROCESSING_DEVICE kDeviceSrc, const PROCESSING_DEVICE kDeviceDst, const size_t kNumBytes){
    // to cpu
    cpu::copy_cpu_2_cpu(from, to, kNumBytes);
}
size_t get_image_element_number(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel){
    return pimm::utils::get_image_element_number(kWidth, kHeight, kColorModel);
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

void invert_color(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::invert_color(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3);
}

void solarise_color(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const uint8_t kThreshold, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::solarise_color(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kThreshold);

}

void adjust_gamma(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight,
    const float kGamma, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::adjust_gamma(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kGamma);
}

void adjust_contrast(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const float kContrast, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::adjust_contrast(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kContrast);
}

void adjust_brightness(uint8_t* rgbImageSrc, uint8_t* rgbImageDst,
    const int kWidth, const int kHeight, const int32_t kBrightness, const PROCESSING_DEVICE kDevice){

    // CPU
    cpu::adjust_brightness(rgbImageSrc, rgbImageDst, kWidth * kHeight * 3, kBrightness);
}

void apply_kernel(uint8_t* src, uint8_t* dst, const size_t kImageCols, const size_t kImageRows,
    float* kernel, const size_t kKernelRows, const size_t kKernelCols){
    // CPU
    cpu::apply_kernel(src, dst, kImageCols, kImageRows, kernel, kKernelRows, kKernelCols);
}

float* get_gaussian_kernel(const size_t kKernelSize, const float kSigma){
    return utils::get_gaussian_kernel(kKernelSize, kSigma);
}

}
