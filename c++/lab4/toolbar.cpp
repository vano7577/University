#include "framework.h"
#include "toolbar.h"
#include "Resource.h"
static int press = 0, prevId = 0;

HWND hwndToolBar = NULL;
void OnCreate(HWND hWnd, HINSTANCE hInst)
{
	SendMessage(hwndToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[6];
	TBADDBITMAP tbab;

	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = IDB_STD_SMALL_COLOR;
	SendMessage(hwndToolBar, TB_ADDBITMAP, 0, (LPARAM)&tbab);

	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = 0;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_TOOL_POINT;

	tbb[1].iBitmap = 1;
	tbb[1].fsState = TBSTATE_ENABLED;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_TOOL_LINE;

	tbb[2].iBitmap = 2;
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_TOOL_RECT;

	tbb[3].iBitmap = 3;
	tbb[3].fsState = TBSTATE_ENABLED;
	tbb[3].fsStyle = TBSTYLE_BUTTON;
	tbb[3].idCommand = ID_TOOL_ELLIPSE;

	tbb[4].iBitmap = 4;
	tbb[4].fsState = TBSTATE_ENABLED;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	tbb[4].idCommand = ID_TOOL_LINEOO;

	tbb[5].iBitmap = 5;
	tbb[5].fsState = TBSTATE_ENABLED;
	tbb[5].fsStyle = TBSTYLE_BUTTON;
	tbb[5].idCommand = ID_TOOL_CUBE;
	SendMessage(hwndToolBar, TB_ADDBUTTONS, 6, (LPARAM)&tbb);
	hwndToolBar = CreateToolbarEx(hWnd,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS |
		CCS_TOP | TBSTYLE_TOOLTIPS,
		IDC_MY_TOOLBAR,
		6,
		hInst,
		IDB_BITMAP1,
		tbb,
		6,
		48, 48, 48, 48,
		sizeof(TBBUTTON));
}
void OnSize(HWND hWnd)
{
	RECT rc, rw;

	if (hwndToolBar)
	{
		GetClientRect(hWnd, &rc);
		GetWindowRect(hwndToolBar, &rw);
		MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
	}
}
void OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	LPNMHDR pnmh = (LPNMHDR)lParam;
	LPSTR pText;

	if (pnmh->code == TTN_NEEDTEXT)
	{
		LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
		switch (lpttt->hdr.idFrom)
		{
		case ID_TOOL_POINT:
			pText = (LPSTR)"Крапка";
			break;
		case ID_TOOL_LINE:
			pText = (LPSTR)"Лінія";
			break;
		case ID_TOOL_RECT:
			pText = (LPSTR)"Прямокутник";
			break;
		case ID_TOOL_ELLIPSE:
			pText = (LPSTR)"Еліпс";
			break;
		case ID_TOOL_LINEOO:
			pText = (LPSTR)"Палиця з бульбами";
			break;
		case ID_TOOL_CUBE:
			pText = (LPSTR)"Куб";
			break;
		default: pText = (LPSTR)"Щось невідоме";
		}
		lstrcpyA((LPSTR)lpttt->szText, pText);
	}
}
void OnToolMove(HWND hWnd, int id)
{
	if (prevId)
	{
		press = !press;
		SendMessage(hwndToolBar, TB_PRESSBUTTON, prevId, press);
	}
	press = !press;
	SendMessage(hwndToolBar, TB_PRESSBUTTON, id, press);
	prevId = id;
}