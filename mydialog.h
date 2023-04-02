#pragma once
#include "pch.h"
#include "resource.h"
#include "GlobalVar.h"
#include <cmath>

HWND dialog_hwnd;
HWND hDlg_intab[2];	//两个要载入到TAB控件中的对话框句柄
HWND htabctrl;
HWND check1;
HWND hListview;

bool flag = false;

typedef void(*myAddProcess)(HANDLE hProcess);
typedef void(*mySetSpeed)(signed int a1);
void routine_change();

void change_page()
{
	int nSel = SendMessage(htabctrl, TCM_GETCURSEL, 0, 0L);
	if (nSel == 0)
	{
		for (int i = IDC_BACK; i <= IDC_BUTTON_GEAR2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_SHOW);
		for (int i = IDC_BACK4; i <= IDC_BUTTON_EFFECT; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK5; i <= IDC_EDIT_Opt2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK6; i <= IDC_CHECK_ROU13; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK7; i <= IDC_HOTKEY9; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
	}
	else if (nSel == 1)
	{
		for (int i = IDC_BACK; i <= IDC_BUTTON_GEAR2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK4; i <= IDC_BUTTON_EFFECT; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_SHOW);
		for (int i = IDC_BACK5; i <= IDC_EDIT_Opt2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK6; i <= IDC_CHECK_ROU13; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK7; i <= IDC_HOTKEY9; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
	}
	else if (nSel == 2)
	{
		for (int i = IDC_BACK; i <= IDC_BUTTON_GEAR2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK4; i <= IDC_BUTTON_EFFECT; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK5; i <= IDC_EDIT_Opt2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_SHOW);
		for (int i = IDC_BACK6; i <= IDC_CHECK_ROU13; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK7; i <= IDC_HOTKEY9; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
	}
	else if(nSel == 3)
	{
		for (int i = IDC_BACK; i <= IDC_BUTTON_GEAR2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK4; i <= IDC_BUTTON_EFFECT; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK5; i <= IDC_EDIT_Opt2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK6; i <= IDC_CHECK_ROU13; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_SHOW);
		for (int i = IDC_BACK7; i <= IDC_HOTKEY9; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
	}
	else
	{
		for (int i = IDC_BACK; i <= IDC_BUTTON_GEAR2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK4; i <= IDC_BUTTON_EFFECT; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK5; i <= IDC_EDIT_Opt2; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK6; i <= IDC_CHECK_ROU13; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_HIDE);
		for (int i = IDC_BACK7; i <= IDC_HOTKEY9; i++)
			ShowWindow(GetDlgItem(dialog_hwnd, i), SW_SHOW);
	}
}

void initDialog()
{
	SetWindowTextA(dialog_hwnd, "配置补丁");
	HICON hIcon = LoadIcon(exe_ins, MAKEINTRESOURCE(137));
	SendMessage(dialog_hwnd, WM_SETICON, FALSE, (LPARAM)hIcon);
	//HCURSOR hCur = LoadCursor(NULL, MAKEINTRESOURCE(9));
	//SendMessage(dialog_hwnd, WM_SETCURSOR, FALSE, (LPARAM)hCur);
	//SetCursor(hCur);

	htabctrl = GetDlgItem(dialog_hwnd, IDC_TAB1);
	TCITEM tie;
	CString tabname[5] = { L"加速配置",L"雨雪配置",L"体验优化",L"常规设置",L"快捷键"};
	tie.mask = TCIF_TEXT | TCIF_IMAGE;//psztext字段有效
	tie.iImage = -1;
	for (INT i = 0; i < 5; i++)
	{
		tie.pszText = (LPWSTR)(LPCWSTR)tabname[i];
		TabCtrl_InsertItem(htabctrl, i, &tie);
	}

	for (int i = 0; i < 6; i++)
		CheckDlgButton(dialog_hwnd, IDC_CHECK_SUPER0 + i, super_check[i]);
	for (int i = 0; i < 5; i++)
		CheckDlgButton(dialog_hwnd, IDC_CHECK_STAGE0 + i, stage_check[i]);
	flag = true;
	for (int i = 0; i < 4; i++) {
		char string[25]; _itoa_s(stage_edit[i], string, 10);
		SetWindowTextA(GetDlgItem(dialog_hwnd, IDC_EDIT_STAGE1 + i), string);
	}
	flag = false;
	CheckDlgButton(dialog_hwnd, IDC_CHECK_GEAR0, gear_check);
	char string[25]; _itoa_s(gear_edit, string, 10);
	SetWindowTextA(GetDlgItem(dialog_hwnd, IDC_EDIT_GEAR1), string);
	SendMessage(GetDlgItem(dialog_hwnd,IDC_SLIDER_GEAR), TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(0, 16));
	int pos = 0;
	if (gear_edit == 0) pos = 8;
	else if (gear_edit > 0) pos = log2(gear_edit) + 9;
	else pos = -log2(-gear_edit) + 7;
	SendMessage(GetDlgItem(dialog_hwnd, IDC_SLIDER_GEAR), TBM_SETPOS, (WPARAM)1, (LPARAM)pos);


	for (int i = 0; i < 7; i++)
		CheckDlgButton(dialog_hwnd, IDC_CHECK_EFFECT0 + i, effect_check[i]);
	flag = true;
	for (int i = 0; i < 6; i++) {
		char string[25]; _itoa_s(effect_edit[i], string, 10);
		SetWindowTextA(GetDlgItem(dialog_hwnd, IDC_EDIT_EFFECT1 + i), string);
	}
	flag = false;
	SendMessage(GetDlgItem(dialog_hwnd, IDC_SLIDER_EFFECT), TBM_SETRANGE, (WPARAM)1, (LPARAM)MAKELONG(0, 255));
	SendMessage(GetDlgItem(dialog_hwnd, IDC_SLIDER_EFFECT), TBM_SETPOS, (WPARAM)1, (LPARAM)effect_edit[6]);


	for (int i = 0; i < 19; i++)
		CheckDlgButton(dialog_hwnd, IDC_CHECK_Opt1 + i, opt_check[i]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt7), false);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt9), opt_check[7]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt11), opt_check[9]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt13), !opt_check[13] & !opt_check[14] & !opt_check[15]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt14), !opt_check[12] & !opt_check[14] & !opt_check[15]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt15), !opt_check[12] & !opt_check[13] & !opt_check[15]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt16), !opt_check[12] & !opt_check[13] & !opt_check[14]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt17), opt_check[12] | opt_check[13] | opt_check[14] | opt_check[15]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt18), opt_check[12] | opt_check[13] | opt_check[14] | opt_check[15]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt19), opt_check[12] | opt_check[13] | opt_check[14] | opt_check[15]);
	flag = true;
	for (int i = 0; i < 2; i++) {
		char string[25]; _itoa_s(opt_edit[i], string, 10);
		SetWindowTextA(GetDlgItem(dialog_hwnd, IDC_EDIT_Opt1 + i), string);
	}
	flag = false;

	routine_change();
	for (int i = 0; i < 13; i++)
		CheckDlgButton(dialog_hwnd, IDC_CHECK_ROU1 + i, rou_check[i]);
	if (version == 62)
	{
		EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_ROU9), false);
		EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_ROU10), false);
		EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_ROU11), false);
	}

	flag = true;
	for (int i = 0; i < 9; i++) {
		SendMessage(GetDlgItem(dialog_hwnd, IDC_HOTKEY1 + i), HKM_SETHOTKEY, hot_key[i], 0);
	}
	flag = false;

	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_STAGE0), !super_check[0]);
	EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_SUPER0), !stage_check[0]);
	if (version > 64) {
		EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt13), false);
		EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt14), false);
		EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt15), false);
		EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt16), false);
	}

	change_page();

}

