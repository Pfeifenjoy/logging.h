[![Build Status](https://drone.metthub.de/api/badges/Pfeifenjoy/logging.h/status.svg)](https://drone.metthub.de/Pfeifenjoy/logging.h)

# Logging.h

A small library which implements logging.

E.g:
```
#include "logging/logging.h"

int main(const int argc, const char **argv) {
	println_debug("42");    // -> [DEBUG] 42
	println_error("42");    // -> [ERROR] 42
	println_info("42");     // -> [INFO]  42
	println_warn("42");     // -> [WARN]  42
}
```

![](https://github.com/Pfeifenjoy/logging.h/blob/master/images/example.gif)
