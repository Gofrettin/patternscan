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
```
See "test.cpp" and "patternscan.h" for more information

![Desktop Screenshot 2021 12 09 - 02 13 32 86](https://user-images.githubusercontent.com/32794121/146113631-8dd9ccf8-e9be-4ad8-84a5-d279505d04e7.jpg)
