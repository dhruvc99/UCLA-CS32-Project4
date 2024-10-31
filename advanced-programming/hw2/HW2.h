/**
 * @file HW2.h 
 * @author Dhruv Chakraborty
 * @brief Review I/O, maps and class hierarchies
 * PIC 10C Homework 2
 */

#ifndef HW2_H
#define HW2_H

#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<map>

class Person
{
    public: 
        Person() {};
        void setname(string s){name=s;};

    private:
        string name;
        template<tyename T, int T_LINE_SIZE>
        virtual void read(ifstream fin, std::map<std::string, T*> m) = 0;
};

class Employee: virtual public Person
{
    public:
        Employee(name, ID, sal)
        {
            setname(name)
            set_id(ID);
            set_salary(sal);
        }
        void set_id(string s){id=s;};
        void set_salary(double d){salary=d;};

    private:
        string id;
        double salary;

        template<typename T, int T_LINE_SIZE>
        void read(ifstream fin, std::map<std::string, T*> m)
        {
            std::string line;
            while(std::getine(fin, line))
            {
                string name = line.substr(0, 20);
                string ID = line.substr(20, 30);
                double salary  = std::stod(line.substr(30, 40));
                T* emp = new Employee(name, ID, Salary);
                m.insert(name, emp);
            })
        }
};

class Student: virtual public Person
{
    public:
        Student(name, ID)
        {
            setname(name);
            set_id(ID);
        }
        void set_id(string s){id=s;};
    private:
        string id;

        template<typename T, int T_LINE_SIZE>
        void read(ifstream fin, std::map<std::string, T*> m)
        {
            std::string line;
            while(std::getine(fin, line))
            {
                string name = line.substr(0, 20);
                string ID = line.substr(20, 30);
                T* stu = new Student(name, ID);
                m.insert(name, stu);
            })
        }
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

template<typename T, int T_LINE_SIZE>
void read(ifstream fin, std::map<std::string, T*> m)
{
    std::string line;
    while(std::getine(fin, line))
    {
        string name = line.substr(0, 20);
        string ID = line.substr(20, 30);
        if(T_LINE_SIZE>40)
        {
            double salary = line.substr(30, 40);
            T* t = new Employee()
        }
        T* stu = new Student(name, ID);
        m.insert(name, stu);
    })
}

#endif