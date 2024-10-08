#ifndef TSTRING_HPP
#define TSTRING_HPP

#include <cmath>
#include <cstring>
#include <iostream>
#include <string>


class TString
{
  private:
    size_t length;
    char *buffer;

    constexpr size_t getClosestPowerOfTwo(size_t size) const
    {
        if (size <= 1)
            return 1;
        size--;
        size |= size >> 1;
        size |= size >> 2;
        size |= size >> 4;
        size |= size >> 8;
        size |= size >> 16;
        size |= size >> 32;
        size++;
        return size;
    }

  public:
    TString(const char *str) : length(strlen(str))
    {
        size_t capacity = getClosestPowerOfTwo(length + 1);
        buffer = new char[capacity];
        std::memcpy(buffer, str, length + 1);
    }

    // New constructor to create TString from a single character
    TString(char ch) : length(1)
    {
        size_t capacity = getClosestPowerOfTwo(length + 1);
        buffer = new char[capacity];
        buffer[0] = ch;
        buffer[1] = '\0';
    }

    // New constructor to create TString from std::string
    TString(const std::string &str) : length(str.size())
    {
        size_t capacity = getClosestPowerOfTwo(length + 1);
        buffer = new char[capacity];
        std::memcpy(buffer, str.c_str(), length + 1);
    }

    TString(const TString &other) : length(other.length)
    {
        size_t capacity = getClosestPowerOfTwo(length + 1);
        buffer = new char[capacity];
        std::memcpy(buffer, other.buffer, length + 1);
    }

    TString(TString &&other) noexcept : length(other.length), buffer(other.buffer)
    {
        other.buffer = nullptr;
        other.length = 0;
    }

    TString &operator=(const TString &other)
    {
        if (this != &other)
        {
            delete[] buffer;
            length = other.length;
            size_t capacity = getClosestPowerOfTwo(length + 1);
            buffer = new char[capacity];
            std::memcpy(buffer, other.buffer, length + 1);
        }
        return *this;
    }

    TString &operator=(TString &&other) noexcept
    {
        if (this != &other)
        {
            delete[] buffer;
            length = other.length;
            buffer = other.buffer;
            other.buffer = nullptr;
            other.length = 0;
        }
        return *this;
    }

    TString &operator=(const std::string &str)
    {
        delete[] buffer;
        length = str.size();
        size_t capacity = getClosestPowerOfTwo(length + 1);
        buffer = new char[capacity];
        std::memcpy(buffer, str.c_str(), length + 1);
        return *this;
    }

    ~TString()
    {
        delete[] buffer;
    }

    size_t size() const
    {
        return length;
    }

    const char *c_str() const
    {
        return buffer;
    }

    size_t buffer_size() const
    {
        return getClosestPowerOfTwo(length + 1);
    }

    void append(const TString &str)
    {
        size_t newLength = length + str.length;
        size_t capacity = getClosestPowerOfTwo(newLength + 1);
        char *newBuffer = new char[capacity];
        std::memcpy(newBuffer, buffer, length);
        std::memcpy(newBuffer + length, str.buffer, str.length + 1);
        delete[] buffer;
        buffer = newBuffer;
        length = newLength;
    }

    void append(const char *str)
    {
        size_t strLength = strlen(str);
        size_t newLength = length + strLength;
        size_t capacity = getClosestPowerOfTwo(newLength + 1);
        char *newBuffer = new char[capacity];
        std::memcpy(newBuffer, buffer, length);
        std::memcpy(newBuffer + length, str, strLength + 1);
        delete[] buffer;
        buffer = newBuffer;
        length = newLength;
    }

    void append(const std::string &str)
    {
        size_t strLength = str.size();
        size_t newLength = length + strLength;
        size_t capacity = getClosestPowerOfTwo(newLength + 1);
        char *newBuffer = new char[capacity];
        std::memcpy(newBuffer, buffer, length);
        std::memcpy(newBuffer + length, str.c_str(), strLength + 1);
        delete[] buffer;
        buffer = newBuffer;
        length = newLength;
    }

    void clear()
    {
        length = 0;
        buffer[0] = '\0';
    }

    bool empty() const
    {
        return length == 0;
    }

    char &operator[](size_t index)
    {
        return buffer[index];
    }

    const char &operator[](size_t index) const
    {
        return buffer[index];
    }

    bool operator==(const TString &other) const
    {
        return std::strcmp(buffer, other.buffer) == 0;
    }

    bool operator!=(const TString &other) const
    {
        return !(*this == other);
    }

    TString &operator+=(const TString &str)
    {
        append(str);
        return *this;
    }

    TString &operator+=(const char *str)
    {
        append(str);
        return *this;
    }

    TString &operator+=(const std::string &str)
    {
        append(str);
        return *this;
    }

    TString operator+(const TString &other) const
    {
        TString result(*this);
        result.append(other);
        return result;
    }

    TString operator+(const char *str) const
    {
        TString result(*this);
        result.append(str);
        return result;
    }

    TString operator+(const std::string &str) const
    {
        TString result(*this);
        result.append(str);
        return result;
    }
};

class TStringConst
{
  private:
    const char *buffer;
    size_t length;

    constexpr size_t const_strlen(const char *str) const
    {
        size_t len = 0;
        while (str[len] != '\0')
        {
            ++len;
        }
        return len;
    }

    constexpr int const_strcmp(const char *str1, const char *str2) const
    {
        size_t i = 0;
        while (str1[i] != '\0' && str2[i] != '\0')
        {
            if (str1[i] != str2[i])
            {
                return (str1[i] < str2[i]) ? -1 : 1;
            }
            ++i;
        }
        if (str1[i] == '\0' && str2[i] == '\0')
        {
            return 0;
        }
        return (str1[i] == '\0') ? -1 : 1;
    }

  public:
    constexpr TStringConst(const char *str) : buffer(str), length(const_strlen(str))
    {
    }

    constexpr size_t size() const
    {
        return length;
    }

    constexpr const char *c_str() const
    {
        return buffer;
    }

    constexpr bool operator==(const TStringConst &other) const
    {
        return const_strcmp(buffer, other.buffer) == 0;
    }

    constexpr bool operator!=(const TStringConst &other) const
    {
        return !(*this == other);
    }

    constexpr char operator[](size_t index) const
    {
        return buffer[index];
    }
};

#endif // TSTRING_HPP