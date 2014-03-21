
#include <rcythrScript/datatypes/rational.h>

using namespace rcythr;

std::string L_RATIONAL::str()
{
    return mNumerator->str() + "/" + mDenominator->str();
}
