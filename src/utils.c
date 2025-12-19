#include "utils.h"

void print_heading(const wchar_t *heading) {
    for (int i = 0; i < 20; ++i) {
        putwchar(L'_');
    }
    wprintf(L"  %s  ", heading);
    // fill line to column 80
    for (int i = 80 - (int)wcslen(heading) - 20 - 4; i > 0; --i) {
        putwchar(L'_');
    }
    putwchar(L'\n');
}
