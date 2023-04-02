#include "pch.h"
#include "resource.h"
#include "mytool.h"
#include "mydialog.h"
#include "randomdialog.h"
#include "myeffect.h"
#include <time.h>

#define IDM_MENUITEM1 0x2001
#define IDM_MENUITEM2 0x2002
#define IDM_MENUITEM3 0x2003
#define IDM_MENUITEM4 0x2004

#ifdef _X86_
extern "C" { int _afxForceUSRDLL; }
#else
extern "C" { int __afxForceUSRDLL; }
#endif

typedef int(*myCDAudioPlayTrack)(int a1, WPARAM wParam);
typedef int(*myCDAudioStop)();
typedef int(*myCDAudioPause)();
typedef int(*myCDAudioResume)();

extern "C" __declspec(dllexport) int CDAudioPause()
{
	HMODULE loadLibrary = LoadLibraryA("Koeicda_org.dll");
	//通过name
	myCDAudioPause procAddress = (myCDAudioPause)GetProcAddress(loadLibrary, "CDAudioPause");
	int result = procAddress();
	//从程序中卸载dll
	FreeLibrary(loadLibrary);
	return 1;
}
extern "C" __declspec(dllexport) int CDAudioPlayTrack(int a1, WPARAM wParam)
{
	HMODULE loadLibrary = LoadLibraryA("Koeicda_org.dll");
	//通过name
	myCDAudioPlayTrack procAddress = (myCDAudioPlayTrack)GetProcAddress(loadLibrary, "CDAudioPlayTrack");
	int result = procAddress(a1, wParam);
	//从程序中卸载dll
	FreeLibrary(loadLibrary);
	return 1;
}
extern "C" __declspec(dllexport) int CDAudioResume()
{
	HMODULE loadLibrary = LoadLibraryA("Koeicda_org.dll");
	//通过name
	myCDAudioResume procAddress = (myCDAudioResume)GetProcAddress(loadLibrary, "CDAudioResume");
	int result = procAddress();
	//从程序中卸载dll
	FreeLibrary(loadLibrary);
	return 1;
}
extern "C" __declspec(dllexport) int CDAudioStop() {
	HMODULE loadLibrary = LoadLibraryA("Koeicda_org.dll");
	//通过name
	myCDAudioStop procAddress = (myCDAudioStop)GetProcAddress(loadLibrary, "CDAudioStop");
	procAddress();
	//从程序中卸载dll
	FreeLibrary(loadLibrary);
	return 1;
}
extern "C" __declspec(dllexport) int CDAudioTerminate() { return 1; }
extern "C" __declspec(dllexport) int CDAudioGetDriveLetter() { return 1; }
extern "C" __declspec(dllexport) int CDAudioGetPlayingPos() { return 1; }
extern "C" __declspec(dllexport) int CDAudioIsPlaying() { return 1; }
extern "C" __declspec(dllexport) int CDAudioInitialize() { return 1; }
extern "C" __declspec(dllexport) int CDAudioGetNumDrives() { return 1; }
extern "C" __declspec(dllexport) int CDAudioOpen() { return 1; }
extern "C" __declspec(dllexport) int CDAudioGetNumTracks() { return 1; }

HHOOK g_hHook, g_hHook2;
bool getRoll = false;      //滚轮是否滑动
bool getKey = false;

void saveAll()
{
	ofstream ofs;
	ofs.open("./patch/pl_06.ini", ios::out | ios::trunc);
	for (int i = 0; i < 6; i++)
		if (super_check[i] == true) ofs << 1 << endl;
		else ofs << 0 << endl;
	for (int i = 0; i < 5; i++)
		if (stage_check[i] == true) ofs << 1 << endl;
		else ofs << 0 << endl;
	for (int i = 0; i < 4; i++)
		ofs << stage_edit[i] << endl;
	if (gear_check == true) ofs << 1 << endl;
	else ofs << 0 << endl;
	ofs << gear_edit << endl;
	for (int i = 0; i < 7; i++)
		if (effect_check[i] == true) ofs << 1 << endl;
		else ofs << 0 << endl;
	for (int i = 0; i < 7; i++)
		ofs << effect_edit[i] << endl;
	for (int i = 0; i < 19; i++)
		if (opt_check[i] == true) ofs << 1 << endl;
		else ofs << 0 << endl;
	for (int i = 0; i < 2; i++)
		ofs << opt_edit[i] << endl;
	for (int i = 0; i < 13; i++)
		if (rou_check[i] == true) ofs << 1 << endl;
		else ofs << 0 << endl;
	for (int i = 0; i < 9; i++)
		ofs << hot_key[i] << endl;
}

