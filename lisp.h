#pragma once

#include <string>
#include <vector>
#include <forward_list>
#include <memory>
#include <unordered_map>

namespace rcythr
{

enum class LispType
{
    // Wrapper types
    LIST,
    LITERAL,
    VECTOR,

    // String Types
    CHAR,
    STRING,

    // NUMERIC TYPES
    INT,
    REAL,
    RATIONAL,
    COMPLEX,

    BOOL,
    SYMBOL,
    BUILTIN_FUNCTION,
    FUNCTION
};

struct L_ATOM
{
    L_ATOM(LispType type)
        : mType(type)
        , mConstant(false)
    {
    }
    LispType mType;
    bool mConstant;
};

typedef std::shared_ptr<L_ATOM> PL_ATOM;
typedef std::unordered_map<std::string,PL_ATOM> SymbolTableType;
typedef std::function<PL_ATOM(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)> BuiltinFuncType;
typedef std::function<PL_ATOM(SymbolTableType&)> UserFunctionType;
typedef std::forward_list<std::string> ArgList;

struct L_LIST : public L_ATOM
{
    L_LIST(std::forward_list<PL_ATOM>& atoms)
        : L_ATOM(LispType::LIST)
        , mAtoms(atoms)
    {
    }

    L_LIST(std::forward_list<PL_ATOM>&& atoms)
        : L_ATOM(LispType::LIST)
        , mAtoms(atoms)
    {
    }

    std::forward_list<PL_ATOM> mAtoms;
};


struct L_VECTOR : public L_ATOM
{
    L_VECTOR(std::vector<PL_ATOM>& atoms)
        : L_ATOM(LispType::VECTOR)
        , mAtoms(atoms)
    {
    }
    L_VECTOR(std::vector<PL_ATOM>&& atoms)
        : L_ATOM(LispType::VECTOR)
        , mAtoms(atoms)
    {
    }
    std::vector<PL_ATOM> mAtoms;
};

struct L_LITERAL : public L_ATOM
{
    L_LITERAL(PL_ATOM literal)
        : L_ATOM(LispType::LITERAL)
        , mLiteral(literal)
    {
    }
    PL_ATOM mLiteral;
};

struct L_BOOL : public L_ATOM
{
    L_BOOL(bool value)
        : L_ATOM(LispType::BOOL)
        , mValue(value)
    {
    }
    bool mValue;
};

struct L_SYMBOL : public L_ATOM
{
    L_SYMBOL(std::string name)
        : L_ATOM(LispType::SYMBOL)
        , mName(name)
    {
    }
    std::string mName;
};

struct L_INT : public L_ATOM
{
    L_INT(int value)
        : L_ATOM(LispType::INT)
        , mValue(value)
    {
    }
    int mValue;
};
typedef std::shared_ptr<L_INT> PL_INT;

struct L_REAL : public L_ATOM
{
    L_REAL(double value)
        : L_ATOM(LispType::REAL)
        , mValue(value)
    {
    }
    double mValue;
};

struct L_RATIONAL : public L_ATOM
{
    L_RATIONAL(PL_INT numerator, PL_INT denominator)
        : L_ATOM(LispType::RATIONAL)
        , mNumerator(numerator)
        , mDenominator(denominator)
    {
    }
    PL_INT mNumerator;
    PL_INT mDenominator;
};

struct L_COMPLEX : public L_ATOM
{
    L_COMPLEX(PL_ATOM real, PL_ATOM imaginary)
        : L_ATOM(LispType::COMPLEX)
        , mReal(real)
        , mImaginary(imaginary)
    {
    }
    PL_ATOM mReal;
    PL_ATOM mImaginary;
};

struct L_CHAR : public L_ATOM
{
    L_CHAR(char value)
        : L_ATOM(LispType::CHAR)
        , mValue(value)
    {
    }
    char mValue;
};

struct L_STRING : public L_ATOM
{
    L_STRING(std::string value)
        : L_ATOM(LispType::STRING)
        , mValue(value)
    {
    }
    std::string mValue;
};

struct L_BUILTIN_FUNCTION : public L_ATOM
{
    L_BUILTIN_FUNCTION(BuiltinFuncType func)
        : L_ATOM(LispType::BUILTIN_FUNCTION)
        , mFunc(func)
    {
    }
    BuiltinFuncType mFunc;
};

struct L_FUNCTION : public L_ATOM
{
    L_FUNCTION(UserFunctionType func, ArgList args)
        : L_ATOM(LispType::FUNCTION)
        , mFunc(func)
        , mArgs(args)
    {
    }
    UserFunctionType mFunc;
    ArgList mArgs;
};

typedef std::shared_ptr<L_LIST> PL_LIST;
typedef std::shared_ptr<L_VECTOR> PL_VECTOR;
typedef std::shared_ptr<L_LITERAL> PL_LITERAL;
typedef std::shared_ptr<L_BOOL> PL_BOOL;
typedef std::shared_ptr<L_SYMBOL> PL_SYMBOL;
typedef std::shared_ptr<L_REAL> PL_REAL;
typedef std::shared_ptr<L_RATIONAL> PL_RATIONAL;
typedef std::shared_ptr<L_COMPLEX> PL_COMPLEX;
typedef std::shared_ptr<L_CHAR> PL_CHAR;
typedef std::shared_ptr<L_STRING> PL_STRING;
typedef std::shared_ptr<L_BUILTIN_FUNCTION> PL_BUILTIN_FUNCTION;
typedef std::shared_ptr<L_FUNCTION> PL_FUNCTION;

PL_ATOM parseBool(const std::string& input, size_t& offset);
PL_ATOM parseList(const std::string& input, size_t& offset);
PL_ATOM parseVector(const std::string& input, size_t& offset);
PL_ATOM parseChar(const std::string& input, size_t& offset);
PL_ATOM parseString(const std::string& input, size_t& offset);
PL_ATOM parseSymbol(const std::string& input, size_t& offset);
PL_ATOM parseNumeric(const std::string& input, size_t& offset);
PL_ATOM parseExpression(const std::string& input, size_t& offset);

PL_ATOM deepCopy(PL_ATOM expr);
void makeConstant(PL_ATOM expr);
void printExpression(PL_ATOM expr, size_t indent=0);
PL_ATOM evaluate(PL_ATOM expr, SymbolTableType& globalSymbolTable, SymbolTableType& localSymbolTable);
PL_ATOM evaluate(PL_ATOM expr);

extern PL_SYMBOL NIL;
extern PL_BOOL TRUE;
extern PL_BOOL FALSE;

}
