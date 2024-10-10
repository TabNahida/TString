#include "TString.hpp" // Assuming your TString implementation is in this header
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
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
    const char *longCString =
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        "aaaaaaaaaa";

    // Header for the table output
    std::cout << std::left << std::setw(30) << "Operation" << std::setw(20) << "TString (ms)" << std::setw(20)
              << "std::string (ms)" << "\n";
    std::cout << std::string(70, '-') << "\n";

    // 1. TString and std::string Construction Performance (Short String)
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        TString str(baseCString);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto tStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        std::string str(baseCString);
    }
    end = std::chrono::high_resolution_clock::now();
    auto stdStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::left << std::setw(30) << "Construction (short string)" << std::setw(20) << tStringDuration
              << std::setw(20) << stdStringDuration << "\n";
    if (exportToFile)
    {
        outFile << "  \"Construction_Short\": {\"TString\": " << tStringDuration
                << ", \"StdString\": " << stdStringDuration << "},\n";
    }

    // 2. TString and std::string Construction Performance (Long String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        TString str(longCString);
    }
    end = std::chrono::high_resolution_clock::now();
    tStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        std::string str(longCString);
    }
    end = std::chrono::high_resolution_clock::now();
    stdStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::left << std::setw(30) << "Construction (long string)" << std::setw(20) << tStringDuration
              << std::setw(20) << stdStringDuration << "\n";
    if (exportToFile)
    {
        outFile << "  \"Construction_Long\": {\"TString\": " << tStringDuration
                << ", \"StdString\": " << stdStringDuration << "},\n";
    }

    // 3. TString and std::string Copy Performance
    TString tStrCopySource(baseCString);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        TString tStrCopy(tStrCopySource);
    }
    end = std::chrono::high_resolution_clock::now();
    tStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::string stdStrCopySource(baseCString);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        std::string stdStrCopy(stdStrCopySource);
    }
    end = std::chrono::high_resolution_clock::now();
    stdStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::left << std::setw(30) << "Copy (short string)" << std::setw(20) << tStringDuration
              << std::setw(20) << stdStringDuration << "\n";
    if (exportToFile)
    {
        outFile << "  \"Copy_Short\": {\"TString\": " << tStringDuration << ", \"StdString\": " << stdStringDuration
                << "},\n";
    }

    // 4. TString and std::string Append Performance
    TString tStrAppend(baseCString);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        tStrAppend.append("a");
    }
    end = std::chrono::high_resolution_clock::now();
    tStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::string stdStrAppend(baseCString);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        stdStrAppend += "a";
    }
    end = std::chrono::high_resolution_clock::now();
    stdStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::left << std::setw(30) << "Append (single char)" << std::setw(20) << tStringDuration
              << std::setw(20) << stdStringDuration << "\n";
    if (exportToFile)
    {
        outFile << "  \"Append_Single_Char\": {\"TString\": " << tStringDuration
                << ", \"StdString\": " << stdStringDuration << "},\n";
    }

    // 5. TString and std::string Clear Performance
    TString tStrClear(baseCString);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        tStrClear.clear();
        tStrClear = baseCString;
    }
    end = std::chrono::high_resolution_clock::now();
    tStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::string stdStrClear(baseCString);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        stdStrClear.clear();
        stdStrClear = baseCString;
    }
    end = std::chrono::high_resolution_clock::now();
    stdStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::left << std::setw(30) << "Clear" << std::setw(20) << tStringDuration << std::setw(20)
              << stdStringDuration << "\n";
    if (exportToFile)
    {
        outFile << "  \"Clear\": {\"TString\": " << tStringDuration << ", \"StdString\": " << stdStringDuration
                << "},\n";
    }

    // 6. TString and std::string Find Performance (Short String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        size_t pos = tStrCopySource.find("Z");
    }
    end = std::chrono::high_resolution_clock::now();
    tStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        size_t pos = stdStrCopySource.find("Z");
    }
    end = std::chrono::high_resolution_clock::now();
    stdStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::left << std::setw(30) << "Find (short string)" << std::setw(20) << tStringDuration
              << std::setw(20) << stdStringDuration << "\n";
    if (exportToFile)
    {
        outFile << "  \"Find_Short\": {\"TString\": " << tStringDuration << ", \"StdString\": " << stdStringDuration
                << "},\n";
    }

    // 7. TString and std::string Find Performance (Long String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        size_t pos = tStrAppend.find("a");
    }
    end = std::chrono::high_resolution_clock::now();
    tStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        size_t pos = stdStrAppend.find("a");
    }
    end = std::chrono::high_resolution_clock::now();
    stdStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::left << std::setw(30) << "Find (long string)" << std::setw(20) << tStringDuration << std::setw(20)
              << stdStringDuration << "\n";
    if (exportToFile)
    {
        outFile << "  \"Find_Long\": {\"TString\": " << tStringDuration << ", \"StdString\": " << stdStringDuration
                << "},\n";
    }

    // 8. TString and std::string Substring Performance (Short String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        TString subStr = tStrCopySource.substr(5, 10);
    }
    end = std::chrono::high_resolution_clock::now();
    tStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        std::string subStr = stdStrCopySource.substr(5, 10);
    }
    end = std::chrono::high_resolution_clock::now();
    stdStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::left << std::setw(30) << "Substring (short string)" << std::setw(20) << tStringDuration
              << std::setw(20) << stdStringDuration << "\n";
    if (exportToFile)
    {
        outFile << "  \"Substring_Short\": {\"TString\": " << tStringDuration
                << ", \"StdString\": " << stdStringDuration << "},\n";
    }

    // 9. TString and std::string Substring Performance (Long String)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        TString subStr = tStrAppend.substr(100, 50);
    }
    end = std::chrono::high_resolution_clock::now();
    tStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; ++i)
    {
        std::string subStr = stdStrAppend.substr(100, 50);
    }
    end = std::chrono::high_resolution_clock::now();
    stdStringDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::left << std::setw(30) << "Substring (long string)" << std::setw(20) << tStringDuration
              << std::setw(20) << stdStringDuration << "\n";
    if (exportToFile)
    {
        outFile << "  \"Substring_Long\": {\"TString\": " << tStringDuration << ", \"StdString\": " << stdStringDuration
                << "}\n";
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