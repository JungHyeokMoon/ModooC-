#include <iostream>
#include <string>
class Employee
{
    protected:
    std::string name;
    int age;

    std::string position; // 직책(이름)
    int rank;             // 순위(값이 클 수록 높은 순위)

public:
    Employee(std::string name, int age, std::string position, int rank) : name(name), age(age), position(position), rank(rank) {}
    Employee(const Employee &e)
    {
        name = e.name;
        age = e.age;
        position = e.position;
        rank = e.rank;
    }
    Employee() {}
    virtual void print_info() const
    {
        std::cout << name << " (" << position << " , " << age << ") ==> "
                  << calculate_pay() << "만원" << std::endl;
    }
    virtual int calculate_pay() const { return 200 + 50 * rank; }
};
class EmployeeList
{
    int alloc_employee;       // 할당한 총 직원 수
    int current_employee;     // 현재 직원 수
    Employee **employee_list; // Employee *를 동적할당 하기 위해 선언

public:
    EmployeeList(int alloc_employee) : alloc_employee(alloc_employee)
    {
        employee_list = new Employee *[alloc_employee];
        current_employee = 0;
    }
    void add_employee(Employee *employee)
    {
        if (current_employee == alloc_employee)
        {
            Employee **prev_employee_list = employee_list;
            alloc_employee *= 2;
            employee_list = new Employee *[alloc_employee];
            for (int i = 0; i < current_employee; i++){
                employee_list[i] = prev_employee_list[i];
                //delete prev_employee_list[i] 하면 안된다. employee_list[i]에 옮겨놨는데 이걸 지우면 오류뜸.
            }
            
            delete[] prev_employee_list;
        }
        employee_list[current_employee++] = employee;
    }
    int current_employee_num() const { return current_employee; }
    void print_employee_info() const
    {
        int total_pay = 0;
        for (int i = 0; i < current_employee; i++)
        {
            employee_list[i]->print_info();
            total_pay += employee_list[i]->calculate_pay(); //업캐스팅은 괜찮지만 employee_list[i]는 Employee클래스의 객체를 가리키기 때문이다.
        }
        std::cout << "총 비용 : " << total_pay << "만원" << std::endl;
    }
    ~EmployeeList()
    {
        for (int i = 0; i < current_employee; i++)
            delete employee_list[i];
        delete[] employee_list;
    }
};
class Manager : public Employee{
    int year_of_service;

    public:
        Manager(std::string name, int age, std::string position, int rank, int year_of_service):Employee(name,age,position,rank),year_of_service(year_of_service){}
        Manager(const Manager & m): Employee(m.name,m.age,m.position,m.rank){
            year_of_service=m.year_of_service;
        }
        Manager(){}
        int calculate_pay()const override{return 200+rank*50+5*year_of_service;}
        void print_info()const override{
            std::cout << name << " (" << position << " , " << age << ", "
              << year_of_service << "년차) ==> " << calculate_pay() << "만원"
              << std::endl;
        }
};

int main() {
  EmployeeList emp_list(10);
  emp_list.add_employee(new Employee("노홍철", 34, "평사원", 1));
  emp_list.add_employee(new Employee("하하", 34, "평사원", 1));

  emp_list.add_employee(new Manager("유재석", 41, "부장", 7, 12));
  emp_list.add_employee(new Manager("정준하", 43, "과장", 4, 15));
  emp_list.add_employee(new Manager("박명수", 43, "차장", 5, 13));
  emp_list.add_employee(new Employee("정형돈", 36, "대리", 2));
  emp_list.add_employee(new Employee("길", 36, "인턴", -2));
  emp_list.print_employee_info();
  return 0;
}