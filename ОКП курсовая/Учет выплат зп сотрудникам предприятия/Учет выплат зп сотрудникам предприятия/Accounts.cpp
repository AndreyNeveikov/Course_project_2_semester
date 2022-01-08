#include "Accounts.h" 
#include "Protection.h" 
#include "Signal.h"

// ������� �� main ��� ������� ���������___________________________________________________________________________________________________ 
void Start_program()
{
	SetConsoleCP(1251); // ���� �� �������/��������� ����
	SetConsoleOutputCP(1251); // ����� �� �������

	int number_of_accounts = 0;
	�heck_accounts_number(number_of_accounts); // ������������ ������� ��������� � ����� � ��������� ����������
	Accounts* array_of_accounts = new Accounts[number_of_accounts]; // ��������� ������ ��� ������� �������� ���������
	Read_file_accounts(array_of_accounts, number_of_accounts); // ������� ������ �� ����� | ������ � �������
	array_of_accounts = Authorization_menu(array_of_accounts, number_of_accounts); // 1 - ���� | 2 - ����������� 

	Write_file_accounts(array_of_accounts, number_of_accounts); // ���������� ����� ������ � ���� 
	delete[] array_of_accounts; // ������� ���������� | ��� �������������� ������ ������
}

// ����������� ���������� �����������____________________________________________________________________________________________________________
void �heck_accounts_number(int& number_of_accounts)
{
	string temp; // ��������� ���������� ��� ���������� ������
	ifstream fin(FILE_INFO_ACCOUNTS, ios::in); // ������ ������ �� ����� 
	if (!fin.is_open()) // ���� ������ ������ --> 1 ������� 
	{
		number_of_accounts = 1;
	}
	else
	{
		while (!fin.eof()) // ���������� ���� ����� ����� | ������������ ������� ��������� 
		{
			fin >> temp >> temp >> temp >> temp;
			number_of_accounts++;
		}
	}
	fin.close(); // ��������� ���� 
}

// ������ ��������� �� �����____________________________________________________________________________________________________________________ 
void Read_file_accounts(Accounts* arr_of_accounts, int number_of_accounts)
{
	ifstream fin(FILE_INFO_ACCOUNTS, ios::in); // ��� ������ ��������� 
	if (!fin.is_open()) // ���� ������ ������ --> ������� ������� ������ 
	{
		Set_color(2, 0);
		cout << "                                ________________________________________________________________  " << endl;
		cout << "                                |                                                              |  " << endl;
		cout << "                                |         ������� ������ >> �����: admin ������: admin         |  " << endl;
		cout << "                                |______________________________________________________________|  " << endl;
		Set_color(7, 0);
		arr_of_accounts[0].login = "admin";
		arr_of_accounts[0].password = "admin";
		arr_of_accounts[0].status = 1;
		arr_of_accounts[0].activation = 1;
	}

	else
	{
		int number_of_accounts = 0; // �������� ���������� 
		while (!fin.eof())
		{
			fin >> arr_of_accounts[number_of_accounts].login >> arr_of_accounts[number_of_accounts].password >>
				arr_of_accounts[number_of_accounts].status >> arr_of_accounts[number_of_accounts].activation;
			number_of_accounts++;
		}
	}
	fin.close();
}

// ������ ��������� � ����_________________________________________________________________________________________________________________________________
void Write_file_accounts(Accounts* arr_of_accounts, int number_of_accounts)
{
	ofstream fout(FILE_INFO_ACCOUNTS, ios::out); // ���������� � ���� 
	for (int i = 0; i < number_of_accounts; i++)
	{
		fout << arr_of_accounts[i].login << " " << arr_of_accounts[i].password << " " << arr_of_accounts[i].status << " " << arr_of_accounts[i].activation;
		if (i < number_of_accounts - 1)
			fout << endl;
	}
	fout.close();
}

