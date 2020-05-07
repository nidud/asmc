ifndef _GDIPLUSGRAPHICS_H
_GDIPLUSGRAPHICS_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template Graphics

    nativeGraphics  ptr_t ?
    lastResult      Status ?
    memState        Status ?


    .operator Graphics {

        .new graphics:ptr Graphics

        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !GdipAlloc(Graphics)
                mov [rax].Graphics.memState,Ok
            .else
                mov [rax].Graphics.memState,NotImplemented
            .endif
            mov [rax].Graphics.nativeGraphics,NULL
            mov [rax].Graphics.lastResult,NotImplemented
        .until 1
        retm<rax>
        }

    .operator Release {

        mov graphics,this

        GdipDeleteGraphics([this].Graphics.nativeGraphics)

        mov this,graphics
        .if [this].Graphics.memState != NotImplemented

            GdipFree(this)
        .endif
        exitm<>
        }

    .operator FromHDC :HDC {
        mov graphics,this
        xchg this,_1
        GdipCreateFromHDC(this, &[_1].Graphics.nativeGraphics)
        exitm<graphics.SetStatus(eax)>
        }

    .operator FromHDC2 :HDC, :HANDLE {
        mov graphics,this
        mov rax,_1
        mov _1,_2
        GdipCreateFromHDC2(rax, _1, &[this].Graphics.nativeGraphics)
        exitm<graphics.SetStatus(eax)>
        }

    .operator FromHWND :HWND, :BOOL {
        mov graphics,this
        mov [this].Graphics.nativeGraphics,NULL
        xchg this,_1
        .if _2
            GdipCreateFromHWNDICM(this, &[_1].Graphics.nativeGraphics)
        .else
            GdipCreateFromHWND(this, &[_1].Graphics.nativeGraphics)
        .endif
        exitm<graphics.SetStatus(eax)>
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

    .operator GetHDC {

        .new hdc:HDC

        mov hdc,NULL
        mov graphics,this
        GdipGetDC([this].Graphics.nativeGraphics, &hdc)
        graphics.SetStatus(eax)
        mov rax,hdc
        retm<rax>
        }

    .operator ReleaseHDC :HDC {
        mov graphics,this
        GdipReleaseDC([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    ;;------------------------------------------------------------------------
    ;; Rendering modes
    ;;------------------------------------------------------------------------

    .operator SetRenderingOrigin :int_t, :int_t {
        mov graphics,this
        GdipSetRenderingOrigin([this].Graphics.nativeGraphics, _1, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetRenderingOrigin :ptr int_t, :ptr int_t {
        mov graphics,this
        GdipGetRenderingOrigin([this].Graphics.nativeGraphics, _1, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator SetCompositingMode :CompositingMode {
        mov graphics,this
        GdipSetCompositingMode([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetCompositingMode {

        .new mode:CompositingMode

        mov graphics,this
        GdipGetCompositingMode([this].Graphics.nativeGraphics, &mode)
        graphics.SetStatus(eax)
        mov eax,mode
        retm<eax>
        }

    .operator SetCompositingQuality :CompositingQuality {
        mov graphics,this
        GdipSetCompositingQuality([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetCompositingQuality {

        .new quality:CompositingQuality

        mov graphics,this
        GdipGetCompositingQuality([this].Graphics.nativeGraphics, &quality)
        graphics.SetStatus(eax)
        mov eax,quality
        retm<eax>
        }

    .operator SetTextRenderingHint :TextRenderingHint {
        mov graphics,this
        GdipSetTextRenderingHint([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetTextRenderingHint {

        .new hint:TextRenderingHint

        mov graphics,this
        GdipGetTextRenderingHint([this].Graphics.nativeGraphics, &hint)
        graphics.SetStatus(eax)

        mov eax,hint
        retm<eax>
        }

    .operator SetTextContrast :UINT {
        mov graphics,this
        GdipSetTextContrast([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetTextContrast {

        .new contrast:UINT

        mov graphics,this
        GdipGetTextContrast([this].Graphics.nativeGraphics, &contrast)
        graphics.SetStatus(eax)
        mov eax,contrast
        retm<eax>
        }

    .operator GetInterpolationMode {

        .new mode:InterpolationMode

        mov mode,InterpolationModeInvalid
        mov graphics,this
        GdipGetInterpolationMode([this].Graphics.nativeGraphics, &mode)
        graphics.SetStatus(eax)
        mov eax,mode
        retm<eax>
        }

    .operator SetInterpolationMode :InterpolationMode {
        mov graphics,this
        GdipSetInterpolationMode([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

if (GDIPVER GE 0x0110)

    .operator SetAbort :ptr GdiplusAbort {
        mov graphics,this
        GdipGraphicsSetAbort([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

endif

    .operator GetSmoothingMode {

        .new smoothingMode:SmoothingMode

        mov smoothingMode,SmoothingModeInvalid
        mov graphics,this
        GdipGetSmoothingMode([this].Graphics.nativeGraphics, &smoothingMode)
        graphics.SetStatus(eax)
        mov eax,smoothingMode
        retm<eax>
        }

    .operator SetSmoothingMode :SmoothingMode {
        mov graphics,this
        GdipSetSmoothingMode([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetPixelOffsetMode {

        .new pixelOffsetMode:PixelOffsetMode

        mov pixelOffsetMode,PixelOffsetModeInvalid
        mov graphics,this
        GdipGetPixelOffsetMode([this].Graphics.nativeGraphics, &pixelOffsetMode)
        mov eax,pixelOffsetMode
        retm<eax>
        }

    .operator SetPixelOffsetMode :PixelOffsetMode {
        mov graphics,this
        GdipSetPixelOffsetMode([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    ;;------------------------------------------------------------------------
    ;; Manipulate current world transform
    ;;------------------------------------------------------------------------

    .operator SetTransform :ptr Matrix {
        mov graphics,this
        GdipSetWorldTransform([this].Graphics.nativeGraphics, [_1].Matrix.nativeMatrix)
        exitm<graphics.SetStatus(eax)>
        }
    .operator ResetTransform {
        mov graphics,this
        GdipResetWorldTransform([this].Graphics.nativeGraphics)
        exitm<graphics.SetStatus(eax)>
        }

    .operator MultiplyTransform :ptr Matrix, :MatrixOrder {
        mov graphics,this
        GdipMultiplyWorldTransform([this].Graphics.nativeGraphics, [_1].Matrix.nativeMatrix, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator TranslateTransform :REAL, :REAL, :MatrixOrder {
        mov graphics,this
        GdipTranslateWorldTransform([this].Graphics.nativeGraphics, _1, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator ScaleTransform :REAL, :REAL, :MatrixOrder {
        mov graphics,this
        GdipScaleWorldTransform([this].Graphics.nativeGraphics, _1, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator RotateTransform :REAL, :MatrixOrder {
        mov graphics,this
        GdipRotateWorldTransform([this].Graphics.nativeGraphics, _1, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetTransform :ptr Matrix {
        mov graphics,this
        GdipGetWorldTransform([this].Graphics.nativeGraphics, [_1].Matrix.nativeMatrix)
        exitm<graphics.SetStatus(eax)>
        }

    .operator SetPageUnit :Unit {
        mov graphics,this
        GdipSetPageUnit([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator SetPageScale :REAL {
        mov graphics,this
        GdipSetPageScale([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetPageUnit {

        .new unit:Unit

        mov graphics,this
        GdipGetPageUnit([this].Graphics.nativeGraphics, &unit)
        graphics.SetStatus(eax)
        mov eax,unit
        retm<eax>
        }

    .operator GetPageScale {

        .new scale:REAL

        mov graphics,this
        GdipGetPageScale([this].Graphics.nativeGraphics, &scale)
        movss xmm0,scale
        retm <xmm0>
        }

    .operator GetDpiX {

        .new dpi:REAL

        mov graphics,this
        GdipGetDpiX([this].Graphics.nativeGraphics, &dpi)
        graphics.SetStatus(eax)
        movss xmm0,dpi
        retm <xmm0>
        }

    .operator GetDpiY {

        .new dpi:REAL

        mov graphics,this
        GdipGetDpiY([this].Graphics.nativeGraphics, &dpi)
        graphics.SetStatus(eax)
        movss xmm0,dpi
        retm <xmm0>
        }

    .operator TransformPoints :CoordinateSpace, :CoordinateSpace, :ptr PointF, :SINT {
        mov graphics,this
        GdipTransformPoints([this].Graphics.nativeGraphics, _1, _2, _3, _4)
        exitm<graphics.SetStatus(eax)>
        }
    .operator TransformPointsI :CoordinateSpace, :CoordinateSpace, :ptr Point, :SINT {
        mov graphics,this
        GdipTransformPointsI([this].Graphics.nativeGraphics, _1, _2, _3, _4)
        exitm<graphics.SetStatus(eax)>
        }

    ;;------------------------------------------------------------------------
    ;; GetNearestColor (for <= 8bpp surfaces).  Note: Alpha is ignored.
    ;;------------------------------------------------------------------------

    .operator GetStatus {
        mov eax,[this].Graphics.lastResult
        retm <eax>
        }

    .operator GetNearestColor :ptr Color {

        .if (_1 == NULL)
            [this].Graphics.SetStatus(InvalidParameter)
        .else

            .new argb:ARGB
            .new color:ptr Color

            mov argb,[_1].Color.Argb
            mov color,_1

            mov graphics,this
            GdipGetNearestColor([this].Graphics.nativeGraphics, &argb)
            graphics.SetStatus(eax)
            color.SetValue(argb)
            graphics.GetStatus()
        .endif
        retm <eax>
        }

    .operator DrawLine :ptr Pen, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipDrawLine([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawLine2 :ptr Pen, :ptr PointF, :ptr PointF {
        exitm<[this].Graphics.DrawLine(_1, [_2].PointF.X, [_2].PointF.Y, [_3].PointF.X, [_3].PointF.Y)>
        }
    .operator DrawLines :ptr Pen, :ptr PointF, :SINT {
        mov graphics,this
        GdipDrawLines([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawLineI :ptr Pen, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        GdipDrawLineI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawLineI2 :ptr Pen, :ptr Point, :ptr Point {
        exitm<[this].Graphics.DrawLineI(_1, [_2].Point.X, [_2].Point.Y, [_3].Point.X, [_3].Point.Y)>
        }
    .operator DrawLinesI :ptr Pen, :ptr Point, :SINT {
        mov graphics,this
        GdipDrawLinesI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawArc :ptr Pen, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipDrawArc([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawArc2 :ptr Pen, :ptr RectF, :REAL, :REAL {
        exitm<[this].Graphics.DrawArc(_1, [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height,  _3, _4)>
        }
    .operator DrawArcI :ptr Pen, :SINT, :SINT, :SINT, :SINT, :REAL, :REAL {
        mov graphics,this
        GdipDrawArcI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawArc2 :ptr Pen, :ptr Rect, :REAL, :REAL {
        exitm<[this].Graphics.DrawArcI(_1, [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height, _3, _4)>
        }

    .operator DrawBezier :ptr Pen, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipDrawBezier([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7, _8, _9)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawBezier2 :ptr Pen, :ptr PointF, :ptr PointF, :ptr PointF, :ptr PointF {
        mov r10,_4
        mov r11,_5
        exitm<[this].Graphics.DrawBezier(_1, \
            [_2].PointF.X, [_2].PointF.Y, \
            [_3].PointF.X, [_3].PointF.Y, \
            [r10].PointF.X, [r10].PointF.Y, \
            [r11].PointF.X, [r11].PointF.Y )>
        }
    .operator DrawBeziers :ptr Pen, :ptr PointF, :SINT {
        mov graphics,this
        GdipDrawBeziers([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawBezierI :ptr Pen, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        GdipDrawBezierI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7, _8, _9)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawBezierI2 :ptr Pen, :ptr Point, :ptr Point, :ptr Point, :ptr Point {
        mov r10,_4
        mov r11,_5
        exitm<[this].Graphics.DrawBezierI(_1, \
            [_2].Point.X, [_2].Point.Y, \
            [_3].Point.X, [_3].Point.Y, \
            [r10].Point.X, [r10].Point.Y, \
            [r11].Point.X, [r11].Point.Y )>
        }
    .operator DrawBeziersI :ptr Pen, :ptr Point, :SINT {
        mov graphics,this
        GdipDrawBeziersI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawRectangle :ptr Pen, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipDrawRectangle([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawRectangle2 :ptr Pen, :ptr RectF {
        exitm<[this].Graphics.DrawRectangle(_1, [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height)>
        }
    .operator DrawRectangles :ptr Pen, :ptr RectF, :SINT {
        mov graphics,this
        GdipDrawRectangles([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawRectangleI :ptr Pen, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        GdipDrawRectangleI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawRectangleI2 :ptr Pen, :ptr Rect {
        exitm<[this].Graphics.DrawRectangleI(_1, [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height)>
        }
    .operator DrawRectanglesI :ptr Pen, :ptr Rect, :SINT {
        mov graphics,this
        GdipDrawRectanglesI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawEllipse :ptr Pen, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipDrawEllipse([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawEllipse2 :ptr Pen, :ptr RectF {
        exitm<[this].Graphics.DrawEllipse(_1, [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height)>
        }
    .operator DrawEllipseI :ptr Pen, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        GdipDrawEllipseI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawEllipse2I :ptr Pen, :ptr Rect {
        exitm<[this].Graphics.DrawEllipseI(_1, [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height)>
        }

    .operator DrawPie :ptr Pen, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipDrawPie([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawPie2 :ptr Pen, :ptr RectF, :REAL, :REAL {
        exitm<[this].Graphics.DrawPie(_1, [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height, _3, _4)>
        }
    .operator DrawPieI :ptr Pen, :SINT, :SINT, :SINT, :SINT, :REAL, :REAL {
        mov graphics,this
        GdipDrawPieI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawPie2I :ptr Pen, :ptr Rect, :REAL, :REAL {
        exitm<[this].Graphics.DrawPieI(_1, [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height, _3, _4)>
        }

    .operator DrawPolygon :ptr Pen, :ptr PointF, :SINT {
        mov graphics,this
        GdipDrawPolygon([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawPolygonI :ptr Pen, :ptr Point, :SINT {
        mov graphics,this
        GdipDrawPolygonI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawPath :ptr Pen, :ptr GraphicsPath {
        mov graphics,this
        .if _1
            mov _1,[_1]
        .endif
        .if _2
            mov _2,[_2]
        .endif
        GdipDrawPath([this].Graphics.nativeGraphics, _1, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawCurve :ptr Pen, :ptr PointF, :SINT {
        mov graphics,this
        GdipDrawCurve([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawCurve2 :ptr Pen, :ptr PointF, :SINT, :REAL {
        mov graphics,this
        GdipDrawCurve2([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawCurve3 :ptr Pen, :ptr PointF, :SINT, :SINT, :SINT, :REAL {
        mov graphics,this
        GdipDrawCurve3([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawCurveI :ptr Pen, :ptr Point, :SINT {
        mov graphics,this
        GdipDrawCurveI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawCurve2I :ptr Pen, :ptr Point, :SINT, :REAL {
        mov graphics,this
        GdipDrawCurve2I([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawCurve3I :ptr Pen, :ptr Point, :SINT, :SINT, :SINT, :REAL {
        mov graphics,this
        GdipDrawCurve3I([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawClosedCurve :ptr Pen, :ptr PointF, :SINT {
        mov graphics,this
        GdipDrawClosedCurve([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawClosedCurve2 :ptr Pen, :ptr PointF, :SINT, :REAL {
        mov graphics,this
        GdipDrawClosedCurve2([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawClosedCurveI :ptr Pen, :ptr Point, :SINT {
        mov graphics,this
        GdipDrawClosedCurveI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawClosedCurve2I :ptr Pen, :ptr Point, :SINT, :REAL {
        mov graphics,this
        GdipDrawClosedCurve2I([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4)
        exitm<graphics.SetStatus(eax)>
        }

    .operator Clear :ptr Color {
        mov graphics,this
        GdipGraphicsClear([this].Graphics.nativeGraphics, [_1].Color.Argb)
        exitm<graphics.SetStatus(eax)>
        }

    .operator FillRectangle :ptr Brush, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipFillRectangle([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillRectangle2 :ptr Brush, :ptr RectF {
        exitm<[this].Graphics.FillRectangle(_1, [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height)>
        }
    .operator FillRectangles :ptr Brush, :ptr RectF, :SINT {
        mov graphics,this
        GdipFillRectangles([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator FillRectangleI :ptr Brush, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        GdipFillRectangleI([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillRectangle2I :ptr Brush, :ptr Rect {
        exitm<[this].Graphics.FillRectangleI(_1, [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height)>
        }
    .operator FillRectanglesI :ptr Brush, :ptr Rect, :SINT {
        mov graphics,this
        GdipFillRectanglesI([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator FillPolygon :ptr Brush, :ptr PointF, :SINT, :FillMode {
        mov graphics,this
        GdipFillPolygon([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillPolygon2 :ptr Brush, :ptr PointF, :SINT {
        exitm<[this].Graphics.FillPolygon(_1, _2, _3, FillModeAlternate)>
        }
    .operator FillPolygonI :ptr Brush, :ptr Point, :SINT, :FillMode {
        mov graphics,this
        GdipFillPolygonI([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillPolygon2I :ptr Brush, :ptr Point, :SINT {
        exitm<[this].Graphics.FillPolygonI(_1, _2, _3, FillModeAlternate)>
        }

    .operator FillEllipse :ptr Brush, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipFillEllipse([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillEllipse2 :ptr Brush, :ptr RectF {
        exitm<[this].Graphics.FillEllipse(_1, [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height)>
        }
    .operator FillEllipseI :ptr Brush, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        GdipFillEllipseI([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillEllipse2I :ptr Brush, :ptr Rect {
        exitm<[this].Graphics.FillEllipseI(_1, [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height)>
        }

    .operator FillPie :ptr Brush, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipFillPie([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5, _6, _7)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillPie2 :ptr Brush, :ptr RectF, :REAL, :REAL {
        exitm<[this].Graphics.FillPie(_1, [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height,  _3, _4)>
        }
    .operator FillPieI :ptr Brush, :SINT, :SINT, :SINT, :SINT, :REAL, :REAL {
        mov graphics,this
        GdipFillPieI([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5, _6, _7)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillPie2I :ptr Brush, :ptr Rect, :REAL, :REAL {
        exitm<[this].Graphics.FillPieI(_1, [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height,  _3, _4)>
        }

    .operator FillPath :ptr Brush, :ptr GraphicsPath {
        mov graphics,this
        GdipFillPath([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, [_2].GraphicsPath.nativePath)
        exitm<graphics.SetStatus(eax)>
        }

    .operator FillClosedCurve :ptr Brush, :ptr PointF, :SINT {
        mov graphics,this
        GdipFillClosedCurve([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillClosedCurve2 :ptr Brush, :ptr PointF, :SINT, :FillMode, :REAL {
        mov graphics,this
        GdipFillClosedCurve2([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillClosedCurveI :ptr Brush, :ptr Point, :SINT {
        mov graphics,this
        GdipFillClosedCurveI([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }
    .operator FillClosedCurve2I :ptr Brush, :ptr Point, :SINT, :FillMode, :REAL {
        mov graphics,this
        GdipFillClosedCurve2I([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }

    .operator FillRegion :ptr Brush, :ptr Region {
        mov graphics,this
        GdipFillRegion([this].Graphics.nativeGraphics, [_1].Brush.nativeBrush, [_2].Region.nativeRegion)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawString :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :ptr Brush {
        mov graphics,this
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
        GdipDrawString([this].Graphics.nativeGraphics, _1, _2, _3, _4, r10, r11)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawString2 :ptr WCHAR, :SINT, :ptr Font, :ptr PointF, :ptr Brush {

        .new rect:RectF

        mov r10,_4
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.Width,0.0
        mov rect.Height,0.0
        exitm<[this].Graphics.DrawString(_1, _2, _3, &rect, NULL, _4)>
        }
    .operator DrawString3 :ptr WCHAR, :SINT, :ptr Font, :ptr PointF, :ptr StringFormat, :ptr Brush {

        .new rect:RectF

        mov r10,_4
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.Width,0.0
        mov rect.Height,0.0
        exitm<[this].Graphics.DrawString(_1, _2, _3, &rect, _5, _6)>
        }

    .operator MeasureString :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :ptr RectF, :SINT, :ptr SINT {
        mov graphics,this
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        mov r10,_5
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, _4, r10, _6, _7, _8)
        exitm<graphics.SetStatus(eax)>
        }
    .operator MeasureString2 :ptr WCHAR, :SINT, :ptr Font, :ptr SizeF, :ptr StringFormat, :ptr SizeF, :SINT, :SINT {

        .new layoutRect:RectF
        .new boundingBox:RectF
        .new size:ptr RectF

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
            graphics.SetStatus(eax)
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

        mov graphics,this
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
        GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, &rect, r10, _6, NULL, NULL)
        exitm<graphics.SetStatus(eax)>
        }
    .operator MeasureString4 :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr RectF {
        mov graphics,this
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, _4, NULL, _5, NULL, NULL)
        exitm<graphics.SetStatus(eax)>
        }
    .operator MeasureString5 :ptr WCHAR, :SINT, :ptr Font, :ptr PointF, :ptr RectF {

        .new rect:RectF

        mov r10,_4
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.Width,0.0
        mov rect.Height,0.0
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, &rect, NULL, _4, NULL, NULL)
        exitm<graphics.SetStatus(eax)>
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
        mov graphics,this
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
        GdipDrawDriverString([this].Graphics.nativeGraphics, _1, _2, _3, r10, _5, _6, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator MeasureDriverString :ptr UINT16, :SINT, :ptr Font, :ptr PointF, :SINT, :ptr Matrix, :ptr RectF {
        mov graphics,this
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        mov r10,_6
        .if r10
            mov r10,[r10].Matrix.nativeMatrix
        .endif
        GdipMeasureDriverString([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, r10, _7)
        exitm<graphics.SetStatus(eax)>
        }

    ;; Draw a cached bitmap on this graphics destination offset by
    ;; x, y. Note this will fail with WrongState if the CachedBitmap
    ;; native format differs from this Graphics.

    .operator DrawCachedBitmap :ptr CachedBitmap, :SINT, :SINT {
        mov graphics,this
        GdipDrawCachedBitmap([this].Graphics.nativeGraphics, [_1].CachedBitmap.nativeCachedBitmap, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawImage :ptr Image, :REAL, :REAL {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImage([this].Graphics.nativeGraphics, _1, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawImageI :ptr Image, :SINT, :SINT {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImageI([this].Graphics.nativeGraphics, _1, _2, _3)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawImageRect :ptr Image, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImageRect([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawImageRect2 :ptr Image, :ptr RectF {
        exitm<[this].Graphics.DrawImageRect(_1, [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height)>
        }
    .operator DrawImageRectI :ptr Image, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImageRectI([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
        }
    .operator DrawImageRect2I :ptr Image, :ptr Rect {
        exitm<[this].Graphics.DrawImageRectI(_1, [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height)>
        }
    .operator DrawImagePoints :ptr Image, :ptr PointF, :SINT {
        mov graphics,this
        .if (_3 != 3 && _3 != 4)
            mov eax,InvalidParameter
        .else
            .if _1
                mov _1,[_1].Image.nativeImage
            .endif
            GdipDrawImagePoints([this].Graphics.nativeGraphics, _1, _2, _3)
        .endif
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawImagePointsI :ptr Image, :ptr Point, :SINT {
        mov graphics,this
        .if (_3 != 3 && _3 != 4)
            mov eax,InvalidParameter
        .else
            .if _1
                mov _1,[_1].Image.nativeImage
            .endif
            GdipDrawImagePointsI([this].Graphics.nativeGraphics, _1, _2, _3)
        .endif
        exitm<graphics.SetStatus(eax)>
        }

    ;.operator DrawImage :ptr Image, :ptr Point {
    ;    DrawImage(image, point.X, point.Y)
    ;}
    ;.operator DrawImage :ptr Image, :ptr PointF {
    ;    DrawImage(image, point.X, point.Y)
    ;}


    .operator DrawImagePointRect :ptr Image, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL, :Unit {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImagePointRect([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawImageRectRect :ptr Image, :ptr RectF, :REAL, :REAL, :REAL, :REAL, :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        mov r10,_8
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRect([this].Graphics.nativeGraphics, _1, [_2].RectF.X, [_2].RectF.Y,\
            [_2].RectF.Width, [_2].RectF.Height, _3, _4, _5, _6, _7, r10, _9, _10)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawImagePointsRect :ptr Image, :ptr PointF, :SINT, :REAL, :REAL, :REAL, :REAL, :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        mov r10,_8
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImagePointsRect([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8, r10, _10, _11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawImagePointRectI :ptr Image, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT, :Unit {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImagePointRectI([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawImageRectRectI :ptr Image, :ptr Rect, :SINT, :SINT, :SINT, :SINT, :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        mov r10,_8
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRectI([this].Graphics.nativeGraphics, _1,\
            [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height, _3, _4, _5, _6, _7, r10, _9, _10)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawImagePointsRectI :ptr Image, :ptr Point, :SINT, :SINT, :SINT, :SINT, :SINT, :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {
        mov graphics,this
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        mov r10,_9
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImagePointsRectI([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8, r10, _10, _11)
        exitm<graphics.SetStatus(eax)>
        }

if (GDIPVER GE 0x0110)
    .operator DrawImageRectRect2 :ptr Image, :ptr RectF, :ptr RectF, :Unit, :ptr ImageAttributes {
        mov graphics,this
        mov r10,_5
        .if r10
            mov r10,[r10].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRect([this].Graphics.nativeGraphics, [_1].Image.nativeImage,\
            [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height,\
            [_3].RectF.X, [_3].RectF.Y, [_3].RectF.Width, [_3].RectF.Height,\
            _4, r10, NULL, NULL)
        exitm<graphics.SetStatus(eax)>
        }

    .operator DrawImageFX :ptr Image, :ptr RectF, :ptr Matrix, :ptr Effect, :ptr ImageAttributes, :Unit {
        mov graphics,this
        .if _3
            mov _3,[_3].Matrix.nativeMatrix
        .endif
        mov r10,_4
        .if r10
            mov r10,[r10].Effect.nativeEffect
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageFX([this].Graphics.nativeGraphics, [_1].Image.nativeImage, _2, _3, r10, r11, _6)
        exitm<graphics.SetStatus(eax)>
        }
endif

    ;; The following methods are for playing an EMF+ to a graphics
    ;; via the enumeration interface.  Each record of the EMF+ is
    ;; sent to the callback (along with the callbackData).  Then
    ;; the callback can invoke the Metafile::PlayRecord method
    ;; to play the particular record.

    .operator EnumerateMetafileDestPoint :ptr Metafile, :ptr PointF, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPoint([this].Graphics.nativeGraphics, _1, _2, _3, _4, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileDestPointI :ptr Metafile, :ptr Point, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPointI([this].Graphics.nativeGraphics, _1, _2, _3, _4, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileDestRect :ptr Metafile, :ptr Rect, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestRect([this].Graphics.nativeGraphics, _1, _2, _3, _4, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileDestRectI :ptr Metafile, :ptr Rect, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestRectI([this].Graphics.nativeGraphics, _1, _2, _3, _4, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileDestPoints :ptr Metafile, :ptr PointF, :SINT, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_6
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPoints([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileDestPointsI :ptr Metafile, :ptr Point, :SINT, :EnumerateMetafileProc, :ptr,:ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPointsI([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileSrcRectDestPoint :ptr Metafile, :ptr PointF, :ptr RectF, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPoint([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileSrcRectDestPointI :ptr Metafile, :ptr Point, :ptr Rect, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPointI([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileSrcRectDestRect :ptr Metafile, :ptr RectF, :ptr RectF, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestRect([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileSrcRectDestRectI :ptr, :ptr, :ptr, :Unit, :EnumerateMetafileProc, :ptr, :ptr {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_7
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestRectI([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileSrcRectDestPoints :ptr Metafile, :ptr PointF, :SINT, :ptr RectF, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_8
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPoints([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator EnumerateMetafileSrcRectDestPointsI :ptr Metafile, :ptr Point, :SINT, :ptr Rect, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        mov graphics,this
        .if _1
            mov _1,[_1];.Metafile.nativeImage
        .endif
        mov r11,_8
        .if r11
            mov r11,[r11].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPointsI([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, r11)
        exitm<graphics.SetStatus(eax)>
        }

    .operator SetClip :ptr Graphics, :CombineMode {
        mov graphics,this
        GdipSetClipGraphics([this].Graphics.nativeGraphics, [_1].Graphics.nativeGraphics, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator SetClipRect :ptr RectF, :CombineMode {
        mov graphics,this
        GdipSetClipRect([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator SetClipRectI :ptr Rect, :CombineMode {
        mov graphics,this
        GdipSetClipRectI([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator SetClipPath :ptr GraphicsPath, :CombineMode {
        mov graphics,this
        GdipSetClipPath([this].Graphics.nativeGraphics, [_1].GraphicsPath.nativePath, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator SetClipRegion :ptr Region, :CombineMode {
        mov graphics,this
        GdipSetClipRegion([this].Graphics.nativeGraphics, [_1].Region.nativeRegion, _2)
        exitm<graphics.SetStatus(eax)>
        }

    ;; This is different than the other SetClip methods because it assumes
    ;; that the HRGN is already in device units, so it doesn't transform
    ;; the coordinates in the HRGN.

    .operator SetClipHrgn :HRGN, :CombineMode {
        mov graphics,this
        GdipSetClipHrgn([this].Graphics.nativeGraphics, _1, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator IntersectClipRect :ptr RectF {
        mov graphics,this
        GdipSetClipRect([this].Graphics.nativeGraphics, [_1].RectF.X, [_1].RectF.Y, [_1].RectF.Width, [_1].RectF.Height, CombineModeIntersect)
        exitm<graphics.SetStatus(eax)>
        }

    .operator IntersectClipRectI :ptr Rect {
        mov graphics,this
        GdipSetClipRectI([this].Graphics.nativeGraphics, [_1].Rect.X, [_1].Rect.Y, [_1].Rect.Width, [_1].Rect.Height, CombineModeIntersect)
        exitm<graphics.SetStatus(eax)>
        }

    .operator IntersectClipRegion :ptr Region {
        mov graphics,this
        GdipSetClipRegion([this].Graphics.nativeGraphics, [_1].Region.nativeRegion, CombineModeIntersect)
        exitm<graphics.SetStatus(eax)>
        }

    .operator ExcludeClipRect :ptr RectF {
        mov graphics,this
        GdipSetClipRect([this].Graphics.nativeGraphics, [_1].RectF.X, [_1].RectF.Y, [_1].RectF.Width, [_1].RectF.Height, CombineModeExclude)
        exitm<graphics.SetStatus(eax)>
        }

    .operator ExcludeClipRectI :ptr Rect {
        mov graphics,this
        GdipSetClipRectI([this].Graphics.nativeGraphics, [_1].Rect.X, [_1].Rect.Y, [_1].Rect.Width, [_1].Rect.Height, CombineModeExclude)
        exitm<graphics.SetStatus(eax)>
        }

    .operator ExcludeClipRegion :ptr Region {
        mov graphics,this
        GdipSetClipRegion([this].Graphics.nativeGraphics, [_1].Region.nativeRegion, CombineModeExclude)
        exitm<graphics.SetStatus(eax)>
        }

    .operator ResetClip {
        mov graphics,this
        GdipResetClip([this].Graphics.nativeGraphics)
        exitm<graphics.SetStatus(eax)>
        }

    .operator TranslateClip :REAL, :REAL {
        mov graphics,this
        GdipTranslateClip([this].Graphics.nativeGraphics, _1, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator TranslateClipI :SINT,:SINT {
        mov graphics,this
        GdipTranslateClipI([this].Graphics.nativeGraphics, _1, _2)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetClip :ptr {
        mov graphics,this
        GdipGetClip([this].Graphics.nativeGraphics, [_1].Region.nativeRegion)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetClipBounds :ptr RectF  {
        mov graphics,this
        GdipGetClipBounds([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetClipBoundsI :ptr Rect {
        mov graphics,this
        GdipGetClipBoundsI([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator IsClipEmpty {

        .new booln:BOOL

        mov booln,FALSE
        mov graphics,this
        GdipIsClipEmpty([this].Graphics.nativeGraphics, &booln)
        graphics.SetStatus(eax)
        mov eax,booln
        retm<eax>
        }

    .operator GetVisibleClipBounds :ptr RectF {
        mov graphics,this
        GdipGetVisibleClipBounds([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator GetVisibleClipBoundsI :ptr Rect {
        mov graphics,this
        GdipGetVisibleClipBoundsI([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator IsVisibleClipEmpty {

        .new booln:BOOL

        mov booln,FALSE
        mov graphics,this
        GdipIsVisibleClipEmpty([this].Graphics.nativeGraphics, &booln)
        graphics.SetStatus(eax)
        mov eax,booln
        retm<eax>
        }

    .operator IsVisiblePointI :ptr Point {

        .new booln:BOOL

        mov booln,FALSE
        mov graphics,this
        GdipIsVisiblePointI([this].Graphics.nativeGraphics, [_1].Point.X, [_1].Point.Y, &booln)
        graphics.SetStatus(eax)
        mov eax,booln
        retm<eax>
        }

    .operator IsVisiblePoint2I :SINT, :SINT {

        .new point:Point

        mov point.X,_1
        mov point.Y,_2
        exitm<[this].Graphics.IsVisiblePointI(&point)>
        }

    .operator IsVisibleRectI :ptr Rect {

        .new booln:BOOL

        mov booln,TRUE
        mov graphics,this
        GdipIsVisibleRectI([this].Graphics.nativeGraphics, [_1].Rect.X, [_1].Rect.Y, [_1].Rect.Width, [_1].Rect.Height, &booln)
        graphics.SetStatus(eax)
        mov eax,booln
        retm<eax>
        }

    .operator IsVisibleRect2I :SINT, :SINT, :SINT, :SINT {

        .new rect:Rect

        mov rect.X,_1
        mov rect.Y,_2
        mov rect.Width,_3
        mov rect.Height,_4
        exitm<[this].Graphics.IsVisibleRectI(&rect)>
        }

    .operator IsVisiblePoint :ptr PointF {

        .new booln:BOOL

        mov booln,FALSE
        mov graphics,this
        GdipIsVisiblePoint([this].Graphics.nativeGraphics, [_1].Point.X, [_1].Point.Y, &booln)
        graphics.SetStatus(eax)
        mov eax,booln
        retm<eax>
        }

    .operator IsVisiblePoint2 :REAL, :REAL {

        .new pointf:PointF

        movss pointf.X,_1
        movss pointf.Y,_2
        exitm<[this].Graphics.IsVisiblePoint(&pointf)>
        }

    .operator IsVisibleRect :ptr RectF {

        .new booln:BOOL

        mov booln,TRUE
        mov graphics,this
        GdipIsVisibleRect([this].Graphics.nativeGraphics, [_1].RectF.X, [_1].RectF.Y, [_1].RectF.Width, [_1].RectF.Height, &booln)
        graphics.SetStatus(eax)
        mov eax,booln
        retm<eax>
        }

    .operator IsVisibleRect2 :REAL, :REAL, :REAL, :REAL {

        .new rectf:RectF

        movss rectf.X,_1
        movss rectf.Y,_2
        movss rectf.Width,_3
        mov rectf.Height,_4
        exitm<[this].Graphics.IsVisibleRect(&rectf)>
        }

    .operator Save {

        .new gstate:GraphicsState

        mov graphics,this
        GdipSaveGraphics([this].Graphics.nativeGraphics, &gstate)
        graphics.SetStatus(eax)
        mov eax,gstate
        retm<eax>
        }

    .operator Restore :GraphicsState {
        mov graphics,this
        GdipRestoreGraphics([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
        }

    .operator BeginContainer :ptr RectF, :ptr RectF, :Unit {

        .new state:GraphicsContainer

        mov graphics,this
        GdipBeginContainer([this].Graphics.nativeGraphics, _1, _2, _3, &state)
        graphics.SetStatus(eax)
        mov eax,state
        retm<eax>
        }

    .operator BeginContainerI :ptr Rect, :ptr Rect, :Unit {

        .new state:GraphicsContainer

        mov graphics,this
        GdipBeginContainerI([this].Graphics.nativeGraphics, _1, _2, _3, &state)
        graphics.SetStatus(eax)
        mov eax,state
        retm<eax>
        }

    .operator BeginContainer2 {

        .new state:GraphicsContainer

        mov graphics,this
        GdipBeginContainer2([this].Graphics.nativeGraphics, &state)
        graphics.SetStatus(eax)
        mov eax,state
        retm<eax>
        }

    .operator EndContainer :GraphicsContainer {
        mov graphics,this
        GdipEndContainer([this].Graphics.nativeGraphics, _1)
        exitm<graphics.SetStatus(eax)>
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
