
#include <rcythrScript/datatypes/bool.h>
#include <rcythrScript/constants.h>

using namespace rcythr;

PL_ATOM rcythr::parseBool(const std::string& input, size_t& offset)
{
    EXPECT_CHAR(input.at(offset++), '#');
    switch(input.at(offset++))
    {
    case 't':
    case 'T':
        return TRUE;

    case 'f':
    case 'F':
        return FALSE;

    default:
        UNEXPECTED_TOKEN(input.at(offset-1), "t/T or f/F");
    }
}

std::string L_BOOL::str()
{
    if(mValue)
        return std::string("#t");
    else
        return std::string("#f");
}

