#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
const string FILE_INFO_EMPLOYEES = "Employee.txt";

struct Employee	// Структура сотрудников 
{
	string Name;
	string Surname;
	string Patronymic;
	string Department;
	string Position;
	int Salary;
};

struct Department // Структура отделов 
{
	string Department_name; // Название отдела 
	int Employees_amount = 0; // Количество сотрудников отдела
	int Total_department_salary = 0; // ЗП всего отдела 
};

// ОСНОВНЫЕ ФУНКЦИИ_____________________________________________________________________________________________________________________

void User_menu(); // Меню пользователя 
void Check_employees_file(int& number_of_Employees); // Определение количества сотрудников 
void Show_employees(Employee* arr_of_Employees, int number_of_Employees); // Вывод сотрудников  
void Add_employees(Employee* arr_of_Employees, int& number_of_Employees); // Добавление сотрудников
void Delete_employees(Employee* arr_of_Employees, int& number_of_Employees); // Удаление сотрудников 
void Write_to_employees_file(Employee* arr_of_Employees, int number_of_Employees); // Запись в файл
void Read_from_employees_file(Employee* arr_of_Employees, int number_of_Employees); // Чтение из файла
void Updating_of_employees_information(Employee* arr_of_Employees, int& number_of_Employees); // Обновление информации о сотрудниках

Employee* Memory_reallocation_for_employees(Employee* arr_of_Employees, int& number_of_Employees, int m); // Перевыделение памяти
Employee* Menu_employees(Employee* arr_of_Employees, int& number_of_Employees); // Меню для выбора действия


// ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ__________________________________________________________________________________________________________________

void Menu_individual_task(Employee* arr_of_Employees, int number_of_Employees); // Выбор индивидуального задания
void Individual_task_salary_info(Employee* arr_of_Employees, int number_of_Employees); // Индивидуальное задание №1: Вывод сотрудников с ЗП < введенной с клавиатуры
void Individual_task_departments_info(Employee* arr_of_Employees, int number_of_Employees); // Индивидуальное задание №2: Инфа по отделам | Общая ЗП | Средняя ЗП

Department* Individual_task_department_memory_reallocation(Department* arr_of_dep, int& number_of_dep, int m); // Индивидуальное задание №2.1: Перевыделение памяти 


// СОРТИРОВКА______________________________________________________________________________________________________________________________

Employee* Sorting_by_Surname(Employee* arr_of_Employees, int number_of_Employees); // Сортировка №1: По фамилиям 
Employee* Sorting_by_department(Employee* arr_of_Employees, int number_of_Employees); // Сортировка №2: По отделам
Employee* Sorting_by_the_salary(Employee* arr_of_Employees, int number_of_Employees); // Сортировка №3: По зарплате
Employee* Selection_sorting_menu(Employee* arr_of_Employees, int number_of_Employees); // Выбор сортировки


// ПОИСК_____________________________________________________________________________________________________________________________________

void Find_surname(Employee* arr_of_Employees, int number_of_Employees); // Поиск №1: По фамилии
void Find_position(Employee* arr_of_Employees, int number_of_Employees); // Поиск №2: По должности
void Find_max_salary(Employee* arr_of_Employees, int number_of_Employees); // Поиск №3: По максимальной ЗП
void Show_result_of_finding(Employee* arr_of_Employees, int number_of_Employees, int i); // Вывод для поиска
void Menu_of_finding_employees(Employee* arr_of_Employees, int number_of_Employees); // Выбор поиска 