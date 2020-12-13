#include <iostream>
#include <string>
class Employee
{
    protected:
    std::string name;
    int age;

    std::string position; // ��å(�̸�)
    int rank;             // ����(���� Ŭ ���� ���� ����)

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
                  << calculate_pay() << "����" << std::endl;
    }
    virtual int calculate_pay() const { return 200 + 50 * rank; }
};
class EmployeeList
{
    int alloc_employee;       // �Ҵ��� �� ���� ��
    int current_employee;     // ���� ���� ��
    Employee **employee_list; // Employee *�� �����Ҵ� �ϱ� ���� ����

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
                //delete prev_employee_list[i] �ϸ� �ȵȴ�. employee_list[i]�� �Űܳ��µ� �̰� ����� ������.
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
            total_pay += employee_list[i]->calculate_pay(); //��ĳ������ �������� employee_list[i]�� EmployeeŬ������ ��ü�� ����Ű�� �����̴�.
        }
        std::cout << "�� ��� : " << total_pay << "����" << std::endl;
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
              << year_of_service << "����) ==> " << calculate_pay() << "����"
              << std::endl;
        }
};

int main() {
  EmployeeList emp_list(10);
  emp_list.add_employee(new Employee("��ȫö", 34, "����", 1));
  emp_list.add_employee(new Employee("����", 34, "����", 1));

  emp_list.add_employee(new Manager("���缮", 41, "����", 7, 12));
  emp_list.add_employee(new Manager("������", 43, "����", 4, 15));
  emp_list.add_employee(new Manager("�ڸ��", 43, "����", 5, 13));
  emp_list.add_employee(new Employee("������", 36, "�븮", 2));
  emp_list.add_employee(new Employee("��", 36, "����", -2));
  emp_list.print_employee_info();
  return 0;
}