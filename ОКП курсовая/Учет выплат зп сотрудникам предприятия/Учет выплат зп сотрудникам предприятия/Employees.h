#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
const string FILE_INFO_EMPLOYEES = "Employee.txt";

struct Employee	// ��������� ����������� 
{
	string Name;
	string Surname;
	string Patronymic;
	string Department;
	string Position;
	int Salary;
};

struct Department // ��������� ������� 
{
	string Department_name; // �������� ������ 
	int Employees_amount = 0; // ���������� ����������� ������
	int Total_department_salary = 0; // �� ����� ������ 
};

// �������� �������_____________________________________________________________________________________________________________________

void User_menu(); // ���� ������������ 
void Check_employees_file(int& number_of_Employees); // ����������� ���������� ����������� 
void Show_employees(Employee* arr_of_Employees, int number_of_Employees); // ����� �����������  
void Add_employees(Employee* arr_of_Employees, int& number_of_Employees); // ���������� �����������
void Delete_employees(Employee* arr_of_Employees, int& number_of_Employees); // �������� ����������� 
void Write_to_employees_file(Employee* arr_of_Employees, int number_of_Employees); // ������ � ����
void Read_from_employees_file(Employee* arr_of_Employees, int number_of_Employees); // ������ �� �����
void Updating_of_employees_information(Employee* arr_of_Employees, int& number_of_Employees); // ���������� ���������� � �����������

Employee* Memory_reallocation_for_employees(Employee* arr_of_Employees, int& number_of_Employees, int m); // ������������� ������
Employee* Menu_employees(Employee* arr_of_Employees, int& number_of_Employees); // ���� ��� ������ ��������


// �������������� �������__________________________________________________________________________________________________________________

void Menu_individual_task(Employee* arr_of_Employees, int number_of_Employees); // ����� ��������������� �������
void Individual_task_salary_info(Employee* arr_of_Employees, int number_of_Employees); // �������������� ������� �1: ����� ����������� � �� < ��������� � ����������
void Individual_task_departments_info(Employee* arr_of_Employees, int number_of_Employees); // �������������� ������� �2: ���� �� ������� | ����� �� | ������� ��

Department* Individual_task_department_memory_reallocation(Department* arr_of_dep, int& number_of_dep, int m); // �������������� ������� �2.1: ������������� ������ 


// ����������______________________________________________________________________________________________________________________________

Employee* Sorting_by_Surname(Employee* arr_of_Employees, int number_of_Employees); // ���������� �1: �� �������� 
Employee* Sorting_by_department(Employee* arr_of_Employees, int number_of_Employees); // ���������� �2: �� �������
Employee* Sorting_by_the_salary(Employee* arr_of_Employees, int number_of_Employees); // ���������� �3: �� ��������
Employee* Selection_sorting_menu(Employee* arr_of_Employees, int number_of_Employees); // ����� ����������


// �����_____________________________________________________________________________________________________________________________________

void Find_surname(Employee* arr_of_Employees, int number_of_Employees); // ����� �1: �� �������
void Find_position(Employee* arr_of_Employees, int number_of_Employees); // ����� �2: �� ���������
void Find_max_salary(Employee* arr_of_Employees, int number_of_Employees); // ����� �3: �� ������������ ��
void Show_result_of_finding(Employee* arr_of_Employees, int number_of_Employees, int i); // ����� ��� ������
void Menu_of_finding_employees(Employee* arr_of_Employees, int number_of_Employees); // ����� ������ 