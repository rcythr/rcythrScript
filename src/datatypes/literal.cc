
#include <rscript/datatypes/literal.h>

using namespace rscript;

std::string L_LITERAL::str()
{
    return std::string("\'") + mLiteral->str();
}
