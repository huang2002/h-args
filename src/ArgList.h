#pragma once
#include "./common.h"

typedef struct _ArgDef {
    ArgKey name;
    ArgKey alias;
    char* value;
    char* help;
} ArgDef;

typedef struct _ArgList {
    int allow_default_arg;
    int length; // length of `args`
    ArgDef** args;
} ArgList;

/**
 * Create a new arg list.
 * (Returns NULL on error.)
 */
ArgList* create_arg_list(int allow_default_arg) {
    ArgList* arg_list = (ArgList*)malloc(sizeof(ArgList));
    if (arg_list == NULL) {
        return NULL;
    }
    arg_list->allow_default_arg = allow_default_arg;
    arg_list->length = 0;
    arg_list->args = (ArgDef**)malloc(sizeof(ArgDef*) * MAX_ARG_COUNT);
    if (arg_list->args == NULL) {
        return NULL;
    }
    return arg_list;
}

/**
 * Define a new arg in the arg list.
 * (Returns NULL on error.)
 */
ArgDef* def_arg(
    ArgList* arg_list,
    ArgKey name,
    ArgKey alias,
    char* value,
    char* help
) {
    ArgDef* def = (ArgDef*)malloc(sizeof(ArgDef));
    if (def == NULL) {
        return NULL;
    }
    def->name = name;
    def->alias = alias;
    def->value = value;
    def->help = help;
    arg_list->args[arg_list->length++] = def;
    return def;
}

/**
 * Find the original name of the given alias.
 * (Returns NULL if it does not exist.)
 */
ArgKey find_name(
    ArgList* arg_list,
    ArgKey alias
) {
    int i;
    ArgDef* def;
    for (i = 0; i < arg_list->length; i++) {
        def = arg_list->args[i];
        if (
            def->alias != NULL
            && strcmp(alias, def->alias) == 0
        ) {
            return def->name;
        }
    }
    return NULL;
}

/**
 * Find the arg definition with the given name.
 * (Returns NULL if it does not exist.)
 */
ArgDef* find_def(
    ArgList* arg_list,
    ArgKey name
) {
    int i;
    for (i = 0; i < arg_list->length; i++) {
        if (strcmp(name, arg_list->args[i]->name) == 0) {
            return arg_list->args[i];
        }
    }
    return NULL;
}
