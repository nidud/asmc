
CLASSNAME equ <"DrawIcon">

OnPaint macro hdc

    .new g:Graphics(hdc)
    .new hIcon:HICON

    .if ExtractIcon(hWnd, @CatStr(<!">, @Environ(HOMEDRIVE),<!">) "\\Windows\\regedit.exe", 2)

        mov hIcon,rax

        .new b:Bitmap(hIcon)

        g.DrawImage(&b, 200.0, 100.0, 0.0, 0.0, 150.0, 48.0, UnitPixel)
        b.Release()
        DestroyIcon(hIcon)
    .endif
    g.Release()

    exitm<>
    endm

include Graphics.inc