void loadAll()
{
	int a[1000];
	for (int i = 0; i < 1000; i++)a[i] = 0;
	ifstream ifs("./patch/pl_06.ini", ios::in);
	if (!ifs.is_open())
		return;
	char buffer2[1024] = { 0 };
	int k = 0, m = 0;
	while (ifs.getline(buffer2, sizeof(buffer2))) {
		while (buffer2[m] != 0) {
			a[k] = a[k] * 10 + buffer2[m] - '0';
			m++;
		}
		k++;
		m = 0;
	}
	k = 0;
	for (int i = 0; i < 6; i++) {
		if (a[k + i] == 1) super_check[i] = true;
		else super_check[i] = false;
	}
	k += 6;
	for (int i = 0; i < 5; i++)
		if (a[k + i] == 1) stage_check[i] = true;
		else stage_check[i] = false;
	k += 5;
	for (int i = 0; i < 4; i++)
		stage_edit[i] = a[k + i];
	k += 4;
	if (a[k] == 1)gear_check = true;
	else gear_check = false;
	k += 1;
	gear_edit = a[k];
	k += 1;
	for (int i = 0; i < 7; i++)
		if (a[k + i] == 1) effect_check[i] = true;
		else effect_check[i] = false;
	k += 7;
	for (int i = 0; i < 7; i++)
		effect_edit[i] = a[k + i];
	k += 7;
	for (int i = 0; i < 19; i++)
		if (a[k + i] == 1) opt_check[i] = true;
		else opt_check[i] = false;
	k += 19;
	for (int i = 0; i < 2; i++)
		opt_edit[i] = a[k + i];
	k += 2;
	for (int i = 0; i < 13; i++)
		if (a[k + i] == 1) rou_check[i] = true;
		else rou_check[i] = false;
	k += 13;
	for (int i = 0; i < 9; i++)
		hot_key[i] = a[k + i];

	super_check[0] = false;
	stage_check[0] = false;

	super_speed();
	stage_speed();
	gear_speed();
	optimization();
	routine();
}

DWORD static WINAPI SoundThread(LPVOID lpvoid)
{
	while (1)
	{
		/*音乐处理*/
		int mp3;
		ReadProcessMemory(hpro, (LPCVOID)0x4B0774, &mp3, 1, 0);
		int open;
		ReadProcessMemory(hpro, (LPCVOID)0x4B0771, &open, 1, 0);
		if (((open >> 5) & 1) == 0) {
			if (wDeviceID != -1) {
				mciSendCommand(wDeviceID, MCI_STOP, 0, NULL);
				mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
				wDeviceID = -1;
			}
			mp3now = 255;
			Sleep(100);
			continue;
		}
		if (mp3 != mp3now) {
			mp3now = mp3;
			// 停止上一个音乐
			if (wDeviceID != -1) {
				mciSendCommand(wDeviceID, MCI_STOP, 0, NULL);
				mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
				wDeviceID = -1;
			}
			if (mp3now == 255)
			{
				Sleep(100);
				continue;
			}
			wchar_t* path = getPath(mp3now);
			MCI_OPEN_PARMS mciOpenParms;
			mciOpenParms.lpstrDeviceType = L"sequencer";
			mciOpenParms.lpstrElementName = path;
			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, DWORD_PTR(&mciOpenParms));	// 打开指定媒体文件
			wDeviceID = mciOpenParms.wDeviceID;	// 返回的 Device ID 需要保存下来，以便实现后续控制

			// 播放音乐
			MCI_PLAY_PARMS mciPlayParms;
			mciSendCommand(wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, DWORD_PTR(&mciPlayParms));
		}

		if (wDeviceID != -1) {
			//音量调节
			MCI_DGV_SETAUDIO_PARMS setvolume; //设置音量的参数结构体
			setvolume.dwCallback = NULL; //
			setvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME; //动作是设置音量
			setvolume.dwValue = vol; //音量值是vol
			mciSendCommand(wDeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&setvolume);


			LONG lStyles = GetWindowLong(pro_hwnd, GWL_STYLE);
			if (lStyles & WS_MINIMIZE)
				mciSendCommand(wDeviceID, MCI_PAUSE, 0, 0);
			else
				mciSendCommand(wDeviceID, MCI_RESUME, 0, 0);
		}
		Sleep(100);
	}
}

