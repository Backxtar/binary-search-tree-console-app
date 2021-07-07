//
// Created by joerg on 01.07.2021.
//

#ifndef P5_CLION_BINARYSEARCHTREE_H
#define P5_CLION_BINARYSEARCHTREE_H
#include "Node.h"
#include "Util.h"
#include <sstream>

template<typename T>
class BinarySearchTree
{
private:
    Node<T>*    root; // Root element
    Node<T>*    current; // Current element
    int         length; // Elements

    bool ins(T& data, Node<T>* node)
    {
        if (data < node->data) {
            if (empty(node->c_left))
                return insLeft(node, data);
            else ins(data, node->c_left);
        }
        else if (data >= node->data) {
            if (empty(node->c_right))
                return insRight(node, data);
            else ins(data, node->c_right);
        }
    }

    bool insRoot(T& data) // Insert root element
    {
        if (!empty(root))
            throw std::invalid_argument("Error in insRoot(): Node already exists.");

        root        = new Node<T>;
        root->key   = 1;
        root->data  = data;
        current     = root;
        length++;

        return true;
    }

    bool insLeft(Node<T>* parent, T& data) // Insert left child of parent
    {
        if (empty(root) || empty(parent))
            throw std::out_of_range("Error in insLeft(): Node is a nullptr.");
        if (!empty(parent->c_left))
            throw std::invalid_argument("Error in insLeft(): Node already exists.");

        auto* child     = new Node<T>;
        child->key      = parent->key * 10;
        child->data     = data;
        child->parent   = parent;
        parent->c_left  = child;
        current         = child;
        length++;

        return true;
    }

    bool insRight(Node<T>* parent, T& data) // Insert right child of parent
    {
        if (empty(root) || empty(parent))
            throw std::out_of_range("Error in insLeft(): Node is a nullptr.");
        if (!empty(parent->c_right))
            throw std::invalid_argument("Error in insLeft(): Node already exists.");

        auto* child     = new Node<T>;
        child->key      = (parent->key * 10) + 1;
        child->data     = data;
        child->parent   = parent;
        parent->c_right = child;
        current         = child;
        length++;

        return true;
    }

    void printPreOrder(Node<T>* node, std::string str) // Print pre order
    {
        if (empty())
        {
            std::cout << "Tree is empty!" << std::endl;
            return;
        }

        std::cout << str << node->key << ": " << node->data << std::endl;
        //str += "| ";

        if (!empty(node->c_left))
            printPreOrder(node->c_left, str + "| ");
        if (!empty(node->c_right))
            printPreOrder(node->c_right, str + "| ");
    }

    void printInOrder(Node<T>* node, std::string str) // Print in order
    {
        if (empty())
        {
            std::cout << "Tree is empty!" << std::endl;
            return;
        }

        if (!empty(node->c_left))
            printInOrder(node->c_left, str + "| ");

        std::cout << str << node->key << ": " << node->data << std::endl;

        if (!empty(node->c_right))
            printInOrder(node->c_right, str + "| ");
    }

    void printPostOrder(Node<T>* node, std::string str) // Print post order
    {
        if (empty())
        {
            std::cout << "Tree is empty!" << std::endl;
            return;
        }

        if (!empty(node->c_left))
            printPostOrder(node->c_left, str + "| ");
        if (!empty(node->c_right))
            printPostOrder(node->c_right, str + "| ");

        std::cout << str << node->key << ": " << node->data << std::endl;
    }

    unsigned int getLayers(Node<T>* node, unsigned int height = 0) // Get layers of the tree
    {
        unsigned int hLeft = 0, hRight = 0;
        ++height;

        if (empty(node->c_left) && empty(node->c_right))
            return height;

        if (!empty(node->c_left))
            hLeft   = getLayers(node->c_left, height);
        if (!empty(node->c_right))
            hRight  = getLayers(node->c_right, height);

        return hLeft >= hRight ? hLeft : hRight;
    }

    Node<T>* searchNode(Node<T>* node, const long key) // Search node by key
    {
        Node<T>* result_l = nullptr;
        Node<T>* result_r = nullptr;

        if (node->key == key)
            return node;

        if (!empty(node->c_left))
            result_l = searchNode(node->c_left, key);
        if (!empty(node->c_right))
            result_r = searchNode(node->c_right, key);

        if (!empty(result_l)) return result_l;
        else if (!empty(result_r)) return result_r;
        else return nullptr;
    }

