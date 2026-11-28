#include "..\Headers\TexPrinting.h"


void printTreeInTexFormat(FILE* const out_file_p, const node_t* const root_p){

    assert(out_file_p);
    assert(root_p);

    fprintf(out_file_p, "\n$$");

    printSubtreeInTexFormat(out_file_p, root_p);

    fprintf(out_file_p, "$$\n");
}

void printSubtreeInTexFormat(FILE* const out_file_p, const node_t* const root_p){

    assert(out_file_p);
    assert(root_p);

    if(root_p->full_value.node_type == CONST_NODE){

        fprintf(out_file_p, "%lg", root_p->full_value.value.const_value);

    }else if(root_p->full_value.node_type == VARIABLE_NODE){

        printVar(out_file_p, root_p->full_value);

    }else{

        printOpSubtreeInTexFormat(out_file_p, root_p);
    }
}

void printOpSubtreeInTexFormat(FILE* const out_file_p, const node_t* const root_p){

    assert(out_file_p);
    assert(root_p);
    assert(root_p->full_value.node_type == OPERATION_NODE);
    assert(root_p->left_p);

    operation_codes op_code = root_p->full_value.value.operation_code;

    const char* l_l_parenthesis  = NULL;
    const char* l_r_parenthesis  = NULL;

    const char* r_l_parenthesis  = NULL;
    const char* r_r_parenthesis  = NULL;

    getParenthesis(&l_l_parenthesis, &l_r_parenthesis, &r_l_parenthesis, &r_r_parenthesis, root_p);

    if(OPERATIONS[op_code].is_tex_pref){

        fprintf(out_file_p, "%s{%s", OPERATIONS[op_code].tex_txt_form, l_l_parenthesis);
        printSubtreeInTexFormat(out_file_p, root_p->left_p);
        fprintf(out_file_p, "%s}", l_r_parenthesis);

        if(OPERATIONS[op_code].num_of_args == 2){

            fprintf(out_file_p, "{%s", r_l_parenthesis);
            printSubtreeInTexFormat(out_file_p, root_p->right_p);
            fprintf(out_file_p, "%s}", r_r_parenthesis);
        }

    }else{

        fprintf(out_file_p, "{%s", l_l_parenthesis);
        printSubtreeInTexFormat(out_file_p, root_p->left_p);
        fprintf(out_file_p, "%s}", l_r_parenthesis);

        fprintf(out_file_p, "%s", OPERATIONS[op_code].tex_txt_form);

        fprintf(out_file_p, "{%s", r_l_parenthesis);
        printSubtreeInTexFormat(out_file_p, root_p->right_p);
        fprintf(out_file_p, "%s}", r_r_parenthesis);
    }
}

void getParenthesis(const char* * const l_l_par_p,
                    const char* * const l_r_par_p,
                    const char* * const r_l_par_p,
                    const char* * const r_r_par_p,
                    const node_t* const root_p){

    assert(l_l_par_p);
    assert(l_r_par_p);
    assert(r_l_par_p);
    assert(r_r_par_p);

    operation_codes op_code = root_p->full_value.value.operation_code;

    *l_l_par_p  = "\\left(";
    *l_r_par_p  = "\\right)";

    *r_l_par_p  = "\\left(";
    *r_r_par_p  = "\\right)";

    if(OPERATIONS[op_code].math_priority == 0){

        return;
    }

    unsigned char left_priority  = 0;
    unsigned char right_priority = 0;

    if(root_p->left_p->full_value.node_type == OPERATION_NODE){

        left_priority  = OPERATIONS[root_p->left_p->full_value.value.operation_code].math_priority;
    }

    if(root_p->right_p != NULL && root_p->right_p->full_value.node_type == OPERATION_NODE){

        right_priority = OPERATIONS[root_p->right_p->full_value.value.operation_code].math_priority;
    }


    if(OPERATIONS[op_code].math_priority >= left_priority){

        *l_l_par_p = " ";
        *l_r_par_p = " ";
    }

    if((OPERATIONS[op_code].math_priority >= right_priority) && (op_code != SUB)){

        *r_l_par_p = " ";
        *r_r_par_p = " ";
    }
}
