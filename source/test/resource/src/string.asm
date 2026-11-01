include windows.inc
include tchar.inc
include res/string.inc

.code

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance: HINSTANCE, lpCmdLine: LPTSTR, nCmdShow: SINT

   .new hello[256]:TCHAR
   .new goodbye[256]:TCHAR

    LoadString(hInstance, IDS_HELLO, &hello, lengthof(hello))
    LoadString(hInstance, IDS_GOODBYE, &goodbye, lengthof(goodbye))
    MessageBox( NULL, &goodbye, &hello, MB_OK )
   .return( 0 )
    endp

    end _tstart
