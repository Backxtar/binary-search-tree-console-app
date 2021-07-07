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

    void ins(T& data, Node<T>* node) // Insert sorted
    {
        if (data < node->data) {
            if (empty(node->c_left))
                insLeft(node, data);
            else ins(data, node->c_left);
        }
        else if (data >= node->data) {
            if (empty(node->c_right))
                insRight(node, data);
            else ins(data, node->c_right);
        }
    }

    void insRoot(T& data) // Insert root element
    {
        if (!empty(root))
            throw std::invalid_argument("Error in insRoot(): Node already exists.");

        root        = new Node<T>;
        root->key   = 1;
        root->data  = data;
        current     = root;
        length++;
    }

    void insLeft(Node<T>* parent, T& data) // Insert left child of parent
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
    }

    void insRight(Node<T>* parent, T& data) // Insert right child of parent
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
    }

    void printPreOrder(Node<T>* node, std::string str) // Print pre order
    {
        if (empty())
        {
            std::cout << "Tree is empty!" << std::endl;
            return;
        }

        std::cout << str << node->key << ": " << node->data << std::endl;

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

    void delNode(Node<T>* node)
    {
        if (empty(node->c_left) && empty(node->c_right) && length == 1) // Edge case only node
        {
            delete node;
            node = nullptr;
            length--;
        }

        if (empty(node->c_left) && empty(node->c_right)) // Case 0 : 0 Children
        {
            if (!empty(node->parent->c_left) && node->parent->c_left->key == node->key)
                node->parent->c_left = nullptr;
            if (!empty(node->parent->c_right) && node->parent->c_right->key == node->key)
                node->parent->c_right = nullptr;
        }

        if (!empty(node->c_left) && empty(node->c_right) || empty(node->c_left) && !empty(node->c_right))  // Case 1 : 1 Child
        {
            if (!empty(node->c_right))
            {
                node->c_right->parent = node->parent;
                node->parent->c_right = node->c_right;
            }
            if (!empty(node->c_left))
            {
                node->c_left->parent = node->parent;
                node->parent->c_left = node->c_left;
            }
        }

        if (!empty(node->c_left) && !empty(node->c_right)) // Case 2 : 2 Children
        {
            Node<T>* deleteNode = node;
            Node<T>* tmp = node->c_right;

            if (node->key == root->key) // Move left child up
            {
                node->c_left->key = 1;
                node->c_left->parent = nullptr;
                root = node->c_left;
            }
            else
            {
                node->parent->c_right = node->c_left;
                node->c_left->parent = node->parent;
            }

            node = node->c_left;

            while (!empty(node->c_right)) // Get lowest child right to append right subtree onto
                node = node->c_right;
            node->c_right = tmp;
            tmp->parent = node->c_right;

            node = deleteNode; // Move current to dangling parent to delete it
        }

        // Delete node
        delete node;
        node = nullptr;
        length--;
        updateKeys(root);
    }

    void rotateLeft(Node<T>* node)
    {
        Node<T>* top; // top of rotation

        if (node->key != root->key)
            top = searchNode(node->parent->key);
        else top = nullptr;

        Node<T>* bottom = node->c_right; // bottom of rotation (right side)
        Node<T>* sub    = bottom->c_left; // sub of bottom left side (will be appended on left side)

        node->c_right   = sub; // append sub to childRight of center
        if (!empty(sub))
            sub->parent = node;
        bottom->c_left  = node; // append center to left of bottom (will be rotated up) forming new cluster
        node->parent    = bottom;

        if (empty(top)) // when center was root bottom rotated up to new root
        {
            root        = bottom;
            root->key   = 1;
        }
        if (node->key == top->c_left->key) // if center was on left side - bottom rotate up to left of top
            top->c_left     = bottom;
        if (node->key == top->c_right->key)	// if center was on right side - bottom rotate up to right of top
            top->c_right    = bottom;

        updateKeys(root);
    }

    void rotateRight(Node<T>* node)
    {
        Node<T>* top; // top of rotation

        if (node->key != root->key)
            top = searchNode(node->parent->key);
        else top = nullptr;

        Node<T>* bottom = node->c_left; // bottom of rotation (right side)
        Node<T>* sub    = bottom->c_right; // sub of bottom left side (will be appended on left side)

        node->c_left    = sub; // append sub to childLeft of center
        if (!empty(sub))
            sub->parent = node;
        bottom->c_right = node; // append center to right of bottom (will be rotated up) forming new cluster
        node->parent    = bottom;

        if (empty(top)) // when center was root bottom rotated up to new root
        {
            root        = bottom;
            root->key   = 1;
        }
        if (node->key == top->c_right->key) // if center was on right side - bottom rotate up to left of top
            top->c_right    = bottom;
        if (node->key == top->c_left->key)	// if center was on left side - bottom rotate up to right of top
            top->c_left     = bottom;

        updateKeys(root);
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

    void ins(T& data) // Insert ank
    {
        if (empty())
            insRoot(data);
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

    void delNode(const long& key)
    {
        if (!Util::isBin(key))
            throw std::invalid_argument("Error in deleteNode(): Keys only contains 0 and 1.");
        if (empty())
            throw std::out_of_range("Error in deleteNode(): Tree is empty.");

        Node<T>* result = searchNode(root, key);

        if (empty(result))
            throw std::invalid_argument("Error in deleteNode(): Key does not exist.");
        delNode(result);
    }

    void rotateLeft(const long& key)
    {
        if (!Util::isBin(key))
            throw std::invalid_argument("Error in rotateLeft(): Keys only contains 0 and 1.");
        if (empty())
            throw std::out_of_range("Error in rotateLeft(): Tree is empty.");

        Node<T>* result = searchNode(root, key);

        if (empty(result))
            throw std::invalid_argument("Error in rotateLeft(): Key does not exist.");

        if (empty(result->c_right))
            throw std::out_of_range("Error in rotateLeft(): Can not rotate if right subtree is empty.");

        rotateLeft(result);
    }

    void rotateRight(const long& key)
    {
        if (!Util::isBin(key))
            throw std::invalid_argument("Error in rotateRight(): Keys only contains 0 and 1.");
        if (empty())
            throw std::out_of_range("Error in rotateRight(): Tree is empty.");

        Node<T>* result = searchNode(root, key);

        if (empty(result))
            throw std::invalid_argument("Error in rotateRight(): Key does not exist.");

        if (empty(result->c_left))
            throw std::out_of_range("Error in rotateRight(): Can not rotate if left subtree is empty.");

        rotateRight(result);
    }

    void balance()
    {
        if (empty() || empty(root->c_left) && empty(root->c_right))
            throw std::invalid_argument("Error in balance(): Tree is already balanced.");

        balance(root);
    }

    void balance(Node<T>* node)
    {
        int dif = getLayers(root->c_left) - getLayers(root->c_right);

        if (dif < -1)
        {
            rotateLeft(node->key);
            balance(node->parent);
        }
        else if (dif > 1)
        {
            rotateRight(node->key);
            balance(node->parent);
        }

        if (!empty(node->c_right))
            balance(node->parent);
        if (!empty(node->c_left))
            balance(node->parent);
    }

    void setValue(const long& key, T data) // Change data value
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
        //TODO: Balance tree
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
