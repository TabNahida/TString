#include "TString.hpp"

#include <iostream>

int main()
{
    TString myStr("Hello");
    std::puts(myStr);

    myStr.append(", World!");
    std::puts(myStr);

    myStr.clear();
    std::cout << "After clear, is empty: " << myStr.empty() << std::endl;

    myStr.append("New String");
    std::puts(myStr);

    TString subStr = myStr.substr(0, 3);
    std::puts(myStr);

    size_t found = myStr.find("String");
    std::cout << "Found 'String' at position: " << found << std::endl;

    TString otherStr("Hello");
    myStr += otherStr;
    std::puts(myStr);

    TString combinedStr = myStr + " World Again!";
    std::puts(combinedStr);

    TString anotherCombinedStr = myStr + otherStr;
    std::puts(anotherCombinedStr);

    TString subFromIndex = myStr.substr(4);
    std::puts(subFromIndex);

    std::vector<TString> parts = combinedStr.split(' ');
    for (const auto &part : parts)
    {
        std::puts(part);
    }

    std::cout << "Buffer size: " << combinedStr.buffer_size() << std::endl;

    constexpr TStringConst constStr("Compile Time String");
    static_assert(constStr.size() == 19, "Unexpected length");
    static_assert(constStr[0] == 'C', "Unexpected character");

    return 0;
}