#include "stdafx.h"
#include "Information.h"

int PutTextToClipboard(HWND hWnd, char *src) {
	HGLOBAL hglbCopy; BYTE *pTmp; long len;

	if (src == NULL) return 0;
	if (src[0] == 0) return 0;
	len = strlen(src);
	hglbCopy = GlobalAlloc(GHND, len + 1);
	if (hglbCopy == NULL) return FALSE;
	pTmp = (BYTE *)GlobalLock(hglbCopy);
	memcpy(pTmp, src, len + 1);
	GlobalUnlock(hglbCopy);
	if (!OpenClipboard(hWnd)) {
		GlobalFree(hglbCopy);
		return 0;
	}
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hglbCopy);
	CloseClipboard();
	return 1;
}

