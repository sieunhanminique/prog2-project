#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cassert>
#include "vector.h"

using namespace std;

class Matrix
{
    int mNumRows, mNumCols;
    double **mData;

    Matrix getMinor(int row, int col) const
    {
        Matrix minor(mNumRows - 1, mNumCols - 1);

        int r = 0;
        for (int i = 0; i < mNumRows; i++)
        {
            if (i == row)
                continue;

            int c = 0;
            for (int j = 0; j < mNumCols; j++)
            {
                if (j == col)
                    continue;
                minor.mData[r][c++] = mData[i][j];
            }
            r++;
        }
        return minor;
    }

    Matrix cofactor() const
    {
        Matrix result(mNumRows, mNumCols);

        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                Matrix minor = getMinor(i, j);
                if ((i + j) % 2 == 0)
                    result.mData[i][j] = minor.determinant();
                else
                    result.mData[i][j] = -minor.determinant();
            }
        }
        return result;
    }

    

public:
    // Constructor
    Matrix() : mNumRows(0), mNumCols(0), mData(nullptr) {}; // Default constructor
    Matrix(int m, int n) : mNumRows(m), mNumCols(n)
    {
        mData = new double *[mNumRows];
        for (int i = 0; i < mNumRows; i++)
        {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; j++)
            {
                mData[i][j] = 0.0;
            }
        }
    }
    Matrix(const Matrix &other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) // Copy constructor
    {
        mData = new double *[mNumRows];
        for (int i = 0; i < mNumRows; i++)
        {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; j++)
            {
                mData[i][j] = other.mData[i][j];
            }
        }
    }

    // Destructor
    ~Matrix()
    {
        for (int i = 0; i < mNumRows; i++)
        {
            delete[] mData[i];
        }
        delete[] mData;
    }

    void display() const
    {
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                cout << mData[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Accessing the number of rows and colomns
    int row() const
    {
        return mNumRows;
    }

    int col() const
    {
        return mNumCols;
    }

    // Check if it is a square matrix
    bool isSquare() const 
    {
        if (mNumCols == mNumRows) return true;
        return false;
    }

    // Swapping rows
    void swapRows(int i, int j)
    {
        double *temp = mData[i - 1];
        mData[i - 1] = mData[j - 1];
        mData[j - 1] = temp;
    }

    Matrix transpose() const
    {
        Matrix transposed(mNumCols, mNumRows);

        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                transposed.mData[j][i] = mData[i][j];
            }
        }
        return transposed;
    }

    // Round bracket overloading
    double& operator()(int m, int n)
    {
        return mData[m - 1][n - 1];
    }

    double operator()(int m, int n) const 
    {
        return mData[m - 1][n - 1];
    }

    // Assignment overloading
    Matrix& operator=(const Matrix &other)
    {
        if (this == &other)
            return *this;

        for (int i = 0; i < mNumRows; i++)
        {
            delete[] mData[i];
        }
        delete[] mData;

        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        mData = new double *[mNumRows];

        for (int i = 0; i < mNumRows; i++)
        {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; j++)
            {
                mData[i][j] = other.mData[i][j];
            }
        }
        return *this;
    }

    // Unary overloading
    Matrix operator-() const
    {
        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                result.mData[i][j] = mData[i][j];
            }
        }
        return result;
    }

    // Binary overloading
    Matrix operator+(const Matrix &other) const // Addition
    {
        // Assertion statement
        assert(mNumRows == other.mNumRows);
        assert(mNumCols == other.mNumCols);

        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                result.mData[i][j] = mData[i][j] + other.mData[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix &other) const // Subtraction
    {
        // Assertion statement
        assert(mNumRows == other.mNumRows);
        assert(mNumCols == other.mNumCols);

        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                result.mData[i][j] = mData[i][j] - other.mData[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix &other) const // Matrix multiplication
    {
        assert(mNumCols == other.mNumRows);

        Matrix result(mNumRows, other.mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < other.mNumCols; j++)
            {
                for (int k = 0; k < mNumCols; k++)
                {
                    result.mData[i][j] += (mData[i][k] * other.mData[k][j]);
                }
            }
        }
        return result;
    }

    Vector operator* (Vector const& v) const // Matrix * Vector
    {
        assert(mNumCols == v.size());

        Vector result(mNumRows);

        for (int i = 1; i <= mNumRows; i++)
        {
            for (int j = 1; j <=mNumCols; j++)
            {
                result(i) += (mData[i-1][j-1] * v(j));
            }
        }
        return result;
        
    }

    Matrix operator*(int n) const // Multiplication of matrices and scalars
    {
        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                result.mData[i][j] = mData[i][j] * n;
            }
        }
        return result;
    }

    // Computing determinant of a given square matrix
    double determinant() const
    {
        assert(mNumCols == mNumRows);

        // Base case
        if (mNumRows == 1)
            return mData[0][0];
        if (mNumRows == 2)
            return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];

        double det = 0.0;
        for (int i = 0; i < mNumCols; i++)
        {
            Matrix minor = getMinor(0, i);
            if (i % 2 == 0)
            {
                det += mData[0][i] * minor.determinant();
            }
            else
                det += -mData[0][i] * minor.determinant();
        }
        return det;
    }

    // Compute the inverse of a given square matrix
    Matrix inverse() const
    {
        assert(mNumCols == mNumRows);

        double det = this->determinant();
        assert(det != 0.0);

        Matrix adj = this->cofactor().transpose();

        Matrix result(mNumRows, mNumCols);

        for (int i = 0; i < mNumRows; i++)
        {
            for (int j = 0; j < mNumCols; j++)
            {
                result.mData[i][j] = adj.mData[i][j] / det;
            }
        }
        return result;
    }

    Matrix pseudo_inverse() const
    {
        Matrix transposeMatrix = this->transpose();
        Matrix result;

        if (mNumRows >= mNumCols) // Full column rank
        {
            Matrix temp = (transposeMatrix * (*this)).inverse();
            result = temp * transposeMatrix;
        }
        else // full row rank
        {
            Matrix temp = ((*this) * transposeMatrix).inverse();
            result = transposeMatrix * temp;
        }

        return result;
    }
};
#endif