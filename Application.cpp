#include"stdafx.h"
#include "Application.h"
#include "GDI.h"

Application::Application(){

}

Application::~Application(){

}


void Application::init(){



}

LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){

	int wmId;
	HDC hdc;

	PAINTSTRUCT ps;
	switch (message){
	case WM_COMMAND:
		break;
		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  在此添加任意绘图代码...
		onPaint(hdc);
		EndPaint(hWnd, &ps);
		break;

		break;
	default:
		break;
	}



	return 0;
}


void Application::onPaint(HDC hdc){
	CGDI GDI;

	

	GDI.DrawSolidRectangleEx(hdc, 0, 0, WINDOW_WIDTH*2, WINDOW_HEIGHT*2, RGB(240, 240, 240), 0, RGB(240, 240, 240));
	GDI.DrawSolidRectangleEx(hdc, WORKSPACE_X, WORKSPACE_Y, WORKSPACE_X + WORKSPACE_WIDTH, WORKSPACE_Y + WORKSPACE_HEIGHT,
		RGB(255, 255, 255),0,0);


}
