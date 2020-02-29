#pragma once
#include "shape.h"

class ShapeObjectsEditor
{
protected:
	int x1, y1, x2, y2;
	bool isMouseMove;
	bool isPoint, isLine, isRect, isEllipse, isLineOO, isCube;
	int count;
	Shape** pcshape;
public:
	ShapeObjectsEditor(void);
	~ShapeObjectsEditor();
	void Start(Shape *);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND, HDC);
	void OnInitMenuPopup(HWND, WPARAM, WPARAM); //відповідно варіанту завдання
};