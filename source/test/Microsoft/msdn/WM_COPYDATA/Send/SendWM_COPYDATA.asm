; SENDWM_COPYDATA.ASM--
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
;;   FUNCTION: ReportError(LPWSTR, DWORD)
;;
;;   PURPOSE: Display an error dialog for the failure of a certain function.
;;
;;   PARAMETERS:
;;   * pszFunction - the name of the function that failed.
;;   * dwError - the Win32 error code. Its default value is the calling
;;   thread's last-error code value.
;;
;;   NOTE: The failing function must be immediately followed by the call of
;;   ReportError if you do not explicitly specify the dwError parameter of
;;   ReportError. This is to ensure that the calling thread's last-error code
;;   value is not overwritten by any calls of API between the failing
;;   function and ReportError.
;;

ReportError proc pszFunction:LPCWSTR, dwError:DWORD

  local szMessage[200]:wchar_t

    .ifd (swprintf_s(&szMessage, ARRAYSIZE(szMessage), L"%s failed w/err 0x%08lx", pszFunction, dwError) != -1)

        MessageBox(NULL, &szMessage, L"Error", MB_ICONERROR)
    .endif
    ret

ReportError endp


;;
;;   FUNCTION: OnCommand(HWND, int, HWND, UINT)
;;
;;   PURPOSE: Process the WM_COMMAND message
;;

OnCommand proc hWnd:HWND, id:int_t, hwndCtl:HWND, codeNotify:UINT

    .if (id == IDC_SENDMSG_BUTTON)

        ;; Find the target window handle.

        .new hTargetWnd:HWND = FindWindow(NULL, L"ReceiveWM_COPYDATA")
        .if (hTargetWnd == NULL)

            MessageBox(hWnd, L"Unable to find the \"ReceiveWM_COPYDATA\" window",
                L"Error", MB_ICONERROR)
            .return
        .endif

        ;; Prepare the COPYDATASTRUCT struct with the data to be sent.

        .new myStruct:MY_STRUCT
        .new fTranslated:BOOL = FALSE

        GetDlgItemInt(hWnd, IDC_NUMBER_EDIT, &fTranslated, TRUE)

        mov myStruct.Number,eax
        .if (!fTranslated)

            MessageBox(hWnd, L"Invalid value of Number!", L"Error", MB_ICONERROR)
            .return
        .endif

        GetDlgItemText(hWnd, IDC_MESSAGE_EDIT, &myStruct.Message,
            ARRAYSIZE(myStruct.Message))

        .new cds:COPYDATASTRUCT
        mov cds.cbData,sizeof(myStruct)
        mov cds.lpData,&myStruct

        ;; Send the COPYDATASTRUCT struct through the WM_COPYDATA message to
        ;; the receiving window. (The application must use SendMessage,
        ;; instead of PostMessage to send WM_COPYDATA because the receiving
        ;; application must accept while it is guaranteed to be valid.)

        SendMessage(hTargetWnd, WM_COPYDATA, hWnd, &cds)

        .new dwError:DWORD = GetLastError()
        .if (dwError != NO_ERROR)

            ReportError(L"SendMessage(WM_COPYDATA)", dwError)
        .endif
    .endif
    ret
OnCommand endp


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

        ;; Handle the WM_COMMAND message in OnCommand
        HANDLE_MSG(hWnd, WM_COMMAND, OnCommand)

        ;; Handle the WM_CLOSE message in OnClose
        HANDLE_MSG(hWnd, WM_CLOSE, OnClose)

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
