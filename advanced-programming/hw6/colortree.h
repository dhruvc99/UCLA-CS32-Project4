/**
 * @file colortree.h
 * @author Dhruv Chakraborty
 * @brief Implement Dijkstra's algorithm and helper functions to check whether 
 *        a binary search tree is a red black tree
 * PIC 10C Homework 6
 */

#ifndef COLORTREE_H
#define COLORTREE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <set>

/**
 * @brief Templated Binary Search Tree class with interface to
 *        insert data, erase data, print data in ascending or 
 *        descending order, and to find the largest or second
 *        largest element stored in the tree.
 * 
 * @tparam T: type of data held in the BST
 */
template <typename T>
class ColorBST
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
                        if (left == nullptr) 
                        {
                            new_node->parent = this;
                            left = new_node;
                        }
                        else left->insert_node(new_node);
                    }
                    else if (data < new_node->data)
                    {
                        if (right == nullptr) 
                        {   
                            new_node->parent = this;
                            right = new_node;
                        }
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
                char color; 
                TreeNode* left;
                TreeNode* right;
                TreeNode* parent; 

            // make BinarySearchTree class friend so we can access private members
            friend class ColorBST;
        };

        /**
         * @brief Construct a new default Binary Search Tree object
         * 
         */
        ColorBST()
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
        void insert(T data, char c)
        {
            if (c != 'b' && c != 'r')
                throw std::logic_error("Please enter a valid color choice i.e. b (black) or r (red).");

            TreeNode* new_node = new TreeNode;
            new_node->data = data;
            new_node->left = nullptr;
            new_node->right = nullptr;
            new_node->color = c;
            if (root == nullptr) 
            {
                new_node->parent = nullptr;
                root = new_node;
            }
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

        /**
         * @brief Checks whether BST has Black root property of RBTs
         * 
         * @return true if root is black
         * @return false if tree has no root (i.e. it's empty) or root is red
         */
        bool BlackRoot() const
        {
            if (root == nullptr || root->color == 'r')
                return false;
            else
                return true;
        }

        /**
         * @brief Checks whether BST has no double red property of RBTs
         * 
         * @return true if red nodes have no red children
         * @return false if a red node has a red child
         */
        bool NoDoubleRed() const
        {
            return checkDoubleRed(root);
        }

        /**
         * @brief Checks whether BST satisfies equal black depth property of RBTs
         * 
         * @return true if depth of black nodes is independent of subtree
         * @return false if depth of black nodes differs in subtrees
         */
        bool BlackDepth() const
        {
            if (checkBlackDepth(root) == -1)
                return false;
            else
                return true;
        }

    private:
        TreeNode* root;

        /**
         * @brief Recursive helper function for NoDoubleRed()
         * 
         * @param node 
         * @return true 
         * @return false 
         */
        bool checkDoubleRed(TreeNode* node) const
        {
            if (node == nullptr)
                return true;
            if (!checkDoubleRed(node->left))
                return false;
            if (!checkDoubleRed(node->right))
                return false;
            
            // ensure that if node is red and has left/right children, 
            // they are not red
            if (node->color == 'r' && ((node->left && node->left->color=='r') 
                                        || (node->right && node->right->color=='r')))
                return false;

            return true;
        }

        /**
         * @brief Recursive helper function for BlackDepth()
         * 
         * @param node 
         * @return int: if black depth is equal in the left and right subtree of node
         *              then return the depth, otherwise return -1
         */
        int checkBlackDepth(TreeNode* node) const
        {
            if (node == nullptr)
                return 0;
            
            int isBlack;
            if (node->color == 'b')
                isBlack = 1;
            else
                isBlack = 0;

            int leftDepth = checkBlackDepth(node->left);
            int rightDepth = checkBlackDepth(node->right);

            // check that black depths are equal in both subtrees and at the level
            // of the node
            if (leftDepth == -1 || rightDepth == -1 || leftDepth != rightDepth)
                return -1;
            else
                return isBlack+leftDepth;
        }
};

/**
 * @brief Helper function for Dijkstra's algorithm to print all 
 *        the shortest paths from origin to target
 * 
 * @param prevs: array of vectors where the i-th index stores all the valid
 *               previous vertices to reach the i-th vertex on a shortest path 
 * @param target 
 * @param origin 
 * @param path 
 */
void print_paths(std::vector<int> prevs[], int target, int origin, std::string path)
{
    for (auto it = prevs[target].begin(); it != prevs[target].end(); it++)
    {
        path = std::to_string(target) + "-" + path;

        if (target == origin)
        {
            std::cout << path.substr(0, path.size()-1) << std::endl;
            break;
        }
        // call recursively on all valid previous vertices
        print_paths(prevs, *it, origin, path);
        path = "";
    }
}

/**
 * @brief Dijkstra's algorithm for adjacency matrix which also prints all available
 *        shortest paths from origin to target
 * 
 * @param map 
 * @param origin 
 * @param target 
 * @return int 
 */
int dijkstra(std::vector<std::vector<int> > map, size_t origin, size_t target)
{
    std::set<int> unvisited;
    size_t num_vertices = map.size();
    
    // **********
    // int dist[num_vertices];
    // std::vector<int> prevs[num_vertices];
    // Although the above works on my laptop (the command I use is g++ -std=c++11),
    // it throws an odd error on Visual Studio on the PIC APPORTO server.
    //
    // I was able to bypass the errors with the following code that may fail to work 
    // depending on how large the adjacency matrices the program is being tested on are.
    // **********

    int dist[1000];
    std::vector<int> prevs[1000];

    for (int i = 0; i < num_vertices; i++)
    {
        dist[i] = INT_MAX; // use INT_MAX for infinity
        unvisited.insert(i);
    }
    dist[origin] = 0;

    while (!unvisited.empty())
    {
        int min_dist = INT_MAX;
        int min_vertex;

        // find vertex with minimum distance in the unvisited set
        for (auto it = unvisited.begin(); it!= unvisited.end(); it++)
        {
            if (dist[*it] <= min_dist)
            {
                min_dist = dist[*it];
                min_vertex = *it;
            }
        }

        unvisited.erase(min_vertex);
        if (min_vertex == target)
            break;

        for (int i = 0; i < num_vertices; i++)
        {
            // there is no path from min_vertex to i, so move on to next vertex
            if (map[min_vertex][i] == 0)
                continue;
            
            int alt = dist[min_vertex] + map[min_vertex][i];

            if (alt <= dist[i])
            {
                // if new distance is strictly lower, we clear prevs but if it is
                // equal to old value we simply append
                if (alt < dist[i])
                {
                    dist[i] = alt;
                    prevs[i].clear();
                }
                prevs[i].push_back(min_vertex);
            }
        }
    }

    if (target == origin)
        std::cout << origin << std::endl;
    else if (prevs[target].empty())
    {
        std::cout << "No path found" << std::endl;
        return -1;
    }
    else
    {
        prevs[origin].push_back(origin);
        print_paths(prevs, target, origin, "");
    }

    return dist[target];
}

#endif