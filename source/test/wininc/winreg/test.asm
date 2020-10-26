;
; http://masm32.com/board/index.php?topic=6887.msg73738#msg73738
;
include winuser.inc
include winreg.inc
include stdio.inc
include tchar.inc

.pragma warning(disable: 6004) ; procedure argument or local not referenced

WM_REFRESH equ 28931

    .code

EnumChildWndProc proc hWnd:HWND, lParam:LPARAM

  local buff[128]:char_t

    GetClassName(hWnd, &buff, 128)
    .ifd !strcmp(&buff, "SHELLDLL_DefView")
	SendMessage(hWnd, WM_COMMAND, WM_REFRESH, 0)
    .endif
    mov eax,1
    ret

EnumChildWndProc endp

EnumWndProc proc hWnd:HWND, lParam:LPARAM

    EnumChildWindows(hWnd, &EnumChildWndProc, 0)
    mov eax,1
    ret

EnumWndProc endp

main proc argc:int_t, argv:array_t

  local key		: HKEY,
	Hidden		: DWORD,
	SuperHidden	: DWORD,
	ShowSuperHidden : DWORD

    .if ( argc != 2 )

	printf("Display hidden Windows files\nUsage: TEST <hide | show>\n")

	.return 0
    .endif

    mov Hidden,2
    mov SuperHidden,1
    mov ShowSuperHidden,0

    mov ecx,size_t
    add rcx,argv
    mov eax,[rcx]
    .if eax == 'wohs'

	mov Hidden,1
	mov SuperHidden,0
	mov ShowSuperHidden,1

    .elseif eax != 'edih'

	.return 1
    .endif

    RegOpenKeyEx(
	HKEY_CURRENT_USER,
	"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced",
	0,
	KEY_WRITE,
	&key)

    RegSetValueEx(
	key,
	"ShowSuperHidden",
	0,
	REG_DWORD,
	&ShowSuperHidden,
	DWORD)

    RegSetValueEx(
	key,
	"SuperHidden",
	0,
	REG_DWORD,
	&SuperHidden,
	DWORD)

    RegSetValueEx(
	key,
	"Hidden",
	0,
	REG_DWORD,
	&Hidden,
	DWORD)

    RegCloseKey(key)
    EnumWindows(&EnumWndProc, "SHELLDLL_DefView")
    xor eaX,eax
    ret

main endp

    end _tstart
