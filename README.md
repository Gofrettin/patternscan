# patternscan
very simple library for pattern scan   
Whatever RPM method you use, you can integrate it with PatternScan.   
example usage   
```
//Include just one header file.
#include "patternscan.h"
//Do PatternScan with your own RPM method.
uintptr ScanResult = PatternScan::Module((uintptr_t)hModule, Pattern_GetCurrentProcessId,
        [&](uintptr Address, void* Buffer, size_t Size) -> bool {
            SIZE_T nBytesRead;
            //Replace ReadProcessMemry with your own read method.
            return ReadProcessMemory(GetCurrentProcess(), LPCVOID(Address), Buffer, Size, &nBytesRead) == TRUE;
        });
//done!
 
//PatternScan function list
template <class Type> using TypeRPMFunc = std::function<bool(Type Address, void* Buffer, size_t Size)>;
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
```
![Desktop Screenshot 2021 12 09 - 02 13 32 86](https://user-images.githubusercontent.com/32794121/146116073-9cc8dd5f-2815-44d3-8d0c-d9ab4dafc228.jpg)
