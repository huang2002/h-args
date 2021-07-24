#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef MAX_VALUE_COUNT
#define MAX_VALUE_COUNT 32
#endif

#ifndef MAX_ARG_COUNT
#define MAX_ARG_COUNT 32
#endif

#ifndef MAX_HELP_LENGTH
#define MAX_HELP_LENGTH 512
#endif

#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 20
#endif

#ifndef ARG_NAME_FORMAT
#define ARG_NAME_FORMAT "%16s " // used in generate_arg_help
#endif

#ifndef ARG_VALUE_FORMAT
#define ARG_VALUE_FORMAT "%-12s " // used in generate_arg_help
#endif

#define ERR_DEFAULT_ARG_NOT_ALLOWED 1
#define ERR_UNKNOWN_ARG_KEY 2
#define ERR_TOO_MANY_ARGS 3
#define ERR_TOO_MANY_VALUES 4

typedef const char* ArgKey;
typedef const char* ArgValue;
