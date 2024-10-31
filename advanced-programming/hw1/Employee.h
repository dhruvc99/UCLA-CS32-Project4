/**
 * @file Employee.h 
 * @author Dhruv Chakraborty
 * @brief Define toy employee class
 * PIC 10C Homework 1
 */

#include<iostream>
#include<string>
using namespace std;

class Employee
{
private:
    string name;
    int salary;
    
public:
    Employee(string _name, int _salary)
    : name(_name), salary(_salary)
    {};

    friend ostream& operator<<(ostream &os, const Employee e) 
    {
        os << e.name;
        return os;
    }

    int get_salary() const
    {
        return(salary);
    }
};

class CompareBySalary
{
public:
    bool operator() (const Employee& e1, const Employee& e2) const 
    {
        return (e1.get_salary() < e2.get_salary());
    }
};