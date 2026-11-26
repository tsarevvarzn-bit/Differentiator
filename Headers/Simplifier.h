#ifndef SIMPLIFIER_H
#define SIMPLIFIER_H

#include <math.h>

#include ".\Tree\TreeCommon.h"
#include ".\Tree\Tree.h"
#include ".\Tree\TreeTextFormat.h"
#include "Operations.h"
#include "Common.h"
#include "CommonDSL.h"

const double EPSILON = 0.0001;

node_t*   simplifyTree(const node_t* const root_p);

bool   simplifyConstSubtrees(node_t* orig_func_root_p);
double calculateConstSubtree(const node_t* const func_root_p);

bool deleteNeutralNodes  (node_t* root_p);
bool tryDeleteNeutralNode(node_t* root_p);

bool optimizeAddSub(node_t* root_p);
bool optimizeMul   (node_t* root_p);
bool optimizeDiv   (node_t* root_p);
bool optimizePow   (node_t* root_p);

bool isZero(double x);

#endif
