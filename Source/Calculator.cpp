#include "..\Headers\Calculator.h"


void insertValues(node_t* root_p, calc_context_t calc_context){

    assert(root_p);

    double var_value = NAN;

    if(root_p->full_value.node_type == VARIABLE_NODE){

        if(! isnan(var_value = getVarValue(calc_context, root_p->full_value.value.var_code))){

            assert(root_p->left_p  == NULL);
            assert(root_p->right_p == NULL);

            root_p->full_value.node_type         = CONST_NODE;
            root_p->full_value.value.const_value = var_value;
        }

    }else if(root_p->full_value.node_type == OPERATION_NODE){

        assert(root_p->left_p);

        insertValues(root_p->left_p, calc_context);

        if(root_p->right_p != NULL){

            insertValues(root_p->right_p, calc_context);
        }
    }
}

node_t* copyAndInsertValues(const node_t* const root_p, calc_context_t calc_context){

    assert(root_p);

    node_t* tree_copy_root_p = createCopy(root_p);

    insertValues(tree_copy_root_p, calc_context);

    return tree_copy_root_p;
}

double getVarValue(calc_context_t calc_context, var_codes var_code){

    switch(var_code){

        case X_VAR:

            return calc_context.x_value;

        case Y_VAR:

            return calc_context.y_value;

        default:

            printf(RED_COLOR "ERROR: incorrect var code: %d to get var value from context", var_code);

            return NAN;
    }
}
