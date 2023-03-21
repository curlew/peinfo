#include "import_table.h"

#include <stdio.h>
#include <stdint.h>

// convert relative virtual address to virtual address
static LPVOID rva_to_va(PIMAGE_NT_HEADERS nt_headers, LPVOID base, DWORD rva) {
    // this can also be done using the windows debug help library
    // see ImageRvaToVa
    // https://learn.microsoft.com/en-us/windows/win32/api/dbghelp/nf-dbghelp-imagervatova

    PIMAGE_SECTION_HEADER sect = IMAGE_FIRST_SECTION(nt_headers);
    for (int i = 0; i < nt_headers->FileHeader.NumberOfSections; ++i, ++sect) {
        DWORD sect_start = sect->VirtualAddress;
        DWORD sect_end = sect->VirtualAddress + sect->Misc.VirtualSize;
        if (sect_start <= rva && rva < sect_end) {
            DWORD file_offset = rva - sect->VirtualAddress + sect->PointerToRawData;
            return (LPVOID)((DWORD_PTR)base + file_offset);
        }
    }
    return NULL;
}

void print_import_table(LPVOID base) {
    PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((uint8_t *)base + ((PIMAGE_DOS_HEADER)base)->e_lfanew);

    if (nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size == 0) {
        _putws(L"Import table is empty");
        return;
    }

    DWORD import_table_rva = nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;

    PIMAGE_IMPORT_DESCRIPTOR import_dir_table = (PIMAGE_IMPORT_DESCRIPTOR)rva_to_va(nt_headers, base, import_table_rva);

    _putws(L"____________________  Import Table  ____________________________________________");

    for (PIMAGE_IMPORT_DESCRIPTOR import = import_dir_table; import->Name != 0; ++import) {
        wprintf(L" - import: %S\n",
            (char *)rva_to_va(nt_headers, base, import->Name));
    }
}
