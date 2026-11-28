#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "..\Common.h"
#include "Tree.h"
#include "TreeTextFormat.h"

const int MAX_LEN_OF_STR_FOR_SYSTEM_CALL = 250;
const int MAX_LEN_OF_NAME_OF_SVG_FILE    = 100;
const int SYSTEM_CORRECT_RETURN          =   0;

const char* const CONST_NODE_COLOR      = "#40b940";
const char* const OPERATION_NODE_COLOR  = "yellow"   ;
const char* const VARIABLE_NODE_COLOR   = "#4fb6b6";


const char* const NAME_OF_DOT_DATA_FILE = ".\\Dump\\Log\\DataForVisualization.dot";

void visualizeTree             (const node_t* const root_p, FILE* const log_file_p, const char* const comment_str);
void addTreeToVisualization    (const node_t* const root_p, FILE* const out_file_p);

const char* getNodeColor(const node_t* const root_p);


#endif
