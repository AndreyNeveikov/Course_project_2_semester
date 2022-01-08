#include "Employees.h"
#include "Protection.h"
#include "Signal.h"

// ��������� ���������� >>  ���  |       �����        | ���������  | �� 
// ��������� �������    >> ����� | ���-�� ����������� | ����� ��
// ��� >> ����� ������ �� ������� | ������� �� �� ������� | ������� ����������� � �� ���� ��������� 
// ��������� ���� ������������ ��� �������� �� ����� � ����������

void User_menu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int number_of_Employees = 0;
	Check_employees_file(number_of_Employees); // ����������� ������� ������� 
	Employee* arr_of_Employees = new Employee[number_of_Employees]; // �������� ����� ������ 
	Read_from_employees_file(arr_of_Employees, number_of_Employees); // ������ ����� � ������� ������ � ������� 
	arr_of_Employees = Menu_employees(arr_of_Employees, number_of_Employees); // ���� �����������

	Write_to_employees_file(arr_of_Employees, number_of_Employees); // ���������� �����������
	delete[] arr_of_Employees;
}

// ����������� ���������� �����������_______________________________________________________________________________________________

void Check_employees_file(int& number_of_Employees)
{
	string temp;
	ifstream fin(FILE_INFO_EMPLOYEES, ios::in); // ������� ���� ��� ������ 
	if (!fin.is_open())
	{
		number_of_Employees = 1;
	}
	else
	{
		while (!fin.eof()) // ���� �� ������ �� ����� ����� 
		{
			fin >> temp >> temp >> temp >> temp >> temp >> temp;
			number_of_Employees++;
		}
	}
	fin.close();
}

// ������ � ������ ���������� � ������� ��������_________________________________________________________________________________

void Read_from_employees_file(Employee* arr_of_Employees, int number_of_Employees)
{
	ifstream fin(FILE_INFO_EMPLOYEES, ios::in);
	if (!fin.is_open()) // ���� ����� 
	{
		Set_color(12, 0);
		cout << "                                ________________________________________________________________" << endl;
		cout << "                                |                                                              |" << endl;
		cout << "                                |                   ������ ����������� ����!                   |" << endl;
		cout << "                                |           ����������, �������� ������� ����������!           |" << endl;
		cout << "                                |______________________________________________________________|" << endl;
		Set_color(7, 0);
		Add_employees(arr_of_Employees, number_of_Employees); // ��������� ������� ���������� �����������
	}
	else // ���� ���������� ��� ���� � ����� 
	{
		int i = 0;
		while (!fin.eof()) // ��������� ��� ���������� �� ����� 
		{
			fin >> arr_of_Employees[i].Name >> arr_of_Employees[i].Surname >> arr_of_Employees[i].Patronymic >>
				arr_of_Employees[i].Department >> arr_of_Employees[i].Position >> arr_of_Employees[i].Salary;
			i++;
		}
	}
	fin.close();
}

// ������ � ����___________________________________________________________________________________________________________________________

void Write_to_employees_file(Employee* arr_of_Employees, int number_of_Employees)
{
	ofstream fout(FILE_INFO_EMPLOYEES, ios::out); // ��� ���������� � ����
	for (int i = 0; i < number_of_Employees; i++)
	{
		fout << arr_of_Employees[i].Name << " " << arr_of_Employees[i].Surname << " " << arr_of_Employees[i].Patronymic << " " <<
			arr_of_Employees[i].Department << " " << arr_of_Employees[i].Position << " " << arr_of_Employees[i].Salary;
		if (i < number_of_Employees - 1) // endl ���� �� ������ �� ���������� ���������� 
			fout << endl;
	}
	fout.close();
}

// ���� ����������� (����� ��������)______________________________________________________________________________________

