#pragma once
#include <windows.h>

inline int _wm_down_btn(int btn);
inline int _wm_up_btn(int btn);
inline int _mk_btn(int btn);

HWND hwnd_from_mouse();
void mouse_down(HWND h, const POINT &point, int btn = -1);
void mouse_move(HWND h, const POINT &point, int btn = -1);
void mouse_up(HWND h, const POINT &point, int btn = -1);
void mouse_click(HWND h, const POINT &point, int btn = -1);
void mouse_dbclick(HWND h, const POINT &point, int btn = -1);
void mouse_scroll(HWND h, const POINT &point, int step = -120); // -1 向下滚动  1 向上滚动 step表示滚动距离?

HWND hwnd_from_mouse()
{
    POINT p;
    GetCursorPos(&p);
    return WindowFromPoint(p);
}

void mouse_down(HWND h, const POINT &point, int btn)
{
    auto tmp = MAKELONG(point.x, point.y);
    SendMessage(h, WM_NCHITTEST, 0, tmp);
    auto k1 = _wm_down_btn(btn);
    SendMessage(h, WM_SETCURSOR, (long long)h, MAKELONG(HTCLIENT, k1));
    PostMessage(h, k1, _mk_btn(btn), tmp);
}

void mouse_move(HWND h, const POINT &point, int btn)
{
    auto tmp = MAKELONG(point.x, point.y);
    PostMessage(h, WM_MOUSEMOVE, _mk_btn(btn), tmp);
}

void mouse_up(HWND h, const POINT &point, int btn)
{
    auto tmp = MAKELONG(point.x, point.y);
    PostMessage(h, _wm_up_btn(btn), 0, tmp);
}

void mouse_click(HWND h, const POINT &point, int btn)
{
    mouse_move(h, point, btn);
    mouse_down(h, point, btn);
    mouse_up(h, point, btn);
}

void mouse_dbclick(HWND h, const POINT &point, int btn)
{
    mouse_click(h, point, btn);
    mouse_click(h, point, btn);
}

void mouse_scroll(HWND h, const POINT &point, int step)
{
    mouse_move(h, point, -1);
    auto tmp = MAKELONG(point.x, point.y);
    PostMessage(h, WM_MOUSEWHEEL, MAKELONG(0, step), tmp);
    SendMessage(h, WM_NCHITTEST, 0, tmp);
}

int _wm_down_btn(int btn)
{
    return btn == -1 ? WM_LBUTTONDOWN : (btn == 0 ? WM_MBUTTONDOWN : WM_RBUTTONDOWN);
}

int _wm_up_btn(int btn)
{
    return btn == -1 ? WM_LBUTTONUP : (btn == 0 ? WM_MBUTTONUP : WM_RBUTTONUP);
}

int _mk_btn(int btn)
{
    return btn == -1 ? MK_LBUTTON : (btn == 0 ? MK_MBUTTON : MK_RBUTTON);
}