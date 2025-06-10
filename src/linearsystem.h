#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "matrix.h"
#include "vector.h"
#include <math.h>

class LinearSystem
{
protected:
    int mSize;
    Matrix *mpA;
    Vector *mpb;

    LinearSystem() = delete; // Default constructor

    LinearSystem(LinearSystem const &) {}; // Copy constructor

public:
    // Constructor
    LinearSystem(Matrix *A, Vector *b)
    {
        // Assertion
        assert(A != nullptr && b != nullptr);
        assert(A->row() == b->size()); // Matrix and vector sizes are compatible

        mpA = A;
        mpb = b;
        mSize = A->row();
    }

    // Destructor
    virtual ~LinearSystem() {};

    virtual Vector Solve() const
    {
        Matrix A = *mpA;
        Vector b = *mpb;
        Vector x(A.row());

        if (!A.isSquare()) {
            Matrix A_pinv = A.pseudo_inverse();
            return A_pinv * b;
        }

        assert(A.determinant() != 0);

        // Gaussian Elemination
        for (int i = 1; i <= mSize; i++)
        {
            // Partial pivoting
            int pivotRow = i;
            double pivot = A(pivotRow, i);
            for (int j = i + 1; j <= mSize; j++)
            {
                if (abs(A(j, i)) < pivot)
                {
                    pivotRow = j;
                    pivot = A(j, i);
                }
            }
            if (pivotRow != i)
            {
                A.swapRows(i, pivotRow);
                b.swap(i, pivotRow);
            }

            // Elimination
            for (int j = i + 1; j <= mSize; j++)
            {
                double temp = A(i, i) / A(j, i);
                for (int k = 1; k <= mSize; k++)
                {
                    A(j, k) = A(j, k) * temp - A(i, k);
                }
                x(j) = b(j) * temp - b(i);
            }
        }

        // Back substitution
        for (int i = mSize; i > 0; i--)
        {
            double sum = 0.0;
            for (int j = i + 1; j <= mSize; j++)
            {
                sum += A(i, j) * b(j);
            }
            x(i) = (b(i) - sum) / A(i, i);
        }
        return x;
    }
};

class PosSymLinSystem : public LinearSystem
{
public:
    PosSymLinSystem(Matrix* A, Vector* b) : LinearSystem(A, b) {};

    // Check if the matrix is symmetric
    bool isSymmetric (Matrix A) const
    {
        for (int i = 1; i <= mSize; i++)
        {
            for (int j = i + 1; j <= mSize; j++)
            {
                if ((A(i, j) - A(j, i)) != 0) return false;
            }
        }
        return true;
    }

    virtual Vector Solve() const override // Using conjugate gradient method
    {   
        Matrix A = *mpA;
        assert(isSymmetric(A));

        Vector b = *mpb;
        Vector x(mSize);
        Vector r = b - (A * x);
        Vector p = r;
        
        double oldResidual = r * r;
        

        for (int i = 1; i <= mSize; i++) {
            Vector Ap = A * p;
            
            double alpha = oldResidual / (p * Ap); 
            
            x = x + p * alpha;
            r = r - Ap * alpha;

            double newResidual = r * r;
            if (sqrt(newResidual) < 1.0e-10) break;

            p = r + p * (newResidual/oldResidual);
            oldResidual = newResidual;
        }
        return x;
    }
};

#endif