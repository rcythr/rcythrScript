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

}
