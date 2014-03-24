// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rscript/builtins.h>
#include <rscript/constants.h>

namespace rscript
{

PL_ATOM proc_load(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_transcript_on(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_transcript_off(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

}
