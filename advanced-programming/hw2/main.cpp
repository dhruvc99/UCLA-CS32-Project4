#include<fstream>
#include<string>
#include<map>
#include"HW2.h"
using namespace std;

const int STUDENT_SIZE = 30+1;
const int EMPLOYEE_SIZE = 40+1;
const int TA_SIZE = 50+1;

int main()
{
    //
    ifstream fin; 
    std::map<std::string, Student*> students;
    std::map<std::string, Employee*> employees;

    // read students 
    fin.open("Students.txt");
    read<Student, STUDENT_SIZE>(fin, students);
    fin.close();
    cout << "*****************Students********************\n"; 
    print(cout, students);


    // read employees 
    fin.open("Employees.txt");
    read<Employee, EMPLOYEE_SIZE>(fin, employees);
    fin.close();
    cout << "*****************Employees********************\n"; 
    print(cout, employees);

    // combine two files assuming each person has different names
    std::map<std::string, Person*> combined;
    combine(students, employees, combined);
    
    // output the combined list into a file "Combined.txt"
    // persons are outputed in the order of 'name' attribute std::less
    ofstream fout;
    fout.open("Combined.txt");
    print(fout, combined);
    fout.close();

    // output the combined list to the console
    cout << "****************Combined***********************\n"; 
    print(cout, combined);
    return 0;
}
