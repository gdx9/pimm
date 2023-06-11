#include "pimm_constants.h"
#include <cstddef>
#include <cstdint>

namespace pimm{
void Init();
void Close();

uint8_t* AllocateImageMemoryBytes(const size_t kWidth, const size_t kHeight,
    const COLOR_MODEL kColorModel, const PROCESSING_DEVICE kDevice);

void ReleaseImageMemoryBytes(uint8_t* image_bytes, const PROCESSING_DEVICE kDevice);

void CopyImageMemoryBytesToDevice(uint8_t* from, uint8_t* to,
    const PROCESSING_DEVICE kDeviceSrc, const PROCESSING_DEVICE kDeviceDst,
    const size_t kNumBytes);

size_t GetNumElementsForColorModel(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel);

void RgbToGray(uint8_t* const rgb888, uint8_t* gray,
    const int kWidth, const int kHeight,
    const PROCESSING_DEVICE kDevice, const GRAYSCALE_CONVERSION_TYPE kGrayConvType);

void InvertColor(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight, const PROCESSING_DEVICE kDevice);

void SolariseColor(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight, const uint8_t kThreshold, const PROCESSING_DEVICE kDevice);

void AdjustGamma(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight, const float kGamma, const PROCESSING_DEVICE kDevice);

void AdjustContrast(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight, const float kContrast, const PROCESSING_DEVICE kDevice);

void AdjustBrightness(uint8_t* rgb888_src, uint8_t* rgb888_dst,
    const int kWidth, const int kHeight, const int32_t kBrightness, const PROCESSING_DEVICE kDevice);

void ApplyConvolutionGray(uint8_t* const src_gray, uint8_t* dst_gray, const int32_t kImageCols, const int32_t kImageRows,
    float* const kernel, const int32_t kKernelRows, const int32_t kKernelCols);

float* CreateGaussianKernel(const size_t kKernelSize, const float kSigma);

void Rgb32ToRgb888(uint8_t* const rgb32, uint8_t* rgb888, const size_t kRows, const size_t kCols);
void Rgb888ToRgb32(uint8_t* const rgb888, uint8_t* rgb32, const size_t kRows, const size_t kCols);

}
