#include <iostream>
#include <functional>
#include <vector>
#include <memory>
#include <stdexcept>
#include <list>

using namespace std;

class Person
{
    public: 
        Person(){};
        void setname(string s){name=s;};
    private:
        string name;
};

class Student: virtual public Person
{
    public:
        Student(){};
        void set_id(string s){id=s;};
    private:
        string id;
};

class Employee: virtual public Person
{
    public:
        Employee(){salary=0;};
        void set_id(string s){id=s;};
        void set_salary(double d){salary=d;};
    private:
        string id;
        double salary;
};

class TA: public Student, public Employee
{
    public:
        TA(string t_name, string s_id, string e_id, double t_salary);
};

TA::TA(string t_name, string s_id, string e_id, double t_salary)
{
    setname(t_name);
    Student::set_id(s_id);
    Employee::set_id(e_id);
    set_salary(t_salary);
};

void f(Employee e)
{
    vector<Employee*> A;
    A.push_back(&e);
    A.push_back(new Employee());
}

/**
 * @tparam CMP should be implemented for input typename T
 */
template <typename T, typename CMP = greater<T> >
vector<T> myfunction(const vector<T> &v)
{
    vector<int> result;
    CMP comparator;
    
    if (v.empty())
        return result;
    else 
        result.push_back(0);
    for (int i =1; i != v.size(); ++i)
    {
        if (comparator(v[i-1],v[i]))
            result.push_back(i);
    }
    return result;
}

class A {};

class B: virtual public A {};
class C: virtual public A {};

class D: virtual public C, virtual public B {};

// template <typename T> 
// auto foo(T t)
// {
//     decltype(*t) x;
//     t++;
//     x = *t+1;
//     return *t;
// }

// template <typename T> 
// void foo (shared_ptr<T> ptr)
// {
//     *ptr = T();
// }

// read in 3 integers and print their product,
// throwing logic_error if any of them are equal
// or not integers
void read_unique3()
{
    int arr[3]; // to store the 3 input integers
    int x;

    for (int i = 0; i < 3; i++)
    {
        int x; 
        std::cin >> x;
        if (std::cin.fail()) // std::cin fails when input not correct type
            throw std::logic_error("Please enter integers");
        arr[i] = x;
    }

    if (arr[0] == arr[1] || arr[1] == arr[2] || arr[0] == arr[2])
        throw logic_error("At least two integers are equal");

    x = arr[0]*arr[1]*arr[2];
    cout << x << endl;
}

void keep_reading_unique3()
{
    while(true)
    {
        try
        {
            read_unique3();
            break;
        }
        catch(std::logic_error& e)
        {
            // reset error flags
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); 
            // ask user for valid input
            std::cout << "Input error: " << e.what() << std::endl;
            std::cout << "Please enter 3 distinct integers separated by spaces" << std::endl;
        }
    }
}

namespace PIC10C
{
    template <typename CMP>
    void sort(std::list<int>::iterator first, std::list<int>::iterator last, CMP comparator)
    {
        std::vector<int> result;
        for (auto it = first; it != last; ++it)
            result.push_back(*it);

        std::sort(result.begin(), result.end(), comparator);
        std::copy(result.begin(), result.end(), first);
    }
}

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

        void clear(TreeNode* node)
        {
            if (node != nullptr)
            {
                clear(node->left);
                clear(node->right);
                delete node;
                node = nullptr;
            }
        }

        TreeNode* copy(const TreeNode* node)
        {
            if (node == nullptr)
                return nullptr;
            

            // make nodes for left and right child
            TreeNode* left_child = copy(node->left);
            TreeNode* right_child = copy(node->right);

            TreeNode* new_node = new TreeNode;
            new_node->data = node->data;
            new_node->left = left_child;
            new_node->right = right_child;

            return new_node;
        }

        BinarySearchTree& operator=(const BinarySearchTree& t)
        {
            // check that t is not *this
            if (t.root != root)
                clear(root); // clear current tree
                root = copy(t.root); // copy t
            return *this;
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

int main ()
{
    // auto f = std::bind2nd(std::less<int>(), 100);

    // auto reciprocal = [](int n)-> double {return 1/double(n);};

    // std::cout << reciprocal(2) << std::endl;

    // TA new_hire("amy","S123","E009",10);
    // f(new_hire);
    // vector<int> v;
    // vector<int> v2;

    // v.push_back(30);
    // v.push_back(20);
    // v.push_back(10);

    // v2 = myfunction<int, less<int> >(v);

    // {
    // for (int i =0; i < v2.size(); ++i)
    //     cout << v2[i] << " ";
    // }

    // A a; B b; C c; D d;
    // A* pa; B* pb; C* pc; D* pd; 

    // a = d;
    // pa = pd;
    // b = d;
    // pb = pd;
    // b = c;
    // pb = pc;

    // pa = dynamic_cast<A*>(pd);
    // pb = dynamic_cast<B*>(pd);
    // pb = dynamic_cast<C*>(pc);

    // cout << typeid(pb).name();

    // int z[2];

    // foo(z);

    // auto p = new int();
    // auto sp = make_shared<int> ();

    // foo(sp);
    // // foo(p);
    // foo(shared_ptr(p));

    std::list<int> L = {2, -5, 4, -1};
    PIC10C::sort( L.begin(), L.end(), std::less<int>());
    for (auto a: L)
        cout << a << endl;
    // L = {-5, -1, 2, 4}
    PIC10C::sort( L.begin(), L.end(), std::greater<int>());
    for (auto a: L)
        cout << a << endl;
    // L = {4, 2, -1, -5}

    // keep_reading_unique3();

    return 0;
}