#ifndef SIMPLIFIER_H
#define SIMPLIFIER_H

#include ".\Tree\TreeCommon.h"
#include ".\Tree\Tree.h"
#include ".\Tree\TreeTextFormat.h"
#include "Operations.h"
#include "Common.h"
#include "CommonDSL.h"



bool   simplifyConstSubtrees(node_t* orig_func_root_p);
double calculateConstSubtree(const node_t* const func_root_p);

#endif
