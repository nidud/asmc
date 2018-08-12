;
; http://masm32.com/board/index.php?topic=5929.msg72217#msg72217
;
include windows.inc
include wininet.inc
include shlobj.inc

BITMAP0 equ <L"%SystemRoot%\\web\\wallpaper\\Windows\\img0.jpg">
BITMAP1 equ <L"%AsmcDir%\\source\\test\\wininc\\SetWallpaper\\test.bmp">

ifdef __PE__
.data

CLSID_ActiveDesktop GUID _CLSID_ActiveDesktop
IID_IActiveDesktop  GUID _IID_IActiveDesktop
endif

.code

main proc

  local w:WALLPAPEROPT
  local p:LPACTIVEDESKTOP

    CoInitialize(NULL)
    CoCreateInstance(&CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER, &IID_IActiveDesktop, &p)
    p.SetWallpaper( BITMAP0, 0 )
    mov w.dwSize,sizeof(WALLPAPEROPT)
    mov w.dwStyle,WPSTYLE_CENTER
    p.SetWallpaperOptions( &w, 0 )
    p.ApplyChanges( AD_APPLY_ALL )
    p.Release()
    CoUninitialize()
    ret

main endp

    end
