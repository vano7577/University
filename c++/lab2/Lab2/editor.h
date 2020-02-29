#pragma once

class Editor
{
public:
	virtual ~Editor();
	virtual void OnLBdown(HWND) = 0;
	virtual void OnLBup(HWND) = 0;
	virtual void OnMouseMove(HWND) = 0;
	virtual void OnPaint(HWND) = 0;
};

class ShapeEditor : public Editor
{
protected:
	int x1, y1, x2, y2;
	bool isPoint, isLine, isRect, isEllipse;
public:
	ShapeEditor();
	~ShapeEditor();
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
	void OnInitMenuPopup(HWND, WPARAM);
};

class PointEditor : public ShapeEditor
{
public:
	void OnLBdown(HWND);
	void OnLBup(HWND);
};
class LineEditor : public ShapeEditor
{
public:
	void OnMouseMove(HWND);
	void OnLBdown(HWND);
	void OnLBup(HWND);
};
class RectEditor : public ShapeEditor
{
public:
	void OnMouseMove(HWND);
	void OnLBdown(HWND);
	void OnLBup(HWND);
};
class EllipseEditor : public ShapeEditor
{
public:
	void OnMouseMove(HWND);
	void OnLBdown(HWND);
	void OnLBup(HWND);
};