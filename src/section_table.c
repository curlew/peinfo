#include "section_table.h"

void print_section_table(PIMAGE_SECTION_HEADER header, WORD section_count) {
    _putws(L"____________________  Section Table  ___________________________________________");

    for (int i = 0; i < section_count; ++i, ++header) {
        wprintf(L"  [ Section %d of %d ]\n", i + 1, section_count);

        const wchar_t *fmt_string    = L"%-20s : %S\n",
                      *fmt_word      = L"%-20s : %hu\n",
                      *fmt_dword     = L"%-20s : %lu\n",
                      *fmt_dword_hex = L"%-20s : %#010lx\n";
        wprintf(fmt_string,    L"Name",                 header->Name);
        wprintf(fmt_dword,     L"PhysicalAddress",      header->Misc.VirtualSize);
        wprintf(fmt_dword,     L"VirtualAddress",       header->VirtualAddress);
        wprintf(fmt_dword,     L"SizeOfRawData",        header->SizeOfRawData);
        wprintf(fmt_dword,     L"PointerToRawData",     header->PointerToRawData);
        wprintf(fmt_dword,     L"PointerToRelocations", header->PointerToRelocations);
        wprintf(fmt_dword,     L"PointerToLinenumbers", header->PointerToLinenumbers);
        wprintf(fmt_word,      L"NumberOfRelocations",  header->NumberOfRelocations);
        wprintf(fmt_word,      L"NumberOfLinenumbers",  header->NumberOfLinenumbers);
        wprintf(fmt_dword_hex, L"Characteristics",      header->Characteristics);
        wprintf(L"\n");
    }
}
