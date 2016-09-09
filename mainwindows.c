#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/wglew.h>
#include "texture.h"
#include "global.h"
#include "shader.h"
#include "winfont.h"
#include "geometry.h"
#define WINDOWSTYLE (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX)
// #define WIDTH 800
// #define HEIGHT 600
static int SX = 40;
static int SY = 40;

int width;
int height;
Texture * texture1 = NULL;
Texture * texture2 = NULL;
static int FRAME = 30;
DWORD nTime = 0;
static DWORD timePreFrame; 

HFONT hFont;
LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lPARAM); 
HINSTANCE g_hInstance = 0;
BOOL RegisterWnd(LPCSTR lpszClassName, WNDPROC wndProc);
HWND CreateWnd(LPCSTR lpszClassName, LPCSTR lpszWindowsName);
int Message(HWND hWnd);
void DisplayWnd(HWND hWnd);
void init_window(HWND hWnd);
static void set_pixel_format_to_hdc(HDC hDC);

void Display();

static void set_pixel_format_to_hdc(HDC hDC) {
	int color_deep;
	PIXELFORMATDESCRIPTOR pfd;
	color_deep = GetDeviceCaps(hDC, BITSPIXEL);
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = color_deep;
	pfd.cDepthBits = 0;
	pfd.cStencilBits = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);
}

void init_window(HWND hWnd) {
	HDC hDC = GetDC(hWnd);
	set_pixel_format_to_hdc(hDC);
	HGLRC glrc = wglCreateContext(hDC);
	if(glrc == 0) {
		exit(1);
	}
	wglMakeCurrent(hDC, glrc);
	if(glewInit() != GLEW_OK) {
		exit(1);
	}
	glViewport(0,0,width, height);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ZERO);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	//FontCreate(48, ANSI_CHARSET, "Consolas", hDc);
	ReleaseDC(hWnd, hDC);
}

void Display() {
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawTexture(texture2, 1.0);
	DrawTexture(texture1, 1.0);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0);
	DrawQuad(50,50,500,500);
}
LRESULT CALLBACK WndProc(HWND hWnd, 
						UINT nMsg, 
						WPARAM wParam, 
						LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	switch(nMsg) {
		case WM_CREATE:
			init_window(hWnd);
		break;
		case WM_QUIT:
			PostQuitMessage(0);
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
		case WM_PAINT:
		/*if (GetUpdateRect(hWnd, NULL, FALSE)) {
			printf("hello world\n");
			HDC hDC = GetDC(hWnd);
			Display();
			SwapBuffers(hDC);
			ReleaseDC(hWnd, hDC);
		}*/
			/*printf("hello world\n");
			Display();
			SwapBuffers(GetDC(hWnd));
			hdc = BeginPaint(hWnd, &ps);
			FontCreate(48, ANSI_CHARSET, "Comic Sans MS", hdc);
			Display();
			SwapBuffers(hdc);
			TextOut(hdc, 10, 10, "hello world", 11);
			EndPaint(hWnd, &ps);*/
		break;
		default:
		break;
	}
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

BOOL RegisterWnd(LPCSTR lpszClassName, WNDPROC wndProc) {
	WNDCLASSEX wcx = { 0 };
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hIcon = NULL;
	wcx.hIconSm = NULL;
	wcx.hInstance = g_hInstance;
	wcx.lpfnWndProc = wndProc;
	wcx.lpszClassName = lpszClassName;
	wcx.lpszMenuName = NULL;
	ATOM nAtom = RegisterClassEx(&wcx);
	if(0 == nAtom) {
		return FALSE;
	}
	return TRUE;
}

HWND CreateWnd(LPCSTR lpszClassName, LPCSTR lpszWindowsName) {
	// HWND hWnd = CreateWindowEx(
	// 		WS_EX_CLIENTEDGE,
	// 		lpszClassName,
	// 		lpszWindowsName,
	// 		WS_POPUP,
	// 		SX,SY,width,height,
	// 		NULL,NULL,g_hInstance, NULL
	// 	);
	// return hWnd;
	HWND hWnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			lpszClassName,
			lpszWindowsName,
			WINDOWSTYLE,
			CW_USEDEFAULT,CW_USEDEFAULT,width,height,
			NULL,NULL,g_hInstance, NULL
		);
	return hWnd;
}

void DisplayWnd(HWND hWnd) {
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
}

int Message(HWND hWnd) {
	MSG nMsg = { 0 };
	while(TRUE) {
		if(PeekMessage(&nMsg, NULL, 0, 0, PM_REMOVE)) {
			if(nMsg.message == WM_QUIT) { break;}
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg);
		} else {
			DWORD time = GetTickCount();
			if((time - nTime) > timePreFrame) {
				nTime = time;
				HDC hDC = GetDC(hWnd);
				Display();
				SwapBuffers(hDC);
				ReleaseDC(hWnd, hDC);
			} else {
				Sleep(0);
			}
		}
	}
	/*while(GetMessage(&nMsg, NULL, 0, 0)) {
		TranslateMessage(&nMsg);
		DispatchMessage(&nMsg);
	}*/
	return (int)nMsg.wParam;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWH(800,600);
	width = GetScreenWidth();
	height = GetScreenHeight();
	timePreFrame = 1000/FRAME;
	if(!RegisterWnd(TEXT("WinWnd"), WndProc)) {
		MessageBox(NULL, TEXT("register fail"),TEXT("Warning"), MB_YESNOCANCEL);
		return 0;
	}
	g_hInstance = hInstance;
	HWND hWnd = CreateWnd(TEXT("WinWnd"), TEXT("main win"));
	texture1 = BindTexture("bg_day.png",0,0,288,512,80,80,368,592);
	texture2 = BindTexture("test2.png",0,0,200,200,0,0,200,200);
	//InitFont();
	DisplayWnd(hWnd);
	Message(hWnd);
	return 0;
} 