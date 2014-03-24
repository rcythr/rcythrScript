
#include <rscript/datatypes/literal.h>

using namespace rscript;

const DataType L_LITERAL::type_value = DataType::LITERAL;

std::string L_LITERAL::str()
{
    return std::string("\'") + mLiteral->str();
}
