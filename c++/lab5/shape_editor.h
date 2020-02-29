#pragma once
#include "shape.h"
#include <string>
const int MY_SHAPE_ARRAY_SIZE = 103;

class ShapeObjectsEditor
{
private:
	static ShapeObjectsEditor* p_instance;
	int x1, y1, x2, y2;
	ShapeObjectsEditor();

protected:


	int count;
	bool isMouseMove, isPoint, isLine, isRect,
		 isEllipse, isLineOO, isCube;
	Shape** pcshape = new Shape * [MY_SHAPE_ARRAY_SIZE];;
	ShapeObjectsEditor& operator=(ShapeObjectsEditor&);
	struct Figure
	{
		Shape* pointer;
		std::string string;
	};
public:
	~ShapeObjectsEditor();
	static ShapeObjectsEditor *getInstance();
	ShapeObjectsEditor::Figure GetData(int indx);
	void Start(Shape *);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND, HDC);
	void OnInitMenuPopup(HWND, WPARAM, WPARAM);
	void Delete(HWND, int);
	void Clear(HWND, int);
	void Add(std::string);
	void Select(HWND, int);
};