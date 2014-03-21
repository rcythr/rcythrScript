
#pragma once

#include <rcythrScript/datatypes/symbol.h>
#include <rcythrScript/datatypes/bool.h>

#define UNEXPECTED_TOKEN(A, B) throw std::runtime_error(std::string("Unexpected token: ")+A+", Expected"+B)
#define EXPECT_CHAR(A, B) if(A != B) UNEXPECTED_TOKEN(A, B)
#define VALIDATE_LENGTH(A, B) if(A >= B) throw std::runtime_error("PARSE ERROR: UNEXPECTED EOF.")

#define WRAP(A, ...) std::make_shared<A>(__VA_ARGS__)
#define AS(A, B) std::static_pointer_cast<A>(B)

namespace rcythr
{

extern PL_SYMBOL NIL;
extern PL_BOOL TRUE;
extern PL_BOOL FALSE;

}
