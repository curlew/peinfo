#include "optional_header.h"

#include "utils.h"
#include <stdio.h>

void print_optional_header(PIMAGE_OPTIONAL_HEADER header) {
    print_heading(L"Optional Header");

    const wchar_t *fmt_byte          = L"%-27s : %hhu\n",
                  *fmt_word          = L"%-27s : %hu\n",
                  *fmt_dword         = L"%-27s : %lu\n",
                  *fmt_ulonglong     = L"%-27s : %llu\n",
                  *fmt_word_hex      = L"%-27s : 0x%hX\n",
                  *fmt_dword_hex     = L"%-27s : 0x%lX\n",
                  *fmt_ulonglong_hex = L"%-27s : 0x%llX\n";

    wprintf(fmt_word_hex, L"Magic", header->Magic);
    wprintf(fmt_byte, L"MajorLinkerVersion", header->MajorLinkerVersion);
    wprintf(fmt_byte, L"MinorLinkerVersion", header->MinorLinkerVersion);
    wprintf(fmt_dword, L"SizeOfCode", header->SizeOfCode);
    wprintf(fmt_dword, L"SizeOfInitializedData", header->SizeOfInitializedData);
    wprintf(fmt_dword, L"SizeOfUninitializedData", header->SizeOfUninitializedData);
    wprintf(fmt_dword_hex, L"AddressOfEntryPoint", header->AddressOfEntryPoint);
    wprintf(fmt_dword_hex, L"BaseOfCode", header->BaseOfCode);
    wprintf(fmt_ulonglong_hex, L"ImageBase", header->ImageBase);
    wprintf(fmt_dword, L"SectionAlignment", header->SectionAlignment);
    wprintf(fmt_dword, L"FileAlignment", header->FileAlignment);
    wprintf(fmt_word, L"MajorOperatingSystemVersion", header->MajorOperatingSystemVersion);
    wprintf(fmt_word, L"MinorOperatingSystemVersion", header->MinorOperatingSystemVersion);
    wprintf(fmt_word, L"MajorImageVersion", header->MajorImageVersion);
    wprintf(fmt_word, L"MinorImageVersion", header->MinorImageVersion);
    wprintf(fmt_word, L"MajorSubsystemVersion", header->MajorSubsystemVersion);
    wprintf(fmt_word, L"MinorSubsystemVersion", header->MinorSubsystemVersion);
    wprintf(fmt_dword, L"Win32VersionValue", header->Win32VersionValue);
    wprintf(fmt_dword, L"SizeOfImage", header->SizeOfImage);
    wprintf(fmt_dword, L"SizeOfHeaders", header->SizeOfHeaders);
    wprintf(fmt_dword, L"CheckSum", header->CheckSum);
    wprintf(fmt_word, L"Subsystem", header->Subsystem);
    wprintf(fmt_word_hex, L"DllCharacteristics", header->DllCharacteristics);
    wprintf(fmt_ulonglong, L"SizeOfStackReserve", header->SizeOfStackReserve);
    wprintf(fmt_ulonglong, L"SizeOfStackCommit", header->SizeOfStackCommit);
    wprintf(fmt_ulonglong, L"SizeOfHeapReserve", header->SizeOfHeapReserve);
    wprintf(fmt_ulonglong, L"SizeOfHeapCommit", header->SizeOfHeapCommit);
    wprintf(fmt_dword, L"LoaderFlags", header->LoaderFlags);
    wprintf(fmt_dword, L"NumberOfRvaAndSizes", header->NumberOfRvaAndSizes);

    //IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];

    wprintf(L"\n");
}