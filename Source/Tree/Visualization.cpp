#include "..\..\Headers\Tree\Visualization.h"

void visualizeTree(const node_t* const root_p, const char * const name_of_file){

    assert(root_p);
    assert(name_of_file);

    FILE* out_dot_file_p = fopen("DataForVisualization.dot", "w");


    fprintf(out_dot_file_p,

    "digraph {\n"
    "\n"
    "    graph [\n"
    "        rankdir=TB,\n"
    "        nodesep=0.5,\n"
    "        ranksep=0.8,\n"
    "        bgcolor=\"#312d4b\"\n"
    "    ]\n"
    "\n"
    "    edge [\n"
    "        penwidth=5,\n"
    "        color=\"#0e6fbe\",\n"
    "    ]\n"
    "\n"
    "    node [\n"
    "        shape=Mrecord\n"
    "        style = filled\n"
    "        fillcolor = \"yellow\"\n"
    "    ]\n"

    );

    addTreeToVisualization(root_p, out_dot_file_p);

    fprintf(out_dot_file_p, "\n}");


    fclose(out_dot_file_p);

    char str_for_system_call[MAX_LEN_OF_STR_FOR_SYSTEM_CALL] = "";

    sprintf(str_for_system_call, "dot.exe -Tsvg DataForVisualization.dot -o %s", name_of_file);

    int result = system(str_for_system_call);

    if(result == SYSTEM_CORRECT_RETURN){

        printf(GREEN_COLOR "Correct visualization! Look for a visualization file named " YELLOW_COLOR "\"%s\"\n" DEFAULT_COLOR, name_of_file);

    }else{

        printf(RED_COLOR "ERROR! Incorrect return of\n"     \
                   "int result = system(%s);\n"       \
                   "result: %d" DEFAULT_COLOR, str_for_system_call, result);
    }
}

void addTreeToVisualization(const node_t* const root_p, FILE* const out_file_p){

    assert(root_p);
    assert(out_file_p);

    ON_DEBUG_VIS(

    fprintf(out_file_p,
    "    \"%p\" [label= \"{\n"
    "               <parent> parent = \\\"%p\\\" |\n"
    "               node type = ",
    root_p, root_p->parent_p);

    printNodeType(out_file_p, root_p->full_value);

    fprintf(out_file_p,
    "|\n               value = "
    );

    printValueOfNode(out_file_p, root_p->full_value);

    fprintf(out_file_p,
    "|\n               { <left> left = \\\"%p\\\"| pointer = \\\"%p\\\" | <right> right = \\\"%p\\\"}\n"
    "           }\"]\n\n",
    root_p->left_p, root_p, root_p->right_p);

    )

    OFF_DEBUG_VIS(

    fprintf(out_file_p,
    "    \"%p\" [label = \"",
    root_p);

    printValueOfNode(out_file_p, root_p->full_value);

    fprintf(out_file_p,
    "\n\"]\n\n"
    );

    )

    if(root_p->left_p == NULL && root_p->right_p == NULL){

        return;
    }

    if(root_p->left_p == NULL){

        addTreeToVisualization(root_p->right_p, out_file_p);
        ON_DEBUG_VIS( fprintf(out_file_p, "   \"%p\":right->\"%p\"\n", root_p, root_p->right_p);)
        OFF_DEBUG_VIS(fprintf(out_file_p, "   \"%p\"->\"%p\"\n", root_p, root_p->right_p);)
        return;
    }

    if(root_p->right_p == NULL){

        addTreeToVisualization(root_p->left_p, out_file_p);
        ON_DEBUG_VIS( fprintf(out_file_p, "   \"%p\":left->\"%p\"\n", root_p, root_p->left_p);)
        OFF_DEBUG_VIS(fprintf(out_file_p, "   \"%p\"->\"%p\"\n", root_p, root_p->left_p);)
        return;
    }

    addTreeToVisualization(root_p->left_p , out_file_p);
    addTreeToVisualization(root_p->right_p, out_file_p);

    ON_DEBUG_VIS( fprintf(out_file_p, "   \"%p\":left->\"%p\"\n" , root_p, root_p->left_p );)
    OFF_DEBUG_VIS(fprintf(out_file_p, "   \"%p\"->\"%p\"\n"      , root_p, root_p->left_p );)
    ON_DEBUG_VIS( fprintf(out_file_p, "   \"%p\":right->\"%p\"\n" , root_p, root_p->right_p);)
    OFF_DEBUG_VIS(fprintf(out_file_p, "   \"%p\"->\"%p\"\n"       , root_p, root_p->right_p);)

    fprintf(out_file_p, "   {rank=same; \"%p\"; \"%p\"}\n", root_p->left_p, root_p->left_p);
}
