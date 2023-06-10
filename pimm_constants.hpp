#pragma once
#include <cstddef>

namespace pimm{
enum class PROCESSING_DEVICE{
    CPU = 0,
    GPU = 1
};

enum class GRAYSCALE_CONVERSION_TYPE{
    MEAN = 0,
    WEIGHTED = 1
};

enum class COLOR_MODEL{
    GRAY = 0,
    RGB32 = 1,
    RGB888 = 2,
    YCBCR444 = 3// TODO: ADD not supported
};

}
