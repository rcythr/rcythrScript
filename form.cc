#include "builtins.h"

namespace rcythr
{

std::unordered_map<std::string,std::function<PL_ATOM(PL_ATOM,SymbolTableType&,SymbolTableType&)>> forms =
{
    { "define", form_define },
    { "lambda", form_lambda },
    { "if", form_if },
    { "begin", form_begin },
    { "define-syntax", form_define_syntax},
    { "set!", form_set_exclaim }
};

PL_ATOM form_define(PL_ATOM lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM form_lambda(PL_ATOM lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM form_if(PL_ATOM lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM form_begin(PL_ATOM lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM form_define_syntax(PL_ATOM lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM form_set_exclaim(PL_ATOM lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

}