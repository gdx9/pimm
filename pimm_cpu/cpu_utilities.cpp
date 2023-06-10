#include "cpu_utilities.hpp"
#include <cmath>

namespace pimm::cpu {

template <typename T>
T* CreateFlippedKernel(T* kernel, const size_t kKernelRows, const size_t kKernelCols){
    const size_t kKernelElements = kKernelRows*kKernelCols;

    T* flipped_kernel = new T[kKernelElements];
    for(size_t i = 0; i < kKernelElements; ++i){
        flipped_kernel[kKernelElements-i-1] = kernel[i];
    }

    return flipped_kernel;
}


void ApplyConvolutionGray(uint8_t* const src_gray, uint8_t* dst_gray, const int32_t kImageCols, const int32_t kImageRows,
    float* const kernel, const int32_t kKernelRows, const int32_t kKernelCols){
    // flip kernel
    const float* flipped_kernel = CreateFlippedKernel(kernel, kKernelRows, kKernelCols);

    // apply kernel zero-pad
    for(int32_t y = 0; y < kImageRows; ++y){
        for(int32_t x = 0; x < kImageCols; ++x){

            float sum = 0;
            for(int32_t kernel_y = 0; kernel_y < kKernelRows; ++kernel_y){
                for(int32_t kernel_x = 0; kernel_x < kKernelCols; ++kernel_x){

                    // image elements
                    int32_t pos_y = y - kKernelRows/2 + kernel_y;
                    int32_t pos_x = x - kKernelCols/2 + kernel_x;

                    // use border values
                    pos_y = (pos_y < 0) ? 0 : (pos_y > (kImageRows-1)) ? (kImageRows-1) : pos_y;
                    pos_x = (pos_x < 0) ? 0 : (pos_x > (kImageCols-1)) ? (kImageCols-1) : pos_x;

                    sum += static_cast<float>(
                        src_gray[pos_y * kImageCols + pos_x] / 256.f// scale for 0.0~1.0
                    ) * flipped_kernel[kernel_y * kKernelCols + kernel_x];
                }
            }
            dst_gray[y*kImageCols + x] = static_cast<uint8_t>(sum * 256.f);
        }
    }

    delete [] flipped_kernel;
    flipped_kernel = nullptr;

}

float* CreateGaussianKernel(const size_t kKernelSize, const float kSigma){
    const size_t kNumElements = kKernelSize*kKernelSize;
    float* kernel = new float[kNumElements];

    const int32_t kRadius = (kKernelSize - 1) / 2;
    float sum = 0.f;

    const float kDenom = 2 * kSigma * kSigma;
    // center coordinates are (0,0)
    for(int32_t y = -kRadius; y < kRadius; ++y){
        for(int32_t x = -kRadius; x < kRadius; ++x){
            const size_t kPos = (y + kRadius) * kKernelSize + (x + kRadius);
            float numer = static_cast<float>(x*x + y*y);
            kernel[kPos] = 1.f / (M_PI * kDenom) * exp(-numer / kDenom);
            sum += kernel[kPos];
        }
    }

    // normalize
    for(size_t i = 0; i < kNumElements; ++i){
        kernel[i] /= sum;
    }

    return kernel;
}

template<typename T>
T* CreatePaddedImageZeros(T* const grayImage, const size_t kRows, const size_t kCols, size_t kPadding){
    const size_t kRowsPadded = kRows + kPadding*2;
    const size_t kColsPadded = kCols + kPadding*2;
    T* image_padded = new T[kRowsPadded * kColsPadded];

    for(size_t yOrig = 0, yPad = kPadding; yOrig < kRows; ++yOrig, ++yPad){
        for(size_t xOrig = 0, xPad = kPadding; xOrig < kCols; ++xOrig, ++xPad){
            image_padded[yPad * kColsPadded + xPad] = grayImage[yOrig*kCols + xOrig];

        }
    }

    return image_padded;
}

<<<<<<< HEAD
=======
void Rgb32ToRgb888(uint8_t* const rgb32, uint8_t* rgb888, const size_t kRows, const size_t kCols){
    const size_t kPlaneSize = kRows * kCols;
    const size_t kNumElements = kPlaneSize * 3;

    uint8_t* r_plane_ptr = rgb888;
    uint8_t* g_plane_ptr = rgb888 + kPlaneSize;
    uint8_t* b_plane_ptr = g_plane_ptr + kPlaneSize;

    for(size_t r_pos_32 = 0, pos_888 = 0; r_pos_32 < kNumElements; r_pos_32 += 3, ++pos_888){
        r_plane_ptr[pos_888] = rgb32[r_pos_32];
        g_plane_ptr[pos_888] = rgb32[r_pos_32+1];
        b_plane_ptr[pos_888] = rgb32[r_pos_32+2];
    }
}

//template<typename T>
void Rgb888ToRgb32(uint8_t* const rgb888, uint8_t* rgb32, const size_t kRows, const size_t kCols){
    const size_t kPlaneSize = kRows * kCols;
    const size_t kNumElements = kPlaneSize * 3;

    uint8_t* r_plane_ptr = rgb888;
    uint8_t* g_plane_ptr = rgb888 + kPlaneSize;
    uint8_t* b_plane_ptr = g_plane_ptr + kPlaneSize;

    for(size_t r_pos_32 = 0, pos_888 = 0; r_pos_32 < kNumElements; r_pos_32 += 3, ++pos_888){
        rgb32[r_pos_32] = r_plane_ptr[pos_888];
        rgb32[r_pos_32+1] = g_plane_ptr[pos_888];
        rgb32[r_pos_32+2] = b_plane_ptr[pos_888];
    }
}

>>>>>>> develop
}
