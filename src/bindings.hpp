#pragma once
#include <duktape.h>
#include <opencv2/opencv.hpp>
#include <string>
#include "path.hpp"
#include "fs.hpp"
#include "duk.hpp"
#include "core/mouse.hpp"
#include "core/win.hpp"
#include "core/capture.hpp"
#include "core/mat.hpp"

// 绑定duk的方法
void tux_core_init(duk_context *ctx, std::string entryRoot);
void tux_bindings_init(duk_context *ctx);

// 初始化core库
void tux_core_init(duk_context *ctx, std::string entryRoot)
{
    auto corePath = entryRoot + DIRECTORY_SEPARATOR + "core" + DIRECTORY_SEPARATOR;
    std::vector<cv::String> file_vec;
    cv::glob(corePath + "*.js", file_vec);
    for (std::string file_name : file_vec)
    {
        auto fn = filename(file_name);
        auto modName = fn.substr(0, fn.length() - 3);
        std::string js = mod_source(ctx, file_name, file_get_contents(file_name.c_str()));
        if (duk_peval_string(ctx, js.c_str()) != 0)
        {
            TUX_ERROR("load file" << file_name << "failed: " << duk_safe_to_string(ctx, -1))
        }
        else
        {
            duk_put_global_string(ctx, modName.c_str());
        }
    }
}

duk_ret_t fn_realpath(duk_context *ctx);   // realpath
duk_ret_t fn_dirname(duk_context *ctx);    // dirname
duk_ret_t fn_cwd(duk_context *ctx);        // 全局cwd
duk_ret_t fn_sleep(duk_context *ctx);      // 睡眠
duk_ret_t fn_exit(duk_context *ctx);       // 退出程序
duk_ret_t fn_entry_path(duk_context *ctx); // mat_read(path)
duk_ret_t fn_glob(duk_context *ctx);       // mat_read(path)

duk_ret_t fn_win_from_mouse(duk_context *ctx);
duk_ret_t fn_win_position(duk_context *ctx);
duk_ret_t fn_win_set_position(duk_context *ctx);
duk_ret_t fn_win_resize(duk_context *ctx);
duk_ret_t fn_win_rect(duk_context *ctx);
duk_ret_t fn_win_size(duk_context *ctx);
duk_ret_t fn_win_capture(duk_context *ctx);
duk_ret_t fn_win_active(duk_context *ctx);
duk_ret_t fn_win_zorder(duk_context *ctx);
duk_ret_t fn_win_show(duk_context *ctx);

duk_ret_t fn_mouse_scroll(duk_context *ctx);  // mouse_scroll(h, pointLike, direction = -1, step = 120)
duk_ret_t fn_mouse_click(duk_context *ctx);   // mouse_click(h, pointLike, whichBtn = -1)
duk_ret_t fn_mouse_dbclick(duk_context *ctx); // mouse_dbclick(h, pointLike, whichBtn = -1)
duk_ret_t fn_mouse_move(duk_context *ctx);    // mouse_move(h, pointLike, whichBtn = -1)
duk_ret_t fn_mouse_up(duk_context *ctx);      // mouse_up(h, pointLike, whichBtn = -1)
duk_ret_t fn_mouse_down(duk_context *ctx);    // mouse_down(h, pointLike, whichBtn = -1)

duk_ret_t fn_mat_release(duk_context *ctx); // mat_release(p)
duk_ret_t fn_mat_crop(duk_context *ctx);    // mat_crop(p, rectLike)
duk_ret_t fn_mat_find(duk_context *ctx);    // mat_find(p, tplP, ...rectLikes)
duk_ret_t fn_mat_show(duk_context *ctx);    // mat_show(p, title = "", waitKey = undefined)
duk_ret_t fn_mat_make(duk_context *ctx);    // mat_make(data, fmt = 'binary,base64')
duk_ret_t fn_mat_read(duk_context *ctx);    // mat_read(path)
duk_ret_t fn_wait_key(duk_context *ctx);    // wait_key(delay=0): key

