#include "framework.h"
#include "table.h"
#include <fstream>
#include <cstdio>
#include "resource.h"


void MyTable::Add(std::string str)
{
	list[count] = str;
	count++;
}

int MyTable::GetLength()
{
	return count;
}

std::string* MyTable::GetList()
{
	return list;
}

std::string MyTable::GetLast()
{
	if (count == 0)
		return "";
	return list[count - 1];
}

void MyTable::Save()
{
	std::ofstream fout;
	fout.open("data.txt");
	fout.seekp(0, std::ios_base::beg);
	int i = 0;
	for (i; i < count - 1; i++) {
		fout << list[i] << "\n";
		fout.seekp(0, std::ios_base::cur);
	}
	fout << list[i];
	fout.close();
}

void MyTable::Delete(HWND hDlg, int id, int indx)
{
	for (int i = 0; i < count; i++) {
		if (i >= indx-1) list[i] = list[i + 1];
	}
	count--;
}
/*
void MyTable::Clear(HWND hDlg, int id, int indx)
{
	std::ofstream ofs("data.txt", std::ios::out | std::ios::trunc);
	ofs.close();
	//this->Open();
}
*/
void MyTable::Show(HWND hDlg, int id)
{
	SendDlgItemMessage(hDlg, IDC_LIST5, LB_RESETCONTENT, 0, 0);
	if (this->GetLength() != 0)
	{
		for (int i = 0; i < this->GetLength(); i++) {
			SendDlgItemMessage(hDlg, IDC_LIST5, LB_ADDSTRING, 0, (LPARAM)list[i].c_str());
		}
	}
}
void MyTable::Open()
{
	std::ifstream fin;
	fin.open("data.txt", std::ios::in);
	fin.seekg(0, std::ios_base::beg);
	while (!fin.eof())
	{
		std::string string;
		getline(fin, string);
		if (string.size() > 1) list[count++] = string;
	}
	fin.close();

}