//超级加速开启
void super_speed() {
	if (super_check[0]) {
		/*跳对话*/
		if (super_check[1]) {
			if (version != 64)
				WriteIn(hpro, 0x42D5D3, 0xC3, 1);
			else
				WriteIn(hpro, 0x42D5B0, 0x000CC2, 3);
		}
		else {
			if (version != 64)
				WriteIn(hpro, 0x42D5D3, 0x55, 1);
			else
				WriteIn(hpro, 0x42D5B0, 0xEC8B55, 3);
		}
		/*跳地图文字*/
		if (super_check[2])
			WriteIn(hpro, 0x4327EF, 0x0010C2, 3);
		else
			WriteIn(hpro, 0x4327EF, 0xEC8B55, 3);
		/*跳延时*/
		if (super_check[3]) {
			if (version != 61)
				WriteIn(hpro, 0x40A985, 0x0004C2, 3);
			else
				WriteIn(hpro, 0x40A986, 0x0004C2, 3);
		}
		else {
			if (version != 61)
				WriteIn(hpro, 0x40A985, 0xEC8B55, 3);
			else
				WriteIn(hpro, 0x40A986, 0xEC8B55, 3);
		}

		/*跳R动作*/
		if (super_check[4]) {
			WriteIn(hpro, 0x429965, 0x90909090, 4);
			WriteIn(hpro, 0x429965 + 4, 0x90, 1);
		}
		else {
			WriteIn(hpro, 0x429965, 0x002B76E8, 4);
			WriteIn(hpro, 0x429965 + 4, 0x00, 1);
		}

		/*跳S动作、旁白*/
		if (super_check[5]) {
			WriteIn(hpro, 0x42C4E8, 0x90909090, 4);
			WriteIn(hpro, 0x42C4E8 + 4, 0xEB909090, 4);
		}
		else {
			if (version >= 63) {
				WriteIn(hpro, 0x42C4E8, 0xFF6646E8, 4);
				WriteIn(hpro, 0x42C4E8 + 4, 0x75C085FF, 4);
			}
			else {
				WriteIn(hpro, 0x42C4E8, 0x003303E8, 4);
				WriteIn(hpro, 0x42C4E8 + 4, 0x75C08500, 4);
			}
		}
	}
	else
	{
		if (version != 64)
			WriteIn(hpro, 0x42D5D3, 0x55, 1);
		else
			WriteIn(hpro, 0x42D5B0, 0xEC8B55, 3);
		WriteIn(hpro, 0x4327EF, 0xEC8B55, 3);
		if (version != 61)
			WriteIn(hpro, 0x40A985, 0xEC8B55, 3);
		else
			WriteIn(hpro, 0x40A986, 0xEC8B55, 3);
		WriteIn(hpro, 0x429965, 0x002B76E8, 4);
		WriteIn(hpro, 0x429965 + 4, 0x00, 1);

		if (version >= 63) {
			WriteIn(hpro, 0x42C4E8, 0xFF6646E8, 4);
			WriteIn(hpro, 0x42C4E8 + 4, 0x75C085FF, 4);
		}
		else
		{
			WriteIn(hpro,  0x42C4E8, 0x003303E8, 4);
			WriteIn(hpro,  0x42C4E8 + 4, 0x75C08500, 4);
		}
	}
}

void stage_speed()
{
	if (stage_check[0])
	{
		WriteIn(hpro, 0x475200, stage_edit[0], 4);
		WriteIn(hpro, 0x475204, stage_edit[1], 4);
		WriteIn(hpro, 0x475208, stage_edit[2], 4);
		if (!stage_check[1])WriteIn(hpro, 0x475200, 80, 4);
		if (!stage_check[2])WriteIn(hpro, 0x475204, 80, 4);
		if (!stage_check[3])WriteIn(hpro, 0x475208, 80, 4);
		char code[] = "55 8B EC 51 0F B7 0D 53 0F 50 00 0F B6 C1 50 B9 00 52 47 00 A0 18 3D 4B 00 8B 04 81 90 90 90 90 "
			"90 90 90 90 90 90 90 83 F8 32 7E 06 83 E8 32 50 EB 25 FF 05 0C 52 47 00 39 05 0C 52 47 00 7C 04 "
			"6A 00 EB 02 6A 01 83 3D 0C 52 47 00 32 7C 08 83 2D 0C 52 47 00 32 90 E8 B0 47 FB FF 83 7D F8 00 "
			"75 08 8B 4D FC E8 31 73 FB FF B8 01 00 00 00 8B E5 5D C3 ";
		WriteIn(hpro,0x42C4E9, 0x00048BEE, 4);
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x4750DB + i, c, 1);
		}
	}
	else
	{
		if (version >= 63)
			WriteIn(hpro, 0x42C4E9, 0xFFFF6646, 4);
		else
			WriteIn(hpro, 0x42C4E9, 0x00003303, 4);
	}
}


void gear_speed()
{
	if (gear_check)
	{
		mySetSpeed procAddress2 = (mySetSpeed)GetProcAddress(gearModule, "SetSpeed");
		procAddress2(gear_edit);
	}
	else
	{
		mySetSpeed procAddress2 = (mySetSpeed)GetProcAddress(gearModule, "SetSpeed");
		procAddress2(0);
	}
}

void gear_speed_change()
{
	gear_check = IsDlgButtonChecked(dialog_hwnd, IDC_CHECK_GEAR0) == BST_CHECKED;
	TCHAR ch[10]; CString str;
	GetWindowText(GetDlgItem(dialog_hwnd, IDC_EDIT_GEAR1), ch, 1024);
	str.Format(TEXT("%s"), ch);
	for (int i = 0; i < str.GetLength(); i++)
		if (str[i] >= '0' && str[i] <= '9')continue;
		else if (str[i] == '-')continue;
		else return;
	gear_edit = _wtoi(str);
	int pos = 0;
	if (gear_edit == 0) pos = 8;
	else if (gear_edit > 0) pos = log2(gear_edit) + 9;
	else pos = -log2(-gear_edit) + 7;
	SendMessage(GetDlgItem(dialog_hwnd, IDC_SLIDER_GEAR), TBM_SETPOS, (WPARAM)1, (LPARAM)pos);
	gear_speed();
}

