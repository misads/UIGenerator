#pragma once
#include<atlstr.h>

class Register{

public:


	void addKey(CString item,CString key, CString value);

	bool delKey(CString item, CString key);

	void updateKey(CString item, CString key, CString value);
	

};