#ifndef AVL_H
#define AVL_H

class CanNotFindException
{};

template<typename T>
class AVLMap
{
    struct node_t
    {
        char c;
        int deep;
        T data;      
        node_t *left, *right;
        node_t() : deep(0), left(nullptr), right(nullptr) {}
    };
public:
    ~AVLMap()
    {
        deleteNode(root);
    }

    void insert(char* key, const T data)
    {
        insert(root, key, data);
    }

    void remove(char* key);

    T find(char* key)
    {
        node_t *node = find(root, key);
        if (node == nullptr)
            throw CanNotFindException();
        return node->data;
    }

private:

    void insert(node_t* node, char* key, const T data)
    {
        if (*key < node->c)
        {
            if (node->left != nullptr) 
                insert(node->left, key + 1, data);
            else
                node->left = createNode(*(key + 1), data);

            int deep = node->left->deep;
            if (node->right != nullptr)
            {
                int r = node->right->deep;
                deep = deep < r ? r : deep;
            }
            if (node->deep != deep + 1)
            {
                node->deep = deep + 1;
            }
        }
        else if (*key > node->c)
        {
            if (node->right != nullptr)
                insert(node->right, key + 1, data);
            else
                node->right = createNode(*(key + 1), data);

            int deep = node->right->deep;
            if (node->left != nullptr)
            {
                int l = node->left->data;
                deep = deep < l ? l : deep;
            }
            if (node->deep != deep + 1)
            {
                node->deep = deep + 1;
            }
        }
        else
        {
            node->data = data;
        }
    }

    node_t* createNode(char c, const T data)
    {
        node_t *node = new node_t();
        node->c = c;
        node->data = data;
        return node;
    }

    node_t* find(node_t* node, char* key)
    {
        if (node == nullptr || *key == 0)
            return nullptr;
        node_t* result = nullptr;
        if (*key < node->c)
            result = find(node->left, key + 1);
        else if (*key > node->c)
            result = find(node->right, key + 1);
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
    
    
    void rout
    
private:
    node_t *root;
};

#endif
