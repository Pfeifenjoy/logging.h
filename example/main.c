#include "logging/logging.h"

int main(const int argc, const char **argv) {
	println_debug("42"); // -> [DEBUG] 42
	println_error("42");    // -> [ERROR] 42
	println_info("42");     // -> [INFO]  42
	println_warn("42");     // -> [WARN]  42
}
