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
    mov mp.cbSize,sizeof(MSGBOXPARAMS)
    mov mp.hwndOwner,NULL
    mov rax,hInstance
    mov mp.hInstance,rax
    lea rax,@CStr( "Message" )
    mov mp.lpszText,rax
    lea rax,@CStr( "Text" )
    mov mp.lpszCaption,rax
    mov mp.dwStyle,MB_YESNOCANCEL or MB_HELP
    mov mp.lpszIcon,NULL
    lea rax,Id
    mov mp.dwContextHelpId,rax
    lea rax,MsgBoxCallback
    mov mp.lpfnMsgBoxCallback,rax
    mov mp.dwLanguageId,LANG_ENGLISH

    MessageBoxIndirect(&mp)
    xor eax,eax
    ret

_tWinMain endp

    end _tstart
