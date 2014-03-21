
#include <rcythrScript/datatypes/builtin_function.h>

#include <sstream>

using namespace rcythr;

std::string L_BUILTIN_FUNCTION::str()
{
    std::ostringstream oss;
    oss << "<BUILTIN FUNCTION @ " << std::hex << (size_t) this << ">";
    return oss.str();
}
