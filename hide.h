/*
	Create time : 2016.12.20
	Author : ddvv
	Function : 
	@1 : void SetTrayIconStatus(LPCWSTR lpwszIcon, BOOL bShow = FALSE);
	设置托盘图标的状态(隐藏/显示)
*/

#define TB_GETBUTTON            (WM_USER + 23)
#define TB_BUTTONCOUNT          (WM_USER + 24)

// 64位对应的结构体
typedef struct _TRAYDATA64 {  
	PVOID64 hWnd;  //HWND 64位 8字节
	UINT uID;  
	UINT uCallbackMessage;  
	DWORD Reserved1[2];  
	PVOID64 hIcon;  //HICON 64位 8字节
	DWORD Reserved2[4];  
	TCHAR szExePath[MAX_PATH];  
	TCHAR szTip[128];  
} TRAYDATA64; 

typedef struct _TBBUTTON64 {
    int iBitmap;
    int idCommand;
    BYTE fsState;
    BYTE fsStyle;
    BYTE bReserved[6];          // padding for alignment
    DWORD_PTR dwData;
    INT_PTR iString;
} TBBUTTON64;

// 32对应的结构体
typedef struct _TRAYDATA32 {  
	HWND hWnd;  
	UINT uID;  
	UINT uCallbackMessage;  
	DWORD Reserved1[2];  
	HICON hIcon;  
	DWORD Reserved2[3];  
	TCHAR szExePath[MAX_PATH];  
	TCHAR szTip[128];  
} TRAYDATA32;

typedef struct _TBBUTTON32 {
    int iBitmap;
    int idCommand;
    BYTE fsState;
    BYTE fsStyle;
    BYTE bReserved[2];          // padding for alignment
    DWORD_PTR dwData;
    INT_PTR iString;
} TBBUTTON32;


/*
	param : 
	@lpwszIcon : 需要被隐藏的图标对应的可执行文件名
	@bSHow : FALSE代表隐藏，TRUE代表显示
*/
void SetTrayIconStatus(LPCWSTR lpwszIcon, BOOL bShow = FALSE);
void SetHide(HWND hWnd, LPCWSTR lpwszIcon, BOOL bShow);