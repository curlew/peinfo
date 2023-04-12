#include "data_directories.h"

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
    _putws(L"____________________  Import Table  ____________________________________________");

    PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((uint8_t *)base + ((PIMAGE_DOS_HEADER)base)->e_lfanew);

    PIMAGE_DATA_DIRECTORY import_data_dir = &nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (import_data_dir->Size == 0) {
        wprintf(L"Import table is empty\n\n");
        return;
    }

    // https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#import-directory-table
    PIMAGE_IMPORT_DESCRIPTOR import_dir_table = (PIMAGE_IMPORT_DESCRIPTOR)rva_to_va(nt_headers, base, import_data_dir->VirtualAddress);

    for (PIMAGE_IMPORT_DESCRIPTOR import_dir_entry = import_dir_table; import_dir_entry->Characteristics != 0; ++import_dir_entry) {
        // each IMAGE_IMPORT_DESCRIPTOR represents a DLL

        wprintf(L" - %S\n", (const char *)rva_to_va(nt_headers, base, import_dir_entry->Name));

        // https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#import-address-table
        PIMAGE_THUNK_DATA import_addr_table = rva_to_va(nt_headers, base, import_dir_entry->FirstThunk);

        for (PIMAGE_THUNK_DATA import = import_addr_table; import->u1.AddressOfData != 0; ++import) {
            // each IMAGE_THUNK_DATA represents a symbol imported from a DLL

            // most significant bit determines type
            if (IMAGE_SNAP_BY_ORDINAL(import->u1.AddressOfData)) {
                // import by ordinal
                wprintf(L"   - %zu\n", IMAGE_ORDINAL(import->u1.AddressOfData));
            } else {
                // import by name
                PIMAGE_IMPORT_BY_NAME name = rva_to_va(nt_headers, base, import->u1.AddressOfData); // TODO:
                wprintf(L"   - %S\n", name->Name);
            }
        }
    }

    wprintf(L"\n");
}

void print_export_table(LPVOID base) {
    _putws(L"____________________  Export Table  ____________________________________________");

    PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((uint8_t *)base + ((PIMAGE_DOS_HEADER)base)->e_lfanew);

    PIMAGE_DATA_DIRECTORY export_data_dir = &nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (export_data_dir->Size == 0) {
        wprintf(L"Export table is empty\n\n");
        return;
    }

    // https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#export-directory-table
    PIMAGE_EXPORT_DIRECTORY export_dir = (PIMAGE_EXPORT_DIRECTORY)rva_to_va(nt_headers, base, export_data_dir->VirtualAddress);

    // https://learn.microsoft.com/en-us/windows/win32/debug/pe-format#export-name-pointer-table
    PDWORD name_ptr_table = rva_to_va(nt_headers, base, export_dir->AddressOfNames);

    for (DWORD i = 0; i < export_dir->NumberOfNames; ++i) {
        wprintf(L" - %S\n", (const char *)rva_to_va(nt_headers, base, name_ptr_table[i]));
    }

    wprintf(L"\n");
}
