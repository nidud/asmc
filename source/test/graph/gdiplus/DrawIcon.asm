include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"DrawIcon">

    .data
    g_hwnd HANDLE 0
    define __HWND__
    .code

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

    .new g:Graphics(hdc)
    .new hIcon:HICON

    .if ExtractIcon(g_hwnd, "C:\\Windows\\regedit.exe", 2)

        mov hIcon,rax

        .new b:Bitmap(hIcon)

        g.DrawImage(&b, 200.0, 100.0, 0.0, 0.0, 150.0, 48.0, UnitPixel)
        b.Release()
        DestroyIcon(hIcon)
    .endif
    g.Release()
    ret

OnPaint endp

include Graphics.inc

