#ifndef LOG_PRINTING_H
#define LOG_PRINTING_H

#include "Common.h"
#include ".\Tree\TreeCommon.h"
#include ".\Tree\TreeTextFormat.h"

void printTreeInTexFormat     (FILE* const out_file_p, const node_t* const root_p);
void printSubtreeInTexFormat  (FILE* const out_file_p, const node_t* const root_p);
void printOpSubtreeInTexFormat(FILE* const out_file_p, const node_t* const root_p);

void getParenthesis(const char* * const l_l_par_p,
                    const char* * const l_r_par_p,
                    const char* * const r_l_par_p,
                    const char* * const r_r_par_p,
                    const node_t* const root_p);

#endif
