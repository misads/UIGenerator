#include "stdafx.h"
#include "GDI.h"


#pragma comment(lib,"Msimg32.lib")


CGDI::CGDI(){
	m_hdc = NULL;
	m_hRenderBuffer = NULL;
	m_hBitmap = NULL;

	m_hFont = CreateFont(30, 0, 0, 0, 400, FALSE, FALSE, 0,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN, L"Î¢ÈíÑÅºÚ");
}

CGDI::~CGDI(){
	if (m_hdc) DeleteObject(m_hdc);
	if (m_hRenderBuffer) DeleteObject(m_hRenderBuffer);
	if (m_hBitmap) DeleteObject(m_hBitmap);
}


bool CGDI::DrawLine(HDC hdc, int a_x, int a_y, int b_x, int b_y,
	int thickness, DWORD color){

	HPEN hPen;
	hPen = CreatePen(PS_SOLID, thickness, color);
	SelectObject(hdc, hPen);
	MoveToEx(hdc, a_x, a_y, 0);
	LineTo(hdc, b_x, b_y);
	DeleteObject(hPen);
	return true;
}


bool CGDI::DrawLineEx(HDC hdc, int a_x, int a_y, int b_x, int b_y,
	LineStyle lineStyle, int thickness, DWORD color){

	HPEN hPen;
	hPen = CreatePen(lineStyle, thickness, color);
	SelectObject(hdc, hPen);
	MoveToEx(hdc, a_x, a_y, 0);
	LineTo(hdc, b_x, b_y);
	DeleteObject(hPen);
	return true;
}

bool CGDI::DrawRectangle(HDC hdc, int a_x, int a_y, int b_x, int b_y,
	int thickness, DWORD color){

	HPEN hPen;
	hPen = CreatePen(PS_SOLID, thickness, color);
	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, a_x, a_y, b_x, b_y);
	DeleteObject(hPen);
	return true;
}

bool CGDI::DrawRectangleEx(HDC hdc, int a_x, int a_y, int b_x, int b_y,
	LineStyle lineStyle, int thickness, DWORD color){

	HPEN hPen;
	hPen = CreatePen(lineStyle, thickness, color);
	SelectObject(hdc, hPen);
	Rectangle(hdc, a_x, a_y, b_x, b_y);
	DeleteObject(hPen);
	return true;
}

bool CGDI::DrawSolidRectangle(HDC hdc, int a_x, int a_y, int b_x, int b_y,
	DWORD color){

	HBRUSH hBrush;
	hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, a_x, a_y, b_x, b_y);
	DeleteObject(hBrush);
	return true;
}

bool CGDI::DrawSolidRectangle(HDC hdc, Line _line,
	DWORD color){
	return DrawSolidRectangle(hdc, _line.a.x, _line.a.y, _line.b.x, _line.b.y);
}

bool CGDI::DrawSolidRectangleEx(HDC hdc, int a_x, int a_y, int b_x, int b_y,
	DWORD color, int nBorderWidth, DWORD dwBorderColor){
	DrawRectangle(hdc, a_x, a_y, b_x, b_y, nBorderWidth, dwBorderColor);
	DrawSolidRectangle(hdc, a_x, a_y, b_x, b_y, color);
	return true;
}

bool CGDI::DrawTextB(HDC hdc, int a_x, int a_y, int b_x, int b_y,
	LPCTSTR text, bool isCenter, bool isTransparent){
	RECT rt;
	UINT uFormat = DT_SINGLELINE;
	rt.left = a_x;
	rt.top = a_y;
	rt.right = b_x;
	rt.bottom = b_y;
	if (isCenter)
		uFormat |= DT_CENTER;
	if (isTransparent)SetBkMode(hdc, TRANSPARENT);


	SelectObject(hdc, m_hFont);

	DrawText(hdc, text, -1, &rt, uFormat);

	//SAFE_DELETE(font1);
	return true;
}

bool CGDI::DrawTextB(HDC hdc, Point _p1, Point _p2,
	LPCTSTR text, bool isCenter, bool isTransparent){
	return DrawTextB(hdc, _p1.x, _p1.y, _p2.x, _p2.y, text, isCenter, isTransparent);
}



bool CGDI::DrawBmp(HDC hdc, LPCTSTR pFileName, int _x, int _y, int _width, int _height,
	int src_x, int src_y){

	HDC Hdc;
	HBITMAP hBitmap;
	Hdc = CreateCompatibleDC(hdc);
	hBitmap = LoadImageFile(pFileName);
	SelectObject(Hdc, hBitmap);
	BitBlt(hdc, _x, _y, _width, _height, Hdc, src_x, src_y, SRCCOPY);
	DeleteObject(hBitmap);
	DeleteObject(Hdc);
	return true;
}