Employee* Menu_employees(Employee* arr_of_Employees, int& number_of_Employees)
{
	bool flag = true; // ��� ��������� ����� 
	while (flag)
	{

		Set_color(1, 0); // ����� | ���� ������ | ���� ����
		cout << "                                            _______________________________________           " << endl;
		cout << "                                           /                                       \\         " << endl;
		cout << "                                          /       � � � � | � � � � � � � � � �     \\        " << endl;
		cout << "                                         /|_________________________________________|\\       " << endl;
		Set_color(7, 0); // ������-�����
		cout << "                                         ||                                         ||        " << endl;
		cout << "                                         ||        1. �������� ���� �����������     ||        " << endl;
		cout << "                                         ||        2. �������� ����������           ||        " << endl;
		cout << "                                         ||        3. ������������� ������          ||        " << endl;
		cout << "                                         ||        4. ������� ����������            ||        " << endl;
		cout << "                                         ||        5. �������������� �������        ||        " << endl;
		cout << "                                         ||        6. ����������                    ||        " << endl;
		cout << "                                         ||        7. �����                         ||        " << endl;
		cout << "                                         ||_________________________________________||        " << endl;
		cout << "                                         ||                                         ||        " << endl;
		cout << "                                         ||        0. ��������� �����               ||        " << endl;
		cout << "                                         ||_________________________________________||        " << endl;
		cout << "                                               >>";

		int sw;
		Protection(0, 7, sw); // ������ �� ����� �� ���� � �������� [0-7]
		switch (sw)
		{
		case 1: // ����� ���� � ����������� 
			system("cls");
			Show_employees(arr_of_Employees, number_of_Employees);
			break;
		case 2: // ���������� ����� ����������� 
			arr_of_Employees = Memory_reallocation_for_employees(arr_of_Employees, number_of_Employees, number_of_Employees + 1); // ����������������� ������ �.�. �� ��������� ����������� 
			Add_employees(arr_of_Employees, number_of_Employees); // ��� ���������� 
			break;
		case 3: // ���������� ���������� � ����������� 
			Updating_of_employees_information(arr_of_Employees, number_of_Employees);
			break;
		case 4: // �������� 
			Show_employees(arr_of_Employees, number_of_Employees);
			Delete_employees(arr_of_Employees, number_of_Employees);
			break;
		case 5: // ���
			Menu_individual_task(arr_of_Employees, number_of_Employees);
			break;
		case 6: // ���������� 
			arr_of_Employees = Selection_sorting_menu(arr_of_Employees, number_of_Employees);
			break;
		case 7: // �����
			Menu_of_finding_employees(arr_of_Employees, number_of_Employees);
			break;
		case 0:
			system("cls");
			flag = false;
			break; // ���� ����� ����� ������ ���� �� false 
		}
	}
	return arr_of_Employees;
}

// �������� ���� �����������____________________________________________________________________________________________________________________

void Show_employees(Employee* arr_of_Employees, int number_of_Employees)
{
	Set_color(14, 0);
	cout << "                                             _____________________________________                            " << endl;
	cout << "                                            /                                     \\                          " << endl;
	cout << "                  _________________________/  � � � � � � | � � � � � � � � � � �  \\_________________________ " << endl;
	cout << "                  |                                                                                         | " << endl << endl;
	Set_color(3, 0);
	cout << "                       " <<
		setw(12) << left << "�������" <<
		setw(12) << left << "���" <<
		setw(18) << left << "��������" <<
		setw(15) << left << "�����" <<
		setw(15) << left << "���������" <<
		setw(15) << left << "��������" << endl;

	cout << endl;
	for (int i = 0; i < number_of_Employees; i++)
	{
		Set_color(9, 0);
		cout << "                       " <<
			setw(12) << left << arr_of_Employees[i].Surname <<
			setw(12) << left << arr_of_Employees[i].Name <<
			setw(18) << left << arr_of_Employees[i].Patronymic <<
			setw(15) << left << arr_of_Employees[i].Department <<
			setw(15) << left << arr_of_Employees[i].Position <<
			setw(15) << left << arr_of_Employees[i].Salary << endl;
	}
	Set_color(7, 0);
}

// ������������� ������___________________________________________________________________________________________________________

