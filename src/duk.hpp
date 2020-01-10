#pragma once

#include <duktape.h>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "log.hpp"
#include "struct.hpp"

void _duk_assign_point(duk_context *ctx, duk_idx_t obj_idx, const POINT &point)
{
    duk_push_int(ctx, point.x);
    duk_put_prop_string(ctx, obj_idx, "x");
    duk_push_int(ctx, point.y);
    duk_put_prop_string(ctx, obj_idx, "y");
}

void _duk_assign_size(duk_context *ctx, duk_idx_t obj_idx, const SIZE &size)
{
    duk_push_uint(ctx, size.cx);
    duk_put_prop_string(ctx, obj_idx, "w");
    duk_push_uint(ctx, size.cy);
    duk_put_prop_string(ctx, obj_idx, "h");
}

duk_bool_t duk_get_size(duk_context *ctx, duk_idx_t idx, SIZE &size);
duk_bool_t duk_get_point(duk_context *ctx, duk_idx_t idx, POINT &point);

duk_bool_t duk_get_rect(duk_context *ctx, duk_idx_t idx, RECT &rect)
{
    idx = duk_require_normalize_index(ctx, idx);

    if (!duk_is_object(ctx, idx))
    {
        // TUX_ERROR("required an object")
        return false;
    }
    POINT p;

    if (!duk_get_point(ctx, idx, p))
    {
        // TUX_ERROR("argument must be a rectlike object");
        return false;
    }

    SIZE s;

    if (!duk_get_size(ctx, idx, s))
    {
        // TUX_ERROR("argument must be a rectlike object");
        return false;
    }

    build_rect(p, s, &rect);

    return true;
}

void duk_push_rect(duk_context *ctx, const RECT &rect)
{
    POINT p;
    SIZE s;
    parse_rect(rect, &p, &s);
    duk_idx_t obj_idx = duk_push_object(ctx);

    _duk_assign_point(ctx, obj_idx, p);
    _duk_assign_size(ctx, obj_idx, s);
}

duk_bool_t duk_get_point(duk_context *ctx, duk_idx_t idx, POINT &point)
{
    idx = duk_require_normalize_index(ctx, idx);

    if (!duk_is_object(ctx, idx))
    {
        // TUX_ERROR("required an object")
        return false;
    }
    duk_get_prop_string(ctx, idx, "x");
    if (duk_is_null_or_undefined(ctx, -1))
    {
        // TUX_ERROR("argument must be a pointlike object");
        duk_pop(ctx);
        return false;
    }
    point.x = duk_to_number(ctx, -1);
    duk_pop(ctx);

    duk_get_prop_string(ctx, idx, "y");
    if (duk_is_null_or_undefined(ctx, -1))
    {
        // TUX_ERROR("argument must be a pointlike object");
        duk_pop(ctx);
        return false;
    }
    point.y = duk_to_number(ctx, -1);
    duk_pop(ctx);

    return true;
}

void duk_push_point(duk_context *ctx, const POINT &point)
{
    duk_idx_t obj_idx = duk_push_object(ctx);
    _duk_assign_point(ctx, obj_idx, point);
}

duk_bool_t duk_get_size(duk_context *ctx, duk_idx_t idx, SIZE &size)
{
    idx = duk_require_normalize_index(ctx, idx);

    if (!duk_is_object(ctx, idx))
    {
        // TUX_ERROR("required an object")
        return false;
    }
    duk_get_prop_string(ctx, idx, "w");
    if (duk_is_null_or_undefined(ctx, -1))
    {
        // TUX_ERROR("argument must be a pointlike object");
        duk_pop(ctx);
        return false;
    }
    size.cx = duk_to_number(ctx, -1);
    duk_pop(ctx);

    duk_get_prop_string(ctx, idx, "h");
    if (duk_is_null_or_undefined(ctx, -1))
    {
        // TUX_ERROR("argument must be a pointlike object");
        duk_pop(ctx);
        return false;
    }
    size.cy = duk_to_number(ctx, -1);
    duk_pop(ctx);

    return true;
}

void duk_push_size(duk_context *ctx, const SIZE &size)
{
    duk_idx_t obj_idx = duk_push_object(ctx);
    _duk_assign_size(ctx, obj_idx, size);
}