bool CGDI::DrawBmp(HDC hdc, HBITMAP hBitmap, int _x, int _y, int _width, int _height,
	int src_x, int src_y){

	HDC Hdc;
	Hdc = CreateCompatibleDC(hdc);
	SelectObject(Hdc, hBitmap);
	BitBlt(hdc, _x, _y, _width, _height, Hdc, src_x, src_y, SRCCOPY);
	//DeleteObject(hBitmap);
	DeleteObject(Hdc);
	return true;


}

bool CGDI::DrawBmp(HDC hdc, HINSTANCE hInst, int resId, int _x, int _y, int _width, int _height,
	int src_x, int src_y){
	HBITMAP hBitmap = LoadImageRes(hInst, resId);
	DrawBmp(hdc, hBitmap, _x, _y, _width, _height,
		src_x, src_y);
	DeleteObject(hBitmap);

	return true;
}

bool CGDI::DrawTransparentBmp(HDC hdc, LPCTSTR filePath, int _x, int _y, int _width, int _height,
	int src_x, int src_y, DWORD transparentColor){

	HDC Hdc;
	HBITMAP hBitmap;
	Hdc = CreateCompatibleDC(hdc);
	hBitmap = LoadImageFile(filePath);
	SelectObject(Hdc, hBitmap);
	//BitBlt(hdc,_x,_y,_width,_height,Hdc,nSrcX,nSrcY,SRCCOPY);
	TransparentBlt(hdc, _x, _y, _width, _height, Hdc, src_x, src_y, _width, _height, transparentColor);
	DeleteObject(hBitmap);
	DeleteObject(Hdc);
	return true;
}

bool CGDI::DrawTransparentBmp(HDC hdc, HBITMAP hBitmap, int _x, int _y, int _width, int _height,
	int src_x, int src_y, DWORD transparentColor){

	HDC Hdc;
	Hdc = CreateCompatibleDC(hdc);
	SelectObject(Hdc, hBitmap);
	//BitBlt(hdc,_x,_y,_width,_height,Hdc,nSrcX,nSrcY,SRCCOPY);
	TransparentBlt(hdc, _x, _y, _width, _height, Hdc, src_x, src_y, _width, _height, transparentColor);
	//DeleteObject(hBitmap);
	DeleteObject(Hdc);
	return true;
}

bool CGDI::DrawTransparentBmp(HDC hdc, HINSTANCE hInst, int resId, int _x, int _y, int _width, int _height,
	int src_x, int src_y, DWORD transparentColor){
	HBITMAP hBitmap = LoadImageRes(hInst, resId);
	DrawTransparentBmp(hdc, hBitmap, _x, _y, _width, _height,
		src_x, src_y, transparentColor);
	DeleteObject(hBitmap);
	return true;

}
bool CGDI::CreateRenderBuffer(HDC hdc, int _width, int _height){
	m_pResolution = Point(_width, _height);
	if (m_hdc) DeleteObject(m_hdc);
	if (m_hRenderBuffer) DeleteObject(m_hRenderBuffer);
	m_hdc = CreateCompatibleDC(NULL);
	m_hRenderBuffer = CreateCompatibleBitmap(hdc, _width, _height);
	SelectObject(m_hdc, m_hRenderBuffer);
	return true;
}

HDC CGDI::GetTempHdc(){
	return m_hdc;
}

bool	CGDI::RenderToScreen(HDC hdc){
	return (BitBlt(hdc, 0, 0, m_pResolution.x, m_pResolution.y, m_hdc, 0, 0, SRCCOPY) != 0);
}


HBITMAP CGDI::LoadImageFile(LPCTSTR filePath){
	//¼ÓÔØbmpÎÄ¼þ
	SAFE_DELETE(m_hBitmap);
	m_hBitmap = (HBITMAP)LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	return m_hBitmap;
}

HBITMAP	CGDI::LoadImageRes(HINSTANCE hInst, int id){
	SAFE_DELETE(m_hBitmap);
	m_hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(id));
	return m_hBitmap;
}

void	CGDI::SetFont(LPCTSTR fontName, int height, int width, int weight,
	DWORD italic, DWORD underline){

	SAFE_DELETE(m_hFont);
	m_hFont = CreateFont(height, width, 0, 0, weight, italic, underline, 0,
		GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_MODERN, fontName);
}
