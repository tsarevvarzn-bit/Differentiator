#include "..\..\Headers\Tree\TreeTextFormat.h"

return_codes printTreeInFile(const node_t* const root_p, const char* const name_of_out_file){

    assert(name_of_out_file);

    FILE* out_file_p = fopen(name_of_out_file, "w");

    if(out_file_p == NULL){

        printf(RED_COLOR "ERROR: can't open a file with name: <%s>\n" DEFAULT_COLOR, name_of_out_file);
        return RET_ERROR;
    }

    printSubtreeInFile(root_p, out_file_p);

    fprintf(out_file_p, "\n");

    fclose(out_file_p);

    return RET_CORRECT;
}

void printSubtreeInFile(const node_t* const root_p, FILE* const out_file_p){

    assert(out_file_p);

    if(root_p == NULL){

        return;

    }else{

        fprintf(out_file_p, "(");

        printValueOfNode(out_file_p, root_p->full_value);

        printSubtreeInFile(root_p->left_p, out_file_p);

        printSubtreeInFile(root_p->right_p, out_file_p);

        fprintf(out_file_p, ")");

    }
}

return_codes createTreeFromFile(node_t** const root_p_p, const char* const name_of_in_file){

    assert(root_p_p);
    assert(name_of_in_file);

    int in_file_descr = open(name_of_in_file, _O_BINARY | _O_RDONLY);

    if(in_file_descr == EOF){

        printf(RED_COLOR "ERROR: can't open a file with name: <%s>\n" DEFAULT_COLOR, name_of_in_file);
        return RET_ERROR;
    }

    struct stat file_stats = {};
    fstat(in_file_descr, &file_stats);

    char* tree_text  = (char*) calloc(file_stats.st_size, sizeof(char));

    if(tree_text == NULL){

        printf(RED_COLOR "ERROR: can't allocate enough memory to read input file with size: %lu byte\n" DEFAULT_COLOR, file_stats.st_size);
        return RET_ERROR;
    }

    read(in_file_descr, tree_text, file_stats.st_size);


    startProcessingFile(root_p_p, tree_text);


    close(in_file_descr);

    return RET_CORRECT;
}

return_codes startProcessingFile(node_t** const root_p_p, const char* const tree_text){

    assert(root_p_p);
    assert(tree_text);

    size_t symbol_idx = 1;

    node_full_value_t full_value = {};

    if(parseNodeValue(tree_text, &symbol_idx, &full_value) == RET_ERROR){ // При этом скипаем до (

        return RET_ERROR;
    }

    if(createNode(root_p_p, full_value, NULL, NULL) == RET_ERROR){

        printf(RED_COLOR "ERROR: can't create a root of tree from file\n" DEFAULT_COLOR);
        return RET_ERROR;
    }

    ON_DEBUG_CONSOLE(

    printf("Processed root with value: <");
    printValueOfNode(stdout, full_value);
    printf(">\n");

    )

    return createSubtreeFromFile(*root_p_p, tree_text, &symbol_idx);
}

return_codes createSubtreeFromFile(node_t* const parent_p, const char* const tree_text, size_t* const symbol_idx_p){

    assert(parent_p);
    assert(symbol_idx_p);
    assert(tree_text);

    if(tree_text[*symbol_idx_p] == '(' && processBranch(parent_p, tree_text, symbol_idx_p, BRANCH_LEFT ) == RET_ERROR){

        return RET_ERROR;
    }

    if(tree_text[*symbol_idx_p] == '(' && processBranch(parent_p, tree_text, symbol_idx_p, BRANCH_RIGHT) == RET_ERROR){

        return RET_ERROR;
    }

    return RET_CORRECT;
}

return_codes processBranch(node_t* const parent_p, const char* const tree_text, size_t* const symbol_idx_p, const branch_codes branch_code){

    assert(parent_p);
    assert(symbol_idx_p);
    assert(tree_text);

    node_full_value_t full_value = {};

    node_t** node_p_p = getBranchPointer(parent_p, branch_code);

    (*symbol_idx_p)++; // Скипаем ( и смотрим на сам аргумент

    if(parseNodeValue(tree_text, symbol_idx_p, &full_value) == RET_ERROR){

        return RET_ERROR;
    }

    ON_DEBUG_CONSOLE(

    printf("Create kid of <");
    printValueOfNode(stdout, parent_p->full_value);
    printf(">, <");
    printValueOfNode(stdout, full_value);
    printf(">\n");

    )

    if(createSheet(parent_p, branch_code, full_value) == RET_ERROR){

        return RET_ERROR;
    }

    if(createSubtreeFromFile(*node_p_p, tree_text, symbol_idx_p) == RET_ERROR){

        return RET_ERROR;
    }

    (*symbol_idx_p)++; // Скипаем ), полностью завершая обработку ветки

    return RET_CORRECT;
}

