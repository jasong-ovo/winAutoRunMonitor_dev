#pragma once
#include <string>
#include <windows.h>
#include <iostream>

using namespace std;

wstring get_path_in_quotation(LPBYTE pPath);
wstring get_path_end_with_exe(LPBYTE pPath);
wstring get_path_end_with_sys(LPBYTE pPath);