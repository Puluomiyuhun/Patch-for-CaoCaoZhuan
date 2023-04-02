#pragma once
#include "pch.h"
#include <fstream>
//枚举所有窗口
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)// 回调函数
{
	DWORD dwCurProcessId = *((DWORD*)lParam);
	DWORD dwProcessId = 0;
	GetWindowThreadProcessId(hwnd, &dwProcessId);
	if (dwProcessId == dwCurProcessId && GetParent(hwnd) == NULL)
	{
		*((HWND*)lParam) = hwnd;
		return FALSE;
	}

	return TRUE;
}

//获取创建偶句柄
HWND GetWindowHandle()
{
	DWORD dwCurrentProcessId = GetCurrentProcessId();
	if (!EnumWindows(EnumWindowsProc, (LPARAM)&dwCurrentProcessId))
	{
		return (HWND)dwCurrentProcessId;
	}
	return NULL;
}

void WriteIn(HANDLE pro, DWORD addr, DWORD value, int len)
{
	DWORD new_sun_value = value;
	WriteProcessMemory(pro, (LPVOID)addr, &new_sun_value, len, 0);
}

void debugInt(int d)
{
	FILE* logFile = fopen("debug.log", "w+");
	fprintf(logFile, "%d\n", d);
	fflush(logFile);
}

int translate(char a, char b)
{
	int res = 0;
	if (a >= '0' && a <= '9')
		res += (a - '0') * 16;
	else
		res += (a - 'A' + 10) * 16;
	if (b >= '0' && b <= '9')
		res += (b - '0');
	else
		res += b - 'A' + 10;
	return res;
}

wchar_t* char2wchar(const char* cchar)
{
	wchar_t* m_wchar;
	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
	m_wchar[len] = '\0';
	return m_wchar;
}

wchar_t* getPath(int idx)
{
	wchar_t path[100];
	wcscpy_s(path, L"./SoundTrk/");
	if (idx < 10) wcscat_s(path, L"0");
	char num[4] = "\0\0\0";
	_itoa(idx, num, 10);
	wcscat_s(path, char2wchar(num));
	wcscat_s(path, L"-AudioTrack ");
	if (idx < 10) wcscat_s(path, L"0");
	wcscat_s(path, char2wchar(num));
	wcscat_s(path, L".mp3");
	return path;
}