#include "gjcDriver.h"
#include "verify.h"
#include "utils.h"


//�������start
bool check_autorun_driver(HKEY parent, LPTSTR subkey, LPBYTE imagePath) {
	HKEY hKey;
	int ret = RegOpenKeyEx(parent, subkey, 0, STANDARD_RIGHTS_READ | KEY_QUERY_VALUE, &hKey);
	if (ret != ERROR_SUCCESS) {
		printf("error code %ld", GetLastError());
		printf("open key error when check autorun service !!\n");
		return false;
	}

	//�õ����ֵ���������
	DWORD dwKeyValueCnt;        // ��ֵ�������  
	DWORD dwKeyValueNameMaxLen; // ��ֵ�����Ƶ���󳤶�(��������β��null�ַ�)  
	DWORD dwKeyValueDataMaxLen; // ��ֵ�����ݵ���󳤶�(in bytes)  
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

	//����key�µ�valueѰ��start��
	dwKeyValueNameMaxLen++;
	dwKeyValueDataMaxLen++;
	LPTSTR tmp_name = (LPTSTR)malloc((dwKeyValueNameMaxLen) * sizeof(TCHAR));
	LPBYTE data = (LPBYTE)malloc((dwKeyValueDataMaxLen) * sizeof(BYTE));
	bool flag_autorun = false;
	bool flag_driver = false;
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
			if (data[0] <= 8) {
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
			if (data[0] <= 2) {
				flag_driver = true;
			}
			continue;
		}
	}

	return flag_driver && flag_autorun;
}



//��������������
//HKLM\System\CurrentControlSet\Services, start=2
void get_driver_autoRun() {
	HKEY rootKey = HKEY_LOCAL_MACHINE;
	const wchar_t * subKey = TEXT("SYSTEM\\CurrentControlSet\\Services");
	HKEY hKey;
	LPTSTR * subkeys;
	LPBYTE * subKey_values;

	//1. ��rootkey�µ�subkey���
	int ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, KEY_ALL_ACCESS, &hKey);
	if (ret != ERROR_SUCCESS) {
		printf("open key error!!\n");
		printf("error code:%ld", GetLastError());
		return;
	}


	//2. �Ķ����Ӽ��µ����м�ֵ��

	//2.1 ��ʼ��
	DWORD dwSubKeyCnt;          // �Ӽ�������  
	DWORD dwSubKeyNameMaxLen;   // �Ӽ����Ƶ���󳤶�(��������β��null�ַ�)  
	DWORD dwKeyValueCnt;        // ��ֵ�������  
	DWORD dwKeyValueNameMaxLen; // ��ֵ�����Ƶ���󳤶�(��������β��null�ַ�)  
	DWORD dwKeyValueDataMaxLen; // ��ֵ�����ݵ���󳤶�(in bytes)  
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

	//2.2 ������ȡ�Ӽ�
	dwSubKeyCnt++; //Ϊ�˰�����β��NULL
	dwSubKeyNameMaxLen++;
	subkeys = (LPTSTR *)malloc(dwSubKeyCnt * sizeof(LPTSTR));
	memset(subkeys, 0, dwSubKeyCnt * sizeof(LPTSTR));
	LPBYTE imagePath = (LPBYTE)malloc(200 * sizeof(BYTE));

	//debug
	// subkeys[0] = (LPTSTR) malloc((dwKeyValueNameMaxLen)*sizeof(TCHAR));

	FILE * fp;
	fopen_s(&fp, "..\\..\\results\\driver.txt", "w");
	if (fp == NULL) printf("error open file!\n");
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
			/*printf("error when enum Value!!\n");*/
			if (GetLastError() == 0) return;
			printf("error code:%ld\n", GetLastError());
			printf("len:%ld\n", dwSubKeyCnt);
		}
		if (check_autorun_driver(hKey, subkeys[i], imagePath)) {
			wstring verifyInfo;
			wstring path;
			path = get_path_end_with_sys(imagePath);
			VerifyEmbeddedSignature(path.c_str(), &verifyInfo);
			printf("  DRIVER: %ws\n", subkeys[i]);
			printf("  INCLUDE PATH:  %ws\n", path.c_str());
			printf("  SIGN AND VERIFY: %ws\n\n", verifyInfo.c_str());

			//д���ļ� 
			wstring bufMessage;
			wstring nameWS = subkeys[i];
			wstring pathWS = path.c_str();
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
			memset(imagePath, 0, sizeof(BYTE) * 200);
		}

	}

	fclose(fp);
	//�ͷ��ڴ棬�رվ��,todo
	RegCloseKey(hKey);
}