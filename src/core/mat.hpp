#pragma once

#include <windef.h>
#include <opencv2/opencv.hpp>
#include "../struct.hpp"

void mat_release(cv::Mat *&mat);
SIZE mat_size(cv::Mat *&mat);
cv::Mat *mat_crop(cv::Mat *mat, RECT rect);
cv::Mat *bin2mat(const char *, size_t size);

struct TplMatchResult
{
    float score;
    POINT point;
    TplMatchResult(float score, int x, int y)
    {
        this->score = score;
        this->point.x = x;
        this->point.y = y;
    }
};

std::vector<TplMatchResult> find_tpl(cv::Mat *src, cv::Mat *tpl, double similar = 0.9);
cv::Mat *gray_scale(cv::Mat *src);

void mat_release(cv::Mat *&mat)
{
    if (mat != NULL)
    {
        mat->release();
        delete mat;
        mat = NULL;
    }
}

SIZE mat_size(cv::Mat *&mat)
{
    auto s = mat->size();
    SIZE size;
    size.cx = s.width;
    size.cy = s.height;
    return size;
}

cv::Mat *mat_crop(cv::Mat *mat, RECT rect)
{
    auto size = mat_size(mat);

    crop_rect_normalize(size, &rect);
    POINT p;
    SIZE s;
    parse_rect(rect, &p, &s);

    cv::Rect crect = cv::Rect(p.x, p.y, s.cx, s.cy);
    cv::Mat region(*mat, crect);
    cv::Mat *roi = new cv::Mat;
    region.copyTo(*roi);
    region.release();
    return roi;
}

cv::Mat *bin2mat(const char *c, size_t size)
{
    std::vector<uchar> buf(c, c + size);
    cv::Mat mat = cv::imdecode(buf, cv::IMREAD_COLOR);
    cv::Mat *pMat = new cv::Mat;
    mat.copyTo(*pMat);
    mat.release();
    return pMat;
}

std::vector<TplMatchResult> find_tpl(cv::Mat *src, cv::Mat *tpl, double similar)
{
    cv::Mat matched = cv::Mat();
    matchTemplate(*src, *tpl, matched, cv::TM_CCOEFF_NORMED);

    cv::threshold(matched, matched, similar, 1., cv::THRESH_TOZERO);

    std::vector<TplMatchResult> results;
    while (true)
    {
        double maxValue;
        cv::Point maxLoc;
        minMaxLoc(matched, NULL, &maxValue, NULL, &maxLoc);

        if (maxValue < similar)
        {
            break;
        }
        cv::floodFill(matched, maxLoc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));
        results.push_back(TplMatchResult(maxValue, maxLoc.x, maxLoc.y));
    }
    matched.release();
    return results;
}

cv::Mat *gray_scale(cv::Mat *src)
{
    int channels = src->channels();
    auto gray = new cv::Mat;
    auto tmp = (cv::Mat)cv::Mat::zeros(src->size(), CV_8UC1);
    tmp.copyTo(*gray);
    tmp.release();
    if (channels == 4)
    {
        cvtColor(*src, *gray, cv::COLOR_BGRA2GRAY);
    }
    else if (channels == 3)
    {
        cvtColor(*src, *gray, cv::COLOR_BGR2GRAY);
    }
    else if (channels == 2)
    {
        cvtColor(*src, *gray, cv::COLOR_BGR5652GRAY);
    }
    else
    {
        src->copyTo(*gray);
    }
    return gray;
}
