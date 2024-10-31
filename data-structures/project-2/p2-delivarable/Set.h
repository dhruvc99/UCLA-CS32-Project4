// Set.h

#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>

using ItemType = std::string;

class Set
{
public:
    Set();  // c'tor
    ~Set(); // d'tor
    Set(const Set& src);    // copy c'tor
    Set& operator=(const Set& src); // assignment o'tor
    
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int i, ItemType& value) const;
    void swap(Set& other);
    
private:
    int m_size;
    
    struct Node
    {
        ItemType value;
        
        Node *next;
        Node *prev;
    };
    Node* head;
    Node* tail;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif // SET_INCLUDED