// �����(��������) ���������________________________________________________________________________________________________________________________________ 
void Show_accounts(Accounts* arr_of_accounts, int number_of_accounts)
{
	cout << "                                    ________________________________________________________               " << endl;
	cout << "                                   /                                                        \\             " << endl;
	cout << "                         _________/             � � � � � � | � � � � � � � � �              \\_________   " << endl << endl;
	for (int i = 0; i < number_of_accounts; i++)
	{
		cout << "                                                        " <<
			arr_of_accounts[i].login << " " << arr_of_accounts[i].password << " " <<
			arr_of_accounts[i].status << " " << arr_of_accounts[i].activation << endl;;
	}
}

// ���������� ���������_______________________________________________________________________________________________________________________________________
void Add_accounts(Accounts* arr_of_accounts, int& number_of_accounts)
{
	system("cls");
	cout << "                                         ________________________________________________" << endl;
	Set_color(2, 0);
	cout << "                                         |                                              |" << endl;
	cout << "                                         |           //  �����������  \\\\                |" << endl;
	cout << "                                         |                                              |" << endl;
	cout << "                                         |   ������ ������ ��������� ����� 2 ��������   |" << endl;
	Set_color(7, 0);
	cout << "                                         |______________________________________________|" << endl << endl;
	cout << "                                                       ������� �����: ";
	string TempLogin, TempPassword, TempPasswordRepeat; // ��������� �����/������/��������� ������
	bool flagLogin = true, flagCheckPassword = true, flagPassword = true; // ����� ��� ������������� ������ 
	cin >> TempLogin; // ������ �������� �����
	int amount = 3;

	while (flagLogin) // ���� true | ��������� ���� �� � ��������� ����� ����� 
	{
		for (int i = 0; i < number_of_accounts; i++)
		{
			if (TempLogin == arr_of_accounts[i].login) // ���� ����� ����� �� 
			{
				system("cls");
				cout << "                                         ____________________________________________" << endl;
				Set_color(12, 0);
				cout << "                                              ������� � ������� " << TempLogin << " ��� ����������" << endl;
				Set_color(7, 0);
				cout << "                                         ____________________________________________" << endl << endl;
				cout << "                                                       ������� �����: ";
				cin >> TempLogin; // ������ ������ ������ 
			}
		}
		flagLogin = false; // ���� ������ ���� --> ������ ���� ��� ������ �� �����
	}
	arr_of_accounts[number_of_accounts - 1].login = TempLogin; // ���������� ����� | -1 �.�. �������������� � 0 

	// ������
	while (flagPassword)
	{
		cout << "                                                       ������� ������: ";
		TempPassword = Inputing_password(); // ���������� ������ 
		while (flagCheckPassword) // ��������� ����� �� ����� ������
		{
			if (TempPassword.size() < 3) // ���� ������ < 3 �������� --> ������� ������
			{
				cout << endl << endl;
				cout << "                                              ������ ������ ��������� ����� 2 ��������           " << endl;
				cout << "                                                       ��������� ����: ";
				TempPassword = Inputing_password(); // ���� < 3 
			}
			else
			{
				flagCheckPassword = false; // ������ ��� --> ������� �� ����� 
			}
		}
		cout << endl;
		cout << "                                                       ������� ������ ��������: ";
		TempPasswordRepeat = Inputing_password(); // ��� ���������� ����� ������  
		if (TempPassword == TempPasswordRepeat) // ���� ������� 
		{
			arr_of_accounts[number_of_accounts - 1].password = TempPassword; // ���������� ������ 
			Save_it();
			flagPassword = false; // ������� �� ����� ������ ������ 
		}
		else
		{
			Password_incorrect(TempLogin, flagPassword, amount); // � Signal | ������� ������ ���� ��������� ��� ����� �� ��� ������
		}
	}
	arr_of_accounts[number_of_accounts - 1].status = 0; // ���� - ������������  
	arr_of_accounts[number_of_accounts - 1].activation = 0; // ������� ������������� 
	cout << endl;
}

// ������������� ���������_____________________________________________________________________________________________________________

