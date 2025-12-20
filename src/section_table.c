#include "section_table.h"

#include "characteristics.h"
#include "utils.h"
#include <stdio.h>

#define SECTION_CHARACTERISTIC_LIST(X) \
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

const struct characteristic section_characteristics[] = {
    SECTION_CHARACTERISTIC_LIST(GENERATE_CHARACTERISTIC_STRUCT)
};


void print_section_table(PIMAGE_SECTION_HEADER header, WORD section_count) {
    print_heading(L"Section Table");

    for (int i = 0; i < section_count; ++i, ++header) {
        wprintf(L"  [ Section %d of %d ]\n", i + 1, section_count);

        #define FMT_STRING    L"%-20s : %S"
        #define FMT_WORD      L"%-20s : %hu"
        #define FMT_DWORD_HEX L"%-20s : 0x%lX"

        wprintf(FMT_STRING L"\n",    L"Name",                 header->Name);
        wprintf(FMT_DWORD_HEX L"\n", L"VirtualSize",          header->Misc.VirtualSize);
        wprintf(FMT_DWORD_HEX L"\n", L"VirtualAddress",       header->VirtualAddress);
        wprintf(FMT_DWORD_HEX L"\n", L"SizeOfRawData",        header->SizeOfRawData);
        wprintf(FMT_DWORD_HEX L"\n", L"PointerToRawData",     header->PointerToRawData);
        wprintf(FMT_DWORD_HEX L"\n", L"PointerToRelocations", header->PointerToRelocations);
        wprintf(FMT_DWORD_HEX L"\n", L"PointerToLinenumbers", header->PointerToLinenumbers);
        wprintf(FMT_WORD L"\n",      L"NumberOfRelocations",  header->NumberOfRelocations);
        wprintf(FMT_WORD L"\n",      L"NumberOfLinenumbers",  header->NumberOfLinenumbers);
        wprintf(FMT_DWORD_HEX,       L"Characteristics",      header->Characteristics);
        if (header->Characteristics == 0) {
            wprintf(L"\n");
        } else {
            wprintf(L" (");
            print_characteristics(header->Characteristics, section_characteristics,
                                  sizeof (section_characteristics) / sizeof (section_characteristics[0]));
            wprintf(L")\n");
        }

        wprintf(L"\n");
    }
}
