ifndef _GDIPLUSGRAPHICS_H
_GDIPLUSGRAPHICS_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template Graphics

    nativeGraphics  ptr_t ?
    lastResult      Status ?

    Graphics proc :ptr, :vararg
    Graphics_Graphics macro this, _1, _2
        mov this.nativeGraphics,NULL
        xchg rcx,rdx
        ifnb <_2>
            if typeof(_2) eq 8
                GdipCreateFromHDC2(rcx, _2, rdx)
            elseif _2
                GdipCreateFromHWNDICM(rcx, rdx)
            else
                GdipCreateFromHWND(rcx, rdx)
            endif
        else
            GdipCreateFromHDC(rcx, rdx)
        endif
        mov this.lastResult,eax
        lea rax,this
        retm<rax>
        endm

    .operator Release {
        exitm<GdipDeleteGraphics([rcx].Graphics.nativeGraphics)>
        }

    .operator FromImage :ptr Image {
        mov graphics,this
        mov [this].Graphics.nativeGraphics,NULL
        xor eax,eax
        .if _1
            xchg this,_1
            GdipGetImageGraphicsContext([this].Image.nativeImage, &[_1].Graphics.nativeGraphics)
            graphics.SetStatus(eax)
        .endif
        retm<eax>
        }

    .operator FromGraphics :ptr Graphics {
        mov     eax,Ok
        mov     [this].Graphics.nativeGraphics,_1
        mov     [this].Graphics.lastResult,eax
        retm    <eax>
        }

    .operator SetNativeGraphics :ptr GpGraphics {
        mov     [this].Graphics.nativeGraphics,_1
        exitm   <>
        }

    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].Graphics.lastResult,eax
        .endif
        retm <eax>
        }

    .operator GetNativeGraphics {
        mov     rax,[this].Graphics.nativeGraphics
        retm    <rax>
        }

    .operator GetNativePen :ptr Pen {
        mov     rax,[this].Pen.nativePen
        retm    <rax>
        }

    .operator Flush :FlushIntention {
        GdipFlush([this].Graphics.nativeGraphics, _1)
        exitm<>
        }

    ;;------------------------------------------------------------------------
    ;; GDI Interop methods
    ;;------------------------------------------------------------------------

    ;; Locks the graphics until ReleaseDC is called

    .operator GetHDC :vararg {

        .new hdc:HDC

        mov hdc,NULL
        .ifd GdipGetDC([rcx].Graphics.nativeGraphics, &hdc)
            mov this.lastResult,eax
        .endif
        mov rax,hdc
        retm<rax>
        }

    .operator ReleaseHDC :vararg {
        .ifd GdipReleaseDC([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    ;;------------------------------------------------------------------------
    ;; Rendering modes
    ;;------------------------------------------------------------------------

    .operator SetRenderingOrigin :vararg {
        .ifd GdipSetRenderingOrigin([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetRenderingOrigin :vararg {
        .ifd GdipGetRenderingOrigin([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetCompositingMode :vararg {
        .ifd GdipSetCompositingMode([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetCompositingMode :vararg {

        .new mode:CompositingMode

        .ifd GdipGetCompositingMode([rcx].Graphics.nativeGraphics, &mode)
            mov this.lastResult,eax
        .endif
        mov eax,mode
        retm<eax>
        }

    .operator SetCompositingQuality :vararg {
        .ifd GdipSetCompositingQuality([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetCompositingQuality :vararg {

        .new quality:CompositingQuality

        .ifd GdipGetCompositingQuality([rcx].Graphics.nativeGraphics, &quality)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,quality>
        }

    .operator SetTextRenderingHint :vararg {
        .ifd GdipSetTextRenderingHint([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetTextRenderingHint :vararg {

        .new hint:TextRenderingHint

        .ifd GdipGetTextRenderingHint([rcx].Graphics.nativeGraphics, &hint)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,hint>
        }

    .operator SetTextContrast :vararg {
        .ifd GdipSetTextContrast([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetTextContrast :vararg {

        .new contrast:UINT

        .ifd GdipGetTextContrast([rcx].Graphics.nativeGraphics, &contrast)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,contrast>
        }

    .operator GetInterpolationMode :vararg {

        .new mode:InterpolationMode

        mov mode,InterpolationModeInvalid
        .ifd GdipGetInterpolationMode([rcx].Graphics.nativeGraphics, &mode)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,mode>
        }

    .operator SetInterpolationMode :vararg {
        .ifd GdipSetInterpolationMode([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

if (GDIPVER GE 0x0110)

    .operator SetAbort :vararg {
        .ifd GdipGraphicsSetAbort([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

endif

    .operator GetSmoothingMode :vararg {

        .new smoothingMode:SmoothingMode

        mov smoothingMode,SmoothingModeInvalid
        .ifd GdipGetSmoothingMode([rcx].Graphics.nativeGraphics, &smoothingMode)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,smoothingMode>
        }

    .operator SetSmoothingMode :vararg {
        .ifd GdipSetSmoothingMode([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetPixelOffsetMode :vararg {

        .new pixelOffsetMode:PixelOffsetMode

        mov pixelOffsetMode,PixelOffsetModeInvalid
        .ifd GdipGetPixelOffsetMode([rcx].Graphics.nativeGraphics, &pixelOffsetMode)
            mov this.lastResult,eax
        .endif
        mov eax,pixelOffsetMode
        exitm<>
        }

    .operator SetPixelOffsetMode :vararg {
        .ifd GdipSetPixelOffsetMode([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    ;;------------------------------------------------------------------------
    ;; Manipulate current world transform
    ;;------------------------------------------------------------------------

    .operator SetTransform :ptr Matrix, :vararg {
        .ifd GdipSetWorldTransform([rcx].Graphics.nativeGraphics, [rdx].Matrix.nativeMatrix)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator ResetTransform :vararg {
        .ifd GdipResetWorldTransform([rcx].Graphics.nativeGraphics)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator MultiplyTransform :ptr Matrix, :vararg {
        .ifd GdipMultiplyWorldTransform([rcx].Graphics.nativeGraphics, [rcx].Matrix.nativeMatrix, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator TranslateTransform :REAL, :REAL, :vararg {
        .ifd GdipTranslateWorldTransform([rcx].Graphics.nativeGraphics, _1, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    ScaleTransform proc :REAL, :REAL, :vararg
    Graphics_ScaleTransform macro this, _1, _2, _3:=<MatrixOrderPrepend>
        .ifd GdipScaleWorldTransform([rcx].Graphics.nativeGraphics, _1, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        endm

    .operator RotateTransform :REAL, :vararg {
        .ifd GdipRotateWorldTransform([rcx].Graphics.nativeGraphics, _1, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetTransform :ptr Matrix, :vararg {
        .ifd GdipGetWorldTransform([rcx].Graphics.nativeGraphics, [rdx].Matrix.nativeMatrix)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetPageUnit :vararg {
        .ifd GdipSetPageUnit([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetPageScale :vararg {
        .ifd GdipSetPageScale([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetPageUnit :vararg {

        .new unit:Unit

        .ifd GdipGetPageUnit([rcx].Graphics.nativeGraphics, &unit)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,unit>
        }

    .operator GetPageScale :vararg {

        .new scale:REAL

        .ifd GdipGetPageScale([rcx].Graphics.nativeGraphics, &scale)
            mov this.lastResult,eax
        .endif
        movss xmm0,scale
        retm <xmm0>
        }

    .operator GetDpiX :vararg {

        .new dpi:REAL

        .ifd GdipGetDpiX([rcx].Graphics.nativeGraphics, &dpi)
            mov this.lastResult,eax
        .endif
        movss xmm0,dpi
        exitm<>
        }

    .operator GetDpiY :vararg {

        .new dpi:REAL

        .ifd GdipGetDpiY([rcx].Graphics.nativeGraphics, &dpi)
            mov this.lastResult,eax
        .endif
        movss xmm0,dpi
        exitm<>
        }

    .operator TransformPoints :vararg {
        .ifd GdipTransformPoints([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator TransformPointsI :vararg {
        .ifd GdipTransformPointsI([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    ;;------------------------------------------------------------------------
    ;; GetNearestColor (for <= 8bpp surfaces).  Note: Alpha is ignored.
    ;;------------------------------------------------------------------------

    .operator GetStatus {
        mov eax,[this].Graphics.lastResult
        retm <eax>
        }

    .operator GetNearestColor :vararg {

        .new argb:ARGB

        .ifd GdipGetNearestColor([rcx].Graphics.nativeGraphics, &argb)
            mov this.lastResult,eax
        .endif
        mov eax,argb
        exitm<>
        }

    .operator DrawLine :ptr Pen, :vararg {
        .ifd GdipDrawLine([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawLines :ptr Pen, :ptr PointF, :vararg {
        .ifd GdipDrawLines([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawLineI :ptr Pen, :vararg {
        .ifd GdipDrawLineI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawLinesI :ptr Pen, :ptr Point, :vararg {
        .ifd GdipDrawLinesI([rcx].Graphics.nativeGraphics, [rcx].Pen.nativePen, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawArc :ptr Pen, :vararg {
        .ifd GdipDrawArc([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawArcI :ptr Pen, :vararg {
        .ifd GdipDrawArcI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawBezier :ptr Pen, :vararg {
        .ifd GdipDrawBezier([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawBeziers :ptr Pen, :ptr PointF, :vararg {
        .ifd GdipDrawBeziers([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawBezierI :ptr Pen, :vararg {
        .ifd GdipDrawBezierI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawBeziersI :ptr Pen, :ptr Point, :vararg {
        .ifd GdipDrawBeziersI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawRectangle :ptr Pen, :vararg {
        .ifd GdipDrawRectangle([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawRectangles :ptr Pen, :ptr RectF, :vararg {
        .ifd GdipDrawRectangles([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawRectangleI :ptr Pen, :vararg {
        .ifd GdipDrawRectangleI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawRectanglesI :ptr Pen, :ptr Rect, :vararg {
        .ifd GdipDrawRectanglesI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawEllipse :ptr Pen, :vararg {
        .ifd GdipDrawEllipse([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawEllipseI :ptr Pen, :vararg {
        .ifd GdipDrawEllipseI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawPie :ptr Pen, :vararg {
        .ifd GdipDrawPie([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawPieI :ptr Pen, :vararg {
        .ifd GdipDrawPieI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawPolygon :ptr Pen, :vararg {
        .ifd GdipDrawPolygon([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawPolygonI :ptr Pen, :vararg {
        .ifd GdipDrawPolygonI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawPath :ptr Pen, :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx]
        .endif
        .if r8
            mov r8,[r8]
        .endif
        .ifd GdipDrawPath([rcx].Graphics.nativeGraphics, rdx, r8)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawCurve :ptr Pen, :vararg {
        .ifd GdipDrawCurve([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawCurve2 :ptr Pen, :vararg {
        .ifd GdipDrawCurve2([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawCurve3 :ptr Pen, :vararg {
        .ifd GdipDrawCurve3([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawCurveI :ptr Pen, :vararg {
        .ifd GdipDrawCurveI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawCurve2I :ptr Pen, :vararg {
        .ifd GdipDrawCurve2I([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawCurve3I :ptr Pen, :vararg {
        .ifd GdipDrawCurve3I([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawClosedCurve :ptr Pen, :vararg {
        .ifd GdipDrawClosedCurve([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawClosedCurve2 :ptr Pen, :vararg {
        .ifd GdipDrawClosedCurve2([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawClosedCurveI :ptr Pen, :vararg {
        .ifd GdipDrawClosedCurveI([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawClosedCurve2I :ptr Pen, :vararg {
        .ifd GdipDrawClosedCurve2I([rcx].Graphics.nativeGraphics, [rdx].Pen.nativePen, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator Clear :vararg {
        .ifd GdipGraphicsClear([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator FillRectangle :ptr Brush, :vararg {
        .ifd GdipFillRectangle([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator FillRectangles :ptr Brush, :ptr RectF, :vararg {
        .ifd GdipFillRectangles([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator FillRectangleI :ptr Brush, :vararg {
        .ifd GdipFillRectangleI([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator FillRectanglesI :ptr Brush, :ptr Rect, :vararg {
        .ifd GdipFillRectanglesI([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator FillPolygon :ptr Brush, :ptr PointF, :vararg {
        .ifd GdipFillPolygon([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator FillPolygonI :ptr Brush, :ptr Point, :vararg {
        .ifd GdipFillPolygonI([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator FillEllipse :ptr Brush, :vararg {
        .ifd GdipFillEllipse([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator FillEllipseI :ptr Brush, :vararg {
        .ifd GdipFillEllipseI([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator FillPie :ptr Brush, :vararg {
        .ifd GdipFillPie([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator FillPieI :ptr Brush, :vararg {
        .ifd GdipFillPieI([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator FillPath :ptr Brush, :ptr GraphicsPath, :vararg {
        .ifd GdipFillPath([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, [r8].GraphicsPath.nativePath)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator FillClosedCurve :ptr Brush, :ptr PointF, :vararg {
        .ifd GdipFillClosedCurve([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator FillClosedCurve2 :ptr Brush, :ptr PointF, :vararg {
        .ifd GdipFillClosedCurve2([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator FillClosedCurveI :ptr Brush, :ptr Point, :vararg {
        .ifd GdipFillClosedCurveI([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator FillClosedCurve2I :ptr Brush, :ptr Point, :vararg {
        .ifd GdipFillClosedCurve2I([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, _2, _3)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator FillRegion :ptr Brush, :ptr Region, :vararg {
        .ifd GdipFillRegion([rcx].Graphics.nativeGraphics, [rdx].Brush.nativeBrush, [r8].Region.nativeRegion)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawString :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :ptr Brush {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        mov r10,_5
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        mov r11,_6
        .if r11
            mov r11,[r11].Brush.nativeBrush
        .endif
        .ifd GdipDrawString([this].Graphics.nativeGraphics, _1, _2, _3, _4, r10, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator MeasureString :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :ptr RectF, :SINT, :ptr SINT {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        mov r10,_5
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        .ifd GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, _4, r10, _6, _7, _8)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }
    .operator MeasureString2 :ptr WCHAR, :SINT, :ptr Font, :ptr SizeF, :ptr StringFormat, :ptr SizeF, :SINT, :SINT {

        .new layoutRect:RectF
        .new boundingBox:RectF
        .new size:ptr RectF
        .new @graphics:ptr Graphics

        mov @graphics,rcx
        mov r10,_4
        mov size,r10
        mov layoutRect.X,0.0
        mov layoutRect.Y,0.0
        mov layoutRect.Width,[r10].SizeF.Width
        mov layoutRect.Height,[r10].SizeF.Height
        mov graphics,this
        mov r10,_6
        .if r10 == NULL
            graphics.SetStatus(InvalidParameter)
        .else
            .if _3
                mov _3,[_3].Font.nativeFont
            .endif
            mov r10,_5
            .if r10
                mov r10,[r10].StringFormat.nativeFormat
            .endif
            GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, &layoutRect, r10, &boundingBox, _7, _8)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
            .if eax == Ok
                mov r10,size
                mov [r10].RectF.Width,  boundingBox.Width
                mov [r10].RectF.Height, boundingBox.Height
            .endif
        .endif
        retm <eax>
        }
    .operator MeasureString3 :ptr WCHAR, :SINT, :ptr Font, :ptr PointF, :ptr StringFormat, :ptr RectF {

       .new rect:RectF
       .new @graphics:ptr Graphics
        mov @graphics,rcx

        mov r10,_4
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.Width,0.0
        mov rect.Height,0.0
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        mov r10,_5
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        .ifd GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, &rect, r10, _6, NULL, NULL)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }
    .operator MeasureString4 :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr RectF {
       .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        .ifd GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, _4, NULL, _5, NULL, NULL)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }
    .operator MeasureString5 :ptr WCHAR, :SINT, :ptr Font, :ptr PointF, :ptr RectF {

       .new rect:RectF
       .new @graphics:ptr Graphics
        mov @graphics,rcx

        mov r10,_4
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.Width,0.0
        mov rect.Height,0.0
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        .ifd GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, &rect, NULL, _4, NULL, NULL)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator MeasureCharacterRanges :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :SINT, :ptr Region {

        .repeat

            .if (!_7 || _6 <= 0)

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
        retm <>eax
    }

    .operator DrawDriverString :ptr UINT16, :SINT, :ptr Font, :ptr Brush, :ptr PointF, :SINT, :ptr Matrix {
       .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        mov r10,_4
        .if r10
            mov r10,[r10].Brush.nativeBrush
        .endif
        mov r11,_7
        .if r11
            mov r11,[r11].Matrix.nativeMatrix
        .endif
        .ifd GdipDrawDriverString([this].Graphics.nativeGraphics, _1, _2, _3, r10, _5, _6, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator MeasureDriverString :ptr UINT16, :SINT, :ptr Font, :ptr PointF, :SINT, :ptr Matrix, :ptr RectF {
       .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        mov r10,_6
        .if r10
            mov r10,[r10].Matrix.nativeMatrix
        .endif
        .ifd GdipMeasureDriverString([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, r10, _7)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    ;; Draw a cached bitmap on this graphics destination offset by
    ;; x, y. Note this will fail with WrongState if the CachedBitmap
    ;; native format differs from this Graphics.

    .operator DrawCachedBitmap :ptr CachedBitmap, :vararg {
        .ifd GdipDrawCachedBitmap([rcx].Graphics.nativeGraphics, [rdx].CachedBitmap.nativeCachedBitmap, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawImage :ptr Image, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        .ifd GdipDrawImage([rcx].Graphics.nativeGraphics, rdx, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawImageI :ptr Image, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        .ifd GdipDrawImageI([rcx].Graphics.nativeGraphics, rdx, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawImageRect :ptr Image, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        .ifd GdipDrawImageRect([rcx].Graphics.nativeGraphics, rdx, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawImageRectI :ptr Image, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        .ifd GdipDrawImageRectI([rcx].Graphics.nativeGraphics, rdx, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }
    .operator DrawImagePoints :ptr Image, :ptr PointF, :vararg {
        .if (r8d != 3 && r8d != 4)
            mov eax,InvalidParameter
        .else
            .if rdx
                mov rdx,[rdx].Image.nativeImage
            .endif
            .ifd GdipDrawImagePoints([rcx].Graphics.nativeGraphics, rdx, r8, r8d)
                mov this.lastResult,eax
            .endif
        .endif
        exitm<>
        }

    .operator DrawImagePointsI :ptr Image, :ptr Point, :vararg {
        .if (r8d != 3 && r8d != 4)
            mov eax,InvalidParameter
        .else
            .if rdx
                mov rdx,[rdx].Image.nativeImage
            .endif
            .ifd GdipDrawImagePointsI([rcx].Graphics.nativeGraphics, rdx, r8, _3)
                mov this.lastResult,eax
            .endif
        .endif
        exitm<>
        }

    ;.operator DrawImage :ptr Image, :ptr Point {
    ;    DrawImage(image, point.X, point.Y)
    ;}
    ;.operator DrawImage :ptr Image, :ptr PointF {
    ;    DrawImage(image, point.X, point.Y)
    ;}


    .operator DrawImagePointRect :ptr Image, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        .ifd GdipDrawImagePointRect([rcx].Graphics.nativeGraphics, rdx, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawImageRectRect :ptr Image, :ptr RectF, :REAL, :REAL, :REAL, :REAL, :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {
       .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        mov r10,_8
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipDrawImageRectRect([this].Graphics.nativeGraphics, _1, [_2].RectF.X, [_2].RectF.Y,\
            [_2].RectF.Width, [_2].RectF.Height, _3, _4, _5, _6, _7, r10, _9, _10)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawImagePointsRect :ptr Image, :ptr PointF, :SINT, :REAL, :REAL, :REAL, :REAL, :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {
       .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        mov r10,_8
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipDrawImagePointsRect([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8, r10, _10, _11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawImagePointRectI :ptr Image, :vararg {
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        .ifd GdipDrawImagePointRectI([rcx].Graphics.nativeGraphics, rdx, _2)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawImageRectRectI :ptr Image, :ptr Rect, :SINT, :SINT, :SINT, :SINT,\
            :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {

       .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        mov r10,_8
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipDrawImageRectRectI([rcx].Graphics.nativeGraphics, rdx,\
            [r8].Rect.X, [r8].Rect.Y, [r8].Rect.Width, [r8].Rect.Height,\
            r9d, _4, _5, _6, _7, r10, _9, _10)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawImagePointsRectI :ptr Image, :ptr Point, :SINT, :SINT, :SINT,\
            :SINT, :SINT, :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {
       .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx].Image.nativeImage
        .endif
        mov r10,_9
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipDrawImagePointsRectI([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, _5, _6, _7, _8, r10, _10, _11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

if (GDIPVER GE 0x0110)
    .operator DrawImageRectRect2 :ptr Image, :ptr RectF, :ptr RectF,\
            :Unit, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        mov r10,_5
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipDrawImageRectRect([rcx].Graphics.nativeGraphics, [rdx].Image.nativeImage,\
            [r8].RectF.X, [r8].RectF.Y, [r8].RectF.Width, [r8].RectF.Height,\
            [r9].RectF.X, [r9].RectF.Y, [r9].RectF.Width, [r9].RectF.Height,\
            _4, r10, NULL, NULL)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator DrawImageFX :ptr Image, :ptr RectF, :ptr Matrix, :ptr Effect,\
            :ptr ImageAttributes, :Unit {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if r9
            mov r9,[r9].Matrix.nativeMatrix
        .endif
        mov r10,_4
        .if r10
            mov r10,[r10].Effect.nativeEffect
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipDrawImageFX([rcx].Graphics.nativeGraphics, [rdx].Image.nativeImage,\
                _2, _3, r10, r11, _6)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }
endif

    ;; The following methods are for playing an EMF+ to a graphics
    ;; via the enumeration interface.  Each record of the EMF+ is
    ;; sent to the callback (along with the callbackData).  Then
    ;; the callback can invoke the Metafile::PlayRecord method
    ;; to play the particular record.

    .operator EnumerateMetafileDestPoint :ptr Metafile, :ptr PointF,\
            :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileDestPoint([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileDestPointI :ptr Metafile, :ptr Point,\
            :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileDestPointI([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileDestRect :ptr Metafile, :ptr Rect,\
            :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileDestRect([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileDestRectI :ptr Metafile, :ptr Rect,\
            :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileDestRectI([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileDestPoints :ptr Metafile, :ptr PointF, :SINT,\
            :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_6
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileDestPoints([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, _5, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileDestPointsI :ptr Metafile, :ptr Point,\
            :SINT, :EnumerateMetafileProc, :ptr,:ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileDestPointsI([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, _5, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileSrcRectDestPoint :ptr Metafile, :ptr PointF, :ptr RectF,\
            :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileSrcRectDestPoint([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, _5, _6, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileSrcRectDestPointI :ptr Metafile, :ptr Point,\
            :ptr Rect, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileSrcRectDestPointI([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, _5, _6, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileSrcRectDestRect :ptr Metafile, :ptr RectF,\
            :ptr RectF, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileSrcRectDestRect([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, _5, _6, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileSrcRectDestRectI :ptr, :ptr, :ptr, :Unit,\
            :EnumerateMetafileProc, :ptr, :ptr {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileSrcRectDestRectI([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, _5, _6, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileSrcRectDestPoints :ptr Metafile, :ptr PointF, :SINT,\
            :ptr RectF, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_8
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileSrcRectDestPoints([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, _5, _6, _7, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator EnumerateMetafileSrcRectDestPointsI :ptr Metafile, :ptr Point,\
            :SINT, :ptr Rect, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        .new @graphics:ptr Graphics
        mov @graphics,rcx
        .if rdx
            mov rdx,[rdx];.Metafile.nativeImage
        .endif
        mov r11,_8
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        .ifd GdipEnumerateMetafileSrcRectDestPointsI([rcx].Graphics.nativeGraphics,\
                _1, _2, _3, _4, _5, _6, _7, r11)
            mov rcx,@graphics
            mov [rcx].Graphics.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetClip :ptr Graphics, :vararg {
        .ifd GdipSetClipGraphics([rcx].Graphics.nativeGraphics, [rdx].Graphics.nativeGraphics, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetClipRect :ptr RectF, :vararg {
        .ifd GdipSetClipRect([rcx].Graphics.nativeGraphics,\
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetClipRectI :ptr Rect, :vararg {
        .ifd GdipSetClipRectI([rcx].Graphics.nativeGraphics,\
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetClipPath :ptr GraphicsPath, :vararg {
        .ifd GdipSetClipPath([rcx].Graphics.nativeGraphics, [rdx].GraphicsPath.nativePath, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetClipRegion :ptr Region, :vararg {
        .ifd GdipSetClipRegion([rcx].Graphics.nativeGraphics, [rdx].Region.nativeRegion, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    ;; This is different than the other SetClip methods because it assumes
    ;; that the HRGN is already in device units, so it doesn't transform
    ;; the coordinates in the HRGN.

    .operator SetClipHrgn :HRGN, :vararg {
        .ifd GdipSetClipHrgn([rcx].Graphics.nativeGraphics, _1, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator IntersectClipRect :ptr RectF, :vararg {
        .ifd GdipSetClipRect([rcx].Graphics.nativeGraphics,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width,\
                [rdx].RectF.Height, CombineModeIntersect)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator IntersectClipRectI :ptr Rect, :vararg {
        .ifd GdipSetClipRectI([rcx].Graphics.nativeGraphics,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, CombineModeIntersect)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator IntersectClipRegion :ptr Region, :vararg {
        .ifd GdipSetClipRegion([rcx].Graphics.nativeGraphics,\
                [rdx].Region.nativeRegion, CombineModeIntersect)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator ExcludeClipRect :ptr RectF, :vararg {
        .ifd GdipSetClipRect([rcx].Graphics.nativeGraphics,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, CombineModeExclude)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator ExcludeClipRectI :ptr Rect, :vararg {
        .ifd GdipSetClipRectI([rcx].Graphics.nativeGraphics,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, CombineModeExclude)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator ExcludeClipRegion :ptr Region, :vararg {
        .ifd GdipSetClipRegion([rcx].Graphics.nativeGraphics, [rdx].Region.nativeRegion, CombineModeExclude)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator ResetClip :vararg {
        .ifd GdipResetClip([rcx].Graphics.nativeGraphics)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator TranslateClip :vararg {
        .ifd GdipTranslateClip([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator TranslateClipI :vararg {
        .ifd GdipTranslateClipI([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetClip :ptr, :vararg {
        .ifd GdipGetClip([rcx].Graphics.nativeGraphics, [rdx].Region.nativeRegion)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetClipBounds :vararg  {
        .ifd GdipGetClipBounds([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetClipBoundsI :vararg {
        .ifd GdipGetClipBoundsI([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator IsClipEmpty :vararg {

        .new booln:BOOL

        mov booln,FALSE
        .ifd GdipIsClipEmpty([rcx].Graphics.nativeGraphics, &booln)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,booln>
        }

    .operator GetVisibleClipBounds :ptr RectF, :vararg {
        .ifd GdipGetVisibleClipBounds([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetVisibleClipBoundsI :ptr Rect, :vararg {
        .ifd GdipGetVisibleClipBoundsI([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator IsVisibleClipEmpty :vararg {

        .new @bool:BOOL

        mov @bool,FALSE
        .ifd GdipIsVisibleClipEmpty([rcx].Graphics.nativeGraphics, &@bool)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,@bool>
        }

    .operator IsVisiblePointI :ptr Point, :vararg {

        .new @bool:BOOL

        mov @bool,FALSE
        .ifd GdipIsVisiblePointI([rcx].Graphics.nativeGraphics,\
                [rdx].Point.X, [rdx].Point.Y, &@bool)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,@bool>
        }

    .operator IsVisiblePoint2I :SINT, :SINT, :vararg {

        .new point:Point

        mov point.X,_1
        mov point.Y,_2
        exitm<this.IsVisiblePointI(&point)>
        }

    .operator IsVisibleRectI :ptr Rect, :vararg {

        .new @bool:BOOL

        mov @bool,TRUE
        .ifd GdipIsVisibleRectI([rcx].Graphics.nativeGraphics,\
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, &@bool)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,@bool>
        }

    .operator IsVisibleRect2I :SINT, :SINT, :SINT, :SINT, :vararg {

        .new rect:Rect

        mov rect.X,_1
        mov rect.Y,_2
        mov rect.Width,_3
        mov rect.Height,_4
        exitm<this.IsVisibleRectI(&rect)>
        }

    .operator IsVisiblePoint :ptr PointF, :vararg {

        .new @bool:BOOL

        mov @bool,FALSE
        .ifd GdipIsVisiblePoint([rcx].Graphics.nativeGraphics, [rdx].Point.X, [rdx].Point.Y, &@bool)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,@bool>
        }

    .operator IsVisiblePoint2 :REAL, :REAL, :vararg {

        .new pointf:PointF

        movss pointf.X,xmm1
        movss pointf.Y,xmm2
        exitm<this.IsVisiblePoint(&pointf)>
        }

    .operator IsVisibleRect :ptr RectF, :vararg {

        .new @bool:BOOL

        mov @bool,TRUE
        .ifd GdipIsVisibleRect([rcx].Graphics.nativeGraphics,\
            [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, &@bool)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,@bool>
        }

    .operator IsVisibleRect2 :REAL, :REAL, :REAL, :REAL, :vararg {

        .new rectf:RectF

        movss rectf.X,xmm1
        movss rectf.Y,xmm2
        movss rectf.Width,xmm3
        mov rectf.Height,_4
        exitm<this.IsVisibleRect(&rectf)>
        }

    .operator Save :vararg {

        .new gstate:GraphicsState

        .ifd GdipSaveGraphics([rcx].Graphics.nativeGraphics, &gstate)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,gstate>
        }

    .operator Restore :vararg {
        .ifd GdipRestoreGraphics([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator BeginContainer :ptr RectF, :ptr RectF, :vararg {

        .new state:GraphicsContainer

        .ifd GdipBeginContainer([rcx].Graphics.nativeGraphics, _1, _2, _3, &state)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,state>
        }

    .operator BeginContainerI :ptr Rect, :ptr Rect, :vararg {

        .new state:GraphicsContainer

        .ifd GdipBeginContainerI([rcx].Graphics.nativeGraphics, _1, _2, _3, &state)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,state>
        }

    .operator BeginContainer2 :vararg {

        .new state:GraphicsContainer

        .ifd GdipBeginContainer2([rcx].Graphics.nativeGraphics, &state)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,state>
        }

    .operator EndContainer :vararg {
        .ifd GdipEndContainer([rcx].Graphics.nativeGraphics, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    ;; Only valid when recording metafiles.

    .operator AddMetafileComment :ptr BYTE, :UINT {
        xchg _1,r8
        exitm<GdipComment([this].Graphics.nativeGraphics, edx, r8)>
        }

    .operator GetHalftonePalette {
        exitm<GdipCreateHalftonePalette()>
        }

    .operator GetLastStatus {
        mov eax,[this].Graphics.lastResult
        mov [this].Graphics.lastResult,Ok
        retm<eax>
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
