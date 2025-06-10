#include "matrix.h"

int main()
{
    // Test 1: Matrix initialization
    Matrix A(2, 2);
    A(1, 1) = 1;
    A(1, 2) = 2;
    A(2, 1) = 3;
    A(2, 2) = 4;
    cout << "Matrix A: " << endl;
    A.display();

    // Test 2: Operator loading
    Matrix B(2, 2);
    B(1, 1) = 5;
    B(1, 2) = 6;
    B(2, 1) = 7;
    B(2, 2) = 8;

    Matrix C = A + B;
    cout << "A + B: " << endl;
    C.display();

    Matrix D = A * B;
    cout << "A * B:\n";
    D.display();

    // Test 3: Determinant
    cout << "Determinant of A: " << A.determinant() << endl;

    // Test 4: Inverse
    Matrix invA = A.inverse();
    cout << "Inverse matrix of A:" << endl;
    invA.display();

    A(1, 1) = 4;
    A(1, 2) = 7;
    A(2, 1) = 2;
    A(2, 2) = 6;
    Matrix pinvA = A.pseudo_inverse();
    cout << "Pseudo Inverse matrix of A:" << endl;
    pinvA.display();

    return 0;
}