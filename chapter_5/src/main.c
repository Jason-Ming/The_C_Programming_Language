#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "main.h"
#include "exercise.h"
#include "example.h"
#include "expr.h"
#include "tail.h"
#include "sortf.h"

int main(int argc, char **argv)
{

    ENUM_RETURN ret_val = RETURN_SUCCESS;
    ret_val = register_introduction("this program execute examples and exerceses in chapter 5.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    ret_val = example_init();
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = exercise_init();
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = expr_init();
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = tail_init();
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = sortf_init();
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    return process(argc, argv);
}

