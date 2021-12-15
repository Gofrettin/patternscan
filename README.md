# patternscan
very simple library for pattern scan   
Whatever RPM method you use, you can integrate it with PatternScan.   
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

![Desktop Screenshot 2021 12 09 - 02 13 32 86](https://user-images.githubusercontent.com/32794121/146100656-c4cc1bbd-e6a0-4556-995f-cd6bc1cf8518.jpg)
