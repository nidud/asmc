;
; https://docs.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-metafiles-about
;
include windows.inc
include gdiplus.inc
include tchar.inc

CLASSNAME equ <"Metafile">


    .data
    MetafileCreated BOOL FALSE

    .code

CreateMetafile proc uses rbx hdc:HDC

   .new m:Metafile(L"MyDiskFile.emf", hdc)
   .new g:Graphics(&m)
   .new p:GraphicsPath()
   .new b:Pen(Red)

    g.SetSmoothingMode(SmoothingModeAntiAlias)
    g.RotateTransform(30.0)
    p.AddEllipse(0, 0, 200, 100)

   .new r:Region(&p)

    g.SetClip(&r)
    g.DrawPath(&b, &p)

    .for ebx = 0: ebx <= 300: ebx += 10

        mov eax,300
        sub eax,ebx
        g.DrawLine(&b, 0, 0, eax, ebx)
    .endf
    p.Release()
    b.Release()
    g.Release()
    m.Release()
    mov MetafileCreated,TRUE
    ret

CreateMetafile endp

OnPaint proc hdc:HDC, ps:ptr PAINTSTRUCT

    .if MetafileCreated == FALSE

        CreateMetafile(hdc)
    .endif

   .new g:Graphics(hdc)
   .new i:Image(L"MyDiskFile.emf")

    g.DrawImage(&i, 10, 10)

    i.Release()
    g.Release()
    ret

OnPaint endp

include Graphics.inc
