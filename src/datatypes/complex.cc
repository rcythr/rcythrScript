
#include <rcythrScript/datatypes/complex.h>

using namespace rcythr;

std::string L_COMPLEX::str()
{
    return mReal->str() + "+" + mImaginary->str() + "i";
}
