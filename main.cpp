#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>
#include <iostream>
#include <clocale>
#include <cstdlib>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawPixels(HWND hwnd);

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//    PWSTR lpCmdLine, int nCmdShow) {
//---------------------------------------------------------------------
main()
//---------------------------------------------------------------------
{
		HINSTANCE	hInstance	 = GetModuleHandle( NULL );
	printf("MB_CUR_MAX %d\n", MB_CUR_MAX );

const char* str_multibyte1="マルチバイト文字";
const char* str_multibyte2=u8"マルチバイト文字";



    MSG  msg;
    WNDCLASSW wc = {0};

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Pixels";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Pixels",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                100, 100, 300, 250, NULL, NULL, hInstance, NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {
    
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    srand(time(NULL));

//    return (int) msg.wParam;
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    switch(msg) {

        case WM_PAINT:

            DrawPixels(hwnd);
            break;

        case WM_DESTROY:

            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void DrawPixels(HWND hwnd) {

    PAINTSTRUCT ps;
    RECT r;

    GetClientRect(hwnd, &r);

    if (r.bottom == 0) {
    
        return;
    }

    HDC hdc = BeginPaint(hwnd, &ps);

	// 点
    for (int i=0; i<1000; i++) {

        int x = rand() % r.right;
        int y = rand() % r.bottom;
        SetPixel(hdc, x, y, RGB(255, 0, 0));
    }

	// 矩形
	Rectangle(hdc, 50, 50, 200, 150);  // 描画

	// ライン
	MoveToEx(hdc , 10 , 10 , NULL);
	LineTo(hdc , 110 , 20);
	LineTo(hdc , 130 , 110);

	// 漢字
	{
		const char* str_mb = u8"utf-8の文字列";
		wchar_t	 str_wide[256];
	 	int len = MultiByteToWideChar(CP_UTF8, 0, str_mb, strlen(str_mb), NULL, 0 );
	 	int ___ = MultiByteToWideChar(CP_UTF8, 0, str_mb, strlen(str_mb), str_wide, len );
		TextOutW( hdc,10,100, str_wide, len ); 
	}

    EndPaint(hwnd, &ps);
}