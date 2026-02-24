; RECEIVEWM_COPYDATA.ASM--
;
; Inter-process Communication (IPC) based on the Windows message WM_COPYDATA
;
; https://github.com/microsoftarchive/msdn-code-gallery-microsoft/
;

include stdio.inc
include windows.inc
include windowsx.inc
include Resource.inc

ifdef _M_IX86
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_IA64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_X64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
else
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
endif
.template MY_STRUCT
    Number  int_t ?
    Message wchar_t 256 dup(?)
   .ends

.code

OnCopyData proc hWnd:HWND, hwndFrom:HWND, pcds:PCOPYDATASTRUCT
  local myStruct:MY_STRUCT
    mov rcx,pcds
    .if ([rcx].COPYDATASTRUCT.cbData == sizeof(myStruct))
        memcpy_s(&myStruct, sizeof(myStruct), [rcx].COPYDATASTRUCT.lpData, [rcx].COPYDATASTRUCT.cbData)
        SetDlgItemInt(hWnd, IDC_NUMBER_STATIC, myStruct.Number, TRUE)
        SetDlgItemText(hWnd, IDC_MESSAGE_STATIC, &myStruct.Message)
    .endif
    .return TRUE
    endp

OnClose proc hWnd:HWND
    EndDialog(hWnd, 0)
    ret
    endp


DialogProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM
    .switch (message)
        HANDLE_MSG (hWnd, WM_COPYDATA, OnCopyData)
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)
    .endsw
    .return 0
    endp

wWinMain proc hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPWSTR, nCmdShow:int_t
    .return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, &DialogProc)
    endp

    end
