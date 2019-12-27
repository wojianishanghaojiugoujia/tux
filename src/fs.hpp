// 文件读写跟文件io
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>

#include "log.hpp"

// 文件是否存在
bool file_exists(const char *filename)
{
    return (access(filename, 0) == 0);
}

std::basic_string<char> file_get_contents(const char *filename)
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
