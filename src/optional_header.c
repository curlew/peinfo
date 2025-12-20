#include "optional_header.h"

#include "characteristics.h"
#include "utils.h"
#include <stdio.h>

#define DLL_CHARACTERISTIC_LIST(X) \
    X(IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA)       X(IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE) \
    X(IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY)       X(IMAGE_DLLCHARACTERISTICS_NX_COMPAT) \
    X(IMAGE_DLLCHARACTERISTICS_NO_ISOLATION)          X(IMAGE_DLLCHARACTERISTICS_NO_SEH) \
    X(IMAGE_DLLCHARACTERISTICS_NO_BIND)               X(IMAGE_DLLCHARACTERISTICS_APPCONTAINER) \
    X(IMAGE_DLLCHARACTERISTICS_WDM_DRIVER)            X(IMAGE_DLLCHARACTERISTICS_GUARD_CF) \
    X(IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE)

const struct characteristic dll_characteristics[] = {
    DLL_CHARACTERISTIC_LIST(GENERATE_CHARACTERISTIC_STRUCT)
};

static const wchar_t *get_subsystem_description(WORD subsystem);

void print_optional_header(PIMAGE_OPTIONAL_HEADER header) {
    print_heading(L"Optional Header");

    // TODO: handle 32-bit files (IMAGE_OPTIONAL_HEADER32)

    #define FMT_BYTE          L"%-27s : %hhu"
    #define FMT_WORD          L"%-27s : %hu"
    #define FMT_WORD_HEX      L"%-27s : 0x%hX"
    #define FMT_DWORD         L"%-27s : %lu"
    #define FMT_DWORD_HEX     L"%-27s : 0x%lX"
    #define FMT_ULONGLONG_HEX L"%-27s : 0x%llX"

    wprintf(FMT_WORD_HEX L" (%s)\n", L"Magic", header->Magic,
            header->Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC ? L"PE32+" : L"PE32");
    wprintf(FMT_BYTE L"\n", L"MajorLinkerVersion", header->MajorLinkerVersion);
    wprintf(FMT_BYTE L"\n", L"MinorLinkerVersion", header->MinorLinkerVersion);
    wprintf(FMT_DWORD_HEX L"\n", L"SizeOfCode", header->SizeOfCode);
    wprintf(FMT_DWORD_HEX L"\n", L"SizeOfInitializedData", header->SizeOfInitializedData);
    wprintf(FMT_DWORD_HEX L"\n", L"SizeOfUninitializedData", header->SizeOfUninitializedData);
    wprintf(FMT_DWORD_HEX L" (0x%016llX)\n", L"AddressOfEntryPoint", header->AddressOfEntryPoint,
            header->ImageBase + header->AddressOfEntryPoint);
    wprintf(FMT_DWORD_HEX L"\n", L"BaseOfCode", header->BaseOfCode);
    wprintf(FMT_ULONGLONG_HEX L" (0x%016llX to 0x%016llX)\n", L"ImageBase", header->ImageBase,
            header->ImageBase, header->ImageBase + header->SizeOfImage - 1);
    wprintf(FMT_DWORD_HEX L"\n", L"SectionAlignment", header->SectionAlignment);
    wprintf(FMT_DWORD_HEX L"\n", L"FileAlignment", header->FileAlignment);
    wprintf(FMT_WORD L"\n", L"MajorOperatingSystemVersion", header->MajorOperatingSystemVersion);
    wprintf(FMT_WORD L"\n", L"MinorOperatingSystemVersion", header->MinorOperatingSystemVersion);
    wprintf(FMT_WORD L"\n", L"MajorImageVersion", header->MajorImageVersion);
    wprintf(FMT_WORD L"\n", L"MinorImageVersion", header->MinorImageVersion);
    wprintf(FMT_WORD L"\n", L"MajorSubsystemVersion", header->MajorSubsystemVersion);
    wprintf(FMT_WORD L"\n", L"MinorSubsystemVersion", header->MinorSubsystemVersion);
    wprintf(FMT_DWORD L"\n", L"Win32VersionValue", header->Win32VersionValue);
    wprintf(FMT_DWORD_HEX L"\n", L"SizeOfImage", header->SizeOfImage);
    wprintf(FMT_DWORD_HEX L"\n", L"SizeOfHeaders", header->SizeOfHeaders);
    wprintf(FMT_DWORD_HEX L"\n", L"CheckSum", header->CheckSum);
    wprintf(FMT_WORD L" (%s)\n", L"Subsystem", header->Subsystem,
            get_subsystem_description(header->Subsystem));
    wprintf(FMT_WORD_HEX, L"DllCharacteristics", header->DllCharacteristics);
    if (header->DllCharacteristics == 0) {
        wprintf(L"\n");
    } else {
        wprintf(L" (");
        print_characteristics(header->DllCharacteristics, dll_characteristics,
                              sizeof (dll_characteristics) / sizeof (dll_characteristics[0]));
        wprintf(L")\n");
    }
    wprintf(FMT_ULONGLONG_HEX L"\n", L"SizeOfStackReserve", header->SizeOfStackReserve);
    wprintf(FMT_ULONGLONG_HEX L"\n", L"SizeOfStackCommit", header->SizeOfStackCommit);
    wprintf(FMT_ULONGLONG_HEX L"\n", L"SizeOfHeapReserve", header->SizeOfHeapReserve);
    wprintf(FMT_ULONGLONG_HEX L"\n", L"SizeOfHeapCommit", header->SizeOfHeapCommit);
    wprintf(FMT_DWORD_HEX L"\n", L"LoaderFlags", header->LoaderFlags);
    wprintf(FMT_DWORD L"\n", L"NumberOfRvaAndSizes", header->NumberOfRvaAndSizes);

    // See https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#optional-header-data-directories-image-only
    const wchar_t *data_directory_entries[] = {
        L"Export Table",
        L"Import Table",
        L"Resource Table",
        L"Exception Table",
        L"Certificate Table",
        L"Base Relocation Table",
        L"Debug",
        L"Architecture",
        L"Global Pointer",
        L"Thread Local Storage (TLS)",
        L"Load Config Table",
        L"Bound Import Table",
        L"Import Address Table (IAT)",
        L"Delay Import Descriptor",
        L"CLR Runtime Header",
        L"Reserved"
    };

    for (DWORD i = 0; i < header->NumberOfRvaAndSizes; ++i) {
        wprintf(L" - DataDirectory[%2d]: RVA [%8lX], Size [%8lX] - %s\n",
                i, header->DataDirectory[i].VirtualAddress, header->DataDirectory[i].Size,
                data_directory_entries[i]);
    }

    wprintf(L"\n");
}

const wchar_t *get_subsystem_description(WORD subsystem) {
    // See https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#windows-subsystem
    switch (subsystem) {
    case IMAGE_SUBSYSTEM_NATIVE:                   return L"Native";
    case IMAGE_SUBSYSTEM_WINDOWS_GUI:              return L"Windows GUI";
    case IMAGE_SUBSYSTEM_WINDOWS_CUI:              return L"Windows CUI";
    case IMAGE_SUBSYSTEM_OS2_CUI:                  return L"OS/2 CUI";
    case IMAGE_SUBSYSTEM_POSIX_CUI:                return L"POSIX CUI";
    case IMAGE_SUBSYSTEM_NATIVE_WINDOWS:           return L"Native Win9x driver";
    case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI:           return L"Windows CE";
    case IMAGE_SUBSYSTEM_EFI_APPLICATION:          return L"EFI application";
    case IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER:  return L"EFI driver with boot services";
    case IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER:       return L"EFI driver with run-time services";
    case IMAGE_SUBSYSTEM_EFI_ROM:                  return L"EFI ROM image";
    case IMAGE_SUBSYSTEM_XBOX:                     return L"XBOX";
    case IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION: return L"Windows boot application";
    default:                                       return L"Unknown";
    }
}
