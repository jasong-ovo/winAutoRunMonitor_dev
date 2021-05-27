#include "gjcService.h"
#include "verify.h"
#include "utils.h"

//检查服务的start
bool check_autorun_service(HKEY parent, LPTSTR subkey, LPBYTE imagePath) {
	HKEY hKey;
	int ret = RegOpenKeyEx(parent, subkey, 0, STANDARD_RIGHTS_READ | KEY_QUERY_VALUE, &hKey);
	if (ret != ERROR_SUCCESS) {
		printf("error code %ld", GetLastError());
		printf("open key error when check autorun service !!\n");
		return false;
	}

	//得到名字的数量限制
	DWORD dwKeyValueCnt;        // 键值项的数量  
	DWORD dwKeyValueNameMaxLen; // 键值项名称的最大长度(不包含结尾的null字符)  
	DWORD dwKeyValueDataMaxLen; // 键值项数据的最大长度(in bytes)  
	ret = RegQueryInfoKey(
		hKey,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		&dwKeyValueCnt,
		&dwKeyValueNameMaxLen,
		&dwKeyValueDataMaxLen,
		NULL,
		NULL
	);
	// printf("%I64d\n", dwKeyValueCnt);

	//遍历key下的value寻找start项
	dwKeyValueNameMaxLen++;
	dwKeyValueDataMaxLen++;
	LPTSTR tmp_name = (LPTSTR)malloc((dwKeyValueNameMaxLen) * sizeof(TCHAR));
	LPBYTE data = (LPBYTE)malloc((dwKeyValueDataMaxLen) * sizeof(BYTE));
	bool flag_autorun = false;
	bool flag_services = false;
	for (DWORD i = 0; i < dwKeyValueCnt; i++) {
		memset(tmp_name, 0, (dwKeyValueNameMaxLen) * sizeof(TCHAR));
		memset(data, 0, (dwKeyValueDataMaxLen) * sizeof(BYTE));
		DWORD tmp_max_name = dwKeyValueNameMaxLen;
		DWORD tmp_max_data = dwKeyValueDataMaxLen;
		ret = RegEnumValue(
			hKey,
			i,
			tmp_name,
			&tmp_max_name,
			NULL,
			NULL,
			data,
			&tmp_max_data
		);
		if (ret != ERROR_SUCCESS) {
			printf("error code %ld\n", GetLastError());
			printf("when check value of service, error!!\n");
		}
		if (!wcscmp(tmp_name, L"Start")) {
			if (data[0] <= 2) {
				flag_autorun = true;
				continue;
			}
		}
		if (!wcscmp(tmp_name, L"ImagePath")) {
			// strcpy(imagePath, data);
			for (unsigned int j = 0; j < tmp_max_data; j++) {
				imagePath[j] = data[j];
			}
			continue;
		}
		if (!wcscmp(tmp_name, L"Type")) {
			if (data[0] >= 16) {
				flag_services = true;
			}
			continue;
		}
	}

	return flag_services && flag_autorun;
}



//查找自启动服务
//HKLM\System\CurrentControlSet\Services, start=2
void get_service_autoRun() {
	HKEY rootKey = HKEY_LOCAL_MACHINE;
	LPCTSTR subKey = L"SYSTEM\\CurrentControlSet\\Services";
	HKEY hKey;
	LPTSTR * subkeys;
	LPBYTE * subKey_values;

	//1. 打开rootkey下的subkey句柄
	int ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, KEY_ALL_ACCESS, &hKey);
	if (ret != ERROR_SUCCESS) {
		printf("open key error!!\n");
		printf("error code:%ld", GetLastError());
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
	//printf("dwKeyValue count:%ld\n", dwSubKeyNameMaxLen);

	//2.2 遍历读取子键
	dwSubKeyCnt++; //为了包括结尾的NULL
	dwSubKeyNameMaxLen++;
	subkeys = (LPTSTR *)malloc(dwSubKeyCnt * sizeof(LPTSTR));
	memset(subkeys, 0, dwSubKeyCnt * sizeof(LPTSTR));
	LPBYTE imagePath = (LPBYTE)malloc(200 * sizeof(BYTE));

	//debug
	// subkeys[0] = (LPTSTR) malloc((dwKeyValueNameMaxLen)*sizeof(TCHAR));

	//load info
	for (DWORD i = 0; i < dwSubKeyCnt; i++) {
		DWORD tmp_max_name = dwSubKeyCnt;
		DWORD tmp_max_ch = dwSubKeyNameMaxLen;
		subkeys[i] = (LPTSTR)malloc((dwSubKeyNameMaxLen) * sizeof(TCHAR));
		memset(subkeys[i], 0, (dwSubKeyNameMaxLen) * sizeof(TCHAR));

		ret = RegEnumKeyEx(
			hKey,
			i,
			subkeys[i],
			&tmp_max_ch,
			NULL,
			NULL,
			NULL,
			NULL
		);
		if (ret != ERROR_SUCCESS) {
			if (GetLastError() == 0) return;
			printf("error code:%ld\n", GetLastError());
			printf("len:%ld\n", dwSubKeyCnt);
		}
		if (check_autorun_service(hKey, subkeys[i], imagePath)) {
			wstring verifyInfo;
			printf("  SERVICE NAME:  %ws\n", subkeys[i]);
			printf("  INCLUDE PATH:  %ws\n", get_path_end_with_exe(imagePath).c_str() );
			VerifyEmbeddedSignature(get_path_end_with_exe(imagePath).c_str(), &verifyInfo);
			printf("  SIGN AND VERIFY:  %ws\n\n", verifyInfo.c_str());
			memset(imagePath, 0, sizeof(BYTE) * 200);
		}
	}

	//释放内存，关闭句柄,todo
	RegCloseKey(hKey);
}