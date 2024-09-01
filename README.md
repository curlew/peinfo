<div align="center">

# peinfo

[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/curlew/peinfo/cmake.yml?logo=github&style=flat-square)](https://github.com/curlew/peinfo/actions/workflows/cmake.yml)
[![License](https://img.shields.io/github/license/curlew/peinfo?style=flat-square)](https://github.com/curlew/peinfo/blob/main/LICENSE)

</div>

## Usage

```
Usage: peinfo.exe [options] FILE
View headers and sections of Portable Executable files.

Options:
  -f  Display file header
  -o  Display optional header
  -s  Display section table
  -i  Display import table
  -e  Display export table
  -h  Display this help message and exit

If no options are specified, display all available information.
```


<details>
<summary>Example output: File header</summary>

```
____________________  File Header  _____________________________________________
Machine              : 0x8664
NumberOfSections     : 6
TimeDateStamp        : 1714645064
PointerToSymbolTable : 0
NumberOfSymbols      : 0
SizeOfOptionalHeader : 240
Characteristics      : 0x0022 (IMAGE_FILE_EXECUTABLE_IMAGE, IMAGE_FILE_LARGE_ADDRESS_AWARE)
```

</details>

<details>
<summary>Example output: Optional header</summary>

```
____________________  Optional Header  _________________________________________
Magic                       : 0x20B
MajorLinkerVersion          : 14
MinorLinkerVersion          : 38
SizeOfCode                  : 66560
SizeOfInitializedData       : 53760
SizeOfUninitializedData     : 0
AddressOfEntryPoint         : 0x1278
BaseOfCode                  : 0x1000
ImageBase                   : 0x140000000
SectionAlignment            : 4096
FileAlignment               : 512
MajorOperatingSystemVersion : 6
MinorOperatingSystemVersion : 0
MajorImageVersion           : 0
MinorImageVersion           : 0
MajorSubsystemVersion       : 6
MinorSubsystemVersion       : 0
Win32VersionValue           : 0
SizeOfImage                 : 139264
SizeOfHeaders               : 1024
CheckSum                    : 0
Subsystem                   : 3
DllCharacteristics          : 0x8160
SizeOfStackReserve          : 1048576
SizeOfStackCommit           : 4096
SizeOfHeapReserve           : 1048576
SizeOfHeapCommit            : 4096
LoaderFlags                 : 0
NumberOfRvaAndSizes         : 16
```

</details>

<details>
<summary>Example output: Section table</summary>

```
____________________  Section Table  ___________________________________________
  [ Section 1 of 6 ]
Name                 : .text
PhysicalAddress      : 66480
VirtualAddress       : 4096
SizeOfRawData        : 66560
PointerToRawData     : 1024
PointerToRelocations : 0
PointerToLinenumbers : 0
NumberOfRelocations  : 0
NumberOfLinenumbers  : 0
Characteristics      : 0x60000020 (IMAGE_SCN_CNT_CODE, IMAGE_SCN_MEM_EXECUTE, IMAGE_SCN_MEM_READ)

  [ Section 2 of 6 ]
Name                 : .rdata
PhysicalAddress      : 38786
VirtualAddress       : 73728
SizeOfRawData        : 38912
PointerToRawData     : 67584
PointerToRelocations : 0
PointerToLinenumbers : 0
NumberOfRelocations  : 0
NumberOfLinenumbers  : 0
Characteristics      : 0x40000040 (IMAGE_SCN_CNT_INITIALIZED_DATA, IMAGE_SCN_MEM_READ)

  [ Section 3 of 6 ]
Name                 : .data
PhysicalAddress      : 7368
VirtualAddress       : 114688
SizeOfRawData        : 3072
PointerToRawData     : 106496
PointerToRelocations : 0
PointerToLinenumbers : 0
NumberOfRelocations  : 0
NumberOfLinenumbers  : 0
Characteristics      : 0xc0000040 (IMAGE_SCN_CNT_INITIALIZED_DATA, IMAGE_SCN_MEM_READ, IMAGE_SCN_MEM_WRITE)

  [ Section 4 of 6 ]
Name                 : .pdata
PhysicalAddress      : 4308
VirtualAddress       : 122880
SizeOfRawData        : 4608
PointerToRawData     : 109568
PointerToRelocations : 0
PointerToLinenumbers : 0
NumberOfRelocations  : 0
NumberOfLinenumbers  : 0
Characteristics      : 0x40000040 (IMAGE_SCN_CNT_INITIALIZED_DATA, IMAGE_SCN_MEM_READ)

  [ Section 5 of 6 ]
Name                 : _RDATA
PhysicalAddress      : 500
VirtualAddress       : 131072
SizeOfRawData        : 512
PointerToRawData     : 114176
PointerToRelocations : 0
PointerToLinenumbers : 0
NumberOfRelocations  : 0
NumberOfLinenumbers  : 0
Characteristics      : 0x40000040 (IMAGE_SCN_CNT_INITIALIZED_DATA, IMAGE_SCN_MEM_READ)

  [ Section 6 of 6 ]
Name                 : .reloc
PhysicalAddress      : 1624
VirtualAddress       : 135168
SizeOfRawData        : 2048
PointerToRawData     : 114688
PointerToRelocations : 0
PointerToLinenumbers : 0
NumberOfRelocations  : 0
NumberOfLinenumbers  : 0
Characteristics      : 0x42000040 (IMAGE_SCN_CNT_INITIALIZED_DATA, IMAGE_SCN_MEM_DISCARDABLE, IMAGE_SCN_MEM_READ)
```

</details>

<details>
<summary>Example output: Import table</summary>

```
____________________  Import Table  ____________________________________________
 - KERNEL32.dll
   - QueryPerformanceCounter
   - GetCurrentProcessId
   - GetCurrentThreadId
   - GetSystemTimeAsFileTime
   - InitializeSListHead
   - RtlCaptureContext
   - RtlLookupFunctionEntry
   - RtlVirtualUnwind
   - IsDebuggerPresent
   - UnhandledExceptionFilter
   - SetUnhandledExceptionFilter
   - GetStartupInfoW
   - IsProcessorFeaturePresent
   - GetModuleHandleW
   - WriteConsoleW
   - RtlUnwindEx
   - GetLastError
   - SetLastError
   - EnterCriticalSection
   - LeaveCriticalSection
   - DeleteCriticalSection
   - InitializeCriticalSectionAndSpinCount
   - TlsAlloc
   - TlsGetValue
   - TlsSetValue
   - TlsFree
   - FreeLibrary
   - GetProcAddress
   - LoadLibraryExW
   - EncodePointer
   - RaiseException
   - RtlPcToFileHeader
   - GetStdHandle
   - WriteFile
   - GetModuleFileNameW
   - GetCurrentProcess
   - ExitProcess
   - TerminateProcess
   - GetModuleHandleExW
   - GetCommandLineA
   - GetCommandLineW
   - GetFileType
   - HeapAlloc
   - HeapFree
   - FindClose
   - FindFirstFileExW
   - FindNextFileW
   - IsValidCodePage
   - GetACP
   - GetOEMCP
   - GetCPInfo
   - MultiByteToWideChar
   - WideCharToMultiByte
   - GetEnvironmentStringsW
   - FreeEnvironmentStringsW
   - SetEnvironmentVariableW
   - SetStdHandle
   - GetStringTypeW
   - FlsAlloc
   - FlsGetValue
   - FlsSetValue
   - FlsFree
   - CompareStringW
   - LCMapStringW
   - GetProcessHeap
   - GetFileSizeEx
   - SetFilePointerEx
   - GetConsoleOutputCP
   - GetConsoleMode
   - HeapSize
   - HeapReAlloc
   - FlushFileBuffers
   - CloseHandle
   - CreateFileW
```

</details>

<details>
<summary>Example output: Export table</summary>

```
____________________  Export Table  ____________________________________________
 - _CreateFrameInfo
 - _CxxThrowException
 - _FindAndUnlinkFrame
 - _IsExceptionObjectToBeDestroyed
 - __AdjustPointer
 - __BuildCatchObject
 - __BuildCatchObjectHelper
 - __C_specific_handler
 - __C_specific_handler_noexcept
 - __CxxDetectRethrow
 - __CxxExceptionFilter
 - __CxxFrameHandler
 - __CxxFrameHandler2
 - __CxxFrameHandler3
 - __CxxQueryExceptionSize
 - __CxxRegisterExceptionObject
 - __CxxUnregisterExceptionObject
 - __DestructExceptionObject
 - __FrameUnwindFilter
 - __GetPlatformExceptionInfo
 - __NLG_Dispatch2
 - __NLG_Return2
 - __RTCastToVoid
 - __RTDynamicCast
 - __RTtypeid
 - __TypeMatch
 - __current_exception
 - __current_exception_context
 - __intrinsic_setjmp
 - __intrinsic_setjmpex
 - __processing_throw
 - __report_gsfailure
 - __std_exception_copy
 - __std_exception_destroy
 - __std_terminate
 - __std_type_info_compare
 - __std_type_info_destroy_list
 - __std_type_info_hash
 - __std_type_info_name
 - __telemetry_main_invoke_trigger
 - __telemetry_main_return_trigger
 - __unDName
 - __unDNameEx
 - __uncaught_exception
 - __uncaught_exceptions
 - __vcrt_GetModuleFileNameW
 - __vcrt_GetModuleHandleW
 - __vcrt_InitializeCriticalSectionEx
 - __vcrt_LoadLibraryExW
 - _get_purecall_handler
 - _get_unexpected
 - _is_exception_typeof
 - _local_unwind
 - _purecall
 - _set_purecall_handler
 - _set_se_translator
 - longjmp
 - memchr
 - memcmp
 - memcpy
 - memmove
 - memset
 - set_unexpected
 - strchr
 - strrchr
 - strstr
 - unexpected
 - wcschr
 - wcsrchr
 - wcsstr
```

</details>


## Building

```
cmake -B build
cmake --build build --config Release
```
