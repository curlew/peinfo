#include "data_directories.h"
#include "file_header.h"
#include "optional_header.h"
#include "section_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

typedef struct arguments {
    bool f, o, s, i, e;
    wchar_t *file;
} arguments_t;

static void print_usage(wchar_t *exe);
static arguments_t parse_arguments(int argc, wchar_t *argv[]);

/*!
 * \retval  0 Success
 * \retval -1 Error opening file
 * \retval -2 File is invalid (bad DOS header)
 * \retval -3 File is invalid (bad PE header)
 */
int wmain(int argc, wchar_t *argv[]) {
    arguments_t args = parse_arguments(argc, argv);

    int ret = 0;
    // variables defined here so cleanup label can be jumped to from anywhere
    HANDLE file      = INVALID_HANDLE_VALUE;
    LPVOID file_base = NULL;

    file = CreateFileW(args.file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) {
        fwprintf(stderr, L"Error opening \"%s\"\n", args.file);
        ret = -1;
        goto cleanup;
    }
    DWORD file_size = GetFileSize(file, NULL);

    file_base = VirtualAlloc(NULL, file_size, MEM_COMMIT, PAGE_READWRITE);
    if (file_base == NULL) {
        fputws(L"Error allocating space for file", stderr);
        ret = -1;
        goto cleanup;
    }

    if (ReadFile(file, file_base, file_size, NULL, NULL) == FALSE) {
        fputws(L"Error reading file", stderr);
        ret = -1;
        goto cleanup;
    }

    CloseHandle(file);


    PIMAGE_DOS_HEADER dos_header = (PIMAGE_DOS_HEADER)file_base;
    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
        fputws(L"Invalid DOS header (e_magic != MZ)", stderr);
        ret = -2;
        goto cleanup;
    }

    // e_lfanew gives the offset of the PE header
    PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)((uint8_t *)dos_header + dos_header->e_lfanew);
    if (nt_headers->Signature != IMAGE_NT_SIGNATURE) {
        fputws(L"Invalid PE header (Signature != PE00)", stderr);
        ret = -3;
        goto cleanup;
    }

    if (args.f) {
        print_file_header(&nt_headers->FileHeader);
    }
    if (args.o) {
        print_optional_header(&nt_headers->OptionalHeader);
    }
    if (args.s) {
        print_section_table(IMAGE_FIRST_SECTION(nt_headers),
                            nt_headers->FileHeader.NumberOfSections);
    }
    if (args.i) {
        print_import_table(file_base);
    }
    if (args.e) {
        print_export_table(file_base);
    }

cleanup:
    if (file_base != NULL)            { VirtualFree(file_base, 0, MEM_RELEASE); }
    if (file != INVALID_HANDLE_VALUE) { CloseHandle(file); }
    return ret;
}

void print_usage(wchar_t *exe) {
    wprintf(L"Usage: %s [options] FILE\n", exe);
    _putws(L"View headers and sections of Portable Executable files.\n"
           L"\n"
           L"Options:\n"
           L"  -f  Display file header\n"
           L"  -o  Display optional header\n"
           L"  -s  Display section table\n"
           L"  -i  Display import table\n"
           L"  -e  Display export table\n"
           L"  -h  Display this help message and exit\n"
           L"\n"
           L"If no options are specified, display all available information.");
}

arguments_t parse_arguments(int argc, wchar_t *argv[]) {
    arguments_t args = {0};

    for (int i = 1, operand_count = 0; i < argc; ++i) {
        if (argv[i][0] == L'-') {
            // option
            for (wchar_t *c = argv[i] + 1; *c; ++c) {
                switch (*c) {
                case L'f': args.f = true; break;
                case L'o': args.o = true; break;
                case L's': args.s = true; break;
                case L'i': args.i = true; break;
                case L'e': args.e = true; break;
                case L'h':
                    print_usage(argv[0]);
                    exit(0);
                default:
                    wprintf(L"Invalid option - \"%c\"\n\n", *c);
                    print_usage(argv[0]);
                    exit(0);
                }
            }
        } else {
            // operand (non-option argument)
            if (++operand_count > 1) {
                print_usage(argv[0]);
                exit(0);
            }
            args.file = argv[i];
        }
    }

    if (!args.file) {
        wprintf(L"No file specified\n\n");
        print_usage(argv[0]);
        exit(0);
    }
    if (!(args.f || args.o || args.s || args.i || args.e)) {
        // default options
        args.f = args.o = args.s = args.i = args.e = true;
    }

    return args;
}
