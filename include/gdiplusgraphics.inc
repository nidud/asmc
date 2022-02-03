ifndef _GDIPLUSGRAPHICS_H
define _GDIPLUSGRAPHICS_H
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Graphics(HDC)
; Graphics(HDC, HANDLE)
; Graphics(HWND, BOOL = FALSE)
; Graphics(Image*)
; Graphics(Metafile*)
; Graphics(Graphics*)
;
.template Graphics fastcall

    nativeGraphics  ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    .static Graphics :abs, :abs=<FALSE> {
        mov this.nativeGraphics,NULL
        LOADARGPTRCX(_1)
      ifidn <ptrImage>,typeid(_1)
        GdipGetImageGraphicsContext([rcx].Image.nativeImage, addr this.nativeGraphics)
      elseifidn <ptrMetafile>,typeid(_1)
        GdipGetImageGraphicsContext([rcx].Image.nativeImage, addr this.nativeGraphics)
      elseifidn <ptrHWND__>,typeid(_1)
       if _2
        GdipCreateFromHWNDICM(rcx, addr this.nativeGraphics)
       else
        GdipCreateFromHDC(rcx, addr this.nativeGraphics)
       endif
      elseifidn <ptrGraphics>,typeid(_1)
        mov this.nativeGraphics,rcx
        mov eax,Ok
      else
        GdipCreateFromHDC(rcx, addr this.nativeGraphics)
      endif
        mov this.lastResult,eax
        }

    .static Release {
        GdipDeleteGraphics(this.nativeGraphics)
        }

    .static SetNativeGraphics :ptr GpGraphics {
        mov this.nativeGraphics,_1
        }

    .static SetStatus watcall state:size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static GetNativeGraphics {
        mov rax,this.nativeGraphics
        }

    .static GetNativePen :ptr Pen {
        mov rax,[rcx].Pen.nativePen
        }

    .static Flush intention:abs=<FlushIntentionFlush> {
        GdipFlush(this.nativeGraphics, intention)
        }

    ;;------------------------------------------------------------------------
    ;; GDI Interop methods
    ;;------------------------------------------------------------------------

    ;; Locks the graphics until ReleaseDC is called

    .static GetHDC {
      local hdc
       .new hdc:HDC = NULL
        this.SetStatus(GdipGetDC(this.nativeGraphics, &hdc))
        mov rax,hdc
        }

    .static ReleaseHDC hdc:abs {
        this.SetStatus(GdipReleaseDC(this.nativeGraphics, hdc))
        }

    ;;------------------------------------------------------------------------
    ;; Rendering modes
    ;;------------------------------------------------------------------------

    .static SetRenderingOrigin x:abs, y:abs {
        this.SetStatus(GdipSetRenderingOrigin(this.nativeGraphics, x, y))
        }

    .static GetRenderingOrigin pX:abs, pY:abs {
        this.SetStatus(GdipGetRenderingOrigin(this.nativeGraphics, pX, pY))
        }

    .static SetCompositingMode mode:abs {
        this.SetStatus(GdipSetCompositingMode(this.nativeGraphics, mode))
        }

    .static GetCompositingMode {
        this.SetStatus(GdipGetCompositingMode(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static SetCompositingQuality compositingQuality:abs {
        this.SetStatus(GdipSetCompositingQuality(this.nativeGraphics, compositingQuality))
        }

    .static GetCompositingQuality {
        this.SetStatus(GdipGetCompositingQuality(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static SetTextRenderingHint newMode:abs {
        this.SetStatus(GdipSetTextRenderingHint(this.nativeGraphics, newMode))
        }

    .static GetTextRenderingHint {
        this.SetStatus(GdipGetTextRenderingHint(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static SetTextContrast contrast:abs {
        this.SetStatus(GdipSetTextContrast(this.nativeGraphics, contrast))
        }

    .static GetTextContrast {
        this.SetStatus(GdipGetTextContrast(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetInterpolationMode {
        mov this.scratch,InterpolationModeInvalid
        this.SetStatus(GdipGetInterpolationMode(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static SetInterpolationMode mode:abs {
        this.SetStatus(GdipSetInterpolationMode(this.nativeGraphics, mode))
        }

if (GDIPVER GE 0x0110)
    .static SetAbort pIAbort:abs {
        this.SetStatus(GdipGraphicsSetAbort(this.nativeGraphics, pIAbort))
        }
endif

    .static GetSmoothingMode {
        mov this.scratch,SmoothingModeInvalid
        this.SetStatus(GdipGetSmoothingMode(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static SetSmoothingMode smoothingMode:abs {
        this.SetStatus(GdipSetSmoothingMode(this.nativeGraphics, smoothingMode))
        }

    .static GetPixelOffsetMode {
        mov this.scratch,PixelOffsetModeInvalid
        this.SetStatus(GdipGetPixelOffsetMode(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static SetPixelOffsetMode pixelOffsetMode:abs {
        this.SetStatus(GdipSetPixelOffsetMode(this.nativeGraphics, pixelOffsetMode))
        }

    ;;------------------------------------------------------------------------
    ;; Manipulate current world transform
    ;;------------------------------------------------------------------------

    .static SetTransform matrix:ptr Matrix {
        this.SetStatus(GdipSetWorldTransform(this.nativeGraphics, [matrix].Matrix.nativeMatrix))
        }
    .static ResetTransform {
        this.SetStatus(GdipResetWorldTransform(this.nativeGraphics))
        }
    .static MultiplyTransform :ptr Matrix, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipMultiplyWorldTransform(this.nativeGraphics, [_1].Matrix.nativeMatrix, _2))
        }
    .static TranslateTransform x:abs, y:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipTranslateWorldTransform(this.nativeGraphics, x, y, order))
        }
    .static ScaleTransform x:abs, y:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipScaleWorldTransform(this.nativeGraphics, x, y, order))
        }
    .static RotateTransform angle:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipRotateWorldTransform(this.nativeGraphics, angle, order))
        }
    .static GetTransform :ptr Matrix {
        this.SetStatus(GdipGetWorldTransform(this.nativeGraphics, [_1].Matrix.nativeMatrix))
        }
    .static SetPageUnit unit:abs {
        this.SetStatus(GdipSetPageUnit(this.nativeGraphics, unit))
        }
    .static SetPageScale scale:abs {
        this.SetStatus(GdipSetPageScale(this.nativeGraphics, scale))
        }

    .static GetPageUnit {
        this.SetStatus(GdipGetPageUnit(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }
    .static GetPageScale {
        this.SetStatus(GdipGetPageScale(this.nativeGraphics, addr this.scratch))
        movss xmm0,this.scratch
        }
    .static GetDpiX {
        this.SetStatus(GdipGetDpiX(this.nativeGraphics, addr this.scratch))
        movss xmm0,this.scratch
        }
    .static GetDpiY {
        this.SetStatus(GdipGetDpiY(this.nativeGraphics, addr this.scratch))
        movss xmm0,this.scratch
        }

    .static TransformPoints destSpace:abs, srcSpace:abs, pPoint:abs, count:abs {
      ifidni <ptrPointF>,typeid(pPoint)
        this.SetStatus(GdipTransformPoints(this.nativeGraphics, destSpace, srcSpace, pPointF, count))
      elseifidni <ptrPoint>,typeid(pPoint)
        this.SetStatus(GdipTransformPointsI(this.nativeGraphics, destSpace, srcSpace, pPoint, count))
      else
        .err <pPoint>
      endif
        }

    ;;------------------------------------------------------------------------
    ;; GetNearestColor (for <= 8bpp surfaces).  Note: Alpha is ignored.
    ;;------------------------------------------------------------------------

    .static GetStatus {
        mov eax,this.lastResult
        }
    .static GetNearestColor {
        this.SetStatus(GdipGetNearestColor(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    ; DrawLine(Pen* pen, REAL x1, REAL y1, REAL x2, REAL y2)
    ; DrawLine(Pen* pen, PointF& pt1, PointF& pt2)
    ; DrawLine(Pen* pen, INT x1, INT y1, INT x2, INT y2)
    ; DrawLine(Pen* pen, Point& pt1, Point& pt2)

    .static DrawLine :ptr Pen, :abs, :abs, :abs, :abs {
      ifidn <PointF>,typeid(_2)
        this.SetStatus(GdipDrawLine(this.nativeGraphics,  [_1].Pen.nativePen, _2.X, _2.Y, _3.X, _3.Y))
      elseifidn <Point>,typeid(_2)
        this.SetStatus(GdipDrawLineI(this.nativeGraphics, [_1].Pen.nativePen, _2.X, _2.Y, _3.X, _3.Y))
      elseif GDIType(_2) eq GDI_Real
        this.SetStatus(GdipDrawLine(this.nativeGraphics,  [_1].Pen.nativePen, _2, _3, _4, _5))
      else
        this.SetStatus(GdipDrawLineI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5))
      endif
        }

    ; DrawLines(Pen* pen, PointF* points, INT count)
    ; DrawLines(Pen* pen, Point* points, INT count)

    .static DrawLines :ptr Pen, points:abs, count:abs {
      ifidn <ptrPointF>,typeid(points)
        this.SetStatus(GdipDrawLines(this.nativeGraphics, [_1].Pen.nativePen, points, count))
      elseifidn <ptrPoint>,typeid(points)
        this.SetStatus(GdipDrawLinesI(this.nativeGraphics, [_1].Pen.nativePen, points, count))
      else
        .err <points>
      endif
        }

    ; DrawArc(Pen* pen, REAL x, REAL y, REAL width, REAL height, REAL startAngle, REAL sweepAngle)
    ; DrawArc(Pen* pen, RectF& rect,REAL startAngle, REAL sweepAngle)
    ; DrawArc(Pen* pen, INT x, INT y, INT width, INT height, REAL startAngle, REAL sweepAngle)
    ; DrawArc(Pen* pen, Rect& rect, REAL startAngle, REAL sweepAngle)

    .static DrawArc :ptr Pen, :abs, :abs, :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_2)
        .err <_2>
      elseifidn <ptrRect>,typeid(_2)
        .err <_2>
      elseifidn <RectF>,typeid(_2)
        this.SetStatus(GdipDrawArc(this.nativeGraphics,  [_1].Pen.nativePen, _2.X, _2.Y, _2.Width, _2.Height, _3, _4))
      elseifidn <Rect>,typeid(_2)
        this.SetStatus(GdipDrawArcI(this.nativeGraphics, [_1].Pen.nativePen, _2.X, _2.Y, _2.Width, _2.Height, _3, _4))
      elseif GDIType(_2) eq GDI_Real
        this.SetStatus(GdipDrawArc(this.nativeGraphics,  [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7))
      else
        this.SetStatus(GdipDrawArcI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7))
      endif
        }

    ; DrawBezier(Pen* pen, REAL x1, REAL y1, REAL x2, REAL y2, REAL x3, REAL y3, REAL x4, REAL y4)
    ; DrawBezier(Pen* pen, PointF& pt1, PointF& pt2, PointF& pt3, PointF& pt4)
    ; DrawBezier(Pen* pen, INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)
    ; DrawBezier(Pen* pen, Point& pt1, Point& pt2, Point& pt3, Point& pt4)

    .static DrawBezier :ptr Pen, :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs {
      ifidn <ptrPointF>,typeid(_2)
        .err <_2>
      elseifidn <ptrPoint>,typeid(_2)
        .err <_2>
      elseifidn <PointF>,typeid(_2)
        this.SetStatus(GdipDrawBezier(this.nativeGraphics,  [_1].Pen.nativePen, _2.X, _2.Y, _3.X, _3.Y, _4.X, _4.Y, _5.X, _5.Y))
      elseifidn <Point>,typeid(_2)
        this.SetStatus(GdipDrawBezierI(this.nativeGraphics, [_1].Pen.nativePen, _2.X, _2.Y, _3.X, _3.Y, _4.X, _4.Y, _5.X, _5.Y))
      elseif GDIType(_2) eq GDI_Real
        this.SetStatus(GdipDrawBezier(this.nativeGraphics,  [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7, _8, _9))
      else
        this.SetStatus(GdipDrawBezierI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7, _8, _9))
      endif
        }

    ; DrawBeziers(Pen* pen, PointF* points, INT count)
    ; DrawBeziers(Pen* pen, Point* points, INT count)

    .static DrawBeziers :ptr Pen, :abs, :abs {
      ifidn <ptrPointF>,typeid(_2)
        this.SetStatus(GdipDrawBeziers(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
      elseifidn <ptrPoint>,typeid(_2)
        this.SetStatus(GdipDrawBeziersI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
      else
        .err <_2>
      endif
        }

    ; DrawRectangle(Pen* pen, RectF& rect)
    ; DrawRectangle(Pen* pen, REAL x, REAL y, REAL width, REAL height)
    ; DrawRectangle(Pen* pen, Rect& rect)
    ; DrawRectangle(Pen* pen, INT x, INT y, INT width, INT height)

    .static DrawRectangle :ptr Pen, :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_2)
        .err <_2>
      elseifidn <ptrRect>,typeid(_2)
        .err <_2>
      elseifidn <RectF>,typeid(_2)
        this.SetStatus(GdipDrawRectangle(this.nativeGraphics,  [_1].Pen.nativePen, _2.X, _2.Y, _2.Width, _2.Height))
      elseifidn <Rect>,typeid(_2)
        this.SetStatus(GdipDrawRectangleI(this.nativeGraphics, [_1].Pen.nativePen, _2.X, _2.Y, _2.Width, _2.Height))
      elseif GDIType(_2) eq GDI_Real
        this.SetStatus(GdipDrawRectangle(this.nativeGraphics,  [_1].Pen.nativePen, _2, _3, _4, _5))
      else
        this.SetStatus(GdipDrawRectangleI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5))
      endif
        }

    ; DrawRectangles(Pen* pen, RectF* rects, INT count)
    ; DrawRectangles(Pen* pen, Rect* rects, INT count)

    .static DrawRectangles :ptr Pen, :abs, :abs {
      ifidn <ptrRectF>,typeid(_2)
        this.SetStatus(GdipDrawRectangles(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
      elseifidn <ptrRect>,typeid(_2)
        this.SetStatus(GdipDrawRectanglesI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
      else
        .err <_2>
      endif
        }

    ; DrawEllipse(Pen* pen, RectF& rect)
    ; DrawEllipse(Pen* pen, REAL x, REAL y, REAL width, REAL height)
    ; DrawEllipse(Pen* pen, Rect& rect)
    ; DrawEllipse(Pen* pen, INT x, INT y, INT width, INT height)

    .static DrawEllipse :ptr Pen, :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_2)
        .err <_2>
      elseifidn <ptrRect>,typeid(_2)
        .err <_2>
      elseifidn <RectF>,typeid(_2)
        this.SetStatus(GdipDrawEllipse(this.nativeGraphics,  [_1].Pen.nativePen, _2.X, _2.Y, _2.Width, _2.Height))
      elseifidn <Rect>,typeid(_2)
        this.SetStatus(GdipDrawEllipseI(this.nativeGraphics, [_1].Pen.nativePen, _2.X, _2.Y, _2.Width, _2.Height))
      elseif GDIType(_2) eq GDI_Real
        this.SetStatus(GdipDrawEllipse(this.nativeGraphics,  [_1].Pen.nativePen, _2, _3, _4, _5))
      else
        this.SetStatus(GdipDrawEllipseI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5))
      endif
        }

    ; DrawPie(Pen* pen, RectF& rect, REAL startAngle, REAL sweepAngle)
    ; DrawPie(Pen* pen, REAL x, REAL y, REAL width, REAL height, REAL startAngle, REAL sweepAngle)
    ; DrawPie(Pen* pen, Rect& rect, REAL startAngle, REAL sweepAngle)
    ; DrawPie(Pen* pen, INT x, INT y,INT width, INT height, REAL startAngle, REAL sweepAngle)

    .static DrawPie :ptr Pen, :abs, :abs, :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_2)
        .err <_2>
      elseifidn <ptrRect>,typeid(_2)
        .err <_2>
      elseifidn <RectF>,typeid(_2)
        this.SetStatus(GdipDrawPie(this.nativeGraphics,  [_1].Pen.nativePen, _2.X, _2.Y, _2.Width, _2.Height, _3, _4))
      elseifidn <Rect>,typeid(_2)
        this.SetStatus(GdipDrawPieI(this.nativeGraphics, [_1].Pen.nativePen, _2.X, _2.Y, _2.Width, _2.Height, _3, _4))
      elseif GDIType(_2) eq GDI_Real
        this.SetStatus(GdipDrawPie(this.nativeGraphics,  [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7))
      else
        this.SetStatus(GdipDrawPieI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6, _7))
      endif
        }

    ; DrawPolygon(Pen* pen, PointF* points, INT count)
    ; DrawPolygon(Pen* pen, Point* points, INT count)

    .static DrawPolygon :ptr Pen, :abs, :abs {
      ifidn <ptrPointF>,typeid(_2)
        this.SetStatus(GdipDrawPolygon(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
      elseifidn <ptrPoint>,typeid(_2)
        this.SetStatus(GdipDrawPolygonI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
      else
        .err <_2>
      endif
        }

    .static DrawPath :ptr Pen, :ptr GraphicsPath {
        .if rcx
            mov rcx,[rcx]
        .endif
        .if rdx
            mov rdx,[rdx]
        .endif
        this.SetStatus(GdipDrawPath(this.nativeGraphics, rcx, rdx))
        }

    ; DrawCurve(Pen* pen, PointF* points, INT count)
    ; DrawCurve(Pen* pen, PointF* points, INT count, REAL tension)
    ; DrawCurve(Pen* pen, PointF* points, INT count, INT offset, INT numberOfSegments, REAL tension = 0.5f)
    ; DrawCurve(Pen* pen, Point* points, INT count)
    ; DrawCurve(Pen* pen, Point* points, INT count, REAL tension)
    ; DrawCurve(Pen* pen, Point* points, INT count, INT offset, INT numberOfSegments, REAL tension = 0.5f)

    .static DrawCurve :ptr Pen, :abs, :abs, :abs, :abs, :abs=<0.5> {
      ifidn <ptrPointF>,typeid(_2)
       ifb <_4>
        this.SetStatus(GdipDrawCurve(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
       elseifb <_5>
        this.SetStatus(GdipDrawCurve2(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4))
       else
        this.SetStatus(GdipDrawCurve3(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6))
       endif
      elseifidn <ptrPoint>,typeid(_2)
       ifb <_4>
        this.SetStatus(GdipDrawCurveI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
       elseifb <_5>
        this.SetStatus(GdipDrawCurve2I(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4))
       else
        this.SetStatus(GdipDrawCurve3I(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4, _5, _6))
       endif
      else
        .err <_2>
      endif
        }

    ; DrawClosedCurve(Pen* pen, PointF* points, INT count)
    ; DrawClosedCurve(Pen *pen, PointF* points, INT count, REAL tension)
    ; DrawClosedCurve(Pen* pen, Point* points, INT count)
    ; DrawClosedCurve(Pen *pen, Point* points, INT count, REAL tension)

    .static DrawClosedCurve :ptr Pen, :abs, :abs, :abs {
      ifidn <ptrPointF>,typeid(_2)
       ifb <_4>
        this.SetStatus(GdipDrawClosedCurve(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
       else
        this.SetStatus(GdipDrawClosedCurve2(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4))
       endif
      elseifidn <ptrPoint>,typeid(_2)
       ifb <_4>
        this.SetStatus(GdipDrawClosedCurveI(this.nativeGraphics, [_1].Pen.nativePen, _2, _3))
       else
        this.SetStatus(GdipDrawClosedCurve2I(this.nativeGraphics, [_1].Pen.nativePen, _2, _3, _4))
       endif
      else
        .err <_2>
      endif
        }

    .static Clear color:abs {
        this.SetStatus(GdipGraphicsClear(this.nativeGraphics, color))
        }

    ; FillRectangle(Brush* brush, RectF& rect)
    ; FillRectangle(Brush* brush, REAL x, REAL y, REAL width, REAL height)
    ; FillRectangle(Brush* brush, Rect& rect)
    ; FillRectangle(Brush* brush, INT x, INT y, INT width, INT height)

    .static FillRectangle :ptr Brush, :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_2)
        .err <_2>
      elseifidn <ptrRect>,typeid(_2)
        .err <_2>
      elseifidn <RectF>,typeid(_2)
        this.SetStatus(GdipFillRectangle(this.nativeGraphics,  [_1].Brush.nativeBrush, _2.X, _2.Y, _2.Width, _2.Height))
      elseifidn <Rect>,typeid(_2)
        this.SetStatus(GdipFillRectangleI(this.nativeGraphics, [_1].Brush.nativeBrush, _2.X, _2.Y, _2.Width, _2.Height))
      elseif GDIType(_2) eq GDI_Real
        this.SetStatus(GdipFillRectangle(this.nativeGraphics,  [_1].Brush.nativeBrush, _2, _3, _4, _5))
      else
        this.SetStatus(GdipFillRectangleI(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5))
      endif
        }

    ; FillRectangles(Brush* brush, RectF* rects, INT count)
    ; FillRectangles(Brush* brush, Rect* rects, INT count)

    .static FillRectangles :ptr Brush, :abs, :abs {
      ifidn <ptrRectF>,typeid(_2)
        this.SetStatus(GdipFillRectangles(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3))
      elseifidn <ptrRect>,typeid(_2)
        this.SetStatus(GdipFillRectanglesI(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3))
      else
        .err <_2>
      endif
        }

    ; FillPolygon(Brush* brush, PointF* points, INT count)
    ; FillPolygon(Brush* brush, PointF* points, INT count, FillMode fillMode)
    ; FillPolygon(Brush* brush, Point* points, INT count)
    ; FillPolygon(Brush* brush, Point* points, INT count, FillMode fillMode)

    .static FillPolygon :ptr Brush, :abs, :abs, :abs {
      ifidn <ptrPointF>,typeid(_2)
       ifb <_4>
        this.SetStatus(GdipFillPolygon(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, FillModeAlternate))
       else
        this.SetStatus(GdipFillPolygon(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4))
       endif
      elseifidn <ptrPoint>,typeid(_2)
       ifb <_4>
        this.SetStatus(GdipFillPolygonI(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, FillModeAlternate))
       else
        this.SetStatus(GdipFillPolygonI(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4))
       endif
      else
        .err <_2>
      endif
        }

    ; FillEllipse(Brush* brush, RectF& rect)
    ; FillEllipse(Brush* brush, REAL x, REAL y, REAL width, REAL height)
    ; FillEllipse(Brush* brush, Rect& rect)
    ; FillEllipse(Brush* brush, INT x, INT y, INT width, INT height)

    .static FillEllipse :ptr Brush, :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_2)
        .err <_2>
      elseifidn <ptrRect>,typeid(_2)
        .err <_2>
      elseifidn <RectF>,typeid(_2)
        this.SetStatus(GdipFillEllipse(this.nativeGraphics,  [_1].Brush.nativeBrush, _2.X, _2.Y, _2.Width, _2.Height))
      elseifidn <Rect>,typeid(_2)
        this.SetStatus(GdipFillEllipseI(this.nativeGraphics, [_1].Brush.nativeBrush, _2.X, _2.Y, _2.Width, _2.Height))
      elseif GDIType(_2) eq GDI_Real
        this.SetStatus(GdipFillEllipse(this.nativeGraphics,  [_1].Brush.nativeBrush, _2, _3, _4, _5))
      else
        this.SetStatus(GdipFillEllipseI(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5))
      endif
        }

    ; FillPie(Brush* brush, RectF& rect, REAL startAngle, REAL sweepAngle)
    ; FillPie(Brush* brush, REAL x, REAL y, REAL width, REAL height, REAL startAngle, REAL sweepAngle)
    ; FillPie(Brush* brush, Rect& rect, REAL startAngle, REAL sweepAngle)
    ; FillPie(Brush* brush, INT x, INT y, INT width, INT height, REAL startAngle, REAL sweepAngle)

    .static FillPie :ptr Brush, :abs, :abs, :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_2)
        .err <_2>
      elseifidn <ptrRect>,typeid(_2)
        .err <_2>
      elseifidn <RectF>,typeid(_2)
        this.SetStatus(GdipFillPie(this.nativeGraphics,  [_1].Brush.nativeBrush, _2.X, _2.Y, _2.Width, _2.Height, _3, _4))
      elseifidn <Rect>,typeid(_2)
        this.SetStatus(GdipFillPieI(this.nativeGraphics, [_1].Brush.nativeBrush, _2.X, _2.Y, _2.Width, _2.Height, _3, _4))
      elseif GDIType(_2) eq GDI_Real
        this.SetStatus(GdipFillPie(this.nativeGraphics,  [_1].Brush.nativeBrush, _2, _3, _4, _5, _6, _7))
      else
        this.SetStatus(GdipFillPieI(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5, _6, _7))
      endif
        }

    .static FillPath :ptr Brush, :ptr GraphicsPath {
        this.SetStatus(GdipFillPath(this.nativeGraphics, [_1].Brush.nativeBrush, [_2].GraphicsPath.nativePath))
        }

    ; FillClosedCurve(Brush* brush, PointF* points, INT count)
    ; FillClosedCurve(Brush* brush, PointF* points, INT count, FillMode fillMode, REAL tension = 0.5f)
    ; FillClosedCurve(Brush* brush, Point* points, INT count)
    ; FillClosedCurve(Brush* brush, Point* points, INT count, FillMode fillMode, REAL tension = 0.5f)

    .static FillClosedCurve :ptr Brush, :abs, :abs, :abs, :abs=<0.5> {
      ifidn <ptrPointF>,typeid(_2)
       ifb <_4>
        this.SetStatus(GdipFillClosedCurve(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3))
       else
        this.SetStatus(GdipFillClosedCurve2(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5))
       endif
      elseifidn <ptrPoint>,typeid(_2)
       ifb <_4>
        this.SetStatus(GdipFillClosedCurveI(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3))
       else
        this.SetStatus(GdipFillClosedCurve2I(this.nativeGraphics, [_1].Brush.nativeBrush, _2, _3, _4, _5))
       endif
      else
        .err <_2>
      endif
        }

    .static FillRegion :ptr Brush, :ptr Region {
        this.SetStatus(GdipFillRegion(this.nativeGraphics, [_1].Brush.nativeBrush, [_2].Region.nativeRegion))
        }

    ; DrawString(WCHAR *string, INT length, Font *font, RectF &layoutRect, StringFormat *stringFormat, Brush *brush)
    ; DrawString(WCHAR *string, INT length, Font *font, PointF &origin, Brush *brush)
    ; DrawString(WCHAR *string, INT length, Font *font, PointF &origin, StringFormat *stringFormat, Brush *brush)

    .static DrawString :abs, :abs, :abs, :abs, :abs, :abs {
      local rc
        .if LOADARGPTRCX(_3)
            mov rcx,[rcx].Font.nativeFont
        .endif
        .if LOADARGPTRDX(_5)
            mov rdx,[rdx].StringFormat.nativeFormat
        .endif
      ifidn <RectF>,typeid(_4)
        .if LOADARGPTRAX(_6)
            mov rax,[rax].Brush.nativeBrush
        .endif
        this.SetStatus(GdipDrawString(this.nativeGraphics, _1, _2, rcx, addr _4, rdx, rax))
      elseifidn <PointF>,typeid(_4)
       .new rc:RectF = { _4.X, _4.Y, 0.0, 0.0 }
       ifb <_6>
        this.SetStatus(GdipDrawString(this.nativeGraphics, _1, _2, rcx, addr rc, NULL, rdx))
       else
        .if LOADARGPTRAX(_6)
            mov rax,[rax].Brush.nativeBrush
        .endif
        this.SetStatus(GdipDrawString(this.nativeGraphics, _1, _2, rcx, addr rc, rdx, rax))
       endif
      else
        .err <_4>
      endif
        }

    ; MeasureString(WCHAR *, INT, Font *, RectF&,  RectF *)
    ; MeasureString(WCHAR *, INT, Font *, RectF&,  StringFormat *, RectF *, INT* = 0, INT* = 0)
    ; MeasureString(WCHAR *, INT, Font *, SizeF&,  StringFormat *, SizeF *, INT * = 0, INT * = 0)
    ; MeasureString(WCHAR *, INT, Font *, PointF&, RectF *)
    ; MeasureString(WCHAR *, INT, Font *, PointF&, StringFormat *, RectF *)

    .static MeasureString :abs, :abs, :abs, :abs, :abs, :abs, :abs=<NULL>, :abs=<NULL> {
      local layoutRect, boundingBox
        .if LOADARGPTRCX(_3)
            mov rcx,[rcx].Font.nativeFont
        .endif
      ifidn <ptrRectF>,typeid(_4)
        .err <_4>
      elseifidn <ptrPointF>,typeid(_4)
        .err <_4>
      elseifidn <ptrSizeF>,typeid(_4)
        .err <_4>
      elseifidn <RectF>,typeid(_4)
       ifb <_6>
        GdipMeasureString(this.nativeGraphics, _1, _2, rcx, addr _4, NULL, _5, NULL, NULL)
       else
        .if LOADARGPTRDX(_5)
            mov rdx,[rdx].StringFormat.nativeFormat
        .endif
        GdipMeasureString(this.nativeGraphics, _1, _2, rcx, addr _4, rdx, _6, _7, _8)
       endif
      elseifidn <SizeF>,typeid(_4)
        .new layoutRect:RectF = { 0.0, 0.0, _4.Width, _4.Height }
        .new boundingBox:RectF
        .if LOADARGPTRDX(_5)
            mov rdx,[rdx].StringFormat.nativeFormat
        .endif
        .if LOADARGPTRAX(_6)
            this.SetStatus(GdipMeasureString(this.nativeGraphics, _1, _2, rcx, addr layoutRect, rdx, addr boundingBox, _7, _8))
            .if ( eax == Ok )
                LOADARGPTRCX(_6)
                mov [rcx].SizeF.Width,boundingBox.Width
                mov [rcx].SizeF.Height,boundingBox.Height
            .endif
            this.GetStatus()
        .endif
      elseifidn <PointF>,typeid(_4)
       .new layoutRect:RectF = { _4.X, _4.Y, 0.0, 0.0 }
       ifb <_6>
        this.SetStatus(GdipMeasureString(this.nativeGraphics, _1, _2, rcx, addr layoutRect, NULL, _5, NULL, NULL))
       else
        .if LOADARGPTRDX(_5)
            mov rdx,[rdx].StringFormat.nativeFormat
        .endif
        this.SetStatus(GdipMeasureString(this.nativeGraphics, _1, _2, rcx, addr layoutRect, rdx, _6, NULL, NULL))
       endif
      endif
        }

    .static MeasureCharacterRanges :abs, :abs, :abs, :abs, :abs, :abs, :abs {
      local p
       .new p:ptr = rbx
        mov eax,_6
        imul ecx,eax,sizeof(p)
        mov rbx,GdipAlloc(rcx)
        LOADARGPTRDX(_7)
        .for ( ecx = 0 : ecx < _6 : ecx++, rdx += Region )
            mov [rbx+rcx*size_t],[rdx].Region.nativeRegion
        .endf
        .if LOADARGPTRCX(_3)
            mov rcx,[rcx].Font.nativeFont
        .endif
        .if LOADARGPTRDX(_5)
            mov rdx,[rdx].StringFormat.nativeFormat
        .endif
        this.SetStatus(GdipMeasureCharacterRanges(this.nativeGraphics, _1, _2, rcx, addr _4, rdx, _6, rbx))
        GdipFree(rbx)
        mov rbx,p
        mov eax,this.lastResult
        }

    .static DrawDriverString text:abs, length:abs, font:abs, brush:abs, positions:abs, flags:abs, matrix:abs {
        .if LOADARGPTRCX(font)
            mov rcx,[rcx].Font.nativeFont
        .endif
        .if LOADARGPTRDX(brush)
            mov rdx,[rdx].Brush.nativeBrush
        .endif
        .if LOADARGPTRAX(matrix)
            mov rax,[rax].Matrix.nativeMatrix
        .endif
        this.SetStatus(GdipDrawDriverString(this.nativeGraphics, text, length, rcx, rdx, positions, flags, rax))
        }

    .static MeasureDriverString :abs, :abs, :abs, :abs, :abs, :abs, :abs {
        .if LOADARGPTRCX(_3)
            mov rcx,[rcx].Font.nativeFont
        .endif
        .if LOADARGPTRDX(_6)
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        this.SetStatus(GdipMeasureDriverString(this.nativeGraphics, _1, _2, rcx, _4, _5, rdx, _7))
        }

    ;; Draw a cached bitmap on this graphics destination offset by
    ;; x, y. Note this will fail with WrongState if the CachedBitmap
    ;; native format differs from this Graphics.

    .static DrawCachedBitmap :ptr CachedBitmap, x:abs, y:abs {
        this.SetStatus(GdipDrawCachedBitmap(this.nativeGraphics, [rcx].CachedBitmap.nativeImage, x, y))
        }

    ; DrawImage(Image*, PointF&)
    ; DrawImage(Image*, REAL, REAL)
    ; DrawImage(Image*, RectF&)
    ; DrawImage(Image*, REAL, REAL, REAL, REAL)
    ; DrawImage(Image*, Point&)
    ; DrawImage(Image*, INT, INT)
    ; DrawImage(Image*, Rect&)
    ; DrawImage(Image*, INT, INT, INT, INT)
    ; DrawImage(Image*, PointF*, INT)
    ; DrawImage(Image*, Point*, INT)
    ; DrawImage(Image*, REAL, REAL, REAL, REAL, REAL, REAL, Unit)
    ; DrawImage(Image*, RectF&, REAL, REAL, REAL, REAL, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)
    ; DrawImage(Image*, PointF*, INT, REAL, REAL, REAL, REAL, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)
    ; DrawImage(Image*, INT, INT, INT, INT, INT, INT, Unit)
    ; DrawImage(Image*, Rect&, INT, INT, INT, INT, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)
    ; DrawImage(Image*, Point*, INT, INT, INT, INT, INT, Unit, ImageAttributes* = NULL, DrawImageAbort = NULL, VOID* = NULL)
  if (GDIPVER GE 0x0110)
    ; DrawImage(Image*, RectF&, RectF&, Unit, ImageAttributes* = NULL)
    ; DrawImage(Image*, RectF*, Matrix*, Effect*, ImageAttributes*, Unit)
  endif

    .static DrawImage :ptr Image, :abs, :abs, :abs, :abs=<NULL>, :abs, :abs, :abs=<NULL>, :abs=<NULL>, :abs=<NULL>, :abs=<NULL> {
      local type,pImage
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
        type = GDIType(_2)
      if type eq GDI_PointF
        GdipDrawImage(this.nativeGraphics, _1, _2.X, _2.Y)
      elseif type eq GDI_Point
        GdipDrawImageI(this.nativeGraphics, _1, _2.X, _2.Y)
      elseif type eq GDI_RectF
       ifb <_3>
        GdipDrawImageRect(this.nativeGraphics, _1, _2.X, _2.Y, _2.Width, _2.Height)
       elseifb <_6>
        if (GDIPVER GE 0x0110)
            .if LOADARGPTRDX(_5)
                mov rdx,[rdx].ImageAttributes.nativeImageAttr
            .endif
            GdipDrawImageRectRect(this.nativeGraphics, _1, _2.X, _2.Y, _2.Width, _2.Height, _3.X, _3.Y, _3.Width, _3.Height, _4, rdx, NULL, NULL)
        else
            .err <GDIPVER lt 0x0110>
        endif
       else
        .if LOADARGPTRDX(_8)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRect(this.nativeGraphics, _1, _2.X, _2.Y, _2.Width, _2.Height, _3, _4, _5, _6, _7, rdx, _9, _10)
       endif
      elseif type eq GDI_Rect
       ifb <_3>
        GdipDrawImageRectI(this.nativeGraphics, _1, _2.X, _2.Y, _2.Width, _2.Height)
       else
        .if LOADARGPTRDX(_8)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageRectRectI(this.nativeGraphics, _1, _2.X, _2.Y, _2.Width, _2.Height, _3, _4, _5, _6, _7, rdx, _9, _10)
       endif
      elseif type eq GDI_PPointF
       ifb <_4>
        GdipDrawImagePoints(this.nativeGraphics, _1, _2, _3)
       else
        .if LOADARGPTRDX(_9)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImagePointsRect(this.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8, rdx, _10, _11)
       endif
      elseif type eq GDI_PPoint
       ifb <_4>
        GdipDrawImagePointsI(this.nativeGraphics, _1, _2, _3)
       else
        .if LOADARGPTRDX(_9)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImagePointsRectI(this.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8, rdx, _10, _11)
       endif
      elseif type eq GDI_Int
       ifb <_4>
        GdipDrawImageI(this.nativeGraphics, _1, _2, _3)
       elseifb <_6>
        GdipDrawImageRectI(this.nativeGraphics, _1, _2, _3, _4, _5)
       else
        GdipDrawImagePointRectI(this.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8)
       endif
      elseif type eq GDI_Real
       ifb <_4>
        GdipDrawImage(this.nativeGraphics, _1, _2, _3)
       elseifb <_6>
        GdipDrawImageRect(this.nativeGraphics, _1, _2, _3, _4, _5)
       else
        GdipDrawImagePointRect(this.nativeGraphics, _1, _2, _3, _4, _5, _6, _7, _8)
       endif
      elseif type eq GDI_PRectF
       if (GDIPVER GE 0x0110)
        .new pImage:ptr Image = _1
        .if LOADARGPTRCX(_3)
            mov rcx,[rcx].Matrix.nativeMatrix
        .endif
        .if LOADARGPTRDX(_4)
            mov rdx,[rdx].Effect.nativeEffect
        .endif
        .if LOADARGPTRAX(_5)
            mov rax,[rax].ImageAttributes.nativeImageAttr
        .endif
        GdipDrawImageFX(this.nativeGraphics, pImage, _2, rcx, rdx, rax, _6)
       endif
      endif
      this.SetStatus()
      }

    ;; The following methods are for playing an EMF+ to a graphics
    ;; via the enumeration interface.  Each record of the EMF+ is
    ;; sent to the callback (along with the callbackData).  Then
    ;; the callback can invoke the Metafile::PlayRecord method
    ;; to play the particular record.

    ; EnumerateMetafile(Metafile*, PointF&, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, Point&, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, RectF&, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, Rect&, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, PointF*, INT, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, Point*, INT, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, PointF&, RectF&, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, Point&, Rect&, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, RectF&, RectF&, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, Rect&, Rect&, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, PointF*, INT, RectF&, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)
    ; EnumerateMetafile(Metafile*, Point*, INT, Rect&, Unit, EnumerateMetafileProc, VOID* = NULL, ImageAttributes* = NULL)

    .static EnumerateMetafile :ptr Image, :abs, :abs, :abs=<NULL>, :abs=<NULL>, :abs, :abs=<NULL>, :abs=<NULL> {
      local type
       type = GDIType(_2)
        .if _1
            mov _1,[_1].Image.nativeImage
        .endif
      if type eq GDI_RectF
       ifdif typeid(_3),<RectF>
        .if LOADARGPTRDX(_5)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestRect(this.nativeGraphics, _1, addr _2, _3, _4, rdx)
       else
        .if LOADARGPTRDX(_7)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestRect(this.nativeGraphics, _1, addr _2, addr _3, _4, _5, _6, rdx)
       endif
      elseif type eq GDI_Rect
       ifdif typeid(_3),<Rect>
        .if LOADARGPTRDX(_5)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestRectI(this.nativeGraphics, _1, addr _2, _3, _4, rdx)
       else
        .if LOADARGPTRDX(_7)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestRectI(this.nativeGraphics, _1, addr _2, addr _3, _4, _5, _6, rdx)
       endif
      elseif type eq GDI_PointF
       ifdif typeid(_3),<RectF>
        .if LOADARGPTRDX(_5)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPoint(this.nativeGraphics, _1, addr _2, _3, _4, rdx)
       else
        .if LOADARGPTRDX(_7)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPoint(this.nativeGraphics, _1, addr _2, addr _3, _4, _5, _6, rdx)
       endif
      elseif type eq GDI_Point
       ifdif typeid(_3),<Rect>
        .if LOADARGPTRDX(_5)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPointI(this.nativeGraphics, _1, addr _2, _3, _4, rdx)
       else
        .if LOADARGPTRDX(_7)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPointI(this.nativeGraphics, _1, addr _2, addr _3, _4, _5, _6, rdx)
       endif
      elseif type eq GDI_PPointF
       ifdif typeid(_4),<RectF>
        .if LOADARGPTRDX(_6)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPoints(this.nativeGraphics, _1, _2, _3, _4, _5, rdx)
       else
        .if LOADARGPTRDX(_8)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPoints(this.nativeGraphics, _1, _2, addr _3, _4, _5, _6, _7, rdx)
       endif
      elseif type eq GDI_PPoint
       ifdif typeid(_4),<Rect>
        .if LOADARGPTRDX(_6)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileDestPointsI(this.nativeGraphics, _1, _2, _3, _4, _5, rdx)
       else
        .if LOADARGPTRDX(_8)
            mov rdx,[rdx].ImageAttributes.nativeImageAttr
        .endif
        GdipEnumerateMetafileSrcRectDestPointsI(this.nativeGraphics, _1, _2, addr _3, _4, _5, _6, _7, rdx)
       endif
      endif
        this.SetStatus()
        }

    ; SetClip(Graphics* g, CombineMode combineMode = CombineModeReplace)
    ; SetClip(RectF& rect, CombineMode combineMode = CombineModeReplace)
    ; SetClip(Rect& rect, CombineMode combineMode = CombineModeReplace)
    ; SetClip(GraphicsPath* path, CombineMode combineMode = CombineModeReplace)
    ; SetClip(Region* region, CombineMode combineMode = CombineModeReplace)
    ; SetClip(HRGN hRgn, CombineMode combineMode = CombineModeReplace)

    .static SetClip :abs, combineMode:abs=<CombineModeReplace> {
      ifidn <Rect>,typeid(_1)
        this.SetStatus(GdipSetClipRectI(this.nativeGraphics, _1.X, _1.Y, _1.Width, _1.Height, combineMode))
      elseifidn <RectF>,typeid(_1)
        this.SetStatus(GdipSetClipRect(this.nativeGraphics, _1.X, _1.Y, _1.Width, _1.Height, combineMode))
      elseifidn <ptrHRGN__>,typeid(_1)
        ;; This is different than the other SetClip methods because it assumes
        ;; that the HRGN is already in device units, so it doesn't transform
        ;; the coordinates in the HRGN.
        this.SetStatus(GdipSetClipHrgn(this.nativeGraphics, _1, combineMode))
      else
       LOADARGPTRCX(_1)
       ifidn <ptrRegion>,typeid(_1)
        this.SetStatus(GdipSetClipRegion(this.nativeGraphics, [rcx].Region.nativeRegion, combineMode))
       elseifidn <ptrGraphicsPath>,typeid(_1)
        this.SetStatus(GdipSetClipPath(this.nativeGraphics, [rcx].GraphicsPath.nativePath, combineMode))
       elseifidn <ptrGraphics>,typeid(_1)
        this.SetStatus(GdipSetClipGraphics(this.nativeGraphics, [rcx].Graphics.nativeGraphics, combineMode))
       endif
      endif
        }

    ; IntersectClip(RectF& rect)
    ; IntersectClip(Rect& rect)
    ; IntersectClip(Region* region)

    .static IntersectClip :abs {
      ifidn <RectF>,typeid(_1)
        this.SetStatus(GdipSetClipRect(this.nativeGraphics, _1.X, _1.Y, _1.Width, _1.Height, CombineModeIntersect))
      elseifidn <Rect>,typeid(_1)
        this.SetStatus(GdipSetClipRectI(this.nativeGraphics, _1.X, _1.Y, _1.Width, _1.Height, CombineModeIntersect))
      elseifidn <ptrRegion>,typeid(_1)
        LOADARGPTRCX(_1)
        this.SetStatus(GdipSetClipRegion(this.nativeGraphics, [rcx].Region.nativeRegion, CombineModeIntersect))
      else
        .err <_1>
      endif
        }

    ; ExcludeClip(RectF& rect)
    ; ExcludeClip(Rect& rect)
    ; ExcludeClip(Region* region)

    .static ExcludeClip :abs {
      ifidn <RectF>,typeid(_1)
        this.SetStatus(GdipSetClipRect(this.nativeGraphics, _1.X, _1.Y, _1.Width, _1.Height, CombineModeExclude))
      elseifidn <Rect>,typeid(_1)
        this.SetStatus(GdipSetClipRectI(this.nativeGraphics, _1.X, _1.Y, _1.Width, _1.Height, CombineModeExclude))
      elseifidn <ptrRegion>,typeid(_1)
        LOADARGPTRCX(_1)
        this.SetStatus(GdipSetClipRegion(this.nativeGraphics, [rcx].Region.nativeRegion, CombineModeExclude))
      else
        .err <_1>
      endif
        }

    .static ResetClip {
        this.SetStatus(GdipResetClip(this.nativeGraphics))
        }

    ; TranslateClip(REAL dx, REAL dy)
    ; TranslateClip(INT dx, INT dy)

    .static TranslateClip x:abs, y:abs {
      if GDIType(x) eq GDI_Real
        this.SetStatus(GdipTranslateClip(this.nativeGraphics, x, y))
      else
        this.SetStatus(GdipTranslateClipI(this.nativeGraphics, x, y))
      endif
        }

    .static GetClip :ptr Region {
        this.SetStatus(GdipGetClip(this.nativeGraphics, [_1].Region.nativeRegion))
        }

    ; GetClipBounds(RectF* rect)
    ; GetClipBounds(Rect* rect)

    .static GetClipBounds :abs {
      ifidn <ptrRectF>,typeid(_1)
        this.SetStatus(GdipGetClipBounds(this.nativeGraphics, _1))
      elseifidn <ptrRect>,typeid(_1)
        this.SetStatus(GdipGetClipBoundsI(this.nativeGraphics, _1))
      else
        .err <_1>
      endif
        }

    .static IsClipEmpty {
        mov this.scratch,FALSE
        this.SetStatus(GdipIsClipEmpty(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetVisibleClipBounds :abs {
      ifidn <ptrRectF>,typeid(_1)
        this.SetStatus(GdipGetVisibleClipBounds(this.nativeGraphics, _1))
      elseifidn <ptrRect>,typeid(_1)
        this.SetStatus(GdipGetVisibleClipBoundsI(this.nativeGraphics, _1))
      else
        .err <_1>
      endif
        }

    .static IsVisibleClipEmpty {
        mov this.scratch,FALSE
        this.SetStatus(GdipIsVisibleClipEmpty(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    ; IsVisible(REAL x, REAL y)
    ; IsVisible(REAL x, REAL y, REAL width, REAL height)
    ; IsVisible(PointF& point)
    ; IsVisible(RectF& rect)
    ; IsVisible(INT x, INT y)
    ; IsVisible(INT x, INT y, INT width, INT height)
    ; IsVisible(Point& point)
    ; IsVisible(Rect& rect)

    .static IsVisible :abs, :abs, :abs, :abs {
        mov this.scratch,FALSE
      ifidn <RectF>,typeid(_1)
        this.SetStatus(GdipIsVisibleRect(this.nativeGraphics, _1.X, _1.Y, _1.Width, _1.Height, addr this.scratch))
      elseifidn <Rect>,typeid(_1)
        this.SetStatus(GdipIsVisibleRectI(this.nativeGraphics, _1.X, _1.Y, _1.Width, _1.Height, addr this.scratch))
      elseifidn <PointF>,typeid(_1)
        this.SetStatus(GdipIsVisiblePoint(this.nativeGraphics, _1.X, _1.Y, addr this.scratch))
      elseifidn <Point>,typeid(_1)
        this.SetStatus(GdipIsVisiblePointI(this.nativeGraphics, _1.X, _1.Y, addr this.scratch))
      elseif GDIType(_1) eq GDI_Real
       ifb <_3>
        this.SetStatus(GdipIsVisiblePoint(this.nativeGraphics, _1, _2, addr this.scratch))
       else
        this.SetStatus(GdipIsVisibleRect(this.nativeGraphics, _1, _2, _3, _4, addr this.scratch))
       endif
      else
       ifb <_3>
        this.SetStatus(GdipIsVisiblePointI(this.nativeGraphics, _1, _2, addr this.scratch))
       else
        this.SetStatus(GdipIsVisibleRectI(this.nativeGraphics, _1, _2, _3, _4, addr this.scratch))
       endif
      endif
        mov eax,this.scratch
        }

    .static Save {
        this.SetStatus(GdipSaveGraphics(this.nativeGraphics, addr this.scratch))
        mov eax,this.scratch
        }

    .static Restore :abs {
        this.SetStatus(GdipRestoreGraphics(this.nativeGraphics, _1))
        }

    ; BeginContainer(RectF &dstrect, RectF &srcrect, Unit unit)
    ; BeginContainer(Rect &dstrect, Rect &srcrect, Unit unit)
    ; BeginContainer()

    .static BeginContainer :abs, :abs, :abs {
      ifb <_1>
        this.SetStatus(GdipBeginContainer2(this.nativeGraphics, addr this.scratch))
      elseifidn <RectF>,typeid(_1)
        this.SetStatus(GdipBeginContainer(this.nativeGraphics, addr _1, addr _2, _3, addr this.scratch))
      elseifidn <Rect>,typeid(_1)
        this.SetStatus(GdipBeginContainerI(this.nativeGraphics, addr _1, addr _2, _3, addr this.scratch))
      else
        .err <_1>
      endif
        mov eax,this.scratch
        }

    .static EndContainer state:abs {
        this.SetStatus(GdipEndContainer(this.nativeGraphics, state))
        }

    ;; Only valid when recording metafiles.

    .static AddMetafileComment data:abs, sizeData:abs {
        this.SetStatus(GdipComment(this.nativeGraphics, data, sizeData))
        }

    .static GetHalftonePalette {
        GdipCreateHalftonePalette()
        }

    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }

    .ends
    GpGraphics typedef Graphics

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;----------------------------------------------------------------------------
;; Implementation of GraphicsPath methods that use Graphics
;;----------------------------------------------------------------------------

;; The GetBounds rectangle may not be the tightest bounds.
if 0
GraphicsPath::GetBounds2 proto :ptr RectF, :ptr Matrix, :ptr Pen
GraphicsPath::GetBounds1 proto :Rect, :ptr Matrix, :ptr Pen
GraphicsPath::IsVisible2 proto :REAL, :REAL, :ptr Graphics
GraphicsPath::IsVisible1 proto :SINT, :SINT, :ptr Graphics
GraphicsPath::IsOutlineVisible2 proto :REAL, :REAL, :ptr Pen, :ptr Graphics
GraphicsPath::IsOutlineVisible1 proto :SINT, :SINT, :ptr Pen, :ptr Graphics
endif
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
