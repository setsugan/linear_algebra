#include "linear_algebra/vector.hpp"

int main(void)
{
    linear_algebra::Vector v {10, 10, 10};
    v.print_info();

    v = v / 2;
    v.print_info();
}