void Change_in_accounts(Accounts* arr_of_accounts, int& number_of_accounts) // ������������� � ��������� | ��� ������ 
{
	system("cls");
	Show_accounts(arr_of_accounts, number_of_accounts); // ������� ��� �������� 
	string TempLogin; // ������ ��� �������� ������
	bool flag = true;
	int i = 0;
	cout << "                               _______________________________________________________________________" << endl << endl;
	cout << "                                        ������� ����� ��������, ������� ������ ��������: ";
	cin >> TempLogin;

	while (flag && i < number_of_accounts) // ���� ��� ������ ������� �������� 
	{
		if (TempLogin == arr_of_accounts[i].login) // ��� ������ ����� ���������� ����� ������ flagPassword �� false
		{
			flag = false;
		}
		else
		{
			i++; // �� ���� ��� �� ������ ������ ������� 
		}
	}

	if (flag) // ���� ���� �������� 
	{
		Account_not_found(); // ������� ��� ������ �������� ��� � �������
	}
	else // ���� ������� ������ --> ����������, ��� ����� ��������
	{

		int sw;
		Set_color(1, 0); // ����� | ���� ������ | ���� ���� 
		cout << "                                            _______________________________________           " << endl;
		cout << "                                           /                                       \\          " << endl;
		cout << "                                          /  � � � � | � � � � � � � � � � � � � �  \\         " << endl;
		cout << "                                         /|_________________________________________|\\        " << endl;
		Set_color(7, 0); // ������-����� 
		cout << "                                         ||            1. �������� �����            ||          " << endl;
		cout << "                                         ||            2. �������� ������           ||          " << endl;
		cout << "                                         ||            3. �������� ����             ||          " << endl;
		cout << "                                         ||            4. �������� ���������        ||          " << endl;
		cout << "                                         ||_________________________________________||          " << endl;
		cout << "                                         ||                                         ||          " << endl;
		cout << "                                         ||             0. ��������� �����          ||          " << endl;
		cout << "                                         ||_________________________________________||          " << endl;
		cout << "                                                   >>";

		Protection(0, 4, sw);
		switch (sw)
		{
		case 1: // ��������� ������ 
			cout << "                                         ____________________________________________" << endl << endl;
			cout << "                                                      ������� ����� �����: ";
			cin >> arr_of_accounts[i].login;
			Save_it(); // ����� ������ ������� ���������
			break;

		case 2: // ��������� ������ 
			cout << "                                         ____________________________________________" << endl << endl;
			cout << "                                                      ������� ����� ������: ";
			cin >> arr_of_accounts[i].password;
			Save_it(); // ����� ������ ������� ���������
			break;

		case 3: // ��������� ������� 
			if (arr_of_accounts[i].status) // true (1) �.�. �����
			{
				arr_of_accounts[i].status = 0; // �������� �� ������������
				Set_color(2, 0);
				cout << "                                ________________________________________________________________" << endl;
				cout << "                                |                                                              |" << endl;
				cout << "                                |             ������ ������� ������� �� ������������!          |" << endl;
				cout << "                                |______________________________________________________________|" << endl;
				Set_color(7, 0);
				Sleep(1000);
				system("cls");
				break;
			}
			if (!arr_of_accounts[i].status) // false (0) �.�. ������������ 
			{
				arr_of_accounts[i].status = 1; // �������� �� ������
				Set_color(2, 0);
				cout << "                                ________________________________________________________________" << endl;
				cout << "                                |                                                              |" << endl;
				cout << "                                |             ������ ������� ������� �� ��������������!        |" << endl;
				cout << "                                |______________________________________________________________|" << endl;
				Set_color(7, 0);
				Sleep(1000);
				system("cls");
				break;
			}
		case 4: // ��������� ��������� 
			if (arr_of_accounts[i].activation) // ���� ������� ����������� 
			{
				arr_of_accounts[i].activation = 0; // ������������ 
				Set_color(12, 0); // ������-�������
				cout << "                                ________________________________________________________________" << endl;
				cout << "                                |                                                              |" << endl;
				cout << "                                |                   ������� ������� �������������!             |" << endl;
				cout << "                                |______________________________________________________________|" << endl;
				Set_color(7, 0);
				Sleep(1000);
				system("cls");
				break;
			}
			if (!arr_of_accounts[i].activation) // ���� ������� �� �����������
			{
				arr_of_accounts[i].activation = 1; // ���������� 
				Set_color(2, 0); //�������
				cout << "                                ________________________________________________________________" << endl;
				cout << "                                |                                                              |" << endl;
				cout << "                                |                    ������� ������� �����������!              |" << endl;
				cout << "                                |______________________________________________________________|" << endl;
				Set_color(7, 0);
				Sleep(1000);
				system("cls");
				break;
			}
		case 0: break;
		}
	}
}

