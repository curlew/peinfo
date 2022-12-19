#include <stdio.h>
#include <windows.h>

/*!
 * \retval  0 Success
 * \retval -1 Error opening file
 */
int wmain(int argc, wchar_t *argv[]) {
    if (argc != 2) {
        wprintf(L"Usage: %s <PE file path>\n", argv[0]);
        return 0;
    }

    const wchar_t *file_path = argv[1];

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

cleanup:
    if (file_mapping_view != NULL)    { UnmapViewOfFile(file_mapping_view); }
    if (file_mapping != NULL)         { CloseHandle(file_mapping); }
    if (file != INVALID_HANDLE_VALUE) { CloseHandle(file); }
    return ret;
}