void optimization()
{
	//暴击不语
	if (opt_check[0] == true)
	{
		if (version == 62) WriteIn(hpro, 0x4527A6, 0, 1);
		else if (version == 63) WriteIn(hpro, 0x45278C, 0, 1);
		else if (version == 64) WriteIn(hpro, 0x452789, 0, 1);
	}
	else
	{
		if (version == 62) WriteIn(hpro, 0x4527A6, 0x32, 1);
		else if (version == 63) WriteIn(hpro, 0x45278C, 0x32, 1);
		else if (version == 64) WriteIn(hpro, 0x452789, 0x32, 1);
	}

	//省略攻击动作
	if (opt_check[1] == true)
	{
		WriteIn(hpro, 0x404388, 0xC3, 1);
		if (version == 64)
			WriteIn(hpro, 0x4214A1, 0xC3, 1);
		else
			WriteIn(hpro, 0x4214C9, 0xC3, 1);
	}
	else
	{
		WriteIn(hpro, 0x404388, 0x55, 1);
		if (version == 64)
			WriteIn(hpro, 0x4214A1, 0x55, 1);
		else
			WriteIn(hpro, 0x4214C9, 0x55, 1);
	}

	//buff固定三回合
	if (opt_check[2] == true){
		for (int i = 0x43C9A2; i <= 0x43C9B6; i++) WriteIn(hpro, i, 0x90, 1);
	}
	else {
		char code[] = "6A 00 FF 75 FC EB 05 6A 01 FF 75 F8 E8 E3 AE FF FF 85 C0 74 BC ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x43C9A2 + i, c, 1);
		}
	}

	//取消浮动伤害
	if (opt_check[3] == true) {
		if (version == 62)
			WriteIn(hpro, 0x43BEC1, 0, 1);
		else
			WriteIn(hpro, 0x412CC7, 0, 1);
	}
	else {
		if (version == 62)
			WriteIn(hpro, 0x43BEC1, 7, 1);
		else
			WriteIn(hpro, 0x412CC7, 7, 1);
	}

	//血条显示比例
	if (version == 62)
		WriteIn(hpro, 0x43EC2D, opt_edit[0] * 2 / 5 + 1, 1);
	else
		WriteIn(hpro, 0x43EC50, opt_edit[0] * 2 / 5 + 1, 1);

	//功勋加成
	if (version == 62)
		WriteIn(hpro, 0x45EA79, opt_edit[1], 1);
	else
		WriteIn(hpro, 0x44D52E, opt_edit[1], 1);

	//ctrl改shift
	if (opt_check[4] == true) {
		WriteIn(hpro, 0x413324, 0x10, 1);
	}
	else
	{
		if (version != 64)
			WriteIn(hpro, 0x413324, 0x11, 1);
	}

	//快捷键存读档
	if (opt_check[5] == true) {
		if (version == 64) {
			char code[] = "E8 FC 7C 00 00 90 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x4132FF + i, c, 1);
			}
			char code2[] = "00 8B 45 0C 80 3D 18 3D 4B 00 00 75 3B 83 F8 70 75 07 6A 14 E8 CD 7A FF FF 83 F8 72 75 2A FE 05 FF AF 41 00 80 3D FF AF 41 00 02 7D 14 50 6A 14 E8 59 D8 FF FF B9 08 3D 4B 00 C6 41 01 05 58 EB 07 C6 05 FF AF 41 00 00 83 F8 25 C3 ";
			for (int i = 0; i < strlen(code2) / 3; i++)
			{
				int c = translate(code2[i * 3], code2[i * 3 + 1]);
				WriteIn(hpro, 0x41AFFF + i, c, 1);
			}
			WriteIn(hpro, 0x41B00E, hot_key[5], 1);
			WriteIn(hpro, 0x41B01A, hot_key[6], 1);
		}
		else if (version == 63) {
			char code[] = "E8 FC 7C 00 00 90 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x4132FF + i, c, 1);
			}
			char code2[] = "00 8B 45 0C 80 3D 18 3D 4B 00 00 75 3B 83 F8 70 75 07 6A 14 E8 CD 7A FF FF 83 F8 72 75 2A FE 05 FF AF 41 00 80 3D FF AF 41 00 02 7D 14 50 6A 14 E8 51 D8 FF FF B9 08 3D 4B 00 C6 41 01 05 58 EB 07 C6 05 FF AF 41 00 00 83 F8 25 C3 ";
			for (int i = 0; i < strlen(code2) / 3; i++)
			{
				int c = translate(code2[i * 3], code2[i * 3 + 1]);
				WriteIn(hpro, 0x41AFFF + i, c, 1);
			}
			WriteIn(hpro, 0x41B00E, hot_key[5], 1);
			WriteIn(hpro, 0x41B01A, hot_key[6], 1);
		}
		else {
			char code[] = "E8 DC 7C 00 00 90 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x41331F + i, c, 1);
			}
			char code2[] = "00 8B 45 0C 80 3D 18 3D 4B 00 00 75 3B 83 F8 70 75 07 6A 14 E8 CD 7A FF FF 83 F8 72 75 2A FE 05 FF AF 41 00 80 3D FF AF 41 00 02 7D 14 50 6A 14 E8 DC CB FF FF B9 08 3D 4B 00 C6 41 01 05 58 EB 07 C6 05 FF AF 41 00 00 83 F8 11 C3 ";
			for (int i = 0; i < strlen(code2) / 3; i++)
			{
				int c = translate(code2[i * 3], code2[i * 3 + 1]);
				WriteIn(hpro, 0x41AFFF + i, c, 1);
			}
			WriteIn(hpro, 0x41B00E, hot_key[5], 1);
			WriteIn(hpro, 0x41B01A, hot_key[6], 1);
		}
	}
	else
	{
		if (version != 62) {
			char code[] = "8B 45 0C 83 F8 25 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x4132FF + i, c, 1);
			}
		}
		else {
			char code[] = "8B 45 0C 83 F8 11 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x41331F + i, c, 1);
			}
		}
	}

	//结束回合提示
	if (opt_check[7] == true)
	{
		char code[] = "B8 00 00 00 00 90 90 90 90 90 90 90 90 90 90 ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x44E602 + i, c, 1);
		}
		if (opt_check[8] == true)
			WriteIn(hpro, 0x44E603, 1, 1);
	}
	else
	{
		char code[] = "68 20 E1 48 00 6A 01 E8 8B 10 FE FF 83 C4 08 ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x44E602 + i, c, 1);
		}
	}

	//战前换位
	if (opt_check[9] == true)
	{
		char code[] = "50 FF 75 DC E8 BC B9 01 00 ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x43D79C + i, c, 1);
		}
		char code2[] = "55 8B EC 83 EC 20 8B 4D 0C E8 8A D0 FA FF 8A 41 05 3C 00 90 0F 85 FA 00 00 00 89 4D F8 A0 0A 3D "
			"4B 00 3C 00 0F 85 EA 00 00 00 B3 00 8A CB 90 E8 64 D0 FA FF 8B 01 3D FF FF 00 00 74 16 8A 41 05 "
			"3C 00 75 13 8A 49 0D 80 E1 06 80 F9 00 0F 85 C1 00 00 00 FE C3 EB D5 8B 45 08 2D 50 2C 4B 00 B9 "
			"24 00 00 00 F6 F9 25 FF 00 00 00 8A 80 B8 4E 50 00 3C 01 0F 84 9B 00 00 00 8B 4D 0C 8A 81 B8 4E "
			"50 00 3C 01 0F 84 8A 00 00 00 8B 45 08 89 45 FC 8B 48 06 89 4D F4 8B 4D 0C E8 FA CF FA FF 8B 41 "
			"06 89 4D F8 8B 41 06 89 45 F0 8B 45 F4 8B 4D F8 66 89 41 06 8B 45 F0 8B 4D FC 66 89 41 06 FF 75 "
			"F4 E8 62 A5 FA FF 50 E8 3C 84 FA FF 59 8B 94 08 80 0C 00 00 8D 9C 08 80 0C 00 00 89 5D EC 89 55 "
			"E4 FF 75 F0 E8 3F A5 FA FF 50 E8 19 84 FA FF 59 8B 94 08 80 0C 00 00 8D 9C 08 80 0C 00 00 89 5D "
			"E8 89 55 E0 8B 45 EC 8B 4D E0 88 08 8B 45 E8 8B 4D E4 88 08 8B E5 5D 83 C4 0C E9 EE 46 FE FF ";
		for (int i = 0; i < strlen(code2) / 3; i++)
		{
			int c = translate(code2[i * 3], code2[i * 3 + 1]);
			WriteIn(hpro, 0x459161 + i, c, 1);
		}
		if (version == 62)
		{
			char code3[] = "E9 FB C5 00 00 90 90 ";
			for (int i = 0; i < strlen(code3) / 3; i++)
			{
				int c = translate(code3[i * 3], code3[i * 3 + 1]);
				WriteIn(hpro, 0x415BA5 + i, c, 1);
			}
			char code4[] = "E9 AC C3 00 00 90 90 ";
			for (int i = 0; i < strlen(code4) / 3; i++)
			{
				int c = translate(code4[i * 3], code4[i * 3 + 1]);
				WriteIn(hpro, 0x415DCF + i, c, 1);
			}
			char code5[] = "3E 89 04 95 60 0F 50 00 3D FF FF 00 00 75 09 C6 82 B8 4E 50 00 00 EB 07 C6 82 B8 4E 50 00 01 E9 30 3C FF FF 90 89 04 95 60 0F 50 00 83 7D F8 00 74 17 3D FF FF 00 00 75 09 C6 82 B8 4E 50 00 00 EB 07 C6 82 B8 4E 50 00 01 E9 DC 39 FF FF ";
			for (int i = 0; i < strlen(code5) / 3; i++)
			{
				int c = translate(code5[i * 3], code5[i * 3 + 1]);
				WriteIn(hpro, 0x422180 + i, c, 1);
			}
		}
		else if (version == 63)
		{
			char code3[] = "E9 64 C4 00 00 90 90 ";
			for (int i = 0; i < strlen(code3) / 3; i++)
			{
				int c = translate(code3[i * 3], code3[i * 3 + 1]);
				WriteIn(hpro, 0x415BA5 + i, c, 1);
			}
			char code4[] = "E9 15 C2 00 00 90 90 ";
			for (int i = 0; i < strlen(code4) / 3; i++)
			{
				int c = translate(code4[i * 3], code4[i * 3 + 1]);
				WriteIn(hpro, 0x415DCF + i, c, 1);
			}
			char code5[] = "3E 89 04 95 60 0F 50 00 3D FF FF 00 00 75 09 C6 82 B8 4E 50 00 00 EB 07 C6 82 B8 4E 50 00 01 E9 C7 3D FF FF 90 89 04 95 60 0F 50 00 83 7D F8 00 74 17 3D FF FF 00 00 75 09 C6 82 B8 4E 50 00 00 EB 07 C6 82 B8 4E 50 00 01 E9 73 3B FF FF ";
			for (int i = 0; i < strlen(code5) / 3; i++)
			{
				int c = translate(code5[i * 3], code5[i * 3 + 1]);
				WriteIn(hpro, 0x421FE9 + i, c, 1);
			}
		}
		else if (version == 64)
		{
			char code3[] = "E9 AB E0 00 00 90 90 90 ";
			for (int i = 0; i < strlen(code3) / 3; i++)
			{
				int c = translate(code3[i * 3], code3[i * 3 + 1]);
				WriteIn(hpro, 0x415B9E + i, c, 1);
			}
			char code4[] = "E9 AB DE 00 00 90 90 90 ";
			for (int i = 0; i < strlen(code4) / 3; i++)
			{
				int c = translate(code4[i * 3], code4[i * 3 + 1]);
				WriteIn(hpro, 0x415DC2 + i, c, 1);
			}
			char code5[] = "3E 89 04 55 DC 09 4B 00 3D FF FF 00 00 75 09 C6 82 B8 4E 50 00 00 EB 07 C6 82 B8 4E 50 00 01 E9 31 1F FF FF 3E 89 04 55 DC 09 4B 00 83 7D F8 00 74 17 3D FF FF 00 00 75 09 C6 82 B8 4E 50 00 00 EB 07 C6 82 B8 4E 50 00 01 E9 2B 21 FF FF ";
			for (int i = 0; i < strlen(code5) / 3; i++)
			{
				int c = translate(code5[i * 3], code5[i * 3 + 1]);
				WriteIn(hpro, 0x423C4E + i, c, 1);
			}
			char code6[] = "2D 20 7B 4A 00 B9 30 00 00 00 F6 F9 ";
			for (int i = 0; i < strlen(code6) / 3; i++)
			{
				int c = translate(code6[i * 3], code6[i * 3 + 1]);
				WriteIn(hpro, 0x4591BB + i, c, 1);
			}
		}
	}
	else
	{
		char code[] = "90 90 90 90 90 90 90 90 90 ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x43D79C + i, c, 1);
		}
	}

	//战前仓库
	if (opt_check[10] == true)
	{
		char code[] = "E8 0E BB 01 00 90 90 90 90 90 90 90 90 90 90 ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x43D7ED + i, c, 1);
		}
		char code2[] = "55 8B EC 83 EC 20 A0 0A 3D 4B 00 3C 00 75 36 90 90 90 90 B3 00 8A CB 90 E8 DC CE FA FF 8B 01 3D FF FF 00 00 74 16 8A 41 05 3C 00 75 13 8A 49 0D 80 E1 06 80 F9 00 75 0D 90 90 90 90 FE C3 EB D5 E8 4A 89 00 00 8B E5 5D C3 ";
		for (int i = 0; i < strlen(code2) / 3; i++)
		{
			int c = translate(code2[i * 3], code2[i * 3 + 1]);
			WriteIn(hpro, 0x459300 + i, c, 1);
		}
		if (version == 64)
			WriteIn(hpro, 0x459341, 0x43, 1);
	}
	else
	{
		char code[] = "68 C8 DF 48 00 6A 02 E8 A0 1E FF FF 83 C4 08 ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x43D7ED + i, c, 1);
		}
	}

	//仓管不语
	if (opt_check[11] == true)
	{
		if (version == 62)
			for (int i = 0x4198AB; i <= 0x4198C9; i++)
				WriteIn(hpro, i, 0x90, 1);
		else
			for (int i = 0x419796; i <= 0x4197B1; i++)
				WriteIn(hpro, i, 0x90, 1);
	}
	else
	{
		if (version == 62) {
			char code[] = "6A 00 6A 00 8D 45 9C 50 E8 1B 3D 01 00 90 90 90 6A 00 FF 75 98 68 BC B4 48 00 E8 09 3D 01 00 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x4198AB + i, c, 1);
			}
		}
		else if (version == 63) {
			char code[] = "6A 00 6A 00 8D 55 D0 52 E8 30 3E 01 00 6A 00 FF 75 CC 68 96 B4 48 00 E8 21 3E 01 00 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x419796 + i, c, 1);
			}
		}
		else if (version >= 64) {
			char code[] = "6A 00 6A 00 8D 55 D0 52 E8 0D 3E 01 00 6A 00 FF 75 CC 68 96 B4 48 00 E8 FE 3D 01 00 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x419796 + i, c, 1);
			}
		}
	}

	if (version > 64)
		return;

	int num = 0; bool show_jiqi = true;
	ReadProcessMemory(hpro, (LPVOID)0x413218, &num, 1, 0);
	if (num == 0x90)show_jiqi = false;
	else show_jiqi = true;  //是否写了辅助克制

	//集气系统
	if (opt_check[12] | opt_check[13] | opt_check[14] | opt_check[15])
	{
		WriteIn(hpro, 0x43B4FD, 0x65, 1);

		//如果开了显示集气
		if (opt_check[18]) {
			WriteIn(hpro, 0x4131D4, 0x28, 1);
			WriteIn(hpro, 0x4131FB, 0xE0, 1);
			WriteIn(hpro, 0x413206, 0xE4, 1);
			if (show_jiqi) {
				WriteIn(hpro, 0x41322C, 0xE8, 1);
				WriteIn(hpro, 0x41323E, 0xEC, 1);
			}
			else {
				WriteIn(hpro, 0x413214, 0xE8, 1);
				WriteIn(hpro, 0x413217, 0xEC, 1);
			}
			char code[] = "E9 85 61 04 00 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x41323F + i, c, 1);
			}
			if (version <= 63) {
				char code2[] = "75 0D 80 3D 33 0E 50 00 01 75 04 83 45 C8 02 90 90 89 4D D8 E8 B9 60 FC FF 89 4D F0 FF 75 0C 8B 45 C8 40 50 6A 04 8B 4D D8 FF 71 06 8D 55 E4 52 E8 59 F7 00 00 8A 45 E5 88 45 F8 8A 45 E4 88 45 F4 E8 D8 E0 FD FF ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x4404BD + i, c, 1);
				}
			}
			else {
				char code2[] = "75 0D 80 3D 68 1A 50 00 01 75 04 83 45 C8 02 90 90 89 4D D8 E8 B8 60 FC FF 89 4D F0 FF 75 0C 8B 45 C8 40 50 6A 04 8B 4D D8 FF 71 06 8D 55 E4 52 E8 58 F7 00 00 8A 45 E5 88 45 F8 8A 45 E4 88 45 F4 E8 D7 E0 FD FF ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x4404BE + i, c, 1);
				}
			}
			char code3[] = "C7 45 DC 00 00 00 00 8B 45 08 89 45 D8 8B 45 14 2D 50 2C 4B 00 B9 24 00 00 00 F6 F1 8A 88 B0 56 50 00 89 4D F0 8A 88 AA 57 50 00 89 4D F4 8B 45 10 2D 50 2C 4B 00 B9 24 00 00 00 F6 F1 8A 88 A4 58 50 00 89 4D F8 EB 03 FF 45 DC 8B 45 DC 3C 07 73 44 6B C8 05 81 C1 BC E9 48 00 51 83 7D DC 04 7D 04 6A 36 EB 02 6A 50 90 90 FF 74 85 E0 6A 12 FF 75 0C FF 75 D8 E8 FE 8F FA FF 83 45 D8 0B 8B 45 DC 83 E0 01 83 F8 01 75 BE 83 45 0C 17 8B 45 08 89 45 D8 EB B2 E9 1A 9E FB FF ";
			for (int i = 0; i < strlen(code3) / 3; i++)
			{
				int c = translate(code3[i * 3], code3[i * 3 + 1]);
				WriteIn(hpro, 0x4593C9 + i, c, 1);
			}
		}
		//如果关了显示集气
		else {
			WriteIn(hpro, 0x4131D4, 0x14, 1);
			WriteIn(hpro, 0x4131FB, 0xEC, 1);
			WriteIn(hpro, 0x413206, 0xF0, 1);
			if (show_jiqi) {
				WriteIn(hpro, 0x41322C, 0xF4, 1);
				WriteIn(hpro, 0x41323E, 0xF8, 1);
			}
			else {
				WriteIn(hpro, 0x413214, 0xF4, 1);
				WriteIn(hpro, 0x413217, 0xF8, 1);
			}
			char code[] = "EB 03 FF 45 E8 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x41323F + i, c, 1);
			}
			if (version <= 63) {
				char code2[] = "75 0C 80 3D 33 0E 50 00 01 75 03 FF 45 C8 89 4D D8 E8 BC 60 FC FF 89 4D F0 FF 75 0C 8B 45 C8 40 50 6A 04 8B 4D D8 FF 71 06 8D 55 E4 52 E8 5C F7 00 00 8A 45 E5 88 45 F8 8A 45 E4 88 45 F4 E8 DB E0 FD FF 90 90 90 ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x4404BD + i, c, 1);
				}
			}
			else {
				char code2[] = "75 0C 80 3D 68 1A 50 00 01 75 03 FF 45 C8 89 4D D8 E8 BB 60 FC FF 89 4D F0 FF 75 0C 8B 45 C8 40 50 6A 04 8B 4D D8 FF 71 06 8D 55 E4 52 E8 5B F7 00 00 8A 45 E5 88 45 F8 8A 45 E4 88 45 F4 E8 DA E0 FD FF 90 90 ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x4404BE + i, c, 1);
				}
			}
		}


		char code4[] = "C1 AC BB F7 00 B1 A9 BB F7 00 BF CB D6 C6 00 B1 BB BF CB 00 C1 AC C6 F8 00 B1 A9 C6 F8 00 B5 B2 C6 F8 00 ";
		for (int i = 0; i < strlen(code4) / 3; i++)
		{
			int c = translate(code4[i * 3], code4[i * 3 + 1]);
			WriteIn(hpro, 0x48E9BC + i, c, 1);
		}
		if (version >= 63) {
			char code5[] = "E9 EA 7F 05 00 90 90 90 ";
			for (int i = 0; i < strlen(code5) / 3; i++)
			{
				int c = translate(code5[i * 3], code5[i * 3 + 1]);
				WriteIn(hpro, 0x40612D + i, c, 1);
			}
			char code6[1000];
			memset(code6, 0, 1000);
			if (opt_check[12]) strcpy(code6, "50 6A 00 50 E8 71 97 FD FF 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 B0 56 50 00 80 FA 64 72 0C 80 A9 B0 56 50 00 64 B0 01 5A EB 15 3C 01 75 0A C6 81 B0 56 50 00 00 5A EB 07 5A 00 91 B0 56 50 00 E9 D0 7F FA FF 50 83 F8 64 72 05 B8 64 00 00 00 6A 00 50 E8 21 97 FD FF 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 AA 57 50 00 80 FA 64 72 0C 80 A9 AA 57 50 00 64 B0 01 5A EB 15 3C 01 75 0A C6 81 AA 57 50 00 00 5A EB 07 5A 00 91 AA 57 50 00 E9 2D 7D FA FF 8B 45 FC 50 6A 00 50 E8 D8 96 FD FF 8A 0D F1 27 49 00 81 E1 FF 00 00 00 8A 91 A4 58 50 00 80 FA 64 72 0C 80 A9 A4 58 50 00 64 B0 00 5A EB 19 3C 00 75 0A C6 81 A4 58 50 00 00 5A EB 0B 5A B3 64 2A DA 00 99 A4 58 50 00 E9 F2 D2 FD FF ");
			else if (opt_check[13]) strcpy(code6, "50 6A 00 50 E8 71 97 FD FF 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 B0 56 50 00 5B 02 D3 80 FA 64 72 09 B0 01 EB 09 90 90 90 EB 15 3C 01 75 0A C6 81 B0 56 50 00 00 90 EB 07 90 00 99 B0 56 50 00 E9 D0 7F FA FF 50 83 F8 64 72 05 B8 64 00 00 00 6A 00 50 E8 21 97 FD FF 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 AA 57 50 00 5B 02 D3 80 FA 64 72 09 B0 01 EB 09 90 90 90 EB 15 3C 01 75 0A C6 81 AA 57 50 00 00 90 EB 07 90 00 99 AA 57 50 00 E9 2D 7D FA FF 8B 45 FC 50 6A 00 50 E8 D8 96 FD FF 8A 0D F1 27 49 00 81 E1 FF 00 00 00 8A 91 A4 58 50 00 5B 80 C2 64 2A D3 80 FA 64 72 06 B0 00 EB 06 EB 19 3C 00 75 0A C6 81 A4 58 50 00 00 90 EB 0B 90 B2 64 2A D3 00 91 A4 58 50 00 E9 F2 D2 FD FF ");
			else if (opt_check[14]) strcpy(code6, "8B D8 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 B0 56 50 00 02 D3 80 FA 64 72 07 B0 01 80 EA 64 EB 02 B0 00 80 3D F8 2D 49 00 01 7D 0A 88 91 B0 56 50 00 90 90 90 90 E9 DA 7F FA FF 90 90 90 90 90 90 90 90 90 90 8B D8 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 AA 57 50 00 02 D3 80 FA 64 72 07 B0 01 80 EA 64 EB 02 B0 00 88 91 AA 57 50 00 90 90 90 90 90 90 90 90 90 90 90 90 90 E9 41 7D FA FF 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 8B 5D FC 8A 0D F1 27 49 00 81 E1 FF 00 00 00 8A 91 A4 58 50 00 80 C2 64 2A D3 80 FA 64 72 07 B0 00 80 EA 64 EB 02 B0 01 88 91 A4 58 50 00 90 90 90 90 90 90 90 90 E9 04 D3 FD FF ");
			else if (opt_check[15]) strcpy(code6, "8B D8 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 B0 56 50 00 02 D0 80 E2 FF 6A 00 52 E8 59 97 FD FF 3C 01 75 09 C6 81 B0 56 50 00 00 EB 0F 80 3D F8 2D 49 00 01 7D 06 00 99 B0 56 50 00 E9 D4 7F FA FF 90 90 90 90 8B D8 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 AA 57 50 00 02 D0 80 E2 FF 6A 00 52 E8 13 97 FD FF 3C 01 75 09 C6 81 AA 57 50 00 00 EB 06 00 99 AA 57 50 00 E9 44 7D FA FF 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 8B 45 FC 50 6A 00 50 E8 D8 96 FD FF 8A 0D F1 27 49 00 81 E1 FF 00 00 00 8A 91 A4 58 50 00 5B 80 C2 64 2A D3 80 FA 64 72 06 B0 00 EB 06 EB 19 3C 00 75 0A C6 81 A4 58 50 00 00 90 EB 0B 90 B2 64 2A D3 00 91 A4 58 50 00 E9 F2 D2 FD FF ");
			for (int i = 0; i < strlen(code6) / 3; i++)
			{
				int c = translate(code6[i * 3], code6[i * 3 + 1]);
				WriteIn(hpro, 0x45E11C + i, c, 1);
			}
			char code7[] = "90 90 90 90 90 E9 83 82 05 00 90 90 90 ";
			for (int i = 0; i < strlen(code7) / 3; i++)
			{
				int c = translate(code7[i * 3], code7[i * 3 + 1]);
				WriteIn(hpro, 0x405ED5 + i, c, 1);
			}
		}
		else {
			char code5[] = "E9 F3 80 05 00 90 90 90 ";
			for (int i = 0; i < strlen(code5) / 3; i++)
			{
				int c = translate(code5[i * 3], code5[i * 3 + 1]);
				WriteIn(hpro, 0x40612D + i, c, 1);
			}
			char code6[1000];
			memset(code6, 0, 1000);
			if (opt_check[12]) strcpy(code6, "50 83 F8 64 72 05 B8 64 00 00 00 6A 00 50 E8 21 97 FD FF 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 AA 57 50 00 80 FA 64 72 0C 80 A9 AA 57 50 00 64 B0 01 5A EB 15 3C 01 75 0A C6 81 AA 57 50 00 00 5A EB 07 5A 00 91 AA 57 50 00 E9 2D 7D FA FF 8B 45 FC 50 6A 00 50 E8 D8 96 FD FF 8A 0D F1 27 49 00 81 E1 FF 00 00 00 8A 91 A4 58 50 00 80 FA 64 72 0C 80 A9 A4 58 50 00 64 B0 00 5A EB 19 3C 00 75 0A C6 81 A4 58 50 00 00 5A EB 0B 5A B3 64 2A DA 00 99 A4 58 50 00 E9 F2 D2 FD FF ");
			else if (opt_check[13]) strcpy(code6, "50 83 F8 64 72 05 B8 64 00 00 00 6A 00 50 E8 21 97 FD FF 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 AA 57 50 00 5B 02 D3 80 FA 64 72 09 B0 01 EB 09 90 90 90 EB 15 3C 01 75 0A C6 81 AA 57 50 00 00 90 EB 07 90 00 99 AA 57 50 00 E9 2D 7D FA FF 8B 45 FC 50 6A 00 50 E8 D8 96 FD FF 8A 0D F1 27 49 00 81 E1 FF 00 00 00 8A 91 A4 58 50 00 5B 80 C2 64 2A D3 80 FA 64 72 06 B0 00 EB 06 EB 19 3C 00 75 0A C6 81 A4 58 50 00 00 90 EB 0B 90 B2 64 2A D3 00 91 A4 58 50 00 E9 F2 D2 FD FF ");
			else if (opt_check[14]) strcpy(code6, "8B D8 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 AA 57 50 00 02 D3 80 FA 64 72 07 B0 01 80 EA 64 EB 02 B0 00 88 91 AA 57 50 00 90 90 90 90 90 90 90 90 90 90 90 90 90 E9 41 7D FA FF 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 8B 5D FC 8A 0D F1 27 49 00 81 E1 FF 00 00 00 8A 91 A4 58 50 00 80 C2 64 2A D3 80 FA 64 72 07 B0 00 80 EA 64 EB 02 B0 01 88 91 A4 58 50 00 90 90 90 90 90 90 90 90 E9 04 D3 FD FF ");
			else if (opt_check[15]) strcpy(code6, "8B D8 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 AA 57 50 00 02 D0 80 E2 FF 6A 00 52 E8 13 97 FD FF 3C 01 75 09 C6 81 AA 57 50 00 00 EB 06 00 99 AA 57 50 00 E9 44 7D FA FF 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 90 8B 45 FC 50 6A 00 50 E8 D8 96 FD FF 8A 0D F1 27 49 00 81 E1 FF 00 00 00 8A 91 A4 58 50 00 5B 80 C2 64 2A D3 80 FA 64 72 06 B0 00 EB 06 EB 19 3C 00 75 0A C6 81 A4 58 50 00 00 90 EB 0B 90 B2 64 2A D3 00 91 A4 58 50 00 E9 F2 D2 FD FF ");
			for (int i = 0; i < strlen(code6) / 3; i++)
			{
				int c = translate(code6[i * 3], code6[i * 3 + 1]);
				WriteIn(hpro, 0x45E162 + i, c, 1);
			}
			char code62[1000];
			memset(code62, 0, 1000);
			if (opt_check[12]) strcpy(code62, "50 6A 00 50 E8 68 96 FD FF 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 B0 56 50 00 80 FA 64 72 0C 80 A9 B0 56 50 00 64 B0 01 5A EB 15 3C 01 75 0A C6 81 B0 56 50 00 00 5A EB 07 5A 00 91 B0 56 50 00 E9 C7 7E FA FF ");
			else if (opt_check[13]) strcpy(code62, "50 6A 00 50 E8 68 96 FD FF 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 B0 56 50 00 5B 02 D3 80 FA 64 72 09 B0 01 EB 09 90 90 90 EB 15 3C 01 75 0A C6 81 B0 56 50 00 00 90 EB 07 90 00 99 B0 56 50 00 E9 C7 7E FA FF ");
			else if (opt_check[14]) strcpy(code62, "8B D8 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 B0 56 50 00 02 D3 80 FA 64 72 07 B0 01 80 EA 64 EB 02 B0 00 80 3D F8 2D 49 00 01 7D 0A 88 91 B0 56 50 00 90 90 90 90 E9 D1 7E FA FF ");
			else if (opt_check[15]) strcpy(code62, "8B D8 8A 0D F0 27 49 00 81 E1 FF 00 00 00 8A 91 B0 56 50 00 02 D0 80 E2 FF 6A 00 52 E8 50 96 FD FF 3C 01 75 09 C6 81 B0 56 50 00 00 EB 0F 80 3D F8 2D 49 00 01 7D 06 00 99 B0 56 50 00 E9 CB 7E FA FF ");
			for (int i = 0; i < strlen(code62) / 3; i++)
			{
				int c = translate(code62[i * 3], code62[i * 3 + 1]);
				WriteIn(hpro, 0x45E225 + i, c, 1);
			}
			char code7[] = "90 90 E9 83 82 05 00 90 90 90 90 90 90 ";
			for (int i = 0; i < strlen(code7) / 3; i++)
			{
				int c = translate(code7[i * 3], code7[i * 3 + 1]);
				WriteIn(hpro, 0x405ED8 + i, c, 1);
			}
		}
		char code8[] = "E9 C1 2C 02 00 90 90 90 90 90 ";
		for (int i = 0; i < strlen(code8) / 3; i++)
		{
			int c = translate(code8[i * 3], code8[i * 3 + 1]);
			WriteIn(hpro, 0x43B4EC + i, c, 1);
		}
		if (version == 64)
		{
			WriteIn(hpro, 0x4593DA, 0x20, 1);
			WriteIn(hpro, 0x4593DB, 0x7B, 1);
			WriteIn(hpro, 0x4593DC, 0x4A, 1);
			WriteIn(hpro, 0x4593DF, 0x30, 1);
			WriteIn(hpro, 0x4593FB, 0x20, 1);
			WriteIn(hpro, 0x4593FC, 0x7B, 1);
			WriteIn(hpro, 0x4593FD, 0x4A, 1);
			WriteIn(hpro, 0x459400, 0x30, 1);
		}

		//每关清气
		if (opt_check[16] == true) {
			if (version <= 63) {
				char code[] = "E9 F7 BF 04 00 ";
				for (int i = 0; i < strlen(code) / 3; i++)
				{
					int c = translate(code[i * 3], code[i * 3 + 1]);
					WriteIn(hpro, 0x412229 + i, c, 1);
				}
				char code2[] = "68 FF 03 00 00 B8 B0 56 50 00 C6 00 00 40 3D 9E 59 50 00 75 F5 E9 EF 3F FB FF ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x45E225 + i, c, 1);
				}
			}
			else {
				char code[] = "E9 ED BF 04 00 ";
				for (int i = 0; i < strlen(code) / 3; i++)
				{
					int c = translate(code[i * 3], code[i * 3 + 1]);
					WriteIn(hpro, 0x412233 + i, c, 1);
				}
				char code2[] = "68 FF 03 00 00 B8 B0 56 50 00 C6 00 00 40 3D 9E 59 50 00 75 F5 E9 F9 3F FB FF ";
				for (int i = 0; i < strlen(code2) / 3; i++)
				{
					int c = translate(code2[i * 3], code2[i * 3 + 1]);
					WriteIn(hpro, 0x45E225 + i, c, 1);
				}
			}
		}
		else {
			if (version <= 63) {
				char code[] = "68 FF 03 00 00 ";
				for (int i = 0; i < strlen(code) / 3; i++)
				{
					int c = translate(code[i * 3], code[i * 3 + 1]);
					WriteIn(hpro, 0x412229 + i, c, 1);
				}
			}
			else {
				char code[] = "68 FF 03 00 00 ";
				for (int i = 0; i < strlen(code) / 3; i++)
				{
					int c = translate(code[i * 3], code[i * 3 + 1]);
					WriteIn(hpro, 0x412233 + i, c, 1);
				}
			}
		}

		//亡者不鞭
		if (opt_check[17] == true) {
			if (version >= 63) {
				if (opt_check[12] || opt_check[13]) {
					char code[] = "E9 D5 00 00 00 90 ";
					for (int i = 0; i < strlen(code) / 3; i++)
					{
						int c = translate(code[i * 3], code[i * 3 + 1]);
						WriteIn(hpro, 0x45E125 + i, c, 1);
					}
					char code2[] = "8A 0D F1 27 49 00 E8 EF 7F FA FF 8B 51 10 83 FA 00 75 08 B0 00 5A E9 43 FF FF FF 8A 0D F0 27 49 00 E9 05 FF FF FF ";
					for (int i = 0; i < strlen(code2) / 3; i++)
					{
						int c = translate(code2[i * 3], code2[i * 3 + 1]);
						WriteIn(hpro, 0x45E1FF + i, c, 1);
					}
				}
				else {
					char code[] = "E9 DC 00 00 00 90 ";
					for (int i = 0; i < strlen(code) / 3; i++)
					{
						int c = translate(code[i * 3], code[i * 3 + 1]);
						WriteIn(hpro, 0x45E11E + i, c, 1);
					}
					char code2[] = "8A 0D F1 27 49 00 E8 EF 7F FA FF 8B 51 10 83 FA 00 75 08 B0 00 90 E9 36 FF FF FF 8A 0D F0 27 49 00 E9 FF FE FF FF ";
					for (int i = 0; i < strlen(code2) / 3; i++)
					{
						int c = translate(code2[i * 3], code2[i * 3 + 1]);
						WriteIn(hpro, 0x45E1FF + i, c, 1);
					}
				}
			}
			else {
				if (opt_check[12] || opt_check[13]) {
					char code[] = "EB CF 90 90 90 90 ";
					for (int i = 0; i < strlen(code) / 3; i++)
					{
						int c = translate(code[i * 3], code[i * 3 + 1]);
						WriteIn(hpro, 0x45E22E + i, c, 1);
					}
					char code2[] = "8A 0D F1 27 49 00 E8 EF 7F FA FF 8B 51 10 83 FA 00 75 08 B0 00 5A E9 43 FF FF FF 8A 0D F0 27 49 00 EB 0E 90 90 90 ";
					for (int i = 0; i < strlen(code2) / 3; i++)
					{
						int c = translate(code2[i * 3], code2[i * 3 + 1]);
						WriteIn(hpro, 0x45E1FF + i, c, 1);
					}
				}
				else {
					char code[] = "EB D6 90 90 90 90 ";
					for (int i = 0; i < strlen(code) / 3; i++)
					{
						int c = translate(code[i * 3], code[i * 3 + 1]);
						WriteIn(hpro, 0x45E227 + i, c, 1);
					}
					char code2[] = "8A 0D F1 27 49 00 E8 EF 7F FA FF 8B 51 10 83 FA 00 75 08 B0 00 90 EB 42 90 90 90 8A 0D F0 27 49 00 EB 0B 90 90 90 ";
					for (int i = 0; i < strlen(code2) / 3; i++)
					{
						int c = translate(code2[i * 3], code2[i * 3 + 1]);
						WriteIn(hpro, 0x45E1FF + i, c, 1);
					}
				}
			}
		}
		else {
			if (version >= 63) {
				if (opt_check[12] || opt_check[13]) {
					char code[] = "8A 0D F0 27 49 00 ";
					for (int i = 0; i < strlen(code) / 3; i++)
					{
						int c = translate(code[i * 3], code[i * 3 + 1]);
						WriteIn(hpro, 0x45E125 + i, c, 1);
					}
				}
				else {
					char code[] = "8A 0D F0 27 49 00";
					for (int i = 0; i < strlen(code) / 3; i++)
					{
						int c = translate(code[i * 3], code[i * 3 + 1]);
						WriteIn(hpro, 0x45E11E + i, c, 1);
					}
				}
			}
			else {
				if (opt_check[12] || opt_check[13]) {
					char code[] = "8A 0D F0 27 49 00 ";
					for (int i = 0; i < strlen(code) / 3; i++)
					{
						int c = translate(code[i * 3], code[i * 3 + 1]);
						WriteIn(hpro, 0x45E22E + i, c, 1);
					}
				}
				else {
					char code[] = "8A 0D F0 27 49 00 ";
					for (int i = 0; i < strlen(code) / 3; i++)
					{
						int c = translate(code[i * 3], code[i * 3 + 1]);
						WriteIn(hpro, 0x45E227 + i, c, 1);
					}
				}
			}
		}
	}

	//关闭集气
	else {
		WriteIn(hpro, 0x43B4FD, 0x55, 1);
		WriteIn(hpro, 0x4131D4, 0x14, 1);
		if (version <= 64) {
			WriteIn(hpro, 0x4131FB, 0xEC, 1);
			WriteIn(hpro, 0x413206, 0xF0, 1);
		}
		else{
			WriteIn(hpro, 0x4131F3, 0xEC, 1);
			WriteIn(hpro, 0x4131FE, 0xF0, 1);
		}
		if (show_jiqi) {
			WriteIn(hpro, 0x41322C, 0xF4, 1);
			WriteIn(hpro, 0x41323E, 0xF8, 1);
		}
		else {
			WriteIn(hpro, 0x413214, 0xF4, 1);
			WriteIn(hpro, 0x413217, 0xF8, 1);
		}
		char code[] = "EB 03 FF 45 E8 ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x41323F + i, c, 1);
		}
		if (version <= 63) {
			char code2[] = "75 0C 80 3D 33 0E 50 00 01 75 03 FF 45 C8 89 4D D8 E8 BC 60 FC FF 89 4D F0 FF 75 0C 8B 45 C8 40 50 6A 04 8B 4D D8 FF 71 06 8D 55 E4 52 E8 5C F7 00 00 8A 45 E5 88 45 F8 8A 45 E4 88 45 F4 E8 DB E0 FD FF 90 90 90 ";
			for (int i = 0; i < strlen(code2) / 3; i++)
			{
				int c = translate(code2[i * 3], code2[i * 3 + 1]);
				WriteIn(hpro, 0x4404BD + i, c, 1);
			}
		}
		else {
			char code2[] = "75 0C 80 3D 68 1A 50 00 01 75 03 FF 45 C8 89 4D D8 E8 BB 60 FC FF 89 4D F0 FF 75 0C 8B 45 C8 40 50 6A 04 8B 4D D8 FF 71 06 8D 55 E4 52 E8 5B F7 00 00 8A 45 E5 88 45 F8 8A 45 E4 88 45 F4 E8 DA E0 FD FF 90 90 ";
			for (int i = 0; i < strlen(code2) / 3; i++)
			{
				int c = translate(code2[i * 3], code2[i * 3 + 1]);
				WriteIn(hpro, 0x4404BE + i, c, 1);
			}
		}
		char code5[] = "6A 00 50 E8 61 17 03 00 ";
		for (int i = 0; i < strlen(code5) / 3; i++)
		{
			int c = translate(code5[i * 3], code5[i * 3 + 1]);
			WriteIn(hpro, 0x40612D + i, c, 1);
		}
		if (version >= 63) {
			char code7[] = "83 F8 64 77 10 6A 00 50 E8 B4 19 03 00 ";
			for (int i = 0; i < strlen(code7) / 3; i++)
			{
				int c = translate(code7[i * 3], code7[i * 3 + 1]);
				WriteIn(hpro, 0x405ED5 + i, c, 1);
			}
		}
		else {
			char code7[] = "83 F8 64 77 10 6A 00 50 E8 B1 19 03 00 ";
			for (int i = 0; i < strlen(code7) / 3; i++)
			{
				int c = translate(code7[i * 3], code7[i * 3 + 1]);
				WriteIn(hpro, 0x405ED8 + i, c, 1);
			}
		}
		char code8[] = "6A 00 FF 75 FC E8 A0 C3 FF FF ";
		for (int i = 0; i < strlen(code8) / 3; i++)
		{
			int c = translate(code8[i * 3], code8[i * 3 + 1]);
			WriteIn(hpro, 0x43B4EC + i, c, 1);
		}
	}
}

