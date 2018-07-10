#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_log.h"

#include "s_type.h"
#include "s_text.h"
#include "s_limits.h"
#include "s_cmd.h"

#include "expr.h"

#define SUBCMD_EXPR "expr"
#define SUBCMD_EXPR_OPTION_S "-s"

ENUM_RETURN subcmd_expr_option_s_proc(struct TAG_STRU_ARG *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);
    R_ASSERT(value->value != NULL, RETURN_FAILURE);

    printf("expressoin: %s\n", value->value);

    _SD result = 0.0;

    ENUM_RETURN ret_val = s_calc_rp(value->value, &result);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    printf("result: %g\n", result);
    
    return RETURN_SUCCESS;
}

int expr_init(void)
{

    ENUM_RETURN ret_val = RETURN_SUCCESS;

    ret_val = register_subcmd(SUBCMD_EXPR, 
        BOOLEAN_FALSE,
        default_subcmd_proc_handler, 
        "evaluates a reverse Polish expression.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_EXPR, 
        SUBCMD_EXPR_OPTION_S, 
        BOOLEAN_FALSE, 
        OPTION_TYPE_MANDATORY, 
        ARG_TYPE_DATA, 
        subcmd_expr_option_s_proc, 
        BOOLEAN_TRUE,
        "specify the expression string by double quote");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}





