#include "Accounts.h" 
#include "Protection.h" 
#include "Signal.h"

// Функция из main для запуска программы___________________________________________________________________________________________________ 
void Start_program()
{
	SetConsoleCP(1251); // Ввод из консоли/редактора кода
	SetConsoleOutputCP(1251); // Вывод на консоль

	int number_of_accounts = 0;
	Сheck_accounts_number(number_of_accounts); // Подсчитывает сколько аккаунтов в файле и обновляем переменную
	Accounts* array_of_accounts = new Accounts[number_of_accounts]; // Выделение память для массива структур аккаунтов
	Read_file_accounts(array_of_accounts, number_of_accounts); // Функция чтения из файла | Запись в массивы
	array_of_accounts = Authorization_menu(array_of_accounts, number_of_accounts); // 1 - вход | 2 - регистрация 

	Write_file_accounts(array_of_accounts, number_of_accounts); // Записывает новые данные в файл 
	delete[] array_of_accounts; // Очистка информации | для предотвращения утечки памяти
}

// Определение количества сотрудников____________________________________________________________________________________________________________
void Сheck_accounts_number(int& number_of_accounts)
{
	string temp; // Временная переменная для считывания данных
	ifstream fin(FILE_INFO_ACCOUNTS, ios::in); // Чтение данных из файла 
	if (!fin.is_open()) // Если первый запуск --> 1 аккаунт 
	{
		number_of_accounts = 1;
	}
	else
	{
		while (!fin.eof()) // Возвращает флаг конца файла | Подсчитываем сколько аккаунтов 
		{
			fin >> temp >> temp >> temp >> temp;
			number_of_accounts++;
		}
	}
	fin.close(); // Закрываем файл 
}

// Чтение аккаунтов из файла____________________________________________________________________________________________________________________ 
void Read_file_accounts(Accounts* arr_of_accounts, int number_of_accounts)
{
	ifstream fin(FILE_INFO_ACCOUNTS, ios::in); // Для чтения аккаунтов 
	if (!fin.is_open()) // Если первый запуск --> создаем аккаунт админа 
	{
		Set_color(2, 0);
		cout << "                                ________________________________________________________________  " << endl;
		cout << "                                |                                                              |  " << endl;
		cout << "                                |         Аккаунт админа >> Логин: admin Пароль: admin         |  " << endl;
		cout << "                                |______________________________________________________________|  " << endl;
		Set_color(7, 0);
		arr_of_accounts[0].login = "admin";
		arr_of_accounts[0].password = "admin";
		arr_of_accounts[0].status = 1;
		arr_of_accounts[0].activation = 1;
	}

	else
	{
		int number_of_accounts = 0; // Обнуляем переменную 
		while (!fin.eof())
		{
			fin >> arr_of_accounts[number_of_accounts].login >> arr_of_accounts[number_of_accounts].password >>
				arr_of_accounts[number_of_accounts].status >> arr_of_accounts[number_of_accounts].activation;
			number_of_accounts++;
		}
	}
	fin.close();
}

// Запись аккаунтов в файл_________________________________________________________________________________________________________________________________
void Write_file_accounts(Accounts* arr_of_accounts, int number_of_accounts)
{
	ofstream fout(FILE_INFO_ACCOUNTS, ios::out); // Сохранение в файл 
	for (int i = 0; i < number_of_accounts; i++)
	{
		fout << arr_of_accounts[i].login << " " << arr_of_accounts[i].password << " " << arr_of_accounts[i].status << " " << arr_of_accounts[i].activation;
		if (i < number_of_accounts - 1)
			fout << endl;
	}
	fout.close();
}

// Вывод(просмотр) аккаунтов________________________________________________________________________________________________________________________________ 
void Show_accounts(Accounts* arr_of_accounts, int number_of_accounts)
{
	cout << "                                    ________________________________________________________               " << endl;
	cout << "                                   /                                                        \\             " << endl;
	cout << "                         _________/             С П И С О К | А К К А У Н Т О В              \\_________   " << endl << endl;
	for (int i = 0; i < number_of_accounts; i++)
	{
		cout << "                                                        " <<
			arr_of_accounts[i].login << " " << arr_of_accounts[i].password << " " <<
			arr_of_accounts[i].status << " " << arr_of_accounts[i].activation << endl;;
	}
}

