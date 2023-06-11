#include "pimm_cpu.h"

using namespace pimm::utils;

namespace pimm::cpu {

uint8_t* AllocateImageMemoryBytes(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel){
    const size_t kNumElements = GetNumElementsForColorModel(kWidth, kHeight, kColorModel);
    if(kNumElements == 0){
        return nullptr;
    }

    return new uint8_t[kNumElements];
}

void ReleaseImageMemoryBytes(uint8_t* image_bytes){
    delete [] image_bytes;
    image_bytes = nullptr;
}

void CopyCpuToCpu(uint8_t* from, uint8_t* to, const size_t kNumBytes){
    memcpy(to, from, kNumBytes);
}

}
