// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rcythrScript/rcythr.h>
#include <rcythrScript/builtins.h>

namespace rcythr
{

void tryToString(PL_ATOM expr, std::string& output);

void toString(PL_LITERAL expr, std::string& output)
{
    output += '\'';
    tryToString(expr->mLiteral, output);
}

void toString(PL_BOOL expr, std::string& output)
{
    if(expr->mValue)
        output += "#t";
    else
        output += "#f";
}

void toString(PL_LIST expr, std::string& output)
{
    output += '(';
    std::string sep;
    for(auto& element : expr->mAtoms)
    {
        output += sep;
        tryToString(element, output);
        sep = " ";
    }
    output += ')';
}

void toString(PL_VECTOR expr, std::string& output)
{
    output += "#(";
    std::string sep;
    for(auto& element : expr->mAtoms)
    {
        output += sep;
        tryToString(element, output);
        sep = " ";
    }
    output += ')';
    output += ')';
}

void toString(PL_CHAR expr, std::string& output)
{
    output += "#\\";
    output += expr->mValue;
}

void toString(PL_STRING expr, std::string& output)
{
    output += expr->mValue;
}

void toString(PL_SYMBOL expr, std::string& output)
{
    output += expr->mName;
}

void toString(PL_INT expr, std::string& output)
{
    output += std::to_string(expr->mValue);
}

void toString(PL_REAL expr, std::string& output)
{
    output += std::to_string(expr->mValue);
}

void toString(PL_RATIONAL expr, std::string& output)
{
    toString(expr->mNumerator, output);
    output += '/';
    toString(expr->mDenominator, output);
}

void toString(PL_COMPLEX expr, std::string& output)
{
    tryToString(expr->mReal, output);
    output += '+';
    tryToString(expr->mImaginary, output);
    output += "i";
}

void toString(PL_BUILTIN_FUNCTION expr, std::string& output)
{
}

void toString(PL_FUNCTION expr, std::string& output)
{
}

void tryToString(PL_ATOM expr, std::string& output)
{
    switch(expr->mType)
    {
    case LispType::LIST:
        toString(AS(L_LIST, expr), output);
        return;
    case LispType::VECTOR:
        toString(AS(L_VECTOR, expr), output);
        return;
    case LispType::BOOL:
        toString(AS(L_BOOL, expr), output);
        return;
    case LispType::CHAR:
        toString(AS(L_CHAR, expr), output);
        return;
    case LispType::SYMBOL:
        toString(AS(L_SYMBOL, expr), output);
        return;
    case LispType::STRING:
        toString(AS(L_STRING, expr), output);
        return;
    case LispType::LITERAL:
        toString(AS(L_LITERAL, expr), output);
        return;
    case LispType::INT:
        toString(AS(L_INT, expr), output);
        return;
    case LispType::REAL:
        toString(AS(L_REAL, expr), output);
        return;
    case LispType::RATIONAL:
        toString(AS(L_RATIONAL, expr), output);
        return;
    case LispType::COMPLEX:
        toString(AS(L_COMPLEX, expr), output);
        return;
    case LispType::FUNCTION:
        toString(AS(L_FUNCTION, expr), output);
        return;
    case LispType::BUILTIN_FUNCTION:
        toString(AS(L_BUILTIN_FUNCTION, expr), output);
        return;
    }
    throw std::runtime_error("Tried to to string an unknown type.");
}


}
