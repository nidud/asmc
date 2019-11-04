include windows.inc
include commctrl.inc
include tchar.inc

    .code

MsgBoxCallback proc WINAPI lpHelpInf:LPHELPINFO

    MessageBox(NULL, "Message", "Help", MB_OK)
    ret

MsgBoxCallback endp

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

  local mp:MSGBOXPARAMS
  local Id:UINT

    mov Id,100
    mov mp.cbSize,              MSGBOXPARAMS
    mov mp.hwndOwner,           NULL
    mov mp.hInstance,           hInstance
    mov mp.lpszText,            &@CStr( "Message" )
    mov mp.lpszCaption,         &@CStr( "Text" )
    mov mp.dwStyle,             MB_YESNOCANCEL or MB_HELP
    mov mp.lpszIcon,            NULL
    mov mp.dwContextHelpId,     &Id
    mov mp.lpfnMsgBoxCallback,  &MsgBoxCallback
    mov mp.dwLanguageId,        LANG_ENGLISH

    MessageBoxIndirect(&mp)
    xor eax,eax
    ret

_tWinMain endp

    end _tstart
