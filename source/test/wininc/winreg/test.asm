;
; http://masm32.com/board/index.php?topic=6887.msg73738#msg73738
;
include windows.inc
include stdio.inc
include tchar.inc

WM_REFRESH equ 28931

    .code

EnumChildWndProc proc hWnd:HWND, lParam:LPARAM

  local buff[128]:char_t

    GetClassName(rcx, &buff, 128)
    .ifd !strcmp(&buff, "SHELLDLL_DefView")
	SendMessage(hWnd, WM_COMMAND, WM_REFRESH, 0)
    .endif
    mov eax,1
    ret

EnumChildWndProc endp

EnumWndProc proc hWnd:HWND, lParam:LPARAM

    EnumChildWindows(rcx, &EnumChildWndProc, 0)
    mov eax,1
    ret

EnumWndProc endp

main proc argc:int_t, argv:array_t

  local key:HKEY, data1, data2, data3

    .if ( ecx != 2 )

	printf("Display hidden Windows files\nUsage: TEST <hide | show>\n")
	.return 0
    .endif

    mov rcx,[rdx+8]
    mov eax,[rcx]
    .if eax == 'wohs'
	mov data1,1
	mov data2,0
	mov data3,1
    .elseif eax == 'edih'
	mov data1,0
	mov data2,1
	mov data3,2
    .else
	.return 1
    .endif
    RegOpenKeyEx(HKEY_CURRENT_USER,
	"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 0, KEY_WRITE, &key)
    RegSetValueEx(key, "ShowSuperHidden", 0, REG_DWORD, &data1, DWORD)
    RegSetValueEx(key, "SuperHidden", 0, REG_DWORD, &data2, DWORD)
    RegSetValueEx(key, "Hidden", 0, REG_DWORD, &data3, DWORD)
    RegCloseKey(key)
    EnumWindows(&EnumWndProc, "SHELLDLL_DefView")
    xor eaX,eax
    ret

main endp

    end _tstart