// 初始化绑定方法
void tux_bindings_init(duk_context *ctx)
{
    duk_push_c_function(ctx, fn_realpath, DUK_VARARGS);
    duk_put_global_string(ctx, "realpath");
    duk_push_c_function(ctx, fn_dirname, DUK_VARARGS);
    duk_put_global_string(ctx, "dirname");
    duk_push_c_function(ctx, fn_entry_path, DUK_VARARGS);
    duk_put_global_string(ctx, "entry_path");
    duk_push_c_function(ctx, fn_glob, DUK_VARARGS);
    duk_put_global_string(ctx, "glob");
    duk_push_c_function(ctx, fn_cwd, DUK_VARARGS);
    duk_put_global_string(ctx, "cwd");
    duk_push_c_function(ctx, fn_sleep, DUK_VARARGS);
    duk_put_global_string(ctx, "sleep");
    duk_push_c_function(ctx, fn_exit, DUK_VARARGS);
    duk_put_global_string(ctx, "exit");

    // 窗口相关
    duk_push_c_function(ctx, fn_win_from_mouse, DUK_VARARGS);
    duk_put_global_string(ctx, "win_from_mouse");
    duk_push_c_function(ctx, fn_win_position, DUK_VARARGS);
    duk_put_global_string(ctx, "win_position");
    duk_push_c_function(ctx, fn_win_set_position, DUK_VARARGS);
    duk_put_global_string(ctx, "win_set_position");
    duk_push_c_function(ctx, fn_win_resize, DUK_VARARGS);
    duk_put_global_string(ctx, "win_resize");
    duk_push_c_function(ctx, fn_win_rect, DUK_VARARGS);
    duk_put_global_string(ctx, "win_rect");
    duk_push_c_function(ctx, fn_win_size, DUK_VARARGS);
    duk_put_global_string(ctx, "win_size");
    duk_push_c_function(ctx, fn_win_capture, DUK_VARARGS);
    duk_put_global_string(ctx, "win_capture");
    duk_push_c_function(ctx, fn_win_active, DUK_VARARGS);
    duk_put_global_string(ctx, "win_active");
    duk_push_c_function(ctx, fn_win_zorder, DUK_VARARGS);
    duk_put_global_string(ctx, "win_zorder");
    duk_push_c_function(ctx, fn_win_show, DUK_VARARGS);
    duk_put_global_string(ctx, "win_show");

    // 鼠标相关
    duk_push_c_function(ctx, fn_mouse_scroll, DUK_VARARGS);
    duk_put_global_string(ctx, "mouse_scroll");
    duk_push_c_function(ctx, fn_mouse_click, DUK_VARARGS);
    duk_put_global_string(ctx, "mouse_click");
    duk_push_c_function(ctx, fn_mouse_dbclick, DUK_VARARGS);
    duk_put_global_string(ctx, "mouse_dbclick");
    duk_push_c_function(ctx, fn_mouse_move, DUK_VARARGS);
    duk_put_global_string(ctx, "mouse_move");
    duk_push_c_function(ctx, fn_mouse_up, DUK_VARARGS);
    duk_put_global_string(ctx, "mouse_up");
    duk_push_c_function(ctx, fn_mouse_down, DUK_VARARGS);
    duk_put_global_string(ctx, "mouse_down");

    // mat相关
    duk_push_c_function(ctx, fn_mat_release, DUK_VARARGS);
    duk_put_global_string(ctx, "mat_release");
    duk_push_c_function(ctx, fn_mat_crop, DUK_VARARGS);
    duk_put_global_string(ctx, "mat_crop");
    duk_push_c_function(ctx, fn_mat_find, DUK_VARARGS);
    duk_put_global_string(ctx, "mat_find");
    duk_push_c_function(ctx, fn_mat_show, DUK_VARARGS);
    duk_put_global_string(ctx, "mat_show");
    duk_push_c_function(ctx, fn_mat_make, DUK_VARARGS);
    duk_put_global_string(ctx, "mat_make");
    duk_push_c_function(ctx, fn_mat_read, DUK_VARARGS);
    duk_put_global_string(ctx, "mat_read");
    duk_push_c_function(ctx, fn_wait_key, DUK_VARARGS);
    duk_put_global_string(ctx, "wait_key");
}

// (path) path
duk_ret_t fn_realpath(duk_context *ctx)
{
    int n = duk_get_top(ctx);
    if (n > 0)
    {
        duk_push_string(ctx, realpath(duk_get_string(ctx, 0)).c_str());
        return 1;
    }
    return 0;
}

// (path) path
duk_ret_t fn_dirname(duk_context *ctx)
{
    int n = duk_get_top(ctx);
    if (n > 0)
    {
        duk_push_string(ctx, dirname(duk_get_string(ctx, 0)).c_str());
        return 1;
    }
    return 0;
}

