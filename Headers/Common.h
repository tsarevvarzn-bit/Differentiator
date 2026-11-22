#ifndef COMMON_H
#define COMMON_H


#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "Colors.h"

enum return_codes{

    RET_ERROR,
    RET_CORRECT
};


#ifdef DEBUG

    #define ON_DEBUG(...) __VA_ARGS__
    #define OFF_DEBUG(...)

#else

    #define ON_DEBUG(...)
    #define OFF_DEBUG(...) __VA_ARGS__

#endif

#endif
