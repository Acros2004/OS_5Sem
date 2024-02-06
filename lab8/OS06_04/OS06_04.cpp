#include <Windows.h>
#include <iostream>

void sh(HANDLE heap) {
    PROCESS_HEAP_ENTRY entry = { 0 };
    while (HeapWalk(heap, &entry)) {
        std::cout << "-- Address: " << std::hex << entry.lpData
            << ", Size: " << std::dec << entry.cbData
            << ((entry.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " UNCOMMITTED" : "")
            << ((entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " BUSY" : "")
            << "\n";
    }
    std::cout << "-----------------------------------\n\n";
}

int main() {
    HANDLE processHeap = GetProcessHeap();

    sh(processHeap);

    int arraySize = 300000;
    int* dynamicArray = new int[arraySize];
    std::cout << "Array Address: " << std::hex << dynamicArray << ", Size: " << std::dec << 4*arraySize << " \n\n";
    std::cout << "-------------------after---------" << std::endl;
    sh(processHeap);

    delete[] dynamicArray;

    return 0;
}
// 000002529DA20000