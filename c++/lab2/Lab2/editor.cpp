#include "stdafx.h"
#include "editor.h"
#include "shape.h"
#include "editor.rh"

const int MY_SHAPE_ARRAY_SIZE = 114;
static int count = 0;

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

void ShapeEditor::OnMouseMove(HWND hWnd) {};


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
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = pt.x;
	y1 = pt.y;
}

void ShapeEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	InvalidateRect(hWnd, NULL, TRUE);
}

// Point


void PointEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x; //������ �������� ���������� ��������� �����
	y1 = y2 = pt.y;
}

void PointEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //������ �������� ���������� ��������� �����
	y2 = pt.y;
	isPoint = TRUE;
	HDC hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	PointShape *Point;
	Point = new PointShape();
	Point->Set(x1, y1, x2, y2);
	pcshape[count] = Point;
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
}

// Line


void LineEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
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

void LineEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void LineEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //������ �������� ���������� ��������� �����
	y2 = pt.y;
	isLine = TRUE;

	LineShape *Line;
	Line = new LineShape();
	Line->Set(x1, y1, x2, y2);
	pcshape[count] = Line;
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
}

// Rect


void RectEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	//��������� �� "��������" ���� ������������ ������������ �������
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y1);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x1, y2);
	LineTo(hdc, x1, y1);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //���������� ������� ����� �������
	y2 = pt.y;
	//	��������� �� "��������" ���� ��� ��������� ������������ �������

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y1);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x1, y2);
	LineTo(hdc, x1, y1);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc); //��������� �������� ����
}

void RectEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void RectEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //������ �������� ���������� ��������� �����
	y2 = pt.y;
	isRect = TRUE;
	HDC hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	RectShape *Rect;
	Rect = new RectShape();
	Rect->Set(x1, y1, x2, y2);
	pcshape[count] = Rect;
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
}

// Ellipse


void EllipseEditor::OnMouseMove(HWND hWnd)
{
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	//��������� �� "��������" ���� ������������ ������������ �������
	int x0 = (x1 + x2) / 2;
	int y0 = (y1 + y2) / 2;
	MoveToEx(hdc, x1, y1, NULL);
	Arc(hdc, x0, y0, x2, y2, 0, 0, 0, 0);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //���������� ������� ����� �������
	y2 = pt.y;
	//	��������� �� "��������" ���� ��� ��������� ������������ �������
	x0 = (x1 + x2) / 2;
	y0 = (y1 + y2) / 2;

	MoveToEx(hdc, x1, y1, NULL);
	Arc(hdc, x0, y0, x2, y2, 0, 0, 0, 0);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc); //��������� �������� ����
}

void EllipseEditor::OnLBdown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
}

void EllipseEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x; //������ �������� ���������� ��������� �����
	y2 = pt.y;
	isEllipse = TRUE;
	HDC hdc = GetDC(hWnd); //�������� �������� ���� ��� ���������
	EllipseShape *Ellipse;
	Ellipse = new EllipseShape();
	Ellipse->Set(x1, y1, x2, y2);
	pcshape[count] = Ellipse;
	count++;
	InvalidateRect(hWnd, NULL, TRUE);
}
