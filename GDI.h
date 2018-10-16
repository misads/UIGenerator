////////////////////////////////////
//								  //	
//		CGDI 图形库				  //
//		版本号:20180921			  //
//		email:523131316@qq.com	  //
//								  //
////////////////////////////////////

#include <windows.h>
#include "Arith.h"

#ifndef _H_RENDER_H
#define _H_RENDER_H
#pragma once




#define WHITE	RGB(255,255,255)
#define BLACK	RGB(0,0,0)
#define RED		RGB(255,0,0)
#define	GREEN	RGB(0,255,0)
#define	BLUE	RGB(0,0,255)
#define	CYAN	RGB(0,255,255)
#define	MAGENTA	RGB(255,0,255)
#define	YELLOW	RGB(255,255,0)

#define SAFE_DELETE(i) if(i!=NULL)DeleteObject(i);

/*
solid		__________
dash		_ _ __ _ _
dot			..........
dashdot		_._._._._.
dashdotdot	_.._.._.._
*/
enum LineStyle{ SOLID, DASH, DOT, DASHDOT, DASHDOTDOT };



class CGDI{
public:
	CGDI(void);
	~CGDI(void);

	//画一条直线
	bool DrawLine(HDC hdc, int a_x, int a_y, int b_x, int b_y,
		int thickness = 1, DWORD color = 0);

	//带样式直线
	bool DrawLineEx(HDC hdc, int a_x, int a_y, int b_x, int b_y,
		LineStyle lineStyle, int thickness = 1, DWORD color = 0);

	bool DrawRectangle(HDC hdc, int a_x, int a_y, int b_x, int b_y,
		int thickness = 1, DWORD color = 0);

	bool DrawRectangleEx(HDC hdc, int a_x, int a_y, int b_x, int b_y,
		LineStyle lineStyle, int thickness = 1, DWORD color = 0);

	//画实心矩形
	bool DrawSolidRectangle(HDC hdc, int a_x, int a_y, int b_x, int b_y,
		DWORD color = 0);

	bool DrawSolidRectangle(HDC hdc, Line _line,
		DWORD color = 0);

	bool DrawSolidRectangleEx(HDC hdc, int a_x, int a_y, int b_x, int b_y,
		DWORD color, int thickness, DWORD borderColor);

	//绘制文本
	bool DrawTextB(HDC hdc, int a_x, int a_y, int b_x, int b_y,
		LPCTSTR text, bool isCenter = false, bool isTransparent = true);

	bool DrawTextB(HDC hdc, Point _p1, Point _p2,
		LPCTSTR text, bool isCenter = false, bool isTransparent = true);

	bool DrawBmp(HDC hdc, LPCTSTR filePath, int _x, int _y, int _width, int _height,
		int src_x = 0, int src_y = 0);

	bool DrawBmp(HDC hdc, HBITMAP hBitmap, int _x, int _y, int _width, int _height,
		int src_x = 0, int src_y = 0);

	bool DrawBmp(HDC hdc, HINSTANCE hInst, int resId, int _x, int _y, int _width, int _height,
		int src_x = 0, int src_y = 0);

	//默认白色透明色
	bool DrawTransparentBmp(HDC hdc, LPCTSTR filePath, int _x, int _y, int _width, int _height,
		int src_x = 0, int src_y = 0, DWORD transparentColor = WHITE);

	//默认白色透明色
	bool DrawTransparentBmp(HDC hdc, HBITMAP hBitmap, int _x, int _y, int _width, int _height,
		int src_x = 0, int src_y = 0, DWORD transparentColor = WHITE);

	//默认白色透明色
	bool DrawTransparentBmp(HDC hdc, HINSTANCE hInst, int resId, int _x, int _y, int _width, int _height,
		int src_x = 0, int src_y = 0, DWORD transparentColor = WHITE);

	//创建一个图片内存缓存,
	bool CreateRenderBuffer(HDC hdc, int _width, int _height);

	//获取临时HDC,可以在临时HDC上画图
	HDC GetTempHdc();

	//更新屏幕，把内存缓存画到屏幕上
	bool	RenderToScreen(HDC hdc);

	HBITMAP		LoadImageFile(LPCTSTR filePath);

	HBITMAP		LoadImageRes(HINSTANCE hInst, int id);

	//width 0  weight 400正常 700加粗
	void		SetFont(LPCTSTR fontName, int height, int width, int weight,
		DWORD italic = FALSE, DWORD underline = FALSE);

private:


	HDC				m_hdc;						//临时HDC
	HBITMAP			m_hRenderBuffer;			//renderBuffer

	HBITMAP			m_hBitmap;					//图片
	HFONT			m_hFont;					//字体

	Point			m_pResolution;				//分辨率
};


#else




#endif

