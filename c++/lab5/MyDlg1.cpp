#include "framework.h"
#include "resource.h"
#include "MyDlg1.h"
/*
void MyDlg1::OnInit(HWND hDlg)
{
//!!!
};
void MyDlg1::OnCommand(HWND hDlg, WPARAM wParam, LPARAM	lParam)
{
	if (LOWORD(wParam) == IDC_DELETE)
	{
		indx = SendDlgItemMessage(hDlg, IDC_LIST5, LB_GETCURSEL, 0, 0);
		if (indx > 0) {
			Table->Delete(hDlg, IDC_LIST5, indx);
			Edit->Delete(GetParent(hDlg), indx);
			SendDlgItemMessage(hDlg, IDC_LIST5, LB_DELETESTRING, indx, 0);
			indx = -1;
		}
		break;
	}
	if (HIWORD(wParam) == LBN_DBLCLK) //двойной клик
	{
		indx = SendDlgItemMessage(hwndList, IDC_LIST5, LB_GETCURSEL, 0, 0);
		InvalidateRect(GetParent(hwndList), NULL, TRUE);
	}
	if (LOWORD(wParam) == IDOK)
	{
		EndDialog(hDlg, 1);
		break;
	}
	if (LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, 0);
};
void WorkDialog1(HWND hWnd) 
{
	MyDlg1* pd;
	pd = new MyDlg1;
	if (pd) 
	{
		pd->Run(hWnd, IDD_TABLE);
		delete pd;
	}
}
*/