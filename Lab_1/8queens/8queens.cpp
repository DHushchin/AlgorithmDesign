#include "Tree.hpp"

using namespace std;

int main()
{
    Tree tree;
    cout << "Initial state: " << endl;
    tree.getRoot()->getBoard().print();
    cout << "Conflicts: " << tree.getRoot()->getBoard().conflictNumber() << endl << endl << endl;
    cout << "Result state: " << endl;
    tree.IDS();
    return 0;
}