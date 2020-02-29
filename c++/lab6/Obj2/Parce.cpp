#include "stdafx.h"
#include "Parce.h"

void IntToBuffer(int *arr, char *buf, int length) {
	buf[1000] = ' ';
	int counter = 0;
	for (int i = 0; i < length * 2; i++) {
		if (arr[i] < 0) {
			arr[i] = 0 - arr[i];
			buf[counter] = '-';
			counter++;
		}
		if (arr[i] < 10) {
			buf[counter] = arr[i] + '0';
			buf[counter + 1] = ',';
			counter += 2;
		}
		else if (arr[i] < 100 && arr[i] >= 10) {
			buf[counter] = arr[i] / 10 + '0';
			buf[counter + 1] = arr[i] % 10 + '0';
			buf[counter + 2] = ',';
			counter += 3;
		}
		else if (arr[i] < 1000 && arr[i] >= 100) {
			buf[counter] = arr[i] / 100 + '0';
			buf[counter + 1] = (arr[i] / 10) % 10 + '0';
			buf[counter + 2] = arr[i] % 10 + '0';
			buf[counter + 3] = ',';
			counter += 4;
		}
		else if (arr[i] < 10000 && arr[i] >= 1000) {
			buf[counter] = arr[i] / 1000 + '0';
			buf[counter + 1] = (arr[i] / 100) % 10 + '0';
			buf[counter + 2] = (arr[i] / 10) % 100 + '0';
			buf[counter + 3] = arr[i] % 10 + '0';
			buf[counter + 4] = ',';
			counter += 5;
		}
		else if (arr[i] < 100000 && arr[i] >= 10000) {
			buf[counter] = arr[i] / 10000 + '0';
			buf[counter + 1] = (arr[i] / 1000) % 10 + '0';
			buf[counter + 2] = (arr[i] / 100) % 100 + '0';
			buf[counter + 3] = (arr[i] / 10) % 1000 + '0';
			buf[counter + 4] = arr[i] % 10 + '0';
			buf[counter + 5] = ',';
			counter += 6;
		}
		if (i == length * 2 - 1) buf[counter] = '$';
	}
}