// ����� �������� � ���� �����������________________________________________________________________________________________________________
Accounts* Authorization_menu(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int sw;
	bool flag = true;
	while (flag)
	{

		Set_color(1, 0); // ����� | ���� ������ | ���� ����
		cout << "                                           ________________________________________            " << endl;
		cout << "                                          /                                        \\          " << endl;
		cout << "                                         /          � � � � � � �  � � � �          \\         " << endl;
		cout << "                                        /|__________________________________________|\\        " << endl;
		Set_color(7, 0); // ������-����� 
		cout << "                                        ||                                          ||         " << endl;
		cout << "                                        ||             1. ���� � �������            ||         " << endl;
		cout << "                                        ||             2. �����������               ||         " << endl;
		cout << "                                        ||__________________________________________||         " << endl;
		cout << "                                        ||                                          ||         " << endl;
		cout << "                                        ||             0. ��������� �����           ||         " << endl;
		cout << "                                        ||__________________________________________||         " << endl;
		cout << "                                                  >>";
		Protection(0, 2, sw);
		switch (sw)
		{
		case 1: // ���� � ������� 
			Check_login_and_password(arr_of_accounts, number_of_accounts); // ��������� ������ ��� ����� 
			break;

		case 2: // ����������� �������� 
			arr_of_accounts = Memory_reallocation_for_accounts(arr_of_accounts, number_of_accounts, number_of_accounts + 1); // ������������� ������
			Add_accounts(arr_of_accounts, number_of_accounts); // ������ ����������
			break;

		case 0:
			flag = false;
			break;
		}
	}
	return arr_of_accounts;
}

// �������� ������ � ������_____________________________________________________________________________________________________________________ 
void Check_login_and_password(Accounts* arr_of_accounts, int& number_of_accounts)
{
	bool findLogin = true, errorLogin = true, flagPassword = true, flagGlobal = true;
	int login, amount = 3;
	string TempLogin, TempPassword;

	while (findLogin) // ���� ��� ������ ������ 
	{
		cout << "                                         ____________________________________________" << endl << endl;
		cout << "                                                       ������� �����: ";

		cin >> TempLogin; // ������ ������ ����� 
		for (int i = 0; i < number_of_accounts; i++)
		{
			if (TempLogin == arr_of_accounts[i].login) // ���� ����� ����� ���������� 
			{
				login = i; // ���������� ������ 
				findLogin = false; // ������� �� ����� �.�. ����� �����
				errorLogin = false; // ��������� ��������� ������
			}
		}
		if (errorLogin) // ��������� ���� ����� �� ����� ������
		{
			system("cls");
			amount--; // ���� ����� �������� ����� ��������� ����������
			cout << "                                         ____________________________________________" << endl << endl;
			Set_color(12, 0);
			cout << "                                              ������� � ������� " << TempLogin << " �� ���������.      " << endl;
			cout << "                                                      ������� ��������: " << amount << "               " << endl;
			Set_color(7, 0);

			if (amount == 0) // ���� �������� 0 --> ������� �� ����� 
			{
				Set_color(12, 0);
				cout << endl << "                                      �� �������� �������������� ����������. ���������� �����.      " << endl;
				Sleep(1500);
				system("cls");
				findLogin = false;
				flagPassword = false; // ��������� ��������� ����
			}
		}
	}
	amount = 3; // ��������� amout 
	while (flagPassword)
	{
		cout << "                                                       ������� ������: ";
		TempPassword = Inputing_password(); // ��� ����� ������ 
		if (TempPassword == arr_of_accounts[login].password) // ���� ������ ������� � �������� 
		{
			if (arr_of_accounts[login].activation) // ���� ��������� 1(true) --> ��������� ����
			{
				Check_user_status(arr_of_accounts, number_of_accounts, arr_of_accounts[login].status); // ��������� ��� �����
			}
			else // ���� 0 (false) --> ������ ������� ������������� 
			{

				Set_color(12, 0);
				cout << endl << "                               ������! ������ ������� � � � � � � � � � � � � �. �������� ���������" << endl << endl;
				Sleep(1500);
				system("cls");
			}
			flagPassword = false;
		}
		else // ���� ������ �� ������ 
		{
			Password_incorrect(TempLogin, flagPassword, amount); // � Signal | ������� ������ ���� ��������� ��� ����� �� ��� ������
		}
	}
}

