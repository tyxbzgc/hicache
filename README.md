# hicache

Hicache is C++ framework for cache. (Inspired by Golang go-cache)

# example

```
#include <iostream>
#include "cache/cache.h"
int main() {
    std::cout << "run" << std::endl;
    hicache::Cache<std::string, int>* ca = new hicache::Cache<std::string, int>(1000, 2000);
    ca->Set("a", 1);
    ca->Set("b", 2);
    ca->Print();
}
```

# How to Build

If you just want to use, copy the cache/*.h and include it.

# Requirements

- C++ compiler with good C++11 support
- CMake for build example

# Building for Examples

```
mkdir build
cd build
cmake ..
make
```

