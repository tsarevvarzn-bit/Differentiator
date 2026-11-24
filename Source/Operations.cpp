#include "..\Headers\Operations.h"

#define CREATE_NEW_BIN_CALC_FUNC(name_of_func, operator)    \
                                                            \
double name_of_func(double left_arg, double right_arg){     \
                                                            \
    return left_arg operator right_arg;                     \
}

#define CHECK_RIGHT_ARGUMENT                                                                                                            \
                                                                                                                                        \
if(! isnan(right_arg))                                                                                                                  \
    printf(YELLOW_COLOR "Warning: not a NULL value of right arg of unary function for calculation: %lg, " DEFAULT_COLOR, right_arg)    \


CREATE_NEW_BIN_CALC_FUNC(calcAdd, +)
CREATE_NEW_BIN_CALC_FUNC(calcSub, -)
CREATE_NEW_BIN_CALC_FUNC(calcMul, *)
CREATE_NEW_BIN_CALC_FUNC(calcDiv, /)

double calcSin(double left_arg, double right_arg){

    CHECK_RIGHT_ARGUMENT;

    return sin(left_arg);
}

double calcCos(double left_arg, double right_arg){

    CHECK_RIGHT_ARGUMENT;

    return cos(left_arg);
}

double calcPow(double left_arg, double right_arg){

    return pow(left_arg, right_arg);
}

double calcLn(double left_arg, double right_arg){

    CHECK_RIGHT_ARGUMENT;

    return log(left_arg);
}


#undef CREATE_NEW_BIN_CALC_FUNC
#undef CHECK_RIGHT_ARGUMENT
