
#include <rcythrScript/rcythr.h>
#include <rcythrScript/constants.h>

using namespace rcythr;

PL_ATOM rcythr::parseList(const std::string& input, size_t& offset)
{
    char c;
    char opener = input.at(offset++);
    char closer;
    if(opener == '(' || opener == '[')
    {
        if(opener == '(')
            closer = ')';
        else
            closer = ']';

        std::forward_list<PL_ATOM> parts;
        auto bb = parts.before_begin();
        bool needsWS = false;

        while(offset < input.size())
        {
            c = input.at(offset);
            if(c == closer)
            {
                ++offset;
                return WRAP(L_LIST, std::move(parts));
            }
            else if(c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                needsWS = false;
                ++offset;
            }
            else
            {
                if(needsWS)
                {
                    throw std::runtime_error(std::string("Unexpected: '")+c+"', Expected some whitespace or '"+closer+'\'');
                }
                else
                {
                    bb = parts.insert_after(bb, parseExpression(input, offset));
                    needsWS = true;
                }
            }
        }
        throw std::runtime_error(std::string("Unmatched '")+opener+"'.");
    }
    throw std::runtime_error(std::string("Unexpected: '")+input[offset-1]+"', Expected '(' or '['");
}

std::string L_LIST::str()
{
    std::string output;
    output += '(';
    std::string sep;
    for(auto& element : mAtoms)
    {
        output += sep;
        output += element->str();
        sep = " ";
    }
    output += ')';

    return output;
}
