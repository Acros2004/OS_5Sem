#include <iostream>
#include <windows.h>
#include <process.h>

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

int main(int argc, char* argv[])
{
    
    int P1, P2, P3;
    LPCWSTR an = L"C:\\Users\\nikit\\Desktop\\univer\\3cource1sem\\OC\\lab5\\os5_1\\Debug\\os5_2x.exe";
    STARTUPINFO si,si1;
    PROCESS_INFORMATION pi, pi1;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&si1, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si1.cb = sizeof(STARTUPINFO);

    try {
        DWORD pa = NULL, sa = NULL;
        if (!GetProcessAffinityMask(GetCurrentProcess(), &pa, &sa)) throw "Process Affinity Mask";
        std::cout << "Process Affinity Mask: " << std::showbase << std::hex << pa << "\n";
        std::cout << "System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
        std::cout << std::dec << std::noshowbase << "\n";
        if (argc == 4) {
            P1 = atoi(argv[1]);
            P2 = atoi(argv[2]);
            P3 = atoi(argv[3]);
        }
        else {
            std::cout << "P1 = "; std::cin >> P1;
            std::cout << "P2 = "; std::cin >> P2;
            std::cout << "P3 = "; std::cin >> P3;
        }
        
		
        if (!SetProcessAffinityMask(GetCurrentProcess(), P1))
            throw "SetProcessAffinityMask";
        if (!GetProcessAffinityMask(GetCurrentProcess(), &pa, &sa)) 
            throw "Process Affinity Mask";
        std::cout << "\nProcess Affinity Mask: " << std::showbase << std::hex << pa << "\n";
        std::cout << "System Affinity Mask: " << std::showbase << std::hex << sa << "\n";
        std::cout << std::dec << std::noshowbase;

        if (!CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | SwPriority(P2), NULL, NULL, &si, &pi))  
            throw "---Proc 1 wasn't created\n";
        if (!CreateProcess(an, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | SwPriority(P3), NULL, NULL, &si1, &pi1))  
            throw "---Proc 2 wasn't created\n";
    
        WaitForSingleObject(pi.hProcess, INFINITE);
        WaitForSingleObject(pi1.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi1.hProcess);
    }
    catch (const std::exception& a)
    {
        std::cout << "Error: " << a.what() << "\n";
    }
    catch (const char* msg)
    {
        std::cout << "Error: " << msg;
    }
    system("pause");
    return 0;
}