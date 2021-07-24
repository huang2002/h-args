#pragma once
#include "./common.h"
#include "./ArgList.h"
#include "./Args.h"

/**
 * Check the args according to the given arg list.
 * (Returns ERR_DEFAULT_ARG_NOT_ALLOWED/ERR_UNKNOWN_ARG_KEY
 * on error and 0 on success.)
 */
int check_args(
    Args* args,
    ArgList* arg_list
) {
    int i;
    if (
        !arg_list->allow_default_arg
        && args->default_arg->value_count > 0
    ) {
        return ERR_DEFAULT_ARG_NOT_ALLOWED;
    }
    for (i = 0; i < args->named_count; i++) {
        if (find_def(arg_list, args->named_args[i]->name) == NULL) {
            return ERR_UNKNOWN_ARG_KEY;
        }
    }
    return 0;
}
