#pragma once
#include "pch.h"
#include "resource.h"
#include "GlobalVar.h"

void beginRandom(HWND hwnd)
{
	/*记录玩家选项*/
	bool sel[6]{ false,false,false,false,false,false };
	int total = 0;
	for (int i = 0; i < 6; i++) {
		sel[i] = IsDlgButtonChecked(hwnd, IDC_CHECK_RAND1 + i) == BST_CHECKED;
		if (sel[i] == true)
			total += pow(2, i);
	}
	if (sel[0] == false && sel[1] == true) {
		MessageBox(hwnd, __TEXT("随机失败\n如果要随机敌友兵种\n必须要勾选随机我军兵种！"), __TEXT("随机结果"), MB_OK);
		return;
	}
	srand((unsigned)time(NULL));
	WriteIn(hpro, 0x50599E, total, 1);

	/*对所有人随机*/
	int base = 0;
	ReadProcessMemory(hpro, (LPCVOID)0x4CEA00, &base, 4, 0);

	/*如果选了“我军随机”，那么就把一些矫正指令ban掉*/
	if (sel[0] == true) {
		int seed = rand() % 65535;
		WriteIn(hpro, 0x5059A0, seed, 2);
		for (int i = 0; i < 1024; i++) {
			seed = seed * 17 % 65535;
			WriteIn(hpro, base + i * 0x48 + 0x2B, seed % 80, 1);
		}
		char code[] = "90 90 90 90 90 90 90 90 90 90 90 90 ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x40C385 + i, c, 1);
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
	}

	if (sel[1] == true) WriteIn(hpro, 0x408D0E, 0x909090, 3);

	if (sel[4] == true) { 
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

	if (sel[5] == true) {
		int tianfu = 0x5089B0;
		if (version == 64)tianfu = 0x508998;
		/*for (int i = 0; i < 120; i++)
		{
			int value[3] = { 0,0,0 };
			value[0] = rand() % 200;
			value[1] = rand() % 200;
			while (value[1] == value[0])value[1] = rand() % 200;
			value[2] = rand() % 200;
			while (value[2] == value[0] || value[2] == value[1])value[2] = rand() % 200;
			WriteIn(hpro, tianfu + i * 8, value[0], 2);
			WriteIn(hpro, tianfu + i * 8 + 2, value[1], 2);
			WriteIn(hpro, tianfu + i * 8 + 4, value[2], 2);
			WriteIn(hpro, tianfu + i * 8 + 6, rand() % 80, 1);
		}*/
		int tf[120][4];
		for (int i = 0; i < 120; i++)for (int j = 0; j < 4; j++)tf[i][j] = -1;
		for (int i = 0; i < 200; i++)
		{
			int value[2] = { 0,0 };
			int times = 0;
			while (true) {
				times++;
				value[0] = rand() % 120;
				if (tf[value[0]][0] == -1) {
					tf[value[0]][0] = i;
					break;
				}
				if (tf[value[0]][1] == -1) {
					tf[value[0]][1] = i;
					break;
				}
				if (tf[value[0]][2] == -1) {
					tf[value[0]][2] = i;
					break;
				}
				if (times >= 4)break;
			}
			times = 0;
			while (true) {
				times++;
				value[1] = rand() % 120;
				if (value[0] == value[1])continue;
				if (tf[value[1]][0] == -1) {
					tf[value[1]][0] = i;
					break;
				}
				if (tf[value[1]][1] == -1) {
					tf[value[1]][1] = i;
					break;
				}
				if (tf[value[1]][2] == -1) {
					tf[value[1]][2] = i;
					break;
				}
				if (times >= 4)break;
			}
		}
		for (int i = 0; i < 80; i++) {
			int times = 0;
			while (true) {
				times++;
				int k = rand() % 120;
				if (tf[k][3] == -1) {
					tf[k][3] = i;
					break;
				}
				if (times >= 4)break;
			}
		}
		for (int i = 0; i < 120; i++) {
			for (int j = 0; j < 3; j++) {
				if (tf[i][j] != -1)
					WriteIn(hpro, tianfu + i * 8 + j * 2, tf[i][j], 2);
				else
					WriteIn(hpro, tianfu + i * 8 + j * 2, 65535, 2);
			}
			if (tf[i][3] != -1)
				WriteIn(hpro, tianfu + i * 8 + 6, tf[i][3], 1);
			else
				WriteIn(hpro, tianfu + i * 8 + 6, 255, 1);
		}
	}
	MessageBox(hwnd, __TEXT("  随机成功！"), __TEXT("随机结果"), MB_OK);
}

void initRandomDialog(HWND hWnd) {
	SetWindowTextA(hWnd, "配置随机");
	HICON hIcon = LoadIcon(exe_ins, MAKEINTRESOURCE(137));
	SendMessage(hWnd, WM_SETICON, FALSE, (LPARAM)hIcon);
}

LRESULT CALLBACK RandomDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case WM_INITDIALOG:
			initRandomDialog(hWnd);
			break;
		case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDC_BUTTON_RAND1:
				beginRandom(hWnd);
				EndDialog(hWnd, wParam);
                return TRUE;
			case IDCANCEL:
				EndDialog(hWnd, wParam);
				return TRUE;
            }
        }
	}
	return FALSE;
}
void randomDialog()
{
	if (version > 64) return;
	DialogBox(dll_ins, MAKEINTRESOURCE(IDD_DIALOGBAR1), pro_hwnd, (DLGPROC)RandomDialogProc);
}