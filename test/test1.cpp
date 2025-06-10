#include <iostream>
#include <cassert>
#include "linearsystem.h"

// Dummy matrix/vector classes for testing if you don't have them
// These should be replaced with your real implementations

int main()
{
    Matrix A(3, 3);
    A(1, 1) = 2;  A(1, 2) = 2;  A(1, 3) = 3;
    A(2, 1) = 2;  A(2, 2) = 3;  A(2, 3) = 1;
    A(3, 1) = 3;  A(3, 2) = 1;  A(3, 3) = 2;

    // Define vector b
    Vector b(3);
    b(1) = 14;
    b(2) = 11;
    b(3) = 13;


    LinearSystem system(&A, &b);
    Vector x = system.Solve();

    std::cout << "x = " << x(1) << ", y = " << x(2) << ", z = " << x(3) << "\n";

    // Expected x = 2, y = 1, z = 3
    assert(std::abs(x(1) - 2.0) < 1e-6);
    assert(std::abs(x(2) - 1.0) < 1e-6);
    assert(std::abs(x(3) - 3.0) < 1e-6);

    return 0;
}
