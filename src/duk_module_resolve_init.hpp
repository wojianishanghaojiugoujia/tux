#pragma once
#include <duktape.h>
#include <duk_module_node.h>
#include <string>
#include "path.hpp"
#include "fs.hpp"

duk_ret_t _cb_resolve_module(duk_context *ctx);
std::string mod_source(duk_context *ctx, const std::string &filename, const std::string &source);
duk_ret_t _cb_load_module(duk_context *ctx);
void duk_module_resolve_init(duk_context *ctx);

void duk_module_resolve_init(duk_context *ctx)
{
    duk_push_object(ctx);
    duk_push_c_function(ctx, _cb_resolve_module, DUK_VARARGS);
    duk_put_prop_string(ctx, -2, "resolve");
    duk_push_c_function(ctx, _cb_load_module, DUK_VARARGS);
    duk_put_prop_string(ctx, -2, "load");
    duk_module_node_init(ctx);
}

duk_ret_t _cb_resolve_module(duk_context *ctx)
{
    /*
     *  Entry stack: [ requested_id parent_id ]
     */
    const char *requested_id = duk_get_string(ctx, 0);
    const char *parent_id = duk_get_string(ctx, 1); /* calling module */
    std::string resolvedId = requested_id;

    resolvedId = dirname(parent_id) + DIRECTORY_SEPARATOR + resolvedId;
    if (!file_exists(resolvedId.c_str()))
    {
        auto tmp = resolvedId + ".js";
        if (!file_exists(tmp.c_str()))
        {
            tmp = resolvedId + DIRECTORY_SEPARATOR + "index.js";
            if (!file_exists(tmp.c_str()))
            {
                return duk_error(ctx, DUK_ERR_ERROR, "resolve file not found!");
            }
        }
        resolvedId = tmp;
    }
    resolvedId = realpath(resolvedId);

    /* Arrive at the canonical module ID somehow. */
    duk_push_string(ctx, resolvedId.c_str());
    return 1; /*nrets*/
}

std::string mod_source(duk_context *ctx, const std::string &filename, const std::string &source)
{
    duk_push_string(ctx, filename.c_str());
    duk_json_encode(ctx, -1);
    std::string filenamej = duk_get_string(ctx, -1);
    duk_pop(ctx);

    auto dn = dirname(filename);
    duk_push_string(ctx, dn.c_str());
    duk_json_encode(ctx, -1);
    std::string dirnamej = duk_get_string(ctx, -1);
    duk_pop(ctx);

    duk_push_string(ctx, DIRECTORY_SEPARATOR);
    duk_json_encode(ctx, -1);
    std::string dsj = duk_get_string(ctx, -1);
    duk_pop(ctx);

    return "var __ds=" + dsj +
           ";var __filename=" + filenamej +
           ";var __dirname=" + dirnamej +
           ";" + source;
}

duk_ret_t _cb_load_module(duk_context *ctx)
{
    /*
     *  Entry stack: [ resolved_id exports module ]
     */
    /* Arrive at the JS source code for the module somehow. */
    auto filename = duk_get_string(ctx, 0);
    auto module_source = file_get_contents(filename);

    duk_push_string(ctx, mod_source(ctx, filename, module_source).c_str());

    return 1; /*nrets*/
}