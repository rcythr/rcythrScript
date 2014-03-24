
#include <rscript/datatypes/real.h>

using namespace rscript;

std::string L_REAL::str()
{
    return std::to_string(mValue);
}
