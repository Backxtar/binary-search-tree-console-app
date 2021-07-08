#include <iostream>
#include "BinarySearchTree.h"

int main() {
    std::vector<int> database = Util::initData(10);
    BinarySearchTree<int> tree;

    for (int& i : database)
        tree.ins(i);

    tree.printTree(1);
    std::cout << "--------------------" << std::endl;
    std::cout << tree.getLength() << std::endl;

    system("pause");

    //tree.rotateLeft(1);
    //tree.balance();
    tree.delNode(10);
    tree.printTree(1);
    std::cout << "--------------------" << std::endl;
    std::cout << tree.getLength() << std::endl;
    system("pause");

    /*tree.balance();
    tree.printTree(1);
    std::cout << "--------------------" << std::endl;*/

    std::cout << tree.getRoot()->data << std::endl;
    std::cout << tree.getRoot()->key << std::endl;

    system("pause");
    //std::cout << tree.searchNode(101)->data << std::endl;
    //std::cout << tree.searchNode(1110)->data << std::endl;

    //system("pause");
    return 0;
}
