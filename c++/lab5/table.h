#pragma once
#include <string>
class MyTable {
private: 	
	std::string* list = new std::string[103];
	int count = 0;
public:
	std::string* GetList();
	int GetLength();
	std::string GetLast();
	void Save();
	void Open();
	void Delete(HWND, int, int);
	void Add(std::string);  //функція додавання у таблицю нового рядка з описом об’єкту     
	//void Clear(HWND, int, int);
	void Show(HWND, int);

};