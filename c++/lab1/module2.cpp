#include "framework.h"
#include "module2.h"
#include "resource2.h"
static INT_PTR CALLBACK Work4(HWND, UINT, WPARAM, LPARAM);

char Buffer_MOD2[50];

//Callback-функція вікна 

INT_PTR CALLBACK Work4(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM) 
{ 
switch (iMessage)
	{   
	case WM_COMMAND:   
		if (LOWORD(wParam) == ID_YES2)          
			{ 
		//зчитуємо вміст елементу Edit Control у буфер       
			GetDlgItemText(hDlg, IDC_EDIT1, (LPTSTR)Buffer_MOD2, 50); 
			EndDialog(hDlg, 1);
			break;
			}   
		if (LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, 0);   
		break;
	default : break;   
	}
return 0;
} 

char* Func_MOD2(HINSTANCE hInst, HWND hWnd)
{
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Work4);
	return Buffer_MOD2;
}
