#include <Windows.h>
#include <iostream>
DWORD WINAPI ChildThreaId()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 50; i++)
	{
		if (i == 25)
		{
			Sleep(10000);
		}
		std::cout << "PID = " << pid << " , Child Thread TID = " << tid << ":" << i << "\n";
		Sleep(1000);
	}
	return 0;
}
DWORD WINAPI ChildThreaId_2()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 125; i++)
	{
		if (i == 80)
		{
			Sleep(15000);
		}
		std::cout << "PID = " << pid << " , Child Thread TID = " << tid << ":" << i << "\n";
		Sleep(1000);
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	DWORD ChildId_T1 = NULL;
	DWORD ChildId_T2 = NULL;

	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreaId, NULL, 0, &ChildId_T1);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreaId_2, NULL, 0, &ChildId_T2);
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 100; i++)
	{
		if (i == 30)
		{
			Sleep(10000);
		}

		std::cout << "PID = " << pid << " , Parent Thread, TID = " << tid << ":" << i << "\n";
		Sleep(1000);
	}
	WaitForSingleObject(hChild, INFINITE);
	CloseHandle(hChild);

	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild2);
	system("pause");
	return 0;
}