#pragma once
#include <cstddef>

namespace pimm{
enum class PROCESSING_DEVICE{
    CPU = 0
};

enum class GRAYSCALE_CONVERSION_TYPE{
    MEAN = 0,
    WEIGHTED = 1
};

enum class COLOR_MODEL{
    GRAY = 0,
    RGB444 = 1,
    YCBCR444 = 2// TODO: ADD not supported
};

}
