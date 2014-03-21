// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include <rcythrScript/datatypes/type.h>
#include <rcythrScript/datatypes/atom.h>
#include <rcythrScript/datatypes/list.h>
#include <rcythrScript/datatypes/vector.h>
#include <rcythrScript/datatypes/literal.h>
#include <rcythrScript/datatypes/bool.h>
#include <rcythrScript/datatypes/symbol.h>
#include <rcythrScript/datatypes/int.h>
#include <rcythrScript/datatypes/real.h>
#include <rcythrScript/datatypes/rational.h>
#include <rcythrScript/datatypes/complex.h>
#include <rcythrScript/datatypes/char.h>
#include <rcythrScript/datatypes/string.h>
#include <rcythrScript/datatypes/builtin_function.h>
#include <rcythrScript/datatypes/function.h>

namespace rcythr
{

PL_ATOM parseNumeric(const std::string& input, size_t& offset);
PL_ATOM parseExpression(const std::string& input, size_t& offset);

PL_ATOM deepCopy(PL_ATOM expr);

PL_ATOM evaluate(PL_ATOM expr, SymbolTableType& globalSymbolTable, SymbolTableType& localSymbolTable);
PL_ATOM evaluate(PL_ATOM expr);

}
