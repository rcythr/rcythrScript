// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rscript/builtins.h>
#include <rscript/arithmetic.h>
#include <rscript/constants.h>

namespace rscript
{

constexpr size_t hashTypes(const DataType a, const DataType b) { return (((size_t)a) << 3) + ((size_t)b); }

std::unordered_map<size_t, std::function<bool(PL_ATOM, PL_ATOM)>> numeqHandlers =
{
    { hashTypes(DataType::INT, DataType::INT),
        [] (PL_ATOM a, PL_ATOM b) -> bool
        {
            return AS(L_INT, a)->mValue == AS(L_INT, b)->mValue;
        }
    },
    { hashTypes(DataType::REAL, DataType::REAL),
        [] (PL_ATOM a, PL_ATOM b) -> bool
        {
            return AS(L_REAL, a)->mValue == AS(L_REAL, b)->mValue;
        }
    },
    { hashTypes(DataType::RATIONAL, DataType::RATIONAL),
        [] (PL_ATOM a, PL_ATOM b) -> bool
        {
            auto aRat = AS(L_RATIONAL, a);
            auto bRat = AS(L_RATIONAL, b);

            auto aNum = aRat->mNumerator->mValue;
            auto aDen = aRat->mDenominator->mValue;
            auto bNum = bRat->mNumerator->mValue;
            auto bDen = bRat->mDenominator->mValue;

            int agcd = steins_gcd(abs(aNum), abs(aDen));
            int bgcd = steins_gcd(abs(bNum), abs(bDen));

            if(agcd != 1)
            {
                aNum /= agcd;
                aDen /= agcd;
            }

            if(bgcd != 1)
            {
                bNum /= bgcd;
                bDen /= bgcd;
            }

            return (aNum == bNum) && (aDen == bDen);    
        }
    },
    { hashTypes(DataType::COMPLEX, DataType::COMPLEX),
        [] (PL_ATOM a, PL_ATOM b) -> bool
        {
            auto aComp = AS(L_COMPLEX, a);
            auto bComp = AS(L_COMPLEX, b);
            return num_eq(aComp->mReal, bComp->mReal) && num_eq(aComp->mImaginary, bComp->mImaginary);
        }
    },
};

std::unordered_map<size_t, std::function<PL_ATOM(PL_ATOM,PL_ATOM)>> addHandlers =
{
    { hashTypes(DataType::INT, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_INT, AS(L_INT, a)->mValue + AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(DataType::INT, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_INT, a)->mValue + AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(DataType::INT, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL, WRAP(L_INT, rat->mNumerator->mValue + (rat->mDenominator->mValue * AS(L_INT, a)->mValue)), rat->mDenominator);
        }
    },

    { hashTypes(DataType::INT, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX bComp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, add(a, bComp->mReal), bComp->mImaginary);
        },
    },

    { hashTypes(DataType::REAL, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue + AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(DataType::REAL, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue + AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(DataType::REAL, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, AS(L_REAL, a)->mValue + ((double)rat->mNumerator->mValue)/(rat->mDenominator->mValue));
        }
    },

    { hashTypes(DataType::REAL, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX bComp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, add(a, bComp->mReal), bComp->mImaginary);
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_RATIONAL, WRAP(L_INT, rat->mNumerator->mValue + (rat->mDenominator->mValue * AS(L_INT, b)->mValue)), rat->mDenominator);
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_REAL, AS(L_REAL, b)->mValue + ((double)rat->mNumerator->mValue)/(rat->mDenominator->mValue));
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM {
            PL_RATIONAL aRat = AS(L_RATIONAL, a);
            PL_RATIONAL bRat = AS(L_RATIONAL, b);

            if(aRat->mDenominator->mValue == bRat->mDenominator->mValue)
            {
                return WRAP(L_RATIONAL,
                    WRAP(L_INT, aRat->mNumerator->mValue + bRat->mNumerator->mValue),
                    aRat->mDenominator);
            }
            else
            {
                return WRAP(L_RATIONAL,
                        WRAP(L_INT, aRat->mNumerator->mValue * bRat->mDenominator->mValue + aRat->mDenominator->mValue * bRat->mNumerator->mValue),
                        WRAP(L_INT, aRat->mDenominator->mValue * bRat->mDenominator->mValue));
            }
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX bComp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, add(a, bComp->mReal), bComp->mImaginary);
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, add(b, aComp->mReal), aComp->mImaginary);
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, add(b, aComp->mReal), aComp->mImaginary);
        }
    },
    { hashTypes(DataType::COMPLEX, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, add(b, aComp->mReal), aComp->mImaginary);
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            PL_COMPLEX bComp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, add(aComp->mReal, bComp->mReal), add(aComp->mImaginary, bComp->mImaginary));
        }
    },
};

