
#include <rcythrScript/datatypes/symbol.h>

#include <rcythrScript/constants.h>

using namespace rcythr;

PL_ATOM rcythr::parseSymbol(const std::string& input, size_t& offset)
{
    std::string symbolName;
    char c;
    while( offset < input.size())
    {
        c = input.at(offset);
        if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '$' && c <= '&') ||
            (c >= '0' && c <= '9') || (c >= '<' && c <= '?') ||  c == '!' || c == '*'  ||
             c == '/' || c == ':'  ||  c == '^' || c == '_'  ||  c == '~' || c == '.'  ||
             c == '+' || c == '-')
         {
            symbolName += c;
         }
         else
         {
            break;
         }
         ++offset;
    }
    return WRAP(L_SYMBOL, symbolName);
}

std::string L_SYMBOL::str()
{
    return mName;
}

