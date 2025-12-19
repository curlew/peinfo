#include "characteristics.h"

#include <stdio.h>
#include <stdbool.h>

void print_characteristics(DWORD value, const struct characteristic *characteristics, size_t characteristics_len) {
    bool is_first_flag = true;

    for (size_t i = 0; i < characteristics_len; ++i) {
        if (characteristics[i].value & value) {
            if (is_first_flag) {
                is_first_flag = false;
            } else {
                wprintf(L", ");
            }
            wprintf(L"%S", characteristics[i].name);
        }
    }
}
