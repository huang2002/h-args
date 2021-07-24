#pragma once
#include "./common.h"
#include "./ArgList.h"

/**
 * Generate help string from the given arg list.
 * (Returns NULL on error.)
 */
char* generate_arg_help(ArgList* arg_list) {

    char* result = (char*)malloc(sizeof(char) * MAX_HELP_LENGTH);
    char* temp0 = (char*)malloc(sizeof(char) * MAX_NAME_LENGTH);
    char* temp1 = (char*)malloc(sizeof(char) * MAX_NAME_LENGTH);
    ArgDef* def;
    int i;

    if (result == NULL || temp0 == NULL || temp1 == NULL) {
        return NULL;
    }

    *result = '\0';

    for (i = 0; i < arg_list->length; i++) {

        def = arg_list->args[i];

        if (def->name == NULL || def->help == NULL) {
            return NULL;
        }

        // name[, alias]
        strcpy(temp0, def->name);
        if (def->alias != NULL) {
            strcat(temp0, ", ");
            strcat(temp0, def->alias);
        }
        sprintf(temp1, ARG_NAME_FORMAT, temp0);
        strcat(result, temp1);
        strcat(result, " ");

        // value
        if (def->value != NULL) {
            strcpy(temp0, def->value);
        } else {
            *temp0 = '\0';
        }
        sprintf(temp1, ARG_VALUE_FORMAT, temp0);
        strcat(result, temp1);
        strcat(result, " ");

        // help
        strcat(result, def->help);
        strcat(result, "\n");

    }

    return result;

}
