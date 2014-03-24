
#include <rscript/datatypes/symbol.h>

#include <rscript/constants.h>

using namespace rscript;

PL_ATOM rscript::parseSymbol(const std::string& input, size_t& offset)
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

