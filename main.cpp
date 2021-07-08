#include <iostream>
#include <sstream>
#include "BinarySearchTree.h"

int main(int argc, char* argv[]) {
    std::string args = "Program started with " + std::to_string(argc) + " ";
    argc > 1 ? args += "arguments" : args += "argument.";
    std::cout << args << std::endl << std::endl;

    std::vector<int> database;
    BinarySearchTree<int> tree;
    bool stop = false;

    while (!stop)
    {
        int tmp;
        std::string input;
        std::stringstream strStream;

        strStream   << ">> Main Menu | You can choose one of the following options <<" << std::endl
                    << "-------------------------------------------------------------" << std::endl
                    << "(1) >> init(amount) > init tree with amount of rand nodes" << std::endl
                    << "(2) >> getLength() > tree's nodes" << std::endl
                    << "(3) >> getRoot() > tree's root node" << std::endl
                    << "(4) >> getCurrent() > tree's current node" << std::endl
                    << "(5) >> searchNode(key) > get mode with key" << std::endl
                    << "(6) >> ins(data) > add node with data to tree" << std::endl
                    << "(7) >> del(key) > delete node with key from tree" << std::endl
                    << "(8) >> clear() > wipe tree" << std::endl
                    << "(9) >> rotateLeft(key) > rotate tree left around node" << std::endl
                    << "(10) > rotateRight(key) > rotate tree right around node" << std::endl
                    << "(11) > balance() > balance tree" << std::endl
                    << "(12) > print(mode) > print tree (pre-, in-, post-order)" << std::endl
                    << "(13) > EXIT" << std::endl;
        std::cout << strStream.str() << std::endl;
        std::cout << "Input >> ";
        std::cin >> input;

        if (!Util::isDigit(input) || std::stoi(input) < 1 || std::stoi(input) > 13)
        {
            std::cout << "Invalid argument. Try again." << std::endl;
            continue;
        }

        try {
            switch (std::stoi(input)) {
                case 1 :    std::cout << "How many rands:" << std::endl << std::endl;
                            std::cout << "Input >> ";
                            input.clear();
                            std::cin >> input;

                            if (!Util::isDigit(input)) {
                                std::cout << "Invalid argument. Try again." << std::endl;
                                continue;
                            }
                            database = Util::initData(std::stoi(input));

                            for (int &i : database)
                                tree.ins(i);
                            std::cout << "Added " << input << " nodes." << std::endl;
                            break;

                case 2 :    std::cout << "Elements: " << tree.getLength() << std::endl;
                            break;

                case 3 :    std::cout << "Root-Key: " << tree.getRoot()->key << std::endl;
                            std::cout << "Root-Data: " << tree.getRoot()->data << std::endl;
                            break;

                case 4 :    std::cout << "Current Node-Key: " << tree.getCurrent()->key << std::endl;
                            std::cout << "Current Node-Data: " << tree.getCurrent()->data << std::endl;
                            break;

                case 5 :    std::cout << "Insert key:" << std::endl << std::endl;
                            std::cout << "Input >> ";
                            input.clear();
                            std::cin >> input;

                            if (!Util::isDigit(input)) {
                                std::cout << "Invalid argument. Try again." << std::endl;
                                continue;
                            }
                            std::cout << "Node-Key: " << tree.searchNode(std::stoi(input))->key << std::endl;
                            std::cout << "Node-Data: " << tree.searchNode(std::stoi(input))->data << std::endl;
                            break;

                case 6 :    std::cout << "Insert Node with data:" << std::endl;
                            input.clear();
                            std::cin >> input;

                            if (!Util::isDigit(input)) {
                                std::cout << "Invalid argument. Try again." << std::endl;
                                continue;
                            }
                            tmp = std::stoi(input);
                            tree.ins(tmp);
                            std::cout << "Inserted node with data: " << tmp << std::endl;
                            break;

                case 7 :    std::cout << "Insert key:" << std::endl << std::endl;
                            std::cout << "Input >> ";
                            input.clear();
                            std::cin >> input;

                            if (!Util::isDigit(input)) {
                                std::cout << "Invalid argument. Try again." << std::endl;
                                continue;
                            }
                            tree.delNode(std::stoi(input));
                            std::cout << "Node deleted." << std::endl;
                            break;

                case 8 :    tree.clear();
                            break;

                case 9 :    std::cout << "Insert key:" << std::endl << std::endl;
                            std::cout << "Input >> ";
                            input.clear();
                            std::cin >> input;

                            if (!Util::isDigit(input)) {
                                std::cout << "Invalid argument. Try again." << std::endl;
                                continue;
                            }
                            tree.rotateLeft(std::stoi(input));
                            std::cout << "Tree rotated around " << input << std::endl;
                            break;

                case 10 :   std::cout << "Insert key:" << std::endl << std::endl;
                            std::cout << "Input >> ";
                            input.clear();
                            std::cin >> input;

                            if (!Util::isDigit(input)) {
                                std::cout << "Invalid argument. Try again." << std::endl;
                                continue;
                            }
                            tree.rotateRight(std::stoi(input));
                            std::cout << "Tree rotated around " << input << std::endl;
                            break;

                case 11 :   tree.balance();
                            break;

                case 12 :   std::cout << ">> Choose mode <<" << std::endl;
                            std::cout << "-----------------" << std::endl;
                            std::cout << "(1) Pre order" << std::endl;
                            std::cout << "(2) In order" << std::endl;
                            std::cout << "(3) Post order" << std::endl;
                            std::cout << "Input >> ";
                            input.clear();
                            std::cin >> input;

                            if (!Util::isDigit(input) || std::stoi(input) < 1 || std::stoi(input) > 3) {
                                std::cout << "Invalid argument. Try again." << std::endl;
                                continue;
                            }

                            if (std::stoi(input) == 1)
                                tree.printTree(1);
                            else if (std::stoi(input) == 2)
                                tree.printTree(2);
                            else if (std::stoi(input) == 3)
                                tree.printTree(3);
                            break;
                default :   stop = true;
            }
        } catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        system("pause");
        system("cls");
    }
    return 0;
}
