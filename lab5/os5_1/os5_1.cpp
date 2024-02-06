#include <Windows.h>
#include <iostream>
#include <process.h>
#include <bitset>

int main()
{
    setlocale(NULL, "rus");
    try
    {
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
        SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);
        DWORD pa = NULL, sa = NULL;
        //if (!GetProcessAffinityMask(GetCurrentProcess(), &pa, &sa)) throw "GetProcessAffinityMask";
            //throw "SetProcessAffinityMask";
            DWORD desiredMask = 0; 
            desiredMask |= (1 << 2); 
            desiredMask |= (1 << 3); 
            desiredMask |= (1 << 1); 
            SetProcessAffinityMask(GetCurrentProcess(), 5);
        if (!GetProcessAffinityMask(GetCurrentProcess(), &pa, &sa))
            throw "Process Affinity Mask";
        int counterOfProcess = 0;
        int numBits = sizeof(pa) * 8;

        for (int i = 0; i < numBits; i++) {
            if (pa & (1U << i)) { 
                counterOfProcess++;
            }
        }
        std::cout << "Process affinity mask: " << std::showbase << std::hex << pa << std::endl;
        std::cout << "System affinity mask: " << std::showbase << std::hex << sa << std::endl;
        std::cout << "Number of processors available to the process: " << std::noshowbase << counterOfProcess << std::endl;
        std::cout << "Preferred processor for the thread: " << SetThreadIdealProcessor(GetCurrentThread(), MAXIMUM_PROCESSORS) << std::endl;
    }
    catch (char* msg) { std::cout << "Error: " << msg << std::endl; }
    system("pause");
    return 0;
}