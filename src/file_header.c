#include "file_header.h"

#include "characteristics.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>

#define FILE_CHARACTERISTIC_LIST(X) \
    X(IMAGE_FILE_RELOCS_STRIPPED)    X(IMAGE_FILE_EXECUTABLE_IMAGE) \
    X(IMAGE_FILE_LINE_NUMS_STRIPPED) X(IMAGE_FILE_LOCAL_SYMS_STRIPPED) \
    X(IMAGE_FILE_AGGRESIVE_WS_TRIM)  X(IMAGE_FILE_LARGE_ADDRESS_AWARE) \
    X(IMAGE_FILE_BYTES_REVERSED_LO)  X(IMAGE_FILE_32BIT_MACHINE) \
    X(IMAGE_FILE_DEBUG_STRIPPED)     X(IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP) \
    X(IMAGE_FILE_NET_RUN_FROM_SWAP)  X(IMAGE_FILE_SYSTEM) \
    X(IMAGE_FILE_DLL)                X(IMAGE_FILE_UP_SYSTEM_ONLY) \
    X(IMAGE_FILE_BYTES_REVERSED_HI)

const struct characteristic file_characteristics[] = {
    FILE_CHARACTERISTIC_LIST(GENERATE_CHARACTERISTIC_STRUCT)
};

static const wchar_t *get_machine_description(WORD machine);

void print_file_header(PIMAGE_FILE_HEADER header) {
    print_heading(L"File Header");

    #define FMT_WORD      L"%-20s : %hu"
    #define FMT_WORD_HEX  L"%-20s : 0x%hX"
    #define FMT_DWORD     L"%-20s : %lu"
    #define FMT_DWORD_HEX L"%-20s : 0x%lX"

    time_t timestamp = header->TimeDateStamp;
    struct tm timestamp_utc;
    wchar_t timestamp_str[30];
    gmtime_s(&timestamp_utc, &timestamp);
    wcsftime(timestamp_str, 30, L"%Y-%m-%d %H:%M:%S UTC", &timestamp_utc);

    wprintf(FMT_WORD_HEX L" (%s)\n", L"Machine",              header->Machine, get_machine_description(header->Machine));
    wprintf(FMT_WORD L"\n",          L"NumberOfSections",     header->NumberOfSections);
    wprintf(FMT_DWORD L" (%s)\n",    L"TimeDateStamp",        header->TimeDateStamp, timestamp_str);
    wprintf(FMT_DWORD_HEX L"\n",     L"PointerToSymbolTable", header->PointerToSymbolTable);
    wprintf(FMT_DWORD L"\n",         L"NumberOfSymbols",      header->NumberOfSymbols);
    wprintf(FMT_WORD_HEX L"\n",      L"SizeOfOptionalHeader", header->SizeOfOptionalHeader);
    wprintf(FMT_WORD_HEX,            L"Characteristics",      header->Characteristics);
    if (header->Characteristics == 0) {
        wprintf(L"\n");
    } else {
        wprintf(L" (");
        print_characteristics(header->Characteristics, file_characteristics,
                              sizeof (file_characteristics) / sizeof (file_characteristics[0]));
        wprintf(L")\n");
    }

    wprintf(L"\n");
}

const wchar_t *get_machine_description(WORD machine) {
    // See https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#machine-types
    switch (machine) {
        case IMAGE_FILE_MACHINE_I386:  return L"x86";
        case IMAGE_FILE_MACHINE_AMD64: return L"x64";
        case IMAGE_FILE_MACHINE_ARM:   return L"ARM little-endian";
        case IMAGE_FILE_MACHINE_ARM64: return L"ARM64 little-endian";
        default:                       return L"Unknown";
    }
}
