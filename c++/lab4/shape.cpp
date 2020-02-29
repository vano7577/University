#include "framework.h"
#include "shape.h"
#include <math.h>


void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

// Point

void PointShape::Show(HDC hdc, bool isMouseMove)
{
	SetPixel(hdc, xs1, ys1, RGB(0, 0, 0));
}

Shape *PointShape::Copy()
{
	return new PointShape;
}

// Line

void LineShape::Show(HDC hdc, bool isMouseMove)
{
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
}

Shape *LineShape::Copy()
{
	return new LineShape;
}

// Rect

void RectShape::Show(HDC hdc, bool isMouseMove)
{
	int xs0 = 2 * xs1 - xs2;
	int ys0 = 2 * ys1 - ys2;
	MoveToEx(hdc, xs0, ys0, NULL);
	LineTo(hdc, xs2, ys0);
	LineTo(hdc, xs2, ys2);
	LineTo(hdc, xs0, ys2);
	LineTo(hdc, xs0, ys0);
}

Shape *RectShape::Copy()
{
	return new RectShape;
}

// Ellipse

void EllipseShape::Show(HDC hdc, bool isMouseMove)
{
	if (!isMouseMove) {
		HBRUSH hBrush, hBrushOld;
		hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0)); //створюється пензль
		hBrushOld = (HBRUSH)SelectObject(hdc, hBrush); //пензль -> у hdc
		Ellipse(hdc, xs1, ys1, xs2, ys2);
		SelectObject(hdc, hBrushOld); //відновлюється пензль-попередник
		DeleteObject(hBrush);
	}
	else {
		Ellipse(hdc, xs1, ys1, xs2, ys2);
	}

}

Shape *EllipseShape::Copy()
{
	return new EllipseShape;
}

// LineOO

void LineOOShape::Show(HDC hdc, bool isMouseMove)
{
	LineShape::Show(hdc, isMouseMove);
	int x1 = xs1;
	int y1 = ys1;
	int x2 = xs2;
	int y2 = ys2;
	EllipseShape::Set(x1 - 10, y1 - 10, x1 + 10, y1 + 10);
	EllipseShape::Show(hdc, isMouseMove);
	EllipseShape::Set(x2 - 10, y2 - 10, x2 + 10, y2 + 10);
	EllipseShape::Show(hdc, isMouseMove);
	xs1 = x1;
	xs2 = x2;
	ys1 = y1;
	ys2 = y2;
}


LineOOShape *LineOOShape::Copy()
{
	return new LineOOShape;
}

// Cube

void CubeShape::Show(HDC hdc, bool isMouseMove)
{
	RectShape::Show(hdc, isMouseMove);
	int x1 = xs1;
	int x2 = xs2;
	int y1 = ys1;
	int y2 = ys2;
	int x01 = 2 * x1 - x2;
	int y01 = 2 * y1 - y2;
	int a = -(y01 - y2) / 3;
	RectShape::Set(x1+a, y1+a, x2+a, y2+a);
	RectShape::Show(hdc, isMouseMove);
	LineShape::Set(x01, y01, x01+a, y01+a);
	LineShape::Show(hdc, isMouseMove);
	LineShape::Set(x2, y01, x2+a, y01+a);
	LineShape::Show(hdc, isMouseMove);
	LineShape::Set(x2, y2, x2+a, y2+a);
	LineShape::Show(hdc, isMouseMove);
	LineShape::Set(x01, y2, x01+a, y2+a);
	LineShape::Show(hdc, isMouseMove);
	xs1 = x1;
	xs2 = x2;
	ys1 = y1;
	ys2 = y2;
}

CubeShape *CubeShape::Copy()
{
	return new CubeShape;
}