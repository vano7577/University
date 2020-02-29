﻿// lab4d1709.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab4d1709.h"
#include "toolbar.h"
#include "shape.h"
#include "shape_editor.h"



#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
WPARAM state;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void OnCreate(HWND hWnd, HINSTANCE hInst);
void OnSize(HWND hWnd);
void OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnToolMove(HWND hWnd, int id);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	InitCommonControls();
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB4D1709, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4D1709));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4D1709));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB4D1709);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//

ShapeObjectsEditor *Edit = new ShapeObjectsEditor;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	
	switch (message)
	{
	case WM_CREATE:
		OnCreate(hWnd, hInst);
		SetWindowTextW(hWnd, (LPCWSTR)"Виберіть режим");
		break;
	case WM_SIZE:
		OnSize(hWnd);
		break;
	case WM_NOTIFY:
		OnNotify(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN: //натиснуто ліву кнопку миші у клієнтській частині вікна
		if (Edit) Edit->OnLBdown(hWnd);
		break;
	case WM_LBUTTONUP: //відпущено ліву кнопку миші у клієнтській частині вікна
		if (Edit) Edit->OnLBup(hWnd);
		break;
	case WM_MOUSEMOVE: //пересунуто мишу у клієнтській частині вікна
		if ((wParam & MK_LBUTTON) && Edit) Edit->OnMouseMove(hWnd);
		break;
	case WM_PAINT: //потрібно оновлення зображення клієнтської частині вікна
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		if (Edit) Edit->OnPaint(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_INITMENUPOPUP: //позначка пунктів меню - для окремих варіантів завдань
		if (Edit) Edit->OnInitMenuPopup(hWnd, wParam, state);
		break;
		
	case WM_COMMAND:
	{
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
			
		case IDM_POINT:
		case ID_TOOL_POINT:
			OnToolMove(hWnd, ID_TOOL_POINT);
			state = IDM_POINT;
			if (Edit) Edit->Start(new PointShape); //початок вводу точкових об’єктів
			break;
		case IDM_LINE:
		case ID_TOOL_LINE:
			state = IDM_LINE;
			OnToolMove(hWnd, ID_TOOL_LINE);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу ліній");
			if (Edit) Edit->Start(new LineShape); //початок вводу об’єктів-ліній
			break;
		case IDM_RECT:
		case ID_TOOL_RECT:
			state = IDM_RECT;
			OnToolMove(hWnd, ID_TOOL_RECT);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу прямокутників");
			if (Edit) Edit->Start(new RectShape); //початок вводу прямокутників
			break;
		case IDM_ELLIPSE:
		case ID_TOOL_ELLIPSE:
			state = IDM_ELLIPSE;
			OnToolMove(hWnd, ID_TOOL_ELLIPSE);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу еліпсів");
			if (Edit) Edit->Start(new EllipseShape); //початок вводу еліпсів
			break;
		case IDM_LINEOO:
		case ID_TOOL_LINEOO:
			state = IDM_LINEOO;
			OnToolMove(hWnd, ID_TOOL_LINEOO);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу палиць з бульбами");
			if (Edit) Edit->Start(new LineOOShape);
			break;
		case IDM_CUBE:
		case ID_TOOL_CUBE:
			state = IDM_CUBE;
			OnToolMove(hWnd, ID_TOOL_CUBE);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу кубів");
			if (Edit) Edit->Start(new CubeShape);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			delete Edit;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
