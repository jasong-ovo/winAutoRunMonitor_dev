#pragma once
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <memory.h>
#include <winreg.h>

//void get_logon_info_reg(HKEY rootKey, LPCSTR subKey, unsigned short mask);
void get_logon_info_file(LPCWSTR fileName);
void get_logon_info_reg(HKEY rootKey, LPCWSTR subKey, unsigned short mask);