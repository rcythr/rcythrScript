
#include <rscript/datatypes/char.h>
#include <rscript/constants.h>

using namespace rscript;

PL_ATOM rscript::parseChar(const std::string& input, size_t& offset)
{
    EXPECT_CHAR(input.at(offset++), '#');
    EXPECT_CHAR(input.at(offset++), '\\');
    return WRAP(L_CHAR, input.at(offset++));
}

std::string L_CHAR::str()
{
    std::string output;
    output += "#\\";
    output += mValue;
    return output;
}

