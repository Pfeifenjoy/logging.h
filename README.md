# Logging.h

A small library which implements logging.

E.g:
```
#include "logging/logging.h"

int main(const int argc, const char **argv) {
	debug(0, "42"); // -> [DEBUG] 42
	error("42");    // -> [ERROR] 42
	info("42");     // -> [INFO]  42
	warn("42");     // -> [WARN]  42
}
```

![](https://github.com/Pfeifenjoy/logging.h/blob/master/images/example.gif)
