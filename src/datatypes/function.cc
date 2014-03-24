
#include <rscript/datatypes/function.h>

#include <sstream>

using namespace rscript;

const DataType L_FUNCTION::type_value = DataType::FUNCTION;

std::string L_FUNCTION::str()
{
    std::ostringstream oss;
    oss << "<FUNCTION @ "<< std::hex << (size_t) this << ">";
    return oss.str();
}
