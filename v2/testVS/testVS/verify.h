#pragma once
#define _UNICODE 1
#define UNICODE 1

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Softpub.h>
#include <wincrypt.h>
#include <wintrust.h>
#include <string>

using namespace std;

// Link with the Wintrust.lib file.
#pragma comment (lib, "wintrust")

BOOL VerifyEmbeddedSignature(LPCWSTR pwszSourceFile, wstring *verifyInfo);