Employee* Memory_reallocation_for_employees(Employee* arr_of_Employees, int& number_of_Employees, int m)
{

	Employee* temp_arr = new Employee[m]; // �������� ������ ��� ������ �������� 
	for (int i = 0; i < number_of_Employees; i++) // ��������� ������ ������
	{
		temp_arr[i].Name = arr_of_Employees[i].Name;
		temp_arr[i].Surname = arr_of_Employees[i].Surname;
		temp_arr[i].Patronymic = arr_of_Employees[i].Patronymic;
		temp_arr[i].Department = arr_of_Employees[i].Department;
		temp_arr[i].Position = arr_of_Employees[i].Position;
		temp_arr[i].Salary = arr_of_Employees[i].Salary;
	}

	delete[]arr_of_Employees; // ������� ������ ������ 
	number_of_Employees = m; // ��������� ���������� ����������� 
	arr_of_Employees = temp_arr; // ��������� ���������� 
	return arr_of_Employees; // ���������� ����������� ����
}

// ���������� ������ ����������____________________________________________________________________________________________________

void Add_employees(Employee* arr_of_Employees, int& number_of_Employees)
{
	Set_color(14, 0);
	cout << "                                ________________________________________________________________" << endl;
	cout << "                                |                                                              |" << endl;
	cout << "                                |                  ���������� ������ ����������!               |" << endl;
	cout << "                                |______________________________________________________________|" << endl;
	Set_color(7, 0);
	cout << "                                                       ������� �������: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Surname; // -1 �.�. �������������� � 0 
	cout << "                                                       ������� ���: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Name;
	cout << "                                                       ������� ��������: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Patronymic;
	cout << "                                                       ������� �����: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Department;
	cout << "                                                       ������� ���������: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Position;
	cout << "                                                       ������� ��������: ";
	Protection(0, 10000000000000000, arr_of_Employees[number_of_Employees - 1].Salary);
	Save_it();
}

// ������������� ���������� � ����������___________________________________________________________________________________________________

void Updating_of_employees_information(Employee* arr_of_Employees, int& number_of_Employees)
{
	system("cls");
	Show_employees(arr_of_Employees, number_of_Employees); // ������� �� ����� ���� ����������� 
	string temp; // ������ ��� ������� 
	bool flag = true;
	int i = 0;
	cout << "                               ____________________________________________________________________" << endl;
	cout << "                                   ������� ������� ����������, ��� ������ ������ ��������: ";
	cin >> temp;
	while (flag && i < number_of_Employees) // ���� ��� ������ ������� | ���� flag true � ���� �� ��������� ���� �����������
	{
		if (temp == arr_of_Employees[i].Surname) // ����� ���������� --> ���������� ���� 
		{
			flag = false;
		}
		else // ����� ��� ������ 
		{
			i++;
		}
	}

	if (flag) // ���� ������ �� ����� 
	{
		Account_not_found(); // ������� ������ � ����� �������� ����
	}
	else // ���� ����� | ����� ����� while --> ���������� ��� ����� �������� 
	{

		Set_color(1, 0); // ����� | ���� ������ | ���� ����
		cout << "                                           _________________________________________            " << endl;
		cout << "                                          /                                         \\          " << endl;
		cout << "                                         /   � � � � | � � � � � � � � � � � � � �   \\         " << endl;
		cout << "                                        /|___________________________________________|\\        " << endl;
		Set_color(7, 0); // ������-�����
		cout << "                                        ||                                           ||         " << endl;
		cout << "                                        ||            1. �������� ���                ||         " << endl;
		cout << "                                        ||            2. �������� �������            ||         " << endl;
		cout << "                                        ||            3. �������� ��������           ||         " << endl;
		cout << "                                        ||            4. �������� �����              ||         " << endl;
		cout << "                                        ||            5. �������� ���������          ||         " << endl;
		cout << "                                        ||            6. �������� ��������           ||         " << endl;
		cout << "                                        ||___________________________________________||         " << endl;
		cout << "                                        ||                                           ||         " << endl;
		cout << "                                        ||            0. ��������� �����             ||         " << endl;
		cout << "                                        ||___________________________________________||         " << endl;
		cout << "                                              >>";

		int sw;
		Protection(0, 6, sw);
		switch (sw)
		{
		case 1:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      ������� ����� ���: ";
			cin >> arr_of_Employees[i].Name;
			Save_it(); // ����� ������ ������� ���������
			break;
		case 2:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      ������� ����� �������: ";
			cin >> arr_of_Employees[i].Surname;
			Save_it();
			break;
		case 3:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      ������� ����� ��������: ";
			cin >> arr_of_Employees[i].Patronymic;
			Save_it();
			break;
		case 4:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      ������� ����� �����: ";
			cin >> arr_of_Employees[i].Department;
			Save_it();
			break;
		case 5:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      ������� ����� ���������: ";
			cin >> arr_of_Employees[i].Position;
			Save_it();
			break;
		case 6:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      ������� ����� ��������: ";
			cin >> arr_of_Employees[i].Salary;
			Save_it();
			break;

		case 0:  break;
		}
	}
}

