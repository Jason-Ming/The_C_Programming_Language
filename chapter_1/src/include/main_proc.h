#ifndef __MAIN_PROC_H__
#define __MAIN_PROC_H__
#include "s_clinkage.h"
#include "s_defines.h"
#include "s_type.h"

typedef ENUM_RETURN (*FUNC_MAIN_PROC)(void);

typedef struct TAG_STRU_MAIN_PROC
{
    const char * n_value;
    FUNC_MAIN_PROC handler;
    const char * introduction;
}STRU_MAIN_PROC;

#endif

