#pragma once
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <memory.h>
#include <winreg.h>

bool check_autorun_service(HKEY parent, LPTSTR subkey, LPBYTE imagePath);
void get_service_autoRun();