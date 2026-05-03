; GUI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include commctrl.inc
include tchar.inc

    .code

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

    MessageBox(NULL, "Win32 gui application", "Dialog(0)", MB_OK)
    xor eax,eax
    ret

_tWinMain endp

    end
