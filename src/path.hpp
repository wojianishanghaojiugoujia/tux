#pragma once
#include <string>
#include <sstream>
#include <direct.h>
#include <windows.h>

#ifdef _WIN32
#define DIRECTORY_SEPARATOR "\\"
#else
#define DIRECTORY_SEPARATOR "/"
#endif

// 获取绝对路径
std::string realpath(const std::string &pathname)
{
    char abs_path_buff[PATH_MAX];

    //获取文件路径, 填充到abs_path_buff
    //realpath函数返回: null表示获取失败; 否则返回指向abs_path_buff的指针
    _fullpath(abs_path_buff, pathname.c_str(), 1024);
    return abs_path_buff;
}

// 截取路径的目录名
std::string dirname(std::string pathname)
{
    pathname.erase(pathname.find_last_not_of("\\/") + 1);
    size_t pos = pathname.find_last_of("\\/");
    return (std::string::npos == pos)
               ? ""
               : pathname.substr(0, pos);
}

// 获取程序名
std::string filename(std::string pathname)
{
    pathname.erase(pathname.find_last_not_of("\\/") + 1);
    size_t pos = pathname.find_last_of("\\/");
    return (std::string::npos == pos)
               ? pathname
               : pathname.substr(pos + 1);
}

// 当前工作目录
std::string cwd()
{
    char *path;
    path = getcwd(NULL, 0);
    return path;
}

// 入口程序
std::string entry()
{
    TCHAR exeFullPath[MAX_PATH + 1];
    GetModuleFileName(NULL, exeFullPath, MAX_PATH);
    std::stringstream ss;
    ss << exeFullPath;
    std::string path;
    ss >> path;
    return path;
}

// 入口程序目录
std::string entry_root()
{
    return dirname(entry());
}
