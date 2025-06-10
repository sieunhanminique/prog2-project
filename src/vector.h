#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

using namespace std;

class Vector
{
    int mSize;
    double *mData;

public:
    // Constructor
    Vector() : mSize(0), mData(nullptr) {}; // Default constructor
    Vector(int size) : mSize(size), mData(new double[size])
    {
        for (int i = 0; i < mSize; ++i)
            mData[i] = 0.0;
    }
    
    Vector(const Vector &other) : mSize(other.mSize), mData(new double[other.mSize])
    { // Copy constructor
        for (int i = 0; i < other.mSize; i++)
        {
            mData[i] = other.mData[i];
        }
    }

    // Destructor
    ~Vector() { delete[] mData; }

    // Display the vector
    void display() const
    {
        for (int i = 0; i < mSize; i++)
        {
            cout << mData[i] << " ";
        };
        cout << endl;
    }

    // Get the size of the vector
    int size() const
    {
        return mSize;
    }

    // Swap
    void swap(int i, int j)
    {
        int temp = mData[i - 1];
        mData[i - 1] = mData[j - 1];
        mData[j - 1] = temp;
    }

    // Assigment overloading
    Vector &operator=(const Vector &other)
    {
        if (this == &other)
            return *this;

        delete[] mData;

        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; i++)
        {
            mData[i] = other.mData[i];
        }
        return *this;
    }

    // Unary overloading
    Vector operator-() const
    {
        Vector result(mSize);
        for (int i = 0; i < mSize; i++)
        {
            result.mData[i] = -mData[i];
        }
        return result;
    }

    // Binary overloading
    Vector operator+(const Vector &other) const // Addition
    {
        if (mSize != other.mSize)
            throw runtime_error("Vector sizes do not match");

        Vector result(mSize);
        for (int i = 0; i < mSize; i++)
        {
            result.mData[i] = mData[i] + other.mData[i];
        }
        return result;
    }

    Vector operator-(const Vector &other) const // subtraction
    {
        if (mSize != other.mSize)
            throw runtime_error("Vector sizes do not match");

        Vector result(mSize);
        for (int i = 0; i < mSize; i++)
        {
            result.mData[i] = mData[i] - other.mData[i];
        }
        return result;
    }

    double operator*(const Vector &other) const // 2 vectors multiplication
    {
        assert(mSize == other.mSize);

        double sum = 0.0;
        for (int i = 0; i < mSize; i++)
        {
            sum += (mData[i] * other.mData[i]);
        }
        return sum;
    }

    Vector operator*(double n) const // Multiplication of vectors and scalars
    {
        Vector result(mSize);
        for (int i = 0; i < mSize; i++)
        {
            result.mData[i] = mData[i] * n;
        }
        return result;
    }

    // Square bracket overload
    bool operator[](int index)
    {
        return (index <= mSize && index > 0);
    }

    // Round bracket overload
    double &operator()(int index)
    {
        return mData[index - 1];
    }

    double operator()(int index) const
    {
        return mData[index - 1];
    }
};

#endif