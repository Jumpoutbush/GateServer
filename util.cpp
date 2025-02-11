#include "util.h"
#include <fstream>

namespace dain {

    DWORD GetThreadId() {
        return GetCurrentThreadId();
    }
    uint32_t GetFiberId()
    {
        return 0;
    }

    void FileTimeToTimeval(const FILETIME* fileTime, timeval* timeVal)
    {
        {
            ULARGE_INTEGER uli;
            uli.LowPart = fileTime->dwLowDateTime;
            uli.HighPart = fileTime->dwHighDateTime;

            // 1601年1月1日到1970年1月1日的100纳秒间隔数
            const ULARGE_INTEGER epochDiff = { 0x019DB1DED53E8000, 0x00000000 };

            // 减去差值得到从1970年1月1日开始的100纳秒间隔数
            uli.QuadPart -= epochDiff.QuadPart;

            // 转换为秒和微秒
            timeVal->tv_sec = static_cast<long>(uli.QuadPart / 10000000);
            timeVal->tv_usec = static_cast<long>((uli.QuadPart % 10000000) / 10);
        }
    }
    uint64_t GetCurrentMS() {
        FILETIME fileTime;
        struct timeval tv;
        // gettimeofday(&tv, NULL);
        GetSystemTimeAsFileTime(&fileTime);
        FileTimeToTimeval(&fileTime, &tv);
        
        return tv.tv_sec * 1000ul + tv.tv_usec / 1000;
    }
    uint64_t GetCurrentUS() {
        FILETIME fileTime;
        struct timeval tv;
        // gettimeofday(&tv, NULL);
        GetSystemTimeAsFileTime(&fileTime);
        FileTimeToTimeval(&fileTime, &tv);
        return tv.tv_sec * 1000 * 1000ul + tv.tv_usec;
    }

    uint64_t GetElapsedMS()
    {
        return 0;
    }


    // FSUtil

    static int __lstat(const char* file, struct _stat32* st = nullptr) {
        struct _stat32 lst;
        int ret = _stat32(file, &lst);
        if (st) {
            *st = lst;
        }
        return ret;
    }

    static int __mkdir(const char* dirname) {
        if (_access(dirname, 0) == 0) {
            return 0;
        }
        return _mkdir(dirname);
    }




    bool FSUtil::Mkdir(const std::string& dirname)
    {
        if (__lstat(dirname.c_str()) == 0) {
            return true;
        }
        char* path = _strdup(dirname.c_str());
        char* ptr = strchr(path + 1, '/');
        do {
            for (; ptr; *ptr = '/', ptr = strchr(ptr + 1, '/')) {
                *ptr = '\0';
                if (__mkdir(path) != 0) {
                    break;
                }
            }
            if (ptr != nullptr) {
                break;
            }
            else if (__mkdir(path) != 0) {
                break;
            }
            free(path);
            return true;
        } while (0);
        free(path);
        return false;
    }

    std::string FSUtil::Dirname(const std::string& filename)
    {
        if (filename.empty()) {
            return ".";
        }
        auto pos = filename.rfind('\\');
        if (pos == 0) {
            return "\\";
        }
        else if (pos == std::string::npos) {
            return ".";
        }
        else {
            return filename.substr(0, pos);
        }
    }

    bool FSUtil::OpenForWrite(std::ofstream& ofs, const std::string& filename
        , std::ios_base::openmode mode) {
        ofs.open(filename.c_str(), mode);
        if (!ofs.is_open()) {
            std::string dir = Dirname(filename);
            Mkdir(dir);
            ofs.open(filename.c_str(), mode);
        }
        return ofs.is_open();
    }






}