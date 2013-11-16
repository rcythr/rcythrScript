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
    {
    }
    LispType mType;
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

template<typename IteratorType> std::shared_ptr<L_ATOM> parseExpression(IteratorType& itr, IteratorType& end);
template<typename IteratorType> std::shared_ptr<L_SYMBOL> parseSymbol(IteratorType& itr, IteratorType& end, char extra);
template<typename IteratorType> std::shared_ptr<L_LIST> parseList(IteratorType& itr, IteratorType& end, char extra);
template<typename IteratorType> std::shared_ptr<L_STRING> parseString(IteratorType& itr, IteratorType& end, char extra);
template<typename IteratorType> std::shared_ptr<L_ATOM> parseNumeric(IteratorType& itr, IteratorType& end, char extra);
template<typename IteratorType> std::shared_ptr<L_BOOL> parseBool(IteratorType& itr, IteratorType& end, char extra);

bool isSpace(char val);
bool isWhitespace(char val);
bool isNumber(char val);
bool isLetter(char val);
bool isAlpha(char val);
bool isSymbol(char val);
bool isAlphaSymbol(char val);

template<typename IteratorType>
std::shared_ptr<L_BOOL> parseBool(IteratorType& itr, IteratorType& end, char extra)
{
    char buf = *itr;
    ++itr;
    return std::make_shared<L_BOOL>((buf == 't' || buf == 'T') ? true : false);
}

template<typename IteratorType>
std::shared_ptr<L_SYMBOL> parseSymbol(IteratorType& itr, IteratorType& end, char extra)
{
    std::string symbol;

    if(extra != '\0')
        symbol += extra;

    char buf = *itr;
    while(isAlphaSymbol(buf))
    {
        symbol += buf;
        ++itr;
        if(itr == end) break;
        buf = *itr;
    }
    return std::make_shared<L_SYMBOL>(symbol);
}

template<typename IteratorType>
std::shared_ptr<L_LIST> parseList(IteratorType& itr, IteratorType& end, char extra)
{
    std::forward_list<PL_ATOM> lst;
    auto bb = lst.before_begin();

    bool needWS = false;

    char buf = *itr;
    while(buf != ')')
    {
        if(!isWhitespace(buf))
        {
            if(needWS) throw std::runtime_error("PARSE ERROR: EXPECTED WHITE SPACE!!");

            bb = lst.insert_after(bb, std::move(parseExpression(itr, end)));
            needWS = true;
        }
        else
        {
            needWS = false;
            ++itr;
        }

        if(itr == end) throw std::runtime_error("MISSING ) before EOF!!");
        buf = *itr;
    }
    ++itr;

    return  std::make_shared<L_LIST>(lst);
}

template<typename IteratorType>
std::shared_ptr<L_STRING> parseString(IteratorType& itr, IteratorType& end, char extra)
{
    std::string value;
    char buf = *itr;
    while(buf != '"')
    {
        if(buf == '\\')
        {
            ++itr;
            buf = *itr;
            switch(buf)
            {
            case '\\': buf = '\\'; break;
            case '"': buf = '"'; break;
            case 'n': buf = '\n'; break;
            case 't': buf = '\t'; break;
            case 'r': buf = '\r'; break;
            default: throw std::runtime_error(std::string("Invalid escape char `")+buf+"` in string.");
            }
        }
        value += buf;
        ++itr;

        if(itr == end) throw std::runtime_error("MISSING \" BEFORE EOF!!");
        buf = *itr;
    }
    ++itr;

    return std::make_shared<L_STRING>(value);
}

template<typename IteratorType>
std::shared_ptr<L_ATOM> parseNumeric(IteratorType& itr, IteratorType& end, char extra)
{
    bool isFloat = false;
    std::string buffer;

    if(extra != '-')
        buffer += extra;

    char buf = *itr;
    while(isNumber(buf) || buf == '.' || buf == 'e')
    {
        if(buf == '.' || buf == 'e') isFloat = true;

        buffer += buf;
        ++itr;

        if(itr == end) break;
        buf = *itr;
    }

    if(isFloat)
    {
        return std::make_shared<L_REAL>((extra == '-') ? -std::stod(buffer) : std::stod(buffer));
    }
    else
    {
        return std::make_shared<L_INT>((extra == '-') ? -std::stoi(buffer) : std::stoi(buffer));
    }
}

template<typename IteratorType>
std::shared_ptr<L_ATOM> parseExpression(IteratorType& itr, IteratorType& end)
{
    if(itr == end) throw std::runtime_error("PARSE ERROR: UNEXPECTED EOF");

    char extra = *itr;
    ++itr;

    char buf = *itr;

    if(extra == '(') // LIST
    {
        return parseList(itr, end, extra);
    }
    else if(extra == '"') // STRING
    {
        return parseString(itr, end, extra);
    }
    else if((extra == '-' && isNumber(buf)) || isNumber(extra)) // NUMBER/FLOAT
    {
        return parseNumeric(itr, end, extra);
    }
    else if(extra == '#' && (buf == 't' || buf == 'f' || buf == 'T' || buf == 'F'))
    {
        return parseBool(itr, end, extra);
    }
    else if(isAlphaSymbol(buf) || isAlphaSymbol(extra)) // SYMBOL
    {
        return parseSymbol(itr, end, extra);
    }
    throw std::runtime_error("PARSE ERROR: Unrecognized character: "+buf);
}

void printExpression(PL_ATOM expr, size_t indent=0);

PL_ATOM evaluate(PL_ATOM expr, SymbolTableType& globalSymbolTable, SymbolTableType& localSymbolTable);
PL_ATOM evaluate(PL_ATOM expr);

}
