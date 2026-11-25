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

    const char*       txt_form   ;
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

    {.txt_form = "+"  , .num_of_args = 2, .calc_func_p = calcAdd},
    {.txt_form = "-"  , .num_of_args = 2, .calc_func_p = calcSub},
    {.txt_form = "*"  , .num_of_args = 2, .calc_func_p = calcMul},
    {.txt_form = "/"  , .num_of_args = 2, .calc_func_p = calcDiv},
    {.txt_form = "sin", .num_of_args = 1, .calc_func_p = calcSin},
    {.txt_form = "cos", .num_of_args = 1, .calc_func_p = calcCos},
    {.txt_form = "^"  , .num_of_args = 2, .calc_func_p = calcPow},
    {.txt_form = "ln" , .num_of_args = 1, .calc_func_p = calcLn }
};

#endif
