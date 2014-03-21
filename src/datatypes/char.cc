
#include <rcythrScript/datatypes/char.h>
#include <rcythrScript/constants.h>

using namespace rcythr;

PL_ATOM rcythr::parseChar(const std::string& input, size_t& offset)
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

