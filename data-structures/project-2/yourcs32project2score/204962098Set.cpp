// Set.cpp

#include "Set.h"


        //////////////////////

////// Needs more useful comments! //////

        //////////////////////
    
Set::Set() : m_size(0), head(nullptr), tail(nullptr) // works
{}

Set::~Set() // probably works
{
    Node *p = head;
    
    while (p != nullptr)
    {
        Node *n = p->next;
        delete p;
        p = n;
    }
}

Set::Set(const Set& src)
{
    head = new Node();
    head->prev = nullptr;
    tail = new Node();
    tail->next = nullptr;
    
    Node* t = src.head->next;
    Node* temp = head;
    
    while (t->next != nullptr)
    {
        Node* p = new Node();
        
        p->prev = temp;
        p->value = t->value;
        temp->next = p;
        temp = p;
        
        t = t->next;
    }
    temp->next = tail;
    tail->prev = temp;
    
    m_size = src.size();
}

Set& Set::operator=(const Set &src) // works
{
    if (this != &src)
    {
        Set temp(src);
        this->swap(temp);
    }
    return *this;
}

bool Set::empty() const // works
{
    return size() == 0;
}

int Set::size() const // works
{
    return m_size;
}

bool Set::insert(const ItemType& value)
{
    if (contains(value))
        return false;
    
    if (head == nullptr) // in case of empty list
    {
        head = new Node;
        head->value = value;
        head->next = nullptr;
        head->prev = nullptr;
        
        tail = head;
        m_size++;
        
        return true;
    }
    
    int sorted_index; // find position to insert value such that list remains sorted
    for (sorted_index = 0; sorted_index < size(); sorted_index++)
    {
        ItemType temp;
        get(sorted_index, temp);
        if (value < temp)
            break;
    }
    
    if (sorted_index == 0) // insert at start
    {
        Node *p = head;
        
        head = new Node;
        head->value = value;
        head->next = p;
        head->prev = nullptr;
        
        p->prev = head;
        
        m_size++;
    }
    else if (sorted_index == size()) // insert at end
    {
        Node *p = tail;
        
        tail = new Node;
        tail->value = value;
        tail->next = nullptr;
        tail->prev = p;
        
        p->next = tail;
        
        m_size++;
    }
    else // sorted position is in middle somehere
    {
        Node *p = head;
        
        for (int i = 0; i < sorted_index; i++)
            p = p->next;


        Node* temp = new Node;
        
        temp->prev = p;
        temp->next = p->next;
        
        p->next->prev = temp;
        p->next = temp;
        
        temp->value = value;

        m_size++;
    }
    return true;
}

bool Set::erase(const ItemType &value)
{
    if (head == nullptr)
        return false;
    
    if (head->value == value)
    {
        Node *removeMe = head;
        
        if (head->next == nullptr) // if one element list
        {
            delete removeMe;
            head = nullptr;
            tail = nullptr;
            m_size--;
            return true;
        }
        
        head = head->next;
        head->prev = nullptr;
     
        delete removeMe;
        m_size--;
        return true;
    }
    
    Node *p = head;
    
    while (p != nullptr)
    {
        if (p->next != nullptr && p->next->value == value) break;
        p = p->next;
    }
    
    if (p != nullptr)
    {
        if (p->next == tail)
        {
            tail = p;
            tail->next = nullptr;
            delete p->next;
            m_size--;
            return true;
        }
        
        Node *removeMe = p->next;
        p->next = removeMe->next;
        p->next->prev = p;
        delete removeMe;
    }
    else
        return false;
    
    m_size--;
    return true;
}

bool Set::contains(const ItemType &value) const
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->value == value)
            return true;
        p = p->next;
    }
    return false;
}

bool Set::get(int i, ItemType &value) const
{
    if (i < 0 || i >= size())
        return false;
    
    Node *p = head;
    for (int j = 0; j < i; j++)
        p = p->next;
    value = p->value;
    
    return true;
}

void Set::swap(Set &other)
{
    int temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;
    
    Node *p = head;
    head = other.head;
    other.head = p;
    
    p = tail;
    tail = other.tail;
    other.tail = p;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
    result = s1;
    
    ItemType temp;
    for (int i = 0; i < s2.size(); i++)
    {
        s2.get(i, temp);
        result.insert(temp);
    }
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    result = s1;
    
    ItemType temp;
    for (int i = 0; i < s2.size(); i++)
    {
        s2.get(i, temp);
        result.erase(temp);
    }
}
