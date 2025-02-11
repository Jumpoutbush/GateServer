#pragma once
#ifndef __SYLAR_UTIL_H__
#define __SYLAR_UTIL_H__
#include <boost/lexical_cast.hpp>
#include <direct.h>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <json/json.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <thread>
#include <time.h>
#include <vector>
#include <Windows.h>

namespace dain {

    DWORD GetThreadId();
    uint32_t GetFiberId();


    // Time ms
    uint64_t GetCurrentMS();
    uint64_t GetCurrentUS();

    //获取当前启动的毫秒数
    uint64_t GetElapsedMS();

    // 将FILETIME转换为timeval结构体
    void FileTimeToTimeval(const FILETIME* fileTime, struct timeval* timeVal);

    class FSUtil {
    public:
        //static void ListAllFile(std::vector<std::string>& files
        //    , const std::string& path
        //    , const std::string& subfix);
        static bool Mkdir(const std::string& dirname);
        //static bool IsRunningPidfile(const std::string& pidfile);
        //static bool Rm(const std::string& path);
        //static bool Mv(const std::string& from, const std::string& to);
        //static bool Realpath(const std::string& path, std::string& rpath);
        //static bool Symlink(const std::string& frm, const std::string& to);
        //static bool Unlink(const std::string& filename, bool exist = false);
        static std::string Dirname(const std::string& filename);
        //static std::string Basename(const std::string& filename);
        //static bool OpenForRead(std::ifstream& ifs, const std::string& filename
        //    , std::ios_base::openmode mode);
        static bool OpenForWrite(std::ofstream& ofs, const std::string& filename
            , std::ios_base::openmode mode);
    };
}
#endif
