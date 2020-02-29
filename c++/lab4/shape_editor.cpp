#include "framework.h"
#include "shape_editor.h"
#include "resource.h"
#include "shape.h"
const int MY_SHAPE_ARRAY_SIZE = 103;

ShapeObjectsEditor::ShapeObjectsEditor()
{
	//isPoint, isLine, isRect, isEllipse = FALSE;
	count = 0;
	pcshape = new Shape * [MY_SHAPE_ARRAY_SIZE];
	//isMouseMove = FALSE;
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
	for (int i = 0; i < count; i++)
		delete pcshape[i];
	delete pcshape;
}

void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam, WPARAM state)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1); //POPUP-меню Об'єкти
	int wmId = LOWORD(wParam);

	if ((HMENU)wParam == hSubMenu && state== IDM_POINT){
		CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);

	};
	
	if (((HMENU)wParam == hSubMenu) && (state== IDM_POINT))
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINEOO, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_CUBE, MF_UNCHECKED);

	}
	
	if (((HMENU)wParam == hSubMenu) && (state == IDM_LINE))
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINEOO, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_CUBE, MF_UNCHECKED);
	}
	if (((HMENU)wParam == hSubMenu) && (state== IDM_RECT))
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINEOO, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_CUBE, MF_UNCHECKED);
	}
	if ((HMENU)wParam == hSubMenu && state== IDM_ELLIPSE)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_LINEOO, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_CUBE, MF_UNCHECKED);
	}
	if ((HMENU)wParam == hSubMenu && state == IDM_LINEOO)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINEOO, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_CUBE, MF_UNCHECKED);
	}
	if ((HMENU)wParam == hSubMenu && state == IDM_CUBE)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINEOO, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_CUBE, MF_CHECKED);
	}
	isPoint = isLine = isRect = isEllipse =isLineOO=isCube= FALSE;
}

/*
void ShapeObjectsEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1); //POPUP-меню Об'єкти
	if ((HMENU)wParam == hSubMenu && isPoint)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINEOO, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_CUBE, MF_UNCHECKED);

	}
	isPoint = isLine = isRect = isEllipse = isLineOO = isCube = FALSE;
}
*/
void ShapeObjectsEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void ShapeObjectsEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //кудись записуємо координати початкової точки
	y2 = pt.y;
	HDC hdc = GetDC(hWnd); //отримуємо контекст вікна для малювання
	pcshape[count]->Set(x1, y1, x2, y2);
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
	pcshape[count] = pcshape[count - 1]->Copy();
}

void ShapeObjectsEditor::OnMouseMove(HWND hWnd)
{
	isMouseMove = true;
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd); //отримуємо контекст вікна для малювання
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, 0);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	//Малюються лінії "гумового" сліду попереднього розташування курсору
	MoveToEx(hdc, x1, y1, NULL);
	pcshape[count]->Set(x1, y1, x2, y2);
	pcshape[count]->Show(hdc, isMouseMove);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //координати поточної точки курсору
	y2 = pt.y;
	//	Малюються лінії "гумового" сліду для поточного розташування курсору
	MoveToEx(hdc, x1, y1, NULL);
	pcshape[count]->Set(x1, y1, x2, y2);
	pcshape[count]->Show(hdc, isMouseMove);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc); //закриваємо контекст вікна
	isMouseMove = FALSE;
}

void ShapeObjectsEditor::OnPaint(HWND hWnd, HDC hdc)
{
	for (int i = 0; i < count; i++)
		if (pcshape[i])
			pcshape[i]->Show(hdc, isMouseMove);
}

void ShapeObjectsEditor::Start(Shape *shape)
{
	pcshape[count] = shape;
}

