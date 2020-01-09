// 文件读写跟文件io
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "log.hpp"

// 文件是否存在
bool file_exists(std::string filename)
{
    auto fp = fopen(filename.c_str(), "r");
    if (fp == NULL)
    {
        return false;
    }
    fclose(fp);
    return true;
}

// 目录是否存在
bool dir_exists(std::string pathname)
{
    return (access(pathname.c_str(), 0) == 0) && !file_exists(pathname);
}

// 写内容
bool file_put_contents(std::string filename, std::string data, std::ios_base::openmode mode)
{
    auto base_mode = std::ios::out;
    std::ofstream file(filename, base_mode | mode);
    if (!file.is_open())
    {
        file.close();
        TUX_ERROR("open file(" << filename << ") err!")
        return false;
    }

    file << data;
    file.close();
    return true;
}

// 写内容
bool file_put_contents(std::string filename, std::string data)
{
    return file_put_contents(filename, data, std::ios::trunc);
}

// 获取文件内容
std::basic_string<char> file_get_contents(std::string filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        file.close();
        TUX_ERROR("read file(" << filename << ") err!")
        return (char *)"";
    }
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    char *buf = new char[size];
    file.seekg(0, std::ios::beg);
    file.read((char *)buf, size);
    file.close();

    auto res = std::basic_string<char>(buf, size);
    delete[] buf;
    return res;
}
