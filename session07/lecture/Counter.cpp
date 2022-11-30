#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <cassert>
#include <climits>

class Counter
{

public:
    // constructor
    Counter() : counter(0)
    {
    }
    Counter(int counter) : counter(counter)
    {
    }
    int get() const
    {
        return counter;
    }
    int increment()
    {
        assert(counter < INT_MAX);
        return ++counter;
    }
    int decrement(){
        assert(counter > INT_MIN);
        return --counter;
    }

private:
    int counter;
};

#endif
