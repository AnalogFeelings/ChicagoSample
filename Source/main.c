#include "framework.h"

#define MAX_LOADSTRING 100
#define TIMER_IDENT 0xBEEF

#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 200

#define LABEL_WIDTH 300
#define LABEL_HEIGHT 32

#define FORMAT_BUFFER_SIZE 48

static HINSTANCE hInst;
static TCHAR szTitle[MAX_LOADSTRING];
static TCHAR szWindowClass[MAX_LOADSTRING];
static TCHAR szExitCaption[MAX_LOADSTRING];
static TCHAR szExitText[MAX_LOADSTRING];

static DWORD SecondsPassed = 0;
static HWND SecondsLabelHwnd = NULL;
static HWND ChicagoLabelHwnd = NULL;
static HFONT GuiFont = NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AboutProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SetFont(HWND, LPARAM);

DWORD APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, DWORD nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CHICAGOSAMPLE, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EXITCAPTION, szExitCaption, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EXITTEXT, szExitText, MAX_LOADSTRING);

	WNDCLASSEX wcex =
	{
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_HREDRAW | CS_VREDRAW,
		.lpfnWndProc = WndProc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = hInstance,
		.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHICAGOSAMPLE)),
		.hCursor = LoadCursor(NULL, IDC_ARROW),
		.hbrBackground = GetSysColorBrush(COLOR_BTNFACE),
		.lpszMenuName = MAKEINTRESOURCE(IDC_CHICAGOSAMPLE),
		.lpszClassName = szWindowClass,
		.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL))
	};

	RegisterClassEx(&wcex);

	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	hInst = hInstance;

	if (!hWnd)
		return FALSE;

	ChicagoLabelHwnd = CreateWindow("STATIC", "Compiled with the Windows 11 SDK and ChicagoCRT!", WS_VISIBLE | WS_CHILD | SS_LEFT, 10, 10, LABEL_WIDTH, LABEL_HEIGHT, hWnd, NULL, hInstance, NULL);
	SecondsLabelHwnd = CreateWindow("STATIC", "0 seconds have passed since opening!", WS_VISIBLE | WS_CHILD | SS_LEFT, 10, 50, LABEL_WIDTH, LABEL_HEIGHT, hWnd, NULL, hInstance, NULL);

	SetTimer(hWnd, TIMER_IDENT, 1000, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHICAGOSAMPLE));

	// Set the font for all child elements.
	NONCLIENTMETRICS metrics;
	RtlZeroMemory(&metrics, sizeof(NONCLIENTMETRICS));

	metrics.cbSize = sizeof(metrics);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);

	GuiFont = CreateFontIndirect(&metrics.lfMessageFont);

	EnumChildWindows(hWnd, (WNDENUMPROC)SetFont, (LPARAM)GuiFont);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

// Set the font for a control.
BOOL CALLBACK SetFont(HWND hWnd, LPARAM font)
{
	SendMessage(hWnd, WM_SETFONT, font, TRUE);

    return TRUE;
}

// Process the messages for the main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		if(MessageBox(hWnd, szExitText, szExitCaption, MB_ICONWARNING | MB_YESNO) == IDYES)
		{
			DestroyWindow(hWnd);
		}
		return 0;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);

		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutProc);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		if(GuiFont) DeleteObject(GuiFont);

		KillTimer(hWnd, TIMER_IDENT);
		PostQuitMessage(0);

		break;
	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_IDENT:
			SecondsPassed++;

			CHAR buff[FORMAT_BUFFER_SIZE];
			RtlZeroMemory(buff, FORMAT_BUFFER_SIZE);

			sprintf(buff, "%d seconds have passed since opening!", SecondsPassed);

			SetWindowText(SecondsLabelHwnd, buff);
			break;
		}
		break;
	case WM_SIZE:
		DWORD width = LOWORD(lParam);
		DWORD height = HIWORD(lParam);

		SetWindowPos(ChicagoLabelHwnd, NULL, 0, 0, width - 20, 32, SWP_NOMOVE);
		SetWindowPos(SecondsLabelHwnd, NULL, 0, 0, width - 20, 32, SWP_NOMOVE);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
LRESULT CALLBACK AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));

			return TRUE;
		}
		break;
	}
	return FALSE;
}
