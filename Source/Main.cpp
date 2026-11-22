#include "..\Headers\Main.h"

int main(){

    node_t* root_p = NULL;
//     node_full_value_t full_root_value = {.node_type = OPERATION_NODE, .value = {.operation_code = ADD}};
//     createNode(&root_p, full_root_value, NULL, NULL);
//
//     node_full_value_t value_left =  {.node_type = CONST_NODE   , .value = {.const_value = 10}};
//     node_full_value_t value_right = {.node_type = VARIABLE_NODE, .value = {.var_code = X_VAR}};
//
//     createSheet(root_p, BRANCH_LEFT , value_left);
//     createSheet(root_p, BRANCH_RIGHT, value_right);

    createTreeFromFile(&root_p, "Tree1.txt");

    visualizeTree(root_p, "Tree1.svg");

    //printTreeInFile(root_p, "Tree1.txt");
}
