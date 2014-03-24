// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include "atom.h"

namespace rscript
{

struct L_COMPLEX : public L_ATOM
{
    L_COMPLEX(PL_ATOM real, PL_ATOM imaginary)
        : L_ATOM(DataType::COMPLEX)
        , mReal(real)
        , mImaginary(imaginary)
    {
    }

    virtual std::string str();

    PL_ATOM mReal;
    PL_ATOM mImaginary;
};

typedef std::shared_ptr<L_COMPLEX> PL_COMPLEX;

}

