#pragma once
#include <iostream> // Ввод | Вывод >> cout 
#include <Windows.h> // Для изменения цвета 

using namespace std;

void Save_it(); // Новые данные успешно сохранены!
void Set_color(int text, int bg); // Изменение цвета
void Ask_for_saving(); // Хотите сохранить? 
void Account_not_found(); // Такого аккаунта нет в системе
void Password_incorrect(string TempLogin, bool& flagPassword, int& amount); // Выводит ошибку если несколько раз ввели не тот пароль [Вход/Регистрация]