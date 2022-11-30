#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cassert>
#include <cstdlib>
#include <utility>

class Array
{
public:
    Array() : nof_elements(0), ip(nullptr)
    {
    }
    Array(std::size_t nof_elements) : nof_elements(nof_elements), ip(new int[nof_elements]{}) {}
    Array(const Array &other) : nof_elements(other.nof_elements), ip(new int[nof_elements])
    {
        for (std::size_t i = 0; i < nof_elements; ++i)
        {
            ip[i] = other.ip[i];
        }
    }
    Array(Array &&other) : nof_elements(other.nof_elements), ip(other.ip)
    {
        other.nof_elements = 0;
        other.ip = nullptr;
    }
    ~Array()
    {
        delete[] ip;
    }
    Array &operator=(const Array &other) = delete;
    Array &operator=(Array &&other) = delete;
    std::size_t size() const { return nof_elements; }
    int &operator()(std::size_t i)
    {
        assert(i < nof_elements);
        return ip[i];
    }
    const int &operator()(std::size_t i) const
    {
        assert(i < nof_elements);
        return ip[i];
    }

private:
    std::size_t nof_elements;
    int *ip;
};

#endif