#include "Employees.h"
#include "Protection.h"
#include "Signal.h"

// Структура работников >>  ФИО  |       Отдел        | Должность  | ЗП 
// Структура отделов    >> Отдел | Кол-во сотрудников | Общая ЗП
// ИДЗ >> Сумма выплат по отделам | Средняя ЗП по отделам | Вывести сотрудников с ЗП ниже введенной 
// Стартовое меню пользователя для перехода из файла с аккаунтами

void User_menu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int number_of_Employees = 0;
	Check_employees_file(number_of_Employees); // Определение размера массива 
	Employee* arr_of_Employees = new Employee[number_of_Employees]; // Выделяем новую память 
	Read_from_employees_file(arr_of_Employees, number_of_Employees); // Чтение файла и перенос данных в массивы 
	arr_of_Employees = Menu_employees(arr_of_Employees, number_of_Employees); // Меню сотрудников

	Write_to_employees_file(arr_of_Employees, number_of_Employees); // Записываем сотрудников
	delete[] arr_of_Employees;
}

// Определение количества сотрудников_______________________________________________________________________________________________

void Check_employees_file(int& number_of_Employees)
{
	string temp;
	ifstream fin(FILE_INFO_EMPLOYEES, ios::in); // Открыть файл для чтения 
	if (!fin.is_open())
	{
		number_of_Employees = 1;
	}
	else
	{
		while (!fin.eof()) // Пока не дойдем до коцна файла 
		{
			fin >> temp >> temp >> temp >> temp >> temp >> temp;
			number_of_Employees++;
		}
	}
	fin.close();
}

// Чтение и запись информации в массивы структур_________________________________________________________________________________

void Read_from_employees_file(Employee* arr_of_Employees, int number_of_Employees)
{
	ifstream fin(FILE_INFO_EMPLOYEES, ios::in);
	if (!fin.is_open()) // Если пусто 
	{
		Set_color(12, 0);
		cout << "                                ________________________________________________________________" << endl;
		cout << "                                |                                                              |" << endl;
		cout << "                                |                   Список сотрудников пуст!                   |" << endl;
		cout << "                                |           Пожалуйста, добавьте первого сотрудника!           |" << endl;
		cout << "                                |______________________________________________________________|" << endl;
		Set_color(7, 0);
		Add_employees(arr_of_Employees, number_of_Employees); // Запускаем функцию добавления сотрудников
	}
	else // Если сотрудники уже есть в файле 
	{
		int i = 0;
		while (!fin.eof()) // Считываем всю информацию из файла 
		{
			fin >> arr_of_Employees[i].Name >> arr_of_Employees[i].Surname >> arr_of_Employees[i].Patronymic >>
				arr_of_Employees[i].Department >> arr_of_Employees[i].Position >> arr_of_Employees[i].Salary;
			i++;
		}
	}
	fin.close();
}

// Запись в файл___________________________________________________________________________________________________________________________

void Write_to_employees_file(Employee* arr_of_Employees, int number_of_Employees)
{
	ofstream fout(FILE_INFO_EMPLOYEES, ios::out); // Для сохранение в файл
	for (int i = 0; i < number_of_Employees; i++)
	{
		fout << arr_of_Employees[i].Name << " " << arr_of_Employees[i].Surname << " " << arr_of_Employees[i].Patronymic << " " <<
			arr_of_Employees[i].Department << " " << arr_of_Employees[i].Position << " " << arr_of_Employees[i].Salary;
		if (i < number_of_Employees - 1) // endl пока не дойдем до последнего сотрудника 
			fout << endl;
	}
	fout.close();
}

// Меню сотрудников (Выбор действия)______________________________________________________________________________________

