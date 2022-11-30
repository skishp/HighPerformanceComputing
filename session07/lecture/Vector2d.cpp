#include <iostream>

class Vector2D
{
public:
    double x, y;
};

void print_point(Vector2D v)
{
    std::cout << "(" << v.x << ", " << v.y << ")";
}

Vector2D add_vectors(Vector2D v, Vector2D w)
{
    Vector2D result;
    result.x = v.x + w.x;
    result.y = v.y + w.y;
    return result;
}

void scale_vector(Vector2D *v, double factor)
{
    v ->x *= factor;
    v ->y *= factor;
}

int main()
{
    Vector2D a;
    a.x = 1;
    a.y = 2;

    Vector2D b;
    b.x = 0;
    b.y = 2;

    Vector2D c = add_vectors(a, b);
    print_point(c);
    std::cout << std::endl;
    scale_vector(&c, 4);
    print_point(c);
    std::cout << std::endl;
}