// ������������� ������____________________________________________________________________________________________________________________

Accounts* Memory_reallocation_for_accounts(Accounts* arr_of_accounts, int& number_of_accounts, int m) // m ��������� �������� �� 1 ������ 
{
	Accounts* temp_arr = new Accounts[m]; // �������� ������

	for (int i = 0; i < number_of_accounts; i++) // ��������� ������ ������ 
	{
		temp_arr[i].login = arr_of_accounts[i].login;
		temp_arr[i].password = arr_of_accounts[i].password;
		temp_arr[i].status = arr_of_accounts[i].status;
		temp_arr[i].activation = arr_of_accounts[i].activation;
	}

	delete[]arr_of_accounts; // ������� ������ ������ ��������
	number_of_accounts = m; // ��������� ���������� � ����������
	arr_of_accounts = temp_arr; // ��������� ���������� 

	return arr_of_accounts; // ���������� ����������� ������
}

// �������� �������. ����� ������ ����: ����� | ������������_______________________________________________________________________________ 
void Check_user_status(Accounts* arr_of_accounts, int& number_of_accounts, int role)
{
	if (role == 1) // ���� ����� 
	{
		system("cls");
		Set_color(2, 0);
		cout << "                                       //// �� �������������� ��� ������������� \\\\\\\\\\           " << endl << endl;
		Set_color(7, 0);
		Admin_menu(arr_of_accounts, number_of_accounts); // �������� ���� ������ 
	}

	else
		if (role == 0) // ���� ������������
		{
			system("cls");
			Set_color(2, 0);
			cout << "                                         //// �� �������������� ��� ������������ \\\\\\\\\\           " << endl;
			Set_color(7, 0);
			User_menu(); // ������� � ���������� ������������ 
		}
}

// ���� ������ ��� ������ ��������_____________________________________________________________________________________________ 
void Admin_menu(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int sw;
	bool flag = true;
	while (flag)
	{
		Set_color(1, 0); // ����� | ���� ������ | ���� ����
		cout << "                                           _______________________________________            " << endl;
		cout << "                                          /                                       \\          " << endl;
		cout << "                                         /   � � � � | � � � � � � � � � � � � �   \\         " << endl;
		cout << "                                        /|_________________________________________|\\        " << endl;
		Set_color(7, 0); // ������-����� 
		cout << "                                        ||                                         ||         " << endl;
		cout << "                                        ||        1. ������ � ����������           ||         " << endl;
		cout << "                                        ||        2. ������ � ������������         ||         " << endl;
		cout << "                                        ||_________________________________________||         " << endl;
		cout << "                                        ||                                         ||         " << endl;
		cout << "                                        ||        0. ��������� �����               ||         " << endl;
		cout << "                                        ||_________________________________________||         " << endl;
		cout << "                                                  >>";

		Protection(0, 2, sw);
		switch (sw)
		{
		case 1: // ������ � ����������
			system("cls");
			Admin_accounts_menu(arr_of_accounts, number_of_accounts); // ���� ��� ���������� ���������� 
			break;

		case 2: // ������ � ������������
			system("cls");
			User_menu();
			break;

		case 0:
			system("cls");
			flag = false; // ��� ������ �� �����
			break;
		}
	}

}

