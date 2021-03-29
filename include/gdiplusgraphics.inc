ifndef _GDIPLUSGRAPHICS_H
_GDIPLUSGRAPHICS_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template Graphics

    nativeGraphics  ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    ; Graphics(HDC)
    ; Graphics(HDC, HANDLE)
    ; Graphics(HWND, BOOL = FALSE)
    ; Graphics(Image*)

    .inline Graphics :abs, :vararg {
        mov this.nativeGraphics,NULL
        this.typeid(Graphics, _1)(_1, _2)
        mov this.lastResult,eax
        }
    .inline GraphicsPVOID :abs, :vararg {
        GdipCreateFromHDC(_1, addr this.nativeGraphics)
        }
    .inline GraphicsREG64 :abs, :vararg {
        GdipCreateFromHDC(_1, addr this.nativeGraphics)
        }
    .inline GraphicsPHWND__ :abs, :abs=<FALSE> {
        if _2
            GdipCreateFromHWNDICM(_1, this)
        else
            GdipCreateFromHDC(_1, this)
        endif
        }
    .inline GraphicsPImage :ptr Image {
        xchg rcx,rdx
        GdipGetImageGraphicsContext([rcx].Image.nativeImage, &[rdx].Graphics.nativeGraphics)
        }
    .inline GraphicsPMetafile :ptr Metafile {
        xchg rcx,rdx
        GdipGetImageGraphicsContext([rcx].Image.nativeImage, &[rdx].Graphics.nativeGraphics)
        }

    .inline GraphicsPGraphics :ptr Graphics, :vararg {
        mov eax,Ok
        mov this.nativeGraphics,rdx
        }

    .inline Release {
        GdipDeleteGraphics([rcx].Graphics.nativeGraphics)
        }

    .inline SetNativeGraphics :ptr GpGraphics {
        mov [this].Graphics.nativeGraphics,_1
        }

    .inline SetStatus :vararg {
        ifnb <_1>
            ifdif <_1>,<eax>
                mov eax,_1
            endif
        endif
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .inline GetNativeGraphics {
        mov rax,[this].Graphics.nativeGraphics
        }

    .inline GetNativePen :ptr Pen {
        mov rax,[this].Pen.nativePen
        }

    .inline Flush :FlushIntention {
        GdipFlush([this].Graphics.nativeGraphics, _1)
        }

    ;;------------------------------------------------------------------------
    ;; GDI Interop methods
    ;;------------------------------------------------------------------------

    ;; Locks the graphics until ReleaseDC is called

    .inline GetHDC :vararg {

        .new hdc:HDC

        mov hdc,NULL
        GdipGetDC(this.nativeGraphics, &hdc)
        GdipSetStatus(this)
        mov rax,hdc
        }

    .inline ReleaseHDC :vararg {
        GdipReleaseDC(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    ;;------------------------------------------------------------------------
    ;; Rendering modes
    ;;------------------------------------------------------------------------

    .inline SetRenderingOrigin :vararg {
        GdipSetRenderingOrigin(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline GetRenderingOrigin :vararg {
        GdipGetRenderingOrigin(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline SetCompositingMode :vararg {
        GdipSetCompositingMode(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline GetCompositingMode :vararg {
        GdipGetCompositingMode(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetCompositingQuality :vararg {
        GdipSetCompositingQuality(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline GetCompositingQuality :vararg {
        GdipGetCompositingQuality(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetTextRenderingHint :vararg {
        GdipSetTextRenderingHint(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline GetTextRenderingHint :vararg {
        GdipGetTextRenderingHint(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetTextContrast :vararg {
        GdipSetTextContrast(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline GetTextContrast :vararg {
        GdipGetTextContrast(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline GetInterpolationMode :vararg {
        mov this.scratch,InterpolationModeInvalid
        GdipGetInterpolationMode(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetInterpolationMode :vararg {
        GdipSetInterpolationMode(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

if (GDIPVER GE 0x0110)

    .inline SetAbort :vararg {
        GdipGraphicsSetAbort(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

endif

    .inline GetSmoothingMode :vararg {
        mov this.scratch,SmoothingModeInvalid
        GdipGetSmoothingMode(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetSmoothingMode :vararg {
        GdipSetSmoothingMode(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline GetPixelOffsetMode :vararg {
        mov this.scratch,PixelOffsetModeInvalid
        GdipGetPixelOffsetMode(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetPixelOffsetMode :vararg {
        GdipSetPixelOffsetMode(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    ;;------------------------------------------------------------------------
    ;; Manipulate current world transform
    ;;------------------------------------------------------------------------

    .inline SetTransform :ptr Matrix, :vararg {
        GdipSetWorldTransform(this.nativeGraphics, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }
    .inline ResetTransform :vararg {
        GdipResetWorldTransform(this.nativeGraphics)
        GdipSetStatus(this)
        }

    .inline MultiplyTransform :ptr Matrix, :vararg {
        GdipMultiplyWorldTransform(this.nativeGraphics, [rdx].Matrix.nativeMatrix, _2)
        GdipSetStatus(this)
        }

    .inline TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipTranslateWorldTransform(this.nativeGraphics, _1, _2, _3)
        GdipSetStatus(this)
        }

    .inline ScaleTransform :abs, :abs, :vararg {
        ifb<_3>
            GdipScaleWorldTransform(this.nativeGraphics, _1, _2, MatrixOrderPrepend)
        else
            GdipScaleWorldTransform(this.nativeGraphics, _1, _2, _3)
        endif
        GdipSetStatus(this)
        }

    .inline RotateTransform :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipRotateWorldTransform(this.nativeGraphics, _1, _2)
        GdipSetStatus(this)
        }

    .inline GetTransform :ptr Matrix, :vararg {
        GdipGetWorldTransform(this.nativeGraphics, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .inline SetPageUnit :vararg {
        GdipSetPageUnit(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline SetPageScale :vararg {
        GdipSetPageScale(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline GetPageUnit :vararg {
        GdipGetPageUnit(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline GetPageScale :vararg {
        GdipGetPageScale(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        movss xmm0,this.scratch
        }

    .inline GetDpiX :vararg {
        GdipGetDpiX(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        movss xmm0,this.scratch
        }

    .inline GetDpiY :vararg {
        GdipGetDpiY(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        movss xmm0,this.scratch
        }

    .inline TransformPoints :abs, :abs, :abs, :vararg {
        this.typeid(TransformPoints, _3)(_1, _2, _3, _4)
        GdipSetStatus(this)
        }
    .inline TransformPointsPPointF :vararg {
        GdipTransformPoints(this.nativeGraphics, _1)
        }
    .inline TransformPointsPPoint :vararg {
        GdipTransformPointsI(this.nativeGraphics, _1)
        }

    ;;------------------------------------------------------------------------
    ;; GetNearestColor (for <= 8bpp surfaces).  Note: Alpha is ignored.
    ;;------------------------------------------------------------------------

    .inline GetStatus {
        mov eax,[this].Graphics.lastResult
        }

    .inline GetNearestColor :vararg {
        GdipGetNearestColor(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

typeid_flti32 macro name, arg_id
    .inline name :abs, :abs, :vararg {
        this.typeid(name, arg_id)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline &name&REG128 :vararg { this.&name&IMMFLT(_1) }
    .inline &name&REAL4  :vararg { this.&name&IMMFLT(_1) }
    .inline &name&REG32  :vararg { this.&name&IMM32(_1) }
    .inline &name&SDWORD :vararg { this.&name&IMM32(_1) }
    exitm<>
    endm

typeid_Point macro name
    .inline &name&PPointF :abs, :ptr PointF, :ptr PointF, :vararg {
        this.&name&IMMFLT(_1, [r8].PointF.X, [r8].PointF.Y, [r9].PointF.X, [r9].PointF.Y)
        }
    .inline &name&PPoint :abs, :ptr Point, :ptr Point, :vararg {
        this.&name&IMM32(_1, [r8].Point.X, [r8].Point.Y, [r9].Point.X, [r9].Point.Y)
        }
    exitm<>
    endm

typeid_Rect macro name
    .inline &name&PRectF :abs, :ptr RectF, :vararg {
        this.&name&IMMFLT(_1, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width, [r8].RectF.Height, _3)
        }
    .inline &name&PRect :abs, :ptr Rect, :vararg {
        this.&name&IMM32(_1, [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width, [r8].Rect.Height, _3)
        }
    exitm<>
    endm


    typeid_flti32(DrawLine, _2)

    .inline DrawLineIMMFLT :ptr Pen, :vararg {
        GdipDrawLine(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawLineIMM32 :ptr Pen, :vararg {
        GdipDrawLineI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_Point(DrawLine)

    .inline DrawLines :abs, :abs, :vararg {
        this.typeid(DrawLines, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline DrawLinesPPointF :ptr Pen, :vararg {
        GdipDrawLines(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawLinesPPoint :ptr Pen, :vararg {
        GdipDrawLinesI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_flti32(DrawArc, _2)

    .inline DrawArcIMMFLT :ptr Pen, :vararg {
        GdipDrawArc(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawArcIMM32 :ptr Pen, :vararg {
        GdipDrawArcI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_Rect(DrawArc)

    typeid_flti32(DrawBezier, _2)

    .inline DrawBezierIMMFLT :ptr Pen, :vararg {
        GdipDrawBezier(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawBezierIMM32 :ptr Pen, :vararg {
        GdipDrawBezierI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    .inline DrawBezierPPointF :abs, :ptr PointF, :ptr PointF, :ptr PointF, :ptr PointF, :vararg {
        mov r10,[rsp+8*4]
        mov r11,[rsp+8*5]
        this.DrawBezierIMMFLT(_1, [r8].PointF.X, [r8].PointF.Y, [r9].PointF.X, [r9].PointF.Y,\
            [r10].PointF.X, [r10].PointF.Y, [r11].PointF.X, [r11].PointF.Y )
        }
    .inline DrawBezierPPoint :abs, :ptr Point, :ptr Point, :ptr Point, :ptr Point, :vararg {
        mov r10,[rsp+8*4]
        mov r11,[rsp+8*5]
        this.DrawBezierIMM32(_1, [r8].Point.X, [r8].Point.Y, [r9].Point.X, [r9].Point.Y,\
            [r10].Point.X, [r10].Point.Y, [r11].Point.X, [r11].Point.Y )
        }


    .inline DrawBeziers :abs, :abs, :vararg {
        this.typeid(DrawBeziers, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline DrawBeziersPPointF :ptr Pen, :vararg {
        GdipDrawBeziers(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawBeziersPPoint :ptr Pen, :vararg {
        GdipDrawBeziersI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_flti32(DrawRectangle, _2)

    .inline DrawRectangleIMMFLT :ptr Pen, :vararg {
        GdipDrawRectangle(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawRectangleIMM32 :ptr Pen, :vararg {
        GdipDrawRectangleI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    .inline DrawRectanglePRectF :abs, :ptr RectF, :vararg {
        this.DrawRectangleIMMFLT(_1, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width, [r8].RectF.Height, _3)
        }
    .inline DrawRectanglePRect :abs, :ptr Rect, :vararg {
        this.DrawRectangleIMM32(_1, [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width, [r8].Rect.Height, _3)
        }

    .inline DrawRectangles :abs, :abs, :vararg {
        this.typeid(DrawRectangles, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline DrawRectanglesPRectF :ptr Pen, :vararg {
        GdipDrawRectangles(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawRectanglesPRect :ptr Pen, :vararg {
        GdipDrawRectanglesI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }


    typeid_flti32(DrawEllipse, _2)

    .inline DrawEllipseIMMFLT :ptr Pen, :vararg {
        GdipDrawEllipse(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawEllipseIMM32 :ptr Pen, :vararg {
        GdipDrawEllipseI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_Rect(DrawEllipse)

    typeid_flti32(DrawPie, _2)

    .inline DrawPieIMMFLT :ptr Pen, :vararg {
        GdipDrawPie(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawPieIMM32 :ptr Pen, :vararg {
        GdipDrawPieI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_Rect(DrawPie)

    .inline DrawPolygon :abs, :abs, :vararg {
        this.typeid(DrawPolygon, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline DrawPolygonPPointF :ptr Pen, :vararg {
        GdipDrawPolygon(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .inline DrawPolygonPPoint :ptr Pen, :vararg {
        GdipDrawPolygonI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    .inline DrawPath :ptr Pen, :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx]
        .endif
        .if r8
            mov r8,[r8]
        .endif
        GdipDrawPath(this.nativeGraphics, rdx, r8)
        GdipSetStatus(this)
        }

    .inline DrawCurve :abs, :abs, :vararg {
        this.typeid(DrawCurve, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline DrawCurvePPointF :ptr Pen, :abs, :abs, :abs, :abs, :abs=<0.5>, :vararg {
        ifb <_4>
            GdipDrawCurve(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
        elseifb <_5>
            GdipDrawCurve2(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4)
        else
            GdipDrawCurve3(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4, _5, _6)
        endif
        }
    .inline DrawCurvePPoint :ptr Pen, :abs, :abs, :abs, :abs, :abs=<0.5>, :vararg {
        ifb <_4>
            GdipDrawCurveI(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
        elseifb <_5>
            GdipDrawCurve2I(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4)
        else
            GdipDrawCurve3I(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4, _5, _6)
        endif
        }


    .inline DrawClosedCurve :abs, :abs, :vararg {
        this.typeid(DrawClosedCurve, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline DrawClosedCurvePPointF :ptr Pen, :abs, :abs, :abs, :vararg {
        ifb <_4>
            GdipDrawClosedCurve(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
        else
            GdipDrawClosedCurve2(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4)
        endif
        }
    .inline DrawClosedCurvePPoint :ptr Pen, :abs, :abs, :abs, :vararg {
        ifb <_4>
            GdipDrawClosedCurveI(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
        else
            GdipDrawClosedCurve2I(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4)
        endif
        }

    .inline Clear :vararg {
        GdipGraphicsClear(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    typeid_flti32(FillRectangle, _2)

    .inline FillRectangleIMMFLT :ptr Brush, :vararg {
        GdipFillRectangle(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }
    .inline FillRectangleIMM32 :ptr Brush, :vararg {
        GdipFillRectangleI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }

    typeid_Rect(FillRectangle)

    .inline FillRectangles :abs, :abs, :vararg {
        this.typeid(FillRectangles, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline FillRectanglesPRectF :ptr Brush, :vararg {
        GdipFillRectangles(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }
    .inline FillRectanglesPRect :ptr Brush, :vararg {
        GdipFillRectanglesI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }


    .inline FillPolygon :abs, :abs, :vararg {
        this.typeid(FillPolygon, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline FillPolygonPPointF :ptr Brush, :abs, :abs, :abs=<FillModeAlternate>, :vararg {
        GdipFillPolygon(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3, _4)
        }
    .inline FillPolygonPPoint :ptr Brush, :abs, :abs, :abs=<FillModeAlternate>, :vararg {
        GdipFillPolygonI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3, _4)
        }


    typeid_flti32(FillEllipse, _2)

    .inline FillEllipseIMMFLT :ptr Brush, :vararg {
        GdipFillEllipse(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }
    .inline FillEllipseIMM32 :ptr Brush, :vararg {
        GdipFillEllipseI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }

    typeid_Rect(FillEllipse)


    typeid_flti32(FillPie, _2)

    .inline FillPieIMMFLT :ptr Brush, :vararg {
        GdipFillPie(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }
    .inline FillPieIMM32 :ptr Brush, :vararg {
        GdipFillPieI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }

    typeid_Rect(FillPie)

    .inline FillPath :ptr Brush, :ptr GraphicsPath, :vararg {
        GdipFillPath(this.nativeGraphics, [rdx].Brush.nativeBrush, [r8].GraphicsPath.nativePath)
        GdipSetStatus(this)
        }

    .inline FillClosedCurve :abs, :abs, :vararg {
        this.typeid(FillClosedCurve, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline FillClosedCurvePPointF :ptr Brush, :abs, :abs, :abs, :abs=<0.5>, :vararg {
        ifb <_4>
            GdipFillClosedCurve(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
        else
            GdipFillClosedCurve2(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3, _5, _4)
        endif
        }
    .inline FillClosedCurvePPoint :ptr Brush, :abs, :abs, :abs, :abs=<0.5>, :vararg {
        ifb <_4>
            GdipFillClosedCurveI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
        else
            GdipFillClosedCurve2I(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3, _5, _4)
        endif
        }


    .inline FillRegion :ptr Brush, :ptr Region, :vararg {
        GdipFillRegion(this.nativeGraphics, [rdx].Brush.nativeBrush, [r8].Region.nativeRegion)
        GdipSetStatus(this)
        }

    ; DrawString(WCHAR*, INT, Font*, RectF*, StringFormat *, Brush*)

    .inline DrawString :abs, :abs, :ptr Font, :ptr RectF, :ptr StringFormat, :ptr Brush, :vararg {

        .if r9
            mov r9,[r9].Font.nativeFont
        .endif
        mov rax,[rsp+8*4]
        mov r10,[rsp+8*5]
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        mov r11,[rsp+8*6]
        .if r11
            mov r11,[r11].Brush.nativeBrush
        .endif
        GdipDrawString(this.nativeGraphics, _1, _2, r9, rax, r10, r11)
        GdipSetStatus(this)
        }

    .inline MeasureString :abs, :abs, :abs, :abs, :vararg {
        this.typeid(MeasureString, _4)(_1, _2, _3, _4, _5)
        }
    .inline MeasureStringPRectF :abs, :abs, :abs, :abs, :abs, :vararg {
        this.typeid(MeasureStringPRectF, _5)(_1, _2, _3, _4, _5, _6)
        }

    ; MeasureString(WCHAR*, INT, Font*, RectF*, StringFormat*, RectF*, INT* = 0, INT* = 0)

    .inline MeasureStringPRectFPStringFormat :abs, :abs, :ptr Font, :ptr RectF, :ptr StringFormat, :abs, :abs=<0>, :abs=<0>, :vararg {
        .if r9
            mov r9,[r9].Font.nativeFont
        .endif
        mov r10,[rsp+8*4]
        mov r11,[rsp+8*5]
        .if r11
            mov r11,[r11].StringFormat.nativeFormat
        .endif
        GdipMeasureString(this.nativeGraphics, _1, _2, r9, r10, r11, _6, _7, _8)
        GdipSetStatus(this)
        }

    ; MeasureString(WCHAR*, INT, Font*, SizeF*, StringFormat*, SizeF*, INT* = 0, INT* = 0)

    .inline MeasureStringPSizeF :abs, :abs, :ptr Font, :ptr SizeF, :ptr StringFormat, :ptr SizeF, :abs=<0>, :abs=<0>, :vararg {

        .new layoutRect:RectF
        .new boundingBox:RectF
        .new size:ptr RectF

        mov r10,[rsp+8*4]
        mov size,r10
        mov layoutRect.X,0.0
        mov layoutRect.Y,0.0
        mov layoutRect.Width,[r10].SizeF.Width
        mov layoutRect.Height,[r10].SizeF.Height
        mov r10,[rsp+8*6]
        .if r10 == NULL
            mov eax,InvalidParameter
        .else
            .if r9
                mov r9,[r9].Font.nativeFont
            .endif
            mov r10,[rsp+8*5]
            .if r10
                mov r10,[r10].StringFormat.nativeFormat
            .endif
            GdipMeasureString(this.nativeGraphics, _1, _2, r9, &layoutRect, r10, &boundingBox, _7, _8)

            .if eax == Ok
                mov r10,size
                mov [r10].RectF.Width,  boundingBox.Width
                mov [r10].RectF.Height, boundingBox.Height
                xor eax,eax
            .endif
        .endif
        GdipSetStatus(this)
        }

    ; MeasureString(WCHAR*, INT, Font*, PointF*, StringFormat*, RectF*)

    .inline MeasureStringPPointF :abs, :abs, :abs, :abs, :abs, :vararg {
        this.typeid(MeasureStringPPointF, _5)(_1, _2, _3, _4, _5, _6)
        }

    .inline MeasureStringPPointFPStringFormat :abs, :abs, :ptr Font, :ptr PointF, :ptr StringFormat, :abs, :vararg {

       .new rect:RectF

        mov r10,[rsp+8*4]
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.Width,0.0
        mov rect.Height,0.0
        .if r9
            mov r9,[r9].Font.nativeFont
        .endif
        mov r10,[rsp+8*5]
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        GdipMeasureString(this.nativeGraphics, _1, _2, r9, &rect, r10, _6, NULL, NULL)
        GdipSetStatus(this)
        }

    ; MeasureString(WCHAR*, INT, Font*, RectF*, RectF*)

    .inline MeasureStringPRectFPRectF :abs, :abs, :ptr Font, :abs, :abs, :vararg {
        .if r9
            mov r9,[r9].Font.nativeFont
        .endif
        GdipMeasureString(this.nativeGraphics, _1, _2, r9, _4, NULL, _5, NULL, NULL)
        GdipSetStatus(this)
        }


    ; MeasureString(WCHAR*, INT, Font*, PointF*, RectF*)

    .inline MeasureStringPPointFPRectF :abs, :abs, :ptr Font, :ptr PointF, :ptr RectF, :vararg {

       .new rect:RectF
        mov r10,[rsp+8*4]
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.Width,0.0
        mov rect.Height,0.0
        .if r9
            mov r9,[r9].Font.nativeFont
        .endif
        GdipMeasureString(this.nativeGraphics, _1, _2, r9, &rect, NULL, _5, NULL, NULL)
        GdipSetStatus(this)
        }

    .inline MeasureCharacterRanges :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :SINT, :ptr Region, :vararg {

        .repeat
            .if qword ptr [rsp+7*8] == 0 || sdword ptr [rsp+6*8] <= 0
                mov eax,InvalidParameter
                .break
            .endif

            .new string:ptr word
            .new length:SINT
            .new nativeRegions:ptr Region

            mov string,rdx
            mov length,r8d
            mov nativeRegions,r9

            mov ecx,[rsp+6*8]
            GdipAlloc( &[rcx*8] )
            .if rax == NULL
                mov eax,OutOfMemory
                .break
            .endif
            .for (r8 = rax, rdx = [rsp+7*8], ecx = 0: ecx < [rsp+6*8]: ecx++, rdx += Region)
                mov [r8+rcx*8],[rdx].Region.nativeRegion
            .endf
            mov r9,nativeRegions
            mov nativeRegions,r8
            .if r9
                mov r9,[r9].Font.nativeFont
            .endif
            mov rcx,[rsp+5*8]
            .if rcx
                mov rcx,[rcx].StringFormat.nativeFormat
            .endif
            mov rdx,[rsp+4*8]
            mov r8d,[rsp+6*8]
            mov length,GdipMeasureCharacterRanges(this.nativeGraphics, string, length, r9, rdx, rcx, r8d, nativeRegions)
            GdipFree(nativeRegions)
            mov eax,length
        .until 1
        this.SetStatus()
        }

    .inline DrawDriverString :abs, :abs, :ptr Font, :ptr Brush, :abs, :abs, :ptr Matrix, :vararg {
        .if r9
            mov r9,[r9].Font.nativeFont
        .endif
        mov r10,[rsp+8*4]
        .if r10
            mov r10,[r10].Brush.nativeBrush
        .endif
        mov r11,[rsp+8*7]
        .if r11
            mov r11,[r11].Matrix.nativeMatrix
        .endif
        GdipDrawDriverString(this.nativeGraphics, _1, _2, _3, r10, _5, _6, r11)
        GdipSetStatus(this)
        }

    .inline MeasureDriverString :abs, :abs, :ptr Font, :abs, :abs, :ptr Matrix, :vararg {
        .if r9
            mov r9,[r9].Font.nativeFont
        .endif
        mov r10,[rsp+8*6]
        .if r10
            mov r10,[r10].Matrix.nativeMatrix
        .endif
        GdipMeasureDriverString(this.nativeGraphics, _1, _2, r9, _4, _5, r10, _7)
        GdipSetStatus(this)
        }

    ;; Draw a cached bitmap on this graphics destination offset by
    ;; x, y. Note this will fail with WrongState if the CachedBitmap
    ;; native format differs from this Graphics.

    .inline DrawCachedBitmap :ptr CachedBitmap, :vararg {
        GdipDrawCachedBitmap(this.nativeGraphics, [rdx].CachedBitmap.nativeCachedBitmap, _2)
        GdipSetStatus(this)
        }

    .inline DrawImage :ptr Image, :abs, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        this.typeid(DrawImage, _2)(_1, _2, _3)
        this.SetStatus()
        }

    ; DrawImage(Image*, PointF*)
    ; DrawImage(Image*, PointF*, INT)
    ; DrawImage(Image*, PointF*, INT, REAL, REAL, REAL, REAL, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)

    .inline DrawImagePPointF :abs, :ptr PointF, :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
        ifb <_3>
            this.DrawImageIMMFLT(rdx, [r8].PointF.X, [r8].PointF.Y)
        elseifb <_4>
            mov r9d,_3
            .if r9d != 3 && r9d != 4
                mov eax,InvalidParameter
            .else
                GdipDrawImagePoints(this.nativeGraphics, rdx, r8, r9d)
            .endif
        else
            mov r10,_9
            .if r10
                mov r10,[r10].ImageAttributes.nativeImageAttr
            .endif
            GdipDrawImagePointsRect(this.nativeGraphics, rdx, r8, _3, _4, _5, _6, _7, _8, r10, _10, _11)
        endif
        }

    ; DrawImage(Image*, Point*)
    ; DrawImage(Image*, Point*, INT)
    ; DrawImage(Image*, Point*, INT, INT, INT, INT, INT, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)

    .inline DrawImagePPoint :abs, :ptr Point, :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
        ifb <_3>
            this.DrawImageIMM32(rdx, [r8].Point.X, [r8].Point.Y)
        elseifb <_4>
            mov r9d,_3
            .if r9d != 3 && r9d != 4
                mov eax,InvalidParameter
            .else
                GdipDrawImagePointsI(this.nativeGraphics, rdx, r8, r9d)
            .endif
        else
            mov r10,_9
            .if r10
                mov r10,[r10].ImageAttributes.nativeImageAttr
            .endif
            GdipDrawImagePointsRectI(this.nativeGraphics, rdx, r8, _3, _4, _5, _6, _7, _8, r10, _10, _11)
        endif
        }

    ; DrawImage(Image*, RectF*)

    .inline DrawImagePRectF :abs, :ptr RectF, :abs, :vararg {
        ifb <_3>
            this.DrawImageIMMFLT(rdx, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width, [r8].RectF.Height)
        else
            this.typeid(DrawImagePRectF, _3)(rdx, r8, _3, _4)
        endif
        }

    ; DrawImage(Image*, RectF*, REAL, REAL, REAL, REAL, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)

    .inline DrawImagePRectFIMMFLT :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
        this.typeid(DrawImagePRectFIMMFLT, _8)(rdx, r8, _3, _4, _5, _6, _7, _8, _9, _10)
        }
    .inline DrawImagePRectFIMM32 :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs, :vararg {
        GdipDrawImageRectRect(this.nativeGraphics, rdx, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width,\
            [r8].RectF.Height, _3, _4, _5, _6, _7, _8, _9, _10)
        }
    .inline DrawImagePRectFIMMFLTPImageAttributes :abs, :abs, :abs, :abs, :abs, :abs, :abs, :ptr ImageAttributes, :abs, :abs, :vararg {
        mov r10,[rsp+8*8]
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRect(this.nativeGraphics, rdx, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width,\
            [r8].RectF.Height, _3, _4, _5, _6, _7, r10, _9, _10)
        }
    .inline DrawImagePRectFREAL4 :vararg {
        this.DrawImagePRectFIMMFLT(_1)
        }

if (GDIPVER GE 0x0110)

    ; DrawImage(Image*, RectF*, RectF*, Unit, ImageAttributes* = NULL)

    .inline DrawImagePRectFPRectF :abs, :ptr RectF, :ptr RectF, :abs, :abs=<0>, :vararg {
        mov r10,_5
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRect(this.nativeGraphics, rdx, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width,\
            [r8].RectF.Height, [r9].RectF.X, [r9].RectF.Y, [r9].RectF.Width, [r9].RectF.Height,\
            _4, r10, NULL, NULL)
        }

    ; DrawImage(Image*, RectF*, Matrix*, Effect*, ImageAttributes*, Unit)

    .inline DrawImagePRectFPMatrix :abs, :abs, :ptr Matrix, :ptr Effect, :ptr ImageAttributes, :abs, :vararg {
        .if r9
            mov r9,[r9].Matrix.nativeMatrix
        .endif
        mov r10,[rsp+8*4]
        .if r10
            mov r10,[r10].Effect.nativeEffect
        .endif
        mov r11,[rsp+8*5]
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageFX(this.nativeGraphics, rdx, r8, r9, r10, r11, _6)
        }
endif

    ; DrawImage(Image*, Rect*)
    ; DrawImage(Image*, Rect*, INT, INT, INT, INT, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)

    .inline DrawImagePRect :abs, :ptr Rect, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
        ifb <_3>
            this.DrawImageIMM32(rdx, [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width, [r8].Rect.Height)
        else
            this.typeid(DrawImagePRect, _8)(rdx, r8, _3, _4, _5, _6, _7, _8, _9, _10)
        endif
        }
    .inline DrawImagePRectIMM32 :abs, :ptr Rect, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
        GdipDrawImageRectRectI(this.nativeGraphics, rdx, [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width,\
            [r8].Rect.Height, _3, _4, _5, _6, _7, _8, _9, _10)
        }
    .inline DrawImagePRectPImageAttributes :abs, :ptr Rect, :abs, :abs, :abs, :abs, :abs, :ptr ImageAttributes, :abs, :abs, :vararg {
        mov r10,[rsp+8*8]
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRectI(this.nativeGraphics, rdx, [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width,\
            [r8].Rect.Height, _3, _4, _5, _6, _7, r10, _9, _10)
        }



    ; DrawImage(Image*, REAL, REAL)
    ; DrawImage(Image*, REAL, REAL, REAL, REAL)
    ; DrawImage(Image*, REAL, REAL, REAL, REAL, REAL, REAL, Unit)

    .inline DrawImageIMMFLT :abs, :abs, :abs, :abs, :abs, :abs, :vararg {
        ifb <_4>
            GdipDrawImage(this.nativeGraphics, rdx, _2, _3)
        elseifb <_6>
            GdipDrawImageRect(this.nativeGraphics, rdx, _2, _3, _4, _5)
        else
            GdipDrawImagePointRect(this.nativeGraphics, rdx, _2, _3, _4, _5, _6, _7)
        endif
        }

    ; DrawImage(Image*, INT, INT)
    ; DrawImage(Image*, INT, INT, INT, INT)
    ; DrawImage(Image*, INT, INT, INT, INT, INT, INT, Unit)

    .inline DrawImageIMM32 :abs, :abs, :abs, :abs, :abs, :abs, :vararg {
        ifb <_4>
            GdipDrawImageI(this.nativeGraphics, rdx, _2, _3)
        elseifb <_6>
            GdipDrawImageRectI(this.nativeGraphics, rdx, _2, _3, _4, _5)
        else
            GdipDrawImagePointRectI(this.nativeGraphics, rdx, _2, _3, _4, _5, _6, _7)
        endif
        }

    ;; The following methods are for playing an EMF+ to a graphics
    ;; via the enumeration interface.  Each record of the EMF+ is
    ;; sent to the callback (along with the callbackData).  Then
    ;; the callback can invoke the Metafile::PlayRecord method
    ;; to play the particular record.

    .inline EnumerateMetafile :ptr Image, :abs, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        this.typeid(EnumerateMetafile, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .inline EnumerateMetafilePPointF :abs, :ptr PointF, :abs, :vararg {
        this.typeid(EnumerateMetafilePPointF, _3)(_1, _2, _3, _4)
        }
    .inline EnumerateMetafilePPoint :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafilePPoint, _3)(_1, _2, _3, _4)
        }
    .inline EnumerateMetafilePRectF :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafilePRectF, _3)(_1, _2, _3, _4)
        }
    .inline EnumerateMetafilePRect :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafilePRect, _3)(_1, _2, _3, _4)
        }
    .inline EnumerateMetafilePPointFIMM32 :abs, :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafilePPointFIMM32, _4)(_1, _2, _3, _4, _5)
        }
    .inline EnumerateMetafilePPointIMM32 :abs, :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafilePPointIMM32, _4)(_1, _2, _3, _4, _5)
        }

    ; EnumerateMetafile(Metafile*, PointF*, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePPointFPNEAR :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPoint(this.nativeGraphics, rdx, _2, _3, _4, r11)
        }

    ; EnumerateMetafile(Metafile*, PointF*, INT, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePPointFIMM32PNEAR :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_6
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPoints(this.nativeGraphics, _1, _2, _3, _4, _5, r11)
        }

    ; EnumerateMetafile(Metafile*, PointF*, INT, RectF*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePPointFIMM32PRectF :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        }

    ; EnumerateMetafile(Metafile*, PointF*, RectF*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePPointFPRectF :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPoint(this.nativeGraphics, _1, _2, _3, _4, _5, _6, r11)
        }

    ; EnumerateMetafile(Metafile*, Point*, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePPointPNEAR :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPointI(this.nativeGraphics, rdx, _2, _3, _4, r11)
        }

    ; EnumerateMetafile(Metafile*, Point*, INT, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePPointIMM32PNEAR :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_6
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPointsI(this.nativeGraphics, _1, _2, _3, _4, _5, r11)
        }

    ; EnumerateMetafile(Metafile*, Point*, INT, Rect*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePPointIMM32PRect :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        }

    ; EnumerateMetafile(Metafile*, Point*, Rect*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePPointPRect :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPointI(this.nativeGraphics, _1, _2, _3, _4, _5, _6, r11)
        }

    ; EnumerateMetafile(Metafile*, RectF*, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePRectFPNEAR :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestRect(this.nativeGraphics, rdx, _2, _3, _4, r11)
        }

    ; EnumerateMetafile(Metafile*, RectF*, RectF*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePRectFPRectF :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestRect(this.nativeGraphics, rdx, _2, _3, _4, _5, _6, r11)
        }

    ; EnumerateMetafile(Metafile*, Rect*, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePRectPNEAR :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestRectI(this.nativeGraphics, _1, _2, _3, _4, r11)
        }

    ; EnumerateMetafile(Metafile*, Rect*, Rect*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .inline EnumerateMetafilePRectPRect :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestRectI(this.nativeGraphics, rdx, _2, _3, _4, _5, _6, r11)
        }


    .inline SetClip :abs, :vararg {
        this.typeid(SetClip , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline SetClipPGraphics :ptr Graphics, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipGraphics(this.nativeGraphics, [rdx].Graphics.nativeGraphics, _2)
        }
    .inline SetClipPRectF :ptr RectF, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipRect(this.nativeGraphics,\
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
        }
    .inline SetClipPRect :ptr Rect, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipRectI(this.nativeGraphics,\
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
        }
    .inline SetClipPGraphicsPath :ptr GraphicsPath, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipPath(this.nativeGraphics, [rdx].GraphicsPath.nativePath, _2)
        }
    .inline SetClipPRegion :ptr Region, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipRegion(this.nativeGraphics, [rdx].Region.nativeRegion, _2)
        }

    ;; This is different than the other SetClip methods because it assumes
    ;; that the HRGN is already in device units, so it doesn't transform
    ;; the coordinates in the HRGN.

    .inline SetClipPVOID :abs, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipHrgn(this.nativeGraphics, _1, _2)
        }

    .inline IntersectClip :abs, :vararg {
        this.typeid(IntersectClip , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline IntersectClipPRectF :ptr RectF, :vararg {
        GdipSetClipRect(this.nativeGraphics,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width,\
                [rdx].RectF.Height, CombineModeIntersect)
        }
    .inline IntersectClipPRect :ptr Rect, :vararg {
        GdipSetClipRectI(this.nativeGraphics,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, CombineModeIntersect)
        }
    .inline IntersectClipPRegion :ptr Region, :vararg {
        GdipSetClipRegion(this.nativeGraphics,\
                [rdx].Region.nativeRegion, CombineModeIntersect)
        }

    .inline ExcludeClip :abs, :vararg {
        this.typeid(ExcludeClip , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline ExcludeClipPRectF :ptr RectF, :vararg {
        GdipSetClipRect(this.nativeGraphics,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, CombineModeExclude)
        }
    .inline ExcludeClipPRect :ptr Rect, :vararg {
        GdipSetClipRectI(this.nativeGraphics,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, CombineModeExclude)
        }
    .inline ExcludeClipPRegion :ptr Region, :vararg {
        GdipSetClipRegion(this.nativeGraphics, [rdx].Region.nativeRegion, CombineModeExclude)
        }

    .inline ResetClip :vararg {
        GdipResetClip(this.nativeGraphics)
        GdipSetStatus(this)
        }

    .inline TranslateClip :abs, :vararg {
        this.typeid(TranslateClip , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline TranslateClipIMMFLT :vararg {
        GdipTranslateClip(this.nativeGraphics, _1)
        }
    .inline TranslateClipIMM32 :vararg {
        GdipTranslateClipI(this.nativeGraphics, _1)
        }

    .inline GetClip :ptr, :vararg {
        GdipGetClip(this.nativeGraphics, [rdx].Region.nativeRegion)
        GdipSetStatus(this)
        }

    .inline GetClipBounds :abs, :vararg {
        this.typeid(GetClipBounds , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline GetClipBoundsPRectF :vararg  {
        GdipGetClipBounds(this.nativeGraphics, _1)
        }
    .inline GetClipBoundsPRect :vararg {
        GdipGetClipBoundsI(this.nativeGraphics, _1)
        }

    .inline IsClipEmpty :vararg {
        mov this.scratch,FALSE
        GdipIsClipEmpty(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline GetVisibleClipBounds :abs, :vararg {
        this.typeid(GetVisibleClipBounds, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline GetVisibleClipBoundsPRectF :abs, :vararg {
        GdipGetVisibleClipBounds(this.nativeGraphics, _1)
        }
    .inline GetVisibleClipBoundsPRect :abs, :vararg {
        GdipGetVisibleClipBoundsI(this.nativeGraphics, _1)
        }

    .inline IsVisibleClipEmpty :vararg {
        mov this.scratch,FALSE
        GdipIsVisibleClipEmpty(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline IsVisible :abs, :vararg {
        this.typeid(IsVisible, _1)(_1, _2)
        }
    .inline IsVisiblePPoint :ptr Point, :vararg {
        mov this.scratch,FALSE
        GdipIsVisiblePointI(this.nativeGraphics, [rdx].Point.X, [rdx].Point.Y, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .inline IsVisiblePRect :ptr Rect, :vararg {
        mov this.scratch,TRUE
        GdipIsVisibleRectI(this.nativeGraphics,\
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .inline IsVisiblePPointF :ptr PointF, :vararg {
        mov this.scratch,FALSE
        GdipIsVisiblePoint(this.nativeGraphics, [rdx].Point.X, [rdx].Point.Y, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .inline IsVisiblePRectF :ptr RectF, :vararg {
        mov this.scratch,TRUE
        GdipIsVisibleRect(this.nativeGraphics,\
            [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .inline IsVisibleIMMFLT :abs, :abs, :abs, :abs, :vararg {

        .new rectf:RectF

        mov rectf.X,_1
        mov rectf.Y,_2
        mov rectf.Width,_3
        mov rectf.Height,_4
        this.IsVisiblePRectF(&rectf)
        }
    .inline IsVisibleIMM32 :abs, :abs, :abs, :abs, :vararg {

        .new rect:Rect

        mov rect.X,_1
        mov rect.Y,_2
        mov rect.Width,_3
        mov rect.Height,_4
        this.IsVisiblePRect(&rect)
        }

    .inline Save :vararg {
        GdipSaveGraphics(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline Restore :vararg {
        GdipRestoreGraphics(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .inline BeginContainer :abs, :vararg {
        ifb <_1>
            GdipBeginContainer2(this.nativeGraphics, addr this.scratch)
        else
            this.typeid(BeginContainer, _1)(_1, _2)
        endif
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .inline BeginContainerPRectF :abs, :abs, :abs, :vararg {
        GdipBeginContainer(this.nativeGraphics, _1, _2, _3, addr this.scratch)
        }
    .inline BeginContainerPRect :abs, :abs, :abs, :vararg {
        GdipBeginContainerI(this.nativeGraphics, _1, _2, _3, addr this.scratch)
        }

    .inline EndContainer :vararg {
        GdipEndContainer(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    ;; Only valid when recording metafiles.

    .inline AddMetafileComment :ptr BYTE, :UINT {
        xchg _1,r8
        GdipComment([this].Graphics.nativeGraphics, edx, r8)
        }

    .inline GetHalftonePalette {
        GdipCreateHalftonePalette()
        retm<rax>
        }

    .inline GetLastStatus {
        mov eax,[this].Graphics.lastResult
        mov [this].Graphics.lastResult,Ok
        }

    .ends
    GpGraphics typedef Graphics

;;----------------------------------------------------------------------------
;; Implementation of GraphicsPath methods that use Graphics
;;----------------------------------------------------------------------------

;; The GetBounds rectangle may not be the tightest bounds.

GraphicsPath::GetBounds2 proto :ptr RectF, :ptr Matrix, :ptr Pen
GraphicsPath::GetBounds1 proto :Rect, :ptr Matrix, :ptr Pen
GraphicsPath::IsVisible2 proto :REAL, :REAL, :ptr Graphics
GraphicsPath::IsVisible1 proto :SINT, :SINT, :ptr Graphics
GraphicsPath::IsOutlineVisible2 proto :REAL, :REAL, :ptr Pen, :ptr Graphics
GraphicsPath::IsOutlineVisible1 proto :SINT, :SINT, :ptr Pen, :ptr Graphics

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
