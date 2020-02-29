#include "stdafx.h"
#include "Information.h"

long GetTextFromClipboard(HWND hWnd, char *dest, long maxsize) {
	HGLOBAL hglb;
	LPTSTR lptstr;
	long size, res;

	res = 0;
	if (!IsClipboardFormatAvailable(CF_TEXT)) return 0;
	if (!OpenClipboard(hWnd)) return 0;
	hglb = GetClipboardData(CF_TEXT);
	if (hglb != NULL) {
		lptstr = (char *)GlobalLock(hglb);
		if (lptstr != NULL) {
			size = strlen(lptstr);
			if (size > maxsize) {
				lptstr[maxsize] = 0;
				size = strlen(lptstr);
			}
			strcpy_s(dest, 1200, lptstr);
			res = size;
			GlobalUnlock(hglb);
		}
	}
	CloseClipboard();
	return res;
}