// (path)
duk_ret_t fn_cwd(duk_context *ctx)
{
    duk_push_string(ctx, cwd().c_str());
    return 1;
}

// () microtimes
duk_ret_t fn_sleep(duk_context *ctx)
{
    int n = duk_get_top(ctx);
    if (n > 0)
    {
        Sleep(duk_get_uint(ctx, 0)); // 毫秒
    }
    return 0;
}

// () code=0
duk_ret_t fn_exit(duk_context *ctx)
{
    int n = duk_get_top(ctx);
    int code = 0;
    if (n > 0)
    {
        code = duk_get_int(ctx, 0); // 错误码
    }
    exit(code);
    return 0;
}

// (path)
duk_ret_t fn_entry_path(duk_context *ctx)
{
    duk_push_string(ctx, entry_root().c_str());
    return 1;
}

// (array<string>)patterms
duk_ret_t fn_glob(duk_context *ctx)
{
    int n = duk_get_top(ctx);
    duk_idx_t arr_idx = duk_push_array(ctx);
    if (n > 0)
    {
        int nn = 0;
        std::vector<cv::String> file_vec;
        cv::glob(duk_get_string(ctx, 0), file_vec);

        for (std::string file_name : file_vec)
        {
            duk_push_string(ctx, file_name.c_str());
            duk_put_prop_index(ctx, arr_idx, nn++);
        }
    }
    return 1;
}

// (hwnd)
duk_ret_t fn_win_from_mouse(duk_context *ctx)
{
    duk_push_uint(ctx, (long long)hwnd_from_mouse());
    return 1;
}

// () hwnd, pointlike, clientOnly = true
duk_ret_t fn_win_set_position(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 1)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least one arguments.");
    }
    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);
    POINT p;
    if (!duk_get_point(ctx, 1, p))
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "argument must be a pointlike object");
    }
    bool clientOnly = true;
    if (n > 2)
    {
        clientOnly = duk_to_boolean(ctx, 2);
    }
    win_set_position(hwnd, p, clientOnly);
    return 0;
}

// () hwnd, sizelike, clientOnly = true
duk_ret_t fn_win_resize(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }
    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    SIZE s;
    if (!duk_get_size(ctx, 1, s))
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "argument must be a sizelike object");
    }
    bool clientOnly = true;
    if (n > 2)
    {
        clientOnly = duk_to_boolean(ctx, 2);
    }
    win_resize(hwnd, s, clientOnly);
    return 0;
}

// (rectlike) hwnd, clientOnly = true
duk_ret_t fn_win_rect(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 1)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least one arguments.");
    }
    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    bool clientOnly = true;
    if (n > 1)
    {
        clientOnly = duk_to_boolean(ctx, 1);
    }

    auto r = win_rect(hwnd, clientOnly);
    duk_push_rect(ctx, r);
    return 1;
}

// (pointlike)hwnd, clientOnly = true
duk_ret_t fn_win_position(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 1)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least one arguments.");
    }
    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    bool clientOnly = true;
    if (n > 1)
    {
        clientOnly = duk_to_boolean(ctx, 1);
    }

    auto p = win_position(hwnd, clientOnly);
    duk_push_point(ctx, p);
    return 1;
}

// (sizeLike) hwnd, clientOnly = true
duk_ret_t fn_win_size(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 1)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least one arguments.");
    }
    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    bool clientOnly = true;
    if (n > 1)
    {
        clientOnly = duk_to_boolean(ctx, 1);
    }

    auto s = win_size(hwnd, clientOnly);
    duk_push_size(ctx, s);
    return 1;
}

// (pMat) hwnd, clientOnly=true
// (pMat) hwnd, rectLike={winRect}, clientOnly=true
duk_ret_t fn_win_capture(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 1)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least one arguments.");
    }
    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    cv::Mat *p;

    if (n > 1)
    {
        bool clientOnly = true;
        if (duk_is_object(ctx, 1)) // hwnd, rectLike
        {
            RECT r;
            if (!duk_get_rect(ctx, 1, r))
            {
                return duk_error(ctx, DUK_ERR_TYPE_ERROR, "parse rectobj err.");
            }
            if (n > 2)
            {
                clientOnly = duk_get_boolean(ctx, 2);
            }
            p = capture(hwnd, r, clientOnly);
        }
        else // hwnd, clientOnly
        {
            clientOnly = duk_get_boolean(ctx, 1);
            p = capture(hwnd, clientOnly);
        }
    }
    else
    {
        p = capture(hwnd);
    }

    duk_push_pointer(ctx, p);
    return 1;
}

