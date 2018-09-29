#pragma once
#include<atlstr.h>
#include<string>

#define MAX_REG_LENGTH 256

class Register{

public:

	//HKEY_CLASSES_ROOT
	//HKEY_CURRENT_USER
	//HKEY_LOCAL_MACHINE
	//�������� ��� ������ �޸�
	void addKey(HKEY hkey, CString item, CString key, CString value);

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
	//lpSubKeyû��ǰ�õ�б��
	bool isExist(HKEY hKey, CString lpSubKey, CString name = L"");

};

