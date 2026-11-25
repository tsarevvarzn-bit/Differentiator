#include "..\Headers\Simplifier.h"

#define IS_LEFT(x) ((root_p->left_p->full_value.node_type == CONST_NODE) && (isZero(root_p->left_p->full_value.value.const_value - x)))
#define IS_RIGHT(x) ((root_p->right_p->full_value.node_type == CONST_NODE) && (isZero(root_p->right_p->full_value.value.const_value - x)))

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

// Должны дойти до дна и все оптимизировать снизу вверх

bool deleteNeutralNodes(node_t* root_p){

    assert(root_p);

    ON_DEBUG_CONSOLE(

    printf("Try to optimised");
    printValueOfNode(stdout, root_p->full_value);
    printf("\n");

    )

    bool isDeleteNodesInLeftSubtree  = false;
    bool isDeleteNodesInRightSubtree = false;

    if(root_p->left_p != NULL){

        isDeleteNodesInLeftSubtree  = deleteNeutralNodes(root_p->left_p);
    }

    if(root_p->right_p != NULL){

        isDeleteNodesInRightSubtree = deleteNeutralNodes(root_p->right_p);
    }

    return tryDeleteNeutralNode(root_p) || isDeleteNodesInLeftSubtree || isDeleteNodesInRightSubtree;
}

bool tryDeleteNeutralNode(node_t* root_p){

    if(root_p->full_value.node_type == OPERATION_NODE){

        switch(root_p->full_value.value.operation_code){

            case ADD:   return optimizeAddSub(root_p);

            case SUB:   return optimizeAddSub(root_p);

            case MUL:   return optimizeMul(root_p);

            case DIV:   return optimizeDiv(root_p);

            case SIN:   return false;

            case COS:   return false;

            case POW:   return optimizePow(root_p);

            case LN:    return false;

            default:

                printf(RED_COLOR "ERROR: incorrect operation code for differentiation\n" DEFAULT_COLOR);
                return false;
        }
    }

    return false;
}

bool optimizeAddSub(node_t* root_p){

    assert(root_p);
    assert(root_p->left_p);
    assert(root_p->right_p);

    printf("LABUBA\n\n");

    if(IS_LEFT(0)){

        deleteSheet(root_p, BRANCH_LEFT);

        replaceRootWithSubtree(root_p, BRANCH_RIGHT);

        printf("LABUBA_LEFT\n\n");

        return true;
    }

    if(IS_RIGHT(0)){

        deleteSheet(root_p, BRANCH_RIGHT);

        replaceRootWithSubtree(root_p, BRANCH_LEFT);

        printf("LABUBA_LEFT\n\n");

        return true;
    }

    return false;
}

bool optimizeMul(node_t* root_p){

    assert(root_p);
    assert(root_p->left_p);
    assert(root_p->right_p);

    if(IS_LEFT(0) || IS_RIGHT(0)){

        deleteSubTree(root_p, BRANCH_LEFT );
        deleteSubTree(root_p, BRANCH_RIGHT);

        root_p->full_value.node_type         = CONST_NODE;
        root_p->full_value.value.const_value = 0         ;

        return true;
    }

    if(IS_LEFT(1)){

        deleteSheet(root_p, BRANCH_LEFT);

        replaceRootWithSubtree(root_p, BRANCH_RIGHT);

        return true;
    }

    if(IS_RIGHT(1)){

        deleteSheet(root_p, BRANCH_RIGHT);

        replaceRootWithSubtree(root_p, BRANCH_LEFT);

        return true;
    }

    return false;
}

bool optimizeDiv(node_t* root_p){

    assert(root_p);
    assert(root_p->left_p);
    assert(root_p->right_p);

    if(IS_LEFT(0)){

        deleteSubTree(root_p, BRANCH_LEFT );
        deleteSubTree(root_p, BRANCH_RIGHT);

        root_p->full_value.node_type         = CONST_NODE;
        root_p->full_value.value.const_value = 0         ;

        return true;
    }

    if(IS_RIGHT(1)){

        deleteSheet(root_p, BRANCH_RIGHT);

        replaceRootWithSubtree(root_p, BRANCH_LEFT);

        return true;
    }

    return false;
}

bool optimizePow(node_t* root_p){

    assert(root_p);
    assert(root_p->left_p);
    assert(root_p->right_p);

    if(IS_LEFT(0)){

        deleteSubTree(root_p, BRANCH_LEFT );
        deleteSubTree(root_p, BRANCH_RIGHT);

        root_p->full_value.node_type         = CONST_NODE;
        root_p->full_value.value.const_value = 0         ;

        return true;
    }

    if(IS_RIGHT(1) || IS_LEFT(1)){

        deleteSheet(root_p, BRANCH_RIGHT);

        replaceRootWithSubtree(root_p, BRANCH_LEFT);

        return true;
    }

    if(IS_RIGHT(0)){

        deleteSubTree(root_p, BRANCH_LEFT );
        deleteSubTree(root_p, BRANCH_RIGHT);

        root_p->full_value.node_type         = CONST_NODE;
        root_p->full_value.value.const_value = 0         ;

        return true;
    }

    return false;
}

bool isZero(double x){

    return (abs(x) < EPSILON) ? 1 : 0;
}

#undef IS_LEFT
#undef IS_RIGHT
