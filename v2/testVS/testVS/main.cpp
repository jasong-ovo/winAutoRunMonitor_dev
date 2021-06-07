// testVS.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "gjcLogon.h"
#include "gjcService.h"
#include "gjcDriver.h"
#include "gjcTask.h"
#include "utils.h"
using namespace std;

int main(int argc, char *argv[])
{	
	if (argc != 2 && argc != 3) {
		cout << "usage: main [logon user]|[service]|[driver]|[task]";
		return 0;
	}

	if (!strcmp(argv[1], "logon")) {
		if (argc != 3) {
			cout <<"usage: main [logon user]" <<endl;
			return -1;
		}
		string user(argv[2]);
		wstring wuser = string2wstring(user);

		wstring prefix = L"C:\\Users\\";
		wstring suffix = L"\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\*.*";
		wstring w_path2 = prefix + wuser + suffix;
		//auto run in folder
		LPCWSTR path1 = L"C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\*.*";
		//LPCWSTR path2 = L"C:\\Users\\considerate Cortana\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\*.*";
		LPCWSTR path2 = w_path2.c_str();
		printf("path:%ws\n", path1);
		get_logon_info_file(path1);
		printf("path:%ws\n", path2);
		get_logon_info_file(path2);

		//auto run in register
		char HKCU[6] = "HKCU\\";
		char HKLM[6] = "HKLM\\";
		LPCTSTR subkey1 = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
		LPCTSTR subkey2 = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run");
		LPCTSTR subkey3 = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce");
		LPCTSTR subkey4 = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnceEx");
		LPCTSTR subkey5 = TEXT("SOFTWARE\\Microsoft\\Active Setup\\Installed Components");
		//subkey1
		printf("path:%s%ws(Wow6432Node)\n", HKCU, subkey1);
		get_logon_info_reg(HKEY_CURRENT_USER, subkey1, KEY_WOW64_32KEY);
		printf("path:%s%ws\n", HKCU, subkey1);
		get_logon_info_reg(HKEY_CURRENT_USER, subkey1, KEY_WOW64_64KEY);
		printf("path:%s%ws(Wow6432Node)\n", HKLM, subkey1);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey1, KEY_WOW64_32KEY);
		printf("path:%s%ws\n", HKLM, subkey1);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey1, KEY_WOW64_64KEY);
		//subkey2
		printf("path:%s%ws(Wow6432Node)\n", HKCU, subkey2);
		get_logon_info_reg(HKEY_CURRENT_USER, subkey2, KEY_WOW64_32KEY);
		printf("path:%s%ws\n", HKCU, subkey2);
		get_logon_info_reg(HKEY_CURRENT_USER, subkey2, KEY_WOW64_64KEY);
		printf("path:%s%ws(Wow6432Node)\n", HKLM, subkey2);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey2, KEY_WOW64_32KEY);
		printf("path:%s%ws\n", HKLM, subkey2);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey2, KEY_WOW64_64KEY);
		//subkey3
		printf("path:%s%ws(Wow6432Node)\n", HKCU, subkey3);
		get_logon_info_reg(HKEY_CURRENT_USER, subkey3, KEY_WOW64_32KEY);
		printf("path:%s%ws\n", HKCU, subkey3);
		get_logon_info_reg(HKEY_CURRENT_USER, subkey3, KEY_WOW64_64KEY);
		printf("path:%s%ws(Wow6432Node)\n", HKLM, subkey3);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey3, KEY_WOW64_32KEY);
		printf("path:%s%ws\n", HKLM, subkey3);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey3, KEY_WOW64_64KEY);
		//subkey4
		printf("path:%s%ws(Wow6432Node)\n", HKCU, subkey4);
		get_logon_info_reg(HKEY_CURRENT_USER, subkey4, KEY_WOW64_32KEY);
		printf("path:%s%ws\n", HKCU, subkey4);
		get_logon_info_reg(HKEY_CURRENT_USER, subkey4, KEY_WOW64_64KEY);
		printf("path:%s%ws(Wow6432Node)\n", HKLM, subkey4);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey4, KEY_WOW64_32KEY);
		printf("path:%s%ws\n", HKLM, subkey4);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey4, KEY_WOW64_64KEY);
		//subkey5
		printf("path:%s%ws(Wow6432Node)\n", HKLM, subkey5);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey5, KEY_WOW64_32KEY);
		printf("path:%s%ws\n", HKLM, subkey5);
		get_logon_info_reg(HKEY_LOCAL_MACHINE, subkey5, KEY_WOW64_64KEY);
	}

	if (!strcmp(argv[1], "service")) {
		printf("path:HKLM\\SYSTEM\\CurrentControlSet\\Services\n");
		get_service_autoRun();
	}

	if (!strcmp(argv[1], "driver")) {
		printf("path:HKLM\\SYSTEM\\CurrentControlSet\\Services\n");
		get_driver_autoRun();
	}

	if (!strcmp(argv[1], "task")) {
		get_task_info();
	}

	
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