int Init() {
	DWORD dwCurrentProcessId = GetCurrentProcessId();
	hpro = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, dwCurrentProcessId);
	int check;
	ReadProcessMemory(hpro, (LPCVOID)0x42BA0A, &check, 1, 0);
	if (check == 0xE8) {
		WriteIn(hpro, 0x42BA0A, 0x90909090, 4);
		WriteIn(hpro, 0x42BA0A + 4, 0x90, 1);
	}
	else if (check == 0) {
		WriteIn(hpro, 0x42BA13, 0x90909090, 4);
		WriteIn(hpro, 0x42BA13 + 4, 0x90, 1);
	}
	/*else {
		WriteIn(hpro, 0x42BA13, 0x90909090, 4);
		WriteIn(hpro, 0x42BA13 + 4, 0x90, 1);
	}*/
	//新版音乐控制
	/*WriteIn(hpro, 0x4B0774, 0x12, 1);
	char code[] = "8B 4D 08 89 0D 74 07 4B 00 90 90 90 90 90 90 90 90 90 ";
	for (int i = 0; i < strlen(code) / 3; i++)
	{
		int c = translate(code[i * 3], code[i * 3 + 1]);
		WriteIn(hpro, 0x474601 + i, c, 1);
	}
	char code2[] = "C6 05 74 07 4B 00 FF 90 90 90 90 90 ";
	for (int i = 0; i < strlen(code2) / 3; i++)
	{
		int c = translate(code2[i * 3], code2[i * 3 + 1]);
		WriteIn(hpro, 0x47461C + i, c, 1);
	}
	CreateThread(NULL, 0, SoundThread, dll_ins, 0, NULL);*/
	Sleep(200);

	exe_ins = GetModuleHandle(NULL);
	if (exe_ins == NULL) {
		return 0;
	}
	pro_hwnd = GetWindowHandle();
	if (pro_hwnd == NULL) {
		return 0;
	}
	GetWindowThreadProcessId(pro_hwnd, &pro_id);	//获取进程ID  
	if (pro_id == 0) {
		return 0;
	}
	//打开进程对象，并获取进程句柄
	hpro = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pro_id);
	if (hpro == 0) {
		return 0;
	}

	//检查版本
	int number = 0;
	ReadProcessMemory(hpro, (LPVOID)(0x42C4E9 + 0), &number, 1, 0);
	if (number == 3) {
		version = 62;
		WriteIn(hpro, 0x48B000, 2, 1);
	}
	else {
		version = 63;
		WriteIn(hpro, 0x48B000, 3, 1);
	}
	number = 0;
	ReadProcessMemory(hpro, (LPVOID)(0x40A986 + 0), &number, 1, 0);
	if (number == 0x55)
	{
		version = 61;
		WriteIn(hpro, 0x48B000, 1, 1);
	}
	number = 0;
	ReadProcessMemory(hpro, (LPVOID)(0x42D5B0 + 0), &number, 1, 0);
	if (number == 0x55)
	{
		version = 64;
		WriteIn(hpro, 0x48B000, 4, 1);
		ReadProcessMemory(hpro, (LPVOID)(0x4131F7), &number, 1, 0);
		if (number == 0xE8) {
			version = 65;
			WriteIn(hpro, 0x48B000, 5, 1);
		}
	}

	//导入变速齿轮的dll
	gearModule = LoadLibraryA("GearNtKe.dll");
	myAddProcess procAddress = (myAddProcess)GetProcAddress(gearModule, "AddProcess");
	procAddress(hpro);
	mySetSpeed procAddress2 = (mySetSpeed)GetProcAddress(gearModule, "SetSpeed");
	procAddress2(0);

	number = 0;
	if (version == 62) ReadProcessMemory(hpro, (LPVOID)(0x43EC2D), &number, 1, 0);
	else ReadProcessMemory(hpro, (LPVOID)(0x43EC50), &number, 1, 0);
	opt_edit[0] = (number - 1) / 5 * 2;
	if (opt_edit[0] >= 100)opt_edit[0] = 100;
	if (version == 62) ReadProcessMemory(hpro, (LPVOID)(0x45EA79), &number, 1, 0);
	else ReadProcessMemory(hpro, (LPVOID)(0x44D52E), &number, 1, 0);
	opt_edit[1] = number;

	loadAll();

	return 1;
}

