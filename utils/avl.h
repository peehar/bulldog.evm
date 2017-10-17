#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <cstdio>
#include <sstream>

#define PRINT_WIDTH  200

class CanNotFindException
{};

template<typename K>
class AVLMapCompare
{
public:
    int operator()(K d1, K d2)
    {
        return d1 < d2 ? -1 : d1 > d2 ? 1 : 0;
    }
};

template<typename K, typename T, typename C = AVLMapCompare<K>>
class AVLMap
{
    struct node_t
    {
        node_t() : deep(0), left(nullptr), right(nullptr) {}
        K c;
        int deep;
        node_t *left, *right;
        T data;
    };
public:
    ~AVLMap()
    {
        deleteNode(root);
    }

//    void print()
//    {
//        char view[20][PRINT_WIDTH] = {0};
//        print(root, 0, 0, PRINT_WIDTH, view);

//        for (int x = 0; x < 10; x++)
//        {
//            for (int y = 0; y < PRINT_WIDTH; y++)
//            {
//                if (view[x][y] != 0)
//                {
//                    std::cout << view[x][y];
//                }
//                else
//                {
//                    std::cout << " ";
//                }
//            }
//            std::cout << std::endl;
//        }
//    }

//    int print(node_t* node, int deep, int offset, int width, char view[][PRINT_WIDTH])
//    {
//        int pos = offset + width / 2;
//        if (deep != 0)
//            view[deep* 2 - 1][pos] = '+';
//        sprintf(view[deep * 2] + pos, "%s(%d)", node->c.c_str(), node->deep);
//        view[deep* 2 + 1][pos] = '+';

//        if (node->left != nullptr)
//        {
//            int lpos = print(node->left, deep + 1, offset, width / 2, view);
//            for (int i = lpos + 1; i < pos; i++)
//                view[deep* 2 + 1][i] = '-';
//        }
//        if (node->right != nullptr)
//        {
//            int rpos = print(node->right, deep + 1, offset + width / 2, width / 2, view);
//            for (int i = pos + 1; i < rpos; i++)
//                view[deep* 2 + 1][i] = '-';
//        }

//        return pos;
//    }

    void insert(K key, const T data)
    {
        root = insert(root, key, data);
//        print();
    }

    void remove(K key);

    T find(K key)
    {
        node_t *node = find(root, key);
        if (node == nullptr)
            throw CanNotFindException();
        return node->data;
    }

private:

    node_t* insert(node_t* node, K key, const T data)
    {
        if (node == nullptr)
            return createNode(key, data);

        int r = compare(key, node->c);

        if (r < 0)
        {
            node->left = insert(node->left, key, data);
            return rotate(node);
        }

        if (r > 0)
        {
            node->right = insert(node->right, key, data);
            return rotate(node);
        }

        node->data = data;
        return node;
    }

    node_t* createNode(K key, const T data)
    {
        node_t*node = new node_t();
        node->c = key;
        node->data = data;
        return node;
    }

    node_t* find(node_t* node, K key)
    {
        if (node == nullptr || key == 0)
            return nullptr;
        node_t* result = nullptr;
        int r = compare(key, node->c);
        if (r < 0)
            result = find(node->left, key);
        else if (r > 0)
            result = find(node->right, key);
        else
            result = node;
        return result;
    }

    void deleteNode(node_t* node)
    {
        if (node->left != nullptr)
            deleteNode(node->left);
        if (node->right != nullptr)
            deleteNode(node->right);
        delete node;
    }

    node_t* rotate(node_t* node)
    {
        int dl = 0;
        int dr = 0;
        if (node->left != nullptr)
            dl = node->left->deep + 1;
        if (node->right != nullptr)
            dr = node->right->deep + 1;

        node->deep = dl > dr ? dl : dr;

        if (lr(node) > 1)
        {
            if (lr(node->left) > 0)
                return rotateLL(node);
            else
                return rotateLR(node);
        }
        else if (lr(node) < -1)
        {
            if (lr(node->right) > 0)
                return rotateRL(node);
            else
                return rotateRR(node);
        }
        return node;
    }
    
    node_t* rotateLL(node_t* node)
    {
        node_t* root = node->left;
        node->left = root->right;
        root->right = node;

        node->deep = deep(node->left, node->right);
        root->deep = deep(root->left, root->right);

        return root;
    }
    
    node_t* rotateLR(node_t* node)
    {
        node->left = rotateRR(node->left);
        return rotateLL(node);
    }

    node_t* rotateRL(node_t* node)
    {
        node->right = rotateLL(node->right);
        return rotateRR(node);
    }

    node_t* rotateRR(node_t* node)
    {
        node_t* root = node->right;
        node->right = root->left;
        root->left = node;

        node->deep = deep(node->left, node->right);
        root->deep = deep(root->left, root->right);

        return root;
    }

private:
    int deep(node_t* node1, node_t* node2)
    {
        int d1 = node1 != nullptr ? node1->deep + 1: 0;
        int d2 = node2 != nullptr ? node2->deep + 1: 0;
        return d1 > d2 ? d1 : d2;
    }

    int lr(node_t* node)
    {
        int d1 = node->left != nullptr ? node->left->deep + 1: 0;
        int d2 = node->right != nullptr ? node->right->deep + 1: 0;
        return d1 - d2;
    }

private:
    C compare;
    node_t *root = nullptr;
};

#endif
