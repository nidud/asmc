ifndef _GDIPLUSPATH_H
_GDIPLUSPATH_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template GraphicsPath

    GpPath typedef GraphicsPath

    nativePath ptr_t ?
    lastResult Status ?
    memState   Status ?

    .operator CreatePath :FillMode {
        mov graphicspath,this
        mov [this].GraphicsPath.nativePath,NULL
        xchg rcx,rdx
        GdipCreatePath(ecx, &[rdx].GraphicsPath.nativePath)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator GraphicsPath :abs, :abs, :abs, :abs, :abs {

        .new graphicspath:ptr GraphicsPath

        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !GdipAlloc(GraphicsPath)
                mov [rax].GraphicsPath.memState,Ok
            .else
                mov [rax].GraphicsPath.memState,NotImplemented
            .endif
            mov [rax].GraphicsPath.nativePath,NULL
            mov [rax].GraphicsPath.lastResult,NotImplemented

            mov graphicspath,rax
            ifnb <_1>
                ifnb <_2>
                    GdipCreatePath2&_5&(_1, _2, _3, _4, rax)
                else
                    GdipCreatePath(_1, rax)
                endif
            else
                GdipCreatePath(FillModeAlternate, &[rax].GraphicsPath.nativePath)
            endif
            graphicspath.SetStatus(eax)
            mov rax,this

        .until 1
        retm<rax>
        }

    .operator Release {

        mov graphicspath,this

        GdipDeletePath([this].GraphicsPath.nativePath)

        mov this,graphicspath
        .if [this].GraphicsPath.memState != NotImplemented

            GdipFree(this)
        .endif

        exitm<>
        }

    .operator FromPath :ptr GraphicsPath {
        mov graphicspath,this
        xchg this,_1
        GdipClonePath([this].GraphicsPath.nativePath, &[_1].GraphicsPath.nativePath)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator SetNativePath :ptr GraphicsPath {
        mov     [this].GraphicsPath.nativePath,_1
        exitm   <>
    }
    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].GraphicsPath.lastResult,eax
        .endif
        retm<eax>
    }

    .operator Clone {

        .new clonepath:ptr GraphicsPath

        mov graphicspath,this
        mov clonepath,GraphicsPath()
        .if rax
            mov rcx,graphicspath
            GdipClonePath([rcx].GraphicsPath.nativePath, &[rax].GraphicsPath.nativePath)
            graphicspath.SetStatus(eax)
            mov edx,eax
            mov rax,clonepath
            mov [rax].GraphicsPath.lastResult,edx
        .endif
        retm <rax>
    }

    ;; Reset the path object to empty (and fill mode to FillModeAlternate)

    .operator Reset {
        mov graphicspath,this
        GdipResetPath([this].GraphicsPath.nativePath)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator GetFillMode {

        .new fillmode:FillMode

        mov graphicspath,this
        GdipGetPathFillMode([this].GraphicsPath.nativePath, &fillmode)
        graphicspath.SetStatus(eax)

        mov eax,fillmode
        retm <eax>
    }

    .operator SetFillMode :FillMode {
        mov graphicspath,this
        GdipSetPathFillMode([this].GraphicsPath.nativePath, _1)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator GetPathData :ptr PathData {

        mov graphicspath,this

        .repeat

            .if _1 == NULL

                graphicspath.SetStatus(InvalidParameter)
                .break
            .endif

            .new count:SINT
            .new pathdata:ptr PathData

            mov pathdata,_1
            mov count,graphicspath.GetPointCount()

            mov _1,pathdata

            .if ((count <= 0) || ([_1].PathData.Count > 0 && [_1].PathData.Count < count))

                mov [_1].PathData.Count,0
                .if ([_1].PathData.Points)

                    GdipFree([_1].PathData.Points)
                    mov _1,pathdata
                    mov [_1].PathData.Points,NULL
                .endif

                .if [_1].PathData.Types

                    GdipFree([_1].PathData.Types)

                    mov _1,pathdata
                    mov [_1].PathData.Types,NULL

                .endif

                .if (count <= 0)

                    mov eax,Ok
                    .break
                .endif
            .endif

            .if [_1].PathData.Count == 0

                imul ecx,count,PointF

                .if !GdipAlloc(rcx)

                    graphicspath.SetStatus(OutOfMemory)
                    .break

                .endif

                mov _1,pathdata
                mov [_1].PathData.Points,rax

                .if !GdipAlloc(count)

                    mov _1,pathdata
                    mov rcx,[_1].PathData.Points
                    mov [_1].PathData.Points,NULL
                    GdipFree(rcx)
                    graphicspath.SetStatus(OutOfMemory)
                    .break
                .endif
                mov _1,pathdata
                mov [_1].PathData.Types,rax
                mov [_1].PathData.Count,count
            .endif

            GdipGetPathData([this].GraphicsPath.nativePath, pathdata)
            graphicspath.SetStatus(eax)
        .until 1
        retm <eax>
    }

    .operator StartFigure {
        mov graphicspath,this
        GdipStartPathFigure([this].GraphicsPath.nativePath)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator CloseFigure {
        mov graphicspath,this
        GdipClosePathFigure([this].GraphicsPath.nativePath)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator CloseAllFigures {
        mov graphicspath,this
        GdipClosePathFigures([this].GraphicsPath.nativePath)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator SetMarker {
        mov graphicspath,this
        GdipSetPathMarker([this].GraphicsPath.nativePath)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator ClearMarkers {
        mov graphicspath,this
        GdipClearPathMarkers([this].GraphicsPath.nativePath)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator Reverse {
        mov graphicspath,this
        GdipReversePath([this].GraphicsPath.nativePath)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator GetLastPoint :ptr PointF {
        mov graphicspath,this
        GdipGetPathLastPoint([this].GraphicsPath.nativePath, _1)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator AddLine :abs, :abs, :abs, :abs {
        mov graphicspath,this
        if opattr(_1)
            GdipAddPathLineI([this].GraphicsPath.nativePath, _1, _2, _3, _4)
        else
            GdipAddPathLine([this].GraphicsPath.nativePath, _1, _2, _3, _4)
        endif
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddPathLine :REAL, :REAL, :REAL, :REAL {
        mov graphicspath,this
        GdipAddPathLine([this].GraphicsPath.nativePath, _1, _2, _3, _4)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddLines :ptr PointF, :SINT {
        mov graphicspath,this
        GdipAddPathLine2([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddPathLineI :SINT, :SINT, :SINT, :SINT {
        mov graphicspath,this
        GdipAddPathLineI([this].GraphicsPath.nativePath, _1, _2, _3, _4)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddLineI :ptr PointF, :ptr PointF {
        exitm<[this].GraphicsPath.AddPathLineI([_1].Point.X, [_1].Point.Y, [_2].Point.X, [_2].Point.Y)>
        }
    .operator AddLinesI :ptr Point, :SINT {
        mov graphicspath,this
        GdipAddPathLine2I([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddPathArc :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        mov graphicspath,this
        GdipAddPathArc([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddArc :ptr RectF, :REAL, :REAL {
        mov r10,_1
        exitm<[this].GraphicsPath.AddPathArc([r10].RectF.X, [r10].RectF.Y, [r10].RectF.Width, [r10].RectF.Height, _2, _3)>
        }
    .operator AddPathArcI :SINT, :SINT, :SINT, :SINT, :REAL, :REAL {
        mov graphicspath,this
        GdipAddPathArcI([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddArcI :ptr Rect, :REAL, :REAL {
        mov r10,_1
        exitm<[this].GraphicsPath.AddPathArcI([r10].Rect.X, [r10].Rect.Y, [r10].Rect.Width, [r10].Rect.Height, _2, _3)>
        }

    .operator AddPathBezier :REAL, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        mov graphicspath,this
        GdipAddPathBezier([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6, _7, _8)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddBezier :ptr PointF, :ptr PointF, :ptr PointF, :ptr PointF {
        mov r10,_4
        exitm<[this].GraphicsPath.AddPathBezier([_1].PointF.X, [_1].PointF.Y,\
            [_2].PointF.X, [_2].PointF.Y, [_3].PointF.X, [_3].PointF.Y, [r10].PointF.X, [r10].PointF.Y)>
        }
    .operator AddBeziers :ptr PointF, :SINT {
        mov graphicspath,this
        GdipAddPathBeziers([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddPathBezierI :SINT, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT, :SINT {
        mov graphicspath,this
        GdipAddPathBezierI([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6, _7, _8)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddBezierI :ptr Point, :ptr Point, :ptr Point, :ptr Point {
        mov r10,_4
        exitm<[this].GraphicsPath.AddPathBezierI([_1].Point.X, [_1].Point.Y,\
            [_2].Point.X, [_2].Point.Y, [_3].Point.X, [_3].Point.Y, [r10].Point.X, [r10].Point.Y)>
        }
    .operator AddBeziersI :ptr Point, :SINT {
        mov graphicspath,this
        GdipAddPathBeziersI([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddCurve :ptr PointF, :SINT {
        mov graphicspath,this
        GdipAddPathCurve([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddCurve2 :ptr PointF, :SINT, :REAL {
        mov graphicspath,this
        GdipAddPathCurve2([this].GraphicsPath.nativePath, _1, _2, _3)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddCurve3 :ptr PointF, :SINT, :SINT, :SINT, :REAL {
        mov graphicspath,this
        GdipAddPathCurve3([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddCurveI :ptr Point, :SINT {
        mov graphicspath,this
        GdipAddPathCurveI([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddCurve2I :ptr Point, :SINT, :REAL {
        mov graphicspath,this
        GdipAddPathCurve2I([this].GraphicsPath.nativePath, _1, _2, _3)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddCurve3I :ptr Point, :SINT, :SINT, :SINT, :REAL {
        mov graphicspath,this
        GdipAddPathCurve3I([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddClosedCurve :ptr PointF, :SINT {
        mov graphicspath,this
        GdipAddPathClosedCurve([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddClosedCurve2 :ptr PointF, :SINT, :REAL {
        mov graphicspath,this
        GdipAddPathClosedCurve2([this].GraphicsPath.nativePath, _1, _2, _3)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddClosedCurveI :ptr Point, :SINT {
        mov graphicspath,this
        GdipAddPathClosedCurveI([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddClosedCurve2I :ptr Point, :SINT, :REAL {
        mov graphicspath,this
        GdipAddPathClosedCurve2I([this].GraphicsPath.nativePath, _1, _2, _3)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddRectangle :ptr RectF {
        mov graphicspath,this
        GdipAddPathRectangle([this].GraphicsPath.nativePath, [_1].RectF.X, [_1].RectF.Y, [_1].RectF.Width, [_1].RectF.Height)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddRectangles :ptr RectF, :SINT {
        mov graphicspath,this
        GdipAddPathRectangles([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddRectangleI :ptr Rect {
        mov graphicspath,this
        GdipAddPathRectangleI([this].GraphicsPath.nativePath, [_1].Rect.X, [_1].Rect.Y, [_1].Rect.Width, [_1].Rect.Height)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddRectanglesI :ptr Rect, :SINT {
        mov graphicspath,this
        GdipAddPathRectanglesI([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddEllipse :abs, :abs, :abs, :abs {
        mov graphicspath,this
        if opattr(_1) ;eq 36
            GdipAddPathEllipseI([this].GraphicsPath.nativePath, _1, _2, _3, _4)
        else
            GdipAddPathEllipse([this].GraphicsPath.nativePath, _1, _2, _3, _4)
        endif
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddPathEllipse :REAL, :REAL, :REAL, :REAL {
        mov graphicspath,this
        GdipAddPathEllipse([this].GraphicsPath.nativePath, _1, _2, _3, _4)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddEllipseF :ptr RectF {
        exitm<[this].GraphicsPath.AddPathEllipse([_1].RectF.X, [_1].RectF.Y, [_1].RectF.Width, [_1].RectF.Height>
        }
    .operator AddPathEllipseI :SINT, :SINT, :SINT, :SINT {
        mov graphicspath,this
        GdipAddPathEllipseI([this].GraphicsPath.nativePath, _1, _2, _3, _4)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddEllipseI :ptr Rect {
        exitm<[this].GraphicsPath.AddPathEllipseI([_1].Rect.X, [_1].Rect.Y, [_1].Rect.Width, [_1].Rect.Height>
        }

    .operator AddPathPie :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        mov graphicspath,this
        GdipAddPathPie([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddPie :ptr RectF, :REAL, :REAL {
        exitm<[this].GraphicsPath.AddPathPie([_1].RectF.X, [_1].RectF.Y, [_1].RectF.Width, [_1].RectF.Height, _2, _3>
        }
    .operator AddPathPieI :SINT, :SINT, :SINT, :SINT, :REAL, :REAL {
        mov graphicspath,this
        GdipAddPathPieI([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddPieI :ptr Rect, :REAL, :REAL {
        exitm<[this].GraphicsPath.AddPathPie([_1].Rect.X, [_1].Rect.Y, [_1].Rect.Width, [_1].Rect.Height, _2, _3>
        }

    .operator AddPolygon :ptr PointF, :SINT {
        mov graphicspath,this
        GdipAddPathPolygon([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator AddPolygonI :ptr Point, :SINT {
        mov graphicspath,this
        GdipAddPathPolygonI([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddPath :ptr GraphicsPath, :BOOL {

        .new nativePath2:ptr GpPath

        mov nativePath2,NULL
        .if _1
            mov nativePath2,[_1].GraphicsPath.nativePath
        .endif
        mov graphicspath,this
        GdipAddPathPath([this].GraphicsPath.nativePath, nativePath2, _2)
        exitm<graphicspath.SetStatus(eax)>
    }

    .operator AddString :ptr WCHAR, :SINT, :ptr FontFamily, :SINT, :REAL, :ptr PointF, :ptr StringFormat {

        .new rect:RectF

        mov r10,_6
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.X,0.0
        mov rect.X,0.0
        .if _3
            mov _3,[_3].FontFamily.nativeFamily
        .endif
        mov r10,_7
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        mov graphicspath,this
        GdipAddPathString([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, &rect, r10)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddString2 :ptr WCHAR, :SINT, :ptr FontFamily, :SINT, :REAL, :ptr RectF, :ptr StringFormat {
        mov graphicspath,this
        .if _3
            mov _3,[_3].Family.nativeFamily
        .endif
        mov rax,_7
        .if rax
            mov rax,[rax].Format.nativeFormat
        .endif
        GdipAddPathString([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6, rax)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddStringI :ptr WCHAR, :SINT, :ptr FontFamily, :SINT, :REAL, :ptr Point, :ptr StringFormat {

        .new rect:Rect

        mov r10,_6
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.X,0.0
        mov rect.X,0.0
        .if _3
            mov _3,[_3].FontFamily.nativeFamily
        .endif
        mov r10,_7
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        mov graphicspath,this
        GdipAddPathStringI([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, &rect, r10)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator AddString2I :ptr WCHAR, :SINT, :ptr FontFamily, :SINT, :REAL, :ptr Rect, :ptr StringFormat {
        mov graphicspath,this
        .if _3
            mov _3,[_3].Family.nativeFamily
        .endif
        mov r10,_7
        .if r10
            mov r10,[r10].Format.nativeFormat
        .endif
        GdipAddPathStringI([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6, r10)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator Transform :ptr Matrix {
        mov graphicspath,this
        mov eax,Ok
        .if _1
            GdipTransformPath([this].GraphicsPath.nativePath, [_1].Matrix.nativeMatrix)
            graphicspath.SetStatus(eax)
        .endif
        retm <eax>
        }

    ;; This is not always the tightest bounds.

    GetBounds2 proc :ptr RectF, :ptr Matrix, :ptr Pen
    GetBounds1 proc :ptr Rect, :ptr Matrix, :ptr Pen

    ;; Once flattened, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL the
    ;; identity matrix is assumed.

    .operator Flatten :ptr Matrix, :REAL {
        .if _1
            mov _1,[_1].Matrix.nativeMatrix
        .endif
        mov graphicspath,this
        GdipFlattenPath([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator Widen :ptr Pen, :ptr Matrix, :REAL {
        .if _2
            mov _2,[_2].Matrix.nativeMatrix
        .endif
        mov graphicspath,this
        GdipWidenPath([this].GraphicsPath.nativePath, [_1].Pen.nativePen, _2, _3)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator Outline :ptr Matrix, :REAL {
        .if _1
            mov _1,[_1].Matrix.nativeMatrix
        .endif
        mov graphicspath,this
        GdipWindingModeOutline([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }

    ;; Once this is called, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL, the
    ;; identity matrix is assumed.

    .operator Warp :ptr PointF, :SINT, :ptr RectF, :ptr Matrix, :WarpMode, :REAL {
        mov r10,_4
        .if r10
            mov r10,[r10].Matrix.nativeMatrix
        .endif
        mov graphicspath,this
        GdipWarpPath([this].GraphicsPath.nativePath, r10, _1, _2, [_3].RectF.X, [_3].RectF.Y, [_3].RectF.Width, [_3].RectF.Height, _5, _6)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator GetPointCount {

        .new count:SINT

        mov count,0
        mov graphicspath,this
        GdipGetPointCount([this].GraphicsPath.nativePath, &count)
        graphicspath.SetStatus(eax)

        mov eax,count
        retm <eax>
        }

    .operator GetPathTypes :ptr BYTE, :SINT {
        mov graphicspath,this
        GdipGetPathTypes([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator GetPathPoints :ptr Point, :SINT {
        mov graphicspath,this
        GdipGetPathPoints([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }
    .operator GetPathPointsI :ptr Point, :SINT {
        mov graphicspath,this
        GdipGetPathPointsI([this].GraphicsPath.nativePath, _1, _2)
        exitm<graphicspath.SetStatus(eax)>
        }

    .operator GetLastStatus {
        mov eax,[this].GraphicsPath.lastResult
        mov [this].GraphicsPath.lastResult,Ok
        retm <eax>
        }

    IsVisible1 proc :SINT, :SINT, :ptr Graphics
    IsVisible2 proc :REAL, :REAL, :ptr Graphics
    IsVisible3 proc :ptr Point, :ptr Graphics
    IsVisible4 proc :ptr PointF, :ptr Graphics

    IsOutlineVisible1 proc :SINT, :SINT, :ptr Pen, :ptr Graphics
    IsOutlineVisible2 proc :REAL, :REAL, :ptr Pen, :ptr Graphics
    IsOutlineVisible3 proc :ptr PointF, :ptr Pen, :ptr Graphics
    IsOutlineVisible4 proc :ptr Point, :ptr Pen, :ptr Graphics
    .ends

;;--------------------------------------------------------------------------
;; GraphisPathIterator class
;;--------------------------------------------------------------------------

.template GraphicsPathIterator

    nativeIterator  ptr_t ?
    lastResult      Status ?
    memState        Status ?

    .operator GraphicsPathIterator :ptr GraphicsPath {

        .new graphicspathiterator:ptr GraphicsPathIterator

        mov rax,this
        .repeat
            .if rax == NULL
                mov graphicspathiterator,_1
                .break .if !GdipAlloc(GraphicsPathIterator)
                mov _1,graphicspathiterator
                mov [rax].GraphicsPathIterator.memState,Ok
            .else
                mov [rax].GraphicsPathIterator.memState,NotImplemented
            .endif
            mov graphicspathiterator,rax
            .if _1
                mov _1,[_1].GraphicsPath.nativePath
            .endif
            GdipCreatePathIter(&[rax].GraphicsPathIterator.nativeIterator, _1)
            mov this,graphicspathiterator
            mov [this].GraphicsPathIterator.lastResult,eax
            mov rax,this
        .until 1
        retm<rax>
        }

    .operator Release {

        mov graphicspathiterator,this

        GdipDeletePathIter([this].GraphicsPathIterator.nativeIterator)

        mov this,graphicspathiterator
        .if [this].GraphicsPathIterator.memState != NotImplemented

            GdipFree(this)
        .endif
        exitm<>
        }


    .operator SetNativeIterator :ptr GraphicsPath {
        mov     [this].GraphicsPathIterator.nativeIterator,_1
        exitm   <>
        }
    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].GraphicsPathIterator.lastResult,eax
        .endif
        retm<eax>
        }


    .operator NextSubpath :ptr SINT, :ptr SINT, :ptr BOOL {

        .new resultCount:SINT

        mov graphicspathiterator,this
        GdipPathIterNextSubpath([this].GraphicsPathIterator.nativeIterator, &resultCount, _1, _2, _3)
        graphicspathiterator.SetStatus(eax)

        mov eax,resultCount
        retm <eax>
        }


    .operator NextSubpath2 :ptr GraphicsPath, :ptr BOOL {

        .new resultCount:SINT

        .if _1
            mov _1,[_1].GraphicsPath.nativePath
        .endif
        mov graphicspathiterator,this
        GdipPathIterNextSubpathPath([this].GraphicsPathIterator.nativeIterator, &resultCount, _1, _2)
        graphicspathiterator.SetStatus(eax)

        mov eax,resultCount
        retm <eax>
        }

    .operator NextPathType :ptr, :ptr SINT, :ptr SINT {

        .new resultCount:SINT

        mov graphicspathiterator,this
        GdipPathIterNextPathType([this].GraphicsPathIterator.nativeIterator, &resultCount, _1, _2, _3)
        graphicspathiterator.SetStatus(eax)

        mov eax,resultCount
        retm <eax>
        }

    .operator NextMarker :ptr SINT, :ptr SINT, :ptr SINT {

        .new resultCount:SINT

        mov graphicspathiterator,this
        GdipPathIterNextMarker([this].GraphicsPathIterator.nativeIterator, &resultCount, _1, _2)
        graphicspathiterator.SetStatus(eax)

        mov eax,resultCount
        retm <eax>
        }


    .operator NextMarker2 :ptr GraphicsPath {

        .new resultCount:SINT

        .if _1
            mov _1,[_1].GraphicsPath.nativePath
        .endif
        mov graphicspathiterator,this
        GdipPathIterNextMarkerPath([this].GraphicsPathIterator.nativeIterator, &resultCount, _1)
        graphicspathiterator.SetStatus(eax)

        mov eax,resultCount
        retm <eax>
        }

    .operator GetCount {

        .new resultCount:SINT

        mov graphicspathiterator,this
        GdipPathIterGetCount([this].GraphicsPathIterator.nativeIterator, &resultCount)
        graphicspathiterator.SetStatus(eax)

        mov eax,resultCount
        retm <eax>
        }

    .operator GetSubpathCount {

        .new resultCount:SINT

        mov graphicspathiterator,this
        GdipPathIterGetSubpathCount([this].GraphicsPathIterator.nativeIterator, &resultCount)
        graphicspathiterator.SetStatus(eax)

        mov eax,resultCount
        retm <eax>
        }

    .operator HasCurve {

        .new hasCurve:BOOL

        mov graphicspathiterator,this
        GdipPathIterHasCurve([this].GraphicsPathIterator.nativeIterator, &hasCurve)
        graphicspathiterator.SetStatus(eax)

        mov eax,hasCurve
        retm <eax>
        }

    .operator Rewind {
        mov graphicspathiterator,this
        GdipPathIterRewind([this].GraphicsPathIterator.nativeIterator)
        exitm<graphicspathiterator.SetStatus(eax)>
        }

    .operator Enumerate :ptr PointF, :ptr BYTE, :SINT {

        .new resultCount:SINT

        mov graphicspathiterator,this
        GdipPathIterEnumerate([this].GraphicsPathIterator.nativeIterator, &resultCount, _1, _2, _3)
        graphicspathiterator.SetStatus(eax)

        mov eax,resultCount
        retm <eax>
        }

    .operator CopyData :ptr PointF, :ptr BYTE, :SINT, :SINT {

        .new resultCount:SINT

        mov graphicspathiterator,this
        GdipPathIterCopyData([this].GraphicsPathIterator.nativeIterator, &resultCount, _1, _2, _3, _4)
        graphicspathiterator.SetStatus(eax)

        mov eax,resultCount
        retm <eax>
        }

    .operator GetLastStatus {

        mov eax,[this].GraphicsPath.lastResult
        mov [this].GraphicsPath.lastResult,Ok

        retm <eax>
        }

    .ends
    GpPathIterator typedef GraphicsPathIterator


;;--------------------------------------------------------------------------
;; Path Gradient Brush
;;--------------------------------------------------------------------------

.template PathGradientBrush : public Brush

    GpPathGradient typedef PathGradientBrush

    BRUSH_OPERATOR(PathGradientBrush)

    .operator PathGradientBrush :ptr, :abs, :abs, :abs {

        .new brush:ptr PathGradientBrush

        mov rax,this
        .repeat
            .if rax == NULL
                mov brush,_1
                .break .if !GdipAlloc(Brush)
                mov [rax].Brush.memState,Ok
                mov _1,brush
            .else
                mov [rax].Brush.memState,NotImplemented
            .endif
            mov [rax].Brush.nativeBrush,NULL
            mov brush,rax
            mov rcx,_1
            ;ifnb <_2>
            ;    GdipCreatePathGradient&_4&(_1, _2, _3, rax)
            ;else
                GdipCreatePathGradientFromPath([rcx].GraphicsPath.nativePath, &[rax].Brush.nativeBrush)
            ;endif
            brush.SetStatus(eax)
            mov rax,this
        .until 1
        retm<rax>
        }

    .operator GetCenterColor :ptr Color {
        mov brush,this
        .if _1 == NULL
            brush.SetStatus(InvalidParameter)
        .else
            GdipGetPathGradientCenterColor([this].Brush.nativeBrush, &[_1].Color.Argb)
            brush.SetStatus(eax)
        .endif
        retm <eax>
        }

    .operator SetCenterColor :ARGB {
        mov brush,this
        GdipSetPathGradientCenterColor([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetPointCount {

        .new count:SINT

        mov brush,this
        GdipGetPathGradientPointCount([this].Brush.nativeBrush, &count)
        brush.SetStatus(eax)

        mov eax,count
        retm <eax>
        }

    .operator GetSurroundColorCount {

        .new count:SINT

        mov brush,this
        GdipGetPathGradientSurroundColorCount([this].Brush.nativeBrush, &count)
        brush.SetStatus(eax)
        mov eax,count
        retm <eax>
        }

    .operator GetSurroundColors :ptr ARGB, :ptr SINT {
        mov brush,this
        .if (_1 == NULL || _2 == NULL)
            mov eax,InvalidParameter
        .else
            GdipGetPathGradientSurroundColorsWithCount([this].Brush.nativeBrush, _1, _2)
        .endif
        exitm<brush.SetStatus(eax)>
        }

    .operator SetSurroundColors :ptr ARGB, :ptr SINT {
        mov brush,this
        .if (_1 == NULL || _2 == NULL)
            mov eax,InvalidParameter
        .else
            GdipSetPathGradientSurroundColorsWithCount([this].Brush.nativeBrush, _1, _2)
        .endif
        exitm<brush.SetStatus(eax)>
        }

    .operator GetGraphicsPath :ptr GraphicsPath {
        mov brush,this
        .if _1 == NULL
            mov eax,InvalidParameter
        .else
            GdipGetPathGradientPath([this].Brush.nativeBrush, [_1].GraphicsPath.nativePath)
        .endif
        exitm<brush.SetStatus(eax)>
        }

    .operator SetGraphicsPath :ptr GraphicsPath {
        mov brush,this
        .if _1 == NULL
            mov eax,InvalidParameter
        .else
            GdipSetPathGradientPath([this].Brush.nativeBrush, [_1].GraphicsPath.nativePath)
        .endif
        exitm<brush.SetStatus(eax)>
        }

    .operator GetCenterPoint :ptr PointF {
        mov brush,this
        GdipGetPathGradientCenterPoint([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetCenterPointI :ptr Point {
        mov brush,this
        GdipGetPathGradientCenterPointI([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetCenterPoint :ptr PointF {
        mov brush,this
        GdipSetPathGradientCenterPoint([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetCenterPointI :ptr Point {
        mov brush,this
        GdipSetPathGradientCenterPointI([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetRectangle :ptr RectF {
        mov brush,this
        GdipGetPathGradientRect([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetRectangleI :ptr Rect {
        mov brush,this
        GdipGetPathGradientRectI([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetGammaCorrection :BOOL {
        mov brush,this
        GdipSetPathGradientGammaCorrection([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetGammaCorrection {

        .new useGammaCorrection:BOOL

        mov brush,this
        GdipGetPathGradientGammaCorrection([this].Brush.nativeBrush, &useGammaCorrection)
        brush.SetStatus(eax)
        mov eax,useGammaCorrection
        retm <eax>
    }

    .operator GetBlendCount {

        .new count:SINT

        mov count,0
        mov brush,this
        GdipGetPathGradientBlendCount([this].Brush.nativeBrush, &count)
        brush.SetStatus(eax)
        mov eax,count
        retm <eax>
        }

    .operator GetBlend :ptr REAL, :ptr REAL, :SINT {
        mov brush,this
        GdipGetPathGradientBlend([this].Brush.nativeBrush, _1, _2, _3)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetBlend :ptr REAL, :ptr REAL, :SINT {
        mov brush,this
        GdipSetPathGradientBlend([this].Brush.nativeBrush, _1, _2, _3)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetInterpolationColorCount {

        .new count:SINT

        mov count,0
        mov brush,this
        GdipGetPathGradientPresetBlendCount([this].Brush.nativeBrush, &count)
        brush.SetStatus(eax)
        mov eax,count
        retm <eax>
        }

    .operator SetInterpolationColors :ptr Color, :ptr REAL, :SINT {

        .repeat

            mov brush,this
            .ifs (_3 < 0 || _1 == NULL)

                brush.SetStatus(InvalidParameter)
                .break
            .endif

            .new count:SINT
            .new blendPositions:ptr SINT
            .new color:ptr Color
            .new argbs:ptr ARGB

            mov color,_1
            mov blendPositions,_2
            mov count,_3

            imul ecx,_3,ARGB
            mov argbs,GdipAlloc(rcx)
            .if rax == NULL

                brush.SetStatus(OutOfMemory)
                .break
            .endif

            mov     rdx,rsi
            xchg    rax,rdi
            mov     rsi,color
            mov     ecx,count
            rep     movsd
            mov     rdi,rax
            mov     rsi,rdx
            mov     this,brush

            GdipSetPathGradientPresetBlend([this].Brush.nativeBrush, argbs, color, count)
            GdipFree(argbs)
            brush.GetStatus()
        .until 1
        retm <eax>
        }

    .operator GetInterpolationColors :ptr Color, :ptr REAL, :SINT {

        .repeat

            mov brush,this
            .ifs (_3 < 0 || _1 == NULL)

                brush.SetStatus(InvalidParameter)
                .break
            .endif

            .new count:SINT
            .new blendPositions:ptr SINT
            .new color:ptr Color
            .new argbs:ptr ARGB

            mov color,_1
            mov blendPositions,_2
            mov count,_3

            imul ecx,_3,ARGB
            mov argbs,GdipAlloc(rcx)
            .if rax == NULL

                brush.SetStatus(OutOfMemory)
                .break
            .endif
            GdipGetPathGradientPresetBlend([this].Brush.nativeBrush, argbs, blendPositions, count)

            mov rdx,rsi
            mov rax,rdi
            mov rdi,argbs
            mov rsi,color
            mov ecx,count
            rep movsd
            mov rdi,rax
            mov rsi,rdx

            GdipFree(argbs)
            brush.GetStatus()
        .until 1
        retm <eax>
        }

    .operator SetBlendBellShape :REAL, :REAL {
        mov brush,this
        GdipSetPathGradientSigmaBlend([this].Brush.nativeBrush, _1, _2)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetBlendTriangularShape :REAL, :REAL {
        mov brush,this
        GdipSetPathGradientLinearBlend([this].Brush.nativeBrush, _1, _2)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetTransform :ptr Matrix {
        mov brush,this
        GdipGetPathGradientTransform([this].Brush.nativeBrush, [_1].Matrix.nativeMatrix)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetTransform :ptr Matrix {
        mov brush,this
        GdipSetPathGradientTransform([this].Brush.nativeBrush, [_1].Matrix.nativeMatrix)
        exitm<brush.SetStatus(eax)>
        }

    .operator ResetTransform {
        mov brush,this
        GdipResetPathGradientTransform([this].Brush.nativeBrush)
        exitm<brush.SetStatus(eax)>
        }

    .operator MultiplyTransform :ptr Matrix, :MatrixOrder {
        mov brush,this
        GdipMultiplyPathGradientTransform([this].Brush.nativeBrush, [_1].Matrix.nativeMatrix, _2)
        exitm<brush.SetStatus(eax)>
        }

    .operator TranslateTransform :REAL, :REAL, :MatrixOrder {
        mov brush,this
        GdipTranslatePathGradientTransform([this].Brush.nativeBrush, _1, _2, _3)
        exitm<brush.SetStatus(eax)>
        }

    .operator ScaleTransform :REAL, :REAL, :MatrixOrder {
        mov brush,this
        GdipScalePathGradientTransform([this].Brush.nativeBrush, _1, _2, _3)
        exitm<brush.SetStatus(eax)>
        }

    .operator RotateTransform :REAL, :MatrixOrder {
        mov brush,this
        GdipRotatePathGradientTransform([this].Brush.nativeBrush, _1, _2)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetFocusScales :ptr REAL, :ptr REAL {
        mov brush,this
        GdipGetPathGradientFocusScales([this].Brush.nativeBrush, _1, _2)
        exitm<brush.SetStatus(eax)>
        }

    .operator SetFocusScales :REAL, :REAL {
        mov brush,this
        GdipSetPathGradientFocusScales([this].Brush.nativeBrush, _1, _2)
        exitm<brush.SetStatus(eax)>
        }

    .operator GetWrapMode {

        .new wrapMode:WrapMode

        mov brush,this
        GdipGetPathGradientWrapMode([this].Brush.nativeBrush, &wrapMode)
        brush.SetStatus(eax)
        mov eax,wrapMode
        retm <eax>
        }

    .operator SetWrapMode :WrapMode {
        mov brush,this
        GdipSetPathGradientWrapMode([this].Brush.nativeBrush, _1)
        exitm<brush.SetStatus(eax)>
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; NOT _GRAPHICSPATH_HPP
