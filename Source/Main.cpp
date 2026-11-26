#include "..\Headers\Main.h"

int main(){

    node_t* root_p = NULL;

    createTreeFromFile(&root_p, "Tree1.txt");

    visualizeTree(root_p, "DefaultTree.svg");

    node_t* simpl_default = simplifyTree(root_p);

    visualizeTree(simpl_default, "DefaultSimplTree.svg");

    node_t* root_diff_p = differentiateSubtree(simpl_default);

    visualizeTree(root_diff_p, "TreeDiff.svg");

    node_t* root_diff_simpl_p = simplifyTree(root_diff_p);

    visualizeTree(root_diff_simpl_p, "TreeDiffSimpl.svg");

    FILE* log_md_file_p = fopen("LofFile.md", "w");

    fprintf(log_md_file_p, "# DefaultTree:");
    printTreeInTexFormat(log_md_file_p, root_p);

    fprintf(log_md_file_p, "# DefaultSimplTree:");
    printTreeInTexFormat(log_md_file_p, simpl_default);

    fprintf(log_md_file_p, "# TreeDiff:");
    printTreeInTexFormat(log_md_file_p, root_diff_p);

    fprintf(log_md_file_p, "# TreeDiffSimpl:");
    printTreeInTexFormat(log_md_file_p, root_diff_simpl_p);
}
