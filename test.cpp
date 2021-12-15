#include <iostream>
#include <Windows.h>
#include "patternscan.h"

//PatternScan function list
template <class Type> Type Range(Type Address, size_t Len, uint8_t* bMask, uint8_t* vMask, TypeRPMFunc<Type> RPM);
template <class Type> Type Range(Type Address, size_t Len, std::string strPattern, TypeRPMFunc<Type> RPM);
template <class Type> Type Module(Type ModuleBase, uint8_t* bMask, uint8_t* vMask, TypeRPMFunc<Type> RPM);
template <class Type> Type Module(Type ModuleBase, std::string strPattern, TypeRPMFunc<Type> RPM);
uintptr_t Range(uintptr_t Address, size_t Len, uint8_t* bMask, uint8_t* vMask, TypeRPMFunc<uintptr_t> RPM);
uintptr_t Range(uintptr_t Address, size_t Len, std::string strPattern, TypeRPMFunc<uintptr_t> RPM);
uintptr_t Module(uintptr_t ModuleBase, uint8_t* bMask, uint8_t* vMask, TypeRPMFunc<uintptr_t> RPM);
uintptr_t Module(uintptr_t ModuleBase, std::string strPattern, TypeRPMFunc<uintptr_t> RPM);
//You can specify the type which is uint32_t or uint64_t when you do PatternScan.
//uint32_t is for 32bit process scan, uint64_t is for 64bit process scan.
//If you don't specify type, type is uintptr_t.

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
    uintptr_t ScanResult = PatternScan::Module((uintptr_t)hModule, Pattern_GetCurrentProcessId,
        [&](uintptr_t Address, void* Buffer, size_t Size) -> bool {
            NumberOfRPMCalled++;
            SIZE_T nBytesRead;
            //Replace ReadProcessMemry with your own read method.
            return ReadProcessMemory(GetCurrentProcess(), LPCVOID(Address), Buffer, Size, &nBytesRead) == TRUE;
        });

    std::cout << std::hex << "ScanResult : 0x" << ScanResult << std::endl;
    std::cout << "NumberOfRPMCalled : " << NumberOfRPMCalled << std::endl;
    return 0;
}
