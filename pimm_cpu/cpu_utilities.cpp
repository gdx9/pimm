#include "cpu_utilities.hpp"

namespace pimm::cpu {
template <typename T>
T* flip_kernel(T* kernel, const size_t kKernelRows, const size_t kKernelCols){
    const size_t kKernelElements = kKernelRows*kKernelCols;

    T* flippedKernel = new T[kKernelElements];
    for(size_t i = 0; i < kKernelElements; ++i){
        flippedKernel[kKernelElements-i-1] = kernel[i];
    }

    return flippedKernel;
}


void apply_kernel(uint8_t* src, uint8_t* dst, const size_t kImageCols, const size_t kImageRows,
    float* kernel, const size_t kKernelRows, const size_t kKernelCols){
    // flip kernel
    float* flippedKernel = flip_kernel(kernel, kKernelRows, kKernelCols);

    const size_t kKernelSize = kKernelRows * kKernelCols;

    // apply kernel zero-pad
    for(int32_t y = 0; y < kImageRows; ++y){
        for(int32_t x = 0; x < kImageCols; ++x){

            float sum = 0;
            for(int32_t kr = 0; kr < kKernelRows; ++kr){
                for(int32_t kc = 0; kc < kKernelCols; ++kc){

                    // image elements
                    int32_t posIy = y - kKernelRows/2 + kr;
                    int32_t posIx = x - kKernelCols/2 + kc;

                    // mirroring
                    posIy = (posIy < 0) ? 0 : (posIy > (kImageRows-1)) ? (kImageRows-1) : posIy;
                    posIx = (posIx < 0) ? 0 : (posIx > (kImageCols-1)) ? (kImageCols-1) : posIx;

                    sum += static_cast<float>(
                        src[posIy * kImageCols + posIx] / 256.f// scale for 0.0~1.0
                    ) * flippedKernel[kr * kKernelCols + kc];
                }
            }
            dst[y*kImageCols + x] = static_cast<uint8_t>(sum * 256.f);
        }
    }

    delete [] flippedKernel;
    flippedKernel = nullptr;

}

template<typename T>
T* create_padded_image_zeros(T* const grayImage, const size_t kRows, const size_t kCols, size_t kPadding){
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

}
