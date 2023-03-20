#include "file_header.h"
#include "section_table.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

void print_usage(wchar_t *exe) {
    wprintf(L"Usage: %s [options] FILE\n", exe);
    _putws(L"View headers and sections of Portable Executable files.\n"
           L"\n"
           L"Options:\n"
           L"  -f  Display file header\n"
           L"  -o  Display optional header\n"
           L"  -s  Display section table\n"
           L"  -h  Display this help message and exit\n"
           L"\n"
           L"If no options are specified, display all available information.");
}

/*!
 * \retval  0 Success
 * \retval -1 Error opening file
 * \retval -2 File is invalid (bad DOS header)
 * \retval -3 File is invalid (bad PE header)
 */
int wmain(int argc, wchar_t *argv[]) {
    wchar_t *file_path = NULL;
    bool opt_f = false, opt_o = false, opt_s = false;

    for (int i = 1, operand_count = 0; i < argc; ++i) {
        if (argv[i][0] == L'-') {
            // option
            for (wchar_t *c = argv[i] + 1; *c; ++c) {
                switch (*c) {
                case L'f': opt_f = true; break;
                case L'o': opt_o = true; break;
                case L's': opt_s = true; break;
                case L'h':
                    print_usage(argv[0]);
                    return 0;
                default:
                    wprintf(L"Invalid option - \"%c\"\n\n", *c);
                    print_usage(argv[0]);
                    return 0;
                }
            }
        } else {
            // operand (non-option argument)
            if (++operand_count > 1) {
                print_usage(argv[0]);
                return 0;
            }
            file_path = argv[i];
        }
    }

    if (!file_path) {
        wprintf(L"No file specified\n\n");
        print_usage(argv[0]);
        return 0;
    }
    if (!(opt_f || opt_o || opt_s)) {
        // default options
        opt_f = opt_o = opt_s = true;
    }


    int ret = 0;
    // variables defined here so cleanup label can be jumped to from anywhere
    HANDLE file              = INVALID_HANDLE_VALUE,
           file_mapping      = NULL; // CreateFileMappingW returns NULL on failure
    LPVOID file_mapping_view = NULL;

    file = CreateFileW(file_path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE) {
        fwprintf(stderr, L"Error opening \"%s\"\n", file_path);
        ret = -1;
        goto cleanup;
    }

    file_mapping = CreateFileMappingW(file, NULL, PAGE_READONLY, 0, 0, NULL);
    if (file_mapping == NULL) {
        fwprintf(stderr, L"Error creating file mapping\n");
        ret = -1;
        goto cleanup;
    }

    file_mapping_view = MapViewOfFile(file_mapping, FILE_MAP_READ, 0, 0, 0);
    if (file_mapping_view == NULL) {
        fwprintf(stderr, L"Error mapping view of file\n");
        ret = -1;
        goto cleanup;
    }
    wprintf(L"Mapped view to %p\n", file_mapping_view);

    PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)file_mapping_view;
    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
        fwprintf(stderr, L"Invalid DOS header (e_magic != MZ)\n");
        ret = -2;
        goto cleanup;
    }
    wprintf(L"Found valid DOS header\n");

    // e_lfanew gives the offset of the PE header
    PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((uint8_t *)dos_header + dos_header->e_lfanew);
    if (nt_headers->Signature != IMAGE_NT_SIGNATURE) {
        fwprintf(stderr, L"Invalid PE header (Signature != PE00)\n");
        ret = -3;
        goto cleanup;
    }
    wprintf(L"Found valid PE header\n");

    wprintf(L"\n");
    if (opt_f) { print_file_header(&nt_headers->FileHeader); }
    if (opt_o) { print_optional_header(&nt_headers->OptionalHeader); }
    if (opt_s) {
        print_section_table(IMAGE_FIRST_SECTION(nt_headers),
                            nt_headers->FileHeader.NumberOfSections);
    }

cleanup:
    if (file_mapping_view != NULL)    { UnmapViewOfFile(file_mapping_view); }
    if (file_mapping != NULL)         { CloseHandle(file_mapping); }
    if (file != INVALID_HANDLE_VALUE) { CloseHandle(file); }
    return ret;
}