// �������� ����������____________________________________________________________________________________________________________________

void Delete_employees(Employee* arr_of_Employees, int& number_of_Employees)
{
	string delEmployee;
	cout << "                               ________________________________________________________________" << endl;
	cout << "                                     ������� ������� ����������, �������� ������ �������: ";
	cin >> delEmployee;
	int i = 0;
	bool flag = true;
	while (flag && i <= number_of_Employees) // ���� ��� ������ ������� �������� 
	{
		if (arr_of_Employees[i].Surname == delEmployee)
		{
			flag = false; // ���� ����� - �������� flag 
		}
		else
		{
			i++;
		}
	}

	if (flag) // ���� �� ����� 
	{
		Account_not_found(); // ����� ������� ������ ��� (������� ���������)
	}
	else // ���� ����� 
	{
		int del = 0;
		cout << "�� ������������� ������ ������� ����������: " << arr_of_Employees[i].Surname << endl;
		cout << "P.S. ��������� ������ �� �������� ��������������." << endl;
		cout << " 1. ��" << "\n 2. ���" << "\n --> ";
		Protection(1, 2, del);
		if (del == 1)
		{
			for (int j = i; j < number_of_Employees - 1; j++) // i -> ����� �������� | �������� � ����� ���������� ��������
			{
				arr_of_Employees[j] = arr_of_Employees[j + 1];
			}
			number_of_Employees--; // ��������� ���������� �����������
			Save_it(); // ������ ������� ���������
		}
		else
		{
			cout << "�������� ��������" << endl;
		}
	}
}


// �������������� �������______________________________________________________________________________________________________________


// ����� ���

void Menu_individual_task(Employee* arr_of_Employees, int number_of_Employees)
{

	Set_color(1, 0); // ����� | ���� ������ | ���� ����
	cout << "                                    ______________________________________________________            " << endl;
	cout << "                                   /                                                      \\          " << endl;
	cout << "                                  /  � � � � | � � � � � � � � � � � � � �  � � � � � � �  \\         " << endl;
	cout << "                                 /|________________________________________________________|\\        " << endl;
	Set_color(7, 0); // ������-�����
	cout << "                                 ||                                                        ||         " << endl;
	cout << "                                 ||             1. ���������� � ��������� < ���������      ||         " << endl;
	cout << "                                 ||             2. ���������� �� �������                   ||         " << endl;
	cout << "                                 ||________________________________________________________||         " << endl;
	cout << "                                 ||                                                        ||         " << endl;
	cout << "                                 ||             0. ��������� �����                         ||         " << endl;
	cout << "                                 ||________________________________________________________||         " << endl;
	cout << "                                               >>";

	int sw;
	Protection(0, 2, sw);
	switch (sw)
	{
	case 1:
		Individual_task_salary_info(arr_of_Employees, number_of_Employees); break;
	case 2:
		Individual_task_departments_info(arr_of_Employees, number_of_Employees); break;
	case 0:
		break;
	}
}

// ��� �1 (����� ����������� � �� ������ ��������� � ����������)__________________________________________________________________________

