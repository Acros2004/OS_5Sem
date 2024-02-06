#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <fileapi.h>
#include <timezoneapi.h>

char* ConvertUtf8ToAnsi(const char* utf8Str) {

    int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, NULL, 0);
    wchar_t* wideStr = new wchar_t[wideStrLen];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str, -1, wideStr, wideStrLen);

    int ansiLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, NULL, 0, NULL, NULL);
    char* ansiStr = new char[ansiLen];
    WideCharToMultiByte(CP_ACP, 0, wideStr, -1, ansiStr, ansiLen, NULL, NULL);

    delete[] wideStr;

    return ansiStr;
}

BOOL printFileText(LPWSTR fileName) {
    try {
        std::cout << "\n\tprintFileText\n";
        HANDLE hf = CreateFile( 
            fileName, 
            GENERIC_READ, 
            NULL, 
            NULL,
            OPEN_ALWAYS, 
            FILE_ATTRIBUTE_NORMAL,
            NULL 
        );
        if (hf == INVALID_HANDLE_VALUE) {
            CloseHandle(hf);
            throw "create or open file failed";
        }

        DWORD  n = NULL;
        char buf[1024];

        ZeroMemory(buf, sizeof(buf));
        BOOL b = ReadFile(hf, &buf, 1024, &n, NULL); 
        if (!b) throw "read file failed";
        
        char* correctAnsi = ConvertUtf8ToAnsi(buf);

        std::cout << correctAnsi << std::endl;
        CloseHandle(hf);
        return true;
    }
    catch (const char* em) {
        std::cout << "error:" << em << std::endl;
        return false;
    }
}

BOOL printFileInfo(LPWSTR fileName) {
    try {
        std::cout << "\tprintFileInfo\n";
        HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hf == INVALID_HANDLE_VALUE) throw "open file failed";

        char filepath[20];
        wcstombs(filepath, fileName, 20); 
        std::cout << "name: " << filepath << "\n";
        std::cout << "type: " << GetFileType(hf) << "\n";
        std::cout << "size: " << GetFileSize(hf, NULL) << " bytes\n";

        BY_HANDLE_FILE_INFORMATION info; 
        ZeroMemory(&info, sizeof(BY_HANDLE_FILE_INFORMATION));
        GetFileInformationByHandle(hf, &info);
        SYSTEMTIME time;

        if (!FileTimeToSystemTime(&info.ftCreationTime, &time))
            throw "FileTimeToSystemTime error";
        SystemTimeToTzSpecificLocalTime(NULL, &time, &time);
        std::cout << "creation time: " << time.wDay << "." << time.wMonth << "." << time.wYear << " " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << "\n";

        if (!FileTimeToSystemTime(&info.ftLastWriteTime, &time))
            throw "FileTimeToSystemTime error";

        SystemTimeToTzSpecificLocalTime(NULL, &time, &time);
        std::cout << "modified time: " << time.wDay << "." << time.wMonth << "." << time.wYear << " " << time.wHour << ":" << time.wMinute << ":" << time.wSecond << "\n";

        CloseHandle(hf);
        return true;
    }
    catch (const char* em) {
        std::cout << "error:" << em << "\n";
        return false;
    }
}

int main()
{
    setlocale(0, "ru");
    LPWSTR file = (LPWSTR)(L"..\\OS09_01.txt");

    printFileInfo(file);
    printFileText(file);
}