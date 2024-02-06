#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	cout << "====================  OS03_02  ====================\n\n";

	LPCWSTR OS03_02_1 = L"C:\\Users\\nikit\\Desktop\\univer\\3cource1sem\\OC\\lab3\\x64\\Debug\\OS03_02_1.exe";
	LPCWSTR OS03_02_2 = L"C:\\Users\\nikit\\Desktop\\univer\\3cource1sem\\OC\\lab3\\x64\\Debug\\OS03_02_2.exe";
	STARTUPINFO si1;			
	STARTUPINFO si2;								
	PROCESS_INFORMATION pi1;						
	PROCESS_INFORMATION pi2;
	ZeroMemory(&si1, sizeof(STARTUPINFO));			
	ZeroMemory(&si2, sizeof(STARTUPINFO));			
	si1.cb = sizeof(STARTUPINFO);					
	si1.dwFlags = STARTF_USEFILLATTRIBUTE;			
	si1.dwFillAttribute = (DWORD)FOREGROUND_GREEN;	
	si1.lpReserved = NULL;							
	si2.cb = sizeof(STARTUPINFO);					
	si2.dwFlags = STARTF_USEFILLATTRIBUTE;			
	si2.dwFillAttribute = (DWORD)FOREGROUND_RED;
	si1.lpReserved = NULL;					


	if (CreateProcess(	
		OS03_02_1,			// lpApplicationName:	имя исполняемого модуля
		NULL,				// lpCommandLine:		параметры коммандной строки
		NULL,				// lpProcessAttributes: может ли возвращаемый дескриптор быть унаследован дочерними процессами (null - нельзя наследовать)
		NULL,				// lpThreadAttributes:	может ли возвращаемый дескриптор быть унаследован дочерними потоками (null - нельзя наследовать)
		FALSE,				// bInheritHandles:		true - каждый возвращаемый дескриптор наследуется дочерним процессом; false - не наследуется
		CREATE_NEW_CONSOLE, // dwCreationFlags:		флаги, управляющие приоритетом и параметрами процесса; конкретно этот создает новый инстанс консоли
		NULL,				// lpEnvironment:		блок конфигурации нового процесса (пары ключ-значение); если null, то конфигурация наследуется от родителя
		NULL,				// lpCurrentDirectory:	полный путь дочернего процесса; если null, то процесс создается в каталоге родительского процесса
		&si1,				// lpStartupInfo:		структура STARTUPINFO (внешний вид окна)
		&pi1))				// lpProcessInfo:		структура PROCESS_INFORMATION (дескрипторы процесса и первичного потока)
		cout << "[OK] Process OS03_02_1 was created.\n";
	else cout << "[ERROR] Process OS03_02_1 was not created.\n";


	if (CreateProcess(OS03_02_2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
		cout << "[OK] Process OS03_02_2 was created.\n\n";
	else cout << "[ERROR] Process OS03_02_2 was not created.\n\n";


	for (short i = 1; i <= 100; ++i)
	{
		cout << i << ". PID = " << GetCurrentProcessId() << "\n";
		Sleep(1000);
	}


	WaitForSingleObject(pi1.hProcess, INFINITE);	
	WaitForSingleObject(pi2.hProcess, INFINITE);	
	CloseHandle(pi1.hThread);	
	CloseHandle(pi2.hThread);		
	CloseHandle(pi1.hProcess);	
	CloseHandle(pi2.hProcess);
	return 0;
}


// CMD: tasklist /FI "IMAGENAME eq OS03_02*"