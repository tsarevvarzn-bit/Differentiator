#include "..\Headers\Main.h"

int main(){

    //DONE calculator
    //TODO tex + log
    //TODO инф читалка
    //TODO readme

    //TODO

    node_t* root_p = NULL;

    const char* name_of_file_with_tree = ".\\TxtTrees\\Tree3.txt";

    createTreeFromFile(&root_p, name_of_file_with_tree);

    FILE* log_md_file_p = fopen(LOG_MD_FILE_NAME, "w");
    FILE* tex_file_p    = fopen(TEX_FILE_NAME, "w");

    visualizeTree(root_p, log_md_file_p, "Прочитаем красотульку из файла Tree3.txt");

    node_t* simpl_default = simplifyTree(root_p);

    visualizeTree(simpl_default, log_md_file_p, "Упростим ее");

    node_t* root_diff_p = differentiateSubtree(simpl_default);

    visualizeTree(root_diff_p, log_md_file_p, "Возьмем производную, это вам должны были объяснить в школе");

    node_t* root_diff_simpl_p = simplifyTree(root_diff_p);

    visualizeTree(root_diff_simpl_p, log_md_file_p, "Несколько простых преобразований, не буду утруждать себя объяснением");

    calc_context_t calc_context = {.x_value = NAN, .y_value = 1};

    node_t* tree_with_context = copyAndInsertValues(root_diff_simpl_p, calc_context);

    visualizeTree(tree_with_context, log_md_file_p, "Подставляем числа обязательно, иначе на егэ снимут баллы");

    node_t* answer = simplifyTree(tree_with_context);

    visualizeTree(answer, log_md_file_p, "Вычисления останутся вам в качестве дз, нужно же вам что-то сделать самостоятельно, вот такой ответ должен получиться");


    fprintf(tex_file_p, "# Прочитаем красотульку из файла Tree3.txt");
    printTreeInTexFormat(tex_file_p, root_p);

    fprintf(tex_file_p, "# Упростим ее");
    printTreeInTexFormat(tex_file_p, simpl_default);

    fprintf(tex_file_p, "# Возьмем производную, это вам должны были объяснить в школе");
    printTreeInTexFormat(tex_file_p, root_diff_p);

    fprintf(tex_file_p, "# Несколько простых преобразований, не буду утруждать себя объяснением");
    printTreeInTexFormat(tex_file_p, root_diff_simpl_p);

    fprintf(tex_file_p, "# Подставляем числа обязательно, иначе на егэ снимут баллы");
    printTreeInTexFormat(tex_file_p, tree_with_context);

    fprintf(tex_file_p, "# Вычисления останутся вам в качестве дз, нужно же вам что-то сделать самостоятельно, вот такой ответ должен получиться");
    printTreeInTexFormat(tex_file_p, answer);
}
