#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Matrix
{
private:
    char** matr; 
    int size; 

public:
    Matrix()
    {
        size = 8;
        matr = new char* [size];
        for (int i = 0; i < size; i++)
        {
            matr[i] = new char[size];
        }

        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                matr[i][j] = '0';
            }
        }
    }

    Matrix(const Matrix& Matr)
    {
        size = Matr.size;

        matr = new char* [size];

        for (int i = 0; i < size; i++)
            matr[i] = new char[size];

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                matr[i][j] = Matr.matr[i][j];
    }

    char getIndex(int i, int j)
    {
        try
        {
            if ((0 <= i < size) && (0 <= j < size))
                return matr[i][j];
            throw "Getting matrix index out of range";
        }
        catch (const char* exception)
        {
            std::cerr << "Error: " << exception << '\n';
        }
    }

    void setIndex(int i, int j, char value)
    {
        try
        {
            if ((0 <= i < size) && (0 <= j < size))
                matr[i][j] = value;
            else
                throw "Setting matrix index out of range";
        }
        catch (const char* exception)
        {
            std::cerr << "Error: " << exception << '\n';
        }
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << setw(3) << matr[i][j];
            }
            cout << endl;
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < size; i++)
        {
            delete[] matr[i];
        }
    }
};
