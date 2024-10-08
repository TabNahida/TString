# TString

TString is a custom C++ string implementation designed for efficient memory management by utilizing a buffer size that is always the closest power of two to the actual string size. This approach optimizes memory usage and provides dynamic growth. The library also includes a `TStringConst` class, which can be used for compile-time string operations, fully leveraging C++20's `constexpr` capabilities.

## Features

- **Dynamic Buffer Management**: Allocates memory with buffer sizes that are powers of two, ensuring efficient memory management and reducing reallocations.
- **String Operations**: Provides common string operations, including concatenation, substring extraction, finding substrings, and splitting.
- **Move Semantics**: Implements both copy and move constructors to efficiently manage resources during object transfers.
- **Compile-time String Support**: `TStringConst` allows compile-time operations for strings using `constexpr` in C++20.
- **Utility Methods**: Includes utility methods such as `clear()`, `empty()`, `split()`, and `print()`.

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

### Example Usage

```cpp
#include "include/TString.hpp"

int main() {
    TString myStr("Hello");
    myStr.print();  // Output: Hello

    myStr.append(", World!");
    myStr.print();  // Output: Hello, World!

    TString subStr = myStr.substr(0, 5);
    subStr.print();  // Output: Hello

    size_t found = myStr.find("World");
    if (found != std::string::npos) {
        std::cout << "Found 'World' at position: " << found << std::endl;
    }

    TString combinedStr = myStr + " Again!";
    combinedStr.print();  // Output: Hello, World! Again!

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
