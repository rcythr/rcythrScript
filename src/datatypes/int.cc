
#include <rscript/datatypes/int.h>

using namespace rscript;

std::string L_INT::str()
{
    return std::to_string(mValue);
}

