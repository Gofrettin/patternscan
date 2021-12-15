#include <iostream>
#include <Windows.h>

//#define PATTERNSCAN_USE64BIT      //You maybe want 64bit pointer type even thought you are in x86.
//#define PATTERNSCAN_USE32BIT      //or vice versa
#include "patternscan.h"

int main()
{
    size_t NumberOfRPMCalled = 0;
    HMODULE hModule = GetModuleHandleA("KERNELBASE.dll");

#ifdef _WIN64
    char Pattern_GetCurrentProcessId[] = "65 48 8b 04 25 ? ? ? ? 8b 40 ? c3 cc";
    //KERNELBASE.GetCurrentProcessId + 0 - 65 48 8B 04 25 30000000  - mov rax, gs: [00000030] { 48 }
    //KERNELBASE.GetCurrentProcessId + 9 - 8B 40 40                 - mov eax, [rax + 40]
    //KERNELBASE.GetCurrentProcessId + C - C3                       - ret
#else
    char Pattern_GetCurrentProcessId[] = "64 a1 ? ? ? ? 8b 40 ? c3 cc";
    //KERNELBASE.GetCurrentProcessId + 0 - 64 A1 18000000   - mov eax, fs: [00000018] { 24 }
    //KERNELBASE.GetCurrentProcessId + 6 - 8B 40 20         - mov eax, [eax + 20]
    //KERNELBASE.GetCurrentProcessId + 9 - C3               - ret
#endif

    uintptr ScanResult = PatternScan::Module((uintptr)hModule, Pattern_GetCurrentProcessId,
        [&](uintptr Address, void* Buffer, size_t Size) -> bool {
            NumberOfRPMCalled++;
            SIZE_T nBytesRead;
            //Replace ReadProcessMemry with your own read method.
            return ReadProcessMemory(GetCurrentProcess(), LPCVOID(Address), Buffer, Size, &nBytesRead) == TRUE;
        });

    std::cout << std::hex << "ScanResult : 0x" << ScanResult << std::endl;
    std::cout << "NumberOfRPMCalled : " << NumberOfRPMCalled << std::endl;
    return 0;
}