#ifndef CALCULATOR_H
#define CALCULATOR_H

#include ".\Tree\TreeCommon.h"
#include ".\Tree\Tree.h"
#include ".\Tree\TreeTextFormat.h"
#include "Operations.h"
#include "Common.h"

#include "Simplifier.h"

void    insertValues(node_t* root_p, calc_context_t calc_context);
node_t* copyAndInsertValues(const node_t* const root_p, calc_context_t calc_context);
double  getVarValue(calc_context_t calc_context, var_codes var_code);

#endif
