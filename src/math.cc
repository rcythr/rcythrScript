// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rscript/builtins.h>
#include <rscript/arithmetic.h>
#include <rscript/constants.h>

#include <cmath>

namespace rscript
{

PL_ATOM proc_eq(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() > 1)
    {
        PL_ATOM cmp = lst[0];
        for(size_t i=1; i < lst.size(); ++i)
        {
            if(cmp->mType != lst[i]->mType)
                return FALSE;

            if(!num_eq(cmp, lst[i]))
                return FALSE;
        }
        return TRUE;
    }
    throw std::runtime_error("= requires at least 2 arguments.");
}

PL_ATOM proc_lt(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_lte(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_gt(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_gte(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_add(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() > 0)
    {
        PL_ATOM ret = lst[0];
        for(size_t i=1; i < lst.size(); ++i)
        {
            ret = add(ret, lst[i]);
        }
        return ret;
    }
    throw std::runtime_error("+ requires one or more arguments.");
}

PL_ATOM proc_substract(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() > 0)
    {
        PL_ATOM ret = lst[0];
        for(size_t i=1; i < lst.size(); ++i)
        {
            ret = sub(ret, lst[i]);
        }
        return ret;
    }
    throw std::runtime_error("- requires one or more arguments.");
}

PL_ATOM proc_multiply(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() > 0)
    {
        PL_ATOM ret = lst[0];
        for(size_t i=1; i < lst.size(); ++i)
        {
            ret = mul(ret, lst[i]);
        }
        return ret;
    }
    throw std::runtime_error("* requires one or more arguments.");
}

PL_ATOM proc_divide(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() > 0)
    {
        PL_ATOM ret = lst[0];
        for(size_t i=1; i < lst.size(); ++i)
        {
            ret = div(ret, lst[i]);
        }
        return ret;
    }
    throw std::runtime_error("/ requires one or more arguments.");
}

PL_ATOM proc_abs(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        switch(lst[0]->mType)
        {
        case DataType::INT:
        {
            return WRAP(L_INT, abs(AS(L_INT, lst[0])->mValue));
        } 
        break;
            
        case DataType::REAL:
        {
            return WRAP(L_REAL, std::abs(AS(L_REAL, lst[0])->mValue));
        } 
        break;
        
        case DataType::RATIONAL:
        {
            PL_RATIONAL rational = AS(L_RATIONAL, lst[0]); 
            return WRAP(L_RATIONAL, 
                        WRAP(L_INT, abs(rational->mNumerator->mValue)), 
                        WRAP(L_INT, abs(rational->mDenominator->mValue)));
        } 
        break;

        default:
            throw std::runtime_error("Argument to abs must be an integer, real, or rational.");
        }
    }
    throw std::runtime_error("abs requires exactly one argument.");
}

PL_ATOM proc_quotient(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_remainder(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_modulo(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_gcd(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 2)
    {
        if(lst[0]->mType == lst[1]->mType && lst[0]->mType == DataType::INT)
        {
            auto a = abs(AS(L_INT, lst[0])->mValue);
            auto b = abs(AS(L_INT, lst[1])->mValue);
            return WRAP(L_INT, steins_gcd(a, b));
        }
    }
    throw std::runtime_error("gcd requires two integer arguments.");
}

PL_ATOM proc_lcm(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_expt(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_sqrt(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_numerator(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == DataType::RATIONAL)
        {
            return AS(L_RATIONAL,lst[0])->mNumerator;
        }
    }
    throw std::runtime_error("numerator requires a single argument which is of type Rational.");
}

PL_ATOM proc_denominator(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == DataType::RATIONAL)
        {
            return AS(L_RATIONAL,lst[0])->mDenominator;
        }
    }
    throw std::runtime_error("denominator requires a single argument which is of type Rational.");
}

PL_ATOM proc_is_rational(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        return WRAP(L_BOOL, lst[0]->mType == DataType::RATIONAL);
    }
    throw std::runtime_error("rational? requires a single argument.");
}