std::unordered_map<size_t, std::function<PL_ATOM(PL_ATOM,PL_ATOM)>> subHandlers =
{
    { hashTypes(DataType::INT, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_INT, AS(L_INT, a)->mValue - AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(DataType::INT, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_INT, AS(L_INT, a)->mValue - AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(DataType::INT, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL,
                WRAP(L_INT, (AS(L_INT, a)->mValue * rat->mDenominator->mValue) - rat->mNumerator->mValue ),
                rat->mDenominator);
        }
    },

    { hashTypes(DataType::INT, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, sub(a, comp->mReal), neg(comp->mImaginary));
        },
    },

    { hashTypes(DataType::REAL, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue - AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(DataType::REAL, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue - AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(DataType::REAL, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, AS(L_REAL, a)->mValue - (((double)rat->mNumerator->mValue)/((double)rat->mDenominator->mValue)));
        }
    },

    { hashTypes(DataType::REAL, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, sub(a, comp->mReal), neg(comp->mImaginary));
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_RATIONAL,
                WRAP(L_INT, rat->mNumerator->mValue - (AS(L_INT, b)->mValue * rat->mDenominator->mValue)),
                rat->mDenominator);
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_REAL, ((double)rat->mNumerator->mValue)/((double)rat->mDenominator->mValue) - (AS(L_REAL, b)->mValue ));
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL aRat = AS(L_RATIONAL, a);
            PL_RATIONAL bRat = AS(L_RATIONAL, b);

            if(aRat->mDenominator->mValue == bRat->mDenominator->mValue)
            {
                return WRAP(L_RATIONAL,
                        WRAP(L_INT, aRat->mNumerator->mValue - bRat->mNumerator->mValue),
                        aRat->mDenominator);
            }
            else
            {
                return WRAP(L_RATIONAL,
                        WRAP(L_INT, aRat->mNumerator->mValue * bRat->mDenominator->mValue - bRat->mNumerator->mValue * aRat->mDenominator->mValue),
                        WRAP(L_INT, aRat->mDenominator->mValue * bRat->mDenominator->mValue));
            }
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                sub(a, comp->mReal),
                neg(comp->mImaginary));
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                sub(comp->mReal, b),
                comp->mImaginary);
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                sub(comp->mReal, b),
                comp->mImaginary);
        }
    },
    { hashTypes(DataType::COMPLEX, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                sub(comp->mReal, b),
                comp->mImaginary);
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            PL_COMPLEX bComp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                sub(aComp->mReal, bComp->mReal),
                sub(aComp->mImaginary, bComp->mImaginary));
        }
    },
};

std::unordered_map<size_t, std::function<PL_ATOM(PL_ATOM,PL_ATOM)>> mulHandlers =
{
    { hashTypes(DataType::INT, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_INT, AS(L_INT, a)->mValue * AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(DataType::INT, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_INT, a)->mValue * AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(DataType::INT, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL, WRAP(L_INT, AS(L_INT, a)->mValue * rat->mNumerator->mValue), rat->mDenominator);
        }
    },

    { hashTypes(DataType::INT, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, mul(a, comp->mReal), mul(a, comp->mImaginary));
        },
    },

    { hashTypes(DataType::REAL, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue * AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(DataType::REAL, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue * AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(DataType::REAL, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, AS(L_REAL, a)->mValue * (((double)rat->mNumerator->mValue)/((double)rat->mDenominator->mValue)));
        }
    },

    { hashTypes(DataType::REAL, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, mul(a, comp->mReal), mul(a, comp->mImaginary));
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_RATIONAL, WRAP(L_INT, AS(L_INT, b)->mValue * rat->mNumerator->mValue), rat->mDenominator);
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_REAL, AS(L_REAL, b)->mValue * (((double)rat->mNumerator->mValue)/((double)rat->mDenominator->mValue)));
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL aRat = AS(L_RATIONAL, a);
            PL_RATIONAL bRat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL,
                    WRAP(L_INT, aRat->mNumerator->mValue * bRat->mNumerator->mValue),
                    WRAP(L_INT, aRat->mDenominator->mValue * bRat->mDenominator->mValue));
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, mul(a, comp->mReal), mul(a, comp->mImaginary));
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, mul(b, comp->mReal), mul(b, comp->mImaginary));
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, mul(b, comp->mReal), mul(b, comp->mImaginary));
        }
    },
    { hashTypes(DataType::COMPLEX, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, mul(b, comp->mReal), mul(b, comp->mImaginary));
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            PL_COMPLEX bComp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                sub( mul(aComp->mReal, bComp->mReal), mul(aComp->mImaginary, bComp->mImaginary)),
                add( mul(aComp->mReal, bComp->mImaginary), mul(aComp->mImaginary, bComp->mReal)));
        }
    },
};

