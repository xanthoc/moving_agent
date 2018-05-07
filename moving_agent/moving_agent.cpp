// moving_agent.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "moving_agent.h"
#include "GameWorld.h"
#include "MyClock.h"
#include "MyConfig.h"
#include "MyGDI.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
GameWorld gWorld;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MOVING_AGENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOVING_AGENT));

    MSG msg;
	bool msg_loop_cont = true;

	while (msg_loop_cont) {
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) { // PeekMessage will return false when there is no message
			if (msg.message == WM_QUIT) {
				msg_loop_cont = false;
				break; // GetMessage will return false when it retrieves WM_QUIT
			}
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		// we can do here something
		long delta = my_clock.delta_msec();
		if (delta > my_config.time_delta()) {
			gWorld.update(delta/1000.0);
			my_clock.update();
			InvalidateRect(msg.hwnd, nullptr, true);
		}
		else {
			Sleep(my_config.time_quantum());
		}
	}

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOVING_AGENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MOVING_AGENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC hdcmem;
	static HBITMAP old_bitmap;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		{
			hdcmem = CreateCompatibleDC(NULL);
			HDC hdc = GetDC(hWnd);
			RECT rect;
			GetClientRect(hWnd, &rect);
			HBITMAP hbitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
			old_bitmap = (HBITMAP)SelectObject(hdcmem, hbitmap);
			my_gdi.set_dc(hdcmem);
			ReleaseDC(hWnd, hdc);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			gWorld.set_target(x, y);
		}
		break;
	case WM_SIZE:
		{
			gWorld.set_width(LOWORD(lParam));
			gWorld.set_height(HIWORD(lParam));
			gWorld.create_detail();
		}
		break;
	case WM_KEYDOWN:
		{
			switch (wParam) {
				case VK_LEFT:
					{
						my_config.set_time_delta(my_config.time_delta() / 2);
						if (my_config.time_delta() == 0) my_config.set_time_delta(1);
					}
					break;
				case VK_RIGHT:
					{
						my_config.set_time_delta(my_config.time_delta() * 2);
					}
					break;
				case VK_UP:
					gWorld.set_panic_dist(gWorld.panic_dist()*2.0);
					break;
				case VK_DOWN:
					gWorld.set_panic_dist(gWorld.panic_dist()/2.0);
					break;
			}
		}
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			BitBlt(hdcmem, 0, 0, gWorld.width(), gWorld.height(), NULL, NULL, NULL, WHITENESS);
			gWorld.render();
			BitBlt(hdc, 0, 0, gWorld.width(), gWorld.height(), hdcmem, 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		old_bitmap = (HBITMAP)SelectObject(hdcmem, old_bitmap);
		DeleteObject(old_bitmap);
		DeleteDC(hdcmem);
        PostQuitMessage(0);
        break;
	case WM_ERASEBKGND:
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
