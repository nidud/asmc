;
; http://masm32.com/board/index.php?topic=5929.msg72217#msg72217
;
include windows.inc
include wininet.inc
include shlobj.inc

.code

SetBackground proc newbmp:wstring_t, oldbmp:wstring_t

  local w:WALLPAPEROPT
  local p:LPACTIVEDESKTOP

    CoInitialize(NULL)
    CoCreateInstance(&CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER, &IID_IActiveDesktop, &p)
    .if oldbmp
        p.GetWallpaper(oldbmp, 256, AD_GETWP_BMP)
    .endif
    p.SetWallpaper(newbmp, 0)
    mov w.dwSize,WALLPAPEROPT
    mov w.dwStyle,WPSTYLE_CENTER
    p.SetWallpaperOptions(&w, 0)
    p.ApplyChanges(AD_APPLY_ALL)
    p.Release()
    CoUninitialize()
    ret

SetBackground endp

main proc

  local oldbmp[256]:WCHAR

    SetBackground(L"%AsmcDir%\\source\\test\\wininc\\SetWallpaper\\test.bmp", &oldbmp)
    MessageBox(NULL, "A new background image has been installed.\n\n"
        "Hit OK to reset the old one.", "SetWallpaper", MB_OK)
    SetBackground(&oldbmp, NULL)
    ret

main endp

    end
