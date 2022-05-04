#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//---------------------------------------------------------------------
void func_PAINT(HWND hwnd) 
//---------------------------------------------------------------------
{

	PAINTSTRUCT ps;
	RECT rect;

	GetClientRect(hwnd, &rect);

	if (rect.bottom == 0) 
	{
		return;
	}

	HDC hdc = BeginPaint(hwnd, &ps);

	// 点
	for (int i=0; i < 2000; i++) 
	{

		int x = rand() % rect.right;
		int y = rand() % rect.bottom;
		SetPixel(hdc, x, y, RGB(255, 0, 0));
	}

	// 矩形
	Rectangle(hdc, 50, 50, 200, 150);  // 描画

	// ライン
	MoveToEx(hdc , 10 , 10 , NULL);
	LineTo(hdc , 110 , 20);
	LineTo(hdc , 130 , 110);

	// 色	赤
	{
		COLORREF col = RGB(255,0,0); 
		SetTextColor (hdc , col );
	}
	// 漢字
	{
		const char* str_mb = u8"utf-8の文字列";
	 	int len_wb = MultiByteToWideChar(CP_UTF8, 0, str_mb, strlen(str_mb), NULL, 0 );
		wchar_t	 str_wb[len_wb];
	 	MultiByteToWideChar(CP_UTF8, 0, str_mb, strlen(str_mb), str_wb, len_wb );
		SetBkMode(hdc,TRANSPARENT);	// 抜き
		TextOutW( hdc,10,100, str_wb, len_wb ); 
	}

	// 色	青
	{
		COLORREF col = RGB(0,0,255); 
		SetTextColor (hdc , col );
	}
	// フォント
	{
		const char* str_mb = u8"回転するよ";
		int	x1 = 180;
		int	y1 = 60;
		int height = 32;
		int width = 0;	// 0:デフォルト
		int	deg = 20;
		float rate_x = 0.5;	// 0.0:top	1.0:bottom	0.5:middle
		float rate_y = 0.5;	// 0.0:top	1.0:bottom	0.5:middle
		{
			// utf8をsjisに変換
		 	int len_wb = MultiByteToWideChar(CP_UTF8, 0, str_mb, strlen(str_mb), NULL, 0 );
			wchar_t	 str_wb[len_wb];
		 	MultiByteToWideChar(CP_UTF8, 0, str_mb, strlen(str_mb), str_wb, len_wb );
			//
			int	cEscapement = deg*10;
			int	cOrientation = 0;
			float rot = 3.141592*(deg)/180.0;
			SIZE size = {0,0}; 
			{
				HFONT hFont = CreateFont(
					height , width , cEscapement , cOrientation , FW_REGULAR , FALSE, FALSE , FALSE ,
					SHIFTJIS_CHARSET , OUT_DEFAULT_PRECIS ,
					CLIP_DEFAULT_PRECIS , DEFAULT_QUALITY , 
					VARIABLE_PITCH | FF_ROMAN , NULL
				);
				SelectObject(hdc , hFont);
				SetBkMode(hdc,TRANSPARENT);	// 抜き
				GetTextExtentPoint32W( hdc, str_wb, len_wb, &size );
				//
				int x = -size.cx*rate_x;
				int y = -size.cy*rate_y;
				int px = x1+(x*cos(-rot)-y*sin(-rot));
				int py = y1+(x*sin(-rot)+y*cos(-rot));
				//
				TextOutW( hdc,px,py, str_wb, len_wb ); 
				SelectObject(hdc , GetStockObject(SYSTEM_FONT));
				DeleteObject(hFont);

			}

		}

		// フォントセンター表示
		{
			int sz = 30;
			MoveToEx(hdc , x1 , y1-sz , NULL);	LineTo(hdc , x1 ,y1+sz);
			MoveToEx(hdc , x1-sz, y1 , NULL);	LineTo(hdc , x1+sz,y1);
		}
	}

	EndPaint(hwnd, &ps);
}


//---------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
//---------------------------------------------------------------------
{

	switch(msg) 
	{

		case WM_PAINT:
			func_PAINT(hwnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			if ( wParam == VK_ESCAPE ) 
			{
				PostQuitMessage( 0 );
			}
			break;

	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

//---------------------------------------------------------------------
main()
//---------------------------------------------------------------------
{
	HINSTANCE	hInstance	 = GetModuleHandle( NULL );


	MSG  msg;
	WNDCLASSW wc = {0};

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"GDI sample";
	wc.hInstance	 = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc   = WndProc;
	wc.hCursor	   = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"GDI sample",
				WS_OVERLAPPEDWINDOW | WS_VISIBLE,
				100, 100, 320, 240, NULL, NULL, hInstance, NULL);

	while (GetMessage(&msg, NULL, 0, 0)) {
	
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}