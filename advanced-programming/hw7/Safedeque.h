/**
 * @file Safedeque.h
 * @author Dhruv Chakraborty
 * @brief Implement a Safedeque class with functionality similar to std::deque
 * 
 * PIC 10C Homework 7
 */

#ifndef SAFEDEQUE_H
#define SAFEDEQUE_H

#include <iostream>
#include <functional>
#include <memory>
#include <stdexcept>

template <typename T>
class Safedeque 
{
public:
    class Iterator
    {
    public:
        Iterator(int _pos, const Safedeque* _d): pos(_pos), d(_d)
        {
            start = d->data.get();
        }

        T& operator*() const
        {
            if (pos == -1)
                throw std::out_of_range("Cannot dereference end() iterator.");

            return *(start+pos);
        }


        friend bool operator==(const Iterator& a, const Iterator &b)
        {
            return (a.pos == b.pos);
        }

        friend bool operator!=(const Iterator& a, const Iterator &b)
        {
            return (a.pos != b.pos);
        }

        Iterator& operator++()
        {
            if (pos == -1)
                throw std::out_of_range("Cannot increment end() iterator.");

            pos++;
            if (pos == d->capacity())
                pos = 0;
            else if (pos == d->back+1) 
                pos = -1;
            return *this;
        }

        Iterator operator++(int)
        {
            if (pos == -1)
                throw std::out_of_range("Cannot increment end() iterator.");

            Iterator copy = Iterator(pos, d);
            if ((pos+1) == d->capacity())
                pos = 0;
            else if ((pos+1) == d->back+1)
                pos = -1;
            return copy;
        }

        Iterator& operator--()
        {
            if (pos == d->front)
                throw std::out_of_range("Cannot decrement begin() iterator.");

            pos--;
            if (pos == 0)
                pos = d->capacity()-1;
            else if (pos == d->front)
                pos = -1;
            return *this;
        }

        Iterator operator--(int)
        {
            if (pos == d->front)
                throw std::out_of_range("Cannot decrement begin() iterator.");

            Iterator copy = Iterator(pos, d);
            if ((pos-1) == 0)
                pos = d->capacity()-1;
            else if ((pos-1) == d->front)
                pos = -1;
            return copy;
        }

    private:
        T* start;
        int pos;
        const Safedeque* d;
    };

    Safedeque() : data(nullptr), front(0), back(0), sz(0), cap(0)
    {}

    Safedeque(const Safedeque& d): front(d.front), back(d.back), sz(d.sz), cap(d.cap)
    {
        std::unique_ptr<T[]> _data(new T[cap]);
        auto ptr = d.data.get();
        auto _ptr = _data.get();

        std::copy(ptr, ptr+back, _ptr);
        std::copy(ptr+front, ptr+cap, _ptr+front);

        data = std::move(_data);
    }

    Safedeque& operator=(const Safedeque& d)
    {
        front = d.front; back = d.back; sz = d.sz; cap = d.cap;

        // std::unique_ptr<T[]> _data(new T[cap]);
        // auto ptr = d.data.get();
        // auto _ptr = _data.get();

        // std::copy(ptr, ptr+back, _ptr);
        // std::copy(ptr+front, ptr+cap, _ptr+front);

        // data = std::move(_data);

        auto _d(d);
        data = std::move(_d.data);

        return *this;
    }

    ~Safedeque() = default;

    T& operator[](size_t index) 
    {
        return data[index];
    }

    T& operator[](size_t index) const
    {
        return data[index];
    }

    T get_front()
    {
        if (cap == 0)
            throw std::logic_error("Container is empty.");
        return data[front];
    }

    T get_back()
    {
        if (cap == 0)
            throw std::logic_error("Container is empty.");
        return data[back];
    }

    void push_front(T val)
    {
        if (cap == 0)
        {
            front = 0;
            back = 0;
            std::unique_ptr<T[]> _data(new T[1]);
            data = std::move(_data);
            cap++;
            std::cout << "One spot added." << std::endl;
        }
        else if (cap == sz)
        {
            std::unique_ptr<T[]> _data(new T[2*cap]);
            auto ptr = data.get();
            auto _ptr = _data.get();

            for (int i = 0; i < 2*cap; i++)
                _data[i] = 0;

            std::copy(ptr, ptr+back, _ptr);
            std::copy(ptr+front, ptr+cap, _ptr+cap+front);
            data = std::move(_data);

            front = cap+front-1;
            cap = 2*cap;
            std::cout << "Capacity doubled." << std::endl;
        }
        else
        {
            front--;
        }

        data[front] = val;
        for (int i= 0; i < cap; i++)
            std::cout << data[i] << "\t";
        std::cout << std::endl;
        sz++;
    }

    void push_back(T val)
    {
        if (cap == 0)
        {
            front = 0;
            back = 0;
            std::unique_ptr<T[]> _data(new T[1]);
            data = std::move(_data);
            cap++;
            std::cout << "One spot added." << std::endl;
        }
        else if (cap == sz)
        {
            std::unique_ptr<T[]> _data(new T[2*cap]);
            auto ptr = data.get();
            auto _ptr = _data.get();

            for (int i = 0; i < 2*cap; i++)
                _data[i] = 0;

            std::copy(ptr, ptr+back, _ptr);
            std::copy(ptr+front, ptr+cap, _ptr+cap+front);
            data = std::move(_data);

            front = cap+front;
            back++;
            cap = 2*cap;
            std::cout << "Capacity doubled." << std::endl;
        }
        else
        {
            back++;
        }

        data[back] = val;
        for (int i= 0; i < cap; i++)
            std::cout << data[i] << "\t";
        std::cout << std::endl;
        sz++;
    }

    void pop_front()
    {
        if (sz == 0)
            throw std::logic_error("Deque is empty");

        if (back == 0)
            back = cap-1;
        else
            back--;
    }

    void pop_back()
    {
        if (sz == 0)
            throw std::logic_error("Deque is empty");

        if (front == cap-1)
            front = 0;
        else
            front++;
    }

    Iterator begin() const
    {
        return Iterator(front, this);
    }

    Iterator end() const
    {
        return Iterator(-1, this);
    }

    size_t size() const
    {
        return sz;
    }

    size_t capacity() const
    {
        return cap;
    }

    void print() const
    {
        for (auto it = begin(); it != end(); it++)
            std::cout << *it << "\t";
        std::cout << std::endl;
    }

    void real_print() const
    {
        // for (int i = 0; i <= back; i++)
        //     std::cout << data[i] << "\t";
        // for (int i = back+1; i < front; i++)
        //     std::cout << '*' << "\t";
        // for (int i = front; i < cap; i++)
        //     std::cout << data[i] << "\t";

        for (int i = 0; i < cap; i++)
            std::cout << data[i] << "\t";
        std::cout << std::endl;
    }

private:
    std::unique_ptr<T[]> data;
    size_t front, back, sz, cap;
};

#endif