void routine_change()
{
	int base_address = 0;
	if (version == 64)base_address = 0x501A65;
	else base_address = 0x500E30;
	int number = 0;
	ReadProcessMemory(hpro, (LPVOID)base_address, &number, 1, 0);
	if (number == 0)rou_check[0] = true;
	else rou_check[0] = false;
	for (int i = 1; i <= 7; i++)
	{
		ReadProcessMemory(hpro, (LPVOID)(base_address + i), &number, 1, 0);
		if (number == 0)rou_check[i] = false;
		else rou_check[i] = true;
	}
	for (int i = 8; i <= 10; i++)
	{
		ReadProcessMemory(hpro, (LPVOID)(base_address + i + 1), &number, 1, 0);
		if (number == 0)rou_check[i] = false;
		else rou_check[i] = true;
	}
}

void routine()
{
	int base_address = 0;
	if (version == 64)base_address = 0x501A65;
	else base_address = 0x500E30;

	if (rou_check[0] == true) WriteIn(hpro, base_address, 0, 1);
	else WriteIn(hpro, base_address, 1, 1);
	for (int i = 1; i <= 7; i++)
	{
		if (rou_check[i] == true) WriteIn(hpro, base_address + i, 1, 1);
		else WriteIn(hpro, base_address + i, 0, 1);
	}
	for (int i = 8; i <= 10; i++)
	{
		if (rou_check[i] == true) WriteIn(hpro, base_address + 1 + i, 1, 1);
		else WriteIn(hpro, base_address + 1 + i, 0, 1);
	}

	if (rou_check[11])
		WriteIn(hpro, 0x41333E, 0xEB, 1);
	else
		WriteIn(hpro, 0x41333E, 0x73, 1);

	if (rou_check[12])
	{
		char code[] = "90 90 90 90 90 90 90 ";
		for (int i = 0; i < strlen(code) / 3; i++)
		{
			int c = translate(code[i * 3], code[i * 3 + 1]);
			WriteIn(hpro, 0x413383 + i, c, 1);
		}
	}
	else
	{
		if (version != 64) {
			char code[] = "80 B0 30 0E 50 00 01 ";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x413383 + i, c, 1);
			}
		}
		else{
			char code[] = "80 B0 65 1A 50 00 01";
			for (int i = 0; i < strlen(code) / 3; i++)
			{
				int c = translate(code[i * 3], code[i * 3 + 1]);
				WriteIn(hpro, 0x413383 + i, c, 1);
			}
		}
	}
}

