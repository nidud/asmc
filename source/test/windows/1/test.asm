include windows.inc
include winnls.inc
include tchar.inc

    option wstring:on

    .data
    align 8
Dialog  DLGTEMPLATE <DS_SETFONT or WS_OVERLAPPED or WS_SYSMENU or DS_CENTER,0,2,50,50,150,80>
    dw 0,0,"Dialog(1)",0,16,"MS Sans Serif",0
    align 4
    DLGITEMTEMPLATE <WS_VISIBLE or WS_CHILD or WS_TABSTOP,0,48,40,50,15,IDCANCEL>
    dw -1,0x0080," &OK ",0
    align 4
    DLGITEMTEMPLATE <WS_VISIBLE or WS_CHILD or SS_CENTER,0,2,20,140,9,100>
    dw -1,0x0082
ifdef __PE__
    dw "/pe "
endif
ifdef _WIN64
    dw "WIN64 "
else
    dw "WIN32 "
endif
ifdef _UNICODE
    dw "UNICODE "
else
    dw "ASCII "
endif
    dw "windows/1/test.asm",0

    .code


DialogFunc proc hWin:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .switch uMsg
      .case WM_INITDIALOG
        SendMessage(hWin, WM_SETICON, 1, LoadIcon(NULL, IDI_ASTERISK))
        .endc
      .case WM_COMMAND
        ;.endc .if wParam != IDCANCEL
      .case WM_CLOSE
        EndDialog(hWin, 0)
    .endsw
    xor eax, eax
    ret

DialogFunc endp

_tmain proc

    mov rcx,GetModuleHandle(NULL)
    DialogBoxIndirectParam(rcx, &Dialog, 0, &DialogFunc, NULL)
    ret

_tmain  endp

    end _tstart
