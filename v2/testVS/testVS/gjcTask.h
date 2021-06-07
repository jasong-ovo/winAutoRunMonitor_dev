#pragma once
#define _WIN32_DCOM

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <comdef.h>
//  Include the task header file.
#include <taskschd.h>
#include <tchar.h>

#pragma comment(lib, "taskschd.lib")
#pragma comment(lib, "comsupp.lib")


using namespace std;
int get_task_in_subfolder(ITaskService * pService, wstring dir);
void get_live_task(ITaskService * pService, wstring taskDir, wstring fileName);
void get_task_info();