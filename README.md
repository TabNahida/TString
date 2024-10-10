# TString

TString is a custom C++ string implementation designed for efficient memory management by utilizing a buffer size that is always the closest power of two to the actual string size. This approach optimizes memory usage and provides dynamic growth. The library also includes a `TStringConst` class, which can be used for compile-time string operations, fully leveraging C++20's `constexpr` capabilities.

## Features

- **Dynamic Buffer Management**: Allocates memory with buffer sizes that are powers of two, ensuring efficient memory management and reducing reallocations.
- **String Operations**: Provides common string operations, including concatenation, substring extraction, finding substrings, splitting, and appending.
- **Move Semantics**: Implements both copy and move constructors to efficiently manage resources during object transfers.
- **Compile-time String Support**: `TStringConst` allows compile-time operations for strings using `constexpr` in C++20.
- **Utility Methods**: Includes utility methods such as `clear()`, `empty()`, `split()`, and hash support.
- **User-defined Literals**: Supports the `""_T` user-defined literal for easy creation of `TString` instances.
- **Custom Reserve**: Allows pre-allocation of memory to improve efficiency for operations involving large or frequent modifications.
- **Benchmarking Support**: Includes a benchmark suite comparing `TString` to `std::string` in various scenarios.

## Getting Started

### Prerequisites

- C++20 compatible compiler
- Microsoft Visual Studio, GCC, or Clang
- [xmake](https://xmake.io) build system

### Installation

To use `TString`, clone the repository and include `TString.hpp` in your project:

```sh
# Clone the repository
git clone https://github.com/yourusername/TString.git
```

Include `TString.hpp` in your code:

```cpp
#include "include/TString.hpp"
```

You can also add `TString` as a package through xmake by adding the `TabNahida/repo-xmake` repository:

```lua
add_repositories("tab-repo https://github.com/TabNahida/repo-xmake.git")
add_requires("tstring")
```

Then, include it in your target:

```lua
target("example")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("tstring")
```

### Example Usage

```cpp
#include "TString.hpp"
#include <iostream>

int main() {
    TString myStr = "Hello, ";
    myStr.append("World!");
    std::cout << myStr << std::endl;  // Output: Hello, World!

    TString subStr = myStr.substr(0, 5);
    std::cout << subStr << std::endl;  // Output: Hello

    size_t found = myStr.find("World");
    if (found != TString::npos) {
        std::cout << "Found 'World' at position: " << found << std::endl;
    }

    TString combinedStr = myStr + " Again!";
    std::cout << combinedStr << std::endl;  // Output: Hello, World! Again!

    return 0;
}
```

### Build with xmake

This project uses [xmake](https://xmake.io) to simplify the build process. To build and run tests, use the following commands:

1. Make sure xmake is installed.
2. Navigate to the project root directory.
3. Run the following commands:

```sh
# Configure the project
xmake f -c

# Build the project
xmake

# Run the built target
xmake run Test
```

Here is the `xmake.lua` configuration file used for the project:

```lua
add_languages("cxx20")

target("Test")
    set_kind("binary")
    add_files("src/main.cpp")
    add_includedirs("include")
target_end()
```

## Features in Detail

- **Dynamic Buffer Growth**: The buffer dynamically grows by powers of two, reducing the frequency of memory allocations during string operations.
- **Move Semantics**: The implementation includes move constructors and assignment operators, allowing efficient transfers of resources without unnecessary copies.
- **Compile-time Strings**: `TStringConst` is designed to provide compile-time constant string operations using `constexpr`, enabling compile-time validation and manipulation.
- **Custom Reserve Functionality**: The `reserve` function allows pre-allocating buffer space to prevent frequent reallocations when working with large strings or repeated appending operations.
- **Hash Support**: `TString` can be used in hash containers like `std::unordered_set` and `std::unordered_map` by leveraging the `std::hash` specialization.

## Benchmark Results

`TString` has been benchmarked against `std::string` across various common operations. The benchmark tests include construction, copy, append, substring, and find operations with both short and long strings. Below is a summary of some of the benchmark results:

| Operation                     | TString (ms) | std::string (ms) |
|-------------------------------|--------------|------------------|
| Construction (short string)   | 91           | 245              |
| Construction (long string)    | 173          | 871              |
| Copy (short string)           | 66           | 156              |
| Append (single char)          | 14           | 19               |
| Clear                         | 76           | 109              |
| Find (short string)           | 11           | 30               |
| Find (long string)            | 8            | 14               |
| Substring (short string)      | 71           | 67               |
| Substring (long string)       | 73           | 165              |

Note: The benchmarks were run with default settings on an Intel Core Ultra 5 125H processor with 32GB LPDDR5X 7467MHz memory. The results may vary depending on hardware and compiler optimizations. For some operations, such as finding a substring in very long strings, `TString` and `std::string` may show different performance characteristics due to the algorithms and optimizations used.

## Directory Structure

```
TString/
├── include/
│   └── TString.hpp
├── src/
│   └── main.cpp
├── xmake.lua
└── README.md
```

## Contributing

Contributions are welcome! If you have ideas for improving `TString`, feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License.