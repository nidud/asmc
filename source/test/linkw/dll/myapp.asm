include windows.inc
include tchar.inc

.pragma comment(lib, mydll)

DllProc proto WINAPI :LPTSTR

    .code

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance:HINSTANCE, lpCmdLine:LPTSTR, nShowCmd:SINT

    DllProc("Hello dllproc\n")
    ret

_tWinMain endp

    end _tstart
