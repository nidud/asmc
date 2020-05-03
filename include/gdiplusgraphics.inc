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
        retm    <eax>
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
        exitm   <>
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
        GdipGetRenderingOrigin([this].Graphics.nativeGraphics, x, y)
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
        mov rax,mode
        retm<rax>
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
        return SetStatus(DllExports::GdipSetWorldTransform([this].Graphics.nativeGraphics,
                                                        matrix->nativeMatrix));
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

    .operator TransformPoints :CoordinateSpace, :CoordinateSpace, :ptr Point, :SINT {
        mov graphics,this
        GdipTransformPointsI([this].Graphics.nativeGraphics, _1, _2, _3, _4)
        exitm<graphics.SetStatus(eax)>
    }

    ;;------------------------------------------------------------------------
    ;; GetNearestColor (for <= 8bpp surfaces).  Note: Alpha is ignored.
    ;;------------------------------------------------------------------------

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

    .operator DrawLine :ptr Pen, :ptr PointF, :ptr PointF {
        exitm<[this].Graphics.DrawLine(_1, [_2].PointF.X, [_2].PointF.Y, [_3].PointF.X, [_3].PointF.Y)>
    }

    .operator DrawLines :ptr Pen, :ptr PointF, :SINT {
        mov graphics,this
        GdipDrawLines([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawLine :ptr Pen, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        GdipDrawLineI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawLine :ptr Pen, :ptr Point, :ptr Point {
        exitm<[this].Graphics.DrawLine(_1, [_2].Point.X, [_2].Point.Y, [_3].Point.X, [_3].Point.Y)>
    }

    .operator DrawLines :ptr Pen, :ptr Point, :SINT {
        mov graphics,this
        GdipDrawLinesI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _1, _2)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawArc :ptr Pen, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipDrawArc([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawArc :ptr Pen, :ptr RectF, :REAL, :REAL {
        exitm<[this].Graphics.DrawArc(_1, [_2].RectF.X, [_2].RectF.Y, [_2].RectF.Width, [_2].RectF.Height,  _3, _4)>
    }

    .operator DrawArc :ptr Pen, :SINT, :SINT, :SINT, :SINT, :REAL, :REAL {
        mov graphics,this
        GdipDrawArcI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7)
        exitm<graphics.SetStatus(eax)>
    }


    .operator DrawArc :ptr Pen, :ptr Rect, :REAL, :REAL {
        exitm<[this].Graphics.DrawArc(_1, [_2].Rect.X, [_2].Rect.Y, [_2].Rect.Width, [_2].Rect.Height,  _3, _4)>
    }

    .operator DrawBezier :ptr Pen, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipDrawBezier([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7, _8, _9)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawBezier :ptr Pen, :ptr PointF, :ptr PointF, :ptr PointF, :ptr PointF {
        DrawBezier(_1, pt1.X, pt1.Y, pt2.X, pt2.Y, pt3.X, pt3.Y, pt4.X, pt4.Y)
    }

    .operator DrawBeziers :ptr Pen, :ptr PointF, :SINT {
        mov graphics,this
        GdipDrawBeziers([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawBezier :ptr Pen, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        GdipDrawBezierI([this].Graphics.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7, _8, _9)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawBezier :ptr Pen, :ptr Point, :ptr Point, :ptr Point, :ptr Point {
        DrawBezier(pen, pt1.X, pt1.Y, pt2.X, pt2.Y, pt3.X, pt3.Y, pt4.X, pt4.Y)
    }

    .operator DrawBeziers :ptr Pen, :ptr Point, :SINT {
        mov graphics,this
        GdipDrawBeziersI([this].Graphics.nativeGraphics, pen->nativePen, _2, _3)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawRectangle :ptr Pen, :ptr RectF {
        DrawRectangle(_1, rect.X, rect.Y, rect.Width, rect.Height)
    }

    .operator DrawRectangle :ptr Pen, :REAL, :REAL, :REAL, :REAL {
        mov graphics,this
        GdipDrawRectangle([this].Graphics.nativeGraphics, pen->nativePen, x, y, width, height)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawRectangles :ptr Pen, :ptr RectF, :SINT {
        mov graphics,this
        GdipDrawRectangles([this].Graphics.nativeGraphics, pen->nativePen, rects, count)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawRectangle :ptr Pen, :ptr Rect {
        DrawRectangle(pen, rect.X, rect.Y, ect.Width, rect.Height)
    }

    .operator DrawRectangle :ptr Pen, :SINT, :SINT, :SINT, :SINT {
        mov graphics,this
        GdipDrawRectangleI([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4, _5)
        exitm<graphics.SetStatus(eax)>
    }

    .operator DrawRectangles :ptr Pen, :ptr Rect, :SINT {
        GdipDrawRectanglesI([this].Graphics.nativeGraphics, pen->nativePen, _2, _3)
    }

    .operator DrawEllipse :ptr Pen, :ptr RectF {
        DrawEllipse(_1, rect.X, rect.Y, rect.Width, rect.Height)
    }

    .operator DrawEllipse :ptr Pen, :REAL, :REAL, :REAL, :REAL {
        GdipDrawEllipse([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4, _5)
    }

    .operator DrawEllipse :ptr Pen, :ptr Rect {
        DrawEllipse(pen, rect.X, rect.Y, rect.Width, rect.Height)
    }

    .operator DrawEllipse :ptr Pen, :SINT, :SINT, :SINT, :SINT {
        GdipDrawEllipseI([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4, _5)
    }

    .operator DrawPie :ptr Pen, :ptr RectF, :REAL, :REAL {
        DrawPie(pen, rect.X, rect.Y, rect.Width, rect.Height, startAngle, sweepAngle)
    }

    .operator DrawPie :ptr Pen, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        GdipDrawPie([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4, _5, _6, _7)
    }

    .operator DrawPie :ptr Pen, :ptr Rect, :REAL, :REAL {
        DrawPie(pen, rect.X, rect.Y, rect.Width, rect.Height, startAngle, sweepAngle)
    }

    .operator DrawPie :ptr Pen, :SINT, :SINT, :SINT, :SINT, :REAL, :REAL {
        GdipDrawPieI([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4, _5, _6, _7)
    }

    .operator DrawPolygon :ptr Pen, :ptr PointF, :SINT {
        GdipDrawPolygon([this].Graphics.nativeGraphics, pen->nativePen, points, count)
    }

    .operator DrawPolygon :ptr Pen, :ptr Point, :SINT {
        GdipDrawPolygonI([this].Graphics.nativeGraphics, pen->nativePen, points, count)
    }

    .operator DrawPath :ptr Pen, :ptr GraphicsPath {
        GdipDrawPath([this].Graphics.nativeGraphics, pen ? pen->nativePen : NULL, path ? path->nativePath : NULL))
    }

    .operator DrawCurve :ptr Pen, :ptr PointF, :SINT {
        GdipDrawCurve([this].Graphics.nativeGraphics, pen->nativePen, _2, _3)
    }

    .operator DrawCurve :ptr Pen, :ptr PointF, :SINT, :REAL {
        GdipDrawCurve2([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4)
    }

    .operator DrawCurve :ptr Pen, :ptr PointF, :SINT, :SINT, :SINT, :REAL {
        GdipDrawCurve3([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4, _5, _6)
    }

    .operator DrawCurve :ptr Pen, :ptr Point, :SINT {
        GdipDrawCurveI([this].Graphics.nativeGraphics, pen->nativePen, _2, _3)
    }

    .operator DrawCurve :ptr Pen, :ptr Point, :SINT, :REAL {
          GdipDrawCurve2I([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4)
    }

    .operator DrawCurve :ptr Pen, :ptr Point, :SINT, :SINT, :SINT, :REAL {
        GdipDrawCurve3I([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4, _5, _6)
    }

    .operator DrawClosedCurve :ptr Pen, :ptr PointF, :SINT {
        GdipDrawClosedCurve([this].Graphics.nativeGraphics, pen->nativePen, _2, _3)
    }

    .operator DrawClosedCurve :ptr Pen, :ptr PointF, :SINT, :REAL {
        GdipDrawClosedCurve2([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4)
    }

    .operator DrawClosedCurve :ptr Pen, :ptr Point, :SINT {
        GdipDrawClosedCurveI([this].Graphics.nativeGraphics, pen->nativePen, _2, _3)
    }

    .operator DrawClosedCurve :ptr Pen, :ptr Point, :SINT, :REAL {
        GdipDrawClosedCurve2I([this].Graphics.nativeGraphics, pen->nativePen, _2, _3, _4)
    }

    .operator Clear :ptr Color {
        GdipGraphicsClear([this].Graphics.nativeGraphics, color.GetValue())
    }

    .operator FillRectangle :ptr Brush, :ptr RectF {
        FillRectangle(brush, rect.X, rect.Y, rect.Width, rect.Height)
    }

    .operator FillRectangle :ptr Brush, :REAL, :REAL, :REAL, :REAL {
        GdipFillRectangle([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4, _5)
    }

    .operator FillRectangles :ptr Brush, :ptr RectF, :SINT {
        GdipFillRectangles([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3)
    }

    .operator FillRectangle :ptr Brush, :ptr Rect {
        FillRectangle(brush, rect.X,rect.Y, rect.Width, rect.Height)
    }

    .operator FillRectangle :ptr Brush, :SINT, :SINT, :SINT, :SINT {
        GdipFillRectangleI([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4, _5)
    }

    .operator FillRectangles :ptr Brush, :ptr Rect, :SINT {
        GdipFillRectanglesI([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3)
    }

    .operator FillPolygon :ptr Brush, :ptr PointF, :SINT {
        FillPolygon(brush, points, count, FillModeAlternate)
    }

    .operator FillPolygon :ptr Brush, :ptr PointF, :SINT, :FillMode {
        GdipFillPolygon([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4)
    }

    .operator FillPolygon :ptr Brush, :ptr Point, :SINT {
        FillPolygon(brush, points, count, FillModeAlternate)
    }

    .operator FillPolygon :ptr Brush, :ptr Point, :SINT, :FillMode {
        GdipFillPolygonI([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4)
    }

    .operator FillEllipse :ptr Brush, :ptr RectF {
        FillEllipse(brush, rect.X, rect.Y, rect.Width, rect.Height)
    }

    .operator FillEllipse :ptr Brush* brush, :REAL, :REAL, :REAL, :REAL {
        GdipFillEllipse([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4, _5)
    }

    .operator FillEllipse :ptr Brush, :ptr Rect {
        FillEllipse(brush, rect.X, rect.Y, rect.Width, rect.Height)
    }

    .operator FillEllipse :ptr Brush, :SINT, :SINT, :SINT, :SINT {
        GdipFillEllipseI([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4, _5)
    }

    .operator FillPie :ptr Brush, :ptr RectF, :REAL, :REAL {
        FillPie(brush, rect.X, rect.Y, rect.Width, rect.Height, startAngle, sweepAngle)
    }

    .operator FillPie :ptr Brush, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        GdipFillPie([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4, _5, _6, _7)
    }

    .operator FillPie :ptr Brush, :ptr Rect, :REAL, :REAL {
        FillPie(brush, rect.X, rect.Y, rect.Width, rect.Height,  startAngle, sweepAngle)
    }

    .operator FillPie :ptr Brush, :SINT, :SINT, :SINT, :SINT, :REAL, :REAL {
        GdipFillPieI([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4, _5, _6, _7)
    }

    .operator FillPath :ptr Brush, :ptr GraphicsPath {
        GdipFillPath([this].Graphics.nativeGraphics, brush->nativeBrush, path->nativePath)
    }

    .operator FillClosedCurve :ptr Brush, :ptr PointF, :SINT {
        GdipFillClosedCurve([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3)

    }

    .operator FillClosedCurve :ptr Brush, :ptr PointF, :SINT, :FillMode, :REAL {
        GdipFillClosedCurve2([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4, _5)
    }

    .operator FillClosedCurve :ptr Brush, :ptr Point, :SINT {
          GdipFillClosedCurveI([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3)
    }

    .operator FillClosedCurve :ptr Brush, :ptr Point, :SINT, :FillMode, :REAL {
        GdipFillClosedCurve2I([this].Graphics.nativeGraphics, brush->nativeBrush, _2, _3, _4, _5)
    }

    .operator FillRegion :ptr Brush, :ptr Region {
        GdipFillRegion([this].Graphics.nativeGraphics, brush->nativeBrush, region->nativeRegion)
    }

    .operator DrawString :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :ptr Brush {
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        mov r10,_5
        .if r10
            mov r10,[r10].Format.nativeFormat
        .endif
        mov r11,_5
        .if r11
            mov r11,[r11].Brush.nativeBrush
        .endif
        GdipDrawString([this].Graphics.nativeGraphics, _1, _2, _3, _4, r10, r11)
    }

    .operator DrawString :ptr WCHAR, :SINT, :ptr Font, :ptr PointF, :ptr Brush {

        .new rect:RectF(origin.X, origin.Y, 0.0, 0.0)
        ;font ? font->nativeFont : NULL
        ;brush ? brush->nativeBrush : NULL
        GdipDrawString([this].Graphics.nativeGraphics, _1, _2, _3, &rect, NULL, _4)
    }

    .operator DrawString :ptr WCHAR, :SINT, :ptr Font, :ptr PointF, :ptr StringFormat, :ptr Brush {

        .new rect:RectF(origin.X, origin.Y, 0.0, 0.0)

        GdipDrawString([this].Graphics.nativeGraphics, string, length,\
            font ? font->nativeFont : NULL,\
            &rect,\
            stringFormat ? stringFormat->nativeFormat : NULL,\
            brush ? brush->nativeBrush : NULL )
    }

    .operator MeasureString :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :ptr RectF, :SINT, :ptr SINT {
        GdipMeasureString([this].Graphics.nativeGraphics, string, length,\
            font ? font->nativeFont : NULL,\
            &layoutRect,\
            stringFormat ? stringFormat->nativeFormat : NULL,\
            boundingBox, codepointsFitted, linesFilled)
    }

    .operator MeasureString :ptr WCHAR, :SINT, :ptr Font, :ptr SizeF, :ptr StringFormat, :ptr SizeF, :SINT, :SINT {

        .new layoutRect:RectF(0, 0, layoutRectSize.Width, layoutRectSize.Height)
        .new boundingBox:RectF
        .new status:Status

        .if (size == NULL)

            SetStatus(InvalidParameter)
        .endif
            ;font ? font->nativeFont : NULL,
            ;stringFormat ? stringFormat->nativeFormat : NULL,
            ;size ? &boundingBox : NULL
        GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8)

        .if (size && status == Ok)

            size->Width  = boundingBox.Width;
            size->Height = boundingBox.Height;
        .endif

        mov eax,status
    }

    .operator MeasureString :ptr WCHAR, :SINT, :ptr Font, :ptr PointF, :ptr StringFormat, :ptr RectF {

        .new rect:RectF(origin.X, origin.Y, 0.0, 0.0)

            ;font ? font->nativeFont : NULL,
            ;stringFormat ? stringFormat->nativeFormat : NULL,
        GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, &rect, _4, NULL, NULL)
    }

    .operator MeasureString :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr RectF {
            ;font ? font->nativeFont : NULL,
        GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, _4, NULL, _5, NULL, NULL)
    }

    .operator MeasureString :ptr WCHAR, :SINT, :ptr Font, :ptr PointF, :ptr RectF {

        .new rect:RectF(origin.X, origin.Y, 0.0, 0.0)

        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        GdipMeasureString([this].Graphics.nativeGraphics, _1, _2, _3, &rect, NULL, _4, NULL, NULL)
    }


    .operator MeasureCharacterRanges :ptr WCHAR, :SINT, :ptr Font, :ptr RectF, :ptr StringFormat, :SINT, :ptr Region {

        .repeat

            .if (!_7 || _6 <= 0)

                mov eax,InvalidParameter
                .break
            .endif

            .new status:Status
            .new nativeRegions:ptr GpRegion ;= new GpRegion* [regionCount];

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
            GpFree(nativeRegions)
            mov eax,status
        .until 1
        retm <>eax
    }

    .operator DrawDriverString :ptr UINT16, :SINT, :ptr Font, :ptr Brush, :ptr PointF, :SINT, :ptr Matrix {
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
    }

    .operator MeasureDriverString :ptr UINT16, :SINT, :ptr Font, :ptr PointF, :SINT, :ptr Matrix, :ptr RectF {
        .if _3
            mov _3,[_3].Font.nativeFont
        .endif
        mov r10,_6
        .if r10
            mov r10,[r10].Matrix.nativeMatrix
        .endif
        GdipMeasureDriverString([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5 r10, _7)
    }

    ;; Draw a cached bitmap on this graphics destination offset by
    ;; x, y. Note this will fail with WrongState if the CachedBitmap
    ;; native format differs from this Graphics.

    .operator DrawCachedBitmap :ptr CachedBitmap, :SINT, :SINT {
        GdipDrawCachedBitmap([this].Graphics.nativeGraphics, [_1].CachedBitmap.nativeCachedBitmap, _2, _3)
    }

    .operator DrawImage :ptr Image, :ptr PointF {
        DrawImage(image, point.X, point.Y)
    }

    .operator DrawImage :ptr Image, :REAL, :REAL {
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImage([this].Graphics.nativeGraphics, _1, _2, _3)
    }

    .operator DrawImage :ptr Image, :ptr RectF {
        DrawImage(image, rect.X, rect.Y, rect.Width, rect.Height)
    }

    .operator DrawImage :ptr Image, :REAL, :REAL, :REAL, :REAL {
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImageRect([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5)
    }

    .operator DrawImage :ptr Image, :ptr Point {
        DrawImage(image, point.X, point.Y)
    }

    .operator DrawImage :ptr Image, :SINT, :SINT {
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImageI([this].Graphics.nativeGraphics, _1, _2, _3)
    }

    .operator DrawImage :ptr Image, :ptr Rect {
        DrawImage(image, rect.X, rect.Y, rect.Width, rect.Height)
    }

    .operator DrawImage :ptr Image, :SINT, :SINT, :SINT, :SINT {
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImageRectI([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5)
    }


    .operator DrawImage :ptr Image, :ptr PointF, :SINT {
        .if (_3 != 3 && _3 != 4)
            SetStatus(InvalidParameter)
        .else
            .if _1
                mov _1,[_1].Image.nativeImage
            .endif

            GdipDrawImagePoints([this].Graphics.nativeGraphics, _1, _2, _3)
        .endif
    }

    .operator DrawImage :ptr Image, :ptr Point, :SINT {
        .if (_3 != 3 && _3 != 4)
            SetStatus(InvalidParameter)
        .else
            .if _1
                mov _1,[_1].Image.nativeImage
            .endif
            GdipDrawImagePointsI([this].Graphics.nativeGraphics, _1, _2, _3)
        .endif
    }

    .operator DrawImage :ptr Image, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL, :Unit {
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImagePointRect([this].Graphics.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8)
    }

    .operator DrawImage :ptr Image, :ptr RectF, :REAL, :REAL, :REAL, :REAL, :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        GdipDrawImageRectRect([this].Graphics.nativeGraphics, _1, \
                destRect.X, destRect.Y, destRect.Width, destRect.Height,\
                srcx, srcy, srcwidth, srcheight, srcUnit,\
                imageAttributes ? imageAttributes->nativeImageAttr : NULL,\
                callback, callbackData)
    }

    .operator DrawImage :ptr Image, :ptr PointF, :SINT, :REAL, :REAL, :REAL, :REAL, :Unit, :ptr ImageAttributes, :DrawImageAbort, :ptr {
        ;image ? image->nativeImage : NULL,
        ;imageAttributes ? imageAttributes->nativeImageAttr : NULL,
        GdipDrawImagePointsRect([this].Graphics.nativeGraphics, _1, \
            destPoints, count, srcx, srcy, srcwidth, srcheight, srcUnit,\
            imageAttributes, callback, callbackData)
    }

    .operator DrawImage :ptr Image, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT, :Unit {
        ;image ? image->nativeImage : NULL,
        GdipDrawImagePointRectI([this].Graphics.nativeGraphics, _1,\
            x, y, srcx, srcy, srcwidth, srcheight, srcUnit)
    }

    .operator DrawImage :ptr Image, :ptr Rect, :SINT, :SINT, :SINT, :SINT, :Unit,\
                     :ptr ImageAttributes, :DrawImageAbort, :ptr {
        ;image ? image->nativeImage : NULL,
        ;imageAttributes ? imageAttributes->nativeImageAttr : NULL,
        GdipDrawImageRectRectI([this].Graphics.nativeGraphics, _1,
            destRect.X, destRect.Y, destRect.Width, destRect.Height,\
            srcx, srcy, srcwidth, srcheight, srcUnit,imageAttributes, callback, callbackData)
    }

    .operator DrawImage :ptr Image, :ptr Point, :SINT, :SINT, :SINT, :SINT, :SINT, :Unit,\
                     :ptr ImageAttributes, :DrawImageAbort, :ptr {
        ;image ? image->nativeImage : NULL,
        ;imageAttributes ? imageAttributes->nativeImageAttr : NULL,
        GdipDrawImagePointsRectI([this].Graphics.nativeGraphics, _1,\
            destPoints, count, srcx, srcy, srcwidth, srcheight, srcUnit,\
            imageAttributes, callback, callbackData)
    }

if (GDIPVER GE 0x0110)
    .operator DrawImage :ptr Image, :ptr RectF, :ptr RectF, :Unit, :ptr ImageAttributes {
        ;imageAttributes ? imageAttributes->nativeImageAttr : NULL,
        GdipDrawImageRectRect([this].Graphics.nativeGraphics, image->nativeImage,\
            destRect.X,\
            destRect.Y,\
            destRect.Width,\
            destRect.Height,\
            sourceRect.X,\
            sourceRect.Y,\
            sourceRect.Width,\
            sourceRect.Height,\
            srcUnit,\
            imageAttributes,\
            NULL, NULL)
    }

    .operator DrawImage :ptr Image, :ptr RectF, :ptr Matrix, :ptr Effect, :ptr ImageAttributes, :Unit {
        GdipDrawImageFX([this].Graphics.nativeGraphics, image->nativeImage, sourceRect,\
            xForm ? xForm->nativeMatrix : NULL,\
            effect ? effect->nativeEffect : NULL,\
            imageAttributes ? imageAttributes->nativeImageAttr : NULL, srcUnit )
    }
endif

    ;; The following methods are for playing an EMF+ to a graphics
    ;; via the enumeration interface.  Each record of the EMF+ is
    ;; sent to the callback (along with the callbackData).  Then
    ;; the callback can invoke the Metafile::PlayRecord method
    ;; to play the particular record.

    .operator EnumerateMetafile :ptr Metafile, :ptr PointF, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
           GdipEnumerateMetafileDestPoint([this].Graphics.nativeGraphics, (metafile ? metafile->nativeImage:NULL),\
                    destPoint, callback, callbackData, imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr Point, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        GdipEnumerteMetafileDestPointI([this].Graphics.nativeGraphics,\
                    (metafile ? metafile->nativeImage:NULL),\
                    destPoint,\
                    callback,\
                    callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr Rect, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        GdipEnumerateMetafileDestRect([this].Graphics.nativeGraphics,\
                    (metafile ? metafile->nativeImage:NULL),\
                    destRect,\
                    callback,\
                    callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr Rect, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        GdipEnumerateMetafileDestRectI([this].Graphics.nativeGraphics,\
                    (metafile ? metafile->nativeImage:NULL),\
                    destRect,\
                    callback,\
                    callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr PointF, :SINT, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        GdipEnumerateMetafileDestPoints([this].Graphics.nativeGraphics, (metafile ? metafile->nativeImage:NULL),\
                    destPoints, count, callback, callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr Point, :SINT, :EnumerateMetafileProc, :ptr,:ptr ImageAttributes {
        GdipEnumerateMetafileDestPointsI([this].Graphics.nativeGraphics,(metafile ? metafile->nativeImage:NULL),\
                    destPoints, count, callback, callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr PointF, :ptr RectF, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        GdipEnumerateMetafileSrcRectDestPoint([this].Graphics.nativeGraphics,(metafile ? metafile->nativeImage:NULL),\
                    destPoint, srcRect, srcUnit, callback, callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr Point, :ptr Rect, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        GdipEnumerateMetafileSrcRectDestPointI([this].Graphics.nativeGraphics,\
                    (metafile ? metafile->nativeImage:NULL),\
                    destPoint, srcRect, srcUnit, callback, callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr RectF, :ptr RectF, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        GdipEnumerateMetafileSrcRectDestRect([this].Graphics.nativeGraphics,(metafile ? metafile->nativeImage:NULL),\
                    destRect, srcRect, srcUnit, callback, callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }


    .operator EnumerateMetafile :ptr, :ptr, :ptr, :Unit, :EnumerateMetafileProc, :ptr, :ptr {
        GdipEnumerateMetafileSrcRectDestRectI([this].Graphics.nativeGraphics,\
                    (metafile ? metafile->nativeImage:NULL),\
                    destRect, srcRect, srcUnit, callback, callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr PointF, :SINT, :ptr RectF, :Unit, \
            :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        GdipEnumerateMetafileSrcRectDestPoints([this].Graphics.nativeGraphics,\
                    (metafile ? metafile->nativeImage:NULL),\
                    destPoints, count, srcRect, srcUnit, callback, callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator EnumerateMetafile :ptr Metafile, :ptr Point, :SINT, :ptr Rect, :Unit, :EnumerateMetafileProc, :ptr, :ptr ImageAttributes {
        GdipEnumerateMetafileSrcRectDestPointsI([this].Graphics.nativeGraphics,\
                    (metafile ? metafile->nativeImage:NULL),\
                    destPoints, count, srcRect, srcUnit, callback, callbackData,\
                    imageAttributes ? imageAttributes->nativeImageAttr : NULL)
    }

    .operator SetClip :ptr Graphics, :CombineMode {
        GdipSetClipGraphics([this].Graphics.nativeGraphics, [_1].Graphics.nativeGraphics, _2)
    }

    .operator SetClip :ptr RectF, :CombineMode {
        GdipSetClipRect([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, _2)
    }

    .operator SetClip :ptr Rect, :CombineMode {
        GdipSetClipRectI([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, _2)
    }

    .operator SetClip :ptr GraphicsPath, :CombineMode {
        GdipSetClipPath([this].Graphics.nativeGraphics, path->nativePath, _2)
    }

    .operator SetClip :ptr Region, :CombineMode {
        GdipSetClipRegion([this].Graphics.nativeGraphics, region->nativeRegion, _2)
    }

    ;; This is different than the other SetClip methods because it assumes
    ;; that the HRGN is already in device units, so it doesn't transform
    ;; the coordinates in the HRGN.

    .operator SetClip :HRGN, :CombineMode {
        GdipSetClipHrgn([this].Graphics.nativeGraphics, _1, _2)
    }

    .operator IntersectClip :ptr RectF {
        GdipSetClipRect([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, CombineModeIntersect)
    }

    .operator IntersectClip :ptr Rect {
        GdipSetClipRectI([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, CombineModeIntersect)
    }

    .operator IntersectClip :ptr Region {
        GdipSetClipRegion([this].Graphics.nativeGraphics, region->nativeRegion, CombineModeIntersect)
    }

    .operator ExcludeClip :ptr RectF {
        GdipSetClipRect([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, CombineModeExclude)
    }

    .operator ExcludeClip :ptr Rect {
        GdipSetClipRectI([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, CombineModeExclude)
    }

    .operator ExcludeClip :ptr Region {
        GdipSetClipRegion([this].Graphics.nativeGraphics, region->nativeRegion, CombineModeExclude)
    }

    .operator ResetClip {
        GdipResetClip([this].Graphics.nativeGraphics));
    }

    .operator TranslateClip :REAL, :REAL {
        GdipTranslateClip([this].Graphics.nativeGraphics, _1, _2)
    }

    .operator TranslateClip :SINT,:SINT {
        GdipTranslateClipI([this].Graphics.nativeGraphics, _1, _2)
    }

    .operator GetClip :ptr {
        GdipGetClip([this].Graphics.nativeGraphics, region->nativeRegion)
    }

    .operator GetClipBounds :ptr RectF  {
        GdipGetClipBounds([this].Graphics.nativeGraphics, _1)
    }

    .operator GetClipBounds :ptr Rect {
        GdipGetClipBoundsI([this].Graphics.nativeGraphics, _1)
    }

    .operator IsClipEmpty {

        .new booln:BOOL

        mov booln,FALSE

        GdipIsClipEmpty([this].Graphics.nativeGraphics, &booln)

        mov eax,booln
    }

    .operator GetVisibleClipBounds :ptr RectF {

        GdipGetVisibleClipBounds([this].Graphics.nativeGraphics, _1)
    }

    .operator GetVisibleClipBounds :ptr Rect {
       GdipGetVisibleClipBoundsI([this].Graphics.nativeGraphics, _1)
    }

    .operator IsVisibleClipEmpty {

        .new booln:BOOL

        mov booln,FALSE

        GdipIsVisibleClipEmpty([this].Graphics.nativeGraphics, &booln)

        mov eax,booln
    }

    .operator IsVisible :int_t, :SINT {
        return IsVisible(Point(x,y));
    }

    .operator IsVisible :ptr Point {

        .new booln:BOOL

        mov booln,FALSE

        GdipIsVisiblePointI([this].Graphics.nativeGraphics, point.X, point.Y, &booln)

        mov eax,booln
    }

    .operator IsVisible :int_t, :int_t, :int_t, :int_t {
        return IsVisible(Rect(x, y, width, height));
    }

    .operator IsVisible :ptr Rect {

        .new booln:BOOL

        mov booln,TRUE

        GdipIsVisibleRectI([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, &booln)
        mov eax,booln
    }

    .operator IsVisible :REAL, :REAL {
        IsVisible(PointF(_1, _2))
    }

    .operator IsVisible :ptr PointF {

        .new booln:BOOL

        mov booln,FALSE

        GdipIsVisiblePoint([this].Graphics.nativeGraphics, point.X, point.Y, &booln)

        mov eax,booln
    }

    .operator IsVisible :REAL, :REAL, :REAL, :REAL {
        IsVisible(RectF(_1, _2, _3, _4))
    }

    .operator IsVisible :ptr RectF {

        .new booln:BOOL

        mov booln,TRUE

        GdipIsVisibleRect([this].Graphics.nativeGraphics, rect.X, rect.Y, rect.Width, rect.Height, &booln)
        mov eax,booln
    }

    .operator Save {

        .new gstate:GraphicsState

        GdipSaveGraphics([this].Graphics.nativeGraphics, &gstate)

        mov eax,gstate
    }

    .operator Restore :GraphicsState {
        GdipRestoreGraphics([this].Graphics.nativeGraphics, _1)
    }

    .operator BeginContainer :ptr RectF, :ptr RectF, :Unit {

        .new state:GraphicsContainer

        GdipBeginContainer([this].Graphics.nativeGraphics, _1, _2, _3, &state)

        mov eax,state
    }

    .operator BeginContainer :ptr Rect, :ptr Rect, :Unit {

        .new state:GraphicsContainer

        GdipBeginContainerI([this].Graphics.nativeGraphics, _1, _2, _3, &state)

        mov eax,state
    }

    .operator BeginContainer {

        .new state:GraphicsContainer

        GdipBeginContainer2([this].Graphics.nativeGraphics, &state)

        mov eax,state
    }

    .operator EndContainer :GraphicsContainer {
        GdipEndContainer([this].Graphics.nativeGraphics, _1)
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
