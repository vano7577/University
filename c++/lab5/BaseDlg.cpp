#include "framework.h"
#include "BaseDlg.h"
/*
static MyDlgBaseClass* pdlg = NULL;

static INT_PTR CALLBACK CalledWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (pdlg) return pdlg->DlgWndProc(hDlg, message, wParam, lParam);
	return (INT_PTR)FALSE;
}
INT_PTR MyDlgBaseClass::DlgWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		OnInit(hDlg);
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, IDCANCEL);
			break;
		}
		OnCommand(hDlg, wParam, lParam);
		break;
	}
	return(INT_PTR)FALSE;
}
int MyDlgBaseClass::Run(HWND hwndParent, int idres)
{
	pdlg = this;
	return DialogBox((HINSTANCE)GetWindowLong(hwndParent, GWLP_HINSTANCE), MAKEINTRESOURCE(idres), hwndParent, CalledWndProc);
}
*/