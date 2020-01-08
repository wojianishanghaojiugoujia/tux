#ifndef DEBUG
#define DEBUG
#endif

#include <iostream>
#include <duktape.h>
#include <duk_console.h>
#include "duk_module_resolve_init.hpp"
#include "bindings.hpp"
#include "path.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        return -1;
    }

    duk_context *ctx = duk_create_heap_default();

    duk_console_init(ctx, DUK_CONSOLE_STDOUT_ONLY);
    duk_module_resolve_init(ctx);
    tux_bindings_init(ctx);
    tux_core_init(ctx, entry_root());

    auto mainScriptPath = realpath(argv[1]);
    string script;
    script = file_get_contents(mainScriptPath.c_str());
    duk_push_string(ctx, mod_source(ctx, mainScriptPath, script).c_str());
    duk_module_node_peval_main(ctx, mainScriptPath.c_str());

    if (duk_is_error(ctx, -1))
    {
        printf("%s\n", duk_safe_to_string(ctx, -1));
    }
    duk_pop(ctx);

    duk_destroy_heap(ctx);
    return 0;
}