PL_ATOM proc_simplest(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == DataType::RATIONAL)
        {
            auto rat = AS(L_RATIONAL, lst[0]);
            int gcd = steins_gcd(rat->mNumerator->mValue, rat->mDenominator->mValue);
            if(gcd == 1)
            {
                return rat;
            }
            else
            {
                return WRAP(L_RATIONAL, 
                            WRAP(L_INT, rat->mNumerator->mValue / gcd), 
                            WRAP(L_INT, rat->mDenominator->mValue / gcd));
            }
        }
    }
    throw std::runtime_error("simplest takes exactly 1 argument of type Rational.");
}

PL_ATOM proc_rationalize(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_floor(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_ceiling(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_truncate(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_round(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");

}

PL_ATOM proc_max(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_min(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_sin(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_cos(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_tan(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_asin(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_acos(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_atan(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_exp(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_log(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_inexact_to_exact(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_exact_to_inexact(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_exact(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_inexact(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_zero(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_negative(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_positive(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_odd(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_even(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_make_rectangular(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_make_polar(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_real_part(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == DataType::COMPLEX)
        {
            return AS(L_COMPLEX, lst[0])->mReal;
        }
    }
    throw std::runtime_error("real-part requires a single argument of type Complex.");
}

PL_ATOM proc_imag_part(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        if(lst[0]->mType == DataType::COMPLEX)
        {
            return AS(L_COMPLEX, lst[0])->mImaginary;
        }
    }
    throw std::runtime_error("imag-part requires a single argument of type Complex.");
}

PL_ATOM proc_magnitude(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_angle(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_complex(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        return WRAP(L_BOOL, lst[0]->mType == DataType::COMPLEX);
    }
    throw std::runtime_error("complex? requires a single argument.");
}

PL_ATOM proc_is_integer(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        return WRAP(L_BOOL, lst[0]->mType == DataType::INT);
    }
    throw std::runtime_error("integer? requires a single argument.");
}

PL_ATOM proc_is_real(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        return WRAP(L_BOOL, lst[0]->mType == DataType::REAL);
    }
    throw std::runtime_error("real? requires a single argument.");
}

PL_ATOM proc_is_number(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() == 1)
    {
        switch(lst[0]->mType)
        {
        case DataType::INT:
        case DataType::REAL:
        case DataType::RATIONAL:
        case DataType::COMPLEX:
            return WRAP(L_BOOL, true);if(lst.size() == 1)
        default:
            break;
        }
        return WRAP(L_BOOL, false);
    }
    throw std::runtime_error("number? requires a single argument.");
}

enum class NumericParserState
{
    SIGN,
    INT,
    INT_PLUS,

    REAL_DOT,
    REAL_DOT_PLUS,

    REAL_EXP_SIGN,
    REAL_EXP,
    REAL_EXP_PLUS,

    RATIONAL_SIGN,
    RATIONAL,
    RATIONAL_PLUS,

    COMPLEX_SIGN,
    COMPLEX,
    COMPLEX_PLUS,
    COMPLEX_REAL_DOT,

    COMPLEX_REAL_EXP_SIGN,
    COMPLEX_REAL_EXP,

    COMPLEX_REAL_DOT_PLUS,
    COMPLEX_REAL_EXP_PLUS,

    COMPLEX_RATIONAL_SIGN,
    COMPLEX_RATIONAL,
    COMPLEX_RATIONAL_PLUS,
};

PL_ATOM parseNumeric(const std::string& input, size_t& offset)
{
    NumericParserState state = NumericParserState::SIGN;
    std::string buf1, buf2;
    PL_ATOM complex_left;
    char c;
    while(offset <= input.size())
    {

        if(offset == input.size())
            c = '\0';
        else
            c = input.at(offset);

        switch(state)
        {

        case NumericParserState::SIGN:
        {
            if(c == '+' || c == '-')
            {
                buf1 += c;
                state = NumericParserState::INT;
            }
            else if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::INT_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected + | - | 0-9 at beginning of parsing of numeric.");
            }
        } break;

        case NumericParserState::INT:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::INT_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected 0-9 at beginning of parsing of numeric.");
            }
        } break;

        case NumericParserState::INT_PLUS:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
            }
            else if(c == '/')
            {
                buf1 += c;
                state = NumericParserState::RATIONAL_SIGN;
            }
            else if(c == '.')
            {
                buf1 += c;
                state = NumericParserState::REAL_DOT;
            }
            else if(c == 'e' || c == 'E')
            {
                buf1 += 'e';
                state = NumericParserState::REAL_EXP_SIGN;
            }
            else if(c == '+')
            {
                complex_left = WRAP(L_INT, std::stoi(buf1));
                buf1.clear();
                state = NumericParserState::COMPLEX_SIGN;
            }
            else
            {
                return WRAP(L_INT, std::stoi(buf1));
            }
        } break;

        case NumericParserState::REAL_DOT:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::REAL_DOT_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected 0-9 after . token in parsing of numeric.");
            }
        } break;

        case NumericParserState::REAL_DOT_PLUS:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
            }
            else if(c == 'e' || c == 'E')
            {
                buf1 += 'e';
                state = NumericParserState::REAL_EXP_SIGN;
            }
            else if(c == '+')
            {
                complex_left = WRAP(L_REAL, std::stod(buf1));
                buf1.clear();
                state = NumericParserState::COMPLEX_SIGN;
            }
            else
            {
                return WRAP(L_REAL, std::stod(buf1));
            }
        } break;

        case NumericParserState::REAL_EXP_SIGN:
        {
            if(c == '+' || c == '-' )
            {
                buf1 += c;
                state = NumericParserState::REAL_EXP;
            }
            else if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::REAL_EXP_PLUS;
            }
            else
            {
                throw::std::runtime_error("Expected + | - | 0-9 parsing the beginning of exponent in numeric.");
            }
        } break;

        case NumericParserState::REAL_EXP:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::REAL_EXP_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected 0-9 after e token in parsing of exponent in numeric.");
            }
        } break;

        case NumericParserState::REAL_EXP_PLUS:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
            }
            else if(c == '+')
            {
                complex_left = WRAP(L_REAL, std::stod(buf1));
                buf1.clear();
                state = NumericParserState::COMPLEX_SIGN;
            }
            else
            {
                return WRAP(L_REAL, std::stod(buf1));
            }
        } break;

        case NumericParserState::RATIONAL_SIGN:
        {
            if(c == '-' || c == '+')
            {
                buf2 += c;
                state = NumericParserState::RATIONAL;
            }
            else if(c >= '0' && c <= '9')
            {
                buf2 += c;
                state = NumericParserState::RATIONAL_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected + | - | 0-9 at beginning of denominator in numeric.");
            }
        } break;

        case NumericParserState::RATIONAL:
        {
            if(c >= '0' && c <= '9')
            {
                buf2 += c;
                state = NumericParserState::RATIONAL_PLUS;
            }
            else
            {
                throw std::runtime_error("Denominator of rational must contain at least one number.");
            }
        } break;

        case NumericParserState::RATIONAL_PLUS:
        {
            if(c >= '0' && c <= '9')
            {
                buf2 += c;
            }
            else if(c == '+')
            {
                complex_left = WRAP(L_RATIONAL,
                                    WRAP(L_INT, std::stoi(buf1)),
                                    WRAP(L_INT, std::stoi(buf2)));

                buf1.clear();
                buf2.clear();
                state = NumericParserState::COMPLEX_SIGN;
            }
            else
            {
                return WRAP(L_RATIONAL,
                            WRAP(L_INT, std::stoi(buf1)),
                            WRAP(L_INT, std::stoi(buf2)));
            }
        } break;

        case NumericParserState::COMPLEX_SIGN:
        {
            if(c == '+' || c == '-')
            {
                buf1 += c;
                state = NumericParserState::COMPLEX;
            }
            else if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::COMPLEX_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected + | - | 0-9 at begining of parsing of imaginary component.");
            }
        } break;

        case NumericParserState::COMPLEX:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::COMPLEX_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected 0-9 at begining of parsing of imaginary component.");
            }
        } break;

        case NumericParserState::COMPLEX_PLUS:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
            }
            else if(c == '/')
            {
                buf1 += c;
                state = NumericParserState::COMPLEX_RATIONAL_SIGN;
            }
            else if(c == '.')
            {
                buf1 += c;
                state = NumericParserState::COMPLEX_REAL_DOT;
            }
            else if(c == 'e' || c == 'E')
            {
                buf1 += 'e';
                state = NumericParserState::COMPLEX_REAL_EXP_SIGN;
            }
            else if(c == 'i')
            {
                ++offset;
                return WRAP(L_COMPLEX,
                            complex_left,
                            WRAP(L_INT, std::stoi(buf1)));
            }
            else
            {
                throw std::runtime_error("Expected i at the end of the imaginary component of numeric.");
            }
        } break;

        case NumericParserState::COMPLEX_REAL_DOT:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::COMPLEX_REAL_DOT_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected 0-9 after . token in parsing of imaginary component of numeric.");
            }
        } break;

        case NumericParserState::COMPLEX_REAL_DOT_PLUS:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
                break;
            }
            else if(c == 'e' || c == 'E')
            {
                buf1 += 'e';
                state = NumericParserState::COMPLEX_REAL_EXP_SIGN;
            }
            else if(c == 'i')
            {
                ++offset;
                return WRAP(L_COMPLEX,
                            complex_left,
                            WRAP(L_REAL, std::stod(buf1)));
            }
            throw std::runtime_error("Expected i at the end of the imaginary component of numeric.");
        } break;

    case NumericParserState::COMPLEX_REAL_EXP_SIGN:
        {
            if(c == '+' || c == '-' )
            {
                buf1 += c;
                state = NumericParserState::COMPLEX_REAL_EXP;
            }
            else if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::COMPLEX_REAL_EXP_PLUS;
            }
            else
            {
                throw::std::runtime_error("Expected + | - | 0-9 parsing the beginning of exponent in imgaginary component of numeric.");
            }
        } break;

        case NumericParserState::COMPLEX_REAL_EXP:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
                state = NumericParserState::COMPLEX_REAL_EXP_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected 0-9 after e token in parsing of exponent in imaginary component of numeric.");
            }
        } break;

        case NumericParserState::COMPLEX_REAL_EXP_PLUS:
        {
            if(c >= '0' && c <= '9')
            {
                buf1 += c;
            }
            else if(c == 'i')
            {
                return WRAP(L_COMPLEX,
                            complex_left,
                            WRAP(L_REAL, std::stod(buf1)));
            }
            else
            {
                throw std::runtime_error("Expected i at the end of parsing imaginary component of numeric.");
            }
        } break;

        case NumericParserState::COMPLEX_RATIONAL_SIGN:
        {
            if(c == '-' || c == '+')
            {
                buf2 += c;
                state = NumericParserState::COMPLEX_RATIONAL;
            }
            else if(c >= '0' && c <= '9')
            {
                buf2 += c;
                state = NumericParserState::COMPLEX_RATIONAL_PLUS;
            }
            else
            {
                throw std::runtime_error("Expected + | - | 0-9 at beginning of denominator in imaginary component of numeric.");
            }
        } break;

        case NumericParserState::COMPLEX_RATIONAL:
        {
            if(c >= '0' && c <= '9')
            {
                buf2 += c;
                state = NumericParserState::COMPLEX_RATIONAL_PLUS;
            }
            else
            {
                throw std::runtime_error("Denominator of rational must contain at least one number.");
            }
        } break;

        case NumericParserState::COMPLEX_RATIONAL_PLUS:
        {
            if(c >= '0' && c <= '9')
            {
                buf2 += c;
            }
            else if(c == 'i')
            {
                ++offset;
                return  WRAP(L_COMPLEX,
                                complex_left,
                                WRAP(L_RATIONAL,
                                    WRAP(L_INT, std::stoi(buf1)),
                                    WRAP(L_INT, std::stoi(buf2))));
            }
            else
            {
                throw std::runtime_error("Expected i at the end of parsing imaginary component of numeric.");
            }
        } break;

        }

        ++offset;
    }
    throw std::runtime_error("Failed to parse numeric.");
}

}
