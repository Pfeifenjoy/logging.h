#ifndef LOGGING_H_LSUOR4FY
#define LOGGING_H_LSUOR4FY

#include "stdarg.h"

typedef unsigned char debug_level;

void vinfo(const char *, va_list);
void info(const char *, ...);

void vwarn(const char *, va_list);
void warn(const char *, ...);

void verror(const char *, va_list);
void error(const char *, ...);

void vdebug(const debug_level, const char *, va_list);
void debug(const debug_level, const char *, ...);

void set_debug_level(debug_level);

#endif /* end of include guard: LOGGING_H_LSUOR4FY */
