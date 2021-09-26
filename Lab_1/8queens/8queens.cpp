#include "Tree.hpp"

using namespace std;

int main()
{
    Tree tree;
    tree.getRoot()->getBoard().print();
    cout << "Conflicts: " << tree.getRoot()->getBoard().conflictNumber() << endl << endl << endl;
    tree.IDS();
    return 0;
}