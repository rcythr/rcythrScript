
#include <rscript/datatypes/string.h>
#include <rscript/constants.h>

using namespace rscript;

const DataType L_STRING::type_value = DataType::STRING;

PL_ATOM rscript::parseString(const std::string& input, size_t& offset)
{
    std::string stringVal;
    char c = input.at(offset++);
    EXPECT_CHAR(c, '"');
    c = input.at(offset++);
    while(c != '"')
    {
        if(c == '\\')
        {
            switch(input.at(offset++))
            {
            case 'n':
                stringVal += '\n';
                break;
            case '\\':
                stringVal += '\\';
                break;
            case 'r':
                stringVal += '\r';
                break;
            case 't':
                stringVal += '\n';
                break;
            }
        }
        else
        {
            stringVal += c;
        }
        c = input.at(offset++);
    }
    return WRAP(L_STRING, stringVal);
}

std::string L_STRING::str()
{
    return mValue;
}