std::unordered_map<size_t, std::function<PL_ATOM(PL_ATOM,PL_ATOM)>> divHandlers =
{
    { hashTypes(DataType::INT, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_INT bInt = AS(L_INT, b);
            if(bInt->mValue == 0)
                throw std::runtime_error("Divide by 0 error.");
            return WRAP(L_RATIONAL, AS(L_INT, a), bInt);
        }
    },

    { hashTypes(DataType::INT, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_INT, a)->mValue / AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(DataType::INT, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL,
                WRAP(L_INT, rat->mDenominator->mValue * AS(L_INT, a)->mValue),
                rat->mNumerator);
        }
    },

    { hashTypes(DataType::INT, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                div(a, comp->mReal),
                div(b, comp->mImaginary));
        },
    },

    { hashTypes(DataType::REAL, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue / AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(DataType::REAL, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue / AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(DataType::REAL, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, AS(L_REAL, a)->mValue * rat->mDenominator->mValue / rat->mNumerator->mValue);
        }
    },

    { hashTypes(DataType::REAL, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                div(a, comp->mReal),
                div(b, comp->mImaginary));
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_RATIONAL,
                rat->mNumerator,
                WRAP(L_INT, rat->mDenominator->mValue * AS(L_INT, b)->mValue));
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, rat->mNumerator->mValue / rat->mDenominator->mValue / AS(L_REAL, a)->mValue );
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL aRat = AS(L_RATIONAL, a);
            PL_RATIONAL bRat = AS(L_RATIONAL, b);

            return WRAP(L_RATIONAL,
                WRAP(L_INT, aRat->mNumerator->mValue * bRat->mDenominator->mValue),
                WRAP(L_INT, aRat->mDenominator->mValue * bRat->mNumerator->mValue));
        }
    },

    { hashTypes(DataType::RATIONAL, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                div(a, comp->mReal),
                div(a, comp->mImaginary));
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                div(comp->mReal, b),
                div(comp->mImaginary, b));
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                div(comp->mReal, b),
                div(comp->mImaginary, b));
        }
    },
    { hashTypes(DataType::COMPLEX, DataType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                div(comp->mReal, b),
                div(comp->mImaginary, b));
        }
    },

    { hashTypes(DataType::COMPLEX, DataType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            PL_COMPLEX bComp = AS(L_COMPLEX, b);

            return div(
                WRAP(L_COMPLEX,
                    add(mul(aComp->mReal, bComp->mReal), mul(aComp->mImaginary, bComp->mImaginary)),
                    sub(mul(aComp->mImaginary, bComp->mReal), mul(aComp->mReal, bComp->mImaginary))),
                add(mul(bComp->mReal, bComp->mReal), mul(bComp->mImaginary, bComp->mImaginary)));

        }
    },
};

bool num_eq(PL_ATOM a, PL_ATOM b)
{
    auto handler = numeqHandlers.find(hashTypes(a->mType, b->mType));
    if(handler != numeqHandlers.end())
    {
        return handler->second(a, b);
    }
    return false;
}

PL_ATOM add(PL_ATOM a, PL_ATOM b)
{
    auto handler = addHandlers.find(hashTypes(a->mType, b->mType));
    if(handler != addHandlers.end())
    {
        return handler->second(a, b);
    }
    throw std::runtime_error("Attempt to perform addition on unsupported operands.");
}

PL_ATOM sub(PL_ATOM a, PL_ATOM b)
{
    auto handler = subHandlers.find(hashTypes(a->mType, b->mType));
    if(handler != subHandlers.end())
    {
        return handler->second(a, b);
    }
    throw std::runtime_error("Attempt to perform subtraction on unsupported operands.");
}

PL_ATOM mul(PL_ATOM a, PL_ATOM b)
{
    auto handler = mulHandlers.find(hashTypes(a->mType, b->mType));
    if(handler != mulHandlers.end())
    {
        return handler->second(a, b);
    }
    throw std::runtime_error("Attempt to perform multiplication on unsupported operands.");
}

PL_ATOM div(PL_ATOM a, PL_ATOM b)
{
    auto handler = divHandlers.find(hashTypes(a->mType, b->mType));
    if(handler != divHandlers.end())
    {
        return handler->second(a, b);
    }
    throw std::runtime_error("Attempt to perform division on unsupported operands.");
}

PL_ATOM neg(PL_ATOM a)
{
    switch(a->mType)
    {
    case DataType::INT:
        return WRAP(L_INT, -(AS(L_INT, a)->mValue));

    case DataType::REAL:
        return WRAP(L_REAL, -(AS(L_REAL, a)->mValue));

    case DataType::RATIONAL:
    {
        PL_RATIONAL rat = AS(L_RATIONAL, a);
        return WRAP(L_RATIONAL, WRAP(L_INT, -(rat->mNumerator->mValue)), rat->mDenominator);
    }

    case DataType::COMPLEX:
    {
        PL_COMPLEX comp = AS(L_COMPLEX, a);
        return WRAP(L_COMPLEX, neg(comp->mReal), neg(comp->mImaginary));
    }

    default:
        break;
    }
    throw std::runtime_error("Attempted to negate non numeric type.");
}

int steins_gcd(int a, int b)
{
    if(a == b || b == 0)
    {
        return a;
    }
    else if(a == 0)
    {
        return b;
    }
    else if(~a & 1)
    {
        if(b & 1)
        {
            return steins_gcd(a >> 1, b);
        }
        else
        {
            return steins_gcd(a >> 1, b >> 1) << 1;
        }
    }
    else if(~b & 1)
    {
        return steins_gcd(a, b >> 1);
    }
    else if(a > b)
    {
        return steins_gcd((a - b) >> 1, b);
    }
    else
    {
        return steins_gcd((b - a) >> 1, a);
    }
}

}
