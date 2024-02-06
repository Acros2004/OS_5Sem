#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>

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
		HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == INVALID_HANDLE_VALUE) throw "create or open file failed";

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

BOOL delRowFileTxt(LPWSTR fileName, DWORD row) {
	std::cout << "\n\tdelRowFileTxt\n";
	char filepath[20];
	wcstombs(filepath, fileName, 20);
	std::cout << "Path to file: " << filepath << "\n";
	std::cout << "Row to delete: " << row << "\n\n";

	try
	{
		HANDLE hf = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == INVALID_HANDLE_VALUE) {
			CloseHandle(hf);
			throw "create or open file failed";
		}

		DWORD n = NULL;
		char buf[1024];
		BOOL b;

		ZeroMemory(buf, sizeof(buf));
		b = ReadFile(hf, &buf, sizeof(buf), &n, NULL);
		if (!b) {
			CloseHandle(hf);
			throw ("Read file unsuccessful\n");
		}
		CloseHandle(hf);

		HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			throw "Error creating or opening file";
		}
		if (!SetEndOfFile(hFile)) {
			throw "Error setting end of file";
		}
		/*DWORD bytesWritten;
		char nullChar = '\0';
		if (!WriteFile(hFile, &nullChar, sizeof(nullChar), &bytesWritten, NULL)) {
			throw "Error writing null character to file";
		}*/
		CloseHandle(hFile);
		char editedBuf[1024];
		ZeroMemory(editedBuf, sizeof(editedBuf));

		int line = 1;
		int j = 0;
		bool rowFound = false;
		bool addedNewLine = false;
		n = ++n;
		int lastPosNewLine = -1;
		int temp;
		bool flag = false;

		for (int i = 0; i < n; i++) {
			
			if (line != row && buf[i] != '\0') {
				editedBuf[j] = buf[i];
				j++;
			}
			else {
				if (buf[i] != '\0') {
					rowFound = true;
					addedNewLine = true;
				}	
				else if (buf[i] == '\0' && lastPosNewLine != -1 && addedNewLine) {
					editedBuf[lastPosNewLine] = '\0';
					j = lastPosNewLine;
					flag = true;
					break;
				}
			}		
			if (buf[i] == '\n') {
				addedNewLine = false;
				temp = j;
				lastPosNewLine = temp - 2;
				line++;
			}			
		}
		if(!flag)
			editedBuf[j] = '\0';

		HANDLE hAppend = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (!rowFound) {
			n = --n;
			b = WriteFile(hAppend, buf, n, &n, NULL);
			CloseHandle(hAppend);
			throw ("Row was not found\n");
		}

		b = WriteFile(hAppend, editedBuf, j, &n, NULL);
		if (!b) {
			CloseHandle(hAppend);
			throw ("Write file unsuccessful\n");
		}

		char* correctAnsi = ConvertUtf8ToAnsi(editedBuf);
		std::cout << correctAnsi << std::endl;
		CloseHandle(hAppend);
		std::cout << "---------------------------------------------------------\n";
		return true;
	}
	catch (const char* em) {
		std::cout << "!! Error: " << em << " \n";
		std::cout << "---------------------------------------------------------\n";
		return false;
	}
}

int main() {
	setlocale(0, "ru");
	LPWSTR file = (LPWSTR)(L"../OS09_01.txt");
	//LPWSTR file = (LPWSTR)(L"../test.txt");
	printFileText(file);
	delRowFileTxt(file, 1);
	delRowFileTxt(file, 3);
	delRowFileTxt(file, 8);
	delRowFileTxt(file, 10);

	printFileText(file);

	system("pause");
	return 0;
}