#pragma once

#include <windows.h>
#include <opencv2/opencv.hpp>

#include "win.hpp"

inline cv::Mat *capture(HWND h, bool clientOnly = true);
cv::Mat *capture(HWND h, RECT rect, bool clientOnly = true);

inline cv::Mat *capture(HWND h, bool clientOnly)
{
    RECT rect;
    return capture(h, rect, clientOnly);
}

cv::Mat *capture(HWND h, RECT rect, bool clientOnly)
{
    HDC hDC = clientOnly ? GetDC(h) : GetWindowDC(h);
    auto hSize = win_size(h, clientOnly);
    if (!crop_rect_normalize(hSize, &rect))
    {
        TUX_ERROR("rectangle is out of size")
        return NULL;
    }
    POINT p;
    SIZE s;
    parse_rect(rect, &p, &s);

    HDC hMemDC = CreateCompatibleDC(NULL);
    HBITMAP hBmp = CreateCompatibleBitmap(hDC, s.cx, s.cy);
    HGDIOBJ oldBmp = SelectObject(hMemDC, hBmp);

    BitBlt(hMemDC, 0, 0, s.cx, s.cy, hDC, p.x, p.y, SRCCOPY);

    cv::Mat *mat = new cv::Mat(s.cy, s.cx, CV_8UC4); // 这里返回的是 bgra
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER); //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    bi.biWidth = s.cx;
    bi.biHeight = -s.cy; //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
    GetDIBits(hMemDC, hBmp, 0, (UINT)s.cy, mat->data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

    SelectObject(hMemDC, oldBmp);
    DeleteDC(hMemDC);
    ReleaseDC(h, hDC);
    DeleteObject(hBmp);

    return mat;
}