#include <Windows.h>
#include <iostream>

DWORD WINAPI TA()
{
    DWORD pid = GetCurrentProcessId();
    HANDLE hp = GetCurrentProcess();
    DWORD prty = GetPriorityClass(hp);
    HANDLE ht = GetCurrentThread();
    DWORD tid = GetCurrentThreadId();
    DWORD prth = GetThreadPriority(ht);
    DWORD icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
	
    for (int i = 0; i < 1000000; i++) {
        if (i % 1000 == 0) 
        {
            Sleep(200);
            std::cout << "\n№: " << i << "  PID: " << GetCurrentProcessId() << "  TID: " << GetCurrentThreadId();
            std::cout << "  Process priority: ";
            switch (GetPriorityClass(GetCurrentProcess()))
            {
            case IDLE_PRIORITY_CLASS: std::cout << "IDLE_PRIORITY_CLASS"; break;
            case BELOW_NORMAL_PRIORITY_CLASS: std::cout << "BELOW_NORMAL_PRIORITY_CLASS"; break;
            case NORMAL_PRIORITY_CLASS: std::cout << "NORMAL_PRIORITY_CLASS"; break;
            case ABOVE_NORMAL_PRIORITY_CLASS: std::cout << "ABOVE_NORMAL_PRIORITY_CLASS"; break;
            case HIGH_PRIORITY_CLASS: std::cout << "HIGH_PRIORITY_CLASS"; break;
            case REALTIME_PRIORITY_CLASS: std::cout << "REALTIME_PRIORITY_CLASS"; break;
            }
            std::cout << "  Thread priority: ";
            switch (GetThreadPriority(GetCurrentThread()))
            {
            case THREAD_PRIORITY_LOWEST: std::cout << "THREAD_PRIORITY_LOWEST"; break;
            case THREAD_PRIORITY_BELOW_NORMAL: std::cout << "THREAD_PRIORITY_BELOW_NORMAL"; break;
            case THREAD_PRIORITY_NORMAL: std::cout << "THREAD_PRIORITY_NORMAL"; break;
            case THREAD_PRIORITY_ABOVE_NORMAL: std::cout << "THREAD_PRIORITY_ABOVE_NORMAL"; break;
            case THREAD_PRIORITY_HIGHEST: std::cout << "THREAD_PRIORITY_HIGHEST"; break;
            case THREAD_PRIORITY_IDLE: std::cout << "THREAD_PRIORITY_IDLE"; break;
            case THREAD_PRIORITY_TIME_CRITICAL: std::cout << "THREAD_PRIORITY_TIME_CRITICAL"; break;
            }
            std::cout << "  Processor number: " << SetThreadIdealProcessor(GetCurrentThread(), MAXIMUM_PROCESSORS);
        }
    }
    return 0;
}

DWORD SwPriority(int i) {
    switch (i) {
    case 1: return IDLE_PRIORITY_CLASS;
    case 2: return BELOW_NORMAL_PRIORITY_CLASS;
    case 3: return NORMAL_PRIORITY_CLASS;
    case 4: return ABOVE_NORMAL_PRIORITY_CLASS;
    case 5: return HIGH_PRIORITY_CLASS;
    case 6: return REALTIME_PRIORITY_CLASS;
    default: throw "No such priority class";
    }
}

DWORD SwPriorityThread(int i) {
    switch (i) {
    case 1: return THREAD_PRIORITY_LOWEST;
    case 2: return THREAD_PRIORITY_BELOW_NORMAL;
    case 3: return THREAD_PRIORITY_NORMAL;
    case 4: return THREAD_PRIORITY_ABOVE_NORMAL;
    case 5: return THREAD_PRIORITY_HIGHEST;
    case 6: return THREAD_PRIORITY_IDLE;
    default: throw "No such priority class";
    }
}

int main(int argc, char* argv[])
{
    setlocale(NULL, "rus");
    DWORD pa = NULL, sa = NULL;
    if (!GetProcessAffinityMask(GetCurrentProcess(), &pa, &sa)) 
        throw "Process Affinity Mask";
    std::cout << "Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
    std::cout << "System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
    std::cout << std::dec << std::noshowbase << "\n";
	
    int P1, P2, P3, P4;
    if (argc == 4) {
        P1 = atoi(argv[1]);
        P2 = atoi(argv[2]);
        P3 = atoi(argv[3]);
        P4 = atoi(argv[4]);
    }
    else {
        std::cout << "P1 = "; std::cin >> P1;
        std::cout << "P2 = "; std::cin >> P2;
        std::cout << "P3 = "; std::cin >> P3;
        std::cout << "P4 = "; std::cin >> P4;
    }
    

    if (!SetProcessAffinityMask(GetCurrentProcess(), P1)) 
        throw "SetProcessAffinityMask";
    if (!GetProcessAffinityMask(GetCurrentProcess(), &pa, &sa)) 
        throw "Process Affinity Mask";
    std::cout << "\nProcess Affinity Mask: " << std::showbase << std::hex << pa << "\n";
    std::cout << "System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
    std::cout << std::dec << std::noshowbase;
    

    SetPriorityClass(GetCurrentProcess(), SwPriority(P2));

    DWORD childId_T1, childId_T2 = NULL;
    HANDLE hChild1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &childId_T1);
    HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TA, NULL, CREATE_SUSPENDED, &childId_T2);

    SetThreadPriority(hChild1, SwPriorityThread(P3));
    SetThreadPriority(hChild2, SwPriorityThread(P4));

    ResumeThread(hChild1);
    ResumeThread(hChild2);

    WaitForSingleObject(hChild1, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);
    CloseHandle(hChild1);
    CloseHandle(hChild2);
    system("pause");
    return 0;
}