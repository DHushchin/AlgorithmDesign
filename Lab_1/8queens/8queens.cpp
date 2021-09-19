#include <iostream>
#include "Tree.hpp"

using namespace std;

int main()
{
    Tree tree;
    tree.getNode().getBoard().print();
    cout << tree.getNode().getBoard().conflictNumber() << endl;
    return 0;
}