# patternscan
very simple library for pattern scan   
example usage
```
//Include just one header file.
#include "patternscan.h"
//Do PatternScan with your own RPM method.
uintptr ScanResult = PatternScan::Module((uintptr)hModule, Pattern_GetCurrentProcessId,
        [&](uintptr Address, void* Buffer, size_t Size) -> bool {
            SIZE_T nBytesRead;
            return ReadProcessMemory(GetCurrentProcess(), LPCVOID(Address), Buffer, Size, &nBytesRead) == TRUE;
        });
//done!
//public methods list
//static uintptr PatternScan::Module(uintptr ModuleBase, std::string strPattern, TypeRPMFunc RPM);
//static uintptr PatternScan::Module(uintptr ModuleBase, uint8_t* bMask, uint8_t* vMask, TypeRPMFunc RPM);
//static uintptr PatternScan::Range(uintptr Address, size_t Len, std::string strPattern, TypeRPMFunc RPM);
//static uintptr PatternScan::Range(uintptr Address, size_t Len, uint8_t* bMask, uint8_t* vMask, TypeRPMFunc RPM);
```
See "test.cpp" and "patternscan.h" for more information
