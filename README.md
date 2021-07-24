# h-args

> A simple argument-parsing lib for C.

## Example

```c
#include <stdlib.h>
#include <stdio.h>
#include "path/to/h-args/main.h"

int main(int argc, const char* argv[]) {

    ArgList* arg_list = create_arg_list(1);
    Args* args = NULL;
    Arg* arg_foo;

    if (arg_list != NULL) {
        def_arg(arg_list, "--help", "-h", NULL, "print help info");
        def_arg(arg_list, "--foo", NULL, "<value>", "arg foo");
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

    if (find_arg(args, "--help") != NULL) {
        printf("\nhelp info:\n%s", generate_arg_help(arg_list));
        return 0;
    }

    arg_foo = find_arg(args, "--foo");
    do_something_with(arg_foo);

    return 0;

}
```