// Добалвение аккаунтов_______________________________________________________________________________________________________________________________________
void Add_accounts(Accounts* arr_of_accounts, int& number_of_accounts)
{
	system("cls");
	cout << "                                         ________________________________________________" << endl;
	Set_color(2, 0);
	cout << "                                         |                                              |" << endl;
	cout << "                                         |           //  Регистрация  \\\\                |" << endl;
	cout << "                                         |                                              |" << endl;
	cout << "                                         |   Пароль должен содержать более 2 символов   |" << endl;
	Set_color(7, 0);
	cout << "                                         |______________________________________________|" << endl << endl;
	cout << "                                                       Введите логин: ";
	string TempLogin, TempPassword, TempPasswordRepeat; // Временный логин/пароль/повторный пароль
	bool flagLogin = true, flagCheckPassword = true, flagPassword = true; // Флаги для регулирования циклов 
	cin >> TempLogin; // Вводим желаемый логин
	int amount = 3;

	while (flagLogin) // пока true | Проверяем есть ли в программе такой логин 
	{
		for (int i = 0; i < number_of_accounts; i++)
		{
			if (TempLogin == arr_of_accounts[i].login) // Если нашли такой же 
			{
				system("cls");
				cout << "                                         ____________________________________________" << endl;
				Set_color(12, 0);
				cout << "                                              Аккаунт с логином " << TempLogin << " уже существует" << endl;
				Set_color(7, 0);
				cout << "                                         ____________________________________________" << endl << endl;
				cout << "                                                       Введите логин: ";
				cin >> TempLogin; // Просим ввести заново 
			}
		}
		flagLogin = false; // Если ошибок нету --> меняем флаг для выхода из цикла
	}
	arr_of_accounts[number_of_accounts - 1].login = TempLogin; // Записываем логин | -1 т.к. индексирование с 0 

	// Пароль
	while (flagPassword)
	{
		cout << "                                                       Введите пароль: ";
		TempPassword = Inputing_password(); // Записываем пароль 
		while (flagCheckPassword) // Проверяем можно ли такой пароль
		{
			if (TempPassword.size() < 3) // Если пароль < 3 символов --> выводим ошибку
			{
				cout << endl << endl;
				cout << "                                              Пароль должен содержать более 2 символов           " << endl;
				cout << "                                                       Повторите ввод: ";
				TempPassword = Inputing_password(); // Если < 3 
			}
			else
			{
				flagCheckPassword = false; // Ошибок нет --> выходим из цикла 
			}
		}
		cout << endl;
		cout << "                                                       Введите пароль повторно: ";
		TempPasswordRepeat = Inputing_password(); // Для повторного ввода пароля  
		if (TempPassword == TempPasswordRepeat) // Если совпали 
		{
			arr_of_accounts[number_of_accounts - 1].password = TempPassword; // Записываем пароль 
			Save_it();
			flagPassword = false; // Выходим из цикла записи пароля 
		}
		else
		{
			Password_incorrect(TempLogin, flagPassword, amount); // В Signal | Выводит ошибку если несколько раз ввели не тот пароль
		}
	}
	arr_of_accounts[number_of_accounts - 1].status = 0; // Роль - пользователь  
	arr_of_accounts[number_of_accounts - 1].activation = 0; // Аккаунт деактивирован 
	cout << endl;
}

// Корректировки аккаунтов_____________________________________________________________________________________________________________