void OnCommand(HWND hWnd, WPARAM wParam)
{
	SHORT nMenuID = LOWORD(wParam);

	switch (nMenuID)
	{
		case IDM_MENUITEM1:
		{
			newDialog();
			break;
		}
		case IDM_MENUITEM2:
		{
			saveAll();
			break;
		}
		case IDM_MENUITEM3:
		{
			int rs = 0; int check = 0;
			ReadProcessMemory(hpro, (LPCVOID)0x4B0776, &rs, 1, 0);
			ReadProcessMemory(hpro, (LPCVOID)0x496F38, &check, 1, 0);
			if (rs == 0 && check == 0) {
				randomDialog();
			}
			else {
				MessageBox(hWnd, __TEXT("  随机失败，游戏开始后不可以再随机了。"), __TEXT("随机结果"), MB_OK);
			}
			break;
		}
		case IDM_MENUITEM4:
		{
			MessageBox(hWnd, __TEXT("  曹操传优化补丁 v0.61\n\n  by普罗  2022.11.26"), __TEXT("关于"), MB_OK);
			break;
		}
		default:
			break;
	}
}

LRESULT CALLBACK NewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
		break;
	default:
		break;
	}
	return  CallWindowProc((WNDPROC)OldWindowProc, hWnd, message, wParam, lParam);
}

