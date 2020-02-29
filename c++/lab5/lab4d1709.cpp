// lab4d1709.cpp : Определяет точку входа для приложения.
//
//ok
#include "framework.h"
#include "lab4d1709.h"
#include "toolbar.h"
#include "shape.h"
#include "shape_editor.h"
#include "table.h"



#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
WPARAM state;
HWND hwndList = NULL;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Dialog(HWND, UINT, WPARAM, LPARAM);


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

ShapeObjectsEditor* Edit = ShapeObjectsEditor::getInstance();
MyTable* Table = new MyTable();
int indx = -1;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	
	switch (message)
	{
	case WM_CREATE:
		OnCreate(hWnd, hInst);
		SetWindowTextW(hWnd, (LPWSTR)"Виберіть режим");
	if (Table && Edit)
		{
			Table->Open();
			for (int i = 0; i < Table->GetLength(); i++)
			{
				Edit->Add(Table->GetList()[i]);
			}
		}
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
		if (Edit) {
			Edit->OnLBup(hWnd);
			if (Table && Edit->GetData(Table->GetLength()).pointer) {
				Table->Add(Edit->GetData(Table->GetLength()).string);
				InvalidateRect(hwndList, NULL, TRUE);
			}
		}
		break;
	case WM_MOUSEMOVE: //пересунуто мишу у клієнтській частині вікна
		if ((wParam & MK_LBUTTON) && Edit) Edit->OnMouseMove(hWnd);
		break;
	case WM_PAINT: //потрібно оновлення зображення клієнтської частині вікна
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		if (Edit) {
			Edit->OnPaint(hWnd, hdc);
			if (indx > -1)
			{
				Edit->Select(hWnd, indx);
			};
		}
		EndPaint(hWnd, &ps);
		break;
	/*case WM_INITMENUPOPUP: //позначка пунктів меню - для окремих варіантів завдань
		if (Edit) Edit->OnInitMenuPopup(hWnd, wParam, state);
		break;
		*/
	case WM_COMMAND:
	{
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
			//state = wParam;
		case IDM_POINT:
		case ID_TOOL_POINT:
			OnToolMove(hWnd, ID_TOOL_POINT);
			if (Edit) Edit->Start(new PointShape); //початок вводу точкових об’єктів
			break;
		case IDM_LINE:
		case ID_TOOL_LINE:
			OnToolMove(hWnd, ID_TOOL_LINE);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу ліній");
			if (Edit) Edit->Start(new LineShape); //початок вводу об’єктів-ліній
			break;
		case IDM_RECT:
		case ID_TOOL_RECT:
			OnToolMove(hWnd, ID_TOOL_RECT);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу прямокутників");
			if (Edit) Edit->Start(new RectShape); //початок вводу прямокутників
			break;
		case IDM_ELLIPSE:
		case ID_TOOL_ELLIPSE:
			OnToolMove(hWnd, ID_TOOL_ELLIPSE);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу еліпсів");
			if (Edit) Edit->Start(new EllipseShape); //початок вводу еліпсів
			break;
		case IDM_LINEOO:
		case ID_TOOL_LINEOO:
			OnToolMove(hWnd, ID_TOOL_LINEOO);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу палиць з бульбами");
			if (Edit) Edit->Start(new LineOOShape);
			break;
		case IDM_CUBE:
		case ID_TOOL_CUBE:
			OnToolMove(hWnd, ID_TOOL_CUBE);
			SetWindowTextW(hWnd, (LPWSTR)"Режим вводу кубів");
			if (Edit) Edit->Start(new CubeShape);
			break;
		case IDM_LISTDLG:
			if (!hwndList) {
				hwndList = CreateDialog(hInst,
					MAKEINTRESOURCE(IDD_TABLE),
					hWnd, Dialog);
			}
			ShowWindow(hwndList, SW_SHOW);
			break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			if (Table) Table->Save();
			DestroyWindow(hWnd);
			DestroyWindow(hwndList);
			delete Edit;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_DESTROY:
		if (Table) Table->Save();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK Dialog(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM)
{
	std::string* list = Table->GetList();
	//std::string caption = "Фігура                         \t x1 \t y1 \t x2 \t y2";
	int wmId, wmEvent;
	switch (iMessage)
	{
	case WM_INITDIALOG:
		//SendDlgItemMessage(hDlg, IDC_LIST5, LB_ADDSTRING, 0, (LPARAM)caption.c_str());
		return (INT_PTR)TRUE;

	case WM_PAINT:
		//ind = SendDlgItemMessage(hDlg, IDC_LIST5, LB_RESETCONTENT, 0, 0);
		Table->Show(hDlg, IDC_LIST5);

		break;
	case WM_COMMAND:
		/*
		if (LOWORD(wParam) == IDC_CLEAR)
		{
			indx = SendDlgItemMessage(hDlg, IDC_LIST5, LB_GETCURSEL, 0, 0);
				Table->Clear(hDlg, IDC_LIST5, indx);
				Table->Show(hDlg, IDC_LIST5);
				Edit->Clear(GetParent(hDlg), indx);
				SendDlgItemMessage(hDlg, IDC_LIST5, LB_DELETESTRING, indx, 0);
				indx = -1;
			break;
		}
		*/
		if (LOWORD(wParam) == IDC_DELETE)
		{
			indx = SendDlgItemMessage(hDlg, IDC_LIST5, LB_GETCURSEL, 0, 0);
			if (indx >= 0) {
				Table->Delete(hDlg, IDC_LIST5, indx);
				Edit->Delete(GetParent(hDlg), indx);
				SendDlgItemMessage(hDlg, IDC_LIST5, LB_DELETESTRING, indx, 0);
				indx = -1;
			}
			break;
		}
		if (HIWORD(wParam) == LBN_DBLCLK) //двойной клик
		{
			indx = SendDlgItemMessage(hwndList, IDC_LIST5, LB_GETCURSEL, 0, 0);
			InvalidateRect(GetParent(hwndList), NULL, TRUE);
			//	Edit->Delete(GetParent(hDlg), indx);
			//HDC hdc;
			//if (Edit) Edit->Select(GetParent(hDlg), hdc, indx);
			break;
		}
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, 1);
			break;
		}
		if (LOWORD(wParam) == IDCANCEL) EndDialog(hDlg, 0);
		break;
	default: break;
	}
	return (INT_PTR)FALSE;
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
