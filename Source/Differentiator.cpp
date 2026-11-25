#include "..\Headers\Differentiator.h"



node_t* differentiateSubtree(const node_t* const func_root_p){

    if(func_root_p == NULL){

        return NULL;
    }

    if(func_root_p->full_value.node_type == CONST_NODE ||
    (func_root_p->full_value.node_type == VARIABLE_NODE && func_root_p->full_value.value.var_code != X_VAR)){

        return _NUM(0);

    }else if(func_root_p->full_value.node_type == VARIABLE_NODE){

        return _NUM(1);

    }else{

        switch(func_root_p->full_value.value.operation_code){

            case ADD:   return _ADD(_DL, _DR);

            case SUB:   return _SUB(_DL, _DR);

            case MUL:   return _ADD(_MUL(_CL, _DR), _MUL(_DL, _CR));

            case DIV:   return _DIV(_SUB(_MUL(_DL, _CR), _MUL(_CL, _DR)), _MUL(_CR, _CR));

            case SIN:   return _MUL(_COS(_CL), _DL);

            case COS:   return _MUL(_SUB(_NUM(0), _SIN(_CL)), _DL);

            case POW:   return diffPow(func_root_p);

            case LN:    return _MUL(_POW(_CL, _NUM(-1)), _DL);

            default:

                printf(RED_COLOR "ERROR: incorrect operation code for differentiation\n" DEFAULT_COLOR);
                return NULL;
        }
    }
}

node_t* diffPow(const node_t* const func_root_p){

    node_t* right_part = _ADD(_MUL(_DIV(_CR, _CL), _DL), _MUL(_LN(_CL), _DR));
    return _MUL(_POW(_CL, _CR), right_part);
}
