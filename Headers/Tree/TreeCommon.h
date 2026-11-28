#ifndef TREE_COMMON_H
#define TREE_COMMON_H

#include "..\Operations.h"

enum types_of_node{

    CONST_NODE    ,
    OPERATION_NODE,
    VARIABLE_NODE
};

enum branch_codes{

    BRANCH_LEFT ,
    BRANCH_RIGHT
};

enum var_codes{

    X_VAR,
    Y_VAR
};

struct calc_context_t{

    double x_value;
    double y_value;
};

union node_value_t{

    double          const_value   ;
    operation_codes operation_code;
    var_codes       var_code      ;
};

struct node_full_value_t{

    types_of_node node_type;
    node_value_t  value    ;
};

struct node_t{

    node_t*           parent_p  ;
    node_t*           left_p    ;
    node_t*           right_p   ;
    node_full_value_t full_value;
};

#endif
