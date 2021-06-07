#include "gjcLogon.h"
#include "utils.h"
#include "verify.h"
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <memory.h>
#include <winreg.h>
#include <tchar.h>



void get_logon_info_file(LPCWSTR fileName)
{	
	HANDLE hFind;
	WIN32_FIND_DATA fileInfo;
	WCHAR * fileNames;
	WCHAR * fileImagePath;
	wstring subPath;
	subPath = fileName;
	subPath = subPath.substr(0, subPath.length()-3);

	FILE * fp;
	fopen_s(&fp, "..\\..\\results\\logon_dir.txt", "a+");
	if (fp == NULL) printf("error open file!\n");

	hFind = FindFirstFile(fileName, &fileInfo);
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("open first file error!\n");
		printf("code:%ld", GetLastError());
		return;
	}


	while (FindNextFile(hFind, &fileInfo)) {
		if (!wcscmp(fileInfo.cFileName, L"..") || !wcscmp(fileInfo.cFileName, L".")) continue;
		if (!wcscmp(fileInfo.cFileName, L"desktop.ini")) continue;
		wstring verifyInfo;
		subPath.append(fileInfo.cFileName);
		VerifyEmbeddedSignature(subPath.c_str(), &verifyInfo);
		printf("  NAME:%ws\n", fileInfo.cFileName);
		printf("  INCLUDE PATH:%ws\n", fileInfo.cFileName);
		printf("  SIGN AND VERIFY:  %ws\n\n", verifyInfo.c_str());

		//写入文件 
		wstring bufMessage;
		wstring nameWS = fileInfo.cFileName;
		wstring pathWS = fileInfo.cFileName;
		wstring verifyWS = verifyInfo.c_str();
		bufMessage += wstring(L"\"");
		bufMessage += nameWS;
		bufMessage += wstring(L"\"");
		bufMessage += wstring(L"\t");
		bufMessage += wstring(L"\"");
		bufMessage += pathWS;
		bufMessage += wstring(L"\"");
		bufMessage += wstring(L"\t");
		bufMessage += wstring(L"\"");
		bufMessage += verifyWS;
		bufMessage += wstring(L"\"");
		bufMessage += wstring(L"\n");
		wcout << bufMessage;

		fprintf_s(fp, "%ws", bufMessage.c_str());
	}

	fclose(fp);
}


void get_logon_info_reg(HKEY rootKey, LPCWSTR subKey, unsigned short mask) {
	HKEY hKey;
	LPTSTR * subkeys;
	LPBYTE * subKey_values;

	FILE * fp;
	fopen_s(&fp, "..\\..\\results\\logon_reg.txt", "a+");
	if (fp == NULL) printf("error open file!\n");

	//1. 打开rootkey下的subkey句柄
	int ret = RegOpenKeyEx(rootKey, subKey, 0, KEY_ALL_ACCESS | mask, &hKey);
	if (ret != ERROR_SUCCESS) {
		printf("  open key error!!\n");
		printf("  error code:%ld\n", GetLastError());
		printf("  seems like you don't have this key!\n\n");
		fclose(fp);
		return;
	}

	    //2. 阅读该子键下的所有键值对
	
	    //2.1 初始化
	    DWORD dwSubKeyCnt;          // 子键的数量  
	    DWORD dwSubKeyNameMaxLen;   // 子键名称的最大长度(不包含结尾的null字符)  
	    DWORD dwKeyValueCnt;        // 键值项的数量  
	    DWORD dwKeyValueNameMaxLen; // 键值项名称的最大长度(不包含结尾的null字符)  
	    DWORD dwKeyValueDataMaxLen; // 键值项数据的最大长度(in bytes)  
	    ret = RegQueryInfoKey(
	        hKey, 
	        NULL,
	        NULL,
	        NULL,
	        &dwSubKeyCnt,
	        &dwSubKeyNameMaxLen,
	        NULL,
	        &dwKeyValueCnt,
	        &dwKeyValueNameMaxLen,
	        &dwKeyValueDataMaxLen,
	        NULL,
	        NULL
	        );
	    if (ret != ERROR_SUCCESS) {
	        printf("query key info error!!\n ");
	        return;
	    }
	    // printf("dwKeyValue count:%I64d\n", dwKeyValueNameMaxLen);
	
	    //2.2 遍历读取键值对
	    dwKeyValueNameMaxLen ++; //为了包括结尾的NULL
	    dwKeyValueDataMaxLen ++;
	    subkeys = (LPTSTR *) malloc(dwKeyValueCnt * sizeof(LPTSTR));
	    memset(subkeys, 0, dwKeyValueCnt * sizeof(LPTSTR));
	    subKey_values = (LPBYTE *) malloc(dwKeyValueDataMaxLen * sizeof(LPBYTE));
	    memset(subKey_values, 0, dwKeyValueDataMaxLen * sizeof(LPBYTE));
	
	    for (unsigned int i=0; i<dwKeyValueCnt; i++){
	        DWORD tmp_max_name = dwKeyValueNameMaxLen;
	        DWORD tmp_max_value = dwKeyValueDataMaxLen;
	        subkeys[i] = (LPTSTR) malloc((dwKeyValueNameMaxLen)*sizeof(TCHAR));
	        subKey_values[i] = (LPBYTE) malloc((dwKeyValueDataMaxLen)*sizeof(BYTE));
	        memset(subkeys[i], 0, (dwKeyValueNameMaxLen)*sizeof(TCHAR));
	        memset(subKey_values[i], 0, (dwKeyValueDataMaxLen)*sizeof(BYTE));
	
	        ret = RegEnumValue(
	            hKey,
	            i,
	            subkeys[i],
	            &tmp_max_name,
	            NULL,
	            NULL,
	            subKey_values[i],
	            &tmp_max_value
	        );
	        if (ret != ERROR_SUCCESS) {
	            printf("error when enum Value!!\n");
	            printf("len:%ld\n", dwSubKeyNameMaxLen);
	        }
			wstring signInfo;
			printf("  NAME:%ws\n", subkeys[i]);
			printf("  INCLUDE PATH: %ws\n",get_path_in_quotation(subKey_values[i]).c_str());
			VerifyEmbeddedSignature(get_path_in_quotation(subKey_values[i]).c_str(), &signInfo);
			printf("  SIGN AND VERIFY:%ws\n\n", signInfo.c_str());

			//写入文件 
			wstring bufMessage;
			wstring nameWS = subkeys[i];
			wstring pathWS = get_path_end_with_exe(subKey_values[i]).c_str();
			wstring verifyWS = signInfo.c_str();
			bufMessage += wstring(L"\"");
			bufMessage += nameWS;
			bufMessage += wstring(L"\"");
			bufMessage += wstring(L"\t");
			bufMessage += wstring(L"\"");
			bufMessage += pathWS;
			bufMessage += wstring(L"\"");
			bufMessage += wstring(L"\t");
			bufMessage += wstring(L"\"");
			bufMessage += verifyWS;
			bufMessage += wstring(L"\"");
			bufMessage += wstring(L"\n");
			wcout << bufMessage;

			fprintf_s(fp, "%ws", bufMessage.c_str());
			
	    }
	
	    //释放内存，关闭句柄,todo
		fclose(fp);
	    RegCloseKey(hKey);
	}
