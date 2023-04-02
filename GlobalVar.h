#pragma once
#include "pch.h"


extern "C" HWND pro_hwnd;			    //主窗口句柄
extern "C" LONG OldWindowProc;         //主窗口回调地址
extern "C" DWORD pro_id;               //进程ID
extern "C" HANDLE hpro;				//进程句柄
extern "C" HINSTANCE dll_ins;          //DLL模块
extern "C" HINSTANCE exe_ins;          //EXE模块
extern "C" HMODULE gearModule;         //变速齿轮模块
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