#ifndef TREE_H
#define TREE_H

#include "..\Common.h"
#include "TreeCommon.h"

return_codes createNode       (node_t** const    new_node_p_p,
                               node_full_value_t full_value,
                               node_t*           left_p,
                               node_t*           right_p);

node_t* integratedCreateNode (node_full_value_t full_value, node_t* left_p, node_t* right_p);

node_t* createConstNode(double value         , node_t* left_p, node_t* right_p);
node_t* createVarNode  (var_codes value      , node_t* left_p, node_t* right_p);
node_t* createOpNode   (operation_codes value, node_t* left_p, node_t* right_p);

return_codes createSheet      (node_t* const parent_p, branch_codes branch_code, node_full_value_t full_value);

return_codes deleteNode       (node_t* const node_p);
return_codes deleteSheet      (node_t* const parent_p, branch_codes branch_code);
void         deleteTree       (node_t* const root_p);
void         deleteSubTree    (node_t* const parent_p, branch_codes branch_code);

node_t**     getBranchPointer (node_t* const parent_p, const branch_codes branch_code);
node_t*      createCopy       (const node_t* const root_p);

void         replaceRootWithSubtree(node_t* const root_p, const branch_codes branch_code);

#endif
