#include "framework.h"
#include "module1.h"
#include "resource1.h"

static INT_PTR CALLBACK Work3(HWND, UINT, WPARAM, LPARAM);

static char 
str1[6] = "ІП-81",
str2[6] = "ІП-82",
str3[6] = "ІП-83",
str4[6] = "ІП-84",
str5[6] = "ІП-85",
buf[6];
INT_PTR CALLBACK Work3(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM)
{
	int id = IDC_LIST1;
	switch (iMessage)
	{
	case WM_INITDIALOG:
		SendDlgItemMessage(hDlg, id, LB_ADDSTRING, 0, (LPARAM)str1);
		SendDlgItemMessage(hDlg, id, LB_ADDSTRING, 0, (LPARAM)str2);
		SendDlgItemMessage(hDlg, id, LB_ADDSTRING, 0, (LPARAM)str3);
		SendDlgItemMessage(hDlg, id, LB_ADDSTRING, 0, (LPARAM)str4);
		SendDlgItemMessage(hDlg, id, LB_ADDSTRING, 0, (LPARAM)str5);
		return 1;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_YES1)
		{
			//зчитуємо вибраний елементу списку у буфер
			int indx = SendDlgItemMessage(hDlg, id, LB_GETCURSEL, 0, 0);
			SendDlgItemMessage(hDlg, id, LB_GETTEXT, indx, (LPARAM)buf);
			EndDialog(hDlg, 1);
			break;
		}
		if (LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, 0);
		break;
	default: break;
	}
	return 0;
}

char *Func_MOD1(HINSTANCE hInst, HWND hWnd)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Work3);
	return buf;
}