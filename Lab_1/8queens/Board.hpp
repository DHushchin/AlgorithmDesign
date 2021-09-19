#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Board
{
private:
    vector<vector<char>> matr; 
    int size; 
private:
    bool correctIndex(int i, int j);
public:
    Board();
    Board(const Board& Matr);
    void generateQueens();
    char getIndex(int i, int j);
    void setIndex(int i, int j, char value);
    void print();
    int getSize();
    int conflictNumber();
    int getConflict(int i, int j);
    void moveFigure(int i);
};
