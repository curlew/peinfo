#include "file_header.h"

#include <stdio.h>

#define FILE_CHARACTERISTICS \
    X(IMAGE_FILE_RELOCS_STRIPPED)    X(IMAGE_FILE_EXECUTABLE_IMAGE) \
    X(IMAGE_FILE_LINE_NUMS_STRIPPED) X(IMAGE_FILE_LOCAL_SYMS_STRIPPED) \
    X(IMAGE_FILE_AGGRESIVE_WS_TRIM)  X(IMAGE_FILE_LARGE_ADDRESS_AWARE) \
    X(IMAGE_FILE_BYTES_REVERSED_LO)  X(IMAGE_FILE_32BIT_MACHINE) \
    X(IMAGE_FILE_DEBUG_STRIPPED)     X(IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP) \
    X(IMAGE_FILE_NET_RUN_FROM_SWAP)  X(IMAGE_FILE_SYSTEM) \
    X(IMAGE_FILE_DLL)                X(IMAGE_FILE_UP_SYSTEM_ONLY) \
    X(IMAGE_FILE_BYTES_REVERSED_HI)

void print_file_header(PIMAGE_FILE_HEADER header) {
    _putws(L"____________________  File Header  _____________________________________________");

    const wchar_t *fmt_word_hex = L"%-20s : %#06x\n",
                  *fmt_word     = L"%-20s : %hu\n",
                  *fmt_dword    = L"%-20s : %lu\n";
    wprintf(fmt_word_hex, L"Machine",              header->Machine);
    wprintf(fmt_word,     L"NumberOfSections",     header->NumberOfSections);
    wprintf(fmt_dword,    L"TimeDateStamp",        header->TimeDateStamp);
    wprintf(fmt_dword,    L"PointerToSymbolTable", header->PointerToSymbolTable);
    wprintf(fmt_dword,    L"NumberOfSymbols",      header->NumberOfSymbols);
    wprintf(fmt_word,     L"SizeOfOptionalHeader", header->SizeOfOptionalHeader);


    wprintf(L"%-20s : %#06x", L"Characteristics", header->Characteristics);
    if (header->Characteristics == 0) {
        wprintf(L"\n");
    } else {
        int flags_printed = 0;
        wprintf(L" (");

        #define X(flag) \
            if (header->Characteristics & flag) { \
                if (flags_printed > 0) { wprintf(L", "); } \
                wprintf(L"%S", #flag); \
                ++flags_printed; \
            }

        FILE_CHARACTERISTICS

        #undef X

        wprintf(L")\n");
    }

    wprintf(L"\n");
}