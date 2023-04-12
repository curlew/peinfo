#include "section_table.h"

#include <stdio.h>

#define SECTION_CHARACTERISTICS \
    X(IMAGE_SCN_TYPE_NO_PAD)          X(IMAGE_SCN_CNT_CODE) \
    X(IMAGE_SCN_CNT_INITIALIZED_DATA) X(IMAGE_SCN_CNT_UNINITIALIZED_DATA) \
    X(IMAGE_SCN_LNK_OTHER)            X(IMAGE_SCN_LNK_INFO) \
    X(IMAGE_SCN_LNK_REMOVE)           X(IMAGE_SCN_LNK_COMDAT) \
    X(IMAGE_SCN_NO_DEFER_SPEC_EXC)    X(IMAGE_SCN_GPREL) \
    X(IMAGE_SCN_MEM_PURGEABLE)        X(IMAGE_SCN_MEM_LOCKED) \
    X(IMAGE_SCN_MEM_PRELOAD)          X(IMAGE_SCN_ALIGN_1BYTES) \
    X(IMAGE_SCN_ALIGN_2BYTES)         X(IMAGE_SCN_ALIGN_4BYTES) \
    X(IMAGE_SCN_ALIGN_8BYTES)         X(IMAGE_SCN_ALIGN_16BYTES) \
    X(IMAGE_SCN_ALIGN_32BYTES)        X(IMAGE_SCN_ALIGN_64BYTES) \
    X(IMAGE_SCN_ALIGN_128BYTES)       X(IMAGE_SCN_ALIGN_256BYTES) \
    X(IMAGE_SCN_ALIGN_512BYTES)       X(IMAGE_SCN_ALIGN_1024BYTES) \
    X(IMAGE_SCN_ALIGN_2048BYTES)      X(IMAGE_SCN_ALIGN_4096BYTES) \
    X(IMAGE_SCN_ALIGN_8192BYTES)      X(IMAGE_SCN_LNK_NRELOC_OVFL) \
    X(IMAGE_SCN_MEM_DISCARDABLE)      X(IMAGE_SCN_MEM_NOT_CACHED) \
    X(IMAGE_SCN_MEM_NOT_PAGED)        X(IMAGE_SCN_MEM_SHARED) \
    X(IMAGE_SCN_MEM_EXECUTE)          X(IMAGE_SCN_MEM_READ) \
    X(IMAGE_SCN_MEM_WRITE)

void print_section_table(PIMAGE_SECTION_HEADER header, WORD section_count) {
    _putws(L"____________________  Section Table  ___________________________________________");

    for (int i = 0; i < section_count; ++i, ++header) {
        wprintf(L"  [ Section %d of %d ]\n", i + 1, section_count);

        const wchar_t *fmt_string    = L"%-20s : %S\n",
                      *fmt_word      = L"%-20s : %hu\n",
                      *fmt_dword     = L"%-20s : %lu\n";
        wprintf(fmt_string, L"Name",                 header->Name);
        wprintf(fmt_dword,  L"PhysicalAddress",      header->Misc.VirtualSize);
        wprintf(fmt_dword,  L"VirtualAddress",       header->VirtualAddress);
        wprintf(fmt_dword,  L"SizeOfRawData",        header->SizeOfRawData);
        wprintf(fmt_dword,  L"PointerToRawData",     header->PointerToRawData);
        wprintf(fmt_dword,  L"PointerToRelocations", header->PointerToRelocations);
        wprintf(fmt_dword,  L"PointerToLinenumbers", header->PointerToLinenumbers);
        wprintf(fmt_word,   L"NumberOfRelocations",  header->NumberOfRelocations);
        wprintf(fmt_word,   L"NumberOfLinenumbers",  header->NumberOfLinenumbers);

        wprintf(L"%-20s : %#010lx", L"Characteristics", header->Characteristics);
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

            SECTION_CHARACTERISTICS

            #undef X

            wprintf(L")\n");
        }

        wprintf(L"\n");
    }
}
