#include "logging/logging.h"

#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "assert.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

void fprint_color(FILE *out, const char *color, const char *text) {
	//check if the programs output is a file
	if(isatty(fileno(out))) {
		fprintf(out, "%s%s%s", color, text, RESET);
	} else {
		fprintf(out, "%s", text);
	}
}

void fprint_tag(FILE *out, const char *color, const char *text) {
	short text_length = strlen(text);
	assert(text_length <= 6 && "Tag name too long.");
	short blank_length = 6 - text_length; 

	fprintf(out, "[");
	fprint_color(out, color, text);
	fprintf(out, "]%*s", blank_length, " ");
}

void vfprint_info(FILE * out, const char *text, va_list args) {
	fprint_tag(out, BLUE, "INFO");
	vfprintf(out, text, args);
}

void fprint_info(FILE * out, const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_info(out, text, args);
	va_end(args);
}

void print_info(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_info(stdout, text, args);
	va_end(args);
}

void println_info(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_info(stdout, text, args);
	va_end(args);
	printf("\n");
}

void vfprint_debug(FILE * out, const char *text, va_list args) {
#ifndef NDEBUG
	fprint_tag(out, GREEN, "DEBUG");
	vfprintf(out, text, args);
#endif
}

void fprint_debug(FILE * out, const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_debug(out, text, args);
	va_end(args);
}

void print_debug(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_debug(stdout, text, args);
	va_end(args);
}

void println_debug(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_debug(stdout, text, args);
	va_end(args);
#ifndef NDEBUG
	printf("\n");
#endif
}

void vfprint_warn(FILE *out, const char *text, va_list args) {
	fprint_tag(out, YELLOW, "WARN");
	vfprintf(out, text, args);
}

void fprint_warn(FILE *out, const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_warn(out, text, args);
	va_end(args);
}

void print_warn(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_warn(stderr, text, args);
	va_end(args);
}

void println_warn(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_warn(stderr, text, args);
	va_end(args);
	printf("\n");
}
void vfprint_error(FILE *out, const char *text, va_list args) {
	fprint_tag(out, RED, "ERROR");
	vfprintf(out, text, args);
}

void fprint_error(FILE *out, const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_error(out, text, args);
	va_end(args);
}

void print_error(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_error(stderr, text, args);
	va_end(args);
}

void println_error(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vfprint_error(stderr, text, args);
	va_end(args);
	printf("\n");
}
