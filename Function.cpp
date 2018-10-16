#include"stdafx.h"
#include"Function.h"


bool Register::isExist(HKEY hKey, CString lpSubKey, CString name) {
	int ret1 = RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKey);

	if (ret1 != ERROR_SUCCESS){
		//RegCloseKey(hKey);
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

	HKEY initial = hkey;
	bool b = isExist(hkey, item);
	if (!b){
		//createKey
		RegCreateKey(hkey, item, &hkey);
		hkey=initial;
	}
	if (name.IsEmpty())return;

	char strVal[MAX_REG_LENGTH];
	memcpy(strVal, value.GetBuffer(), value.GetLength() * 2);
	int ret2 = RegOpenKeyEx(hkey, item, 0, KEY_SET_VALUE, &hkey);
	if (ret2 != ERROR_SUCCESS)
		return;
	if (name == TEXT("@")){
		ret2 = RegSetValueEx(hkey, L"", 0, REG_SZ, (BYTE*)strVal, value.GetLength() * 2);//注册键值
	}
	else{
		ret2 = RegSetValueEx(hkey, name, 0, REG_SZ, (BYTE*)strVal, value.GetLength() * 2);//注册键值
	}
	
	RegCloseKey(hkey);
}

bool Register::delKey(HKEY hkey, CString item, CString name){
	if (name.IsEmpty()){
		bool b = isExist(hkey, item);
		if (b){
			SHDeleteKey(hkey, item);
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

CString Register::readKey(HKEY hkey, CString item, CString key){
	if (key == L"@")key = L"";
 	if (isExist(hkey, item, key)){
		TCHAR ch[40]=L"";
		LPBYTE owner_Get = new BYTE[80];
		DWORD type_1 = REG_SZ;
		DWORD cbData_1 = 80;
		int ret1 = RegOpenKeyEx(hkey, item, 0, KEY_READ, &hkey);
		int ret = RegQueryValueEx(hkey, key, NULL, &type_1, owner_Get, &cbData_1);
		if (ret != ERROR_SUCCESS){
			throw "no DATA";
			RegCloseKey(hkey);
			return L"";
		}
		memcpy(ch, owner_Get, 80);
		RegCloseKey(hkey);

		CString  str;
		str.Format(_T("%s"), ch);
		return str;
	}
	else{
		throw "not exist";
		return L"";
	}
}

FileRelation::FileRelation(){
}

FileRelation::~FileRelation(){
}


void FileRelation::setRelation(CString extension, CString filepath){
	Register reg;
	
	int dotpos = filepath.ReverseFind(L'.');
	int pos = filepath.ReverseFind(L'\\');
	CString name=filepath.Mid(pos + 1, dotpos - pos - 1);
	CString path =  name + TEXT("\\shell\\open\\command");
	CString iconpath = name + TEXT("\\DefaultIcon");
	//name.MakeUpper();
	//MessageBox(0, name, L"", 0);

	reg.addKey(HKEY_CLASSES_ROOT, extension, L"@", name);
	reg.addKey(HKEY_CLASSES_ROOT, path, L'@', TEXT("\"") + filepath + TEXT("\" %1"));
	reg.addKey(HKEY_CLASSES_ROOT, iconpath, L"@", TEXT("\"") + filepath + TEXT("\" ,0"));
}

#define DoNothing ;
#define JustDeleteFilePathRelation DoNothing

//若filepath为空，删除所有文件关联，否则只删除filepath的文件关联
void FileRelation::cancelRelation(CString extension, CString filepath){
	Register reg;	
	if (filepath.IsEmpty()){
		CString path = reg.readKey(HKEY_CLASSES_ROOT, extension, L"@");
		reg.delKey(HKEY_CLASSES_ROOT, extension);
		reg.delKey(HKEY_CLASSES_ROOT, path);

	}else{
		JustDeleteFilePathRelation
	}

}


#ifdef _DEBUG


void MsgBox(CString text){

	MessageBox(0, text, L"DebugInfo", 0);
}
#else

void MsgBox(CString text){
}

#endif