return_codes parseNodeValue(const char* const        tree_text,
                            size_t* const            symbol_idx_p,
                            node_full_value_t* const full_value_p){ //TODO поделить

    assert(tree_text);
    assert(symbol_idx_p);
    assert(full_value_p);

    ON_DEBUG_CONSOLE( printf("Parse str: %s\n", tree_text + *symbol_idx_p); )

    if(tree_text[*symbol_idx_p] >= 'x' && tree_text[*symbol_idx_p] <= 'z'){

        full_value_p->node_type = VARIABLE_NODE;

        if(tree_text[*symbol_idx_p] == 'x'){

            full_value_p->value.var_code = X_VAR;

        }else if(tree_text[*symbol_idx_p] == 'y'){

            full_value_p->value.var_code = Y_VAR;

        }else{

            printf(RED_COLOR "ERROR: incorrect data in file of tree, in %llu idx variable with name: <%c>\n" DEFAULT_COLOR,
            *symbol_idx_p, tree_text[*symbol_idx_p]);

            return RET_ERROR;
        }

    }else if(isdigit(tree_text[*symbol_idx_p]) || (tree_text[*symbol_idx_p] == '-' && isdigit(tree_text[(*symbol_idx_p) + 1]))){

        full_value_p->node_type = CONST_NODE;

        if(sscanf(tree_text + *symbol_idx_p, "%lg", &(full_value_p->value.const_value)) != 1){

            printf(RED_COLOR "ERROR: incorrect data in file of tree, in %llu idx incorrect const number\n" DEFAULT_COLOR,
            *symbol_idx_p);

            return RET_ERROR;
        }

    }else{

        full_value_p->node_type = OPERATION_NODE;

        for(size_t i = 0; i < sizeof(OPERATIONS); i++){

            if(strncmp(tree_text + *symbol_idx_p, OPERATIONS[i].txt_form, strlen(OPERATIONS[i].txt_form)) == 0){

                full_value_p->value.operation_code = (operation_codes) i;

                ON_DEBUG_CONSOLE( printf("Detected operation %s\n", OPERATIONS[i].txt_form); )

                break;

            }else if(i == sizeof(OPERATIONS) - 1){

                ON_DEBUG_CONSOLE( printf(RED_COLOR "ERROR: incorrect data in file of tree, in %llu idx incorrect name of operation\n" DEFAULT_COLOR, *symbol_idx_p); )

                return RET_ERROR;
            }
        }
    }

    while(tree_text[(*symbol_idx_p)] != '(' && tree_text[(*symbol_idx_p)] != ')'){

        (*symbol_idx_p)++;
    }

    ON_DEBUG_CONSOLE( printf("idx: %llu\n", *symbol_idx_p); )

    return RET_CORRECT;
}

void printValueOfNode(FILE* const out_file_p, const node_full_value_t node_full_value){

    assert(out_file_p);

    switch(node_full_value.node_type){

        case CONST_NODE:

            fprintf(out_file_p, "%lg", node_full_value.value.const_value);
            break;

        case OPERATION_NODE:

            printOperation(out_file_p, node_full_value);
            break;

        case VARIABLE_NODE:

            printVar(out_file_p, node_full_value);
            break;

        default:

            printf(RED_COLOR "ERROR: incorrect node value type\n" DEFAULT_COLOR);
    }
}

void printOperation(FILE* const out_file_p, const node_full_value_t node_full_value){

    assert(out_file_p);
    assert(node_full_value.node_type == OPERATION_NODE);

    fprintf(out_file_p, "%s", OPERATIONS[node_full_value.value.operation_code].txt_form);

}

void printVar(FILE* const out_file_p, const node_full_value_t node_full_value){

    assert(out_file_p);
    assert(node_full_value.node_type == VARIABLE_NODE);

    switch(node_full_value.value.var_code){

        case X_VAR:

            fprintf(out_file_p, "x");
            break;

        case Y_VAR:

            fprintf(out_file_p, "y");
            break;

        default:

            printf(RED_COLOR "ERROR: incorrect value of node: incorrect operation\n" DEFAULT_COLOR);
    }
}

void printNodeType(FILE* const out_file_p, const node_full_value_t node_full_value){

    assert(out_file_p);

    switch(node_full_value.node_type){

        case CONST_NODE:

            fprintf(out_file_p, "CONST");
            break;

        case OPERATION_NODE:

            fprintf(out_file_p, "OPERATION");
            break;

        case VARIABLE_NODE:

            fprintf(out_file_p, "VARIABLE");
            break;

        default:

            printf(RED_COLOR "ERROR: incorrect value of node: incorrect operation\n" DEFAULT_COLOR);
    }
}