Employee* Menu_employees(Employee* arr_of_Employees, int& number_of_Employees)
{
	bool flag = true; // Для остановки цикла 
	while (flag)
	{

		Set_color(1, 0); // Синий | Цвет текста | Цвет фона
		cout << "                                            _______________________________________           " << endl;
		cout << "                                           /                                       \\         " << endl;
		cout << "                                          /       М Е Н Ю | С О Т Р У Д Н И К И     \\        " << endl;
		cout << "                                         /|_________________________________________|\\       " << endl;
		Set_color(7, 0); // Светло-серый
		cout << "                                         ||                                         ||        " << endl;
		cout << "                                         ||        1. Показать всех сотрудников     ||        " << endl;
		cout << "                                         ||        2. Добавить сотрудника           ||        " << endl;
		cout << "                                         ||        3. Редактировать данные          ||        " << endl;
		cout << "                                         ||        4. Удалить сотрудника            ||        " << endl;
		cout << "                                         ||        5. Индивидуальное задание        ||        " << endl;
		cout << "                                         ||        6. Сортировка                    ||        " << endl;
		cout << "                                         ||        7. Поиск                         ||        " << endl;
		cout << "                                         ||_________________________________________||        " << endl;
		cout << "                                         ||                                         ||        " << endl;
		cout << "                                         ||        0. Вернуться назад               ||        " << endl;
		cout << "                                         ||_________________________________________||        " << endl;
		cout << "                                               >>";

		int sw;
		Protection(0, 7, sw); // Защита на ввода от букв и диапазон [0-7]
		switch (sw)
		{
		case 1: // Вывод инфу о сотрудниках 
			system("cls");
			Show_employees(arr_of_Employees, number_of_Employees);
			break;
		case 2: // Добавление новых сотрудников 
			arr_of_Employees = Memory_reallocation_for_employees(arr_of_Employees, number_of_Employees, number_of_Employees + 1); // перераспределение памяти т.к. мы добавляем сотрудников 
			Add_employees(arr_of_Employees, number_of_Employees); // Для добавления 
			break;
		case 3: // Обновление информации о сотрудниках 
			Updating_of_employees_information(arr_of_Employees, number_of_Employees);
			break;
		case 4: // Удаление 
			Show_employees(arr_of_Employees, number_of_Employees);
			Delete_employees(arr_of_Employees, number_of_Employees);
			break;
		case 5: // ИДЗ
			Menu_individual_task(arr_of_Employees, number_of_Employees);
			break;
		case 6: // Сортировка 
			arr_of_Employees = Selection_sorting_menu(arr_of_Employees, number_of_Employees);
			break;
		case 7: // Поиск
			Menu_of_finding_employees(arr_of_Employees, number_of_Employees);
			break;
		case 0:
			system("cls");
			flag = false;
			break; // Если хотят выйти меняем флаг на false 
		}
	}
	return arr_of_Employees;
}

// ПОКАЗАТЬ ВСЕХ СОТРУДНИКОВ____________________________________________________________________________________________________________________

