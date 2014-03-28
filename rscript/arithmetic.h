// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

namespace rscript
{

PL_ATOM neg(PL_ATOM a);

PL_ATOM add(PL_ATOM a, PL_ATOM b);

PL_ATOM sub(PL_ATOM a, PL_ATOM b);

PL_ATOM mul(PL_ATOM a, PL_ATOM b);

PL_ATOM div(PL_ATOM a, PL_ATOM b);

bool num_eq(PL_ATOM a, PL_ATOM b);
bool num_lt(PL_ATOM a, PL_ATOM b);
bool num_lte(PL_ATOM a, PL_ATOM b);
bool num_gt(PL_ATOM a, PL_ATOM b);
bool num_gte(PL_ATOM a, PL_ATOM b);

int steins_gcd(int a, int b);

}
