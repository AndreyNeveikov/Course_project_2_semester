#pragma once // Чтобы не произошел повторный запуск
#include <iostream> // cout 
#include <string> // Строки 
#include <fstream> // Работа с файлами 
#include <iomanip> // Для setw

using namespace std;
const string FILE_INFO_ACCOUNTS = "Accounts.txt"; // Файл для аккаунтов 

struct Accounts	// Структура аккаунтов
{
	string login;
	string password;
	int status; // 0 - пользователь | 1 - администратор 
	int activation; // 0 - деактивирован | 1 - активирован 
};

void Start_program(); // Функция из main для запуска программы 
void User_menu(); // Меню для пользователя | Переход
void Admin_menu(Accounts* arr_of_accounts, int& number_of_accounts); // Меню для админа [Упр.аккаунтами/сотрудниками]
void Add_accounts(Accounts* arr_of_accounts, int& number_of_accounts); // Добавление аккаунтов 
void Del_accounts(Accounts* arr_of_accounts, int& number_of_accounts); // Для удаление аккаунтов
void Show_accounts(Accounts* arr_of_accounts, int number_of_accounts); // Вывод аккаунтов 
void Check_user_status(Accounts* arr_of_accounts, int& number_of_accounts, int role); // Проверка кто авторизировался
void Read_file_accounts(Accounts* arr_of_accounts, int number_of_accounts); // Чтение|Перенос аккаунтов из файла 
void Write_file_accounts(Accounts* arr_of_accounts, int number_of_accounts); // Записать аккаунтов в файл
void Admin_accounts_menu(Accounts* arr_of_accounts, int& number_of_accounts); // Управление аккаунтами 
void Сheck_accounts_number(int& number_of_accounts); // Определение количества аккаунтов в файле
void Check_login_and_password(Accounts* arr_of_accounts, int& number_of_accounts); // Проверка логина и пароля 

Accounts* Authorization_menu(Accounts* arr_of_accounts, int& number_of_accounts); // Меню авторизации [Вход/Регистрация]
Accounts* Memory_reallocation_for_accounts(Accounts* arr_of_accounts, int& number_of_accounts, int m); // Перевыделение памяти
 