duk_ret_t fn_win_active(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 1)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least one arguments.");
    }
    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    win_active(hwnd);
    return 0;
}

duk_ret_t fn_win_zorder(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }
    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);
    auto order = duk_get_int(ctx, 1);

    win_zorder(hwnd, order);
    return 0;
}

duk_ret_t fn_win_show(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }
    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);
    auto cmd = duk_get_int(ctx, 1);
    win_show(hwnd, cmd);
    return 0;
}

// mouse_scroll(h, pointLike, step = -120)
duk_ret_t fn_mouse_scroll(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }

    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    POINT p;
    if (!duk_get_point(ctx, 1, p))
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "second argument must be a pointlike object");
    }

    int step = -120;

    if (n > 2)
    {
        step = duk_to_int(ctx, 2);
    }

    mouse_scroll(hwnd, p, step);
    return 0;
}

// mouse_click(h, pointLike, whichBtn = -1)
duk_ret_t fn_mouse_click(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }

    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    SIZE wsize = win_size(hwnd, true);

    POINT p;
    if (!duk_get_point(ctx, 1, p))
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "second argument must be a pointlike object");
    }

    int whichBtn = -1;
    if (n > 2)
    {
        whichBtn = duk_to_int(ctx, 2);
    }

    mouse_click(hwnd, p, whichBtn);
    return 0;
}

// mouse_dbclick(h, pointLike, whichBtn = -1)
duk_ret_t fn_mouse_dbclick(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }

    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    POINT p;
    if (!duk_get_point(ctx, 1, p))
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "second argument must be a pointlike object");
    }
    int whichBtn = -1;
    if (n > 2)
    {
        whichBtn = duk_to_int(ctx, 2);
    }

    mouse_dbclick(hwnd, p, whichBtn);
    return 0;
}

// mouse_move(h, pointLike, whichBtn = -1)
duk_ret_t fn_mouse_move(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }

    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    POINT p;
    if (!duk_get_point(ctx, 1, p))
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "second argument must be a pointlike object");
    }

    int whichBtn = -1;
    if (n > 2)
    {
        whichBtn = duk_to_int(ctx, 2);
    }

    mouse_move(hwnd, p, whichBtn);
    return 0;
}

// mouse_up(h, pointLike, whichBtn = -1)
duk_ret_t fn_mouse_up(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }

    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    POINT p;
    if (!duk_get_point(ctx, 1, p))
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "second argument must be a pointlike object");
    }

    int whichBtn = -1;
    if (n > 2)
    {
        whichBtn = duk_to_int(ctx, 2);
    }

    mouse_up(hwnd, p, whichBtn);
    return 0;
}

// mouse_down(h, pointLike, whichBtn = -1)
duk_ret_t fn_mouse_down(duk_context *ctx)
{

    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }

    HWND hwnd = (HWND)(long long)duk_to_uint(ctx, 0);

    POINT p;
    if (!duk_get_point(ctx, 1, p))
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "second argument must be a pointlike object");
    }

    int whichBtn = -1;
    if (n > 2)
    {
        whichBtn = duk_to_int(ctx, 2);
    }

    mouse_down(hwnd, p, whichBtn);
    return 0;
}

// mat_release(p)
duk_ret_t fn_mat_release(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 1)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least one arguments.");
    }

    cv::Mat *pmat = (cv::Mat *)duk_get_pointer(ctx, 0);
    TUX_DEBUG("mat-release:" << pmat)
    if (pmat == NULL)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "first argument must be a pointer");
    }

    mat_release(pmat);
    return 0;
}

// mat_crop(p, rectLike)
duk_ret_t fn_mat_crop(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least two arguments.");
    }

    cv::Mat *pmat = (cv::Mat *)duk_get_pointer(ctx, 0);
    if (pmat == NULL)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "first argument must be a pointer");
    }

    RECT rect;

    if (!duk_get_rect(ctx, 1, rect))
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "second argument must be a rectlike object");
    }

    cv::Mat *roi = mat_crop(pmat, rect);

    duk_push_pointer(ctx, roi);
    return 1;
}

