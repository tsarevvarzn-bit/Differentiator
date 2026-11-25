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

    if(left_p != NULL){

        left_p->parent_p  = *new_node_p_p;
    }

    if(right_p != NULL){

        right_p->parent_p = *new_node_p_p;
    }

    return RET_CORRECT;
}
node_t* integratedCreateNode(node_full_value_t full_value, node_t* left_p, node_t* right_p){

    node_t* new_node_p = NULL;

    createNode(&new_node_p, full_value, left_p, right_p);

    return new_node_p;
}

node_t* createConstNode(double value, node_t* left_p, node_t* right_p){

    node_full_value_t full_node_value = {.node_type = CONST_NODE, .value = { .const_value = value}};

    node_t* new_node_p = NULL;

    createNode(&new_node_p, full_node_value, left_p, right_p);

    return new_node_p;
}

node_t* createVarNode(var_codes value, node_t* left_p, node_t* right_p){


    node_full_value_t full_node_value = {.node_type = VARIABLE_NODE, .value = { .var_code  = value}};

    node_t* new_node_p = NULL;

    createNode(&new_node_p, full_node_value, left_p, right_p);

    return new_node_p;
}

node_t* createOpNode(operation_codes value, node_t* left_p, node_t* right_p){

    node_full_value_t full_node_value = {.node_type = OPERATION_NODE, .value = { .operation_code = value}};

    node_t* new_node_p = NULL;

    createNode(&new_node_p, full_node_value, left_p, right_p);

    return new_node_p;
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

void deleteTree(node_t* const root_p){

    if(root_p->left_p == NULL && root_p->right_p == NULL){

        deleteNode(root_p);

    }else{

        deleteNode(root_p->left_p );
        deleteNode(root_p->right_p);
    }
}

void deleteSubTree(node_t* const parent_p, branch_codes branch_code){

    node_t** root_of_subtree_p_p = getBranchPointer(parent_p, branch_code); //Указатель на указатель на лист внутри структуры родителя

    if(*root_of_subtree_p_p == NULL){

        return;
    }

    if((*root_of_subtree_p_p)->left_p == NULL && (*root_of_subtree_p_p)->right_p == NULL){

        deleteNode((*root_of_subtree_p_p));

    }else{

        deleteNode((*root_of_subtree_p_p)->left_p );
        deleteNode((*root_of_subtree_p_p)->right_p);
    }

    (*root_of_subtree_p_p) = NULL;
}

node_t** getBranchPointer(node_t* const parent_p, const branch_codes branch_code){

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

node_t* createCopy(const node_t* const root_p){

    if(root_p == NULL){

        return NULL;
    }

    return integratedCreateNode(root_p->full_value, createCopy(root_p->left_p), createCopy(root_p->right_p));
}


void replaceRootWithSubtree(node_t* const root_p, const branch_codes branch_code){

    assert(root_p);

    node_t* subtree_p = *getBranchPointer(root_p, branch_code);

    assert(subtree_p);

    root_p->full_value = subtree_p->full_value;
    root_p->left_p     = subtree_p->left_p    ;
    root_p->right_p    = subtree_p->right_p   ;

    if(subtree_p->left_p != NULL){

        subtree_p->left_p->parent_p = root_p;

    }

    if(subtree_p->right_p != NULL){

        subtree_p->right_p->parent_p = root_p;

    }

    subtree_p->left_p  = NULL;
    subtree_p->right_p = NULL;

    deleteNode(subtree_p);
}
