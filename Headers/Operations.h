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
    POW,
    LN
};

typedef double (*function_t)(double, double);

struct operation_t{

    operation_codes   code       ;
    const char* const txt_form   ;
    unsigned char     num_of_args;
    function_t        calc_func_p;

};

double calcAdd(double left_arg, double right_arg);
double calcSub(double left_arg, double right_arg);
double calcMul(double left_arg, double right_arg);
double calcDiv(double left_arg, double right_arg);

double calcSin(double left_arg, double right_arg);
double calcCos(double left_arg, double right_arg);
double calcPow(double left_arg, double right_arg);
double calcLn (double left_arg, double right_arg);

const operation_t OPERATIONS[] = {

    {.code = ADD, .txt_form = "+"  , .num_of_args = 2, .calc_func_p = calcAdd},
    {.code = SUB, .txt_form = "-"  , .num_of_args = 2, .calc_func_p = calcSub},
    {.code = MUL, .txt_form = "*"  , .num_of_args = 2, .calc_func_p = calcMul},
    {.code = DIV, .txt_form = "/"  , .num_of_args = 2, .calc_func_p = calcDiv},
    {.code = SIN, .txt_form = "sin", .num_of_args = 1, .calc_func_p = calcSin},
    {.code = COS, .txt_form = "cos", .num_of_args = 1, .calc_func_p = calcCos},
    {.code = POW, .txt_form = "^"  , .num_of_args = 2, .calc_func_p = calcPow},
    {.code = LN , .txt_form = "ln" , .num_of_args = 1, .calc_func_p = calcLn }
};

#endif