// ���� ������ ��� ������ � ����������_________________________________________________________________________________________________
void Admin_accounts_menu(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int sw;
	bool flag = true;
	while (flag)
	{
		Set_color(1, 0); // ����� | ���� ������ | ���� ����
		cout << "                                           _______________________________________            " << endl;
		cout << "                                          /                                       \\          " << endl;
		cout << "                                         /             � � � � � � � �             \\         " << endl;
		cout << "                                        /|_________________________________________|\\        " << endl;
		Set_color(7, 0); // ������-����� 
		cout << "                                        ||                                         ||         " << endl;
		cout << "                                        ||         1. ���������� ��������          ||        " << endl;
		cout << "                                        ||         2. ������������� ��������       ||        " << endl;
		cout << "                                        ||         3. ������� �������              ||        " << endl;
		cout << "                                        ||_________________________________________||         " << endl;
		cout << "                                        ||                                         ||         " << endl;
		cout << "                                        ||             0. ��������� �����          ||         " << endl;
		cout << "                                        ||_________________________________________||         " << endl;
		cout << "                                                  >>";

		Protection(0, 3, sw);
		switch (sw)
		{
		case 1: // �������� ���������
			system("cls");
			Show_accounts(arr_of_accounts, number_of_accounts);
			break;

		case 2: // ������������� ���������
			Change_in_accounts(arr_of_accounts, number_of_accounts);
			break;

		case 3: // �������� ��������
			system("cls");
			Show_accounts(arr_of_accounts, number_of_accounts);
			Del_accounts(arr_of_accounts, number_of_accounts);
			break;

		case 0: // ��� ������ �� while
			flag = false;
			system("cls");
			break;
		}
	}

}

// ��� �������� ��������_____________________________________________________________________________________________________________________ 
void Del_accounts(Accounts* arr_of_accounts, int& number_of_accounts)
{
	string delLogin; // ��� ������ ��������, ������� ����� ������� 
	cout << "                               ____________________________________________________________________" << endl << endl;
	cout << "                                        ������� ����� ��������, ������� ������ �������: ";

	cin >> delLogin;
	int i = 0, del = 0;
	bool flag = true;

	while (flag && i <= number_of_accounts)
	{
		if (arr_of_accounts[i].login == delLogin) // ����� �������� 
		{
			flag = false; // ���� ����� --> ������� �� ����� 
		}
		else
		{
			i++;
		}
	}

	if (flag) // ���� �������� ��� 
	{
		Account_not_found();
	}
	else // ���� ������� ���� 
	{
		if (arr_of_accounts[i].status == 1) // ������ ����� ������ ���� ������� ������� ������ 
		{
			Set_color(12, 0);
			cout << endl;
			cout << "                                                     _______________" << endl;
			cout << "                                                    /               \\                           " << endl;
			cout << "                                                   /   � � � � � �   \\                          " << endl;
			cout << "                               ___________________/___________________\\_________________________" << endl;
			cout << "                               |                                                               | " << endl;
			cout << "                               | � ��� ������������ ���� ��� �������� �������� ��������������! | " << endl;
			cout << "                               |           ������ ��� ������� �������� ���� ��������!          | " << endl;
			cout << "                               |_______________________________________________________________| " << endl;
			Set_color(7, 0);
			Sleep(2000);
			system("cls");
		}
		else
		{
			cout << "�� ������������� ������ ������� �������: " << arr_of_accounts[i].login << endl;
			cout << "P.S. ��������� ������ �� �������� ��������������." << endl;
			cout << " 1. ��" << "\n 2. ���" << "\n --> ";
			Protection(1, 2, del);
			if (del == 1)
			{
				for (int j = i; j < number_of_accounts - 1; j++) // i -> ����� �������� | �������� � ����� ���������� ��������
				{
					arr_of_accounts[j] = arr_of_accounts[j + 1];
				}
				number_of_accounts--; // ��������� ���������� ��������� 
				Save_it(); // ������ ������� ���������
			}
			else
			{
				cout << "�������� ��������" << endl;
			}
		}
	}
}
