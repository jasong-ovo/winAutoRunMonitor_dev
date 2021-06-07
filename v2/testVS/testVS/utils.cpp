#include "utils.h"


wstring get_path_in_quotation(LPBYTE pPath) {
	wstring path;
	path = (TCHAR *)pPath;
	wstring modified_path;
	int start_point, end_point;
	start_point = path.find(L'\"', 0) + 1;
	end_point = path.find(L'\"', start_point);
	modified_path = path.substr(start_point, end_point - start_point );
	return modified_path;
}

wstring get_path_end_with_exe(LPBYTE pPath) {
	wstring path;
	path = (TCHAR *)pPath;
	wstring modified_path;
	int start_point, end_point;
	if (path.find(L'\"') != path.npos) start_point = 1;
	else start_point = 0;
	end_point = path.find(L"exe");
	modified_path = path.substr(start_point, end_point + 3 - start_point);
	return modified_path;
}

wstring get_path_end_with_sys(LPBYTE pPath) {
	wstring path;
	path = (TCHAR *)pPath;
	wstring modified_path;
	if (path.find(L"exe") != path.npos) return get_path_end_with_exe(pPath);
	modified_path = path;
	return modified_path;
}


wstring string2wstring(string str)
{
	wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}



//将wstring转换成string  
string wstring2string(wstring wstr)
{
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

