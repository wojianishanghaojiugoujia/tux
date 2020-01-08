#pragma once
// 窗口相关函数

#include <windows.h>
#include "../struct.hpp"

inline void win_active(HWND h);
inline void win_zorder(HWND h, int insertAfter);
inline void win_show(HWND h, int cmdShow);
RECT win_rect(HWND h, bool clientOnly = true);
SIZE win_size(HWND h, bool clientOnly = true);
POINT win_position(HWND h, bool clientOnly = true);
void win_resize(HWND h, const SIZE &size, bool clientOnly = true);         // 重置窗口大小
void win_set_position(HWND h, const POINT &point, bool clientOnly = true); // 设置窗口位置

inline void win_active(HWND h)
{
    SwitchToThisWindow(h, TRUE);
}

RECT win_rect(HWND h, bool clientOnly)
{
    RECT rect;
    if (clientOnly)
    {
        GetClientRect(h, &rect);
        POINT p;
        p.x = p.y = 0;
        ClientToScreen(h, &p);
        SIZE s;

        parse_rect(rect, NULL, &s);
        build_rect(p, s, &rect);
        return rect;
    }
    else
    {
        GetWindowRect(h, &rect);
        return rect;
    }
}

SIZE win_size(HWND h, bool clientOnly)
{
    RECT rect = win_rect(h, clientOnly);
    SIZE s;
    parse_rect(rect, NULL, &s);
    return s;
}

POINT win_position(HWND h, bool clientOnly)
{
    RECT rect = win_rect(h, clientOnly);
    POINT p;
    parse_rect(rect, &p, NULL);
    return p;
}

// 重置窗口大小
void win_resize(HWND h, const SIZE &size, bool clientOnly)
{
    int w = size.cx;
    int hh = size.cy;
    if (clientOnly)
    {
        auto ws = win_size(h, false);
        auto cs = win_size(h, true);
        w += (ws.cx - cs.cx);
        hh += (ws.cy - cs.cy);
    }
    SetWindowPos(h, 0, 0, 0, w, hh, SWP_NOZORDER | SWP_NOMOVE);
}

// 设置窗口位置
void win_set_position(HWND h, const POINT &point, bool clientOnly)
{
    auto x = point.x;
    auto y = point.y;
    if (clientOnly)
    {
        auto wp = win_position(h, false);
        auto cp = win_position(h, true);
        x += (wp.x - cp.x);
        y += (wp.y - cp.y);
    }
    SetWindowPos(h, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

// HWND_TOP=0  HWND_BOTTOM=1  HWND_TOPMOST=-1  HWND_NOTOPMOST=-2
inline void win_zorder(HWND h, int insertAfter)
{
    SetWindowPos(h, (HWND)(long long)insertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

inline void win_show(HWND h, int cmdShow)
{
    ShowWindow(h, cmdShow);
}
