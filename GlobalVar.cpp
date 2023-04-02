#include "pch.h"
#include "GlobalVar.h"

HWND pro_hwnd;			    //主窗口句柄
LONG OldWindowProc;         //主窗口回调地址
DWORD pro_id;               //进程ID
HANDLE hpro;				//进程句柄
HINSTANCE dll_ins;          //DLL模块
HINSTANCE exe_ins;          //EXE模块
HMODULE gearModule;         //变速齿轮模块
HWND sm_hwnd;

HMENU menu;
HMENU submenu;

bool active = false;
int version;

bool super_check[6]{ false, true, true, true, true, true };
bool stage_check[5]{ false, true, true, true, true };
int stage_edit[4]{ 80,80,80,5 };
bool gear_check = false;
int gear_edit = 0;

bool effect_check[7]{ true, true, true, true, true, true, false };
int effect_edit[7]{ 20,40,20,30,300,100,255 };

bool opt_check[19]{ false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,true };
int opt_edit[2]{ 100,5 };

bool rou_check[13]{ true,true,true,true,true,true,true,true,false,false,false,false,false };

int hot_key[9]{ 90,88,86,87,81,112,114,78,77 };

bool sound1 = false;
bool sound2 = false;

int mp3now = 255;
UINT wDeviceID = -1;
int vol = 1000;