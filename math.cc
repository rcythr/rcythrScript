#include "builtins.h"

namespace rcythr
{

PL_ATOM proc_add(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_substract(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_multiply(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_divide(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_abs(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_quotient(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_remainder(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_modulo(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_gcd(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_lcm(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_expt(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_sqrt(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_numerator(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == LispType::RATIONAL)
        {
            return AS(L_RATIONAL,lst[0])->mNumerator;
        }
    }
    throw std::runtime_error("numerator requires a single argument which is of type Rational.");
}

PL_ATOM proc_denominator(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == LispType::RATIONAL)
        {
            return AS(L_RATIONAL,lst[0])->mDenominator;
        }
    }
    throw std::runtime_error("denominator requires a single argument which is of type Rational.");
}

PL_ATOM proc_is_rational(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        return WRAP(L_BOOL, lst[0]->mType == LispType::RATIONAL);
    }
    throw std::runtime_error("rational? requires a single argument.");
}

PL_ATOM proc_rationalize(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_floor(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_ceiling(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_truncate(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_round(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");

}

PL_ATOM proc_max(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_min(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_sin(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_cos(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_tan(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_asin(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_acos(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_atan(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_exp(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_log(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_inexact_to_exact(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_exact_to_inexact(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_exact(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_inexact(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_zero(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_negative(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_positive(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_odd(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_even(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_make_rectangular(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_make_polar(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_real_part(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == LispType::COMPLEX)
        {
            return AS(L_COMPLEX, lst[0])->mReal;
        }
    }
    throw std::runtime_error("real-part requires a single argument of type Complex.");
}

PL_ATOM proc_imag_part(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == LispType::COMPLEX)
        {
            return AS(L_COMPLEX, lst[0])->mImaginary;
        }
    }
    throw std::runtime_error("imag-part requires a single argument of type Complex.");
}

PL_ATOM proc_magnitude(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_angle(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_complex(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        return WRAP(L_BOOL, lst[0]->mType == LispType::COMPLEX);
    }
    throw std::runtime_error("complex? requires a single argument.");
}

PL_ATOM proc_is_integer(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        return WRAP(L_BOOL, lst[0]->mType == LispType::INT);
    }
    throw std::runtime_error("integer? requires a single argument.");
}

PL_ATOM proc_is_real(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        return WRAP(L_BOOL, lst[0]->mType == LispType::REAL);
    }
    throw std::runtime_error("real? requires a single argument.");
}

PL_ATOM proc_is_number(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    if(lst.size() == 1)
    {
        switch(lst[0]->mType)
        {
        case LispType::INT:
        case LispType::REAL:
        case LispType::RATIONAL:
        case LispType::COMPLEX:
            return WRAP(L_BOOL, true);if(lst.size() == 1)
        default:
            break;
        }
        return WRAP(L_BOOL, false);
    }
    throw std::runtime_error("number? requires a single argument.");
}

}