void Individual_task_salary_info(Employee* arr_of_Employees, int number_of_Employees) // � �� ������ ��������� 
{
	cout << "                                    ________________________________________________________   " << endl;
	cout << "                                   /                                                        \\  " << endl;
	cout << "                                  /            ���������� � �� ������ ���������!             \\ " << endl;
	cout << "                                                      ������� ��������: ";
	int FindSalary;
	cin >> FindSalary;
	for (int i = 0; i < number_of_Employees; i++)
	{
		if (arr_of_Employees[i].Salary < FindSalary) // ���� �������� ������ ��������� --> ������� ���� � ���������� 
		{
			Show_result_of_finding(arr_of_Employees, number_of_Employees, i);
		}
	}
}

// ��� �2 (���������� �� ������� | ����� �� | ������� �� | ����������)____________________________________________________________________

void Individual_task_departments_info(Employee* arr_of_Employees, int number_of_Employees)
{
	int number_of_dep = 1;
	Department* arr_of_dep = new Department[number_of_dep]; // ������ 1 ������ ��������� ���������� | ����� | ���������� | ��
	// ����� 1 ���������� � ������� ��� ���� �� ����� �������� 
	for (int i = 0; i < number_of_Employees; i++) // ��������� ����������� 
	{
		for (int j = 0; j <= number_of_dep; j++) // ��������� ������� 
		{
			if (arr_of_Employees[i].Department == arr_of_dep[j].Department_name) // ���� ����� ���������� ������ � ����� �� ��� ������������ ������� 
			{
				arr_of_dep[j].Total_department_salary += arr_of_Employees[i].Salary; // �� ���������� ��������� � ����� �� ������ 
				arr_of_dep[j].Employees_amount++; // ��������� ���������� ����������� 
				break;
			}

			if (j == number_of_dep) // ���� ��� --> ���� ��� ������ ��������� | ���� ���� ������ ������ 
			{
				if (number_of_dep == 0) // ��������� ���������� ����� ��� ��������� ����� ������
				{
					arr_of_dep[j].Department_name = arr_of_Employees[i].Department; // ������� �������� ������ 
					arr_of_dep[j].Employees_amount++; // ��������� ���������� ����������� � ������ 
					arr_of_dep[j].Total_department_salary += arr_of_Employees[i].Salary; // ��������� �������� ���������� � ����� �� ������ 
				}
				else // �������� ����� ������ 
				{
					arr_of_dep = Individual_task_department_memory_reallocation(arr_of_dep, number_of_dep, number_of_dep + 1); // ��������� ������
					arr_of_dep[j].Department_name = arr_of_Employees[i].Department;
					arr_of_dep[j].Employees_amount++;
					arr_of_dep[j].Total_department_salary += arr_of_Employees[i].Salary;
				}
				break;
			}
		}
	}

	for (int k = 1; k < number_of_dep; k++) // ����� ���������� �� ������ 
	{
		cout << "                                                       �����: " << arr_of_dep[k].Department_name << endl;
		cout << "                                                       ����������� � ������: " << arr_of_dep[k].Employees_amount << endl;
		cout << "                                                       ����� ��������: " << arr_of_dep[k].Total_department_salary << endl;
		cout << "                                                       ������� ��: " << arr_of_dep[k].Total_department_salary / arr_of_dep[k].Employees_amount << endl << endl;
	}
	delete[]arr_of_dep; // ������� ���� ����� ������������� 
}

// ��� �2 ������������� ������ ��� �������_______________________________________________________________________________________________

Department* Individual_task_department_memory_reallocation(Department* arr_of_dep, int& number_of_dep, int m)
{

	Department* temp_arr = new Department[m];
	for (int i = 0; i < number_of_dep; i++) // ������� ����������
	{
		temp_arr[i].Department_name = arr_of_dep[i].Department_name;
		temp_arr[i].Employees_amount = arr_of_dep[i].Employees_amount;
		temp_arr[i].Total_department_salary = arr_of_dep[i].Total_department_salary;
	}

	delete[]arr_of_dep; // ������� ������ ������ 
	number_of_dep = m; // ��������� ������  
	arr_of_dep = temp_arr; // ��������� ����������
	return arr_of_dep; // ���������� ����������� ������ 
}



