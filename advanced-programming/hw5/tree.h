/**
 * @file tree.h
 * @author Dhruv Chakraborty
 * @brief Define and implement a templated Binary Search Tree class
 * PIC 10C Homework 5
 */

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <stdexcept>

namespace UCLA_Spring2021_PIC10C_HW5
{
    /**
     * @brief Templated Binary Search Tree class with interface to
     *        insert data, erase data, print data in ascending or 
     *        descending order, and to find the largest or second
     *        largest element stored in the tree.
     * 
     * @tparam T: type of data held in the BST
     */
    template <typename T>
    class BinarySearchTree
    {
        public:
            /**
             * @brief Nested class for nodes in the BST
             * 
             */
            class TreeNode
            {
                public:
                    /**
                     * @brief Helper function to insert node into tree while
                     *        mainitaing binary search tree properties
                     * 
                     * @param new_node: node to insert
                     */
                    void insert_node(TreeNode* new_node)
                    {
                        if (new_node->data < data)
                        {
                            if (left == nullptr) left = new_node;
                            else left->insert_node(new_node);
                        }
                        else if (data < new_node->data)
                        {
                            if (right == nullptr) right = new_node;
                            else right->insert_node(new_node);
                        }
                    }

                    /**
                     * @brief Helper function to print data in ascending order
                     * 
                     */
                    void print_nodes_asc() const
                    {
                        if (left != nullptr)
                            left->print_nodes_asc();
                        std::cout << data << "\n";
                        if (right != nullptr)
                            right->print_nodes_asc();
                    }

                    /**
                     * @brief Helper function to print data in descending order
                     * 
                     */
                    void print_nodes_desc() const
                    {
                        if (right != nullptr)
                            right->print_nodes_desc();
                        std::cout << data << "\n";
                        if (left != nullptr)
                            left->print_nodes_desc();
                    }

                private:
                    T data;
                    TreeNode* left;
                    TreeNode* right;

                // make BinarySearchTree class friend so we can access private members
                friend class BinarySearchTree;
            };

            /**
             * @brief Construct a new default Binary Search Tree object
             * 
             */
            BinarySearchTree()
            {
                root = nullptr;
            }

            /**
             * @brief Make node to store given data and insert into Binary Search Tree
             *        (given it doesn't already exist) using helper function in the 
             *        TreeNode class
             * 
             * @param data: data to insert into BST
             */
            void insert(T data)
            {
                TreeNode* new_node = new TreeNode;
                new_node->data = data;
                new_node->left = nullptr;
                new_node->right = nullptr;
                if (root == nullptr) root = new_node;
                else root->insert_node(new_node);
            }

            /**
             * @brief Remove node containing given data from Binary Search Tree (if it 
             *        is present), ensuring to maintain BST properties after removal
             * 
             * @param data: data to remove from BST
             */
            void erase(T data)
            {
                // Find node to be removed
                TreeNode* to_be_removed = root;
                TreeNode* parent = nullptr;
                bool found = false;

                // determine if 'data' exists in my tree
                while (!found && to_be_removed != nullptr)
                {
                    if (to_be_removed->data < data)
                    {
                        parent = to_be_removed;
                        to_be_removed = to_be_removed->right;
                    }
                    else if (data < to_be_removed->data)
                    {
                        parent = to_be_removed;
                        to_be_removed = to_be_removed->left;
                    }
                    else found = true;
                }

                if (!found) return;

                // to_be_removed contains data

                // If one of the children is empty, use the other

                if (to_be_removed->left == nullptr || to_be_removed->right == nullptr)
                {
                    TreeNode* new_child = nullptr;
                    if (to_be_removed->left == nullptr)
                        new_child = to_be_removed->right;
                    else
                        new_child = to_be_removed->left;
                    if (parent == nullptr) // Found in root
                        root = new_child;
                    else if (parent->left == to_be_removed)
                        parent->left = new_child;
                    else
                        parent->right = new_child;
                    return;
                }

                // Neither subtree is empty

                // Find smallest element of the right subtree

                TreeNode* smallest_parent = to_be_removed;
                TreeNode* smallest = to_be_removed->right;
                while (smallest->left != nullptr)
                {
                    smallest_parent = smallest;
                    smallest = smallest->left;
                }

                // smallest contains smallest child in right subtree

                // Move contents, unlink child
                to_be_removed->data = smallest->data;
                if (smallest_parent == to_be_removed) //smallest is its parent's right child
                    smallest_parent->right = smallest->right;
                else // smallest is its parent's left child
                    smallest_parent->left = smallest->right;
            }

            /**
             * @brief Print data stored in tree in ascending order
             * 
             */
            void ascending_print() const
            {
                if (root != nullptr)
                    root->print_nodes_asc();
            }

            /**
             * @brief Print data stored in tree in descending order
             * 
             */
            void descending_print() const
            {
                if (root != nullptr)
                    root->print_nodes_desc();
            }

            /**
             * @brief Return largest element stored in tree
             * 
             * @return T: largest i.e. right most element of BST
             */
            T largest() const
            {
                // throw logic error if tree is empty
                if (root == nullptr)
                    throw std::logic_error("Tried to call largest() for an empty tree");
                else
                {
                    TreeNode* right_most = root;
                    while (right_most->right != nullptr)
                    {
                        right_most = right_most->right;
                    }
                    return right_most->data;
                }
            }

            /**
             * @brief Return second largest element stored in tree
             * 
             * @return T: second largest element of BST
             */
            T second_largest() const
            {
                // throw logic error if tree is empty
                if (root == nullptr)
                    throw std::logic_error("Tried to call second_largest() for an empty tree");
                // throw logic error if tree only has one element
                else if (root->left == nullptr && root->right == nullptr)
                    throw std::logic_error("Tried to call second_largest() for an one-element tree");
                else
                {
                    TreeNode* pre = root;
                    TreeNode* curr = root;
                    while (curr->right != nullptr)
                    {
                        pre = curr;
                        curr = curr->right;
                    } 
                    // if the rightmost node doesn't have a left subtree, return its parent's data
                    if (curr->left == nullptr)
                        return pre->data;
                    // if the rightmost node has a left subtree, return the data stored in the 
                    // left subtree's rightmost node
                    else
                    {
                        curr = curr->left;
                        while(curr->right != nullptr)
                            curr = curr->right;
                        return curr->data;
                    }
                }
            }

        private:
            TreeNode* root;
    };
}

#endif