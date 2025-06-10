#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "src/linearsystem.h"

using namespace std;

struct Dataset
{
    Matrix feature;
    Vector target;
};

// Function to load the dataset
void loadDataset(const string &filename, Matrix& feature, Vector& target)
{
    ifstream file(filename);
    string line;
    int rows = 1;

    while (getline(file, line))
    {
        string value;
        stringstream ss(line);

        getline(ss, value, ','); // Vendor name
        getline(ss, value, ','); // Model name

        feature(rows, 1) = 1.0;

        for (int col = 2; col <= 7; col++)
        {
            getline(ss, value, ',');
            feature(rows, col) = stod(value);
        }

        getline(ss, value, ','); // PRP
        target(rows) = stod(value);
        rows++;
    }
}

// Test train split function
pair<Dataset, Dataset> train_test_split(const Dataset& dataset)
{
    int train_size = 209 * 0.8;

    Dataset train;
    train.feature = Matrix(train_size, 7);
    train.target = Vector(train_size);

    Dataset test;
    test.feature = Matrix(209 - train_size, 7);
    test.target = Vector(209 - train_size);

    int train_rows = 1;
    int test_rows = 1;

    srand(time(NULL));
    for (int i = 1; i <= 209; i++)
    {
        if ((double)rand() / RAND_MAX < 0.8 && train_rows <= train_size) // Training set (80%)
        {
            for (int j = 1; j <= 7; j++)
            {
                train.feature(train_rows, j) = dataset.feature(i, j);
            }
            train.target(train_rows) = dataset.target(i);
            train_rows++;
        }
        else
        {
            for (int j = 1; j <= 7; j++)
            {
                test.feature(test_rows, j) = dataset.feature(i, j);
            }
            test.target(test_rows) = dataset.target(i);
            test_rows++;
        }
    }
    return {train, test};
}

Vector LinearRegression(const Dataset& train)
{
    Matrix A = train.feature;
    Vector b = train.target;

    LinearSystem function(&A, &b);

    return function.Solve();
}

Vector prediction(const Matrix& test, const Vector& weights)
{
    return test * weights;
}

double rmseEvaluation(const Vector& predict, const Vector& target)
{   
    double sum = 0.0;
    int size = predict.size();
    for (int i = 1; i <= size; i++)
    {
        double diff = predict(i) - target(i);
        sum += diff*diff;
    }
    double mean = sum / size;
    return sqrt(mean);
}

int main()
{   
    string filename = "dataset/machine.data";

    Dataset dataset;
    dataset.feature = Matrix(209, 7);
    dataset.target = Vector(209);
    loadDataset(filename, dataset.feature, dataset.target);

    auto [train, test] = train_test_split(dataset);

    Vector weights = LinearRegression(train);
    weights.display();
    Vector predict = prediction(test.feature, weights);
    // cout << "prediction: " << endl;
    // predict.display();
    // cout << "\n";
    // cout << "Actual: " << endl;
    // test.target.display();

    double rsme = rmseEvaluation(predict, test.target);

    cout << rsme;
    
    return 0;
}