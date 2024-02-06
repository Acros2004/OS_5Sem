#include <Windows.h>
#include <iostream>

int main()
{
    setlocale(NULL, "rus");
    for (int i = 0; i < 1000000; i++) {
        if (i % 1000 == 0) 
        {
            Sleep(200);
            std::cout << "№: " << i << std::endl;
            std::cout << "PID: " << GetCurrentProcessId() << "\tTID: " << GetCurrentThreadId() << std::endl;
            std::cout << "Process priority: ";
            switch (GetPriorityClass(GetCurrentProcess()))
            {
            case IDLE_PRIORITY_CLASS: std::cout << "IDLE_PRIORITY_CLASS" << std::endl; break;
            case BELOW_NORMAL_PRIORITY_CLASS: std::cout << "BELOW_NORMAL_PRIORITY_CLASS" << std::endl; break;
            case NORMAL_PRIORITY_CLASS: std::cout << "NORMAL_PRIORITY_CLASS" << std::endl; break;
            case ABOVE_NORMAL_PRIORITY_CLASS: std::cout << "ABOVE_NORMAL_PRIORITY_CLASS" << std::endl; break;
            case HIGH_PRIORITY_CLASS: std::cout << "HIGH_PRIORITY_CLASS" << std::endl; break;
            case REALTIME_PRIORITY_CLASS: std::cout << "REALTIME_PRIORITY_CLASS" << std::endl; break;
            }
            std::cout << "Thread priority: ";
            switch (GetThreadPriority(GetCurrentThread()))
            {
            case THREAD_PRIORITY_LOWEST: std::cout << "THREAD_PRIORITY_LOWEST" << std::endl; break;
            case THREAD_PRIORITY_BELOW_NORMAL: std::cout << "THREAD_PRIORITY_BELOW_NORMAL" << std::endl; break;
            case THREAD_PRIORITY_NORMAL: std::cout << "THREAD_PRIORITY_NORMAL" << std::endl; break;
            case THREAD_PRIORITY_ABOVE_NORMAL: std::cout << "THREAD_PRIORITY_ABOVE_NORMAL" << std::endl; break;
            case THREAD_PRIORITY_HIGHEST: std::cout << "THREAD_PRIORITY_HIGHEST" << std::endl; break;
            case THREAD_PRIORITY_IDLE: std::cout << "THREAD_PRIORITY_IDLE" << std::endl; break;
            case THREAD_PRIORITY_TIME_CRITICAL: std::cout << "THREAD_PRIORITY_TIME_CRITICAL" << std::endl; break;
            }
            std::cout << "Processor number: " << SetThreadIdealProcessor(GetCurrentThread(), MAXIMUM_PROCESSORS) << std::endl << std::endl;
        }
    }
    system("pause");
    return 0;
}