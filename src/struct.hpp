// 数据结构转换的方法
#pragma once

#include <windef.h>
#include <duktape.h>
#include "log.hpp"

void build_rect(const POINT &p, const SIZE &s, LPRECT r)
{
    r->left = p.x;
    r->top = p.y;
    r->right = p.x + s.cx;
    r->bottom = p.y + s.cy;
}

void parse_rect(const RECT &r, LPPOINT p, LPSIZE s)
{
    if (p)
    {
        p->x = r.left;
        p->y = r.top;
    }
    if (s)
    {
        s->cx = r.right - r.left;
        s->cy = r.bottom - r.top;
    }
}

bool crop_rect_normalize(const SIZE &size, LPRECT rect)
{
    SIZE s;
    POINT p;
    parse_rect(*rect, &p, &s);
    if (p.x < 0 || p.x >= size.cx || p.y < 0 || p.y >= size.cy || s.cx < 0 || s.cy < 0)
    {
        return false;
    }

    s.cx == 0 && (s.cx = size.cx);
    s.cy == 0 && (s.cy = size.cy);

    (s.cx > size.cx - p.x) && (s.cx = size.cx - p.x);
    (s.cy > size.cy - p.y) && (s.cy = size.cy - p.y);

    build_rect(p, s, rect);
    return true;
}