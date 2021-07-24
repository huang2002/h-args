#pragma once
#include "./common.h"

typedef struct _Arg
{
    ArgKey name;
    int value_count; // length of `values`
    ArgValue* values;
} Arg;

typedef struct _Args {
    int named_count; // length of `named_args`
    Arg* default_arg;
    Arg** named_args;
} Args;

/**
 * Create a new arg with the given name.
 * (Returns NULL on error.)
 */
Arg* create_arg(ArgKey name) {
    Arg* arg = (Arg*)malloc(sizeof(Arg));
    if (arg == NULL) {
        return NULL;
    }
    arg->name = name;
    arg->value_count = 0;
    arg->values = (ArgValue*)malloc(sizeof(ArgValue) * MAX_VALUE_COUNT);
    if (arg->values == NULL) {
        return NULL;
    }
    return arg;
}

/**
 * Create a new arg collection.
 * (Returns NULL on error.)
 */
Args* create_args() {
    Args* args = (Args*)malloc(sizeof(Args));
    if (args == NULL) {
        return NULL;
    }
    args->named_count = 0;
    args->default_arg = create_arg(NULL);
    if (args->default_arg == NULL) {
        return NULL;
    }
    args->named_args = (Arg**)malloc(sizeof(Arg*) * MAX_ARG_COUNT);
    if (args->named_args == NULL) {
        return NULL;
    }
    return args;
}

/**
 * Find the arg with the given name.
 * (Returns NULL if it does not exist.)
 */
Arg* find_arg(
    Args* args,
    ArgKey key
) {
    int i;
    if (key == NULL) {
        return args->default_arg;
    }
    for (i = 0; i < args->named_count; i++) {
        if (strcmp(key, args->named_args[i]->name) == 0) {
            return args->named_args[i];
        }
    }
    return NULL;
}

/**
 * Push a value into arg->values.
 * (Returns ERR_TOO_MANY_VALUES on error and 0 on success.)
 */
int push_arg_value(Arg* arg, ArgValue value) {
    if (arg->value_count >= MAX_VALUE_COUNT) {
        return ERR_TOO_MANY_VALUES;
    } else {
        arg->values[arg->value_count++] = value;
        return 0;
    }
}

/**
 * Push an arg into args->named_args.
 * (Returns ERR_TOO_MANY_ARGS on error and 0 on success.)
 */
int push_arg(Args* args, Arg* arg) {
    if (args->named_count >= MAX_ARG_COUNT) {
        return ERR_TOO_MANY_ARGS;
    } else {
        args->named_args[args->named_count++] = arg;
        return 0;
    }
}
