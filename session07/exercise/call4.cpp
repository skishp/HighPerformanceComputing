#include "printf.hpp" /* needed for fmt::printf */

void f(int &val)
{
    val = val + 1;
}

int main()
{
    int i = 1;
    f(i);
    fmt::printf("i = %d\n", i); /* now 2 */
}