// ������ ����������________________________________________________________________________________________________________________


// ����� ���������� 
Employee* Selection_sorting_menu(Employee* arr_of_Employees, int number_of_Employees)
{
	int sw;
	Set_color(1, 0); // ����� | ���� ������ | ���� ���� 
	cout << "                                        ______________________________________________            " << endl;
	cout << "                                       /                                              \\          " << endl;
	cout << "                                      /          � � � � | � � � � � � � � � �         \\         " << endl;
	cout << "                                     /|________________________________________________|\\        " << endl;
	Set_color(7, 0); // ������-����� 
	cout << "                                     ||                                                ||         " << endl;
	cout << "                                     ||             1. ������������� �� �������        ||         " << endl;
	cout << "                                     ||             2. ������������� �� �������        ||         " << endl;
	cout << "                                     ||             3. ������������� �� ���������      ||         " << endl;
	cout << "                                     ||________________________________________________||         " << endl;
	cout << "                                     ||                                                ||         " << endl;
	cout << "                                     ||             0. ��������� �����                 ||         " << endl;
	cout << "                                     ||________________________________________________||         " << endl;
	cout << "                                               >>";

	Protection(0, 3, sw);
	switch (sw)
	{
	case 1: arr_of_Employees = Sorting_by_Surname(arr_of_Employees, number_of_Employees); break;
	case 2: arr_of_Employees = Sorting_by_department(arr_of_Employees, number_of_Employees); break;
	case 3: arr_of_Employees = Sorting_by_the_salary(arr_of_Employees, number_of_Employees); break;
	case 0:break;
	}
	return arr_of_Employees;
}

// ���������� �1 (�� ��������)__________________________________________________________________________________________________________

Employee* Sorting_by_Surname(Employee* arr_of_Employees, int number_of_Employees)
{
	Employee* temp_arr = new Employee[number_of_Employees]; // �������� ������ 
	for (int i = 0; i < number_of_Employees; i++) // ��������� ���������� 
	{
		temp_arr[i].Name = arr_of_Employees[i].Name;
		temp_arr[i].Surname = arr_of_Employees[i].Surname;
		temp_arr[i].Patronymic = arr_of_Employees[i].Patronymic;
		temp_arr[i].Department = arr_of_Employees[i].Department;
		temp_arr[i].Position = arr_of_Employees[i].Position;
		temp_arr[i].Salary = arr_of_Employees[i].Salary;

	}
	cout << "                                    ________________________________________________________       " << endl;
	cout << "                                   /                                                        \\     " << endl;
	cout << "                                  /            ���������� ����������� �� �������!            \\    " << endl << endl;

	for (int i = 0; i < number_of_Employees - 1; i++)  // ���������� �� � �� � 
	{
		for (int j = 0; j < number_of_Employees - i - 1; j++) // ��������� �� ���� ��� 
		{
			if (temp_arr[j].Surname > temp_arr[j + 1].Surname) // �������� �� ASCII
			{
				swap(temp_arr[j], temp_arr[j + 1]); // ������ �������
			}
		}
	}
	Show_employees(temp_arr, number_of_Employees);

	int temp; // ��������� ���������� 
	Ask_for_saving(); // ���������? 

	Protection(1, 2, temp);
	switch (temp)
	{
	case 1: // ��������� (��������� ������) 
		delete[]arr_of_Employees;
		arr_of_Employees = temp_arr;
		break;
	case 2: // �������� 
		delete[] temp_arr; // ������� ��������������� 
		break;
	}
	return arr_of_Employees;
}

// ���������� �2 (�� �������)__________________________________________________________________________________________________________

