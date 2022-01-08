#pragma once // ����� �� ��������� ��������� ������
#include <iostream> // cout 
#include <string> // ������ 
#include <fstream> // ������ � ������� 
#include <iomanip> // ��� setw

using namespace std;
const string FILE_INFO_ACCOUNTS = "Accounts.txt"; // ���� ��� ��������� 

struct Accounts	// ��������� ���������
{
	string login;
	string password;
	int status; // 0 - ������������ | 1 - ������������� 
	int activation; // 0 - ������������� | 1 - ����������� 
};

void Start_program(); // ������� �� main ��� ������� ��������� 
void User_menu(); // ���� ��� ������������ | �������
void Admin_menu(Accounts* arr_of_accounts, int& number_of_accounts); // ���� ��� ������ [���.����������/������������]
void Add_accounts(Accounts* arr_of_accounts, int& number_of_accounts); // ���������� ��������� 
void Del_accounts(Accounts* arr_of_accounts, int& number_of_accounts); // ��� �������� ���������
void Show_accounts(Accounts* arr_of_accounts, int number_of_accounts); // ����� ��������� 
void Check_user_status(Accounts* arr_of_accounts, int& number_of_accounts, int role); // �������� ��� ���������������
void Read_file_accounts(Accounts* arr_of_accounts, int number_of_accounts); // ������|������� ��������� �� ����� 
void Write_file_accounts(Accounts* arr_of_accounts, int number_of_accounts); // �������� ��������� � ����
void Admin_accounts_menu(Accounts* arr_of_accounts, int& number_of_accounts); // ���������� ���������� 
void �heck_accounts_number(int& number_of_accounts); // ����������� ���������� ��������� � �����
void Check_login_and_password(Accounts* arr_of_accounts, int& number_of_accounts); // �������� ������ � ������ 

Accounts* Authorization_menu(Accounts* arr_of_accounts, int& number_of_accounts); // ���� ����������� [����/�����������]
Accounts* Memory_reallocation_for_accounts(Accounts* arr_of_accounts, int& number_of_accounts, int m); // ������������� ������
 
