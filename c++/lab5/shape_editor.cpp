#include "framework.h"
#include "shape_editor.h"
#include "shape.h"
#include <iomanip>
#include <fstream>

ShapeObjectsEditor* ShapeObjectsEditor::p_instance = NULL;

ShapeObjectsEditor& ShapeObjectsEditor::operator=(ShapeObjectsEditor& obj)
{
	x1 = obj.x1;
	x2 = obj.x2;
	y1 = obj.x1;
	y2 = obj.y2;
	count = obj.count;
	pcshape = obj.pcshape;
	isMouseMove = obj.isMouseMove;
	p_instance = obj.p_instance;
	return *this;
}

ShapeObjectsEditor* ShapeObjectsEditor::getInstance()
{
	if (!p_instance)
	{
		p_instance = new ShapeObjectsEditor();
	}
	return p_instance;
}

ShapeObjectsEditor::ShapeObjectsEditor()
{
	count = 0;
	isMouseMove = FALSE;
	for (int i = 0; i < MY_SHAPE_ARRAY_SIZE; i++)
		pcshape[i] = NULL;
}

ShapeObjectsEditor::~ShapeObjectsEditor()
{
	for (int i = 0; i < count; i++)
		delete[] pcshape[i];
	delete pcshape;
}
/*
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
void ShapeObjectsEditor::Select(HWND hWnd, int num) 
{
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd); //отримуємо контекст вікна для малювання
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	pcshape[num]->Show(hdc, isMouseMove);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc); //закриваємо контекст вікна
	//pcshape[num]->Show(hdc, isMouseMove, TRUE);
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

void ShapeObjectsEditor::Clear(HWND hWnd, int indx) {
	pcshape[0] = pcshape[count];
	count = 0;
	InvalidateRect(hWnd, NULL, TRUE);
}

ShapeObjectsEditor::Figure ShapeObjectsEditor::GetData(int indx)
{
	Figure f;
	if (pcshape[count]) {
		std::string stri = pcshape[indx]->Type();
		stri = stri +
			std::to_string(x1) + '\t'+
			std::to_string(y1) + '\t' +
			std::to_string(x2) + '\t' +
			std::to_string(y2);
		f.string = stri;
	}
	
	f.pointer = pcshape[indx];
	return f;
}

void ShapeObjectsEditor::Delete(HWND hWnd, int indx)
{
	for (int i = 0; i < count; i++) {
		if (i >= indx - 1) pcshape[i] = pcshape[i + 1];
	}
	count--;
	InvalidateRect(hWnd, NULL, TRUE);
}

void ShapeObjectsEditor::Add(std::string str)
{
	int tubPos1 = str.find('\t');
	std::string type = str.substr(0, tubPos1 + 1);
	type.pop_back();
	if (type.compare("Крапка                    ") == 0) pcshape[count] = new PointShape;
	if (type.compare("Лінія                        ") == 0) pcshape[count] = new LineShape;
	if (type.compare("Прямокутник            ") == 0) pcshape[count] = new RectShape;
	if (type.compare("Еліпс                        ") == 0) pcshape[count] = new EllipseShape;
	if (type.compare("Лінія з кружечками") == 0) pcshape[count] = new LineOOShape;
	if (type.compare("Паралелепіпед        ") == 0) pcshape[count] = new CubeShape;

	int tubPos2 = str.find_first_of('\t', tubPos1 + 1);
	int tubPos3 = str.find_first_of('\t', tubPos2 + 1);
	int tubPos4 = str.find_first_of('\t', tubPos3 + 1);
	int xs1 = atoi(str.substr(tubPos1, 4).c_str());
	int ys1 = atoi(str.substr(tubPos2, 4).c_str());
	int xs2 = atoi(str.substr(tubPos3, 4).c_str());
	int ys2 = atoi(str.substr(tubPos4, 4).c_str());
	if (pcshape[count]) {
		pcshape[count]->Set(xs1, ys1, xs2, ys2);
		count++;
	}
}
