#pragma once
#include "pch.h"
#include "GlobalVar.h"
#include <Atlimage.h>
#include <mmsystem.h>
#include <digitalv.h>
#pragma comment(lib,"dwmapi.lib")
#pragma comment(lib, "winmm.lib")
using namespace std;

HWND effect_hwnd;            //雨雪效果窗口句柄
HWND effect_hwnd2;           //明暗效果窗口句柄

int timer = 0;            //雨雪效果计时器
int frame = 1;            //雨雪效果帧编号
int day = 20;

//雨雪效果控件响应
LRESULT CALLBACK EffectWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY: {
		exit(0);
		break;
	}
	default:
		return  DefWindowProc(hWnd, message, wParam, lParam);
	}
}

//雨雪效果线程
DWORD static WINAPI Effect(LPVOID lpvoid)
{
	int rs = 0, last_rs = 0;
	int weather_idx = 0, weather_type = 0;
	int lighting = 0;
	int raining = 0;
	int thunder = 0;
	int condition = 0;
	bool light_up = true;

	int weather_list[30] = { 0,0,0,1,2,3,0,0,0,0,1,2,0,1,2,2,3,3,0,0,1,1,4,4,0,1,4,4,4,4 };
	srand((unsigned)time(NULL));
	//载入图片
	HBITMAP hBitmap[17];
	CImage ci;
	HRESULT ret = ci.Load(_T("./patch/rain/1.jpg"));
	hBitmap[1] = ci.Detach();
	ret = ci.Load(_T("./patch/rain/2.jpg"));
	hBitmap[2] = ci.Detach();
	ret = ci.Load(_T("./patch/rain/3.jpg"));
	hBitmap[3] = ci.Detach();
	ret = ci.Load(_T("./patch/rain/4.jpg"));
	hBitmap[4] = ci.Detach();
	ret = ci.Load(_T("./patch/rain/5.jpg"));
	hBitmap[5] = ci.Detach();
	ret = ci.Load(_T("./patch/rain/6.jpg"));
	hBitmap[6] = ci.Detach();
	ret = ci.Load(_T("./patch/rain/7.jpg"));
	hBitmap[7] = ci.Detach();
	ret = ci.Load(_T("./patch/rain/8.jpg"));
	hBitmap[8] = ci.Detach();
	ret = ci.Load(_T("./patch/snow/1.jpg"));
	hBitmap[9] = ci.Detach();
	ret = ci.Load(_T("./patch/snow/2.jpg"));
	hBitmap[10] = ci.Detach();
	ret = ci.Load(_T("./patch/snow/3.jpg"));
	hBitmap[11] = ci.Detach();
	ret = ci.Load(_T("./patch/snow/4.jpg"));
	hBitmap[12] = ci.Detach();
	ret = ci.Load(_T("./patch/snow/5.jpg"));
	hBitmap[13] = ci.Detach();
	ret = ci.Load(_T("./patch/snow/6.jpg"));
	hBitmap[14] = ci.Detach();
	ret = ci.Load(_T("./patch/snow/7.jpg"));
	hBitmap[15] = ci.Detach();
	ret = ci.Load(_T("./patch/snow/8.jpg"));
	hBitmap[16] = ci.Detach();
	SetLayeredWindowAttributes(effect_hwnd, RGB(0, 0, 0), 0, LWA_ALPHA);
	SetLayeredWindowAttributes(effect_hwnd2, RGB(255, 255, 255), 0, LWA_ALPHA | LWA_COLORKEY);
	while (1)
	{
		/*全随机判定*/
		short num = 0;
		ReadProcessMemory(hpro, (LPCVOID)0x50599E, &num, 1, 0);
		int base = 0;
		ReadProcessMemory(hpro, (LPCVOID)0x4CEA00, &base, 4, 0);
		/*我军随机*/
		if ((num & 1) != 0) {
			char code[] = "5A 5A 90 90 90 90 90 90 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x40C389 + i, c, 1);
			}
			char code2[] = "55 8B EC 83 EC 18 6A 02 8B 4D 08 E8 11 38 00 00 66 89 45 FC 90 90 90 90 90 90 6A 03 8B 4D 08 E8 "
				"FD 37 00 00 66 89 45 F8 66 3D 00 80 90 90 90 90 90 90 90 90 90 90 90 90 E8 0F 6D FF FF 90 90 90 "
				"90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 "
				"90 0F B7 45 FC 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 "
				"90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 "
				"90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 "
				"90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 "
				"90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 B8 01 00 00 00 8B E5 5D C3 ";
			for (int i = 0; i < strlen(code2) / 3; i++)
			{
				int c = translate(code2[i * 3], code2[i * 3 + 1]);
				WriteIn(hpro, 0x414BD6 + i, c, 1);
			}

			/*只有选了“我军随机”而没选“敌友随机”的时候执行这个*/
			/*ReadProcessMemory(hpro, (LPVOID)(hpro, 0x4B0776 + 0), &rs, 1, 0);
			if ((num & 2) == 0 && rs % 2 == 0 && last_rs != rs) {
				int wojun = 0;
				srand((unsigned)time(NULL));
				for (int i = 0; i < 1024; i++) {
					ReadProcessMemory(hpro, (LPCVOID)(base + i * 0x48 + 0x2A), &wojun, 1, 0);
					if (wojun != 0) {
						int random = rand() % 80;
						WriteIn(hpro, base + i * 0x48 + 0x2B, random, 1);
					}
				}
			}*/
			ReadProcessMemory(hpro, (LPVOID)(hpro, 0x4B0776 + 0), &rs, 1, 0);
			if (rs % 2 == 0 && last_rs != rs) {
				unsigned int seed;
				ReadProcessMemory(hpro, (LPCVOID)0x5059A0, &seed, 2, 0);
				for (int i = 0; i < 1024; i++) {
					seed = seed * 17 % 65535;
					int wojun = 0;
					ReadProcessMemory(hpro, (LPCVOID)(base + i * 0x48 + 0x2A), &wojun, 1, 0);
					if (wojun != 0) {
						//ExitProcess(0);
						WriteIn(hpro, base + i * 0x48 + 0x2B, seed % 80, 1);
					}
				}
			}
		}
		else {
			char code[] = "FF 75 08 E8 DB 5C 05 00 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x40C389 + i, c, 1);
			}
			if (version <= 64) {
				char code2[] = "55 8B EC 83 EC 18 6A 02 8B 4D 08 E8 11 38 00 00 66 89 45 FC 66 3D 00 80 74 14 6A 03 8B 4D 08 E8 "
					"FD 37 00 00 66 89 45 F8 66 3D 00 80 75 0A B8 05 00 00 00 E9 C4 00 00 00 E8 0F 6D FF FF 85 C0 74 "
					"20 0F B7 45 FC 3D 00 04 00 00 7C 15 3D 02 04 00 00 7F 0E B9 F0 5D 4B 00 E8 AD 40 00 00 66 89 45 "
					"FC 0F B7 45 FC 3D 00 04 00 00 0F 8D 87 00 00 00 50 E8 98 15 FF FF 89 4D E8 8A 55 F8 52 E8 C7 93 "
					"FF FF FF 75 E8 E8 33 FF FF FF 80 3D C4 5F 50 00 00 74 0D FF 75 FC FF 75 E8 6A 00 E8 5D FD FF FF "
					"E8 A7 6C FF FF 85 C0 74 44 8B 4D E8 E8 55 2E 06 00 3C FF 74 38 8A C8 E8 67 15 FF FF 89 4D F0 83 "
					"3D 80 3C 4B 00 01 74 0F 8B C9 E8 87 B1 02 00 8B 4D F0 E8 1C B0 02 00 B8 50 77 49 00 8B 4D E8 89 "
					"48 10 8B 4D F0 89 48 08 E8 1C 54 00 00 0F B7 4D FC 51 E8 34 4D 06 00 B8 01 00 00 00 8B E5 5D C3 ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x414BD6 + i, c, 1);
				}
			}
			else {
				char code2[] = "55 8B EC 83 EC 18 6A 02 8B 4D 08 E8 11 38 00 00 66 89 45 FC 66 3D 00 80 74 14 6A 03 8B 4D 08 E8 "
					"FD 37 00 00 66 89 45 F8 66 3D 00 80 75 0A B8 05 00 00 00 E9 C1 00 00 00 E8 0F 6D FF FF 85 C0 74 "
					"20 0F B7 45 FC 3D 00 04 00 00 7C 15 3D 02 04 00 00 7F 0E B9 F0 5D 4B 00 E8 AD 40 00 00 66 89 45 "
					"FC 0F B7 45 FC 3D 00 04 00 00 0F 8D 85 00 00 00 50 E8 98 15 FF FF 89 4D E8 8A 55 F8 52 E8 C7 93 "
					"FF FF FF 75 E8 E8 33 FF FF FF 80 3D C4 5F 50 00 00 74 0D FF 75 FC FF 75 E8 6A 00 E8 59 FD FF FF "
					"E8 A7 6C FF FF 85 C0 74 42 8B 4D E8 E8 55 2E 06 00 3C FF 74 36 8A C8 E8 67 15 FF FF 89 4D F0 83 "
					"3D 80 3C 4B 00 01 74 0D E8 89 B1 02 00 8B 4D F0 E8 1E B0 02 00 B8 50 77 49 00 8B 4D E8 89 48 10 "
					"8B 4D F0 89 48 08 E8 1E 54 00 00 0F B7 4D FC 51 E8 36 4D 06 00 33 C0 B0 01 8B E5 5D C3 55 8B EC "
					"51 33 C0 50 50 50 E8 AE 18 FF FF 51 8B 4D FC E8 E2 76 02 00 8B 55 F8 8B 4D 0C 85 C9 75 06 85 C0 "
					"75 27 EB 14 85 C0 75 10 FF 45 F0 66 FF 4D F4 83 F9 06 73 15 49 89 4D 08 83 45 F8 04 ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x414BD6 + i, c, 1);
				}

			}
		}
		/*敌友随机*/
		if (version <= 63) {
			if ((num & 2) != 0) WriteIn(hpro, 0x408D0E, 0x909090, 3);
			else WriteIn(hpro, 0x408D0E, 0x2B4188, 3);
		}
		else {
			if ((num & 2) != 0) WriteIn(hpro, 0x40E025, 0x909090, 3);
			else WriteIn(hpro, 0x40E025, 0x2B4188, 3);
		}
		/*随机对象形象归为普造*/
		if ((num & 4) != 0) {
			int ss = 0; int wojun = 0;
			for (int i = 0; i < 1024; i++) {
				ReadProcessMemory(hpro, (LPCVOID)(base + i * 0x48 + 0x2A), &wojun, 1, 0);
				if ((num & 1) != 0 && wojun == 0)
					WriteIn(hpro, 0x501000 + i * 2, 0, 2);
				if ((num & 2) != 0 && wojun != 0)
					WriteIn(hpro, 0x501000 + i * 2, 0, 2);
			}
		}
		/*文官mp补偿*/
		if ((num & 8) != 0) {
			int mp = 0; int bingzhong = 0; int wojun = 0; int type = 0; int offset = 0;
			ReadProcessMemory(hpro, (LPCVOID)0x41A8A0, &offset, 1, 0);
			if (offset == 0x55) offset = 0x1F;
			else offset = 0x20;
			for (int i = 0; i < 1024; i++) {
				ReadProcessMemory(hpro, (LPCVOID)(base + i * 0x48 + 0x2A), &wojun, 1, 0);
				ReadProcessMemory(hpro, (LPCVOID)(base + i * 0x48 + 0x2B), &bingzhong, 1, 0);
				if (bingzhong < 60)bingzhong = bingzhong / 3;
				else bingzhong = bingzhong - 40;
				mp = 0;
				ReadProcessMemory(hpro, (LPCVOID)(base + i * 0x48 + offset), &mp, 0x21 - offset, 0);
				ReadProcessMemory(hpro, (LPCVOID)(0x4D2188 + bingzhong), &type, 1, 0);
				/*检查是否突破过mp上限*/
				if ((num & 1) != 0 && wojun == 0 && type == 1 && mp < 50)
					WriteIn(hpro, base + i * 0x48 + offset, 50, 0x21 - offset);
				if ((num & 2) != 0 && wojun != 0 && type == 1 && mp < 50)
					WriteIn(hpro, base + i * 0x48 + offset, 50, 0x21 - offset);
			}
		}
		/*随机宝物*/
		if ((num & 16) != 0) {
			WriteIn(hpro, 0x48ECD4, rand() % 0xFFFFFFFF, 4);
			if (version <= 63) {
				char code[] = "E9 C8 87 FF FF ";
				for (int i = 0; i < strlen(code) / 3; i++)
				{
					int c = translate(code[i * 3], code[i * 3 + 1]);
					WriteIn(hpro, 0x4143E5 + i, c, 1);
				}
				char code2[] = "83 F8 56 76 09 3D 82 00 00 00 7D 02 EB 28 68 99 00 00 00 E8 49 2F 07 00 83 F8 56 76 09 3D 82 00 00 00 7D 02 EB E8 8B D0 6B D2 19 8A 8A 54 11 4A 00 80 F9 FF 74 D8 89 45 F8 6A 49 E9 F8 77 00 00 ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x40CBB2 + i, c, 1);
				}
			}
			else {
				char code[] = "E8 CF 87 FF FF ";
				for (int i = 0; i < strlen(code) / 3; i++)
				{
					int c = translate(code[i * 3], code[i * 3 + 1]);
					WriteIn(hpro, 0x4143DE + i, c, 1);
				}
				char code2[] = "3D 95 00 00 00 7F 1A 68 95 00 00 00 E8 50 2F 07 00 8B D0 6B D2 19 8A 8A 54 11 4A 00 80 F9 FF 74 E6 3D 00 80 00 00 C3 ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x40CBB2 + i, c, 1);
				}
			}
		}
		else {
			if (version <= 63) {
				char code[] = "89 45 F8 6A 49 ";
				for (int i = 0; i < strlen(code) / 3; i++)
				{
					int c = translate(code[i * 3], code[i * 3 + 1]);
					WriteIn(hpro, 0x4143E5 + i, c, 1);
				}
			}
			else {
				char code[] = "3D 00 80 00 00 ";
				for (int i = 0; i < strlen(code) / 3; i++)
				{
					int c = translate(code[i * 3], code[i * 3 + 1]);
					WriteIn(hpro, 0x4143DE + i, c, 1);
				}
			}
		}



		if (IsIconic(pro_hwnd)) {
			if (sound1 == true) {
				mciSendString(_T("pause rain"), NULL, 0, NULL);
				sound1 = false;
			}
			if (sound2 == true) {
				mciSendString(_T("pause snow"), NULL, 0, NULL);
				sound2 = false;
			}
		}
		/*未开启雨雪功能，清除图片，关闭声音*/
		if (!effect_check[0])
		{
			SetLayeredWindowAttributes(effect_hwnd, RGB(0, 0, 0), 0, LWA_ALPHA);
			SetLayeredWindowAttributes(effect_hwnd2, RGB(255, 255, 255), 0, LWA_ALPHA | LWA_COLORKEY);
			if (sound1 == true) {
				mciSendString(_T("pause rain"), NULL, 0, NULL);
				sound1 = false;
			}
			if (sound2 == true) {
				mciSendString(_T("pause snow"), NULL, 0, NULL);
				sound2 = false;
			}
			raining = 0;
			Sleep(1000);
			continue;
		}
		/*检查当前RS剧本、天气*/
		{
			ReadProcessMemory(hpro, (LPVOID)(hpro, 0x4B0776 + 0), &rs, 1, 0);
			ReadProcessMemory(hpro, (LPVOID)(hpro, 0x4B3D0C + 0), &weather_idx, 1, 0);
			ReadProcessMemory(hpro, (LPVOID)(hpro, 0x4B3D19 + 0), &weather_type, 1, 0);
		}
		/*检查如果是R剧本*/
		if ((rs % 2 == 0 || last_rs != rs) && !effect_check[6])
		{
			SetLayeredWindowAttributes(effect_hwnd, RGB(0, 0, 0), 0, LWA_ALPHA);
			SetLayeredWindowAttributes(effect_hwnd2, RGB(255, 255, 255), 0, LWA_ALPHA | LWA_COLORKEY);
			if (sound1 == true) {
				mciSendString(_T("pause rain"), NULL, 0, NULL);
				sound1 = false;
			}
			if (sound2 == true) {
				mciSendString(_T("pause snow"), NULL, 0, NULL);
				sound2 = false;
			}
			last_rs = rs;
			raining = 0;
			Sleep(400);
			continue;
		}
		last_rs = rs;
		RECT rt1, rt2, rt3;
		GetWindowRect(pro_hwnd, &rt1);
		GetWindowRect(effect_hwnd, &rt2);
		GetWindowRect(effect_hwnd, &rt3);
		{
			MARGINS m = { 0, 0, 1920, 1440 };
			DwmExtendFrameIntoClientArea(effect_hwnd, &m);
			MoveWindow(effect_hwnd, 0, 56, 1920, 1440, true);
		}
		{
			MARGINS m = { 0, 0, 1920, 1440 };
			DwmExtendFrameIntoClientArea(effect_hwnd2, &m);
			MoveWindow(effect_hwnd2, 0, 56, 1920, 1440, true);
		}
		//Sleep(1000);
		Sleep(effect_edit[5]);
		{
			int weather = weather_list[weather_type * 6 + weather_idx];
			if (weather == 0)
			{
				if (raining > 0)raining -= 5;
				if (lighting > 0)lighting -= 1;
				if (lighting <= 0)lighting = 0;
				if (lighting <= 0 && raining <= 0)condition = 0;
			}
			else if (weather == 1)
			{
				if (raining > 0)raining -= 5;
				if (lighting < effect_edit[3])lighting += 1;
				else if (lighting > effect_edit[3] + 5)lighting -= 1;
				else if (raining == 0)condition = 0;
			}
			else if (weather == 2) {
				if (light_up == true)
					lighting += 1;
				else
					lighting -= 1;
				if (lighting <= effect_edit[0])
					light_up = true;
				if (lighting >= effect_edit[0] + 10)
					light_up = false;
				if (raining < 235)
					raining += 10;
				if (raining > 235)
					raining = 235;
				condition = 1;
			}
			else if (weather == 3) {
				if (light_up == true)
					lighting += 1;
				else
					lighting -= 1;
				if (lighting <= effect_edit[1] + 5)
					light_up = true;
				if (lighting >= effect_edit[1] + 15)
					light_up = false;
				if (raining < 255)
					raining += 10;
				if (raining > 255)
					raining = 255;
				condition = 1;
			}
			else {
				if (light_up == true)
					lighting += 1;
				else
					lighting -= 1;
				if (lighting <= effect_edit[2] + 5)
					light_up = true;
				if (lighting >= effect_edit[2] + 15)
					light_up = false;
				if (raining < 255)
					raining += 10;
				if (raining > 255)
					raining = 255;
				condition = 2;
			}
			SetLayeredWindowAttributes(effect_hwnd, RGB(0, 0, 0), raining * effect_edit[6] / 550, LWA_ALPHA);
			
			if (weather == 3 && rand() % effect_edit[4] < 2 && effect_check[5])
				thunder = 3;
			if (thunder > 0)
			{
				if (thunder > 2 || thunder <= 1)
					SetLayeredWindowAttributes(effect_hwnd2, RGB(255, 255, 255), lighting - 17, LWA_ALPHA | LWA_COLORKEY);
				else
					SetLayeredWindowAttributes(effect_hwnd2, RGB(255, 255, 255), lighting, LWA_ALPHA | LWA_COLORKEY);
				thunder--;
			}
			else
				SetLayeredWindowAttributes(effect_hwnd2, RGB(255, 255, 255), lighting, LWA_ALPHA | LWA_COLORKEY);

			CWnd* pCWnd = CWnd::FromHandle(effect_hwnd);
			CWnd* pWnd = pCWnd->GetDlgItem(10000);
			CStatic* cs = (CStatic*)pCWnd->GetDlgItem(10000);
			cs->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
			HBITMAP hBitmap_now;
			if (condition == 1) {
				hBitmap_now = hBitmap[frame];
				cs->SetBitmap(hBitmap_now);
				if (sound1 == false && effect_check[2]) {
					mciSendString(_T("open ./patch/rain/rain.mp3 alias rain"), NULL, 0, NULL);
					mciSendString(_T("play rain repeat"), NULL, 0, NULL);
					sound1 = true;
				}
				if (!effect_check[2] && sound1 == true) {
					mciSendString(_T("pause rain"), NULL, 0, NULL);
					sound1 = false;
				}
				if (!effect_check[1])
					SetLayeredWindowAttributes(effect_hwnd, RGB(0, 0, 0), 0, LWA_ALPHA);
			}
			else if (condition == 2)
			{
				hBitmap_now = hBitmap[frame + 8];
				cs->SetBitmap(hBitmap_now);
				if (sound2 == false && effect_check[4]) {
					mciSendString(_T("open ./patch/snow/snow.mp3 alias snow"), NULL, 0, NULL);
					mciSendString(_T("play snow repeat"), NULL, 0, NULL);
					sound2 = true;
				}
				if (!effect_check[4] && sound2 == true) {
					mciSendString(_T("pause snow"), NULL, 0, NULL);
					sound2 = false;
				}
				if (!effect_check[3])
					SetLayeredWindowAttributes(effect_hwnd, RGB(0, 0, 0), 0, LWA_ALPHA);
			}
			else {
				if (sound1 == true) {
					mciSendString(_T("pause rain"), NULL, 0, NULL);
					sound1 = false;
				}
				if (sound2 == true) {
					mciSendString(_T("pause snow"), NULL, 0, NULL);
					sound2 = false;
				}
			}
			frame++;
			if (frame == 9)
				frame = 1;
		}
	}
}

