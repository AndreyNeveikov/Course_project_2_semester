#pragma once
#include <iostream> // ���� | ����� >> cout 
#include <Windows.h> // ��� ��������� ����� 

using namespace std;

void Save_it(); // ����� ������ ������� ���������!
void Set_color(int text, int bg); // ��������� �����
void Ask_for_saving(); // ������ ���������? 
void Account_not_found(); // ������ �������� ��� � �������
void Password_incorrect(string TempLogin, bool& flagPassword, int& amount); // ������� ������ ���� ��������� ��� ����� �� ��� ������ [����/�����������]