#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include ".\Tree\TreeCommon.h"
#include ".\Tree\Tree.h"
#include ".\Operations.h"
#include "Common.h"

node_t* differentiateSubtree(const node_t* const func_root_p);
node_t* diffPow(const node_t* const func_root_p);

#endif
