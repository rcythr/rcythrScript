// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rcythrScript/builtins.h>
#include <rcythrScript/arithmetic.h>

namespace rcythr
{

constexpr size_t hashTypes(const LispType a, const LispType b) { return (((size_t)a) << 3) + ((size_t)b); }

std::unordered_map<size_t, std::function<PL_ATOM(PL_ATOM,PL_ATOM)>> addHandlers =
{
    { hashTypes(LispType::INT, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_INT, AS(L_INT, a)->mValue + AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(LispType::INT, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_INT, a)->mValue + AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(LispType::INT, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL, WRAP(L_INT, rat->mNumerator->mValue + (rat->mDenominator->mValue * AS(L_INT, a)->mValue)), rat->mDenominator);
        }
    },

    { hashTypes(LispType::INT, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX bComp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, add(a, bComp->mReal), bComp->mImaginary);
        },
    },

    { hashTypes(LispType::REAL, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue + AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(LispType::REAL, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue + AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(LispType::REAL, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, AS(L_REAL, a)->mValue + ((double)rat->mNumerator->mValue)/(rat->mDenominator->mValue));
        }
    },

    { hashTypes(LispType::REAL, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX bComp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, add(a, bComp->mReal), bComp->mImaginary);
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_RATIONAL, WRAP(L_INT, rat->mNumerator->mValue + (rat->mDenominator->mValue * AS(L_INT, b)->mValue)), rat->mDenominator);
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_REAL, AS(L_REAL, b)->mValue + ((double)rat->mNumerator->mValue)/(rat->mDenominator->mValue));
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::RATIONAL) ,
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

    { hashTypes(LispType::RATIONAL, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX bComp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, add(a, bComp->mReal), bComp->mImaginary);
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, add(b, aComp->mReal), aComp->mImaginary);
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, add(b, aComp->mReal), aComp->mImaginary);
        }
    },
    { hashTypes(LispType::COMPLEX, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX aComp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, add(b, aComp->mReal), aComp->mImaginary);
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::COMPLEX) ,
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
    { hashTypes(LispType::INT, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_INT, AS(L_INT, a)->mValue - AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(LispType::INT, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_INT, AS(L_INT, a)->mValue - AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(LispType::INT, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL,
                WRAP(L_INT, (AS(L_INT, a)->mValue * rat->mDenominator->mValue) - rat->mNumerator->mValue ),
                rat->mDenominator);
        }
    },

    { hashTypes(LispType::INT, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, sub(a, comp->mReal), neg(comp->mImaginary));
        },
    },

    { hashTypes(LispType::REAL, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue - AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(LispType::REAL, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue - AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(LispType::REAL, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, AS(L_REAL, a)->mValue - (((double)rat->mNumerator->mValue)/((double)rat->mDenominator->mValue)));
        }
    },

    { hashTypes(LispType::REAL, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, sub(a, comp->mReal), neg(comp->mImaginary));
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_RATIONAL,
                WRAP(L_INT, rat->mNumerator->mValue - (AS(L_INT, b)->mValue * rat->mDenominator->mValue)),
                rat->mDenominator);
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_REAL, ((double)rat->mNumerator->mValue)/((double)rat->mDenominator->mValue) - (AS(L_REAL, b)->mValue ));
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::RATIONAL) ,
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

    { hashTypes(LispType::RATIONAL, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                sub(a, comp->mReal),
                neg(comp->mImaginary));
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                sub(comp->mReal, b),
                comp->mImaginary);
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                sub(comp->mReal, b),
                comp->mImaginary);
        }
    },
    { hashTypes(LispType::COMPLEX, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                sub(comp->mReal, b),
                comp->mImaginary);
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::COMPLEX) ,
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
    { hashTypes(LispType::INT, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_INT, AS(L_INT, a)->mValue * AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(LispType::INT, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_INT, a)->mValue * AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(LispType::INT, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL, WRAP(L_INT, AS(L_INT, a)->mValue * rat->mNumerator->mValue), rat->mDenominator);
        }
    },

    { hashTypes(LispType::INT, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, mul(a, comp->mReal), mul(a, comp->mImaginary));
        },
    },

    { hashTypes(LispType::REAL, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue * AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(LispType::REAL, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue * AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(LispType::REAL, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, AS(L_REAL, a)->mValue * (((double)rat->mNumerator->mValue)/((double)rat->mDenominator->mValue)));
        }
    },

    { hashTypes(LispType::REAL, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, mul(a, comp->mReal), mul(a, comp->mImaginary));
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_RATIONAL, WRAP(L_INT, AS(L_INT, b)->mValue * rat->mNumerator->mValue), rat->mDenominator);
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_REAL, AS(L_REAL, b)->mValue * (((double)rat->mNumerator->mValue)/((double)rat->mDenominator->mValue)));
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL aRat = AS(L_RATIONAL, a);
            PL_RATIONAL bRat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL,
                    WRAP(L_INT, aRat->mNumerator->mValue * bRat->mNumerator->mValue),
                    WRAP(L_INT, aRat->mDenominator->mValue * bRat->mDenominator->mValue));
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX, mul(a, comp->mReal), mul(a, comp->mImaginary));
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, mul(b, comp->mReal), mul(b, comp->mImaginary));
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, mul(b, comp->mReal), mul(b, comp->mImaginary));
        }
    },
    { hashTypes(LispType::COMPLEX, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX, mul(b, comp->mReal), mul(b, comp->mImaginary));
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::COMPLEX) ,
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
    { hashTypes(LispType::INT, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_INT bInt = AS(L_INT, b);
            if(bInt->mValue == 0)
                throw std::runtime_error("Divide by 0 error.");
            return WRAP(L_INT, AS(L_INT, a)->mValue / bInt->mValue);
        }
    },

    { hashTypes(LispType::INT, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_INT, a)->mValue / AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(LispType::INT, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_RATIONAL,
                WRAP(L_INT, rat->mDenominator->mValue * AS(L_INT, a)->mValue),
                rat->mNumerator);
        }
    },

    { hashTypes(LispType::INT, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                div(a, comp->mReal),
                div(b, comp->mImaginary));
        },
    },

    { hashTypes(LispType::REAL, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue / AS(L_INT, b)->mValue);
        }
    },

    { hashTypes(LispType::REAL, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            return WRAP(L_REAL, AS(L_REAL, a)->mValue / AS(L_REAL, b)->mValue);
        }
    },

    { hashTypes(LispType::REAL, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, AS(L_REAL, a)->mValue * rat->mDenominator->mValue / rat->mNumerator->mValue);
        }
    },

    { hashTypes(LispType::REAL, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                div(a, comp->mReal),
                div(b, comp->mImaginary));
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, a);
            return WRAP(L_RATIONAL,
                rat->mNumerator,
                WRAP(L_INT, rat->mDenominator->mValue * AS(L_INT, b)->mValue));
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL rat = AS(L_RATIONAL, b);
            return WRAP(L_REAL, rat->mNumerator->mValue / rat->mDenominator->mValue / AS(L_REAL, a)->mValue );
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_RATIONAL aRat = AS(L_RATIONAL, a);
            PL_RATIONAL bRat = AS(L_RATIONAL, b);

            return WRAP(L_RATIONAL,
                WRAP(L_INT, aRat->mNumerator->mValue * bRat->mDenominator->mValue),
                WRAP(L_INT, aRat->mDenominator->mValue * bRat->mNumerator->mValue));
        }
    },

    { hashTypes(LispType::RATIONAL, LispType::COMPLEX) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, b);
            return WRAP(L_COMPLEX,
                div(a, comp->mReal),
                div(a, comp->mImaginary));
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::INT) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                div(comp->mReal, b),
                div(comp->mImaginary, b));
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::REAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                div(comp->mReal, b),
                div(comp->mImaginary, b));
        }
    },
    { hashTypes(LispType::COMPLEX, LispType::RATIONAL) ,
        [] (PL_ATOM a, PL_ATOM b) -> PL_ATOM
        {
            PL_COMPLEX comp = AS(L_COMPLEX, a);
            return WRAP(L_COMPLEX,
                div(comp->mReal, b),
                div(comp->mImaginary, b));
        }
    },

    { hashTypes(LispType::COMPLEX, LispType::COMPLEX) ,
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
    case LispType::INT:
        return WRAP(L_INT, -(AS(L_INT, a)->mValue));

    case LispType::REAL:
        return WRAP(L_REAL, -(AS(L_REAL, a)->mValue));

    case LispType::RATIONAL:
    {
        PL_RATIONAL rat = AS(L_RATIONAL, a);
        return WRAP(L_RATIONAL, WRAP(L_INT, -(rat->mNumerator->mValue)), rat->mDenominator);
    }

    case LispType::COMPLEX:
    {
        PL_COMPLEX comp = AS(L_COMPLEX, a);
        return WRAP(L_COMPLEX, neg(comp->mReal), neg(comp->mImaginary));
    }

    default:
        break;
    }
    throw std::runtime_error("Attempted to negate non numeric type.");
}

}
