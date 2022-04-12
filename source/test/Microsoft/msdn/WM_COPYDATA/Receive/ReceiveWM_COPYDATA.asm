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

;; Enable Visual Style

ifdef _M_IX86
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_IA64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
elseifdef _M_X64
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
else
.pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
endif


;; The struct that carries the data.

.template MY_STRUCT

    Number  int_t ?
    Message wchar_t 256 dup(?)
   .ends


.code

;;
;;   FUNCTION: OnCopyData(HWND, HWND, PCOPYDATASTRUCT)
;;
;;   PURPOSE: Process the WM_COPYDATA message
;;
;;   PARAMETERS:
;;   * hWnd - Handle to the current window.
;;   * hwndFrom - Handle to the window passing the data.
;;   * pcds - Pointer to a COPYDATASTRUCT structure that contains the data
;;     that was passed.
;;

OnCopyData proc hWnd:HWND, hwndFrom:HWND, pcds:PCOPYDATASTRUCT

  local myStruct:MY_STRUCT

    ;; If the size matches

    mov rcx,pcds
    .if ([rcx].COPYDATASTRUCT.cbData == sizeof(myStruct))

        ;; The receiving application should consider the data (pcds->lpData)
        ;; read-only. The pcds parameter is valid only during the processing
        ;; of the message. The receiving application should not free the
        ;; memory referenced by pcds. If the receiving application must
        ;; access the data after SendMessage returns, it must copy the data
        ;; into a local buffer.

        memcpy_s(&myStruct, sizeof(myStruct), [rcx].COPYDATASTRUCT.lpData, [rcx].COPYDATASTRUCT.cbData)

        ;; Display the MY_STRUCT value in the window.

        SetDlgItemInt(hWnd, IDC_NUMBER_STATIC, myStruct.Number, TRUE)
        SetDlgItemText(hWnd, IDC_MESSAGE_STATIC, &myStruct.Message)
    .endif
    .return TRUE

OnCopyData endp


;;
;;   FUNCTION: OnClose(HWND)
;;
;;   PURPOSE: Process the WM_CLOSE message
;;

OnClose proc hWnd:HWND

    EndDialog(hWnd, 0)
    ret

OnClose endp


;;
;;  FUNCTION: DialogProc(HWND, UINT, WPARAM, LPARAM)
;;
;;  PURPOSE:  Processes messages for the main dialog.
;;

DialogProc proc hWnd:HWND, message:UINT, wParam:WPARAM, lParam:LPARAM

    .switch (message)

        ;; Handle the WM_COPYDATA message in OnCopyData
        HANDLE_MSG (hWnd, WM_COPYDATA, OnCopyData)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG (hWnd, WM_CLOSE, OnClose)

    .default
        .return FALSE
    .endsw
    .return 0

DialogProc endp


;;
;;  FUNCTION: wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
;;
;;  PURPOSE:  The entry point of the application.
;;

wWinMain proc hInstance:     HINSTANCE,
              hPrevInstance: HINSTANCE,
              lpCmdLine:     LPWSTR,
              nCmdShow:      int_t

    .return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAINDIALOG), NULL, &DialogProc)

wWinMain endp

    end
