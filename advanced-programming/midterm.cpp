#include <iostream>
#include <vector>
#include <stdexcept>

// // Q2

// // Helper function for foo() to handle one element case
// template<typename CMP, typename T>
// T foo(CMP comparator, const T& ele)
// {
//     return ele;
// }

// template<typename CMP, typename T, typename... Ts>
// T foo(CMP comparator, const T& ele1, const T& ele2, const Ts& ... eles)
// {
//     // Iterate over parameters, comparing the "smallest"/"largest"
//     // element we come across with each following element
//     if (comparator(ele1, ele2))
//         return foo(comparator, ele1, eles...); 
//     else
//         return foo(comparator, ele2, eles...);
// }

// // Q3
// class Person
// {
//     public: 
//         Person(){};
//         void setname(std::string s){name=s;};
//         void print(){std::cout<<name;}
//         virtual ~Person() {};
//     private:
//         std::string name;
// };

// class Student: virtual public Person
// {
//     public:
//         Student(){};
//         void set_id(std::string s){id=s;};
//     private:
//         std::string id;
// };

// class Employee: virtual public Person
// {
//     public:
//         Employee(){salary=0;};
//         Employee(std::string name, std::string id, double salary);
//         void set_id(std::string s){id=s;};
//         void set_salary(double d){salary=d;};
//         // virtual ~Employee();
//     private:
//         std::string id;
//         double salary;
// };

// Employee::Employee(std::string name, std::string id, double salary)
// {
//     setname(name);
//     set_id(id);
//     set_salary(salary);
// }

// class TA: public Student, public Employee
// {
//     public:
//         TA(std::string t_name, std::string s_id, std::string e_id, double t_salary);
// };

// class People 
// {
// public:
//     // People(); // default constructor
//     // People(const People&); // copy constructor
//     // People& operator=(const People&); // copy-assignment operator
//     ~People(); // destructor
//     void add_person(Person* p); // function to add person to data
// private:
//     std::vector<Person*> data;
// };

// People::~People()
// {
//     for (auto iter = data.begin(); iter != data.end(); ++iter)
//     {
//         delete *iter;
//     }
// }

// void People::add_person(Person* p)
// {
//     data.push_back(p);
// }

// Q4

// double division()
// {
//     int m, n;
//     std::cout << "Please enter two integers."
//              << "The second one can't be zero." << std::endl;
    
//     try {
//         std::cin >> m >> n;
//         if (n==0)
//             throw std::logic_error("Denominator can't be zero.");
//         else
//             return double(m)/n;
//     }
//     catch (std::logic_error& e)
//     {
//         std::cout << e.what() << std::endl;
//         throw;
//     }
// }


// Q5

class Stringpair
{
friend Stringpair operator+(const Stringpair& x, const Stringpair& y)
{
    Stringpair result = Stringpair(*(x.first)+*(y.first), *(x.second)+*(y.second));
    return result;
}
public:
    Stringpair() = default;
    Stringpair(const std::string& f, const std::string& s)
    {
        first = new std::string(f);
        second = new std::string(s);
    }
    Stringpair(const Stringpair& p)
    {
        std::cout << "copy constructor" << std::endl;
        first = new std::string(*(p.first));
        second = new std::string(*(p.second));
    }
    Stringpair& operator=(const Stringpair& p)
    {
        Stringpair result(*(p.first), *(p.second));
        first = result.first;
        second = result.second;
        return *this;
    }
    ~Stringpair()
    {
        std::cout << "destructor" << std::endl;
        delete first;
        delete second;
    }
    void print()
    {
        std::cout << *first << ", " << *second << std::endl;
    }
    void wipe_first()
    {
        *first = "";
    }
private:
    std::string* first;
    std::string* second;
};


int main()
{
    // std::cout << foo(std::less<int>(), 4, 1, 2, 3) << std::endl;
    // std::cout << foo(std::greater<char>(), 'z', 'a', 'c') << std:: endl;

    // People StudyGroup;
    // StudyGroup.add_person(new Employee("Tom", "E123", 1002.02));


    // while(true)
    // {
    //     try
    //     {
    //         std::cout << division() << std::endl;
    //         break;
    //     }
    //     catch(std::logic_error& e) // catch logic error that we rethrew above
    //     {
    //         // Ask user if they would like to try again
    //         std::cout << "Would you like to retry? (y/n)" << std::endl;
    //         char c;
    //         std::cin >> c;
    //         // Confirm input is a character
    //         // and if it is 'y', let them retry
    //         if (!std::cin.fail() && c == 'y')
    //             continue;
    //         else // otherwise end program
    //             break;
    //     }
    // }

    // Stringpair x = Stringpair("a", "b");
    // Stringpair y = Stringpair("c", "d");
    // Stringpair u = x+y;
    // Stringpair z(u);
    // u.wipe_first();
    // z.print();

    Stringpair x("a", "b");
    Stringpair* y = new Stringpair(x);
    Stringpair z;
    z = x+(*y);
    Stringpair pairs[3] = {x, z};
    delete y;

    return 0;
}