
#include <rscript/datatypes/complex.h>

using namespace rscript;

std::string L_COMPLEX::str()
{
    return mReal->str() + "+" + mImaginary->str() + "i";
}
