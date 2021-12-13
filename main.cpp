#include <iostream>
#include "Tree, Stack and Queue.h"
using namespace std;

int main() {
    tree a;
    cout << "Filling the tree with elements" << endl;

    a.insert(33);
    a.insert(20);
    a.insert(34);
    a.insert(14);
    a.insert(35);
    a.insert(16);
    a.insert(24);
    a.insert(22);
    a.insert(26);
    a.insert(15);
    a.insert(17);

    a.remove(20);

    cout << "Deeper traversal of the tree: " << endl;

    Iterator* tree_iterator_stack = a.create_dft_iterator();
    while (tree_iterator_stack->has_next()) {
        cout << tree_iterator_stack->next() << ' ';
    }
    cout << endl;

    cout << "Traversing the tree in breadth: " << endl;

    Iterator* tree_iterator_queue = a.create_bft_iterator();
    while (tree_iterator_queue->has_next()) {
        cout << tree_iterator_queue->next() << ' ';
    }

    return 0;
}