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
    
    HANDLE userHeap = HeapCreate(0, 4 * 1024 * 1024, 0);

    sh(userHeap);

    int size = 300000;
    int* arr = (int*)HeapAlloc(userHeap, 0, size * sizeof(int));

    std::cout << "Array Address: " << std::hex << arr << ", Size: " << std::dec << size * 4 << " \n\n";

    sh(userHeap);

    HeapFree(userHeap, 0, arr);

    HeapDestroy(userHeap);

    return 0;
}
// 000002529DA20000