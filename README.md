<div align="center">

# peinfo

[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/curlew/peinfo/cmake.yml?logo=github&style=flat-square)](https://github.com/curlew/peinfo/actions/workflows/cmake.yml)
[![Latest tag](https://img.shields.io/github/v/tag/curlew/peinfo?color=informational&logo=github&style=flat-square)](https://github.com/curlew/peinfo/tags)
[![License](https://img.shields.io/github/license/curlew/peinfo?style=flat-square)](https://github.com/curlew/peinfo/blob/main/LICENSE)

</div>

## Overview

`peinfo` is a small standalone utility for examining Portable Executable (PE) files.
See the [PE Format Specification](https://learn.microsoft.com/en-us/windows/win32/debug/pe-format).


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
Machine              : 0x8664 (x64)
NumberOfSections     : 7
TimeDateStamp        : 1766202990 (2025-12-20 03:56:30 UTC)
PointerToSymbolTable : 0x0
NumberOfSymbols      : 0
SizeOfOptionalHeader : 0xF0
Characteristics      : 0x22 (IMAGE_FILE_EXECUTABLE_IMAGE, IMAGE_FILE_LARGE_ADDRESS_AWARE)
```

</details>

<details>
<summary>Example output: Optional header</summary>

```
____________________  Optional Header  _________________________________________
Magic                       : 0x20B (PE32+)
MajorLinkerVersion          : 14
MinorLinkerVersion          : 38
SizeOfCode                  : 0x19400
SizeOfInitializedData       : 0x10E00
SizeOfUninitializedData     : 0x0
AddressOfEntryPoint         : 0x2650 (0x0000000140002650)
BaseOfCode                  : 0x1000
ImageBase                   : 0x140000000 (0x0000000140000000 to 0x000000014002FFFF)
SectionAlignment            : 0x1000
FileAlignment               : 0x200
MajorOperatingSystemVersion : 6
MinorOperatingSystemVersion : 0
MajorImageVersion           : 0
MinorImageVersion           : 0
MajorSubsystemVersion       : 6
MinorSubsystemVersion       : 0
Win32VersionValue           : 0
SizeOfImage                 : 0x30000
SizeOfHeaders               : 0x400
CheckSum                    : 0x0
Subsystem                   : 3 (Windows CUI)
DllCharacteristics          : 0x8160
SizeOfStackReserve          : 0x100000
SizeOfStackCommit           : 0x1000
SizeOfHeapReserve           : 0x100000
SizeOfHeapCommit            : 0x1000
LoaderFlags                 : 0x0
NumberOfRvaAndSizes         : 16
 - DataDirectory[ 0]: RVA [       0], Size [       0] - Export Table
 - DataDirectory[ 1]: RVA [   27114], Size [      28] - Import Table
 - DataDirectory[ 2]: RVA [   2E000], Size [     1E0] - Resource Table
 - DataDirectory[ 3]: RVA [   2B000], Size [    150C] - Exception Table
 - DataDirectory[ 4]: RVA [       0], Size [       0] - Certificate Table
 - DataDirectory[ 5]: RVA [   2F000], Size [     6F4] - Base Relocation Table
 - DataDirectory[ 6]: RVA [   256B0], Size [      1C] - Debug
 - DataDirectory[ 7]: RVA [       0], Size [       0] - Architecture
 - DataDirectory[ 8]: RVA [       0], Size [       0] - Global Pointer
 - DataDirectory[ 9]: RVA [       0], Size [       0] - Thread Local Storage (TLS)
 - DataDirectory[10]: RVA [   25570], Size [     140] - Load Config Table
 - DataDirectory[11]: RVA [       0], Size [       0] - Bound Import Table
 - DataDirectory[12]: RVA [   1B000], Size [     290] - Import Address Table (IAT)
 - DataDirectory[13]: RVA [       0], Size [       0] - Delay Import Descriptor
 - DataDirectory[14]: RVA [       0], Size [       0] - CLR Runtime Header
 - DataDirectory[15]: RVA [       0], Size [       0] - Reserved
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
 - SHELL32.dll
   -  1AE ShellExecuteW
 - KERNEL32.dll
   -  224 GetCurrentThreadId
   -  2F2 GetSystemTimeAsFileTime
   -  310 GetTickCount
   -  4D4 RtlCaptureContext
   -  220 GetCurrentProcessId
   -  4E2 RtlVirtualUnwind
   -  5BE UnhandledExceptionFilter
   -  57D SetUnhandledExceptionFilter
   -  21F GetCurrentProcess
   -  59C TerminateProcess
   -  451 QueryPerformanceCounter
   -  4DB RtlLookupFunctionEntry
 - msvcrt.dll
   -   90 __setusermatherr
   -  17D _initterm
   -   57 __C_specific_handler
   -  382 _wcmdln
   -  127 _fmode
   -   D2 _commode
   -   2F ?terminate@@YAXXZ
   -   C1 _cexit
   -   9D __wgetmainargs
   -   AE _amsg_exit
   -   55 _XcptFilter
   -  432 exit
   -   8E __set_app_type
   -  10E _exit
 - ADVAPI32.dll
   -  122 EventSetInformation
   -  129 EventWriteTransfer
   -  121 EventRegister
 - api-ms-win-core-synch-l1-2-0.dll
   -   2D Sleep
 - api-ms-win-core-processthreads-l1-1-0.dll
   -   20 GetStartupInfoW
 - api-ms-win-core-libraryloader-l1-2-0.dll
   -   14 GetModuleHandleW
```

</details>

<details>
<summary>Example output: Export table</summary>

```
____________________  Export Table  ____________________________________________
Number of functions: 1634
Number of names: 1634
Ordinal base: 1

Ordinal    RVA        Name
1                     AcquireSRWLockExclusive (forwarded to NTDLL.RtlAcquireSRWLockExclusive)
2                     AcquireSRWLockShared (forwarded to NTDLL.RtlAcquireSRWLockShared)
3          000203C0   ActivateActCtx
4          0001BA40   ActivateActCtxWorker
5          0005B850   AddAtomA
6          00012920   AddAtomW
7          00025980   AddConsoleAliasA
8          00025990   AddConsoleAliasW
9                     AddDllDirectory (forwarded to api-ms-win-core-libraryloader-l1-1-0.AddDllDirectory)
10         0003E3F0   AddIntegrityLabelToBoundaryDescriptor
11         0005B990   AddLocalAlternateComputerNameA
12         0005B9F0   AddLocalAlternateComputerNameW
13         000225B0   AddRefActCtx
14         0001E600   AddRefActCtxWorker
15         0003BD30   AddResourceAttributeAce
16         00020BE0   AddSIDToBoundaryDescriptor
17         0003BD50   AddScopedPolicyIDAce
18         0003A150   AddSecureMemoryCacheCallback
19                    AddVectoredContinueHandler (forwarded to NTDLL.RtlAddVectoredContinueHandler)
20                    AddVectoredExceptionHandler (forwarded to NTDLL.RtlAddVectoredExceptionHandler)
21         00007200   AdjustCalendarDate
22         000255D0   AllocConsole
23         0003BD90   AllocateUserPhysicalPages
24         0003BD70   AllocateUserPhysicalPagesNuma
25                    AppPolicyGetClrCompat (forwarded to kernelbase.AppPolicyGetClrCompat)
26                    AppPolicyGetCreateFileAccess (forwarded to kernelbase.AppPolicyGetCreateFileAccess)
27                    AppPolicyGetLifecycleManagement (forwarded to kernelbase.AppPolicyGetLifecycleManagement)
28                    AppPolicyGetMediaFoundationCodecLoading (forwarded to kernelbase.AppPolicyGetMediaFoundationCodecLoading)
29                    AppPolicyGetProcessTerminationMethod (forwarded to kernelbase.AppPolicyGetProcessTerminationMethod)
30                    AppPolicyGetShowDeveloperDiagnostic (forwarded to kernelbase.AppPolicyGetShowDeveloperDiagnostic)
31                    AppPolicyGetThreadInitializationType (forwarded to kernelbase.AppPolicyGetThreadInitializationType)
32                    AppPolicyGetWindowingModel (forwarded to kernelbase.AppPolicyGetWindowingModel)
33                    AppXGetOSMaxVersionTested (forwarded to kernelbase.AppXGetOSMaxVersionTested)
34         00045540   ApplicationRecoveryFinished
35         00045550   ApplicationRecoveryInProgress
36         00020F30   AreFileApisANSI
37         00020240   AssignProcessToJobObject
38         000255E0   AttachConsole
39         0005E3F0   BackupRead
40         0005F5B0   BackupSeek
```

</details>


## Building

```
cmake -B build
cmake --build build --config Release
```