Employee* Sorting_by_department(Employee* arr_of_Employees, int number_of_Employees)
{

	Employee* arr_new = new Employee[number_of_Employees];
	for (int i = 0; i < number_of_Employees; i++)
	{
		arr_new[i].Name = arr_of_Employees[i].Name;
		arr_new[i].Surname = arr_of_Employees[i].Surname;
		arr_new[i].Patronymic = arr_of_Employees[i].Patronymic;
		arr_new[i].Department = arr_of_Employees[i].Department;
		arr_new[i].Position = arr_of_Employees[i].Position;
		arr_new[i].Salary = arr_of_Employees[i].Salary;

	}
	cout << "                                    _______________________________________________________       " << endl;
	cout << "                                   /                                                       \\     " << endl;
	cout << "                                  /             ���������� ����������� �� ������!           \\    " << endl << endl;

	for (int i = 0; i < number_of_Employees - 1; i++) // ��� ������������ 1-�� ��������� --> 1 | �� � ������� 0 || �� � �� �
	{
		for (int j = 0; j < number_of_Employees - i - 1; j++)
		{
			if (arr_new[j].Department > arr_new[j + 1].Department) // ASCII 
			{
				swap(arr_new[j], arr_new[j + 1]);
			}
		}
	}
	Show_employees(arr_new, number_of_Employees);

	int temp;
	Ask_for_saving(); // ���������? 

	Protection(1, 2, temp);
	switch (temp)
	{
	case 1:
		delete[]arr_of_Employees; // ���� ����� ���������� ����� �������� --> ������� ������ ������ 
		arr_of_Employees = arr_new; // ��������� ������ ������ ���������� 
		break;
	case 2:
		delete[] arr_new; // ���� ��� --> ������� ��������������� 
		break;
	}
	return arr_of_Employees;
}

// ���������� �3 (�� ��������)_________________________________________________________________________________________________________

Employee* Sorting_by_the_salary(Employee* arr_of_Employees, int number_of_Employees)
{

	Employee* arr_new = new Employee[number_of_Employees];
	for (int i = 0; i < number_of_Employees; i++)
	{
		arr_new[i].Name = arr_of_Employees[i].Name;
		arr_new[i].Surname = arr_of_Employees[i].Surname;
		arr_new[i].Patronymic = arr_of_Employees[i].Patronymic;
		arr_new[i].Department = arr_of_Employees[i].Department;
		arr_new[i].Position = arr_of_Employees[i].Position;
		arr_new[i].Salary = arr_of_Employees[i].Salary;

	}
	cout << "                                    _________________________________________________________    " << endl;
	cout << "                                   /                                                         \\  " << endl;
	cout << "                                  /            ���������� ����������� �� ��������!            \\ " << endl << endl;

	for (int i = 0; i < number_of_Employees - 1; i++) // �� ������� � ������� 
	{
		for (int j = 0; j < number_of_Employees - i - 1; j++)
		{
			if (arr_new[j].Salary > arr_new[j + 1].Salary)
			{
				swap(arr_new[j], arr_new[j + 1]);
			}
		}
	}
	Show_employees(arr_new, number_of_Employees);

	int temp;
	Ask_for_saving(); // ���������? 

	Protection(1, 2, temp);
	switch (temp)
	{
	case 1: // ��������� ����� 
		Save_it(); // ����� ������ ������� ���������
		delete[]arr_of_Employees;
		arr_of_Employees = arr_new;
		break;
	case 2: // �������� ��� ��������� 
		delete[] arr_new;
		Save_it();
		break;
	}
	return arr_of_Employees;
}



// ������ ������_______________________________________________________________________________________________________________ 


// ���� ������ ������ 
void Menu_of_finding_employees(Employee* arr_of_Employees, int number_of_Employees)
{
	Set_color(1, 0); // ����� | ���� ������ | ���� ���� 
	cout << "                                      __________________________________________________            " << endl;
	cout << "                                     /                                                  \\          " << endl;
	cout << "                                    /               � � � � | � � � � � A                \\         " << endl;
	cout << "                                   /|____________________________________________________|\\        " << endl;
	Set_color(7, 0); // ������-����� 
	cout << "                                   ||                                                    ||         " << endl;
	cout << "                                   ||             1. ����� �� �������                    ||         " << endl;
	cout << "                                   ||             2. ����� �� ���������                  ||         " << endl;
	cout << "                                   ||             3. ����� ���������� � ������������ ��  ||         " << endl;
	cout << "                                   ||____________________________________________________||         " << endl;
	cout << "                                   ||                                                    ||         " << endl;
	cout << "                                   ||             0. ��������� �����                     ||         " << endl;
	cout << "                                   ||____________________________________________________||         " << endl;
	cout << "                                               >>";

	int sw;
	Protection(0, 3, sw);

	switch (sw)
	{
	case 1: Find_surname(arr_of_Employees, number_of_Employees); break; // ����� �� �������
	case 2: Find_position(arr_of_Employees, number_of_Employees); break; // ����� �� ��������� 
	case 3: Find_max_salary(arr_of_Employees, number_of_Employees); break; // ����� �� ������������ �������� 
	case 0: break; // ����� 
	}
}

