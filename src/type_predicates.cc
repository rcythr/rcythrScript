
#include <rscript/builtins.h>
#include <rscript/constants.h>

namespace rscript
{

PL_ATOM proc_is_bool(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::BOOL) ? TRUE : FALSE;
}

PL_ATOM proc_is_char(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::CHAR) ? TRUE : FALSE;
}

PL_ATOM proc_is_complex(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::COMPLEX) ? TRUE : FALSE;    
}

PL_ATOM proc_is_integer(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::INT) ? TRUE : FALSE;    
}

PL_ATOM proc_is_list(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::LIST) ? TRUE : FALSE;    
}

PL_ATOM proc_is_number(PL_ATOM atom, SymbolTable& symbols)
{
    DataType type = atom->mType;
    return (type == DataType::INT || type == DataType::REAL || type == DataType::RATIONAL || type == DataType::COMPLEX) ? TRUE : FALSE;
}

PL_ATOM proc_is_procedure(PL_ATOM atom, SymbolTable& symbols) 
{ 
    return (atom->mType == DataType::BUILTIN_FUNCTION || atom->mType == DataType::FUNCTION) ? TRUE : FALSE; 
}

PL_ATOM proc_is_rational(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::RATIONAL) ? TRUE : FALSE;    
}

PL_ATOM proc_is_real(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::REAL) ? TRUE : FALSE;    
}

PL_ATOM proc_is_string(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::STRING) ? TRUE : FALSE;    
}

PL_ATOM proc_is_symbol(PL_ATOM atom, SymbolTable& symbols) 
{
    return (atom->mType == DataType::SYMBOL) ? TRUE : FALSE;
}

PL_ATOM proc_is_vector(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::VECTOR) ? TRUE : FALSE;    
}

}
