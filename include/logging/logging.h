#ifndef LOGGING_H_SIGO0LBD
#define LOGGING_H_SIGO0LBD

#include "stdio.h"
#include "stdarg.h"

void vfprint_debug(FILE *, const char *, va_list);
void fprint_debug(FILE *, const char *, ...);
void print_debug(const char *, ...);
void println_debug(const char *, ...);

void vfprint_info(FILE *, const char *, va_list);
void fprint_info(FILE *, const char *, ...);
void print_info(const char *, ...);
void println_info(const char *, ...);

void vfprint_warn(FILE *, const char *, va_list);
void fprint_warn(FILE *, const char *, ...);
void print_warn(const char *, ...);
void println_warn(const char *, ...);

void vfprint_error(FILE *, const char *, va_list);
void fprint_error(FILE *, const char *, ...);
void print_error(const char *, ...);
void println_error(const char *, ...);

#endif /* end of include guard: LOGGING_H_SIGO0LBD */
