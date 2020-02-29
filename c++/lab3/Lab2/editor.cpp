#include "stdafx.h"
#include "editor.h"
#include "shape.h"
#include "editor.rh"

const int MY_SHAPE_ARRAY_SIZE = 114;
static int count = 0;
int position = 0;


Shape *pcshape[MY_SHAPE_ARRAY_SIZE];

Editor::~Editor()
{
	for (int i = 0; i < count; i++)
		free(pcshape[i]);
}

ShapeEditor::ShapeEditor()
{
	isPoint = isLine = isRect = isEllipse = FALSE;
}

ShapeEditor::~ShapeEditor()
{}

void ShapeEditor::OnMouseMove(HWND hWnd) {
};


void ShapeEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < count; i++)
		if (pcshape[i])
			pcshape[i]->Show(hdc);
	EndPaint(hWnd, &ps);
}

void ShapeEditor::OnInitMenuPopup(HWND hWnd, WPARAM wParam)
{
	HMENU hMenu, hSubMenu;
	hMenu = GetMenu(hWnd);
	hSubMenu = GetSubMenu(hMenu, 1); //POPUP-���� ��'����
	if ((HMENU)wParam == hSubMenu && isPoint)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
	if ((HMENU)wParam == hSubMenu && isLine)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
	if ((HMENU)wParam == hSubMenu && isRect)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_CHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_UNCHECKED);
	}
	if ((HMENU)wParam == hSubMenu && isEllipse)
	{
		CheckMenuItem(hSubMenu, IDM_POINT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_LINE, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_RECT, MF_UNCHECKED);
		CheckMenuItem(hSubMenu, IDM_ELLIPSE, MF_CHECKED);
	}
	isPoint = isLine = isRect = isEllipse = FALSE;
}

void ShapeEditor::OnLBdown(HWND hWnd)
{
	if (isPoint) { position = 1; };
	if (isLine) { position = 2; };
	if (isRect) { position = 3; };
	if (isEllipse) { position = 4; };
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	if (isPoint)
	{
		x1 = x2 = pt.x;
		y1 = y2 = pt.y;
	}
	else {
		x1 = pt.x;
		y1 = pt.y;
	}
}

void ShapeEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	HDC hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	switch (position)
	{
	case 1:
		PointShape * Point;
		Point = new PointShape();
		Point->Set(x1, y1, x2, y2);
		pcshape[count] = Point;
		break;
	case 2:
		LineShape * Line;
		Line = new LineShape();
		Line->Set(x1, y1, x2, y2);
		pcshape[count] = Line;
		break;
	case 3:
		RectShape * Rect;
		Rect = new RectShape();
		Rect->Set(x1, y1, x2, y2);
		pcshape[count] = Rect;
		break;
	case 4:
		EllipseShape * Ellipse;
		Ellipse = new EllipseShape();
		Ellipse->Set(x1, y1, x2, y2);
		pcshape[count] = Ellipse;
		break;
	default:
		break;
	}
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
	
}

// Point


PointEditor::PointEditor()
{
	isPoint = TRUE;
}

// Line
LineEditor::LineEditor() {
	isLine = TRUE;
}
EllipseEditor::EllipseEditor() {
	isEllipse = TRUE;
}

void LineEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, 0);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	//��������� �� "��������" ���� ������������ ������������ �������
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //���������� ������� ����� �������
	y2 = pt.y;
	//	��������� �� "��������" ���� ��� ��������� ������������ �������

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc); //��������� �������� ����
}

// Rect
RectEditor::RectEditor() {
	isRect = TRUE;
}

void RectEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, 0);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	//��������� �� "��������" ���� ������������ ������������ �������
	int x0 = 2 * x1 - x2;
	int y0 = 2 * y1 - y2;
	MoveToEx(hdc, x0, y0, NULL);
	LineTo(hdc, x2, y0);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x0, y2);
	LineTo(hdc, x0, y0);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //���������� ������� ����� �������
	y2 = pt.y;
	//	��������� �� "��������" ���� ��� ��������� ������������ �������
	int x01 = 2 * x1 - x2;
	int y01 = 2 * y1 - y2;
	MoveToEx(hdc, x01, y01, NULL);
	LineTo(hdc, x2, y01);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x01, y2);
	LineTo(hdc, x01, y01);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc); //��������� �������� ����
}

// Ellipse


void EllipseEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, 0);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	//��������� �� "��������" ���� ������������ ������������ �������

	MoveToEx(hdc, x1, y1, NULL);
	Arc(hdc, x1, y1, x2, y2, 0, 0, 0, 0);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //���������� ������� ����� �������
	y2 = pt.y;
	//	��������� �� "��������" ���� ��� ��������� ������������ �������


	MoveToEx(hdc, x1, y1, NULL);
	Arc(hdc, x1, y1, x2, y2, 0, 0, 0, 0);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc); //��������� �������� ����
}
