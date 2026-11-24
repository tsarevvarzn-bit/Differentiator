#include "..\Headers\Simplifier.h"

bool simplifyConstSubtrees(node_t* orig_func_root_p){

    if(orig_func_root_p == NULL){

        return false;
    }

    ON_DEBUG_CONSOLE(
    printf("Begin of simplifier ");
    printValueOfNode(stdout, orig_func_root_p->full_value);
    printf("\n");
    )

    double value_of_tree = NAN;

    if(! isnan(value_of_tree = calculateConstSubtree(orig_func_root_p))){

        if(orig_func_root_p->left_p != NULL || orig_func_root_p->right_p != NULL){

            deleteSubTree(orig_func_root_p, BRANCH_LEFT );
            deleteSubTree(orig_func_root_p, BRANCH_RIGHT);

            orig_func_root_p->full_value.node_type         = CONST_NODE;
            orig_func_root_p->full_value.value.const_value = value_of_tree;

            ON_DEBUG_CONSOLE(
            printf("End of simplifier by simplif ");
            printValueOfNode(stdout, orig_func_root_p->full_value);
            printf("\n");
            )

            return true;

        }else{

            return false;
        }

    }else{

        ON_DEBUG_CONSOLE(
        printf("End of simplifier by recurs ");
        printValueOfNode(stdout, orig_func_root_p->full_value);
        printf("\n");
        )

        bool is_left_simplified  = simplifyConstSubtrees(orig_func_root_p->left_p);
        bool is_right_simplified = simplifyConstSubtrees(orig_func_root_p->right_p);

        return is_left_simplified || is_right_simplified;
    }
}

double calculateConstSubtree(const node_t* const func_root_p){

    assert(func_root_p);

    double value_of_tree = NAN;
    double value_of_left_subtree  = NAN;
    double value_of_right_subtree = NAN;

    if(func_root_p->full_value.node_type == CONST_NODE){

        value_of_tree = func_root_p->full_value.value.const_value;

    }else if(func_root_p->full_value.node_type == OPERATION_NODE){

        if(OPERATIONS[func_root_p->full_value.value.operation_code].num_of_args == 1){

            value_of_left_subtree = calculateConstSubtree(func_root_p->left_p);

            if(!isnan(value_of_left_subtree)){

                value_of_tree = (OPERATIONS[func_root_p->full_value.value.operation_code].calc_func_p)(value_of_left_subtree, NULL);
            }

        }else{

            value_of_left_subtree  = calculateConstSubtree(func_root_p->left_p );
            value_of_right_subtree = calculateConstSubtree(func_root_p->right_p);

            if(!isnan(value_of_left_subtree) && !isnan(value_of_right_subtree)){

                value_of_tree = (OPERATIONS[func_root_p->full_value.value.operation_code].calc_func_p)(value_of_left_subtree, value_of_right_subtree);

            }
        }
    }

    return value_of_tree;
}
