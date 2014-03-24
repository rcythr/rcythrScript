
#include <rscript/datatypes/complex.h>

using namespace rscript;

const DataType L_COMPLEX::type_value = DataType::COMPLEX;

std::string L_COMPLEX::str()
{
    return mReal->str() + "+" + mImaginary->str() + "i";
}
