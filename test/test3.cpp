#include <iostream>
#include "matrix.h"
#include "vector.h"
#include "linearsystem.h"

void testOverDetermined() {
    std::cout << "\n=== Over-determined system ===\n";
    Matrix A(3, 2);
    A(1,1) = 1; A(1,2) = 1;
    A(2,1) = 1; A(2,2) = 2;
    A(3,1) = 1; A(3,2) = 3;

    Vector b(3);
    b(1) = 6;
    b(2) = 2;
    b(3) = 1;

    LinearSystem ls(&A, &b);
    Vector x = ls.Solve();
    std::cout << "Solution:\n";
    x.display();
}

void testUnderDetermined() {
    std::cout << "\n=== Under-determined system ===\n";
    Matrix A(2, 3);
    A(1,1) = 1; A(1,2) = 2; A(1,3) = 3;
    A(2,1) = 4; A(2,2) = 5; A(2,3) = 6;

    Vector b(2);
    b(1) = 14;
    b(2) = 32;

    LinearSystem ls(&A, &b);
    Vector x = ls.Solve();
    std::cout << "Solution:\n";
    x.display();
}

void testSymmetricPositiveDefinite() {
    std::cout << "\n=== Symmetric Positive-Definite system ===\n";
    Matrix A(2, 2);
    A(1,1) = 4; A(1,2) = 1;
    A(2,1) = 1; A(2,2) = 3;

    Vector b(2);
    b(1) = 1;
    b(2) = 2;

    PosSymLinSystem psls(&A, &b);
    Vector x = psls.Solve();
    std::cout << "Solution:\n";
    x.display();
}

int main() {
    testOverDetermined();
    testUnderDetermined();
    testSymmetricPositiveDefinite();
    
    return 0;
}