void Change_in_accounts(Accounts* arr_of_accounts, int& number_of_accounts) // Корректировки в аккаунтах | Для админа 
{
	system("cls");
	Show_accounts(arr_of_accounts, number_of_accounts); // Выводим все аккаунты 
	string TempLogin; // Строка для внесения логина
	bool flag = true;
	int i = 0;
	cout << "                               _______________________________________________________________________" << endl << endl;
	cout << "                                        Введите логин аккаунта, который хотите изменить: ";
	cin >> TempLogin;

	while (flag && i < number_of_accounts) // Цикл для поиска нужного аккаунта 
	{
		if (TempLogin == arr_of_accounts[i].login) // Как только нашли подходящий логин меняем flagPassword на false
		{
			flag = false;
		}
		else
		{
			i++; // До того как не найдем нужный аккаунт 
		}
	}

	if (flag) // Если нету аккаунта 
	{
		Account_not_found(); // Выводит что такого аккаунта нет в системе
	}
	else // Если аккаунт найден --> спрашиваем, что нужно заменить
	{

		int sw;
		Set_color(1, 0); // Синий | Цвет текста | Цвет фона 
		cout << "                                            _______________________________________           " << endl;
		cout << "                                           /                                       \\          " << endl;
		cout << "                                          /  М Е Н Ю | Р Е Д А К Т И Р О В А Н И Е  \\         " << endl;
		cout << "                                         /|_________________________________________|\\        " << endl;
		Set_color(7, 0); // Светло-серый 
		cout << "                                         ||            1. Изменить логин            ||          " << endl;
		cout << "                                         ||            2. Изменить пароль           ||          " << endl;
		cout << "                                         ||            3. Изменить роль             ||          " << endl;
		cout << "                                         ||            4. Изменить состояние        ||          " << endl;
		cout << "                                         ||_________________________________________||          " << endl;
		cout << "                                         ||                                         ||          " << endl;
		cout << "                                         ||             0. Вернуться назад          ||          " << endl;
		cout << "                                         ||_________________________________________||          " << endl;
		cout << "                                                   >>";

		Protection(0, 4, sw);
		switch (sw)
		{
		case 1: // Изменение логина 
			cout << "                                         ____________________________________________" << endl << endl;
			cout << "                                                      Введите новый логин: ";
			cin >> arr_of_accounts[i].login;
			Save_it(); // Новые данные успешно сохранены
			break;

		case 2: // Изменение пароля 
			cout << "                                         ____________________________________________" << endl << endl;
			cout << "                                                      Введите новый пароль: ";
			cin >> arr_of_accounts[i].password;
			Save_it(); // Новые данные успешно сохранены
			break;

		case 3: // Изменение статуса 
			if (arr_of_accounts[i].status) // true (1) т.е. админ
			{
				arr_of_accounts[i].status = 0; // Изменяем на пользователя
				Set_color(2, 0);
				cout << "                                ________________________________________________________________" << endl;
				cout << "                                |                                                              |" << endl;
				cout << "                                |             Статус успешно изменен на пользователя!          |" << endl;
				cout << "                                |______________________________________________________________|" << endl;
				Set_color(7, 0);
				Sleep(1000);
				system("cls");
				break;
			}
			if (!arr_of_accounts[i].status) // false (0) т.е. пользователь 
			{
				arr_of_accounts[i].status = 1; // Изменяем на админа
				Set_color(2, 0);
				cout << "                                ________________________________________________________________" << endl;
				cout << "                                |                                                              |" << endl;
				cout << "                                |             Статус успешно изменен на администратора!        |" << endl;
				cout << "                                |______________________________________________________________|" << endl;
				Set_color(7, 0);
				Sleep(1000);
				system("cls");
				break;
			}
		case 4: // Изменение состояния 
			if (arr_of_accounts[i].activation) // Если аккаунт активирован 
			{
				arr_of_accounts[i].activation = 0; // Деактивируем 
				Set_color(12, 0); // Светло-зеленый
				cout << "                                ________________________________________________________________" << endl;
				cout << "                                |                                                              |" << endl;
				cout << "                                |                   Аккаунт успешно деактивирован!             |" << endl;
				cout << "                                |______________________________________________________________|" << endl;
				Set_color(7, 0);
				Sleep(1000);
				system("cls");
				break;
			}
			if (!arr_of_accounts[i].activation) // Если аккаунт НЕ активирован
			{
				arr_of_accounts[i].activation = 1; // Активируем 
				Set_color(2, 0); //Зеленый
				cout << "                                ________________________________________________________________" << endl;
				cout << "                                |                                                              |" << endl;
				cout << "                                |                    Аккаунт успешно активирован!              |" << endl;
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

// Выбор действия в меню авторизации________________________________________________________________________________________________________
Accounts* Authorization_menu(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int sw;
	bool flag = true;
	while (flag)
	{

		Set_color(1, 0); // Синий | Цвет текста | Цвет фона
		cout << "                                           ________________________________________            " << endl;
		cout << "                                          /                                        \\          " << endl;
		cout << "                                         /          Г Л А В Н О Е  М Е Н Ю          \\         " << endl;
		cout << "                                        /|__________________________________________|\\        " << endl;
		Set_color(7, 0); // Светло-серый 
		cout << "                                        ||                                          ||         " << endl;
		cout << "                                        ||             1. Вход в аккаунт            ||         " << endl;
		cout << "                                        ||             2. Регистрация               ||         " << endl;
		cout << "                                        ||__________________________________________||         " << endl;
		cout << "                                        ||                                          ||         " << endl;
		cout << "                                        ||             0. Вернуться назад           ||         " << endl;
		cout << "                                        ||__________________________________________||         " << endl;
		cout << "                                                  >>";
		Protection(0, 2, sw);
		switch (sw)
		{
		case 1: // Вход в аккаунт 
			Check_login_and_password(arr_of_accounts, number_of_accounts); // Проверяем данные для входа 
			break;

		case 2: // Регистрация аккаунта 
			arr_of_accounts = Memory_reallocation_for_accounts(arr_of_accounts, number_of_accounts, number_of_accounts + 1); // Перевыделение памяти
			Add_accounts(arr_of_accounts, number_of_accounts); // Запись информации
			break;

		case 0:
			flag = false;
			break;
		}
	}
	return arr_of_accounts;
}

// Проверка логина и пароля_____________________________________________________________________________________________________________________ 
void Check_login_and_password(Accounts* arr_of_accounts, int& number_of_accounts)
{
	bool findLogin = true, errorLogin = true, flagPassword = true, flagGlobal = true;
	int login, amount = 3;
	string TempLogin, TempPassword;

	while (findLogin) // Цикл для поиска логина 
	{
		cout << "                                         ____________________________________________" << endl << endl;
		cout << "                                                       Введите логин: ";

		cin >> TempLogin; // Просим ввести логин 
		for (int i = 0; i < number_of_accounts; i++)
		{
			if (TempLogin == arr_of_accounts[i].login) // Если такой логин существует 
			{
				login = i; // Запоминаем индекс 
				findLogin = false; // Выходим из цикла т.к. нашли логин
				errorLogin = false; // Отключаем следующую запись
			}
		}
		if (errorLogin) // Сработает если логин не будет найден
		{
			system("cls");
			amount--; // Если ввели неверный логин уменьшаем переменную
			cout << "                                         ____________________________________________" << endl << endl;
			Set_color(12, 0);
			cout << "                                              Аккаунт с логином " << TempLogin << " не обнаружен.      " << endl;
			cout << "                                                      Попыток осталось: " << amount << "               " << endl;
			Set_color(7, 0);

			if (amount == 0) // Если значение 0 --> выходим из цикла 
			{
				Set_color(12, 0);
				cout << endl << "                                      Мы заметили подозрительную активность. Попробуйте позже.      " << endl;
				Sleep(1500);
				system("cls");
				findLogin = false;
				flagPassword = false; // Отключаем следующий цикл
			}
		}
	}
	amount = 3; // Обновляем amout 
	while (flagPassword)
	{
		cout << "                                                       Введите пароль: ";
		TempPassword = Inputing_password(); // Для ввода пароля 
		if (TempPassword == arr_of_accounts[login].password) // Если пароль подошел к аккаунту 
		{
			if (arr_of_accounts[login].activation) // Если состояние 1(true) --> проверяем роль
			{
				Check_user_status(arr_of_accounts, number_of_accounts, arr_of_accounts[login].status); // Проверяем кто зашел
			}
			else // Если 0 (false) --> значит аккаунт деактивирован 
			{

				Set_color(12, 0);
				cout << endl << "                               Ошибка! Данный аккаунт Д Е К А Т И В И Р О В А Н. Ожидайте активацию" << endl << endl;
				Sleep(1500);
				system("cls");
			}
			flagPassword = false;
		}
		else // Если пароль не совпал 
		{
			Password_incorrect(TempLogin, flagPassword, amount); // В Signal | Выводит ошибку если несколько раз ввели не тот пароль
		}
	}
}

// Перевыделение памяти____________________________________________________________________________________________________________________

Accounts* Memory_reallocation_for_accounts(Accounts* arr_of_accounts, int& number_of_accounts, int m) // m принимает значение на 1 больше 
{
	Accounts* temp_arr = new Accounts[m]; // Выделяем память

	for (int i = 0; i < number_of_accounts; i++) // Переносим старые данные 
	{
		temp_arr[i].login = arr_of_accounts[i].login;
		temp_arr[i].password = arr_of_accounts[i].password;
		temp_arr[i].status = arr_of_accounts[i].status;
		temp_arr[i].activation = arr_of_accounts[i].activation;
	}

	delete[]arr_of_accounts; // Удаляем старый массив структур
	number_of_accounts = m; // Обновляем информацию о количестве
	arr_of_accounts = temp_arr; // Переносим информацию 

	return arr_of_accounts; // Возвращаем обновленный массив
}

// Проверка статуса. Выбор вывода меню: Админ | Пользователь_______________________________________________________________________________ 
void Check_user_status(Accounts* arr_of_accounts, int& number_of_accounts, int role)
{
	if (role == 1) // Если админ 
	{
		system("cls");
		Set_color(2, 0);
		cout << "                                       //// Вы авторизовались как администратор \\\\\\\\\\           " << endl << endl;
		Set_color(7, 0);
		Admin_menu(arr_of_accounts, number_of_accounts); // Включаем меню админа 
	}

	else
		if (role == 0) // Если пользователь
		{
			system("cls");
			Set_color(2, 0);
			cout << "                                         //// Вы авторизовались как пользователь \\\\\\\\\\           " << endl;
			Set_color(7, 0);
			User_menu(); // Переход в функционал пользователя 
		}
}

// Меню админа для выбора действия_____________________________________________________________________________________________ 
void Admin_menu(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int sw;
	bool flag = true;
	while (flag)
	{
		Set_color(1, 0); // Синий | Цвет текста | Цвет фона
		cout << "                                           _______________________________________            " << endl;
		cout << "                                          /                                       \\          " << endl;
		cout << "                                         /   М Е Н Ю | А Д М И Н С Т Р А Т О Р А   \\         " << endl;
		cout << "                                        /|_________________________________________|\\        " << endl;
		Set_color(7, 0); // Светло-серый 
		cout << "                                        ||                                         ||         " << endl;
		cout << "                                        ||        1. Работа с аккаунтами           ||         " << endl;
		cout << "                                        ||        2. Работа с сотрудниками         ||         " << endl;
		cout << "                                        ||_________________________________________||         " << endl;
		cout << "                                        ||                                         ||         " << endl;
		cout << "                                        ||        0. Вернуться назад               ||         " << endl;
		cout << "                                        ||_________________________________________||         " << endl;
		cout << "                                                  >>";

		Protection(0, 2, sw);
		switch (sw)
		{
		case 1: // Работа с аккаунтами
			system("cls");
			Admin_accounts_menu(arr_of_accounts, number_of_accounts); // Меню для управление аккаунтами 
			break;

		case 2: // Работа с сотрудниками
			system("cls");
			User_menu();
			break;

		case 0:
			system("cls");
			flag = false; // Для выхода из цикла
			break;
		}
	}

}

// Меню админа для работы с аккаунтами_________________________________________________________________________________________________
void Admin_accounts_menu(Accounts* arr_of_accounts, int& number_of_accounts)
{
	int sw;
	bool flag = true;
	while (flag)
	{
		Set_color(1, 0); // Синий | Цвет текста | Цвет фона
		cout << "                                           _______________________________________            " << endl;
		cout << "                                          /                                       \\          " << endl;
		cout << "                                         /             А К К А У Н Т Ы             \\         " << endl;
		cout << "                                        /|_________________________________________|\\        " << endl;
		Set_color(7, 0); // Светло-серый 
		cout << "                                        ||                                         ||         " << endl;
		cout << "                                        ||         1. Посмотреть аккаунты          ||        " << endl;
		cout << "                                        ||         2. Редактировать аккаунты       ||        " << endl;
		cout << "                                        ||         3. Удалить аккаунт              ||        " << endl;
		cout << "                                        ||_________________________________________||         " << endl;
		cout << "                                        ||                                         ||         " << endl;
		cout << "                                        ||             0. Вернуться назад          ||         " << endl;
		cout << "                                        ||_________________________________________||         " << endl;
		cout << "                                                  >>";

		Protection(0, 3, sw);
		switch (sw)
		{
		case 1: // Просмотр аккаунтов
			system("cls");
			Show_accounts(arr_of_accounts, number_of_accounts);
			break;

		case 2: // Корректировки аккаунтов
			Change_in_accounts(arr_of_accounts, number_of_accounts);
			break;

		case 3: // Удаление аккаунта
			system("cls");
			Show_accounts(arr_of_accounts, number_of_accounts);
			Del_accounts(arr_of_accounts, number_of_accounts);
			break;

		case 0: // Для выхода из while
			flag = false;
			system("cls");
			break;
		}
	}

}

// Для удаления аккаунта_____________________________________________________________________________________________________________________ 
void Del_accounts(Accounts* arr_of_accounts, int& number_of_accounts)
{
	string delLogin; // Для логина аккаунта, который хотим удалить 
	cout << "                               ____________________________________________________________________" << endl << endl;
	cout << "                                        Введите логин аккаунта, который хотите удалить: ";

	cin >> delLogin;
	int i = 0, del = 0;
	bool flag = true;

	while (flag && i <= number_of_accounts)
	{
		if (arr_of_accounts[i].login == delLogin) // Поиск аккаунта 
		{
			flag = false; // Если нашли --> выходим из цикла 
		}
		else
		{
			i++;
		}
	}

	if (flag) // Если аккаунта нет 
	{
		Account_not_found();
	}
	else // Если аккаунт есть 
	{
		if (arr_of_accounts[i].status == 1) // Защита чтобы нельзя было удалить аккаунт админа 
		{
			Set_color(12, 0);
			cout << endl;
			cout << "                                                     _______________" << endl;
			cout << "                                                    /               \\                           " << endl;
			cout << "                                                   /   О Ш И Б К А   \\                          " << endl;
			cout << "                               ___________________/___________________\\_________________________" << endl;
			cout << "                               |                                                               | " << endl;
			cout << "                               | У Вас недостаточно прав для удаления аккаунта администратора! | " << endl;
			cout << "                               |           Сперва Вам следует изменить роль аккаунта!          | " << endl;
			cout << "                               |_______________________________________________________________| " << endl;
			Set_color(7, 0);
			Sleep(2000);
			system("cls");
		}
		else
		{
			cout << "Вы действительно хотите удалить аккаунт: " << arr_of_accounts[i].login << endl;
			cout << "P.S. Удаленные данные не подлежат восстановления." << endl;
			cout << " 1. Да" << "\n 2. Нет" << "\n --> ";
			Protection(1, 2, del);
			if (del == 1)
			{
				for (int j = i; j < number_of_accounts - 1; j++) // i -> номер аккаунта | Смещение в конец удаленного аккаунта
				{
					arr_of_accounts[j] = arr_of_accounts[j + 1];
				}
				number_of_accounts--; // Уменьшаем количество аккаунтов 
				Save_it(); // Данные успешно сохранены
			}
			else
			{
				cout << "Удаление отменено" << endl;
			}
		}
	}
}
