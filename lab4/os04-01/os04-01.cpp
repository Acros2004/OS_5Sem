
#include <Windows.h>
#include <iostream>

int main()
{
	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();


	for (unsigned long long i = 0; i < MAXULONGLONG; i++)
	{
		std::cout << "PID = " << pid << ",  TID = " << tid << ":" << i << "\n";
		Sleep(1000);
	}
	system("pause");
	return 0;
}
// (get-process os04-01).Threads