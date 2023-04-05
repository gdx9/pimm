#include "pimm_utils.hpp"

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
}