LRESULT CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case WM_INITDIALOG:
			dialog_hwnd = hWnd;
			initDialog();
			break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDCANCEL) {
				EndDialog(hWnd, wParam);
				return TRUE;
			}
			else if (LOWORD(wParam) >= IDC_CHECK_SUPER0 && LOWORD(wParam) <= IDC_CHECK_SUPER5) {
				for (int i = 0; i < 6; i++)
					super_check[i] = IsDlgButtonChecked(dialog_hwnd, IDC_CHECK_SUPER0 + i) == BST_CHECKED;
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_STAGE0), !super_check[0]);
				super_speed();
			}
			else if (LOWORD(wParam) >= IDC_CHECK_STAGE0 && LOWORD(wParam) <= IDC_CHECK_STAGE4) {
				for (int i = 0; i < 5; i++)
					stage_check[i] = IsDlgButtonChecked(dialog_hwnd, IDC_CHECK_STAGE0 + i) == BST_CHECKED;
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_SUPER0), !stage_check[0]);
				stage_speed();
			}
			else if (HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) >= IDC_EDIT_STAGE1 && LOWORD(wParam) <= IDC_EDIT_STAGE4 && flag == false) {
				for (int i = 0; i < 4; i++) {
					TCHAR ch[10]; CString str;
					GetWindowText(GetDlgItem(dialog_hwnd, IDC_EDIT_STAGE1 + i), ch, 1024);
					str.Format(TEXT("%s"), ch);
					stage_edit[i] = _wtoi(str);
				}
				stage_speed();
			}
			else if (LOWORD(wParam) >= IDC_CHECK_GEAR0 && LOWORD(wParam) <= IDC_EDIT_GEAR1) {
				gear_speed_change();
			}
			else if (LOWORD(wParam) == IDC_BUTTON_GEAR1) {
				if (gear_edit > 0) gear_edit /= 2;
				else if (gear_edit < 0 && gear_edit >= -64) gear_edit *= 2;
				else if (gear_edit == 0) gear_edit = -1;
				char string[25]; _itoa_s(gear_edit, string, 10);
				SetWindowTextA(GetDlgItem(dialog_hwnd, IDC_EDIT_GEAR1), string);
			}
			else if (LOWORD(wParam) == IDC_BUTTON_GEAR2) {
				if (gear_edit > 0 && gear_edit <= 64) gear_edit *= 2;
				else if (gear_edit < 0) gear_edit /= 2;
				else if (gear_edit == 0) gear_edit = 1;
				char string[25]; _itoa_s(gear_edit, string, 10);
				SetWindowTextA(GetDlgItem(dialog_hwnd, IDC_EDIT_GEAR1), string);
			}
			else if (LOWORD(wParam) >= IDC_CHECK_EFFECT0 && LOWORD(wParam) <= IDC_CHECK_EFFECT6) {
				effect_check[LOWORD(wParam) - IDC_CHECK_EFFECT0] = IsDlgButtonChecked(dialog_hwnd, LOWORD(wParam)) == BST_CHECKED;
			}
			else if (HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) >= IDC_EDIT_EFFECT1 && LOWORD(wParam) <= IDC_EDIT_EFFECT6 && flag == false) {
				TCHAR ch[10]; CString str;
				GetWindowText(GetDlgItem(dialog_hwnd, LOWORD(wParam)), ch, 1024);
				str.Format(TEXT("%s"), ch);
				effect_edit[LOWORD(wParam) - IDC_EDIT_EFFECT1] = _wtoi(str);
			}
			else if (LOWORD(wParam) >= IDC_CHECK_Opt1 && LOWORD(wParam) <= IDC_CHECK_Opt19) {
				for (int i = 0; i < 19; i++)
					opt_check[i] = IsDlgButtonChecked(dialog_hwnd, IDC_CHECK_Opt1 + i) == BST_CHECKED;
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt9), opt_check[7]);
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt11), opt_check[9]);
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt13), !opt_check[13] & !opt_check[14] & !opt_check[15]);
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt14), !opt_check[12] & !opt_check[14] & !opt_check[15]);
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt15), !opt_check[12] & !opt_check[13] & !opt_check[15]);
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt16), !opt_check[12] & !opt_check[13] & !opt_check[14]);
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt17), opt_check[12] | opt_check[13] | opt_check[14] | opt_check[15]);
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt18), opt_check[12] | opt_check[13] | opt_check[14] | opt_check[15]);
				EnableWindow(GetDlgItem(dialog_hwnd, IDC_CHECK_Opt19), opt_check[12] | opt_check[13] | opt_check[14] | opt_check[15]);
				optimization();
			}
			else if (HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) >= IDC_EDIT_Opt1 && LOWORD(wParam) <= IDC_EDIT_Opt2 && flag == false) {
				TCHAR ch[100]; CString str;
				GetWindowText(GetDlgItem(dialog_hwnd, IDC_EDIT_Opt1), ch, 100);
				str.Format(TEXT("%s"), ch);
				opt_edit[0] = _wtoi(str);
				GetWindowText(GetDlgItem(dialog_hwnd, IDC_EDIT_Opt2), ch, 100);
				str.Format(TEXT("%s"), ch);
				opt_edit[1] = _wtoi(str);
				optimization();
			}
			else if (LOWORD(wParam) >= IDC_CHECK_ROU1 && LOWORD(wParam) <= IDC_CHECK_ROU13) {
				for (int i = 0; i < 13; i++)
					rou_check[i] = IsDlgButtonChecked(dialog_hwnd, IDC_CHECK_ROU1 + i) == BST_CHECKED;
				routine();
			}
			else if (HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) >= IDC_HOTKEY1 && LOWORD(wParam) <= IDC_HOTKEY9 && flag == false) {
				hot_key[LOWORD(wParam)- IDC_HOTKEY1] = SendMessage(GetDlgItem(dialog_hwnd, LOWORD(wParam)), HKM_GETHOTKEY, 0, 0);
			}
			break;
		case WM_HSCROLL:
			if (lParam == (LPARAM)GetDlgItem(dialog_hwnd, IDC_SLIDER_GEAR)) {
				int pos = (unsigned char)SendMessage(GetDlgItem(dialog_hwnd, IDC_SLIDER_GEAR), TBM_GETPOS, 0, 0);
				if (pos <= 7) gear_edit = -powf(2, 7 - pos);
				else if (pos == 8)gear_edit = 0;
				else gear_edit = powf(2, pos - 9);
				char string[25]; _itoa_s(gear_edit, string, 10);
				SetWindowTextA(GetDlgItem(dialog_hwnd, IDC_EDIT_GEAR1), string);
				return TRUE;
			}
			else if (lParam == (LPARAM)GetDlgItem(dialog_hwnd, IDC_SLIDER_EFFECT)) {
				effect_edit[6] = (unsigned char)SendMessage(GetDlgItem(dialog_hwnd, IDC_SLIDER_EFFECT), TBM_GETPOS, 0, 0);
			}
			break;
		case WM_NOTIFY:
			switch (((LPNMHDR)lParam)->code)
			{
				case TCN_SELCHANGE:
					change_page();
					break;
			}
	}
	return FALSE;
}

void newDialog()
{
	DialogBox(dll_ins, MAKEINTRESOURCE(IDD_DIALOGBAR), pro_hwnd, (DLGPROC)DialogProc);
}