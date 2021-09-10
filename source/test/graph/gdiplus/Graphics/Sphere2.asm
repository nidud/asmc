
CLASSNAME equ <"Sphere2">

OnPaint macro hdc

       .new g:Graphics(hdc)
       .new p:GraphicsPath()

       .new count:SINT
       .new FullTranslucent:ARGB
       .new x:real4
       .new y:real4
       .new w:real4

        p.AddEllipse(200, 0, 200, 200)

       .new b:PathGradientBrush(&p)

        b.SetCenterColor(ColorAlpha(Green, 180))

        mov count,1
        mov FullTranslucent,ColorAlpha(Black, 230)
        b.SetSurroundColors(&FullTranslucent, &count)
        g.SetSmoothingMode(SmoothingModeAntiAlias)
        g.FillEllipse(&b, 200 + 2, 0 + 2, 200 - 4, 200 - 4)
        b.Release()
        p.Release()

       .new z:PointF(20.0, 20.0)
       .new r:SolidBrush(Green)
       .new f:Font(L"Arial", 16.0)

        g.DrawString("Resize", 6, &f, &z, NULL, &r)
        f.Release()
        r.Release()

       .new p:GraphicsPath()

        mov eax,ps.rcPaint.right
        sub eax,ps.rcPaint.left
        inc eax
        mov ecx,ps.rcPaint.bottom
        sub ecx,ps.rcPaint.top
        inc ecx

        cvtsi2ss xmm0,eax
        cvtsi2ss xmm1,ecx
        movss    xmm2,xmm0
        comiss   xmm0,xmm1
        .ifb
           movss xmm2,xmm1
        .endif
        divss    xmm2,3.0
        subss    xmm0,xmm2
        divss    xmm0,2.0
        subss    xmm1,xmm2
        divss    xmm1,2.0

        movss    x,xmm0
        movss    y,xmm1
        movss    w,xmm2

        p.AddEllipse(xmm0, xmm1, xmm2, xmm2)

        mov count,1
        mov FullTranslucent,ColorAlpha(Red, 200)

       .new b:PathGradientBrush(&p)

        b.SetCenterColor(ColorAlpha(Yellow, 180))
        b.SetSurroundColors(&FullTranslucent, &count)

        movss xmm0,x
        movss xmm1,y
        movss xmm2,w
        addss xmm0,2.0
        addss xmm1,2.0
        subss xmm2,4.0

        g.FillEllipse(&b, xmm0, xmm1, xmm2, xmm2)

        b.Release()
        p.Release()
        g.Release()

    exitm<>
    endm

include Graphics.inc

