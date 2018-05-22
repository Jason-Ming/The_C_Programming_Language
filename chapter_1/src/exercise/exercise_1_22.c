#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"

#define DEFAULT_FOLD_NUM 80

PRIVATE int fold_num = DEFAULT_FOLD_NUM;

ENUM_RETURN subcmd_fold_option_n_proc(struct TAG_STRU_ARG *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);
    R_ASSERT(value->value != NULL, RETURN_FAILURE);

    fold_num = atoi(value->value);
    
    return RETURN_SUCCESS;
}

ENUM_RETURN subcmd_fold_proc(STRU_OPTION_RUN_BLOCK *value)
{
    return RETURN_SUCCESS;
}

int main(int argc, char **argv)
{
    ENUM_RETURN ret_val;
    ret_val = register_introduction("this program folds the lines of input file.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    ret_val = register_usage("<sub-command> [<input files>] [<options> [<args>]]");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_subcmd("fold", BOOLEAN_TRUE, subcmd_fold_proc, "fold each line in input files");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option("fold", "-n", OPTION_TYPE_OPTIONAL, ARG_TYPE_DATA, subcmd_fold_option_n_proc, "set the fold number");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    return process(argc, argv);
}
