#include"stdafx.h"
#include"Function.h"


bool Register::isExist(HKEY hKey, CString lpSubKey, CString name) {
	int ret1 = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKey);

	if (ret1 != ERROR_SUCCESS){
		//throw "error";
		return false;
		//cout << "打开错误!";


	}
	else{

		if (name.IsEmpty()){
			RegCloseKey(hKey);
			return true;
		}

	}
	LPBYTE owner_Get = new BYTE[80];
	DWORD type_1 = REG_SZ;
	DWORD cbData_1 = 80;
	ret1 = RegQueryValueEx(hKey, name, NULL, &type_1, owner_Get, &cbData_1);

	if (ret1 != ERROR_SUCCESS){
		return false;
	}
	else{
		RegCloseKey(hKey);
		return true;
	}


}


void Register::addKey(HKEY hkey, CString item, CString name, CString value){
	bool b = isExist(hkey, item);
	if (!b){
		//createKey
		RegCreateKey(hkey, item, &hkey);
	}
	char strVal[MAX_REG_LENGTH];
	memcpy(strVal, value.GetBuffer(), value.GetLength() * 2);
	int ret2 = RegOpenKeyEx(hkey, item, 0, KEY_SET_VALUE, &hkey);
	if (ret2 != ERROR_SUCCESS)
		return;
	ret2 = RegSetValueEx(hkey, name, 0, REG_SZ, (BYTE*)strVal, value.GetLength() * 2);//注册键值
	RegCloseKey(hkey);
}



bool Register::delKey(HKEY hkey, CString item, CString name){
	if (name.IsEmpty()){
		bool b = isExist(hkey, item);
		if (b){
			RegDeleteKey(hkey, item);
			return true;
		}
		else{
			throw "not exist";
			return false;
		}
	}

	if (isExist(hkey, item, name) == true) {
		if (ERROR_SUCCESS == RegOpenKeyEx(hkey, item, 0, KEY_SET_VALUE, &hkey))
			// 删除 Test 子键下键值 TestRegSz
		if (ERROR_SUCCESS == RegDeleteValue(hkey, name))
		{
			RegCloseKey(hkey);
			return true;
		}
	}
	else{
		throw "not exist";
		return false;
	}

}

void Register::updateKey(HKEY hkey, CString item, CString name, CString value){
	bool b = isExist(hkey, item, name);
	if (b){
		char strVal[MAX_REG_LENGTH];
		memcpy(strVal, value.GetBuffer(), value.GetLength() * 2);
		int ret3 = RegOpenKeyEx(hkey, item, 0, KEY_SET_VALUE, &hkey);
		if (ret3 != ERROR_SUCCESS)
			return;
		ret3 = RegSetValueEx(hkey, name, 0, REG_SZ, (BYTE*)strVal, value.GetLength() * 2);//修改键值
		RegCloseKey(hkey);
	}
	else{
		throw "not exist";
	}
}