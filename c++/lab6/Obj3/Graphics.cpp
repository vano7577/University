#include "stdafx.h"
#include "Graphics.h"

void Graph(HWND hWnd, int maxx, int maxy, int minx, int miny, int *arr, int length) {
	int *arrey = new int[length];
	for (int i = 0; i < length; i++) {
		arrey[i] = arr[i];
	}
	HDC hdc = GetDC(hWnd);
	char lol[20];

	MoveToEx(hdc, 40, 20, NULL);
	LineTo(hdc, 40, 640);
	MoveToEx(hdc, 40, 330, NULL);
	LineTo(hdc, 780, 330);

	LineTo(hdc, 770, 325);
	MoveToEx(hdc, 780, 330, NULL);
	LineTo(hdc, 770, 335);
	TextOut(hdc, 790, 320, "X*10", 4);

	MoveToEx(hdc, 35, 30, NULL);
	LineTo(hdc, 40, 20);
	LineTo(hdc, 45, 30);
	TextOut(hdc, 50, 20, "Y*10", 4);

	float consx = (maxx - minx) / 20.0;
	float vivodx = (maxx - minx) / 20.0;

	float consy = (maxy - miny) / 20.0;
	float vivody = (maxy - miny) / 20.0;

	_itoa_s(miny, lol, sizeof(lol), 10);
	TextOut(hdc, 10, 610, lol, 2);
	for (int i = 1; i <= 10; i++) {
		MoveToEx(hdc, 36 * i + 40, 325, NULL);
		LineTo(hdc, 36 * i + 40, 335);

		_itoa_s((minx + vivodx) * 10, lol, sizeof(lol), 10);
		TextOut(hdc, 36 * i + 40, 345, lol, sizeof((minx + vivodx) * 10) - 1);


		MoveToEx(hdc, 36 * i + 400, 325, NULL);
		LineTo(hdc, 36 * i + 400, 335);

		_itoa_s((minx + consx * 21 - vivodx) * 10, lol, sizeof(lol), 10);
		TextOut(hdc, 36 * (11 - i) + 400, 345, lol, 3);

		vivodx += consx;



		MoveToEx(hdc, 35, 29 * i + 20, NULL);
		LineTo(hdc, 45, 29 * i + 20);
		_itoa_s((miny + consy * 21 - vivody) * 10, lol, sizeof(lol), 10);
		TextOut(hdc, 10, 29 * i + 10, lol, 3);

		MoveToEx(hdc, 35, 29 * i + 330, NULL);
		LineTo(hdc, 45, 29 * i + 330);
		_itoa_s((miny + consy * 11 - vivody) * 10, lol, sizeof(lol), 10);
		TextOut(hdc, 10, 29 * i + 290, lol, 3);

		vivody += consy;

	}

	if (maxx == minx)maxx++;
	if (maxy == miny)maxy++;

	bool fist = true;
	for (int i = 0; i < length; i += 2) {
		int max = -100000;
		int el = 0;

		for (int j = 0; j < length; j += 2) {
			if (max < arrey[j]) {
				max = arrey[j];
				el = j;
			}
			if (j == length - 2) arrey[el] = -1000000;
		}
		if (fist) {
			MoveToEx(hdc, 37 * ((arr[el] - minx) * 20 / (maxx - minx)) + 40, 640 - 30 * ((arr[el + 1] - miny) * 20 / (maxy - miny)), NULL);
			fist = false;
			continue;
		}
		LineTo(hdc, 37 * ((arr[el] - minx) * 20 / (maxx - minx)) + 40, 640 - 30 * ((arr[el + 1] - miny) * 20 / (maxy - miny)));
	}


}