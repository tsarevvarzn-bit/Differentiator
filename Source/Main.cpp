#include "..\Headers\Main.h"

int main(){

    node_t* root_p = NULL;

    createTreeFromFile(&root_p, "Tree1.txt");

    visualizeTree(root_p, "Tree1.svg");


    node_t* root_diff_p = differentiateSubtree(root_p);

    visualizeTree(root_diff_p, "Tree2.svg");


    node_t* root_diff_simpl_p = createCopy(root_diff_p);

    printf("%d", simplifyConstSubtrees(root_diff_simpl_p));

    visualizeTree(root_diff_simpl_p, "Tree3.svg");


    printf("%d", deleteNeutralNodes(root_diff_simpl_p));

    visualizeTree(root_diff_simpl_p, "Tree4.svg");

    //printTreeInFile(root_p, "Tree1.txt");
}
