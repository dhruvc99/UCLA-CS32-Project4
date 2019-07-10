//
//  Trie.h
//  genomics
//
//  Created by Dhruv Chakraborty on 3/11/19.
//  Copyright © 2019 Dhruv Chakraborty. All rights reserved.
//

#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
private:
    struct Node;
    struct Child // use struct to represent children since each Child will have a Node object and a label associated with it
    {
        Child(Node* ptr, char ch)
        {
            ptrToChild = ptr;
            label = ch;
        }
        Node* ptrToChild;
        char label;
    };

    struct Node
    {
        ~Node(); // ensure that we are deleting the Child structs
        
        std::vector<Child*> children;
        std::vector<ValueType> values;
        
        void recursivelyInsert(const std::string& key, const ValueType& value);
        void recursivelyFind(const std::string& key, const std::string originalKey, bool exactMatchOnly, std::vector<ValueType> &results) const;
    };
    
    Node* m_root;
    void freeTree(Node* root); // function to remove sub-trie rooted at given root
};

// ==================== Node's implementations: ====================

template<typename ValueType>
Trie<ValueType>::Node::~Node()
{
    for (int i = children.size() - 1; i >= 0; i--)
    {
        if (children[i] != nullptr)
            delete children[i];
    }
}

template<typename ValueType>
void Trie<ValueType>::Node::recursivelyInsert(const std::string &key, const ValueType &value)
{
    if (key.size() == 0)
    {
        values.push_back(value);
        return;
    }
    
    for (int i = 0; i < children.size(); i++)
    {
        if (key[0] == children[i]->label)
        {
            children[i]->ptrToChild->recursivelyInsert(key.substr(1), value);
            return;
        }
    }
    
    // if this path doesn't exist (since label didn't match with any children), we create said child and call function on key substring
    children.push_back(new Child(new Node, key[0]));
    children[children.size() - 1]->ptrToChild->recursivelyInsert(key.substr(1), value); // call on newly created child
}

template<typename ValueType>
void Trie<ValueType>::Node::recursivelyFind(const std::string& key, const std::string originalKey, bool exactMatchOnly, std::vector<ValueType> &results) const
{
    if (key.size() != 0)
    {
        for (int i = 0; i < children.size(); i++)
        {
            if (children[i]->label == key[0])
                children[i]->ptrToChild->recursivelyFind(key.substr(1), originalKey, exactMatchOnly, results);
            else if (key.size() != originalKey.size() && exactMatchOnly == false) // allowed a mismatch if exactMatchOnly is false (not in 1st pos)
                children[i]->ptrToChild->recursivelyFind(key.substr(1), originalKey, true, results);
        }
    }
    else
    {
        for (int i = 0; i < values.size(); i++)
            results.push_back(values[i]);
    }
}

// ==================== Trie's implementations: ====================

template<typename ValueType>
void Trie<ValueType>::freeTree(Node* root)
{
    if (root == nullptr)
        return;
    
    for (int i = 0; i < root->children.size(); i++)
    {
        freeTree(root->children[i]->ptrToChild);
    }
    delete root;
}

template<typename ValueType>
Trie<ValueType>::Trie()
{
    m_root = new Node();
}

template<typename ValueType>
Trie<ValueType>::~Trie()
{
    freeTree(m_root);
}

template<typename ValueType>
void Trie<ValueType>::reset()
{
    freeTree(m_root);
    m_root = new Node;
}

template<typename ValueType>
void Trie<ValueType>::insert(const std::string& key, const ValueType& value)
{
    m_root->recursivelyInsert(key, value);
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string& key, bool exactMatchOnly) const
{
    std::vector<ValueType> results;
    m_root->recursivelyFind(key, key, exactMatchOnly, results);
    return results;
}

#endif // TRIE_INCLUDED
