// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include <rscript/datatypes/type.h>
#include <rscript/datatypes/atom.h>
#include <rscript/datatypes/list.h>
#include <rscript/datatypes/vector.h>
#include <rscript/datatypes/literal.h>
#include <rscript/datatypes/bool.h>
#include <rscript/datatypes/symbol.h>
#include <rscript/datatypes/int.h>
#include <rscript/datatypes/real.h>
#include <rscript/datatypes/rational.h>
#include <rscript/datatypes/complex.h>
#include <rscript/datatypes/char.h>
#include <rscript/datatypes/string.h>
#include <rscript/datatypes/builtin_function.h>
#include <rscript/datatypes/function.h>

namespace rscript
{

PL_ATOM parseNumeric(const std::string& input, size_t& offset);
PL_ATOM parseExpression(const std::string& input, size_t& offset);

PL_ATOM deepCopy(PL_ATOM expr);

PL_ATOM evaluate(PL_ATOM expr, SymbolTable& symbolTable);
PL_ATOM evaluate(PL_ATOM expr);

}