void Show_employees(Employee* arr_of_Employees, int number_of_Employees)
{
	Set_color(14, 0);
	cout << "                                             _____________________________________                            " << endl;
	cout << "                                            /                                     \\                          " << endl;
	cout << "                  _________________________/  С П И С О К | С О Т Р У Д Н И К О В  \\_________________________ " << endl;
	cout << "                  |                                                                                         | " << endl << endl;
	Set_color(3, 0);
	cout << "                       " <<
		setw(12) << left << "Фамилия" <<
		setw(12) << left << "Имя" <<
		setw(18) << left << "Отчество" <<
		setw(15) << left << "Отдел" <<
		setw(15) << left << "Должность" <<
		setw(15) << left << "Зарплата" << endl;

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

// Перевыделение памяти___________________________________________________________________________________________________________

Employee* Memory_reallocation_for_employees(Employee* arr_of_Employees, int& number_of_Employees, int m)
{

	Employee* temp_arr = new Employee[m]; // Выделяем память под массив структур 
	for (int i = 0; i < number_of_Employees; i++) // Переносим старые данных
	{
		temp_arr[i].Name = arr_of_Employees[i].Name;
		temp_arr[i].Surname = arr_of_Employees[i].Surname;
		temp_arr[i].Patronymic = arr_of_Employees[i].Patronymic;
		temp_arr[i].Department = arr_of_Employees[i].Department;
		temp_arr[i].Position = arr_of_Employees[i].Position;
		temp_arr[i].Salary = arr_of_Employees[i].Salary;
	}

	delete[]arr_of_Employees; // Удаляем старые данные 
	number_of_Employees = m; // Обновляем количество сотрудников 
	arr_of_Employees = temp_arr; // Переносим информацию 
	return arr_of_Employees; // Возвращаем обновленную инфу
}

// ДОБАВЛЕНИЕ НОВОГО СОТРУДНИКА____________________________________________________________________________________________________

void Add_employees(Employee* arr_of_Employees, int& number_of_Employees)
{
	Set_color(14, 0);
	cout << "                                ________________________________________________________________" << endl;
	cout << "                                |                                                              |" << endl;
	cout << "                                |                  Добавление нового сотрудника!               |" << endl;
	cout << "                                |______________________________________________________________|" << endl;
	Set_color(7, 0);
	cout << "                                                       Введите фамилию: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Surname; // -1 т.к. индексирование с 0 
	cout << "                                                       Введите имя: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Name;
	cout << "                                                       Введите отчество: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Patronymic;
	cout << "                                                       Введите отдел: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Department;
	cout << "                                                       Введите должность: ";
	cin >> arr_of_Employees[number_of_Employees - 1].Position;
	cout << "                                                       Введите зарплату: ";
	Protection(0, 10000000000000000, arr_of_Employees[number_of_Employees - 1].Salary);
	Save_it();
}

// РЕДАКТИРОВАТЬ ИНФОРМАЦИЮ О СОТРУДНИКЕ___________________________________________________________________________________________________

void Updating_of_employees_information(Employee* arr_of_Employees, int& number_of_Employees)
{
	system("cls");
	Show_employees(arr_of_Employees, number_of_Employees); // Выводим на экран всех сотрудников 
	string temp; // Строка для фамилии 
	bool flag = true;
	int i = 0;
	cout << "                               ____________________________________________________________________" << endl;
	cout << "                                   Введите фамилию сотрудника, чьи данные хотите изменить: ";
	cin >> temp;
	while (flag && i < number_of_Employees) // Цикл для поиска фамилии | Пока flag true и пока не перебрали всех сотрудников
	{
		if (temp == arr_of_Employees[i].Surname) // Нашли совпадение --> прекращаем цикл 
		{
			flag = false;
		}
		else // Иначе идём дальше 
		{
			i++;
		}
	}

	if (flag) // Если ничего не нашли 
	{
		Account_not_found(); // Учетной записи с такой фамилией нету
	}
	else // Если нашли | После цикла while --> спрашиваем что нужно изменить 
	{

		Set_color(1, 0); // Синий | Цвет текста | Цвет фона
		cout << "                                           _________________________________________            " << endl;
		cout << "                                          /                                         \\          " << endl;
		cout << "                                         /   М Е Н Ю | Р Е Д А К Т И Р О В А Н И Е   \\         " << endl;
		cout << "                                        /|___________________________________________|\\        " << endl;
		Set_color(7, 0); // Светло-серый
		cout << "                                        ||                                           ||         " << endl;
		cout << "                                        ||            1. Изменить имя                ||         " << endl;
		cout << "                                        ||            2. Изменить фамилию            ||         " << endl;
		cout << "                                        ||            3. Изменить отчество           ||         " << endl;
		cout << "                                        ||            4. Изменить отдел              ||         " << endl;
		cout << "                                        ||            5. Изменить должность          ||         " << endl;
		cout << "                                        ||            6. Изменить зарплату           ||         " << endl;
		cout << "                                        ||___________________________________________||         " << endl;
		cout << "                                        ||                                           ||         " << endl;
		cout << "                                        ||            0. Вернуться назад             ||         " << endl;
		cout << "                                        ||___________________________________________||         " << endl;
		cout << "                                              >>";

		int sw;
		Protection(0, 6, sw);
		switch (sw)
		{
		case 1:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      Введите новое имя: ";
			cin >> arr_of_Employees[i].Name;
			Save_it(); // Новые данные успешно сохранены
			break;
		case 2:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      Введите новую фамилию: ";
			cin >> arr_of_Employees[i].Surname;
			Save_it();
			break;
		case 3:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      Введите новое отчество: ";
			cin >> arr_of_Employees[i].Patronymic;
			Save_it();
			break;
		case 4:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      Введите новый отдел: ";
			cin >> arr_of_Employees[i].Department;
			Save_it();
			break;
		case 5:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      Введите новую должность: ";
			cin >> arr_of_Employees[i].Position;
			Save_it();
			break;
		case 6:
			cout << "                                         ____________________________________________" << endl;
			cout << "                                                      Введите новую зарплату: ";
			cin >> arr_of_Employees[i].Salary;
			Save_it();
			break;

		case 0:  break;
		}
	}
}

// УДАЛЕНИЕ СОТРУДНИКА____________________________________________________________________________________________________________________

void Delete_employees(Employee* arr_of_Employees, int& number_of_Employees)
{
	string delEmployee;
	cout << "                               ________________________________________________________________" << endl;
	cout << "                                     Введите фамилию сотрудника, которого хотите удалить: ";
	cin >> delEmployee;
	int i = 0;
	bool flag = true;
	while (flag && i <= number_of_Employees) // Цикл для поиска нужного аккаунта 
	{
		if (arr_of_Employees[i].Surname == delEmployee)
		{
			flag = false; // Если нашли - изменяем flag 
		}
		else
		{
			i++;
		}
	}

	if (flag) // Если не нашли 
	{
		Account_not_found(); // Такой учетной записи нет (выводим сообщение)
	}
	else // Если нашли 
	{
		int del = 0;
		cout << "Вы действительно хотите удалить сотрудника: " << arr_of_Employees[i].Surname << endl;
		cout << "P.S. Удаленные данные не подлежат восстановления." << endl;
		cout << " 1. Да" << "\n 2. Нет" << "\n --> ";
		Protection(1, 2, del);
		if (del == 1)
		{
			for (int j = i; j < number_of_Employees - 1; j++) // i -> номер аккаунта | Смещение в конец удаленного аккаунта
			{
				arr_of_Employees[j] = arr_of_Employees[j + 1];
			}
			number_of_Employees--; // Уменьшаем количество сотрудников
			Save_it(); // Данные успешно сохранены
		}
		else
		{
			cout << "Удаление отменено" << endl;
		}
	}
}


// ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ______________________________________________________________________________________________________________


// Выбор ИДЗ

void Menu_individual_task(Employee* arr_of_Employees, int number_of_Employees)
{

	Set_color(1, 0); // Синий | Цвет текста | Цвет фона
	cout << "                                    ______________________________________________________            " << endl;
	cout << "                                   /                                                      \\          " << endl;
	cout << "                                  /  М Е Н Ю | И Н Д И В И Д У А Л Ь Н О Е  З А Д А Н И Е  \\         " << endl;
	cout << "                                 /|________________________________________________________|\\        " << endl;
	Set_color(7, 0); // Светло-серый
	cout << "                                 ||                                                        ||         " << endl;
	cout << "                                 ||             1. Сотрудники с зарплатой < введенной      ||         " << endl;
	cout << "                                 ||             2. Информация по отделам                   ||         " << endl;
	cout << "                                 ||________________________________________________________||         " << endl;
	cout << "                                 ||                                                        ||         " << endl;
	cout << "                                 ||             0. Вернуться назад                         ||         " << endl;
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

// ИДЗ №1 (Вывод сотрудников с ЗП меньше введенной с клавиатуры)__________________________________________________________________________

void Individual_task_salary_info(Employee* arr_of_Employees, int number_of_Employees) // С ЗП меньше указанной 
{
	cout << "                                    ________________________________________________________   " << endl;
	cout << "                                   /                                                        \\  " << endl;
	cout << "                                  /            Сотрудники с ЗП меньше указанной!             \\ " << endl;
	cout << "                                                      Введите зарплату: ";
	int FindSalary;
	cin >> FindSalary;
	for (int i = 0; i < number_of_Employees; i++)
	{
		if (arr_of_Employees[i].Salary < FindSalary) // Если зарплата меньше введенной --> выводим инфу о сотруднике 
		{
			Show_result_of_finding(arr_of_Employees, number_of_Employees, i);
		}
	}
}

// ИДЗ №2 (Информация по отделам | Общая ЗП | Средняя ЗП | Сотрудники)____________________________________________________________________

void Individual_task_departments_info(Employee* arr_of_Employees, int number_of_Employees)
{
	int number_of_dep = 1;
	Department* arr_of_dep = new Department[number_of_dep]; // Создаю 1 объект структуры изначально | Отдел | Сотрудники | ЗП
	// Берем 1 сотрудника и сверяем его инфу со всеми отделами 
	for (int i = 0; i < number_of_Employees; i++) // Прокрутка сотрудников 
	{
		for (int j = 0; j <= number_of_dep; j++) // Прокрутка отделов 
		{
			if (arr_of_Employees[i].Department == arr_of_dep[j].Department_name) // Если отдел сотрудника совпал с одним из уже существующих отедлов 
			{
				arr_of_dep[j].Total_department_salary += arr_of_Employees[i].Salary; // ЗП сотрудника добавляем к общей ЗП отдела 
				arr_of_dep[j].Employees_amount++; // Обновляем количество сотрудников 
				break;
			}

			if (j == number_of_dep) // Если так --> либо это первый сотрудинк | либо нету такого отдела 
			{
				if (number_of_dep == 0) // Добавляем сотрудника сразу без выделения новой памяти
				{
					arr_of_dep[j].Department_name = arr_of_Employees[i].Department; // Заносим название отдела 
					arr_of_dep[j].Employees_amount++; // Обновляем количество сотрудников в отделе 
					arr_of_dep[j].Total_department_salary += arr_of_Employees[i].Salary; // Добавляем зарплату сотрудника к общей по отделу 
				}
				else // Выделяем новую память 
				{
					arr_of_dep = Individual_task_department_memory_reallocation(arr_of_dep, number_of_dep, number_of_dep + 1); // Расширяем память
					arr_of_dep[j].Department_name = arr_of_Employees[i].Department;
					arr_of_dep[j].Employees_amount++;
					arr_of_dep[j].Total_department_salary += arr_of_Employees[i].Salary;
				}
				break;
			}
		}
	}

	for (int k = 1; k < number_of_dep; k++) // Вывод информации по отделу 
	{
		cout << "                                                       Отдел: " << arr_of_dep[k].Department_name << endl;
		cout << "                                                       Сотрудников в отделе: " << arr_of_dep[k].Employees_amount << endl;
		cout << "                                                       Общая зарплата: " << arr_of_dep[k].Total_department_salary << endl;
		cout << "                                                       Средняя ЗП: " << arr_of_dep[k].Total_department_salary / arr_of_dep[k].Employees_amount << endl << endl;
	}
	delete[]arr_of_dep; // Удаляем инфу после использования 
}

// ИДЗ №2 Перевыделение памяти для отделов_______________________________________________________________________________________________

Department* Individual_task_department_memory_reallocation(Department* arr_of_dep, int& number_of_dep, int m)
{

	Department* temp_arr = new Department[m];
	for (int i = 0; i < number_of_dep; i++) // Перенос информации
	{
		temp_arr[i].Department_name = arr_of_dep[i].Department_name;
		temp_arr[i].Employees_amount = arr_of_dep[i].Employees_amount;
		temp_arr[i].Total_department_salary = arr_of_dep[i].Total_department_salary;
	}

	delete[]arr_of_dep; // Удаляем старый массив 
	number_of_dep = m; // Обновляем размер  
	arr_of_dep = temp_arr; // Переносим информацию
	return arr_of_dep; // Возвращаем обновленные данные 
}



// МЕТОДЫ СОРТИРОВКИ________________________________________________________________________________________________________________


// Выбор сортировки 
Employee* Selection_sorting_menu(Employee* arr_of_Employees, int number_of_Employees)
{
	int sw;
	Set_color(1, 0); // Синий | Цвет текста | Цвет фона 
	cout << "                                        ______________________________________________            " << endl;
	cout << "                                       /                                              \\          " << endl;
	cout << "                                      /          М Е Н Ю | С О Р Т И Р О В К А         \\         " << endl;
	cout << "                                     /|________________________________________________|\\        " << endl;
	Set_color(7, 0); // Светло-серый 
	cout << "                                     ||                                                ||         " << endl;
	cout << "                                     ||             1. Отсортировать по фамилии        ||         " << endl;
	cout << "                                     ||             2. Отсортировать по отделам        ||         " << endl;
	cout << "                                     ||             3. Отсортировать по зарплатам      ||         " << endl;
	cout << "                                     ||________________________________________________||         " << endl;
	cout << "                                     ||                                                ||         " << endl;
	cout << "                                     ||             0. Вернуться назад                 ||         " << endl;
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

// Сортировка №1 (По фамилиям)__________________________________________________________________________________________________________

Employee* Sorting_by_Surname(Employee* arr_of_Employees, int number_of_Employees)
{
	Employee* temp_arr = new Employee[number_of_Employees]; // Выделяем память 
	for (int i = 0; i < number_of_Employees; i++) // Переносим информацию 
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
	cout << "                                  /            Сортировка сотрудников по фамилии!            \\    " << endl << endl;

	for (int i = 0; i < number_of_Employees - 1; i++)  // Сортировка от А до Я 
	{
		for (int j = 0; j < number_of_Employees - i - 1; j++) // Отступаем на один шаг 
		{
			if (temp_arr[j].Surname > temp_arr[j + 1].Surname) // Сравнием по ASCII
			{
				swap(temp_arr[j], temp_arr[j + 1]); // Меняет местами
			}
		}
	}
	Show_employees(temp_arr, number_of_Employees);

	int temp; // Временная переменная 
	Ask_for_saving(); // Сохранять? 

	Protection(1, 2, temp);
	switch (temp)
	{
	case 1: // Сохранить (Обновляем старый) 
		delete[]arr_of_Employees;
		arr_of_Employees = temp_arr;
		break;
	case 2: // Оставить 
		delete[] temp_arr; // Удаляем отсортированный 
		break;
	}
	return arr_of_Employees;
}

// Сортировка №2 (По отделам)__________________________________________________________________________________________________________

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
	cout << "                                  /             Сортировка сотрудников по отделу!           \\    " << endl << endl;

	for (int i = 0; i < number_of_Employees - 1; i++) // Для пользователя 1-ый сотрудинк --> 1 | Но в массиве 0 || От А до Я
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
	Ask_for_saving(); // Сохранять? 

	Protection(1, 2, temp);
	switch (temp)
	{
	case 1:
		delete[]arr_of_Employees; // Если нужно сохраниеть новые значения --> удаляем старый массив 
		arr_of_Employees = arr_new; // Заполняем массив новыми значениями 
		break;
	case 2:
		delete[] arr_new; // Если нет --> удаляем отсортированный 
		break;
	}
	return arr_of_Employees;
}

// Сортировка №3 (По зарплате)_________________________________________________________________________________________________________

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
	cout << "                                  /            Сортировка сотрудников по зарплате!            \\ " << endl << endl;

	for (int i = 0; i < number_of_Employees - 1; i++) // От меньшей к большей 
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
	Ask_for_saving(); // Сохранять? 

	Protection(1, 2, temp);
	switch (temp)
	{
	case 1: // Сохранить новый 
		Save_it(); // Новые данные успешно сохранены
		delete[]arr_of_Employees;
		arr_of_Employees = arr_new;
		break;
	case 2: // Оставить без изменений 
		delete[] arr_new;
		Save_it();
		break;
	}
	return arr_of_Employees;
}



// МЕТОДЫ ПОИСКА_______________________________________________________________________________________________________________ 


// Меню выбора поиска 
void Menu_of_finding_employees(Employee* arr_of_Employees, int number_of_Employees)
{
	Set_color(1, 0); // Синий | Цвет текста | Цвет фона 
	cout << "                                      __________________________________________________            " << endl;
	cout << "                                     /                                                  \\          " << endl;
	cout << "                                    /               М Е Н Ю | П О И С К A                \\         " << endl;
	cout << "                                   /|____________________________________________________|\\        " << endl;
	Set_color(7, 0); // Светло-серый 
	cout << "                                   ||                                                    ||         " << endl;
	cout << "                                   ||             1. Найти по фамилии                    ||         " << endl;
	cout << "                                   ||             2. Найти по должности                  ||         " << endl;
	cout << "                                   ||             3. Найти сотрудника с максимальной ЗП  ||         " << endl;
	cout << "                                   ||____________________________________________________||         " << endl;
	cout << "                                   ||                                                    ||         " << endl;
	cout << "                                   ||             0. Вернуться назад                     ||         " << endl;
	cout << "                                   ||____________________________________________________||         " << endl;
	cout << "                                               >>";

	int sw;
	Protection(0, 3, sw);

	switch (sw)
	{
	case 1: Find_surname(arr_of_Employees, number_of_Employees); break; // Поиск по фамилии
	case 2: Find_position(arr_of_Employees, number_of_Employees); break; // Поиск по должности 
	case 3: Find_max_salary(arr_of_Employees, number_of_Employees); break; // Поиск по максимальной зарплате 
	case 0: break; // Выход 
	}
}

// Поиск №1 (По фамилии)____________________________________________________________________________________________

void Find_surname(Employee* arr_of_Employees, int number_of_Employees)
{
	string FindSurname; // Для ввода фамилии 
	bool flag = true;
	cout << "                                  ________________________________________________________    " << endl;
	cout << "                                 /                                                        \\  " << endl;
	cout << "                                /              Поиск сотрудников по фамилии!               \\ " << endl;
	cout << "                                               Введите фамилию для поиска: ";
	cin >> FindSurname;
	for (int i = 0; i < number_of_Employees; i++)
	{
		if (FindSurname == arr_of_Employees[i].Surname) // Если нашли --> выводим 
		{
			Show_result_of_finding(arr_of_Employees, number_of_Employees, i);
			flag = false; // --> отклюачем следующий if
		}
	}
	if (flag)
	{
		Account_not_found(); // Такого аккаунта нет в системе
	}

}

// Поиск №2 (По должности)___________________________________________________________________________________________

void Find_position(Employee* arr_of_Employees, int number_of_Employees)
{
	string SearchPositio; // Для ввода должности 
	cout << "                                  _________________________________________________________     " << endl;
	cout << "                                 /                                                         \\   " << endl;
	cout << "                                /              Поиск сотрудников по должности!              \\  " << endl;
	cout << "                                               Введите должность для поиска: ";
	cin >> SearchPositio;
	bool flag = true;
	for (int i = 0; i < number_of_Employees; i++)
	{
		if (arr_of_Employees[i].Position == SearchPositio)
		{
			Show_result_of_finding(arr_of_Employees, number_of_Employees, i);
			flag = false; // --> отклюачем следующий if
		}
	}
	if (flag)
	{
		Account_not_found(); // Такого аккаунта нет в системе
	}
}

// Поиск №3 (По максимальной ЗП)__________________________________________________________________________________________

void Find_max_salary(Employee* arr_of_Employees, int number_of_Employees)
{
	cout << "                                    ________________________________________________________      " << endl;
	cout << "                                   /                                                        \\    " << endl;
	cout << "                                  /            Поиск сотрудников с наибольшей ЗП!            \\   " << endl;
	int MaxKol = 0;
	for (int i = 0; i < number_of_Employees; i++)
	{
		if (MaxKol < arr_of_Employees[i].Salary) // Если нашли зарплату больше 
		{
			MaxKol = arr_of_Employees[i].Salary; // Обновляем значение MaxKol
		}
	}
	for (int i = 0; i < number_of_Employees; i++) // Какой сотрудник имеет эту ЗП
	{
		if (arr_of_Employees[i].Salary == MaxKol) // Сверяем ЗП сотрудника 
		{
			Show_result_of_finding(arr_of_Employees, number_of_Employees, i);
		}
	}

}

// Вывод результатов поиска___________________________________________________________________________________________________________

void Show_result_of_finding(Employee* arr_of_Employees, int number_of_Employees, int i)
{
	cout << endl;
	cout << "                                               Ф.И.О. " << arr_of_Employees[i].Surname << " " << arr_of_Employees[i].Name << " " << arr_of_Employees[i].Patronymic << endl;
	cout << "                                               Отдел: " << arr_of_Employees[i].Department << endl;
	cout << "                                               Должность: " << arr_of_Employees[i].Position << endl;
	cout << "                                               Зарплата: " << arr_of_Employees[i].Salary << endl;
	cout << endl;
}
