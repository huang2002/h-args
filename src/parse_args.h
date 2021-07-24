#pragma once
#include "./common.h"
#include "./Args.h"
#include "./ArgList.h"

/**
 * Parse the given raw args into structured ones
 * according to specific arg list.
 * (Returns NULL on error.)
 */
Args* parse_args(
    ArgList* arg_list,
    int argc,
    const char* argv[]
) {
    int i, j;
    Args* args = create_args();
    Arg* arg = args->default_arg;
    ArgKey key = NULL;
    ArgKey name = NULL;
    if (args == NULL) {
        return NULL;
    }
    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-') { // arg value
            if (push_arg_value(arg, argv[i])) {
                return NULL;
            }
        } else { // arg key
            key = argv[i];
            if (arg_list != NULL) {
                name = find_name(arg_list, key);
                if (name != NULL) {
                    key = name; // alias -> name
                }
            }
            arg = create_arg(key);
            if (arg == NULL || push_arg(args, arg)) {
                return NULL;
            }
        }
    }
    return args;
}
