ifndef _GDIPLUSPATH_H
_GDIPLUSPATH_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template GraphicsPath

    nativePath ptr_t ?
    lastResult Status ?

    GraphicsPath proc :vararg
    GraphicsPath_GraphicsPath macro this, _1:=<FillModeAlternate>, _2, _3, _4:=<FillModeAlternate>
        mov this.nativePath,NULL
        if typeof(_1) eq 8
            ifb <_2>
                xchg rcx,rdx
                GdipClonePath([rcx].GraphicsPath.nativePath, rdx)
            elseif @InStr(1, <_1>, <addr >) and typeof(@SubStr(<_1>, 5)) eq sizeof(PointF)
                GdipCreatePath2(_1, _2, _3, _4, rcx)
            else
                GdipCreatePath2I(_1, _2, _3, _4, rcx)
            endif
        else
            GdipCreatePath(_1, rcx)
        endif
        mov this.lastResult,eax
        lea rax,this
        exitm<>
        endm

    .operator Release {
        exitm<GdipDeletePath([this].GraphicsPath.nativePath)>
        }

    .operator SetNativePath :ptr GraphicsPath {
        mov     [this].GraphicsPath.nativePath,_1
        }
    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].GraphicsPath.lastResult,eax
        .endif
        }

    ;; Reset the path object to empty (and fill mode to FillModeAlternate)

    .operator Reset :vararg {
        .ifd GdipResetPath([rcx].GraphicsPath.nativePath)
            mov this.lastResult,eax
        .endif
        }

    .operator GetFillMode :vararg {
        .new @fillmode:FillMode
        .ifd GdipGetPathFillMode([rcx].GraphicsPath.nativePath, &@fillmode)
            mov this.lastResult,eax
        .endif
        mov eax,@fillmode
        }

    .operator SetFillMode :vararg {
        .ifd GdipSetPathFillMode([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator GetPathData :ptr PathData, :vararg {

       .new count:SINT
       .new pathdata:ptr PathData

        mov pathdata,rdi
        mov rdi,rdx
        mov count,this.GetPointCount()

        .repeat

            .if ((count <= 0) || ([rdi].PathData.Count > 0 && [rdi].PathData.Count < count))

                mov [rdi].PathData.Count,0
                .if ([rdi].PathData.Points)

                    GdipFree([rdi].PathData.Points)
                    mov [rdi].PathData.Points,NULL
                .endif

                .if [rdi].PathData.Types

                    GdipFree([rdi].PathData.Types)
                    mov [rdi].PathData.Types,NULL
                .endif
                .if (count <= 0)

                    mov eax,Ok
                    .break
                .endif
            .endif

            .if [rdi].PathData.Count == 0

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
        mov this.lastResult,eax
        }

    .operator StartFigure :vararg {
        .ifd GdipStartPathFigure([rcx].GraphicsPath.nativePath)
            mov this.lastResult,eax
        .endif
        }

    .operator CloseFigure :vararg {
        .ifd GdipClosePathFigure([rcx].GraphicsPath.nativePath)
            mov this.lastResult,eax
        .endif
        }

    .operator CloseAllFigures :vararg {
        .ifd GdipClosePathFigures([rcx].GraphicsPath.nativePath)
            mov this.lastResult,eax
        .endif
        }

    .operator SetMarker :vararg {
        .ifd GdipSetPathMarker([rcx].GraphicsPath.nativePath)
            mov this.lastResult,eax
        .endif
        }

    .operator ClearMarkers :vararg {
        .ifd GdipClearPathMarkers([rcx].GraphicsPath.nativePath)
            mov this.lastResult,eax
        .endif
        }

    .operator Reverse :vararg {
        .ifd GdipReversePath([rcx].GraphicsPath.nativePath)
            mov this.lastResult,eax
        .endif
        }

    .operator GetLastPoint :vararg {
        .ifd GdipGetPathLastPoint([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddLine :vararg {
        .ifd GdipAddPathLine([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddLines :vararg {
        .ifd GdipAddPathLine2([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddLineI :vararg {
        .ifd GdipAddPathLineI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddLinesI :vararg {
        .ifd GdipAddPathLine2I([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddArc :vararg {
        .ifd GdipAddPathArc([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddArcI :vararg {
        .ifd GdipAddPathArcI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddBezier :vararg {
        .ifd GdipAddPathBezier([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddBeziers :vararg {
        .ifd GdipAddPathBeziers([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddBezierI :vararg {
        .ifd GdipAddPathBezierI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddBeziersI :vararg {
        .ifd GdipAddPathBeziersI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddCurve :vararg {
        .ifd GdipAddPathCurve([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddCurve2 :vararg {
        .ifd GdipAddPathCurve2([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddCurve3 :vararg {
        .ifd GdipAddPathCurve3([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddCurveI :vararg {
        .ifd GdipAddPathCurveI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddCurve2I :vararg {
        .ifd GdipAddPathCurve2I([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddCurve3I :vararg {
        .ifd GdipAddPathCurve3I([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddClosedCurve :vararg {
        .ifd GdipAddPathClosedCurve([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddClosedCurve2 :vararg {
        .ifd GdipAddPathClosedCurve2([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddClosedCurveI :vararg {
        .ifd GdipAddPathClosedCurveI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddClosedCurve2I :vararg {
        .ifd GdipAddPathClosedCurve2I([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddRectangle :ptr RectF, :vararg {
        .ifd GdipAddPathRectangle([rcx].GraphicsPath.nativePath,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height)
            mov this.lastResult,eax
        .endif
        }
    .operator AddRectangles :vararg {
        .ifd GdipAddPathRectangles([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddRectangleI :ptr Rect, :vararg {
        .ifd GdipAddPathRectangleI([rcx].GraphicsPath.nativePath,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height)
            mov this.lastResult,eax
        .endif
        }
    .operator AddRectanglesI :vararg {
        .ifd GdipAddPathRectanglesI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddEllipse :vararg {
        .ifd GdipAddPathEllipse([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddEllipseI :vararg {
        .ifd GdipAddPathEllipseI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddPie :vararg {
        .ifd GdipAddPathPie([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddPieI :vararg {
        .ifd GdipAddPathPieI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddPolygon :vararg {
        .ifd GdipAddPathPolygon([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }
    .operator AddPolygonI :vararg {
        .ifd GdipAddPathPolygonI([rcx].GraphicsPath.nativePath, _1)
            mov this.lastResult,eax
        .endif
        }

    .operator AddPath :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx].GraphicsPath.nativePath
        .endif
        .ifd GdipAddPathPath([rcx].GraphicsPath.nativePath, rdx, _2)
            mov this.lastResult,eax
        .endif
        }

    .operator AddString :ptr WCHAR, :SINT, :ptr FontFamily, :SINT, :REAL, :ptr PointF, :ptr StringFormat {

        .new rect:RectF
        .new @graphicspath:ptr GraphicsPath

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
        mov @graphicspath,this
        .ifd GdipAddPathString([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, &rect, r10)
            mov this,@graphicspath
            mov [this].GraphicsPath.lastResult,eax
        .endif
        }

    .operator AddString2 :ptr WCHAR, :SINT, :ptr FontFamily, :SINT, :REAL, :ptr RectF, :ptr StringFormat {
       .new @graphicspath:ptr GraphicsPath
        mov @graphicspath,this
        .if _3
            mov _3,[_3].FontFamily.nativeFamily
        .endif
        mov rax,_7
        .if rax
            mov rax,[rax].StringFormat.nativeFormat
        .endif
        .ifd GdipAddPathString([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6, rax)
            mov this,@graphicspath
            mov [this].GraphicsPath.lastResult,eax
        .endif
        }

    .operator AddStringI :ptr WCHAR, :SINT, :ptr FontFamily, :SINT, :REAL, :ptr Point, :ptr StringFormat {

       .new rect:Rect
       .new @graphicspath:ptr GraphicsPath
        mov @graphicspath,this

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
        mov @graphicspath,this
        .ifd GdipAddPathStringI([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, &rect, r10)
            mov this,@graphicspath
            mov [this].GraphicsPath.lastResult,eax
        .endif
        }

    .operator AddString2I :ptr WCHAR, :SINT, :ptr FontFamily, :SINT, :REAL, :ptr Rect, :ptr StringFormat {
       .new @graphicspath:ptr GraphicsPath
        mov @graphicspath,this
        .if _3
            mov _3,[_3].FontFamily.nativeFamily
        .endif
        mov r10,_7
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        .ifd GdipAddPathStringI([this].GraphicsPath.nativePath, _1, _2, _3, _4, _5, _6, r10)
            mov this,@graphicspath
            mov [this].GraphicsPath.lastResult,eax
        .endif
        }

    .operator Transform :ptr Matrix, :vararg {
        mov eax,Ok
        .if rdx
            .ifd GdipTransformPath([rcx].GraphicsPath.nativePath, [rdx].Matrix.nativeMatrix)
                mov this.lastResult,eax
            .endif
        .endif
        }

    ;; This is not always the tightest bounds.

    GetBounds2 proc :ptr RectF, :ptr Matrix, :ptr Pen
    GetBounds1 proc :ptr Rect, :ptr Matrix, :ptr Pen

    ;; Once flattened, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL the
    ;; identity matrix is assumed.

    .operator Flatten :ptr Matrix, :vararg {
        .if rdx
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        .if GdipFlattenPath([rcx].GraphicsPath.nativePath, rdx, _2)
            mov this.lastResult,eax
        .endif
        }

    .operator Widen :ptr Pen, :ptr Matrix, :vararg {
        .if r8
            mov r8,[r8].Matrix.nativeMatrix
        .endif
        .ifd GdipWidenPath([rcx].GraphicsPath.nativePath, [rdx].Pen.nativePen, r8, _3)
            mov this.lastResult,eax
        .endif
        }

    .operator Outline :ptr Matrix, :REAL {
        .if _1
            mov _1,[_1].Matrix.nativeMatrix
        .endif
        GdipWindingModeOutline([this].GraphicsPath.nativePath, _1, _2)
        }

    ;; Once this is called, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL, the
    ;; identity matrix is assumed.

    .operator Warp :ptr PointF, :SINT, :ptr RectF, :ptr Matrix, :WarpMode, :REAL {
        mov r10,_4
        .if r10
            mov r10,[r10].Matrix.nativeMatrix
        .endif
        GdipWarpPath([this].GraphicsPath.nativePath, r10, _1, _2, [_3].RectF.X, [_3].RectF.Y, [_3].RectF.Width, [_3].RectF.Height, _5, _6)
        }

    .operator GetPointCount {

        .new count:SINT

        mov count,0
        GdipGetPointCount([this].GraphicsPath.nativePath, &count)
        mov eax,count
        }

    .operator GetPathTypes :ptr BYTE, :SINT {
        GdipGetPathTypes([this].GraphicsPath.nativePath, _1, _2)
        }

    .operator GetPathPoints :ptr Point, :SINT {
        GdipGetPathPoints([this].GraphicsPath.nativePath, _1, _2)
        }
    .operator GetPathPointsI :ptr Point, :SINT {
        GdipGetPathPointsI([this].GraphicsPath.nativePath, _1, _2)
        }

    .operator GetLastStatus {
        mov eax,[this].GraphicsPath.lastResult
        mov [this].GraphicsPath.lastResult,Ok
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
    GpPath typedef GraphicsPath

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
