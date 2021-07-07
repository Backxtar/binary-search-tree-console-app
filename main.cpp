#include <iostream>
#include "BinarySearchTree.h"

int main() {
    std::vector<int> database = Util::initData(10);
    BinarySearchTree<int> tree;

    for (int& i : database)
        tree.ins(i);

    tree.printTree(1);
    std::cout << "--------------------" << std::endl;

    system("pause");

    if (tree.deleteNode(1))
        std::cout << "Success" << std::endl;

    system("pause");

    tree.printTree(1);

    system("pause");

    std::cout << tree.getRoot()->data << std::endl;


    system("pause");
    //std::cout << tree.searchNode(101)->data << std::endl;
    //std::cout << tree.searchNode(1110)->data << std::endl;

    //system("pause");
    return 0;
}
