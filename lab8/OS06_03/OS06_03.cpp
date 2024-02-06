
#include <iostream>
#include <Windows.h>


using namespace std;
int PG = 4096;



int main()
{
    setlocale(LC_ALL, "rus");
    
    int pg = 256;

    int countItems = pg * PG / sizeof(int);


    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);

    int* virtArray = (int*)VirtualAlloc(NULL, pg * PG, MEM_COMMIT, PAGE_READWRITE);

    for (int i = 0; i < countItems; i++)
    {
        virtArray[i] = i;
    }
    cout << "Каребо" << endl;


    char char1 = 'К';
    int codeChar1 = 0xca;
    char char2 = 'а';
    int codeChar2 = 0xe0;
    char char3 = 'р';
    int codeChar3 = 0xf0;
    int offset_E0F = 3596;

    int page_CA = codeChar1;
    int address_CA = 4096 * page_CA;
    int address_E0F = address_CA + offset_E0F;
    int*  forDebug = &virtArray[address_E0F];
    cout << char1 << " = " << hex << codeChar1 << endl;
    cout << char2 << " = " << hex << codeChar2 << endl;
    cout << char3 << " = " << hex << codeChar3 << endl;
    cout << "Страница " << hex << codeChar1 << ", смещение " << hex << offset_E0F << " = " << dec << offset_E0F << endl;
    int value = address_E0F / 4;
    cout << virtArray[value] << endl;

    cout << endl;

    VirtualFree(virtArray, NULL, MEM_RELEASE) ? cout << "VirtualFree free\n" : cout << "Virtual false\n";

    //К=202=ca
    //а=224=e0
    //р=240=f0
    //страница ca = 202
    //смещение e0f = 3599 = 3596
    //адрес страницы =4096*202=827 392(10)
    // адрес смещения = 827392 + 3596 = 830 988 = CAE0C
    // (830 988)/ 4 = 207 747(10) =  32B83(16)
    // адрес смещения = адрес + смещение
}
