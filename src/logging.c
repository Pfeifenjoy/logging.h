#include "logging/logging.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "assert.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

#define MAX_LABEL_WIDTH 8

debug_level current_debug_level = 0;

char *scolor(FILE *out, const char *color, const char *text) {
	char *result;
	size_t length;

	//check if the programs output is a file
	if(isatty(fileno(out))) {
		length = strlen(color) + strlen(text) + strlen(RESET) + 1;
		result = malloc(length * sizeof(char));
		snprintf(result, length, "%s%s%s", color, text, RESET);
	} else {
		length = strlen(text) + 1;
		result = malloc(length * sizeof(char));
		snprintf(result, length, "%s", text);
	}

	result[length - 1] = 0;
	return result;
}

char *printr(char c, size_t n) {
	char *result = malloc((n + 1) * sizeof(char));
	for(size_t i = 0; i < n; ++i) {
		result[i] = c;
	}
	result[n] = 0;
	return result;
}

char *make_label(FILE *out, const char *color, const char *name) {
	assert(strlen(name) <= MAX_LABEL_WIDTH);

	char *colored_name = scolor(out, color, name);
	char *space =  printr(' ', MAX_LABEL_WIDTH - strlen(name));

	size_t length = MAX_LABEL_WIDTH + strlen("[") + strlen("] ") + 1;
	char *result = (char *) malloc(length * sizeof(char));
	snprintf(result, length, "[%s]%s ", colored_name, space);
	result[length - 1] = 0;

	free(colored_name);
	free(space);

	return result;
}

void vlog(
		FILE *out,
		const char *label_text,
		const char *color,
		const char *text,
		va_list args
	) {

	//label
	char *label = make_label(out, color, label_text);

	//create format
	size_t format_length = strlen(label) + strlen(text) + 2;
	char *format = (char *) malloc(format_length * sizeof(char));
	snprintf(format, format_length, "%s%s\n", label, text);
	format[format_length - 1] = 0;

	//print
	vfprintf(out, format, args);

	free(label);
	free(format);
}

void vinfo(const char *text, va_list args) {
	vlog(stdout, "INFO", BLUE, text, args);
}
void info(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vinfo(text, args);
	va_end(args);
}

void vwarn(const char *text, va_list args) {
	vlog(stderr, "WARN", YELLOW, text, args);
}

void warn(const char *text, ...) {
	va_list args;
	va_start(args, text);
	vwarn(text, args);
	va_end(args);
}

void verror(const char *formatting, va_list args) {
	vlog(stderr, "ERROR", RED, formatting, args);
}

void error(const char *text, ...) {
	va_list args;
	va_start(args, text);
	verror(text, args);
	va_end(args);
}

void vdebug(const debug_level level, const char *text, va_list args) {
    if(level <= current_debug_level) {
		vlog(stdout, "DEBUG", GREEN, text, args);
	}

}

void debug(const debug_level level, const char *text, ...) {
    va_list args;
    va_start(args, text);
	vdebug(level, text, args);
    va_end(args);
}

void set_debug_level(debug_level level) {
    current_debug_level = level;
}
