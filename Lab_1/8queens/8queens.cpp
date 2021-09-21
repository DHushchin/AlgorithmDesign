#include <iostream>
#include "Tree.hpp"

using namespace std;

int main()
{
    Tree tree;
    tree.getRoot()->getBoard().print();
    cout << tree.getRoot()->getBoard().conflictNumber() << endl;
    tree.AStar();
    return 0;
}