
#include <rscript/datatypes/int.h>

using namespace rscript;

const DataType L_INT::type_value = DataType::INT;

std::string L_INT::str()
{
    return std::to_string(mValue);
}

