
#include <rscript/datatypes/rational.h>

using namespace rscript;

const DataType L_RATIONAL::type_value = DataType::RATIONAL;

std::string L_RATIONAL::str()
{
    return mNumerator->str() + "/" + mDenominator->str();
}
