# TString

TString is a custom string implementation in C++ designed to provide efficient memory management by using a buffer size that is the closest power of two to the actual string size. This allows for optimized memory usage and dynamic growth. Additionally, TString provides a `constexpr` version called `TStringConst`, which can be used for compile-time string operations in C++20.

## Features

- **Dynamic Buffer Allocation**: The buffer size is always set to the closest power of two to ensure efficient memory allocation.
- **String Operations**: Supports common string operations like concatenation, substring extraction, finding substrings, and more.
- **Move Semantics**: Implements both copy and move constructors to support efficient resource management.
- **Compile-time Strings**: `TStringConst` allows compile-time operations with `constexpr` support in C++20.
- **Utility Functions**: Includes utility methods for clearing, checking emptiness, splitting strings, and printing.

## Getting Started

### Prerequisites

- C++20 compatible compiler

### Installation

To use `TString`, simply clone the repository and include the `TString.h` header in your project.

```sh
# Clone the repository
git clone https://github.com/yourusername/TString.git
```

### Example Usage

```cpp
#include "TString.h"

int main() {
    TString myStr("Hello");
    myStr.print();

    myStr.append(", World!");
    myStr.print();

    TString subStr = myStr.substr(0, 5);
    subStr.print();

    size_t found = myStr.find("World");
    if (found != std::string::npos) {
        std::cout << "Found 'World' at position: " << found << std::endl;
    }

    TString combinedStr = myStr + " Again!";
    combinedStr.print();

    return 0;
}
```

### Build

To build your project using `TString`, make sure your compiler is set to C++20.

```sh
g++ -std=c++20 -o example example.cpp
```

## Features in Detail

- **Dynamic Growth**: The buffer dynamically grows in powers of two, minimizing reallocations during appending.
- **Move Semantics**: Move constructors and assignment operators are implemented for efficient resource transfers.
- **Compile-time Strings**: `TStringConst` enables the use of `constexpr` to perform compile-time checks and string manipulations.

## Contributing

Contributions are welcome! If you have ideas for improving `TString`, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License.