// ����� �1 (�� �������)____________________________________________________________________________________________

void Find_surname(Employee* arr_of_Employees, int number_of_Employees)
{
	string FindSurname; // ��� ����� ������� 
	bool flag = true;
	cout << "                                  ________________________________________________________    " << endl;
	cout << "                                 /                                                        \\  " << endl;
	cout << "                                /              ����� ����������� �� �������!               \\ " << endl;
	cout << "                                               ������� ������� ��� ������: ";
	cin >> FindSurname;
	for (int i = 0; i < number_of_Employees; i++)
	{
		if (FindSurname == arr_of_Employees[i].Surname) // ���� ����� --> ������� 
		{
			Show_result_of_finding(arr_of_Employees, number_of_Employees, i);
			flag = false; // --> ��������� ��������� if
		}
	}
	if (flag)
	{
		Account_not_found(); // ������ �������� ��� � �������
	}

}

// ����� �2 (�� ���������)___________________________________________________________________________________________

void Find_position(Employee* arr_of_Employees, int number_of_Employees)
{
	string SearchPositio; // ��� ����� ��������� 
	cout << "                                  _________________________________________________________     " << endl;
	cout << "                                 /                                                         \\   " << endl;
	cout << "                                /              ����� ����������� �� ���������!              \\  " << endl;
	cout << "                                               ������� ��������� ��� ������: ";
	cin >> SearchPositio;
	bool flag = true;
	for (int i = 0; i < number_of_Employees; i++)
	{
		if (arr_of_Employees[i].Position == SearchPositio)
		{
			Show_result_of_finding(arr_of_Employees, number_of_Employees, i);
			flag = false; // --> ��������� ��������� if
		}
	}
	if (flag)
	{
		Account_not_found(); // ������ �������� ��� � �������
	}
}

// ����� �3 (�� ������������ ��)__________________________________________________________________________________________

void Find_max_salary(Employee* arr_of_Employees, int number_of_Employees)
{
	cout << "                                    ________________________________________________________      " << endl;
	cout << "                                   /                                                        \\    " << endl;
	cout << "                                  /            ����� ����������� � ���������� ��!            \\   " << endl;
	int MaxKol = 0;
	for (int i = 0; i < number_of_Employees; i++)
	{
		if (MaxKol < arr_of_Employees[i].Salary) // ���� ����� �������� ������ 
		{
			MaxKol = arr_of_Employees[i].Salary; // ��������� �������� MaxKol
		}
	}
	for (int i = 0; i < number_of_Employees; i++) // ����� ��������� ����� ��� ��
	{
		if (arr_of_Employees[i].Salary == MaxKol) // ������� �� ���������� 
		{
			Show_result_of_finding(arr_of_Employees, number_of_Employees, i);
		}
	}

}

// ����� ����������� ������___________________________________________________________________________________________________________

void Show_result_of_finding(Employee* arr_of_Employees, int number_of_Employees, int i)
{
	cout << endl;
	cout << "                                               �.�.�. " << arr_of_Employees[i].Surname << " " << arr_of_Employees[i].Name << " " << arr_of_Employees[i].Patronymic << endl;
	cout << "                                               �����: " << arr_of_Employees[i].Department << endl;
	cout << "                                               ���������: " << arr_of_Employees[i].Position << endl;
	cout << "                                               ��������: " << arr_of_Employees[i].Salary << endl;
	cout << endl;
}
