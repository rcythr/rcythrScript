
#include <rscript/datatypes/rational.h>

using namespace rscript;

std::string L_RATIONAL::str()
{
    return mNumerator->str() + "/" + mDenominator->str();
}
