#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <fileapi.h>

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
		HANDLE hf = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//совместное чтение и запись
		if (hf == INVALID_HANDLE_VALUE) throw "create or open file failed";

		DWORD  n = NULL;
		char buf[1024];

		ZeroMemory(buf, sizeof(buf));
		BOOL b = ReadFile(hf, &buf, 1024, &n, NULL);
		if (!b) throw "read file failed";
		char* correct = ConvertUtf8ToAnsi(buf);
		std::cout << correct << std::endl;
		CloseHandle(hf);
		return true;
	}
	catch (const char* em) {
		std::cout << "error:" << em << std::endl;
		return false;
	}
}

BOOL insRowFileTxt(LPWSTR fileName, LPWSTR str, DWORD row) {
	char filepath[20];
	wcstombs(filepath, fileName, 20);
	char stringToInsert[50];
	wcstombs(stringToInsert, str, 50);

	std::cout << "Path to file: " << filepath << "\n";
	std::cout << "String to insert: " << stringToInsert << "\n";
	std::cout << "Row to insert: " << row << "\n\n";

	try
	{
		HANDLE hf = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

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
			std::cout << "Read file unsuccessfully\n";
			CloseHandle(hf);
			return false;
		}
		CloseHandle(hf);

		HANDLE hAppend = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		char editedBuf[1024];
		ZeroMemory(editedBuf, sizeof(editedBuf));

		int line = 1;
		int j = 0;
		int k = 0;
		bool newLineDetected = false;
		bool beforeNewLine = false;
		bool emptyFile = false;
		bool inserted = false;
		bool lastInserted = false;
		bool correntInserted = false;
		for (int i = 0; i < n + 1; i++) {
			if (row == 1)
				row = 0;
			if (row == -1 && !lastInserted) {
				if (buf[i] == '\0') {
					if (buf[i - 1] == '\n') {
						newLineDetected = true;
					}
					for (int k = 0; k < sizeof(stringToInsert); k++) {
						if (!newLineDetected && !beforeNewLine && j > 0) {
							editedBuf[j] = '\r'; //	возврат каретки
							j++;
							editedBuf[j] = '\n'; //перевод строки
							j++;
							beforeNewLine = true;
						}
						editedBuf[j] = stringToInsert[k];
						j++;
						if (stringToInsert[k + 1] == '\0') {
							editedBuf[j] = '\0';
							lastInserted = true;
							break;
						}
							
					}

				}
				else {
					editedBuf[j] = buf[i];
					j++;
				}
			}
			else if (row == 0 && !inserted) {
				if (buf[i] == '\0') {
					emptyFile = true;
				}
				for (int k = 0; k < sizeof(stringToInsert); k++) {
					editedBuf[j] = stringToInsert[k];
					j++;
					if (stringToInsert[k + 1] == '\0') {
						if(emptyFile)
							editedBuf[j] = '\0';
						else {
							editedBuf[j] = '\r';
							j++;
							editedBuf[j] = '\n';
							j++;
						}
						inserted = true;
						i--;
						break;
					}

				}
			}
			else if(inserted){
				editedBuf[j] = buf[i];
				j++;
			}
			else if (!inserted && !lastInserted && !correntInserted) {
				if (buf[i] == '\n') {
					editedBuf[j] = buf[i];
					j++;
					line++;
				}
				if (line != row) {
					if (buf[i + 1] == '\0') {
						row = -1;
					}
					if (buf[i] != '\n') {
						editedBuf[j] = buf[i];
						j++;
					}
				}
				else {
					for (int k = 0; k < sizeof(stringToInsert); k++) {
						editedBuf[j] = stringToInsert[k];
						j++;
						if (stringToInsert[k + 1] == '\0') {
							if(buf[i + 1] == '\0')
								editedBuf[j] = '\0';
							else {
								editedBuf[j] = '\r';
								j++;
								editedBuf[j] = '\n';
								j++;
							}
							line++;
							correntInserted = true;
							break;
						}

					}
				}
			}
			else if (correntInserted) {
				editedBuf[j] = buf[i];
				j++;
			}
		}

		b = WriteFile(hAppend, editedBuf, j, &n, NULL);
		if (!b) {
			CloseHandle(hAppend);
			throw ("Write file unsuccessful\n");
		}

		char* correct = ConvertUtf8ToAnsi(editedBuf);
		std::cout << correct << std::endl;
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


int main()
{
	setlocale(0, "ru");
	LPWSTR  file = (LPWSTR)(L"../OS09_01.txt");

	char str[] = "1234567890";
	wchar_t wStr[50];
	mbstowcs(wStr, str, strlen(str) + 1);
	LPWSTR strToIns = wStr;

	insRowFileTxt(file, strToIns, 0);
	insRowFileTxt(file, strToIns, -1);
	insRowFileTxt(file, strToIns, 5);
	insRowFileTxt(file, strToIns, 7);

	printFileText(file);

	system("pause");
}