#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <math.h>

#include "Common.h"

enum operation_codes{

    ADD = 0,
    SUB,
    MUL,
    DIV,

    SIN,
    COS,
    TG,
    CTG,

    POW,
    LN
};

typedef double (*function_t)(double, double);

struct operation_t{

    const char*       txt_form     ;
    unsigned char     num_of_args  ;
    function_t        calc_func_p  ;
    bool              is_tex_pref  ;
    const char*       tex_txt_form ;
    unsigned char     math_priority;

};

double calcAdd(double left_arg, double right_arg);
double calcSub(double left_arg, double right_arg);
double calcMul(double left_arg, double right_arg);
double calcDiv(double left_arg, double right_arg);

double calcSin(double left_arg, double right_arg);
double calcCos(double left_arg, double right_arg);
double calcTg (double left_arg, double right_arg);
double calcCtg(double left_arg, double right_arg);

double calcPow(double left_arg, double right_arg);
double calcLn (double left_arg, double right_arg);

// TODO унарный минус,
// TODO упрощение последовательности минусов через эту операцию

const operation_t OPERATIONS[] = {

    {.txt_form = "+"  , .num_of_args = 2, .calc_func_p = calcAdd, .is_tex_pref = false, .tex_txt_form = "+"     , .math_priority = 2},
    {.txt_form = "-"  , .num_of_args = 2, .calc_func_p = calcSub, .is_tex_pref = false, .tex_txt_form = "-"     , .math_priority = 2},
    {.txt_form = "*"  , .num_of_args = 2, .calc_func_p = calcMul, .is_tex_pref = false, .tex_txt_form = "\\cdot", .math_priority = 1},
    {.txt_form = "/"  , .num_of_args = 2, .calc_func_p = calcDiv, .is_tex_pref = true , .tex_txt_form = "\\frac", .math_priority = 3},

    {.txt_form = "sin", .num_of_args = 1, .calc_func_p = calcSin, .is_tex_pref = true , .tex_txt_form = "\\sin" , .math_priority = 0},
    {.txt_form = "cos", .num_of_args = 1, .calc_func_p = calcCos, .is_tex_pref = true , .tex_txt_form = "\\cos" , .math_priority = 0},
    {.txt_form = "tg" , .num_of_args = 1, .calc_func_p = calcTg , .is_tex_pref = true , .tex_txt_form = "\\tg"  , .math_priority = 0},
    {.txt_form = "ctg", .num_of_args = 1, .calc_func_p = calcCtg, .is_tex_pref = true , .tex_txt_form = "\\ctg" , .math_priority = 0},

    // {.txt_form = "arcsin", .num_of_args = 1, .calc_func_p = calcSin, .is_tex_pref = true , .tex_txt_form = "\\sin" , .math_priority = 0},
    // {.txt_form = "arccos", .num_of_args = 1, .calc_func_p = calcCos, .is_tex_pref = true , .tex_txt_form = "\\cos" , .math_priority = 0},
    // {.txt_form = "arctg" , .num_of_args = 1, .calc_func_p = calcTg , .is_tex_pref = true , .tex_txt_form = "\\tg"  , .math_priority = 0},
    // {.txt_form = "arcctg", .num_of_args = 1, .calc_func_p = calcCtg, .is_tex_pref = true , .tex_txt_form = "\\ctg" , .math_priority = 0},

    {.txt_form = "^"  , .num_of_args = 2, .calc_func_p = calcPow, .is_tex_pref = false, .tex_txt_form = "^"     , .math_priority = 0},
    {.txt_form = "ln" , .num_of_args = 1, .calc_func_p = calcLn , .is_tex_pref = true , .tex_txt_form = "\\ln"  , .math_priority = 0}
};

#endif