void CreateEffectWindow()
{
	WNDCLASSEX wndcls;
	wndcls.cbSize = sizeof(WNDCLASSEX);
	wndcls.lpfnWndProc = EffectWndProc;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = HBRUSH(RGB(0, 0, 0));
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hIcon = NULL;
	wndcls.hIconSm = NULL;
	wndcls.hInstance = NULL;
	wndcls.lpszClassName = L"EffectWindow";
	wndcls.lpszMenuName = L"EffectMenu";
	if (RegisterClassEx(&wndcls))
	{
		RECT rt;
		GetWindowRect(pro_hwnd, &rt);
		effect_hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, L"EffectWindow", L"EffectMenu", WS_POPUP | WS_VISIBLE, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top - 55, NULL, NULL, NULL, NULL);
		effect_hwnd2 = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT, L"EffectWindow", L"EffectMenu", WS_POPUP | WS_VISIBLE, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top - 55, NULL, NULL, NULL, NULL);

		CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_CHILD | WS_VISIBLE,
			0, 0, 1920, 1440,
			effect_hwnd,
			(HMENU)10000,
			NULL, //(HINSTANCE)GetWindowLongPtr((HWND)lpParameter,GWLP_HWNDPARENT)
			NULL);
		CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_CHILD | WS_VISIBLE,
			0, 0, 1920, 1440,
			effect_hwnd2,
			(HMENU)10001,
			NULL, //(HINSTANCE)GetWindowLongPtr((HWND)lpParameter,GWLP_HWNDPARENT)
			NULL);

		CWnd* pCWnd = CWnd::FromHandle(effect_hwnd);
		CWnd* pWnd = pCWnd->GetDlgItem(10000);
		CStatic* cs = (CStatic*)pCWnd->GetDlgItem(10000);
		cs->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);

		MARGINS m = { 0, 0, 1920, 1440 };
		DwmExtendFrameIntoClientArea(effect_hwnd, &m);
		SetLayeredWindowAttributes(effect_hwnd, RGB(0, 0, 0), 0, LWA_ALPHA);
		ShowWindow(effect_hwnd, SW_SHOW);


		CWnd* pCWnd2 = CWnd::FromHandle(effect_hwnd2);
		CWnd* pWnd2 = pCWnd2->GetDlgItem(10001);
		CStatic* cs2 = (CStatic*)pCWnd2->GetDlgItem(10001);
		cs2->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		CImage ci;
		HRESULT ret = ci.Load(_T("./patch/0.jpg"));
		HBITMAP hBitmap2 = ci.Detach();
		cs2->SetBitmap(hBitmap2);

		MARGINS m2 = { 0, 0, 1920, 1440 };
		DwmExtendFrameIntoClientArea(effect_hwnd2, &m2);
		SetLayeredWindowAttributes(effect_hwnd2, RGB(0, 0, 0), 0, LWA_ALPHA);
		ShowWindow(effect_hwnd2, SW_SHOW);

		SetParent(effect_hwnd, pro_hwnd);
		SetParent(effect_hwnd2, pro_hwnd);

		CreateThread(NULL, 0, Effect, 0, 0, NULL);
	}
}