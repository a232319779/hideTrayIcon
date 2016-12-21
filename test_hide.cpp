// test_hide.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "hide.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WCHAR exeName[128] = {0};
	WCHAR *seps = L",";				// 使用","逗号做名称分割
	WCHAR *token = NULL;  
	WCHAR *next_token = NULL; 
	
	// 默认隐藏图标
	BOOL isShow = FALSE;
	if(strcmp(lpCmdLine,"show")==0)
		isShow = TRUE;
	// config.ini 只能放在当前EXE所在的路径
	GetPrivateProfileString(L"CONFIG",L"exeName",L"speed",exeName, 128, L".\\config.ini");
 
	token = wcstok_s(exeName,seps,&next_token);  

	while (NULL != token)  
	{  
		SetTrayIconStatus(token, isShow);
		token = wcstok_s(NULL,seps,&next_token);  
	}  

	return 0;
}