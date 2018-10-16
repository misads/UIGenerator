#pragma once


#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768


#define WORKSPACE_X 180
#define WORKSPACE_Y 30
#define WORKSPACE_WIDTH 640
#define WORKSPACE_HEIGHT 640
#define SCALING 1





class Application{

public:
	Application();
	~Application();

	void init();

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	

private:

	void onPaint(HDC hdc);



};