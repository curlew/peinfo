#include "file_header.h"

#include <stdio.h>

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
    wprintf(fmt_word_hex, L"Characteristics",      header->Characteristics);
    wprintf(L"\n");
}