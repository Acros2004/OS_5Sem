#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include "Windows.h"

BOOL printWatchRowFileTxt(LPWSTR fileName, DWORD milliseconds);

int rowCount = 0;

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    LPWSTR filePath = (LPWSTR)(L"../OS09_01.txt");

    printWatchRowFileTxt(filePath, 300000);
}

BOOL printWatchRowFileTxt(LPWSTR fileName, DWORD milliseconds)
{
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();

    LPWSTR watchDirectory = (LPWSTR)(L"C:/Users/nikit/Desktop/univer/3cource1sem/OC/lab9");

    char* cFileName = new char[wcslen(fileName) * sizeof(char) + 1];
    wcstombs(cFileName, fileName, strlen(cFileName));

    try
    {
        HANDLE notificationHandle = FindFirstChangeNotification(watchDirectory, false, FILE_NOTIFY_CHANGE_LAST_WRITE);
        DWORD lastError = GetLastError();

        clock_t startTime = clock();
        clock_t currentTime = clock();

        DWORD waitStatus;

        printf("\nWatch started at timestamp: %d", startTime);

        while (true)
        {
            waitStatus = WaitForSingleObject(notificationHandle, milliseconds);

            switch (waitStatus)
            {
            case WAIT_OBJECT_0:
            {
                if (FindNextChangeNotification(notificationHandle) == FALSE)
                {
                    break;
                }
                else
                {
                    //Sleep(1000);
                    int position = 0;
                    int currentRowCount = 0;

                    HANDLE fileHandle = CreateFile(
                        fileName,
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_ALWAYS,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);

                    if (fileHandle == INVALID_HANDLE_VALUE)
                    {
                        CloseHandle(fileHandle);
                        throw "Failed to open the file";
                    }

                    if (GetFileSizeEx(fileHandle, fileSize))
                    {
                        char* buffer = new char[(fileSize->QuadPart + 1) * sizeof(char)];
                        ZeroMemory(buffer, (fileSize->QuadPart + 1) * sizeof(char));
                        DWORD bytesRead = 0;

                        if (ReadFile(fileHandle, buffer, fileSize->QuadPart, &bytesRead, NULL))
                        {
                            while (buffer[position++] != '\0')
                            {
                                if (buffer[position] == '\n')
                                {
                                    currentRowCount++;
                                }
                            }

                            if (position != 0) {
                                currentRowCount++;
                            }
                        }
                    }

                    if (rowCount != currentRowCount)
                    {
                        printf("\nRow quantity: %d", currentRowCount);
                        rowCount = currentRowCount;
                    }

                    CloseHandle(fileHandle);
                }
            }
            }

            currentTime = clock();

            if (currentTime - startTime > milliseconds)
            {
                break;
            }
        }

        CloseHandle(notificationHandle);

        printf("\nWatch ended at timestamp: %d", currentTime);
    }
    catch (const char* error)
    {
        std::cout << "--- Error:\n" << error << "\n";
        return false;
    }

    return true;
}
