#ifndef CHARACTERISTICS_H_INCLUDED
#define CHARACTERISTICS_H_INCLUDED

#include <windows.h>

typedef struct characteristic {
    DWORD value;
    const char *name;
} characteristic_t;

#define GENERATE_CHARACTERISTIC_STRUCT(flag) { flag, #flag },

/// Print characteristics indicated by `value` as a comma-separated list using names from `characteristics` array.
void print_characteristics(DWORD value, const struct characteristic *characteristics, size_t characteristics_len);

#endif // ifndef CHARACTERISTICS_H_INCLUDED
