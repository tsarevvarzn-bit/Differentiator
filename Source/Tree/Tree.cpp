#include "..\..\Headers\Tree\Tree.h"



return_codes createNode(node_t** const    new_node_p_p,
                        node_full_value_t full_value,
                        node_t*           left_p,
                        node_t*           right_p){

    assert(new_node_p_p);

    if(*new_node_p_p != NULL){

        printf(RED_COLOR "ERROR: there is already a node following this pointer: [%p]\n" DEFAULT_COLOR, *new_node_p_p);
        return RET_ERROR;
    }

    *new_node_p_p = (node_t*) calloc(1, sizeof(node_t));

    if(*new_node_p_p == NULL){

        printf(RED_COLOR "ERROR: no way to allocate memory for new root\n" DEFAULT_COLOR);
        return RET_ERROR;
    }

    (*new_node_p_p)->parent_p   = NULL;
    (*new_node_p_p)->left_p     = left_p;
    (*new_node_p_p)->right_p    = right_p;
    (*new_node_p_p)->full_value = full_value;

    return RET_CORRECT;
}

return_codes createSheet(node_t* const parent_p, branch_codes branch_code, node_full_value_t full_value){

    assert(parent_p);

    node_t** new_node_p_p = getBranchPointer(parent_p, branch_code);

    if(createNode(new_node_p_p, full_value, NULL, NULL) == RET_ERROR){

        return RET_ERROR;
    }

    (*new_node_p_p)->parent_p = parent_p;

    return RET_CORRECT;
}

return_codes deleteNode(node_t* const node_p){

    assert(node_p);

    if(node_p->left_p != NULL || node_p->right_p != NULL){

        printf(RED_COLOR "ERROR: node for delete: %p have branches: left: %p, right: %p, delete them first!\n" DEFAULT_COLOR,
        node_p, node_p->left_p, node_p->right_p);

        return RET_ERROR;
    }

    free(node_p);

    return RET_CORRECT;
}

return_codes deleteSheet(node_t* const parent_p, branch_codes branch_code){

    assert(parent_p);

    node_t** new_node_p_p = getBranchPointer(parent_p, branch_code); //Указатель на указатель на лист внутри структуры родителя

    if(deleteNode(*new_node_p_p) == RET_ERROR){

        return RET_ERROR;
    }

    (*new_node_p_p) = NULL;

    return RET_CORRECT;
}

node_t** getBranchPointer(node_t * parent_p, const branch_codes branch_code){

    assert(parent_p);

    switch(branch_code){

        case BRANCH_LEFT:

            return &(parent_p->left_p);
            break;

        case BRANCH_RIGHT:

            return &(parent_p->right_p);
            break;

        default:

            printf(RED_COLOR "ERROR: incorrect enum value in getBrunchPointer function: %d\n" DEFAULT_COLOR, branch_code);
            return NULL;
    }
}