// mat_find(p, tplP, ...rectLikes)
duk_ret_t fn_mat_find(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 2)
    {
        return 0;
    }
    cv::Mat *src = (cv::Mat *)duk_get_pointer(ctx, 0);
    cv::Mat *tpl = (cv::Mat *)duk_get_pointer(ctx, 1);
    double similar = 0.9;
    std::vector<RECT> rectLikes;
    RECT r;
    double d;
    for (auto i = 2; i < n; ++i)
    {
        if (duk_get_rect(ctx, i, r))
        {
            rectLikes.push_back(r);
        }
        else if (duk_is_number(ctx, i))
        {
            d = duk_get_number(ctx, i);
            if (d > 0 && d <= 1)
            {
                similar = d;
            }
        }
        else
        {
            TUX_DEBUG("param " << i << " ignored")
        }
    }
    if (rectLikes.empty())
    {
        r.left = r.top = r.right = r.bottom = 0;
        rectLikes.push_back(r);
    }

    auto matSize = mat_size(src);
    std::vector<TplMatchResult> results;
    auto tplgray = gray_scale(tpl);
    auto tplSize = mat_size(tplgray);
    for (auto rect : rectLikes)
    {
        cv::Mat *tmat = mat_crop(src, rect);
        cv::Mat *tsrcgray = gray_scale(tmat);
        mat_release(tmat);
        auto tresult = find_tpl(tsrcgray, tplgray, similar);
        mat_release(tsrcgray);
        for (auto &tpoint : tresult)
        {
            tpoint.point.x += rect.left;
            tpoint.point.y += rect.top;
            tpoint.size = tplSize;
            results.push_back(tpoint);
        }
        std::vector<TplMatchResult>().swap(tresult);
    }
    mat_release(tplgray);

    std::sort(results.begin(), results.end(), [](const TplMatchResult &a, const TplMatchResult &b) -> bool {
        return a.score > b.score;
    });

    duk_idx_t arr_idx = duk_push_array(ctx);
    int nn = 0;
    for (const auto &fr : results)
    {
        duk_idx_t obj_idx = duk_push_object(ctx);
        duk_push_number(ctx, fr.score);
        duk_put_prop_string(ctx, obj_idx, "score");
        _duk_assign_point(ctx, obj_idx, fr.point);
        _duk_assign_size(ctx, obj_idx, fr.size);

        duk_put_prop_index(ctx, arr_idx, nn++);
    }
    std::vector<TplMatchResult>().swap(results);

    return 1;
}

// mat_show(p, title = "")
duk_ret_t fn_mat_show(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 1)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least one arguments.");
    }

    cv::Mat *pmat = (cv::Mat *)duk_get_pointer(ctx, 0);
    if (pmat == NULL)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "first argument must be a pointer");
    }

    std::string title = "mat-show";
    if (n > 1)
    {
        title = duk_safe_to_string(ctx, 1);
    }
    cv::imshow(title, *pmat);
    return 0;
}

// wait_key(delay=0): key
duk_ret_t fn_wait_key(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数

    int delay = 0;
    if (n > 0)
    {
        delay = duk_get_uint(ctx, 0);
    }

    int key = cv::waitKey(delay);
    duk_push_int(ctx, key);
    return 1;
}

// mat_make(data, fmt = 'binary,base64')
duk_ret_t fn_mat_make(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数
    if (n < 1)
    {
        return duk_error(ctx, DUK_ERR_TYPE_ERROR, "requires at least one arguments.");
    }
    std::string fmt = "base64";
    if (n > 1)
    {
        fmt = duk_safe_to_string(ctx, 1);
    }

    if (fmt == "base64")
    {
        duk_base64_decode(ctx, 0);
    }
    duk_size_t sz;
    void *pbuf = duk_to_buffer(ctx, 0, &sz);
    cv::Mat *mat = bin2mat((const char *)pbuf, sz);
    duk_push_pointer(ctx, (void *)mat);
    return 1; // 返回值一个参数
}

// mat_read(path)
duk_ret_t fn_mat_read(duk_context *ctx)
{
    int n = duk_get_top(ctx); // 参数个数

    if (n < 1)
    {
        return 0;
    }

    const char *filepath = duk_get_string(ctx, 0);
    if (!file_exists(filepath))
    {
        TUX_DEBUG("file " << filepath << " not found!")
        return 0;
    }

    std::string bin = file_get_contents(filepath);
    cv::Mat *mat = bin2mat(bin.c_str(), bin.length());
    duk_push_pointer(ctx, (void *)mat);
    return 1; // 返回值一个参数
}
