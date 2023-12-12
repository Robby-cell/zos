#ifndef _PRINT_H_
#define _PRINT_H_

#include <stdarg.h>
#include <stddef.h>

#include "limine.h"

extern void (*limine_print)(const char *buf, size_t size);
/// @brief Halt and Catch Fire
/// @param  
extern void hcf(void);

void putc(char c);
void print_blind(const char *msg);
void _puts(const char *msg);
void _printf(const char *format, ...);

#endif