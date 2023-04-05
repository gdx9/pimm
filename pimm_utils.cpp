#include "pimm_utils.hpp"
#include <cmath>

using namespace std;
namespace pimm::utils{
size_t get_image_element_number(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel){
    switch(kColorModel){
        case COLOR_MODEL::GRAY:
            return kWidth * kHeight;
        case COLOR_MODEL::RGB444:
        case COLOR_MODEL::YCBCR444:
            return kWidth * kHeight * 3;
        default:
            // not supported color model
            return 0;
    }
}

float* get_gaussian_kernel(const size_t kKernelSize, const float kSigma){
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

}
