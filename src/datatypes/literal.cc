
#include <rcythrScript/datatypes/literal.h>

using namespace rcythr;

std::string L_LITERAL::str()
{
    return std::string("\'") + mLiteral->str();
}
