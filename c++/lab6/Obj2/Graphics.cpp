#include "stdafx.h"
#include "Graphics.h"

void Table(long Num, HWND hWnd, int *arr, int length) {
	HDC hdc = GetDC(hWnd);
	char text[40];
	int kilk = 0;
	bool znakx = true;
	//InvalidateRect(hWnd,NULL, TRUE);
	TextOut(hdc, 60, 20, "X", 1);
	TextOut(hdc, 120, 20, "Y", 1);
	for (int i = 0; i < Num; i++) {
		TextOut(hdc, 60, 20 * (i + 2), "       ", 7);
		TextOut(hdc, 120, 20 * (i + 2), "       ", 7);
		if (i < length) {
			kilk = 0;
			if (arr[2 * i] < 0) {
				kilk = 1;
				znakx = false;
				arr[2 * i] = 0 - arr[2 * i];
			}
			if (arr[2 * i] < 10) kilk += 1;
			else if (arr[2 * i] < 100 && arr[2 * i] >= 10) kilk += 2;
			else if (arr[2 * i] < 1000 && arr[2 * i] >= 100) kilk += 3;
			else if (arr[2 * i] < 10000 && arr[2 * i] >= 1000) kilk += 4;
			else if (arr[2 * i] < 100000 && arr[2 * i] >= 10000) kilk += 5;
			if (!znakx) arr[2 * i] = 0 - arr[2 * i];
			_itoa_s(arr[2 * i], text, sizeof(text), 10);
			TextOut(hdc, 60, 20 * (i + 2), text, kilk);

			kilk = 0;
			if (arr[2 * i + 1] < 0) {
				kilk = 1;
				znakx = false;
				arr[2 * i + 1] = 0 - arr[2 * i + 1];
			}
			if (arr[2 * i] < 10) kilk += 1;
			else if (arr[2 * i + 1] < 100 && arr[2 * i] >= 10) kilk += 2;
			else if (arr[2 * i + 1] < 1000 && arr[2 * i] >= 100) kilk += 3;
			else if (arr[2 * i + 1] < 10000 && arr[2 * i] >= 1000) kilk += 4;
			else if (arr[2 * i + 1] < 100000 && arr[2 * i] >= 10000) kilk += 5;
			if (!znakx) arr[2 * i + 1] = 0 - arr[2 * i];
			//text[40] = ' ';

			_itoa_s(arr[2 * i + 1], text, sizeof(text), 10);
			TextOut(hdc, 120, 20 * (i + 2), text, kilk);
		}

	}
}