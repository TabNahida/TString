#include "TString.hpp" // Assuming your TString implementation is in this header
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

void printUsage()
{
    std::cout << "Usage: program_name [OPTIONS]\n";
    std::cout << "Options:\n";
    std::cout << "  -e, --export         Export results to a file (default: false)\n";
    std::cout << "  -i, --iterations N   Set the number of iterations for the test (default: 1000000)\n";
    std::cout << "  -h, --help           Display this help message\n";
}

void performanceTest(bool exportToFile, int numIterations)
{
    std::ofstream outFile;
    if (exportToFile)
    {
        outFile.open("tstring_performance_results.json");
        if (!outFile.is_open())
        {
            std::cerr << "Failed to open file for writing test results." << std::endl;
            return;
        }
        outFile << "{\n";
    }

    // Test data
    const char *baseCString = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    TString baseString(baseCString);
    TString longString;
    longString.reserve(10000);
    for (int i = 0; i < 10000; ++i)
    {
        longString += 'a';
    }

    // 1. TString Construction Performance (Short String)
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        TString str(baseCString);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Construction of TString (short string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"TString_Construction_Short\": " << duration << ",\n";
    }

    // TString Construction Performance (Long String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        TString str(longString.c_str());
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Construction of TString (long string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"TString_Construction_Long\": " << duration << ",\n";
    }

    // std::string Construction Performance (Short String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        std::string str(baseCString);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Construction of std::string (short string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"StdString_Construction_Short\": " << duration << ",\n";
    }

    // std::string Construction Performance (Long String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        std::string str(longString.c_str());
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Construction of std::string (long string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"StdString_Construction_Long\": " << duration << ",\n";
    }

    // 2. TString Find Performance (Short String)
    TString tStrShort(baseCString);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        size_t pos = tStrShort.find("Z");
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Find operation in TString (short string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"TString_Find_Short\": " << duration << ",\n";
    }

    // TString Find Performance (Long String)
    TString tStrLong(longString.c_str());
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        size_t pos = tStrLong.find("a");
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Find operation in TString (long string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"TString_Find_Long\": " << duration << ",\n";
    }

    // std::string Find Performance (Short String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        size_t pos = std::string(baseCString).find("Z");
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Find operation in std::string (short string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"StdString_Find_Short\": " << duration << ",\n";
    }

    // std::string Find Performance (Long String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        size_t pos = std::string(longString.c_str()).find("a");
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Find operation in std::string (long string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"StdString_Find_Long\": " << duration << ",\n";
    }

    // 3. TString Substring Performance (Short String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        TString subStr = tStrShort.substr(5, 10);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Substring operation in TString (short string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"TString_Substring_Short\": " << duration << ",\n";
    }

    // TString Substring Performance (Long String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        TString subStr = tStrLong.substr(100, 50);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Substring operation in TString (long string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"TString_Substring_Long\": " << duration << ",\n";
    }

    // std::string Substring Performance (Short String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        std::string subStr = std::string(baseCString).substr(5, 10);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Substring operation in std::string (short string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"StdString_Substring_Short\": " << duration << ",\n";
    }

    // std::string Substring Performance (Long String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        std::string subStr = std::string(longString.c_str()).substr(100, 50);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Substring operation in std::string (long string) took: " << duration << " ms\n";
    if (exportToFile)
    {
        outFile << "  \"StdString_Substring_Long\": " << duration << "\n";
    }

    if (exportToFile)
    {
        outFile << "}\n";
        outFile.close();
        std::cout << "Performance test completed. Results saved to tstring_performance_results.json" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    bool exportToFile = false;
    int numIterations = 1000000;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--export") == 0 || strcmp(argv[i], "-e") == 0)
        {
            exportToFile = true;
        }
        else if ((strcmp(argv[i], "--iterations") == 0 || strcmp(argv[i], "-i") == 0) && i + 1 < argc)
        {
            numIterations = std::atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
        {
            printUsage();
            return 0;
        }
        else
        {
            printUsage();
            return 1;
        }
    }

    performanceTest(exportToFile, numIterations);
    return 0;
}