# The Tiny Project
This project is an exercise of **Programming 2 Course**, practicing implementing OOP using C++. It includes 2 parts to build a program to solve a system of linear equations.
## Part A
Vector, Matrix, and LinearSystem classes are built in order to solve a linear system equation: **Ax = b**. They are written in .h files and tested.

Vector class:
- Operator overload

Matrix class:
- Operator overload
- Methods for accessing number of rows and columns
- Methods for computing the determinant and inverse of a square matrix
- Methods for computing the pseudo-inverse of a matrix

LinearSystem class:
- Using Gaussian Elimination algorithm to solve a system linear equations
- Deriving PosSymLinSystem from LinearSystem class

## Part B
[Dataset](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware) is downloaded and divided into 2 sets, training set (80%) and validation set (20%) using a `train_test_split` function. There are 209 instances, each has 10 features:
- vendor name
- Model Name: many unique symbols
- MYCT: machine cycle time in nanoseconds (integer)
- MMIN: minimum main memory in kilobytes (integer)
- MMAX: maximum main memory in kilobytes (integer)
- CACH: cache memory in kilobytes (integer)
- CHMIN: minimum channels in units (integer)
- CHMAX: maximum channels in units (integer)
- PRP: published relative performance (integer)
- ERP: estimated relative performance from the original article (integer)

**Linear Regression model:** PRP=x1*MYCT+ x2*MMIN+ x3*MMAX+ x4*CACH+ x5*CHMIN+ x6*CHMAX

**Root Square Mean Error (RMSE)** is used to measure the differences between true and predicted values.

![](https://c3.ai/wp-content/uploads/2020/11/Screen-Shot-2020-11-10-at-8.06.16-AM-500x159.png)

