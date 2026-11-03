include windows.inc
include tchar.inc
include res/unicode.inc

.code

_tWinMain proc WINAPI hInstance:HINSTANCE, hPrevInstance: HINSTANCE, lpCmdLine: LPTSTR, nCmdShow: SINT

   .new cn[256]:TCHAR
   .new ru[256]:TCHAR
   .new ar[256]:TCHAR

    LoadString(hInstance, IDS_CHINESESTRING, &cn, lengthof(cn))
    LoadString(hInstance, IDS_RUSSIANSTRING, &ru, lengthof(ru))
    LoadString(hInstance, IDS_ARABICSTRING, &ar, lengthof(ar))

    MessageBox( NULL, &cn, "Chinese", MB_OK )
    MessageBox( NULL, &ru, "Russian", MB_OK )
    MessageBox( NULL, &ar, "Arabic", MB_OK )
   .return( 0 )
    endp

    end _tstart
