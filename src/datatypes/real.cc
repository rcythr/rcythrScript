
#include <rscript/datatypes/real.h>

using namespace rscript;

const DataType L_REAL::type_value = DataType::REAL;

std::string L_REAL::str()
{
    return std::to_string(mValue);
}
