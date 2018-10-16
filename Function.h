#pragma once
#include<atlstr.h>
#include<string>

#define MAX_REG_LENGTH 256

class Register{

public:

	//HKEY_CLASSES_ROOT
	//HKEY_CURRENT_USER
	//HKEY_LOCAL_MACHINE
	//若不存在 添加 若存在 修改
	void addKey(HKEY hkey, CString item, CString key =L"", CString value=L"");

	//HKEY_CLASSES_ROOT
	//HKEY_CURRENT_USER
	//HKEY_LOCAL_MACHINE
	bool delKey(HKEY hkey, CString item, CString key = L"");

	//HKEY_CLASSES_ROOT
	//HKEY_CURRENT_USER
	//HKEY_LOCAL_MACHINE
	void updateKey(HKEY hkey, CString item, CString key, CString value);

	//HKEY_CLASSES_ROOT
	//HKEY_CURRENT_USER
	//HKEY_LOCAL_MACHINE
	//若key空 返回默认 若不存在 返回空
	CString readKey(HKEY hkey, CString item, CString key = L"");

	//HKEY_CLASSES_ROOT
	//HKEY_CURRENT_USER
	//HKEY_LOCAL_MACHINE
	//lpSubKey没有前置的斜杠
	bool isExist(HKEY hKey, CString lpSubKey, CString name = L"");

};

class FileRelation{

public:
	FileRelation();
	~FileRelation();

	//例:setRelation(L".txt",L"c:\\windows\\notepad.exe");
	void setRelation(CString extension,CString filepath);
	
	//取消文件关联
	void cancelRelation(CString extension, CString filepath=TEXT(""));

private:
	Register m_reg;
	
};

//#ifdef _DEBUG
	void MsgBox(CString text);
//#endif