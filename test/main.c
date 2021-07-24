#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ARG_NAME_FORMAT "%12s "

#include "../main.h"

void print_array(
    const char* tag,
    const char* delimiter,
    const char** array,
    int length
) {
    int i;
    printf("%s%s [", tag, delimiter);
    for (i = 0; i < length; i++) {
        if (i) {
            printf(",");
        }
        printf(" \"%s\"", array[i]);
    }
    printf(" ]\n");
}

void print_arg(
    const char* tag,
    const char* delimiter,
    Arg* arg
) {
    if (arg != NULL) {
        print_array(tag, delimiter, arg->values, arg->value_count);
    } else {
        printf("%s%s NULL\n", tag, delimiter);
    }
}

int main(int argc, const char* argv[]) {

    int i, j;
    ArgList* arg_list = create_arg_list(1);
    Args* args = NULL;
    Arg* arg;

    if (arg_list != NULL) {
        def_arg(arg_list, "--foo", "-f", "<value>", "arg foo");
        def_arg(arg_list, "-a", NULL, "<values...>", "arg a");
        def_arg(arg_list, "--help", "-h", NULL, "print help info");
        args = parse_args(arg_list, argc, argv);
    }

    if (args == NULL) {
        printf("PARSING ERROR!");
        return 1;
    }

    if (check_args(args, arg_list)) {
        printf("CHECKING ERROR");
        return 1;
    }

    print_array("argv", ":", argv, argc);

    print_arg("default_arg", ":", args->default_arg);

    printf("named_args:\n");
    for (i = 0; i < args->named_count; i++) {
        arg = args->named_args[i];
        print_arg(arg->name, " ->", arg);
    }

    arg = find_arg(args, NULL);
    print_arg("find_arg(args, NULL)", ":", arg);

    arg = find_arg(args, "--foo");
    print_arg("find_arg(args, \"--foo\")", ":", arg);

    arg = find_arg(args, "-a");
    print_arg("find_arg(args, \"-a\")", ":", arg);

    arg = find_arg(args, "--help");
    print_arg("find_arg(args, \"--help\")", ":", arg);

    arg = find_arg(args, "-h");
    print_arg("find_arg(args, \"-h\")", ":", arg);

    arg = find_arg(args, "--baz");
    print_arg("find_arg(args, \"--baz\")", ":", arg);

    if (find_arg(args, "--help") != NULL) {
        printf("\nhelp info:\n%s", generate_arg_help(arg_list));
    }

    return 0;

}
