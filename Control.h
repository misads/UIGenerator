#pragma once
#include<atlstr.h>
#include<map>
#include<vector>

class AbstractControl{

public:


protected:
	CString m_name;




};

class Control:public AbstractControl{

public:
	Control();
	~Control();

protected:
	std::map<CString, CString> m_property;	//属性 值
	std::vector<CString> m_event;			//事件
};

class ControlBoxItem{

public:

private:
	AbstractControl m_abstrctControl;
	LPCTSTR m_icon;

};

class ButtonControl :public Control{

public:
	ButtonControl();

	~ButtonControl();



};