    void deleteNode(Node<T>* node) // Delete single Node
    {
        Node<T>* pNode   = node->parent;
        Node<T>* lChild  = node->c_left;
        Node<T>* rChild  = node->c_right;

        if (empty(lChild) && empty(rChild) && !empty(node))
        {
            delete node;
            length--;
            return;
        }

        if(!empty(pNode))
        {
            if(empty(lChild))
            {
                if(pNode->c_left == node)
                    pNode->c_left = rChild;
                else pNode->c_right = rChild;
                return;
            }

            lChild->parent = pNode;
            if(pNode->c_left == node)
                pNode->c_left = lChild;
            else pNode->c_right = lChild;
        }
        else
        {
            if(empty(lChild))
            {
                root = rChild;
                if(!empty(rChild))
                    rChild->parent = nullptr;
                return;
            }
            lChild->parent = nullptr;
            root = lChild;
        }

        delete node;
        node = lChild;

        while (true)
        {
            if (empty(node->c_right))
                break;
            node = node->c_right;
        }

        node->c_right = rChild;
        rChild->parent = node;
    }

    bool empty() // checks if tree is empty
    {
        return root == nullptr || current == nullptr || length == 0;
    }

    bool empty(Node<T>* node) // checks if node is nullptr
    {
        return node == nullptr;
    }

    void clear(Node<T>* node) // Delete tree
    {
        if (empty())
            return;

        if (node->c_left != nullptr)
            clear(node->c_left);
        if (node->c_right != nullptr)
            clear(node->c_right);

        delete node;
        current == nullptr;
        root    == nullptr;
        length--;
    }

public:
    // Constructor
    BinarySearchTree()
    {
      root      = nullptr;
      current   = nullptr;
      length    = 0;
    }

    // Destructor
    ~BinarySearchTree()
    {
        clear(root);
    }

    int getLength() // Element count getter
    {
        return length;
    }

    Node<T>* getRoot() // Root element getter
    {
        if (empty(root) || empty())
            throw std::out_of_range("Error in getRoot(): Node is a nullptr.");
        else return root;
    }

    Node<T>* getCurrent() // Current Element getter
    {
        if (empty(current) || empty())
            throw std::out_of_range("Error in getCurrent(): Node is a nullptr.");
        else return current;
    }

    bool ins(T& data) // Insert ank
    {
        if (empty())
            return insRoot(data);
        else ins(data, root);
    }

    unsigned int getLayers() // Layers ank
    {
        if (empty())
            throw std::out_of_range("Error in getLayers(): Tree is empty");
        else return getLayers(root);
    }

    void updateKeys(Node<T>* node) // Update keys
    {
        if (!empty(root) && root->key != 1)
            root->key = 1;

        if (!empty(node->c_left))
        {
            node->c_left->key = node->key * 10;
            updateKeys(node->c_left);
        }
        if (!empty(node->c_right))
        {
            node->c_right->key = (node->key * 10) + 1;
            updateKeys(node->c_right);
        }
    }

    void printTree(const unsigned int mode) // Print ank
    {
        std::string str;

        switch (mode) {
            case 1 : printPreOrder(root, str);
                break;
            case 2 : printInOrder(root, str);
                break;
            case 3 : printPostOrder(root, str);
                break;
            default : throw std::invalid_argument("Error in printTree(): This mode does not exist!");
        }
    }

    Node<T>* searchNode(const long& key)  // Search node ank
    {
        if (!Util::isBin(key))
            throw std::invalid_argument("Error in searchNode(): Keys only contains 0 and 1.");
        if (empty())
            throw std::out_of_range("Error in searchNode(): Tree is empty.");

        Node<T>* result = searchNode(root, key);

        if (empty(result))
            throw std::invalid_argument("Error in searchNode(): Key does not exist.");
        else return result;
    }

    bool deleteNode(const long& key) // delete node ank
    {
        if (!Util::isBin(key))
            throw std::invalid_argument("Error in deleteNode(): Keys only contains 0 and 1.");
        if (empty())
            throw std::out_of_range("Error in deleteNode(): Tree is empty.");

        Node<T>* result = searchNode(root, key);

        if (empty(result))
            throw std::invalid_argument("Error in deleteNode(): Key does not exist.");
        else
        {
            int before = getLayers(root);
            deleteNode(result);
            int after = getLayers(root);

            if (after < before)
            {
                updateKeys(root);
                length--;
                return true;
            }
        }
    }

    bool setValue(const long& key, T data) // Change data value
    {
        if (!Util::isBin(key))
            throw std::invalid_argument("Error in setValue(): Keys only contains 0 and 1.");
        if (empty())
            throw std::out_of_range("Error in setValue(): Tree is empty.");

        Node<T>* result = searchNode(root, key);

        if (empty(result))
            throw std::invalid_argument("Error in setValue(): Key does not exist.");
        if (result->data == data)
            throw std::invalid_argument("Error in setValue(): This node already contains that data.");

        result->data = data;
        return result->data == data;
    }

    bool clear() // Delete tree ank
    {
        if (empty())
            throw std::out_of_range("Error in setValue(): Tree is empty.");
        clear(root);
        return empty();
    }
};

#endif //P5_CLION_BINARYSEARCHTREE_H
