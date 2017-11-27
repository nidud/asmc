include windows.inc
include commctrl.inc
include tchar.inc

    .code

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

    MessageBox(NULL, "Hello World", "Dialog(0)", MB_OK)
    xor eax,eax
    ret

_tWinMain endp

    end