LRESULT CALLBACK MyMouseCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	HWND m_hWndTop = ::GetForegroundWindow();
	TCHAR szBuff[256];
	GetClassName(m_hWndTop, szBuff, sizeof(szBuff) / sizeof(TCHAR));
	if (szBuff[0] != 'S' || !stage_check[0] || !stage_check[4])
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
	if (wParam == WM_MOUSEWHEEL)
	{
		MSLLHOOKSTRUCT* mouselparam = (MSLLHOOKSTRUCT*)lParam;
		short tmp = HIWORD(mouselparam->mouseData);
		int a = 0;
		if (getRoll == false) {
			if (tmp != 0)
				ReadProcessMemory(hpro, (LPVOID)(0x4B3D18), &a, 1, 0);
			if (a >= 2) a = 2;
			if (tmp > 0)
				stage_edit[a] += stage_edit[3];
			else if (tmp < 0)
				stage_edit[a] -= stage_edit[3];
			if (stage_edit[3] < 20) stage_edit[3] = 20;
			if (stage_edit[3] > 200)stage_edit[3] = 200;
			getRoll = true;
		}
		else
			getRoll = false;
	}
	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MyKeyBoardCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;
	HWND m_hWndTop = ::GetForegroundWindow();
	TCHAR szBuff[256];
	GetClassName(m_hWndTop, szBuff, sizeof(szBuff) / sizeof(TCHAR));
	//::SendMessageA(hBtn2, WM_SETTEXT, 0, (LPARAM)szBuff);
	if (szBuff[0] != 'S' && szBuff[0] != '{' && szBuff[0] != 'B')
		return CallNextHookEx(g_hHook2, nCode, wParam, lParam);
	if (wParam == WM_KEYDOWN) {
		if (getKey == true)
			return CallNextHookEx(g_hHook2, nCode, wParam, lParam);
		getKey = true;
		if (pKeyStruct->vkCode == hot_key[0]) {
			if (super_check[0] == true || stage_check[0] == false) {
				super_check[0] = !super_check[0];
				super_speed();
			}
		}
		else if (pKeyStruct->vkCode == hot_key[1]) {
			if (stage_check[0] == true || super_check[0] == false) {
				stage_check[0] = !stage_check[0];
				stage_speed();
			}
		}
		else if (pKeyStruct->vkCode == hot_key[2]) {
			gear_check = !gear_check;
			gear_speed();
		}
		else if (pKeyStruct->vkCode == hot_key[3]) {
			if (gear_edit > 0 && gear_edit <= 64) gear_edit *= 2;
			else if (gear_edit < 0) gear_edit /= 2;
			else if (gear_edit == 0) gear_edit = 1;
			gear_speed();
		}
		else if (pKeyStruct->vkCode == hot_key[4]) {
			if (gear_edit > 0) gear_edit /= 2;
			else if (gear_edit < 0 && gear_edit >= -64) gear_edit *= 2;
			else if (gear_edit == 0) gear_edit = -1;
			gear_speed();
		}
		else if (pKeyStruct->vkCode == hot_key[5] || pKeyStruct->vkCode == hot_key[6]) {
			optimization();
		}
		else if (pKeyStruct->vkCode == hot_key[7] && IsWindowVisible(pro_hwnd)) {
			if (sound1 == true) {
				mciSendString(_T("pause rain"), NULL, 0, NULL);
				sound1 = false;
			}
			if (sound2 == true) {
				mciSendString(_T("pause snow"), NULL, 0, NULL);
				sound2 = false;
			}
			CDAudioPause();
			sm_hwnd = FindWindow(_T("SmallMap"), NULL);
			SetWindowPos(pro_hwnd, NULL, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
			if (sm_hwnd != NULL)
				SetWindowPos(sm_hwnd, NULL, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
		}
		else if (pKeyStruct->vkCode == hot_key[8] && !IsWindowVisible(pro_hwnd)) {
			CDAudioResume();
			SetWindowPos(pro_hwnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
			if (sm_hwnd != NULL)
				SetWindowPos(sm_hwnd, NULL, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);
		}
		else if (pKeyStruct->vkCode == 9) {
			newDialog();
		}
		else if (pKeyStruct->vkCode == 0xBE) {
			if (vol <= 900) vol += 100;
		}
		else if (pKeyStruct->vkCode == 0xBC) {
			if (vol >= 100) vol -= 100;
		}
	}
	if (wParam == WM_KEYUP)
	{
		getKey = false;
	}
	return CallNextHookEx(g_hHook2, nCode, wParam, lParam);
}

DWORD APIENTRY MainThread(LPVOID lpParameter)
{
	Init();

	OldWindowProc = GetWindowLong(pro_hwnd, GWL_WNDPROC);
	SetWindowLong(pro_hwnd, GWL_WNDPROC, (LONG)NewWndProc);

	//AfxSetResourceHandle(exe_ins);
	menu = LoadMenuA(exe_ins, (LPCSTR)"APPMENU");
	submenu = CreatePopupMenu();
	AppendMenu(submenu, MF_STRING | MF_ENABLED, IDM_MENUITEM1, L"配置补丁");
	AppendMenu(submenu, MF_STRING | MF_ENABLED, IDM_MENUITEM2, L"保存配置");
	AppendMenu(submenu, MF_STRING | MF_ENABLED, IDM_MENUITEM3, L"超级随机开局");
	AppendMenu(submenu, MF_STRING | MF_ENABLED, IDM_MENUITEM4, L"关于");
	AppendMenu(menu, MF_ENABLED | MF_POPUP | MF_STRING, (UINT)submenu, TEXT("优化补丁v0.61"));

	SetMenu(pro_hwnd, menu);

	g_hHook = SetWindowsHookEx(WH_MOUSE_LL, MyMouseCallback, exe_ins, 0);
	g_hHook2 = SetWindowsHookEx(WH_KEYBOARD_LL, MyKeyBoardCallback, exe_ins, 0);

	CreateEffectWindow();
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		dll_ins = hModule;
		CreateThread(NULL, 0, MainThread, hModule, 0, NULL);
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

