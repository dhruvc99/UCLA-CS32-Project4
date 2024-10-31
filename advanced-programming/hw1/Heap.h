/**
 * @file Heap.h 
 * @author Dhruv Chakraborty
 * @brief Define a template heap class
 * PIC 10C Homework 1
 */

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <iomanip>
#include <vector>

/**
 * @class Heap serves as a templated maximum heap with 
 * a custom comparison operator.
 * @tparam T the type being stored
 * @tparam CMP the comparison operator
 */
template <typename T, typename CMP=std::less<T> >
class Heap 
{
private:
    std::vector<T> data; // stores vector as member
    CMP comparator; // for comparison operator

    /**
     * Returns index of parent of specified node
     * @param i index of specified node
     */
    std::size_t parent(std::size_t i) 
    {
        return (i-1)/2;
    }

    /**
     * Returns index of left child of specified node
     * @param i index of specified node
     */
    std::size_t left(std::size_t i) 
    {
        return (2*i + 1);
    }

    /**
     * Returns index of right child of specified node
     * @param i index of specified node
     */
    std::size_t right(std::size_t i) 
    {
        return (2*i + 2);
    }

    /**
     * Recursive algorithm to maintain max heap structure
     * from the bottom up.
     * @param i index of node to heapify above
     */
    void heapify_up(std::size_t i) 
    {
        if (i && comparator(data[i], data[parent(i)])) 
        {
            std::swap(data[i], data[parent(i)]);
            heapify_up(parent(i));
        }
    }               

    /**
     * Recursive algorithm to maintain max heap structure
     * from the top down.
     * @param i index of node to heapify below
     */
    void heapify_down(std::size_t i) 
    {
        size_t index = i;

        if (left(i) < size() && comparator(data[left(i)], data[i]))
            index = left(i);

        if (right(i) < size() && comparator(data[right(i)], data[index]))
            index = right(i);

        if (index != i) 
        {
            std::swap(data[i], data[index]);
            heapify_down(index);
        }
    }

    /**
     * Bubble sort algorithm for display function
     */
    std::vector<T> bubble_sort(std::vector<T> data) const
    {
        std::vector<T> vals = data;

        int i,j;
        for(i=0; i<vals.size()-1; i++)
        {
            for(j=0; j<vals.size()-i-1; j++)
            {
                if(comparator(vals[j+1], vals[j]))
                    std::swap(vals[j], vals[j+1]);
            }
        }

        return vals;
    }

public:
    /**
     * Default constructor: initialize member vector and
     * comparison operator, defaulting to std::less
     */ 
    Heap(const CMP& _comparator = CMP())
    : data{}, comparator{_comparator} 
    {}

    /**
     * Construct heap with data in input std::vector and
     * comparison operator, defaulting to std::less
     */ 
    Heap(std::vector<T> vals, const CMP& _comparator = CMP())
    : data{}, comparator{_comparator} 
    {
        for(int i=0; i<vals.size(); i++)
            push(vals[i]);
    }

    /** 
     * Returns the size of the max_heap
     * @return size_t of values
     */
    std::size_t size() const
    {
        return data.size();
    }

    /**
     * Recursively push variadic list of elements into 
     * Heap while maintaining heap structure.
     * @param objs elements to insert
     */
    void push() {}

    template<typename Tfirst, typename ... Trest>
    void push(const Tfirst& obj, const Trest&... objs)
    {
        data.push_back(obj);
        heapify_up(size()-1);
        push(objs...);
    }

    /** 
     * Return top i.e. first element of Heap
     * @return "maximum" value in Heap
     */
    T& top()
    {
        return data[0];
    }

    /**
     * Removes first element of Heap 
     * while maintaining heap structure.
     */
    void pop() 
    {
        if (size() == 0)
            return;
        
        data[0] = data.back();
        data.pop_back();

        heapify_down(0);
    }


    /**
     * Print the heap in sorted order determined by CMP
     */
    void display() const
    {   
        if(size()>0)
        {
            std::vector<T> vals = bubble_sort(data);

            for(int k=0; k<vals.size(); k++)
                std::cout << vals[k] << "\t";
        }
    }
};

/**
 * Print elements of all input heaps in sorted order
 * @param objs variadic list of heaps
 */
void print() {}

template<typename Tfirst, typename ... Trest>
void print(const Tfirst& obj, const Trest&... objs)
{
    obj.display();
    std::cout << std::endl;
    print(objs...);
}

#endif