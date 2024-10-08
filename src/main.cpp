#include "TString.hpp"

int main()
{
    TString myStr("Hello");
    myStr.print();

    myStr.append(", World!");
    myStr.print();

    myStr.clear();
    std::cout << "After clear, is empty: " << myStr.empty() << std::endl;

    myStr.append("New String");
    myStr.print();

    TString subStr = myStr.substr(0, 3);
    subStr.print();

    size_t found = myStr.find("String");
    std::cout << "Found 'String' at position: " << found << std::endl;

    TString otherStr("Hello");
    myStr += otherStr;
    myStr.print();

    TString combinedStr = myStr + " World Again!";
    combinedStr.print();

    TString anotherCombinedStr = myStr + otherStr;
    anotherCombinedStr.print();

    TString subFromIndex = myStr.substr_from_index(4);
    subFromIndex.print();

    std::vector<TString> parts = combinedStr.split(' ');
    for (const auto &part : parts)
    {
        part.print();
    }

    std::cout << "Buffer size: " << combinedStr.buffer_size() << std::endl;

    constexpr TStringConst constStr("Compile Time String");
    static_assert(constStr.size() == 19, "Unexpected length");
    static_assert(constStr[0] == 'C', "Unexpected character");

    return 0;
}