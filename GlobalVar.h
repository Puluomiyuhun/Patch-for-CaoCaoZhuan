#pragma once
#include "pch.h"


extern "C" HWND pro_hwnd;			    //�����ھ��
extern "C" LONG OldWindowProc;         //�����ڻص���ַ
extern "C" DWORD pro_id;               //����ID
extern "C" HANDLE hpro;				//���̾��
extern "C" HINSTANCE dll_ins;          //DLLģ��
extern "C" HINSTANCE exe_ins;          //EXEģ��
extern "C" HMODULE gearModule;         //���ٳ���ģ��
extern "C" HWND sm_hwnd;

extern "C" HMENU menu;
extern "C" HMENU submenu;
extern "C" bool active;
extern "C" int version;

extern "C" bool super_check[];
extern "C" bool stage_check[];
extern "C" int stage_edit[];

extern "C" bool gear_check;
extern "C" int gear_edit;

extern "C" bool effect_check[];
extern "C" int effect_edit[];

extern "C" bool opt_check[];
extern "C" int opt_edit[];

extern "C" bool rou_check[];

extern "C" int hot_key[];

extern bool sound1;
extern bool sound2;

extern int mp3now;
extern UINT wDeviceID;
extern int vol;