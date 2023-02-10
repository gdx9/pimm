#include "cpu_management.hpp"

using namespace pimm::utils;

namespace pimm{

uint8_t* cpu::allocateImageBytes(const size_t kWidth, const size_t kHeight, const COLOR_MODEL kColorModel){
    const size_t kNumElements = getImageElementsNumber1(kWidth, kHeight, kColorModel);
    if(kNumElements == 0){
        return nullptr;
    }

    return new uint8_t[kNumElements];
}

void cpu::releaseImageBytes(uint8_t* imageBytes){
    delete [] imageBytes;
    imageBytes = nullptr;
}

void cpu::copyCpu2Cpu(uint8_t* from, uint8_t* to, const size_t kNumBytes){
    memcpy(to, from, kNumBytes);
}

}
