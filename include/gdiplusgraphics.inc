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

    .operator Graphics :abs, :vararg {
        mov this.nativeGraphics,NULL
        this.typeid(Graphics, _1)(_1, _2)
        mov this.lastResult,eax
        }
    .operator Graphics?pvoid :abs, :vararg {
        GdipCreateFromHDC(_1, addr this.nativeGraphics)
        }
    .operator Graphics?r64 :abs, :vararg {
        GdipCreateFromHDC(_1, addr this.nativeGraphics)
        }
    .operator Graphics?pHWND__ :abs, :abs=<FALSE> {
        if _2
            GdipCreateFromHWNDICM(_1, this)
        else
            GdipCreateFromHDC(_1, this)
        endif
        }
    .operator Graphics?pImage :ptr Image {
        xchg rcx,rdx
        GdipGetImageGraphicsContext([rcx].Image.nativeImage, &[rdx].Graphics.nativeGraphics)
        }
    .operator Graphics?pMetafile :ptr Metafile {
        xchg rcx,rdx
        GdipGetImageGraphicsContext([rcx].Image.nativeImage, &[rdx].Graphics.nativeGraphics)
        }

    .operator Graphics?pGraphics :ptr Graphics, :vararg {
        mov eax,Ok
        mov this.nativeGraphics,rdx
        }

    .operator Release {
        GdipDeleteGraphics([rcx].Graphics.nativeGraphics)
        }

    .operator SetNativeGraphics :ptr GpGraphics {
        mov [this].Graphics.nativeGraphics,_1
        }

    .operator SetStatus :vararg {
        ifnb <_1>
            ifdif <_1>,<eax>
                mov eax,_1
            endif
        endif
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .operator GetNativeGraphics {
        mov rax,[this].Graphics.nativeGraphics
        }

    .operator GetNativePen :ptr Pen {
        mov rax,[this].Pen.nativePen
        }

    .operator Flush :FlushIntention {
        GdipFlush([this].Graphics.nativeGraphics, _1)
        }

    ;;------------------------------------------------------------------------
    ;; GDI Interop methods
    ;;------------------------------------------------------------------------

    ;; Locks the graphics until ReleaseDC is called

    .operator GetHDC :vararg {

        .new hdc:HDC

        mov hdc,NULL
        GdipGetDC(this.nativeGraphics, &hdc)
        GdipSetStatus(this)
        mov rax,hdc
        }

    .operator ReleaseHDC :vararg {
        GdipReleaseDC(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    ;;------------------------------------------------------------------------
    ;; Rendering modes
    ;;------------------------------------------------------------------------

    .operator SetRenderingOrigin :vararg {
        GdipSetRenderingOrigin(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator GetRenderingOrigin :vararg {
        GdipGetRenderingOrigin(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator SetCompositingMode :vararg {
        GdipSetCompositingMode(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator GetCompositingMode :vararg {
        GdipGetCompositingMode(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetCompositingQuality :vararg {
        GdipSetCompositingQuality(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator GetCompositingQuality :vararg {
        GdipGetCompositingQuality(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetTextRenderingHint :vararg {
        GdipSetTextRenderingHint(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator GetTextRenderingHint :vararg {
        GdipGetTextRenderingHint(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetTextContrast :vararg {
        GdipSetTextContrast(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator GetTextContrast :vararg {
        GdipGetTextContrast(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetInterpolationMode :vararg {
        mov this.scratch,InterpolationModeInvalid
        GdipGetInterpolationMode(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetInterpolationMode :vararg {
        GdipSetInterpolationMode(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

if (GDIPVER GE 0x0110)

    .operator SetAbort :vararg {
        GdipGraphicsSetAbort(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

endif

    .operator GetSmoothingMode :vararg {
        mov this.scratch,SmoothingModeInvalid
        GdipGetSmoothingMode(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetSmoothingMode :vararg {
        GdipSetSmoothingMode(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator GetPixelOffsetMode :vararg {
        mov this.scratch,PixelOffsetModeInvalid
        GdipGetPixelOffsetMode(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetPixelOffsetMode :vararg {
        GdipSetPixelOffsetMode(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    ;;------------------------------------------------------------------------
    ;; Manipulate current world transform
    ;;------------------------------------------------------------------------

    .operator SetTransform :ptr Matrix, :vararg {
        GdipSetWorldTransform(this.nativeGraphics, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }
    .operator ResetTransform :vararg {
        GdipResetWorldTransform(this.nativeGraphics)
        GdipSetStatus(this)
        }

    .operator MultiplyTransform :ptr Matrix, :vararg {
        GdipMultiplyWorldTransform(this.nativeGraphics, [rdx].Matrix.nativeMatrix, _2)
        GdipSetStatus(this)
        }

    .operator TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipTranslateWorldTransform(this.nativeGraphics, _1, _2, _3)
        GdipSetStatus(this)
        }

    .operator ScaleTransform :abs, :abs, :vararg {
        ifb<_3>
            GdipScaleWorldTransform(this.nativeGraphics, _1, _2, MatrixOrderPrepend)
        else
            GdipScaleWorldTransform(this.nativeGraphics, _1, _2, _3)
        endif
        GdipSetStatus(this)
        }

    .operator RotateTransform :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipRotateWorldTransform(this.nativeGraphics, _1, _2)
        GdipSetStatus(this)
        }

    .operator GetTransform :ptr Matrix, :vararg {
        GdipGetWorldTransform(this.nativeGraphics, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .operator SetPageUnit :vararg {
        GdipSetPageUnit(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator SetPageScale :vararg {
        GdipSetPageScale(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator GetPageUnit :vararg {
        GdipGetPageUnit(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetPageScale :vararg {
        GdipGetPageScale(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        movss xmm0,this.scratch
        }

    .operator GetDpiX :vararg {
        GdipGetDpiX(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        movss xmm0,this.scratch
        }

    .operator GetDpiY :vararg {
        GdipGetDpiY(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        movss xmm0,this.scratch
        }

    .operator TransformPoints :abs, :abs, :abs, :vararg {
        this.typeid(TransformPoints, _3)(_1, _2, _3, _4)
        GdipSetStatus(this)
        }
    .operator TransformPoints?pPointF :vararg {
        GdipTransformPoints(this.nativeGraphics, _1)
        }
    .operator TransformPoints?pPoint :vararg {
        GdipTransformPointsI(this.nativeGraphics, _1)
        }

    ;;------------------------------------------------------------------------
    ;; GetNearestColor (for <= 8bpp surfaces).  Note: Alpha is ignored.
    ;;------------------------------------------------------------------------

    .operator GetStatus {
        mov eax,[this].Graphics.lastResult
        }

    .operator GetNearestColor :vararg {
        GdipGetNearestColor(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

typeid_flti32 macro name, arg_id
    .operator name :abs, :abs, :vararg {
        this.typeid(name, arg_id)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator &name&?r128   :vararg { this.&name&?flt(_1) }
    .operator &name&?real4  :vararg { this.&name&?flt(_1) }
    .operator &name&?r32    :vararg { this.&name&?i32(_1) }
    .operator &name&?sdword :vararg { this.&name&?i32(_1) }
    exitm<>
    endm

typeid_Point macro name
    .operator &name&?pPointF :abs, :ptr PointF, :ptr PointF, :vararg {
        this.&name&?flt(_1, [r8].PointF.X, [r8].PointF.Y, [r9].PointF.X, [r9].PointF.Y)
        }
    .operator &name&?pPoint :abs, :ptr Point, :ptr Point, :vararg {
        this.&name&?i32(_1, [r8].Point.X, [r8].Point.Y, [r9].Point.X, [r9].Point.Y)
        }
    exitm<>
    endm

typeid_Rect macro name
    .operator &name&?pRectF :abs, :ptr RectF, :vararg {
        this.&name&?flt(_1, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width, [r8].RectF.Height, _3)
        }
    .operator &name&?pRect :abs, :ptr Rect, :vararg {
        this.&name&?i32(_1, [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width, [r8].Rect.Height, _3)
        }
    exitm<>
    endm


    typeid_flti32(DrawLine, _2)

    .operator DrawLine?flt :ptr Pen, :vararg {
        GdipDrawLine(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawLine?i32 :ptr Pen, :vararg {
        GdipDrawLineI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_Point(DrawLine)

    .operator DrawLines :abs, :abs, :vararg {
        this.typeid(DrawLines, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator DrawLines?pPointF :ptr Pen, :vararg {
        GdipDrawLines(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawLines?pPoint :ptr Pen, :vararg {
        GdipDrawLinesI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_flti32(DrawArc, _2)

    .operator DrawArc?flt :ptr Pen, :vararg {
        GdipDrawArc(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawArc?i32 :ptr Pen, :vararg {
        GdipDrawArcI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_Rect(DrawArc)

    typeid_flti32(DrawBezier, _2)

    .operator DrawBezier?flt :ptr Pen, :vararg {
        GdipDrawBezier(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawBezier?i32 :ptr Pen, :vararg {
        GdipDrawBezierI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    .operator DrawBezier?pPointF :abs, :ptr PointF, :ptr PointF, :ptr PointF, :ptr PointF, :vararg {
        mov r10,[rsp+8*4]
        mov r11,[rsp+8*5]
        this.DrawBezier?flt(_1, [r8].PointF.X, [r8].PointF.Y, [r9].PointF.X, [r9].PointF.Y,\
            [r10].PointF.X, [r10].PointF.Y, [r11].PointF.X, [r11].PointF.Y )
        }
    .operator DrawBezier?pPoint :abs, :ptr Point, :ptr Point, :ptr Point, :ptr Point, :vararg {
        mov r10,[rsp+8*4]
        mov r11,[rsp+8*5]
        this.DrawBezier?i32(_1, [r8].Point.X, [r8].Point.Y, [r9].Point.X, [r9].Point.Y,\
            [r10].Point.X, [r10].Point.Y, [r11].Point.X, [r11].Point.Y )
        }


    .operator DrawBeziers :abs, :abs, :vararg {
        this.typeid(DrawBeziers, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator DrawBeziers?pPointF :ptr Pen, :vararg {
        GdipDrawBeziers(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawBeziers?pPoint :ptr Pen, :vararg {
        GdipDrawBeziersI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_flti32(DrawRectangle, _2)

    .operator DrawRectangle?flt :ptr Pen, :vararg {
        GdipDrawRectangle(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawRectangle?i32 :ptr Pen, :vararg {
        GdipDrawRectangleI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    .operator DrawRectangle?pRectF :abs, :ptr RectF, :vararg {
        this.DrawRectangle?flt(_1, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width, [r8].RectF.Height, _3)
        }
    .operator DrawRectangle?pRect :abs, :ptr Rect, :vararg {
        this.DrawRectangle?i32(_1, [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width, [r8].Rect.Height, _3)
        }

    .operator DrawRectangles :abs, :abs, :vararg {
        this.typeid(DrawRectangles, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator DrawRectangles?pRectF :ptr Pen, :vararg {
        GdipDrawRectangles(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawRectangles?pRect :ptr Pen, :vararg {
        GdipDrawRectanglesI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }


    typeid_flti32(DrawEllipse, _2)

    .operator DrawEllipse?flt :ptr Pen, :vararg {
        GdipDrawEllipse(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawEllipse?i32 :ptr Pen, :vararg {
        GdipDrawEllipseI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_Rect(DrawEllipse)

    typeid_flti32(DrawPie, _2)

    .operator DrawPie?flt :ptr Pen, :vararg {
        GdipDrawPie(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawPie?i32 :ptr Pen, :vararg {
        GdipDrawPieI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    typeid_Rect(DrawPie)

    .operator DrawPolygon :abs, :abs, :vararg {
        this.typeid(DrawPolygon, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator DrawPolygon?pPointF :ptr Pen, :vararg {
        GdipDrawPolygon(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }
    .operator DrawPolygon?pPoint :ptr Pen, :vararg {
        GdipDrawPolygonI(this.nativeGraphics, [rdx].Pen.nativePen, _2)
        }

    .operator DrawPath :ptr Pen, :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx]
        .endif
        .if r8
            mov r8,[r8]
        .endif
        GdipDrawPath(this.nativeGraphics, rdx, r8)
        GdipSetStatus(this)
        }

    .operator DrawCurve :abs, :abs, :vararg {
        this.typeid(DrawCurve, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator DrawCurve?pPointF :ptr Pen, :abs, :abs, :abs, :abs, :abs=<0.5>, :vararg {
        ifb <_4>
            GdipDrawCurve(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
        elseifb <_5>
            GdipDrawCurve2(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4)
        else
            GdipDrawCurve3(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4, _5, _6)
        endif
        }
    .operator DrawCurve?pPoint :ptr Pen, :abs, :abs, :abs, :abs, :abs=<0.5>, :vararg {
        ifb <_4>
            GdipDrawCurveI(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
        elseifb <_5>
            GdipDrawCurve2I(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4)
        else
            GdipDrawCurve3I(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4, _5, _6)
        endif
        }


    .operator DrawClosedCurve :abs, :abs, :vararg {
        this.typeid(DrawClosedCurve, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator DrawClosedCurve?pPointF :ptr Pen, :abs, :abs, :abs, :vararg {
        ifb <_4>
            GdipDrawClosedCurve(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
        else
            GdipDrawClosedCurve2(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4)
        endif
        }
    .operator DrawClosedCurve?pPoint :ptr Pen, :abs, :abs, :abs, :vararg {
        ifb <_4>
            GdipDrawClosedCurveI(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
        else
            GdipDrawClosedCurve2I(this.nativeGraphics, [rdx].Pen.nativePen, _2, _3, _4)
        endif
        }

    .operator Clear :vararg {
        GdipGraphicsClear(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    typeid_flti32(FillRectangle, _2)

    .operator FillRectangle?flt :ptr Brush, :vararg {
        GdipFillRectangle(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }
    .operator FillRectangle?i32 :ptr Brush, :vararg {
        GdipFillRectangleI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }

    typeid_Rect(FillRectangle)

    .operator FillRectangles :abs, :abs, :vararg {
        this.typeid(FillRectangles, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator FillRectangles?pRectF :ptr Brush, :vararg {
        GdipFillRectangles(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }
    .operator FillRectangles?pRect :ptr Brush, :vararg {
        GdipFillRectanglesI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }


    .operator FillPolygon :abs, :abs, :vararg {
        this.typeid(FillPolygon, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator FillPolygon?pPointF :ptr Brush, :abs, :abs, :abs=<FillModeAlternate>, :vararg {
        GdipFillPolygon(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3, _4)
        }
    .operator FillPolygon?pPoint :ptr Brush, :abs, :abs, :abs=<FillModeAlternate>, :vararg {
        GdipFillPolygonI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3, _4)
        }


    typeid_flti32(FillEllipse, _2)

    .operator FillEllipse?flt :ptr Brush, :vararg {
        GdipFillEllipse(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }
    .operator FillEllipse?i32 :ptr Brush, :vararg {
        GdipFillEllipseI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }

    typeid_Rect(FillEllipse)


    typeid_flti32(FillPie, _2)

    .operator FillPie?flt :ptr Brush, :vararg {
        GdipFillPie(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }
    .operator FillPie?i32 :ptr Brush, :vararg {
        GdipFillPieI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2)
        }

    typeid_Rect(FillPie)

    .operator FillPath :ptr Brush, :ptr GraphicsPath, :vararg {
        GdipFillPath(this.nativeGraphics, [rdx].Brush.nativeBrush, [r8].GraphicsPath.nativePath)
        GdipSetStatus(this)
        }

    .operator FillClosedCurve :abs, :abs, :vararg {
        this.typeid(FillClosedCurve, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator FillClosedCurve?pPointF :ptr Brush, :abs, :abs, :abs, :abs=<0.5>, :vararg {
        ifb <_4>
            GdipFillClosedCurve(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
        else
            GdipFillClosedCurve2(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3, _5, _4)
        endif
        }
    .operator FillClosedCurve?pPoint :ptr Brush, :abs, :abs, :abs, :abs=<0.5>, :vararg {
        ifb <_4>
            GdipFillClosedCurveI(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
        else
            GdipFillClosedCurve2I(this.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3, _5, _4)
        endif
        }


    .operator FillRegion :ptr Brush, :ptr Region, :vararg {
        GdipFillRegion(this.nativeGraphics, [rdx].Brush.nativeBrush, [r8].Region.nativeRegion)
        GdipSetStatus(this)
        }

    ; DrawString(WCHAR*, INT, Font*, RectF*, StringFormat *, Brush*)

    .operator DrawString :abs, :abs, :ptr Font, :ptr RectF, :ptr StringFormat, :ptr Brush, :vararg {

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

    .operator MeasureString :abs, :abs, :abs, :abs, :vararg {
        this.typeid(MeasureString, _4)(_1, _2, _3, _4, _5)
        }
    .operator MeasureString?pRectF :abs, :abs, :abs, :abs, :abs, :vararg {
        this.typeid(MeasureString?pRectF, _5)(_1, _2, _3, _4, _5, _6)
        }

    ; MeasureString(WCHAR*, INT, Font*, RectF*, StringFormat*, RectF*, INT* = 0, INT* = 0)

    .operator MeasureString?pRectF?pStringFormat :abs, :abs, :ptr Font, :ptr RectF, :ptr StringFormat, :abs, :abs=<0>, :abs=<0>, :vararg {
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

    .operator MeasureString?pSizeF :abs, :abs, :ptr Font, :ptr SizeF, :ptr StringFormat, :ptr SizeF, :abs=<0>, :abs=<0>, :vararg {

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

    .operator MeasureString?pPointF :abs, :abs, :abs, :abs, :abs, :vararg {
        this.typeid(MeasureString?pPointF, _5)(_1, _2, _3, _4, _5, _6)
        }

    .operator MeasureString?pPointF?pStringFormat :abs, :abs, :ptr Font, :ptr PointF, :ptr StringFormat, :abs, :vararg {

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

    .operator MeasureString?pRectF?pRectF :abs, :abs, :ptr Font, :abs, :abs, :vararg {
        .if r9
            mov r9,[r9].Font.nativeFont
        .endif
        GdipMeasureString(this.nativeGraphics, _1, _2, r9, _4, NULL, _5, NULL, NULL)
        GdipSetStatus(this)
        }


    ; MeasureString(WCHAR*, INT, Font*, PointF*, RectF*)

    .operator MeasureString?pPointF?pRectF :abs, :abs, :ptr Font, :ptr PointF, :ptr RectF, :vararg {

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

    .operator MeasureCharacterRanges :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :SINT, :ptr Region {

        .repeat

            .if qword ptr _7 == 0 || sdword ptr _6 <= 0

                mov eax,InvalidParameter
                .break
            .endif

            .new status:Status
            .new nativeRegions:ptr Region ;= new GpRegion* [regionCount];

            .if (!nativeRegions)

                mov eax,OutOfMemory
                .break
            .endif

            .for (ecx = 0: ecx < _6: ecx++)

               ; mov nativeRegions[rcx],regions[rcx].nativeRegion
            .endf

            ;font ? font->nativeFont : NULL,
            ;stringFormat ? stringFormat->nativeFormat : NULL,

            mov status,GdipMeasureCharacterRanges([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7)
            GdipFree(nativeRegions)
            mov eax,status
        .until 1
        }

    .operator DrawDriverString :abs, :abs, :ptr Font, :ptr Brush, :abs, :abs, :ptr Matrix, :vararg {
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

    .operator MeasureDriverString :abs, :abs, :ptr Font, :abs, :abs, :ptr Matrix, :vararg {
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

    .operator DrawCachedBitmap :ptr CachedBitmap, :vararg {
        GdipDrawCachedBitmap(this.nativeGraphics, [rdx].CachedBitmap.nativeCachedBitmap, _2)
        GdipSetStatus(this)
        }

    .operator DrawImage :ptr Image, :abs, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        this.typeid(DrawImage, _2)(_1, _2, _3)
        this.SetStatus()
        }

    ; DrawImage(Image*, PointF*)
    ; DrawImage(Image*, PointF*, INT)
    ; DrawImage(Image*, PointF*, INT, REAL, REAL, REAL, REAL, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)

    .operator DrawImage?pPointF :abs, :ptr PointF, :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
        ifb <_3>
            this.DrawImage?flt(rdx, [r8].PointF.X, [r8].PointF.Y)
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

    .operator DrawImage?pPoint :abs, :ptr Point, :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
        ifb <_3>
            this.DrawImage?i32(rdx, [r8].Point.X, [r8].Point.Y)
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

    .operator DrawImage?pRectF :abs, :ptr RectF, :abs, :vararg {
        ifb <_3>
            this.DrawImage?flt(rdx, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width, [r8].RectF.Height)
        else
            this.typeid(DrawImage?pRectF, _3)(rdx, r8, _3, _4)
        endif
        }

    ; DrawImage(Image*, RectF*, REAL, REAL, REAL, REAL, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)

    .operator DrawImage?pRectF?flt :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
        mov r10,_8
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRect(this.nativeGraphics, rdx, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width,\
            [r8].RectF.Height, _3, _4, _5, _6, _7, r10, _9, _10)
        }

if (GDIPVER GE 0x0110)

    ; DrawImage(Image*, RectF*, RectF*, Unit, ImageAttributes* = NULL)

    .operator DrawImage?pRectF?pRectF :abs, :ptr RectF, :ptr RectF, :abs, :abs=<0>, :vararg {
        mov r10,_5
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRect(this.nativeGraphics, rdx, [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width,\
            [r8].RectF.Height, [r9].RectF.X, [r9].RectF.Y, [r9].RectF.Width, [r9].RectF.Height,\
            _4, r10, NULL, NULL)
        }

    ; DrawImage(Image*, RectF*, Matrix*, Effect*, ImageAttributes*, Unit)

    .operator DrawImage?pRectF?pMatrix :abs, :abs, :ptr Matrix, :ptr Effect, :ptr ImageAttributes, :abs, :vararg {
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

    .operator DrawImage?pRect :abs, :ptr Rect, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
        ifb <_3>
            this.DrawImage?i32(rdx, [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width, [r8].Rect.Height)
        else
            mov r10,_8
            .if r10
                mov r10,[r10].ImageAttributes.nativeImageAttr
            .endif
            GdipDrawImageRectRectI(this.nativeGraphics, rdx, [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width,\
                [r8].Rect.Height, _3, _4, _5, _6, _7, r10, _9, _10)
        endif
        }

    ; DrawImage(Image*, REAL, REAL)
    ; DrawImage(Image*, REAL, REAL, REAL, REAL)
    ; DrawImage(Image*, REAL, REAL, REAL, REAL, REAL, REAL, Unit)

    .operator DrawImage?flt :abs, :abs, :abs, :abs, :abs, :abs, :vararg {
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

    .operator DrawImage?i32 :abs, :abs, :abs, :abs, :abs, :abs, :vararg {
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

    .operator EnumerateMetafile :ptr Image, :abs, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        this.typeid(EnumerateMetafile, _2)(_1, _2, _3)
        GdipSetStatus(this)
        }
    .operator EnumerateMetafile?pPointF :abs, :ptr PointF, :abs, :vararg {
        this.typeid(EnumerateMetafile?pPointF, _3)(_1, _2, _3, _4)
        }
    .operator EnumerateMetafile?pPoint :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafile?pPoint, _3)(_1, _2, _3, _4)
        }
    .operator EnumerateMetafile?pRectF :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafile?pRectF, _3)(_1, _2, _3, _4)
        }
    .operator EnumerateMetafile?pRect :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafile?pRect, _3)(_1, _2, _3, _4)
        }
    .operator EnumerateMetafile?pPointF?i32 :abs, :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafile?pPointF?i32, _4)(_1, _2, _3, _4, _5)
        }
    .operator EnumerateMetafile?pPoint?i32 :abs, :abs, :abs, :abs, :vararg {
        this.typeid(EnumerateMetafile?pPoint?i32, _4)(_1, _2, _3, _4, _5)
        }

    ; EnumerateMetafile(Metafile*, PointF*, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pPointF?pnear :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPoint(this.nativeGraphics, rdx, _2, _3, _4, r11)
        }

    ; EnumerateMetafile(Metafile*, PointF*, INT, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pPointF?i32?pnear :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_6
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPoints(this.nativeGraphics, _1, _2, _3, _4, _5, r11)
        }

    ; EnumerateMetafile(Metafile*, PointF*, INT, RectF*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pPointF?i32?pRectF :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        }

    ; EnumerateMetafile(Metafile*, PointF*, RectF*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pPointF?pRectF :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPoint(this.nativeGraphics, _1, _2, _3, _4, _5, _6, r11)
        }

    ; EnumerateMetafile(Metafile*, Point*, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pPoint?pnear :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPointI(this.nativeGraphics, rdx, _2, _3, _4, r11)
        }

    ; EnumerateMetafile(Metafile*, Point*, INT, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pPoint?i32?pnear :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_6
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPointsI(this.nativeGraphics, _1, _2, _3, _4, _5, r11)
        }

    ; EnumerateMetafile(Metafile*, Point*, INT, Rect*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pPoint?i32?pRect :abs, :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        }

    ; EnumerateMetafile(Metafile*, Point*, Rect*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pPoint?pRect :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPointI(this.nativeGraphics, _1, _2, _3, _4, _5, _6, r11)
        }

    ; EnumerateMetafile(Metafile*, RectF*, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pRectF?pnear :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestRect(this.nativeGraphics, rdx, _2, _3, _4, r11)
        }

    ; EnumerateMetafile(Metafile*, RectF*, RectF*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pRectF?pRectF :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestRect(this.nativeGraphics, rdx, _2, _3, _4, _5, _6, r11)
        }

    ; EnumerateMetafile(Metafile*, Rect*, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pRect?pnear :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestRectI(this.nativeGraphics, _1, _2, _3, _4, r11)
        }

    ; EnumerateMetafile(Metafile*, Rect*, Rect*, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .operator EnumerateMetafile?pRect?pRect :abs, :abs, :abs, :abs, :abs, :abs=<0>, :abs=<0>, :vararg {
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestRectI(this.nativeGraphics, rdx, _2, _3, _4, _5, _6, r11)
        }


    .operator SetClip :abs, :vararg {
        this.typeid(SetClip , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator SetClip?pGraphics :ptr Graphics, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipGraphics(this.nativeGraphics, [rdx].Graphics.nativeGraphics, _2)
        }
    .operator SetClip?pRectF :ptr RectF, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipRect(this.nativeGraphics,\
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
        }
    .operator SetClip?pRect :ptr Rect, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipRectI(this.nativeGraphics,\
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
        }
    .operator SetClip?pGraphicsPath :ptr GraphicsPath, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipPath(this.nativeGraphics, [rdx].GraphicsPath.nativePath, _2)
        }
    .operator SetClip?pRegion :ptr Region, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipRegion(this.nativeGraphics, [rdx].Region.nativeRegion, _2)
        }

    ;; This is different than the other SetClip methods because it assumes
    ;; that the HRGN is already in device units, so it doesn't transform
    ;; the coordinates in the HRGN.

    .operator SetClip?pvoid :abs, :abs=<CombineModeReplace>, :vararg {
        GdipSetClipHrgn(this.nativeGraphics, _1, _2)
        }

    .operator IntersectClip :abs, :vararg {
        this.typeid(IntersectClip , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator IntersectClip?pRectF :ptr RectF, :vararg {
        GdipSetClipRect(this.nativeGraphics,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width,\
                [rdx].RectF.Height, CombineModeIntersect)
        }
    .operator IntersectClip?pRect :ptr Rect, :vararg {
        GdipSetClipRectI(this.nativeGraphics,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, CombineModeIntersect)
        }
    .operator IntersectClip?pRegion :ptr Region, :vararg {
        GdipSetClipRegion(this.nativeGraphics,\
                [rdx].Region.nativeRegion, CombineModeIntersect)
        }

    .operator ExcludeClip :abs, :vararg {
        this.typeid(ExcludeClip , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator ExcludeClip?pRectF :ptr RectF, :vararg {
        GdipSetClipRect(this.nativeGraphics,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, CombineModeExclude)
        }
    .operator ExcludeClip?pRect :ptr Rect, :vararg {
        GdipSetClipRectI(this.nativeGraphics,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, CombineModeExclude)
        }
    .operator ExcludeClip?pRegion :ptr Region, :vararg {
        GdipSetClipRegion(this.nativeGraphics, [rdx].Region.nativeRegion, CombineModeExclude)
        }

    .operator ResetClip :vararg {
        GdipResetClip(this.nativeGraphics)
        GdipSetStatus(this)
        }

    .operator TranslateClip :abs, :vararg {
        this.typeid(TranslateClip , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator TranslateClip?flt :vararg {
        GdipTranslateClip(this.nativeGraphics, _1)
        }
    .operator TranslateClip?i32 :vararg {
        GdipTranslateClipI(this.nativeGraphics, _1)
        }

    .operator GetClip :ptr, :vararg {
        GdipGetClip(this.nativeGraphics, [rdx].Region.nativeRegion)
        GdipSetStatus(this)
        }

    .operator GetClipBounds :abs, :vararg {
        this.typeid(GetClipBounds , _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator GetClipBounds?pRectF :vararg  {
        GdipGetClipBounds(this.nativeGraphics, _1)
        }
    .operator GetClipBounds?pRect :vararg {
        GdipGetClipBoundsI(this.nativeGraphics, _1)
        }

    .operator IsClipEmpty :vararg {
        mov this.scratch,FALSE
        GdipIsClipEmpty(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetVisibleClipBounds :abs, :vararg {
        this.typeid(GetVisibleClipBounds, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator GetVisibleClipBounds?pRectF :abs, :vararg {
        GdipGetVisibleClipBounds(this.nativeGraphics, _1)
        }
    .operator GetVisibleClipBounds?pRect :abs, :vararg {
        GdipGetVisibleClipBoundsI(this.nativeGraphics, _1)
        }

    .operator IsVisibleClipEmpty :vararg {
        mov this.scratch,FALSE
        GdipIsVisibleClipEmpty(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator IsVisible :abs, :vararg {
        this.typeid(IsVisible, _1)(_1, _2)
        }
    .operator IsVisible?pPoint :ptr Point, :vararg {
        mov this.scratch,FALSE
        GdipIsVisiblePointI(this.nativeGraphics, [rdx].Point.X, [rdx].Point.Y, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .operator IsVisible?pRect :ptr Rect, :vararg {
        mov this.scratch,TRUE
        GdipIsVisibleRectI(this.nativeGraphics,\
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .operator IsVisible?pPointF :ptr PointF, :vararg {
        mov this.scratch,FALSE
        GdipIsVisiblePoint(this.nativeGraphics, [rdx].Point.X, [rdx].Point.Y, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .operator IsVisible?pRectF :ptr RectF, :vararg {
        mov this.scratch,TRUE
        GdipIsVisibleRect(this.nativeGraphics,\
            [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .operator IsVisible?flt :abs, :abs, :abs, :abs, :vararg {

        .new rectf:RectF

        mov rectf.X,_1
        mov rectf.Y,_2
        mov rectf.Width,_3
        mov rectf.Height,_4
        this.IsVisible?pRectF(&rectf)
        }
    .operator IsVisible?i32 :abs, :abs, :abs, :abs, :vararg {

        .new rect:Rect

        mov rect.X,_1
        mov rect.Y,_2
        mov rect.Width,_3
        mov rect.Height,_4
        this.IsVisible?pRect(&rect)
        }

    .operator Save :vararg {
        GdipSaveGraphics(this.nativeGraphics, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator Restore :vararg {
        GdipRestoreGraphics(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    .operator BeginContainer :abs, :vararg {
        ifb <_1>
            GdipBeginContainer2(this.nativeGraphics, addr this.scratch)
        else
            this.typeid(BeginContainer, _1)(_1, _2)
        endif
        GdipSetStatus(this)
        mov eax,this.scratch
        }
    .operator BeginContainer?pRectF :abs, :abs, :abs, :vararg {
        GdipBeginContainer(this.nativeGraphics, _1, _2, _3, addr this.scratch)
        }
    .operator BeginContainer?pRect :abs, :abs, :abs, :vararg {
        GdipBeginContainerI(this.nativeGraphics, _1, _2, _3, addr this.scratch)
        }

    .operator EndContainer :vararg {
        GdipEndContainer(this.nativeGraphics, _1)
        GdipSetStatus(this)
        }

    ;; Only valid when recording metafiles.

    .operator AddMetafileComment :ptr BYTE, :UINT {
        xchg _1,r8
        GdipComment([this].Graphics.nativeGraphics, edx, r8)
        }

    .operator GetHalftonePalette {
        GdipCreateHalftonePalette()
        }

    .operator GetLastStatus {
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
