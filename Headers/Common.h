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


#ifdef DEBUG_VIS

    #define ON_DEBUG_VIS(...) __VA_ARGS__
    #define OFF_DEBUG_VIS(...)

#else

    #define ON_DEBUG_VIS(...)
    #define OFF_DEBUG_VIS(...) __VA_ARGS__

#endif

#ifdef DEBUG_CONSOLE

    #define ON_DEBUG_CONSOLE(...) __VA_ARGS__
    #define OFF_DEBUG_CONSOLE(...)

#else

    #define ON_DEBUG_CONSOLE(...)
    #define OFF_DEBUG_CONSOLE(...) __VA_ARGS__

#endif

#endif
