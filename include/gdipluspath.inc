ifndef _GDIPLUSPATH_H
define _GDIPLUSPATH_H
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

; GraphicsPath(FillMode fillMode = FillModeAlternate)
; GraphicsPath(PointF* points, BYTE* types, INT count,FillMode fillMode = FillModeAlternate)
; GraphicsPath(Point* points, BYTE* types, INT count, FillMode fillMode = FillModeAlternate)

.template GraphicsPath fastcall

    nativePath  ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .static GraphicsPath points:abs=<FillModeAlternate>, types:abs, count:abs, fillMode:abs=<FillModeAlternate> {
      ifb <types>
        GdipCreatePath(points, addr this)
      elseifidn <ptrPointF>,typeid(_1)
        GdipCreatePath2(points, types, count, fillMode, addr this)
      elseifidn <ptrPoint>,typeid(_1)
        GdipCreatePath2I(points, types, count, fillMode, addr this)
      endif
        mov this.lastResult,eax
        }

    .static Release {
        GdipDeletePath(this.nativePath)
        }

    .static SetNativePath :ptr GraphicsPath {
        mov this.nativePath,_1
        }

    .static SetStatus watcall state:size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    ;; Reset the path object to empty (and fill mode to FillModeAlternate)

    .static Reset {
        this.SetStatus(GdipResetPath(this.nativePath))
        }

    .static GetFillMode {
        mov this.scratch,FillModeAlternate
        this.SetStatus(GdipGetPathFillMode(this.nativePath, addr this.scratch))
        mov eax,this.scratch
        }

    .static SetFillMode fillmode:abs {
        this.SetStatus(GdipSetPathFillMode(this.nativePath, fillmode))
        }

    .static GetPathData :ptr PathData {
      local count,pathdata
       .new count:SINT
       .new pathdata:ptr PathData = rdi
        mov rdi,_1
        mov count,this.GetPointCount()

        .repeat

            .if ( ( count <= 0 ) || ( [rdi].PathData.Count > 0 && [rdi].PathData.Count < count ) )

                mov [rdi].PathData.Count,0
                .if ([rdi].PathData.Points)
                    GdipFree([rdi].PathData.Points)
                    mov [rdi].PathData.Points,NULL
                .endif
                .if ( [rdi].PathData.Types )
                    GdipFree([rdi].PathData.Types)
                    mov [rdi].PathData.Types,NULL
                .endif
                .if (count <= 0)
                    mov eax,Ok
                   .break
                .endif
            .endif

            .if ( [rdi].PathData.Count == 0 )

                imul ecx,count,PointF
                .if !GdipAlloc(rcx)
                    mov eax,OutOfMemory
                   .break
                .endif
                mov [rdi].PathData.Points,rax

                .if !GdipAlloc(count)

                    mov rcx,[rdi].PathData.Points
                    mov [rdi].PathData.Points,NULL
                    GdipFree(rcx)
                    mov eax,OutOfMemory
                   .break
                .endif
                mov [rdi].PathData.Types,rax
                mov [rdi].PathData.Count,count
            .endif
            GdipGetPathData(this.nativePath, rdi)
        .until 1
        mov rdi,pathdata
        this.SetStatus()
        }

    .static StartFigure {
        this.SetStatus(GdipStartPathFigure(this.nativePath))
        }
    .static CloseFigure {
        this.SetStatus(GdipClosePathFigure(this.nativePath))
        }
    .static CloseAllFigures {
        this.SetStatus(GdipClosePathFigures(this.nativePath))
        }
    .static SetMarker {
        this.SetStatus(GdipSetPathMarker(this.nativePath))
        }
    .static ClearMarkers {
        this.SetStatus(GdipClearPathMarkers(this.nativePath))
        }
    .static Reverse {
        this.SetStatus(GdipReversePath(this.nativePath))
        }
    .static GetLastPoint lastPoint:abs {
        this.SetStatus(GdipGetPathLastPoint(this.nativePath, lastPoint))
        }

    ; AddLine(PointF& pt1, PointF& pt2)
    ; AddLine(REAL x1, REAL y1, REAL x2, REAL y2)
    ; AddLine(Point& pt1, Point& pt2)
    ; AddLine(INT x1, INT y1, INT x2, INT y2)

    .static AddLine :abs, :abs, :abs, :abs {
      ifidn <ptrPointF>,typeid(_1)
        .err <_1 -- GraphicsPath::AddLine(Point[F])>
      elseifidn <ptrPoint>,typeid(_1)
        .err <_1 -- GraphicsPath::AddLine(Point[F])>
      elseifidn <PointF>,typeid(_1)
        this.SetStatus(GdipAddPathLine(this.nativePath, _1.X, _1.Y, _2.X, _2.Y))
      elseifidn <Point>,typeid(_1)
        this.SetStatus(GdipAddPathLineI(this.nativePath, _1.X, _1.Y, _2.X, _2.Y))
      elseifidn <flt>,typeid(_1)
        this.SetStatus(GdipAddPathLine(this.nativePath, _1, _2, _3, _4))
      elseifidn <oword>,typeid(_1)
        this.SetStatus(GdipAddPathLine(this.nativePath, _1, _2, _3, _4))
      elseifidn <real4>,typeid(_1)
        this.SetStatus(GdipAddPathLine(this.nativePath, _1, _2, _3, _4))
      else
        this.SetStatus(GdipAddPathLineI(this.nativePath, _1, _2, _3, _4))
      endif
        }

    ; AddLines(PointF* points, INT count)
    ; AddLines(Point* points, INT count)

    .static AddLines :abs, :abs {
      ifidn <ptrPoint>,typeid(_1)
        this.SetStatus(GdipAddPathLine2I(this.nativePath, _1, _2))
      elseifidn <ptrPointF>,typeid(_1)
        this.SetStatus(GdipAddPathLine2(this.nativePath, _1, _2))
      else
        .err <_1 -- GraphicsPath::AddLines(Point[F]*, int)>
      endif
        this.SetStatus()
        }

    ; AddArc(RectF& rect, REAL startAngle, REAL sweepAngle)
    ; AddArc(REAL x, REAL y, REAL width, REAL height, REAL startAngle, REAL sweepAngle)
    ; AddArc(Rect& rect, REAL startAngle, REAL sweepAngle)
    ; AddArc(INT x, INT y, INT width, INT height, REAL startAngle, REAL sweepAngle)

    .static AddArc :abs, :abs, :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_1)
        .err <_1 -- GraphicsPath::AddArc(Rect[F])>
      elseifidn <ptrRect>,typeid(_1)
        .err <_1 -- GraphicsPath::AddArc(Rect[F])>
      elseifidn <RectF>,typeid(_1)
        this.SetStatus(GdipAddPathArc(this.nativePath, _1.X, _1.Y, _1.Width, _1.Height, _2, _3))
      elseifidn <Rect>,typeid(_1)
        this.SetStatus(GdipAddPathArcI(this.nativePath, _1.X, _1.Y, _1.Width, _1.Height, _2, _3))
      elseifidn <flt>,typeid(_1)
        this.SetStatus(GdipAddPathArc(this.nativePath, _1, _2, _3, _4, _5, _6))
      elseifidn <real4>,typeid(_1)
        this.SetStatus(GdipAddPathArc(this.nativePath, _1, _2, _3, _4, _5, _6))
      elseifidn <oword>,typeid(_1)
        this.SetStatus(GdipAddPathArc(this.nativePath, _1, _2, _3, _4, _5, _6))
      else
        this.SetStatus(GdipAddPathArcI(this.nativePath, _1, _2, _3, _4, _5, _6))
      endif
        }

    ; AddBezier(PointF& pt1, PointF& pt2, PointF& pt3, PointF& pt4)
    ; AddBezier(REAL x1, REAL y1, REAL x2, REAL y2, REAL x3, REAL y3, REAL x4, REAL y4)
    ; AddBezier(Point& pt1, Point& pt2, Point& pt3, Point& pt4)
    ; AddBezier(INT x1, INT y1, INT x2, INT y2, INT x3, INT y3, INT x4, INT y4)

    .static AddBezier :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs {
      ifidn <ptrPointF>,typeid(_1)
        .err <_1 -- GraphicsPath::AddBezier(Point[F])>
      elseifidn <ptrPoint>,typeid(_1)
        .err <_1 -- GraphicsPath::AddBezier(Point[F])>
      elseifidn <PointF>,typeid(_1)
        this.SetStatus(GdipAddPathBezier(this.nativePath, _1.X, _1.Y, _2.X, _2.Y, _3.X, _3.Y, _4.X, _4.Y))
      elseifidn <Point>,typeid(_1)
        this.SetStatus(GdipAddPathBezierI(this.nativePath, _1.X, _1.Y, _2.X, _2.Y, _3.X, _3.Y, _4.X, _4.Y))
      elseifidn <flt>,typeid(_1)
        this.SetStatus(GdipAddPathBezier(this.nativePath, _1, _2, _3, _4, _5, _6, _7, _8))
      elseifidn <real4>,typeid(_1)
        this.SetStatus(GdipAddPathBezier(this.nativePath, _1, _2, _3, _4, _5, _6, _7, _8))
      elseifidn <oword>,typeid(_1)
        this.SetStatus(GdipAddPathBezier(this.nativePath, _1, _2, _3, _4, _5, _6, _7, _8))
      else
        this.SetStatus(GdipAddPathBezierI(this.nativePath, _1, _2, _3, _4, _5, _6, _7, _8))
      endif
        }

    ; AddBeziers(PointF* points, INT count)
    ; AddBeziers(Point* points, INT count)

    .static AddBeziers :abs, :abs {
      ifidn <ptrPointF>,typeid(_1)
        this.SetStatus(GdipAddPathBeziers(this.nativePath, _1, _2))
      elseifidn <ptrPoint>,typeid(_1)
        this.SetStatus(GdipAddPathBeziers(this.nativePath, _1, _2))
      else
        .err <_1 -- GraphicsPath::AddBeziers(Point[F]*, int)>
      endif
        }

    ; AddCurve(PointF* points, INT count)
    ; AddCurve(PointF* points, INT count, REAL tension)
    ; AddCurve(PointF* points, INT count, INT offset, INT numberOfSegments, REAL tension)
    ; AddCurve(Point* points, INT count)
    ; AddCurve(Point* points, INT count, REAL tension)
    ; AddCurve(Point* points, INT count, INT offset, INT numberOfSegments, REAL tension)

    .static AddCurve :abs, :abs, :abs, :abs, :abs {
      ifidn <ptrPointF>,typeid(_1)
       ifb <_3>
        this.SetStatus(GdipAddPathCurve(this.nativePath, _1, _2))
       elseifb <_4>
        this.SetStatus(GdipAddPathCurve2(this.nativePath, _1, _2, _3))
       else
        this.SetStatus(GdipAddPathCurve3(this.nativePath, _1, _2, _3, _4, _5))
       endif
      elseifidn <ptrPoint>,typeid(_1)
       ifb <_3>
        this.SetStatus(GdipAddPathCurveI(this.nativePath, _1, _2))
       elseifb <_4>
        this.SetStatus(GdipAddPathCurve2I(this.nativePath, _1, _2, _3))
       else
        this.SetStatus(GdipAddPathCurve3I(this.nativePath, _1, _2, _3, _4, _5))
       endif
      else
        .err <_1 -- GraphicsPath::AddCurve(Point[F]*, )>
      endif
        }

    ; AddClosedCurve(PointF* points, INT count)
    ; AddClosedCurve(PointF* points, INT count, REAL tension)
    ; AddClosedCurve(Point* points, INT count)
    ; AddClosedCurve(Point* points, INT count, REAL tension)

    .static AddClosedCurve :abs, :abs, :abs {
      ifidn <ptrPointF>,typeid(_1)
       ifb <_3>
        this.SetStatus(GdipAddPathClosedCurve(this.nativePath, _1, _2))
       else
        this.SetStatus(GdipAddPathClosedCurve2(this.nativePath, _1, _2, _3))
       endif
      elseifidn <ptrPoint>,typeid(_1)
       ifb <_3>
        this.SetStatus(GdipAddPathClosedCurveI(this.nativePath, _1, _2))
       else
        this.SetStatus(GdipAddPathClosedCurve2I(this.nativePath, _1, _2, _3))
       endif
      else
        .err <_1 -- GraphicsPath::AddClosedCurve(Point[F]*, )>
      endif
      }

    ; AddRectangle(RectF& rect)
    ; AddRectangle(Rect& rect)

    .static AddRectangle :abs {
      ifidn <RectF>,typeid(_1)
        this.SetStatus(GdipAddPathRectangle(this.nativePath, _1.X, _1.Y, _1.Width, _1.Height))
      elseifidn <Rect>,typeid(_1)
        this.SetStatus(GdipAddPathRectangleI(this.nativePath, _1.X, _1.Y, _1.Width, _1.Height))
      else
        .err <_1 -- GraphicsPath::AddRectangle(Rect[F])>
      endif
      }

    ; AddRectangles(RectF* rects, INT count)
    ; AddRectangles(Rect* rects, INT count)

    .static AddRectangles :abs, :abs {
      ifidn <ptrRectF>,typeid(_1)
        this.SetStatus(GdipAddPathRectangles(this.nativePath, _1, _2))
      elseifidn <ptrRect>,typeid(_1)
        this.SetStatus(GdipAddPathRectanglesI(this.nativePath, _1, _2))
      else
        .err <_1 -- GraphicsPath::AddRectangles(Rect[F] *, int)>
      endif
      }

    ; AddEllipse(RectF& rect)
    ; AddEllipse(REAL x, REAL y, REAL width, REAL height)
    ; AddEllipse(Rect& rect)
    ; AddEllipse(INT x, INT y, INT width, INT height)

    .static AddEllipse :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_1)
        .err <_1 -- GraphicsPath::AddEllipse(Rect[F])>
      elseifidn <ptrRect>,typeid(_1)
        .err <_1 -- GraphicsPath::AddEllipse(Rect[F])>
      elseifidn <RectF>,typeid(_1)
        this.SetStatus(GdipAddPathEllipse(this.nativePath, _1.X, _1.Y, _1.Width, _1.Height))
      elseifidn <Rect>,typeid(_1)
        this.SetStatus(GdipAddPathEllipseI(this.nativePath, _1.X, _1.Y, _1.Width, _1.Height))
      elseifidn <flt>,typeid(_1)
        this.SetStatus(GdipAddPathEllipse(this.nativePath, _1, _2, _3, _4))
      elseifidn <real4>,typeid(_1)
        this.SetStatus(GdipAddPathEllipse(this.nativePath, _1, _2, _3, _4))
      elseifidn <oword>,typeid(_1)
        this.SetStatus(GdipAddPathEllipse(this.nativePath, _1, _2, _3, _4))
      else
        this.SetStatus(GdipAddPathEllipseI(this.nativePath, _1, _2, _3, _4))
      endif
        }

    ; AddPie(RectF& rect, REAL startAngle, REAL sweepAngle)
    ; AddPie(REAL x, REAL y, REAL width, REAL height, REAL startAngle, REAL sweepAngle)
    ; AddPie(Rect& rect, REAL startAngle, REAL sweepAngle)
    ; AddPie(INT x, INT y, INT width, INT height, REAL startAngle, REAL sweepAngle)

    .static AddPie :abs, :abs, :abs, :abs, :abs, :abs {
      ifidn <ptrRectF>,typeid(_1)
        .err <_1 -- GraphicsPath::AddPie(Rect[F])>
      elseifidn <ptrRect>,typeid(_1)
        .err <_1 -- GraphicsPath::AddPie(Rect[F])>
      elseifidn <RectF>,typeid(_1)
        this.SetStatus(GdipAddPathPie(this.nativePath, _1.X, _1.Y, _1.Width, _1.Height, _2, _3))
      elseifidn <Rect>,typeid(_1)
        this.SetStatus(GdipAddPathPieI(this.nativePath, _1.X, _1.Y, _1.Width, _1.Height, _2, _3))
      elseifidn <flt>,typeid(_1)
        this.SetStatus(GdipAddPathPie(this.nativePath, _1, _2, _3, _4, _5, _6))
      elseifidn <real4>,typeid(_1)
        this.SetStatus(GdipAddPathPie(this.nativePath, _1, _2, _3, _4, _5, _6))
      elseifidn <oword>,typeid(_1)
        this.SetStatus(GdipAddPathPie(this.nativePath, _1, _2, _3, _4, _5, _6))
      else
        this.SetStatus(GdipAddPathPieI(this.nativePath, _1, _2, _3, _4, _5, _6))
      endif
        }


    ; AddPolygon(PointF* points, INT count)
    ; AddPolygon(Point* points, INT count)

    .static AddPolygon :abs, :abs {
      ifidn <ptrPointF>,typeid(_1)
        this.SetStatus(GdipAddPathPolygon(this.nativePath, _1, _2))
      elseifidn <ptrPoint>,typeid(_1)
        this.SetStatus(GdipAddPathPolygonI(this.nativePath, _1, _2))
      else
        .err <_1 -- GraphicsPath::AddPolygon(Point[F] *, int)>
      endif
        }

    ; AddPath(GraphicsPath* addingPath, BOOL connect)

    .static AddPath :ptr GraphicsPath, :abs {
        .if _1
            mov _1,[_1].GraphicsPath.nativePath
        .endif
        this.SetStatus(GdipAddPathPath(this.nativePath, _1, _2))
        }

    ; AddString(WCHAR *, INT, FontFamily *, INT, REAL, PointF &, StringFormat *)
    ; AddString(WCHAR *, INT, FontFamily *, INT, REAL, RectF &,  StringFormat *)
    ; AddString(WCHAR *, INT, FontFamily *, INT, REAL, Point &,  StringFormat *)
    ; AddString(WCHAR *, INT, FontFamily *, INT, REAL, Rect &,   StringFormat *)

    .static AddString string:abs, length:abs, family:abs, style:abs, emSize:abs, origin:abs, format:abs {
      local rc
        .if LOADARGPTRCX(family)
            mov rcx,[rcx].FontFamily.nativeFamily
        .endif
        .if LOADARGPTRDX(format)
            mov rdx,[rdx].StringFormat.nativeFormat
        .endif
      ifidn <PointF>,typeid(origin)
        .new rc:RectF = { origin.X, origin.Y, 0.0, 0.0 }
        this.SetStatus(GdipAddPathString(this.nativePath, string, length, rcx, style, emSize, addr rc, rdx))
      elseifidn <Point>,typeid(origin)
        .new rc:Rect = { origin.X, origin.Y, 0.0, 0.0 }
        this.SetStatus(GdipAddPathStringI(this.nativePath, string, length, rcx, style, emSize, addr rc, rdx))
      elseifidn <Rect>,typeid(origin)
        this.SetStatus(GdipAddPathStringI(this.nativePath, string, length, rcx, style, emSize, addr origin, rdx))
      elseifidn <RectF>,typeid(origin)
        this.SetStatus(GdipAddPathString(this.nativePath, string, length, rcx, style, emSize, addr origin, rdx))
      else
        .err <origin -- GraphicsPath::AddString(Point[F]|Rect[F])>
      endif
      }


    .static Transform :ptr Matrix {
        mov eax,Ok
        .if _1
            GdipTransformPath(this.nativePath, [_1].Matrix.nativeMatrix)
        .endif
        this.SetStatus()
        }

    ;; This is not always the tightest bounds.

    ; GetBounds(RectF* bounds, Matrix* matrix = NULL, Pen* pen = NULL)
    ; GetBounds(Rect* bounds,  Matrix* matrix = NULL, Pen* pen = NULL)

    .static GetBounds bounds:abs, matrix:abs=<NULL>, pen:abs=<NULL> {
      ifidn <ptrRectF>,typeid(bounds)
        .err <Not implemented>
      elseifidn <ptrRect>,typeid(bounds)
        .err <Not implemented>
      else
        .err <bounds -- GraphicsPath::GetBounds(Rect[F]*)>
      endif
        }

    ;; Once flattened, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL the
    ;; identity matrix is assumed.

    ; Flatten(Matrix* matrix = NULL, REAL flatness = FlatnessDefault)

    .static Flatten matrix:abs=<NULL>, flatness:abs=<FlatnessDefault> {
        .if LOADARGPTRDX(matrix)
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        this.SetStatus(GdipFlattenPath(this.nativePath, rdx, flatness))
        }

    ; Widen(Pen* pen, Matrix* matrix = NULL, REAL flatness = FlatnessDefault)

    .static Widen pen:ptr Pen, matrix:abs=<NULL>, flatness:abs=<FlatnessDefault> {
        .if LOADARGPTRDX(matrix)
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        this.SetStatus(GdipWidenPath(this.nativePath, [rcx].Pen.nativePen, rdx, flatness))
        }

    ; Outline(Matrix *matrix = NULL, REAL flatness = FlatnessDefault)

    .static Outline matrix:abs=<NULL>, flatness:abs=<FlatnessDefault> {
        .if LOADARGPTRDX(matrix)
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        this.SetStatus(GdipWindingModeOutline(this.nativePath, rdx, flatness))
        }

    ;; Once this is called, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL, the
    ;; identity matrix is assumed.

    ; Warp(PointF* destPoints, INT count, RectF& srcRect, Matrix* matrix = NULL,
    ;   WarpMode warpMode = WarpModePerspective, REAL flatness = FlatnessDefault)

    .static Warp destPoints:abs, count:abs, srcRect:abs, matrix:abs=<NULL>,
            warpMode:abs=<WarpModePerspective>, flatness:abs=<FlatnessDefault> {
      ifidn <ptrRectF>,typeid(srcRect)
        .err <srcRect -- GraphicsPath::Warp(Rect[F])>
      endif
        .if LOADARGPTRDX(matrix)
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        this.SetStatus(GdipWarpPath(this.nativePath, rdx, destPoints, count,
            srcRect.X, srcRect.Y, srcRect.Width, srcRect.Height, warpMode, flatness))
        }

    .static GetPointCount {
        mov this.scratch,0
        this.SetStatus(GdipGetPointCount(this.nativePath, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetPathTypes types:abs, count:abs {
        this.SetStatus(GdipGetPathTypes(this.nativePath, types, count))
        }

    ; GetPathPoints(PointF* points, INT count)
    ; GetPathPoints(Point* points, INT count)

    .static GetPathPoints points:abs, count:abs {
      ifidn <ptrPointF>,typeid(points)
        GdipGetPathPoints(this.nativePath, points, count)
      elseifidn <ptrPoint>,typeid(points)
        GdipGetPathPointsI(this.nativePath, points, count)
      else
        .err <points -- GraphicsPath::GetPathPoints(Point[F]*)>
      endif
        }

    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }

    ; IsVisible(PointF& point, Graphics* g = NULL)
    ; IsVisible(REAL x, REAL y, Graphics* g = NULL)
    ; IsVisible(Point& point, Graphics* g = NULL)
    ; IsVisible(INT x, INT y, Graphics* g = NULL)

    .static IsVisible :abs, :abs, :abs=<NULL> {
      ifidn <PointF>,typeid(_1)
      elseifidn <Point>,typeid(_1)
      elseifidn <flt>,typeid(_1)
      elseifidn <real4>,typeid(_1)
      elseifidn <oword>,typeid(_1)
      else
      endif
        .err <Not Implemented: GraphicsPath::IsVisible()>
        mov eax,NotImplemented
        }

    ; IsOutlineVisible(PointF& point, Pen* pen, Graphics* g = NULL)
    ; IsOutlineVisible(REAL x, REAL y, Pen* pen, Graphics* g = NULL)
    ; IsOutlineVisible(Point& point, Pen* pen, Graphics* g = NULL)
    ; IsOutlineVisible(INT x, INT y, Pen* pen, Graphics* g = NULL)

    .static IsOutlineVisible :abs, :abs, :abs, :abs=<NULL> {
      ifidn <PointF>,typeid(_1)
      elseifidn <Point>,typeid(_1)
      elseifidn <flt>,typeid(_1)
      elseifidn <real4>,typeid(_1)
      elseifidn <oword>,typeid(_1)
      else
      endif
        .err <Not Implemented: GraphicsPath::IsOutlineVisible()>
        mov eax,NotImplemented
        }
    .ends
    GpPath typedef GraphicsPath

;;--------------------------------------------------------------------------
;; GraphisPathIterator class
;;--------------------------------------------------------------------------

.template GraphicsPathIterator fastcall

    nativeIterator  ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    .static GraphicsPathIterator :ptr GraphicsPath {
        .if _1
            mov _1,[_1].GraphicsPath.nativePath
        .endif
        this.SetStatus(GdipCreatePathIter(addr this.nativeIterator, _1))
        }

    .static Release {
        GdipDeletePathIter(this.nativeIterator)
        }

    .static SetNativeIterator :ptr GraphicsPath {
        mov this.nativeIterator,_1
        }

    .static SetStatus watcall :size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    ; NextSubpath(INT* startIndex, INT* endIndex, BOOL* isClosed)
    ; NextSubpath(GraphicsPath* path, BOOL* isClosed)
    ; NextPathType(BYTE* pathType, INT* startIndex, INT* endIndex)

    .static NextSubpath :ptr, :abs, :abs {
      ifb <_3>
        .if _1
            mov _1,[_1].GraphicsPath.nativePath
        .endif
        this.SetStatus(GdipPathIterNextSubpathPath(this.nativeIterator, addr this.scratch, _1, _2))
      elseifidn <ptrsdword>,typeid(_1)
        this.SetStatus(GdipPathIterNextSubpath(this.nativeIterator, addr this.scratch, _1, _2, _3))
      else
        this.SetStatus(GdipPathIterNextPathType(this.nativeIterator, addr this.scratch, _1, _2, _3))
      endif
        mov eax,this.scratch
        }

    .static NextPathType pathType:abs, startIndex:abs, endIndex:abs {
        this.SetStatus(GdipPathIterNextPathType(this.nativeIterator, addr this.scratch, pathType, startIndex, endIndex))
        mov eax,this.scratch
        }

    ; NextMarker(INT* startIndex, INT* endIndex)
    ; NextMarker(GraphicsPath* path)

    .static NextMarker startIndex:ptr, endIndex:abs {
      ifb <endIndex>
        .if rcx
            mov rcx,[rcx].GraphicsPath.nativePath
        .endif
        this.SetStatus(GdipPathIterNextMarkerPath(this.nativeIterator, addr this.scratch, rcx))
      else
        this.SetStatus(GdipPathIterNextMarker(this.nativeIterator, addr this.scratch, startIndex, endIndex))
      endif
        mov eax,this.scratch
        }

    .static GetCount {
        this.SetStatus(GdipPathIterGetCount(this.nativeIterator, addr this.scratch))
        mov eax,this.scratch
        }
    .static GetSubpathCount {
        this.SetStatus(GdipPathIterGetSubpathCount(this.nativeIterator, addr this.scratch))
        mov eax,this.scratch
        }
    .static HasCurve {
        this.SetStatus(GdipPathIterHasCurve(this.nativeIterator, addr this.scratch))
        mov eax,this.scratch
        }
    .static Rewind {
        this.SetStatus(GdipPathIterRewind(this.nativeIterator))
        }
    .static Enumerate points:abs, types:abs, count:abs {
        this.SetStatus(GdipPathIterEnumerate(this.nativeIterator, addr this.scratch, points, types, count))
        mov eax,this.scratch
        }
    .static CopyData points:abs, types:abs, startIndex:abs, endIndex:abs {
        this.SetStatus(GdipPathIterCopyData(this.nativeIterator, addr this.scratch, points, types, startIndex, endIndex))
        mov eax,this.scratch
        }
    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    .ends
    GpPathIterator typedef GraphicsPathIterator


;;--------------------------------------------------------------------------
;; Path Gradient Brush
;;
;; PathGradientBrush(PointF*, INT, WrapMode = WrapModeClamp)
;; PathGradientBrush(Point*, INT, WrapMode = WrapModeClamp)
;; PathGradientBrush(GraphicsPath*)
;;
;;--------------------------------------------------------------------------

.template PathGradientBrush fastcall : public Brush

    GpPathGradient typedef PathGradientBrush

    .static PathGradientBrush :abs, :abs, :abs=<WrapModeClamp> {
      ifidn <ptrPointF>,typeid(_1)
        GdipCreatePathGradient(_1, _2, _3, addr this.nativeBrush)
      elseifidn <ptrPoint>,typeid(_1)
        GdipCreatePathGradient(_1, _2, _3, addr this.nativeBrush)
      elseifidn <ptrGraphicsPath>,typeid(_1)
        LOADARGPTRCX(_1)
        GdipCreatePathGradientFromPath([rcx].GraphicsPath.nativePath, addr this.nativeBrush)
      else
        .err <_1>
      endif
        mov this.lastResult,eax
        }

    .static GetCenterColor :ptr Color {
        mov eax,InvalidParameter
        .if _1
            GdipGetPathGradientCenterColor(this.nativeBrush, _1)
        .endif
        this.SetStatus()
        }

    .static SetCenterColor color:abs {
        this.SetStatus(GdipSetPathGradientCenterColor(this.nativeBrush, color))
        }

    .static GetPointCount {
        this.SetStatus(GdipGetPathGradientPointCount(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetSurroundColorCount {
        this.SetStatus(GdipGetPathGradientSurroundColorCount(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetSurroundColors :ptr ARGB, :ptr SINT {
        mov eax,InvalidParameter
        .if _1 && _2
            GdipGetPathGradientSurroundColorsWithCount(this.nativeBrush, _1, _2)
        .endif
        this.SetStatus()
        }

    .static SetSurroundColors :ptr ARGB, :ptr SINT {
        mov eax,InvalidParameter
        .if _1 && _2
            GdipSetPathGradientSurroundColorsWithCount(this.nativeBrush, _1, _2)
        .endif
        this.SetStatus()
        }

    .static GetGraphicsPath :ptr GraphicsPath {
        mov eax,InvalidParameter
        .if _1
            GdipGetPathGradientPath(this.nativeBrush, [_1].GraphicsPath.nativePath)
        .endif
        this.SetStatus()
        }

    .static SetGraphicsPath :ptr GraphicsPath {
        mov eax,InvalidParameter
        .if _1
            GdipSetPathGradientPath(this.nativeBrush, [_1].GraphicsPath.nativePath)
        .endif
        this.SetStatus()
        }

    ; GetCenterPoint(PointF* point)
    ; GetCenterPoint(Point* point)

    .static GetCenterPoint :abs {
      ifidn <ptrPointF>,typeid(_1)
        this.SetStatus(GdipGetPathGradientCenterPoint(this.nativeBrush, _1))
      elseifidn <ptrPoint>,typeid(_1)
        this.SetStatus(GdipGetPathGradientCenterPointI(this.nativeBrush, _1))
      else
        .err <_1>
      endif
        }

    ; SetCenterPoint(PointF& point)
    ; SetCenterPoint(Point& point)

    .static SetCenterPoint :abs {
      ifidn <PointF>,typeid(_1)
        this.SetStatus(GdipSetPathGradientCenterPoint(this.nativeBrush, addr _1))
      elseifidn <Point>,typeid(_1)
        this.SetStatus(GdipSetPathGradientCenterPointI(this.nativeBrush, addr _1))
      else
        .err <_1>
      endif
        }

    ; GetRectangle(RectF* rect)
    ; GetRectangle(Rect* rect)

    .static GetRectangle :abs {
      ifidn <ptrRectF>,typeid(_1)
        GdipGetPathGradientRect(this.nativeBrush, _1)
      elseifidn <ptrRect>,typeid(_1)
        GdipGetPathGradientRectI(this.nativeBrush, _1)
      else
        .err <_1>
      endif
        }

    .static SetGammaCorrection useGammaCorrection:abs {
        this.SetStatus(GdipSetPathGradientGammaCorrection(this.nativeBrush, useGammaCorrection))
        }

    .static GetGammaCorrection {
        this.SetStatus(GdipGetPathGradientGammaCorrection(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetBlendCount {
        mov this.scratch,0
        this.SetStatus(GdipGetPathGradientBlendCount(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }

    .static GetBlend blendFactors:abs, blendPositions:abs, count:abs {
        this.SetStatus(GdipGetPathGradientBlend(this.nativeBrush, blendFactors, blendPositions, count))
        }

    .static SetBlend blendFactors:abs, blendPositions:abs, count:abs {
        this.SetStatus(GdipSetPathGradientBlend(this.nativeBrush, blendFactors, blendPositions, count))
        }

    .static GetInterpolationColorCount {
        mov this.scratch,0
        this.SetStatus(GdipGetPathGradientPresetBlendCount(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }

    .static SetInterpolationColors :ptr Color, :ptr REAL, :abs {
      local presetColors,blendPositions,count,argbs
       .new presetColors:ptr Color = _1
       .new blendPositions:ptr REAL = _2
       .new count:SINT = _3
       .new argbs:ptr ARGB
        .repeat
            .ifs ( count < 0 || blendPositions == NULL )
                mov eax,InvalidParameter
                mov this.lastResult,eax
               .break
            .endif
            imul ecx,count,ARGB
            mov argbs,GdipAlloc(rcx)
            .if rax == NULL
                mov eax,OutOfMemory
                mov this.lastResult,eax
               .break
            .endif
            mov rdx,rsi
            xchg rax,rdi
            mov rsi,presetColors
            mov ecx,count
            rep movsd
            mov rdi,rax
            mov rsi,rdx
            this.SetStatus(GdipSetPathGradientPresetBlend(this.nativeBrush, argbs, presetColors, count))
            GdipFree(argbs)
            mov eax,this.lastResult
        .until 1
        }

    .static GetInterpolationColors :ptr Color, :ptr REAL, :abs {
      local presetColors,blendPositions,count,argbs
       .new presetColors:ptr Color = _1
       .new blendPositions:ptr REAL = _2
       .new count:SINT = _3
       .new argbs:ptr ARGB
        .repeat
            .ifs ( count < 0 || presetColors == NULL )
                mov eax,InvalidParameter
                mov this.lastResult,eax
               .break
            .endif
            imul ecx,count,ARGB
            mov argbs,GdipAlloc(rcx)
            .if rax == NULL
                mov eax,OutOfMemory
                mov this.lastResult,eax
               .break
            .endif
            this.SetStatus(GdipGetPathGradientPresetBlend(this.nativeBrush, argbs, blendPositions, count))
            mov rdx,rsi
            mov rax,rdi
            mov rdi,argbs
            mov rsi,presetColors
            mov ecx,count
            rep movsd
            mov rdi,rax
            mov rsi,rdx
            GdipFree(argbs)
            mov eax,this.lastResult
        .until 1
        }

    .static SetBlendBellShape focus:abs, scale:abs=<1.0> {
        this.SetStatus(GdipSetPathGradientSigmaBlend(this.nativeBrush, focus, scale))
        }
    .static SetBlendTriangularShape focus:abs, scale:abs=<1.0> {
        this.SetStatus(GdipSetPathGradientLinearBlend(this.nativeBrush, focus, scale))
        }
    .static GetTransform :ptr Matrix {
        this.SetStatus(GdipGetPathGradientTransform(this.nativeBrush, [_1].Matrix.nativeMatrix))
        }
    .static SetTransform :ptr Matrix {
        this.SetStatus(GdipSetPathGradientTransform(this.nativeBrush, [_1].Matrix.nativeMatrix))
        }
    .static ResetTransform {
        this.SetStatus(GdipResetPathGradientTransform(this.nativeBrush))
        }
    .static MultiplyTransform :ptr Matrix, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipMultiplyPathGradientTransform(this.nativeBrush, [_1].Matrix.nativeMatrix, order))
        }
    .static TranslateTransform x:abs, y:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipTranslatePathGradientTransform(this.nativeBrush, x, y, order))
        }
    .static ScaleTransform x:abs, y:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipScalePathGradientTransform(this.nativeBrush, x, y, order))
        }
    .static RotateTransform angle:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipRotatePathGradientTransform(this.nativeBrush, angle, order))
        }
    .static GetFocusScales xScale:abs, yScale:abs {
        this.SetStatus(GdipGetPathGradientFocusScales(this.nativeBrush, xScale, yScale))
        }
    .static SetFocusScales xScale:abs, yScale:abs {
        this.SetStatus(GdipSetPathGradientFocusScales(this.nativeBrush, xScale, yScale))
        }
    .static GetWrapMode {
        this.SetStatus(GdipGetPathGradientWrapMode(this.nativeBrush, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetWrapMode wrapMode:abs {
        this.SetStatus(GdipSetPathGradientWrapMode(this.nativeBrush, wrapMode))
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; NOT _GRAPHICSPATH_HPP
