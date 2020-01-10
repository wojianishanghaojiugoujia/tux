#ifndef DEBUG
#define DEBUG
#endif

#include <winsock2.h>
#include <iostream>
#include <duktape.h>
#include <duk_console.h>
#include "duk_module_resolve_init.hpp"
#include "bindings.hpp"
#include "path.hpp"
#include "httplib.h"
using namespace std;

#define TUX_VERSION 202001101

int main(int argc, char *argv[])
{
    TUX_INFO("tux version checking...")
    httplib::Client cli("ys.yuwabao.net");
    auto res = cli.Get("/img/version");
    if (!res || res->status != 200)
    {
        TUX_ERROR("checking error code: 0xff(" << (res ? res->status : -1) << ")")
        return -1;
    }
    auto version = s2int(res->body);
    if (version == -1)
    {
        TUX_ERROR("checking error code: 0x01(" << res->body << ")")
        return -1;
    }

    if (version != TUX_VERSION)
    {
        TUX_INFO("tux version has expired, please update the version!!!")
        return -1;
    }

    TUX_INFO("tux version:" << TUX_VERSION)

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
