
#include <rscript/datatypes/builtin_function.h>

#include <sstream>

using namespace rscript;

const DataType L_BUILTIN_FUNCTION::type_value = DataType::BUILTIN_FUNCTION;

std::string L_BUILTIN_FUNCTION::str()
{
    std::ostringstream oss;
    oss << "<BUILTIN FUNCTION @ " << std::hex << (size_t) this << ">";
    return oss.str();
}
