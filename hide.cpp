#include "stdafx.h"
#include "hide.h"
#include <Shellapi.h>

// 打开下面注释编译64位，否则编译32位
//#define MYSYS_64

#ifdef MYSYS_64
#define TBBUTTON TBBUTTON64
#define TRAYDATA TRAYDATA64
#else
#define TBBUTTON TBBUTTON32
#define TRAYDATA TRAYDATA32
#endif

void SetTrayIconStatus(LPCWSTR lpwszIcon, BOOL bShow)
{
	HWND hWnd1, hWnd2;

	hWnd1 = FindWindow(TEXT("Shell_TrayWnd"), NULL);
	hWnd1 = FindWindowEx(hWnd1, 0, TEXT("TrayNotifyWnd"), NULL);
	hWnd1 = FindWindowEx(hWnd1, 0, TEXT("SysPager"), NULL);
	hWnd1 = FindWindowEx(hWnd1, 0, TEXT("ToolbarWindow32"), NULL);
	SetHide(hWnd1, lpwszIcon, bShow);

	hWnd2 = FindWindow(TEXT("NotifyIconOverflowWindow"), NULL);
	hWnd2 = FindWindowEx(hWnd2, 0, TEXT("ToolbarWindow32"), NULL);
	SetHide(hWnd2, lpwszIcon, bShow);
}

void SetHide(HWND hWnd, LPCWSTR lpwszIcon, BOOL bShow)
{
	DWORD dwProcessId;
	int dwButtonCount;
	HANDLE hProcess;
	LPVOID lpAddress;
	TBBUTTON tb;

	GetWindowThreadProcessId(hWnd, &dwProcessId);
	hProcess = OpenProcess(PROCESS_ALL_ACCESS
		|PROCESS_VM_OPERATION
		|PROCESS_VM_READ
		|PROCESS_VM_WRITE,
		0,
		dwProcessId);
	lpAddress = VirtualAllocEx(hProcess,0, 0x4096, MEM_COMMIT, PAGE_READWRITE);
	dwButtonCount = SendMessage(hWnd, TB_BUTTONCOUNT, 0, 0);

	for(int i = 0 ; i < dwButtonCount; i++)
	{
		SendMessage(hWnd, TB_GETBUTTON, i, (LPARAM)lpAddress);
		ReadProcessMemory(hProcess, lpAddress, &tb, sizeof(tb), 0);

		if(tb.iString != -1)
		{
			TRAYDATA trayData;
			WCHAR *pwsz = NULL;
			ReadProcessMemory(hProcess, (LPVOID)tb.dwData, &trayData, sizeof(TRAYDATA), 0);
			pwsz = wcsstr(trayData.szExePath, lpwszIcon);
			if (pwsz)
			{
				NOTIFYICONDATA nid;
				nid.cbSize = sizeof(NOTIFYICONDATA);
				nid.hWnd = (HWND)trayData.hWnd;
				nid.uID = trayData.uID;
				nid.uFlags = NIF_STATE;
				nid.dwState = bShow?NIS_SHAREDICON:NIS_HIDDEN;
				nid.dwStateMask = NIS_HIDDEN;
				Shell_NotifyIcon(NIM_MODIFY, &nid);
			}
		}
	}
	VirtualFreeEx( hProcess, lpAddress, 0x4096, MEM_RELEASE);
	CloseHandle(hProcess);
}