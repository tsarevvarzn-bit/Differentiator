#include "..\Headers\Operations.h"


#define CREATE_NEW_BIN_CALC_FUNC(name_of_func, operator)    \
                                                            \
double name_of_func(double left_arg, double right_arg){     \
                                                            \
    return left_arg operator right_arg;                     \
}


#define CREATE_NEW_UN_CALC_FUNC(name_of_func, operator)                                                                                                         \
                                                                                                                                                                \
double name_of_func(double left_arg, double right_arg){                                                                                                         \
                                                                                                                                                                \
    if(! isnan(right_arg))                                                                                                                                      \
        printf(YELLOW_COLOR "Warning: not a NAN value of right arg of unary function: " # name_of_func" for calculation: %lg\n" DEFAULT_COLOR, right_arg);      \
                                                                                                                                                                \
    return operator(left_arg);                                                                                                                                  \
}


CREATE_NEW_BIN_CALC_FUNC(calcAdd, +)
CREATE_NEW_BIN_CALC_FUNC(calcSub, -)
CREATE_NEW_BIN_CALC_FUNC(calcMul, *)
CREATE_NEW_BIN_CALC_FUNC(calcDiv, /)

CREATE_NEW_UN_CALC_FUNC(calcSin, sin)
CREATE_NEW_UN_CALC_FUNC(calcCos, cos)
CREATE_NEW_UN_CALC_FUNC(calcTg , tan)
CREATE_NEW_UN_CALC_FUNC(calcCtg, 1 / tan)


double calcPow(double left_arg, double right_arg){

    return pow(left_arg, right_arg);
}

CREATE_NEW_UN_CALC_FUNC(calcLn, log)


#undef CREATE_NEW_BIN_CALC_FUNC
#undef CREATE_NEW_UN_CALC_FUNC
