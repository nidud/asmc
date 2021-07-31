ifndef _GDIPLUSPATH_H
_GDIPLUSPATH_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template GraphicsPath

    nativePath  ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .inline GraphicsPath :abs, :vararg {
        ifnb <_1>
            this.typeid(GraphicsPath, _1)(_1, _2)
        else
            this.GraphicsPathIMM32(FillModeAlternate)
        endif
        mov this.lastResult,eax
        }
    .inline GraphicsPathIMM32 :abs {
        GdipCreatePath(_1, this)
        }
    .inline GraphicsPathPPointF :abs, :abs, :abs, :abs=<FillModeAlternate> {
        GdipCreatePath2(_1, _2, _3, _4, this)
        }
    .inline GraphicsPathPPoint :abs, :abs, :abs, :abs=<FillModeAlternate> {
        GdipCreatePath2I(_1, _2, _3, _4, this)
        }

    .inline Release :vararg {
        GdipDeletePath(this.nativePath)
        }

    .inline SetNativePath :ptr GraphicsPath, :vararg {
        mov this.nativePath,rdx
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

    ;; Reset the path object to empty (and fill mode to FillModeAlternate)

    .inline Reset :vararg {
        GdipResetPath(this.nativePath)
        GdipSetStatus(this)
        }

    .inline GetFillMode :vararg {
        mov this.scratch,FillModeAlternate
        GdipGetPathFillMode(this.nativePath, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetFillMode :vararg {
        GdipSetPathFillMode(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .inline GetPathData :ptr PathData, :vararg {

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

    .inline StartFigure :vararg {
        GdipStartPathFigure(this.nativePath)
        GdipSetStatus(this)
        }

    .inline CloseFigure :vararg {
        GdipClosePathFigure(this.nativePath)
        GdipSetStatus(this)
        }

    .inline CloseAllFigures :vararg {
        GdipClosePathFigures(this.nativePath)
        GdipSetStatus(this)
        }

    .inline SetMarker :vararg {
        GdipSetPathMarker(this.nativePath)
        GdipSetStatus(this)
        }

    .inline ClearMarkers :vararg {
        GdipClearPathMarkers(this.nativePath)
        GdipSetStatus(this)
        }

    .inline Reverse :vararg {
        GdipReversePath(this.nativePath)
        GdipSetStatus(this)
        }

    .inline GetLastPoint :vararg {
        GdipGetPathLastPoint(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .inline AddLine :abs, :vararg {
        this.typeid(AddLine, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline AddLineIMMFLT :vararg {
        GdipAddPathLine(this.nativePath, _1)
        }
    .inline AddLineIMM32 :vararg {
        GdipAddPathLineI(this.nativePath, _1)
        }
    .inline AddLineREG128   :vararg { this.AddLineIMMFLT(_1) }
    .inline AddLineREAL4    :vararg { this.AddLineIMMFLT(_1) }
    .inline AddLineREG32    :vararg { this.AddLineIMM32(_1) }
    .inline AddLineSDWORD   :vararg { this.AddLineIMM32(_1) }

    .inline AddLinePPointF :ptr PointF, :ptr PointF, :vararg {
        this.AddLineIMMFLT([rdx].PointF.X, [rdx].PointF.Y, [r8].PointF.X, [r8].PointF.Y)
        }
    .inline AddLinePPoint :ptr Point, :ptr Point, :vararg {
        this.AddLineIMM32([rdx].Point.X, [rdx].Point.Y, [r8].Point.X, [r8].Point.Y)
        }

    .inline AddLines :abs, :vararg {
        this.typeid(AddLines, _1)(_1, _2)
        this.SetStatus()
        }
    .inline AddLinesPPointF :vararg {
        GdipAddPathLine2(this.nativePath, _1)
        }
    .inline AddLinesPPoint :vararg {
        GdipAddPathLine2I(this.nativePath, _1)
        }

    .inline AddArc :abs, :vararg {
        this.typeid(AddArc, _1)(_1, _2)
        this.SetStatus()
        }
    .inline AddArcIMMFLT :vararg {
        GdipAddPathArc(this.nativePath, _1)
        }
    .inline AddArcIMM32 :vararg {
        GdipAddPathArcI(this.nativePath, _1)
        }
    .inline AddArcREG128   :vararg { this.AddArcIMMFLT(_1) }
    .inline AddArcREAL4    :vararg { this.AddArcIMMFLT(_1) }
    .inline AddArcREG32    :vararg { this.AddArcIMM32(_1) }
    .inline AddArcSDWORD   :vararg { this.AddArcIMM32(_1) }

    .inline AddArcPRectF :ptr RectF, :vararg {
        GdipAddPathArc(this.nativePath, \
            [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, _2)
        }
    .inline AddArcPRect :ptr Rect, :vararg {
        GdipAddPathArcI(this.nativePath, \
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
        }

    .inline AddBezier :abs, :vararg {
        this.typeid(AddBezier, _1)(_1, _2)
        this.SetStatus()
        }
    .inline AddBezierREG128   :vararg { this.AddBezierIMMFLT(_1) }
    .inline AddBezierREAL4  :vararg { this.AddBezierIMMFLT(_1) }
    .inline AddBezierREG32    :vararg { this.AddBezierIMM32(_1) }
    .inline AddBezierSDWORD   :vararg { this.AddBezierIMM32(_1) }

    .inline AddBezierIMMFLT :vararg {
        GdipAddPathBezier(this.nativePath, _1)
        }
    .inline AddBezierIMM32 :vararg {
        GdipAddPathBezierI(this.nativePath, _1)
        }
    .inline AddBezierPPointF :ptr PointF, :ptr PointF, :ptr PointF, :ptr PointF, :vararg {
        mov r10,[rsp+8*4]
        GdipAddPathBezier(this.nativePath, [rdx].PointF.X, [rdx].PointF.Y,\
            [r8].PointF.X, [r8].PointF.Y, [r9].PointF.X, [r9].PointF.Y, [r10].PointF.X, [r10].PointF.Y)
        }
    .inline AddBezierPPoint :ptr Point, :ptr Point, :ptr Point, :ptr Point, :vararg {
        mov r10,[rsp+8*4]
        GdipAddPathBezierI(this.nativePath, [rdx].Point.X, [rdx].Point.Y,\
            [r8].Point.X, [r8].Point.Y, [r9].Point.X, [r9].Point.Y, [r10].Point.X, [r10].Point.Y)
        }

    .inline AddBeziers :abs, :vararg {
        this.typeid(AddBeziers, _1)(_1, _2)
        }
    .inline AddBeziersPPointF :vararg {
        GdipAddPathBeziers(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddBeziersPPoint :vararg {
        GdipAddPathBeziersI(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .inline AddCurve :abs, :vararg {
        this.typeid(AddCurve, _1)(_1, _2)
        }
    .inline AddCurvePPointF :abs, :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathCurve(this.nativePath, _1, _2)
        elseifb <_4>
            GdipAddPathCurve2(this.nativePath, _1, _2, _3)
        else
            GdipAddPathCurve3(this.nativePath, _1, _2, _3, _4, _5)
        endif
        GdipSetStatus(this)
        }
    .inline AddCurvePPoint :abs, :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathCurveI(this.nativePath, _1, _2)
        elseifb <_4>
            GdipAddPathCurve2I(this.nativePath, _1, _2, _3)
        else
            GdipAddPathCurve3I(this.nativePath, _1, _2, _3, _4, _5)
        endif
        GdipSetStatus(this)
        }

    .inline AddClosedCurve :abs, :vararg {
        this.typeid(AddClosedCurve, _1)(_1, _2)
        }
    .inline AddClosedCurvePPointF :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathClosedCurve(this.nativePath, _1, _2)
        else
            GdipAddPathClosedCurve2(this.nativePath, _1, _2, _3)
        endif
        GdipSetStatus(this)
        }
    .inline AddClosedCurvePPoint :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathClosedCurveI(this.nativePath, _1, _2)
        else
            GdipAddPathClosedCurve2I(this.nativePath, _1, _2, _3)
        endif
        GdipSetStatus(this)
        }

    .inline AddRectangle :abs, :vararg {
        this.typeid(AddRectangle, _1)(_1, _2)
        }
    .inline AddRectangleIMM32 :vararg {
        GdipAddPathRectangleI(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddRectangleREG32  :vararg { this.AddRectangleIMM32(_1) }
    .inline AddRectangleSDWORD :vararg { this.AddRectangleIMM32(_1) }
    .inline AddRectanglePRectF :ptr RectF, :vararg {
        GdipAddPathRectangle(this.nativePath,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height)
        GdipSetStatus(this)
        }
    .inline AddRectanglePRect :ptr Rect, :vararg {
        GdipAddPathRectangleI(this.nativePath,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height)
        GdipSetStatus(this)
        }

    .inline AddRectangles :abs, :vararg {
        this.typeid(AddRectangles, _1)(_1, _2)
        }
    .inline AddRectanglesPRectF :vararg {
        GdipAddPathRectangles(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddRectanglesPRect :vararg {
        GdipAddPathRectanglesI(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .inline AddEllipse :abs, :vararg {
        this.typeid(AddEllipse, _1)(_1, _2)
        }
    .inline AddEllipseIMMFLT :vararg {
        GdipAddPathEllipse(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddEllipseIMM32 :vararg {
        GdipAddPathEllipseI(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddEllipseREG128 :vararg { this.AddEllipseIMMFLT(_1) }
    .inline AddEllipseREAL4  :vararg { this.AddEllipseIMMFLT(_1) }
    .inline AddEllipseREG32  :vararg { this.AddEllipseIMM32(_1) }
    .inline AddEllipseSDWORD :vararg { this.AddEllipseIMM32(_1) }

    .inline AddPie :abs, :vararg {
        this.typeid(AddPie, _1)(_1, _2)
        }
    .inline AddPieIMMFLT :vararg {
        GdipAddPathPie(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddPieIMM32 :vararg {
        GdipAddPathPieI(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddPieREG128 :vararg { this.AddPieIMMFLT(_1) }
    .inline AddPieREAL4  :vararg { this.AddPieIMMFLT(_1) }
    .inline AddPieREG32  :vararg { this.AddPieIMM32(_1) }
    .inline AddPieSDWORD :vararg { this.AddPieIMM32(_1) }

    .inline AddPolygon :abs, :vararg {
        this.typeid(AddPolygon, _1)(_1, _2)
        }
    .inline AddPolygonPPointF :vararg {
        GdipAddPathPolygon(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddPolygonPPoint :vararg {
        GdipAddPathPolygonI(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .inline AddPath :ptr GraphicsPath, :vararg {
        test    rdx,rdx
        cmovnz  rdx,[rdx].GraphicsPath.nativePath
        GdipAddPathPath(this.nativePath, rdx, _2)
        GdipSetStatus(this)
        }

    .inline AddString :abs, :abs, :abs, :abs, :abs, :abs, :abs, :vararg {
        this.typeid(AddString, _6)(_1, _2, _3, _4, _5, _6, _7, _8)
        }

    .inline AddStringPPointF :abs, :abs,\
            :ptr FontFamily, :abs, :abs, :ptr PointF, :ptr StringFormat, :vararg {

        .new    rect:RectF

        mov r10,[rsp+6*8]
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.X,0.0
        mov rect.X,0.0
        .if rdx
            mov rdx,[rdx].FontFamily.nativeFamily
        .endif
        mov r10,[rsp+7*8]
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        GdipAddPathString(this.nativePath, rdx, _2, _3, _4, _5, &rect, r10)
        GdipSetStatus(this)
        }

    .inline AddStringPRectF :abs, :abs, :ptr FontFamily, :abs, :abs, :abs, :ptr StringFormat, :vararg {
        .if r9
            mov r9,[r9].FontFamily.nativeFamily
        .endif
        mov     rax,[rsp+7*8]
        test    rax,rax
        cmovnz  rax,[rax].StringFormat.nativeFormat

        GdipAddPathString(this.nativePath, _1, _2, r9, _4, _5, _6, rax)
        GdipSetStatus(this)
        }

    .inline AddStringPPoint :abs, :abs, :ptr FontFamily, :abs, :abs, :ptr Point, :ptr StringFormat, :vararg {

       .new     rect:Rect

        mov     r10,_6
        mov     rect.X,[r10].PointF.X
        mov     rect.Y,[r10].PointF.Y
        mov     rect.X,0.0
        mov     rect.X,0.0
        .if r9
            mov r9,[r9].FontFamily.nativeFamily
        .endif
        mov r10,[rsp+7*8]
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        GdipAddPathStringI(this.nativePath, _1, _2, r9, _4, _5, &rect, r10)
        GdipSetStatus(this)
        }

    .inline AddStringPRect :abs, :abs, :ptr FontFamily, :abs, :abs, :abs, :ptr StringFormat, :vararg {

        .if r9
            mov r9,[r9].FontFamily.nativeFamily
        .endif
        mov     r10,[rsp+7*8]
        .if r10
            mov r10,[r10].StringFormat.nativeFormat
        .endif
        GdipAddPathStringI(this.nativePath, _1, _2, r9, _4, _5, _6, r10)
        GdipSetStatus(this)
        }

    .inline Transform :ptr Matrix, :vararg {
        mov eax,Ok
        .if rdx
            GdipTransformPath(this.nativePath, [rdx].Matrix.nativeMatrix)
            GdipSetStatus(this)
        .endif
        }

    ;; This is not always the tightest bounds.

    .inline GetBounds :abs, :vararg {
        this.typeid(GetBounds, _1)(_1, _2)
        }
    .inline GetBoundsPRectF :ptr RectF, :ptr Matrix, :ptr Pen {
        }
    .inline GetBoundsPRect :ptr Rect, :ptr Matrix, :ptr Pen {
        }

    ;; Once flattened, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL the
    ;; identity matrix is assumed.

    .inline Flatten :ptr Matrix, :vararg {
        .if rdx
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        GdipFlattenPath(this.nativePath, rdx, _2)
        GdipSetStatus(this)
        }

    .inline Widen :ptr Pen, :ptr Matrix, :vararg {
        .if r8
            mov r8,[r8].Matrix.nativeMatrix
        .endif
        GdipWidenPath(this.nativePath, [rdx].Pen.nativePen, r8, _3)
        GdipSetStatus(this)
        }

    .inline Outline :ptr Matrix, :vararg {
        .if rdx
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        GdipWindingModeOutline(this.nativePath, rdx, _2)
        GdipSetStatus(this)
        }

    ;; Once this is called, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL, the
    ;; identity matrix is assumed.

    .inline Warp :abs, :abs, :ptr RectF, :abs=<0>, :abs=<WarpModePerspective>, :vararg {

        mov rcx,_4
        .if rcx
            mov rcx,[rcx].Matrix.nativeMatrix
        .endif
        GdipWarpPath( this.nativePath, rcx, _1, _2,\
                      [r9].RectF.X,\
                      [r9].RectF.Y,\
                      [r9].RectF.Width,\
                      [r9].RectF.Height,\
                      _5, _6 )
        GdipSetStatus(this)
        }

    .inline GetPointCount :vararg {
        mov this.scratch,0
        GdipGetPointCount(this.nativePath, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline GetPathTypes :vararg {
        GdipGetPathTypes(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .inline GetPathPoints :abs, :vararg {
        this.typeid(GetPathPoints, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline GetPathPointsPPointF :abs, :vararg {
        GdipGetPathPoints(this.nativePath, _1, _2)
        }
    .inline GetPathPointsPPoint :abs, :vararg {
        GdipGetPathPointsI(this.nativePath, _1, _2)
        }

    .inline GetLastStatus :vararg {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }

    .inline IsVisible :abs, :vararg {
        this.typeid(IsVisible, _1)(_1, _2)
        }
    .inline IsVisibleIMM32 :vararg {
        mov eax,NotImplemented
        }
    .inline IsVisibleIMMFLT :vararg {
        mov eax,NotImplemented
        }
    .inline IsVisiblePPoint :ptr Point, :vararg {
        this.IsVisible([rdx].Point.X, [rdx].Point.Y, _2)
        }
    .inline IsVisiblePPointF :ptr PointF, :vararg {
        this.IsVisible([rdx].PointF.X, [rdx].PointF.Y, _2)
        }

    .inline IsOutlineVisible :abs, :vararg {
        this.typeid(IsOutlineVisible, _1)(_1, _2)
        }
    .inline IsOutlineVisibleIMM32 :vararg {
        mov eax,NotImplemented
        }
    .inline IsOutlineVisibleIMMFLT :vararg {
        mov eax,NotImplemented
        }
    .inline IsOutlineVisible3 :ptr PointF, :vararg {
        this.IsOutlineVisible4([rdx].Point.X, [rdx].Point.Y, _2)
        }
    .inline IsOutlineVisible4 :ptr Point, :vararg {
        this.IsOutlineVisible4([rdx].Point.X, [rdx].Point.Y, _2)
        }
    .ends
    GpPath typedef GraphicsPath

;;--------------------------------------------------------------------------
;; GraphisPathIterator class
;;--------------------------------------------------------------------------

.template GraphicsPathIterator

    nativeIterator  ptr_t ?
    lastResult      Status ?
    scratch         int_t ?

    .inline GraphicsPathIterator :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx].GraphicsPath.nativePath
        .endif
        GdipCreatePathIter(addr this.nativeIterator, rdx)
        this.SetStatus()
        }

    .inline Release :vararg {
        GdipDeletePathIter(this.nativeIterator)
        }

    .inline SetNativeIterator :ptr GraphicsPath, :vararg {
        mov     this.nativeIterator,_1
        }
    .inline SetStatus :abs, :vararg {
        ifnb <_1>
        ifdif <_1>,<eax>
            mov eax,_1
        endif
        endif
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }


    .inline NextSubpath :abs, :vararg {
        this.typeid(NextSubpath, _1)(_1, _2)
        }
    .inline NextSubpathPSDWORD :vararg {
        GdipPathIterNextSubpath(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline NextSubpathPGraphicsPath :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx].GraphicsPath.nativePath
        .endif
        GdipPathIterNextSubpathPath(this.nativeIterator, addr this.scratch, rdx, _2)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline NextPathType :vararg {
        GdipPathIterNextPathType(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline NextMarker :abs, :vararg {
        this.typeid(NextMarker, _1)(_1, _2)
        }
    .inline NextMarkerPSDWORD :vararg {
        GdipPathIterNextMarker(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline NextMarkerPGraphicsPath :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx].GraphicsPath.nativePath
        .endif
        GdipPathIterNextMarkerPath(this.nativeIterator, addr this.scratch, rdx, _2)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetCount :vararg {
        GdipPathIterGetCount(this.nativeIterator, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetSubpathCount :vararg {
        GdipPathIterGetSubpathCount(this.nativeIterator, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline HasCurve :vararg {
        GdipPathIterHasCurve(this.nativeIterator, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline Rewind :vararg {
        GdipPathIterRewind(this.nativeIterator)
        this.SetStatus()
        }

    .inline Enumerate :vararg {
        GdipPathIterEnumerate(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline CopyData :vararg {
        GdipPathIterCopyData(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }

    .inline GetLastStatus :vararg {
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

.template PathGradientBrush : public Brush

    GpPathGradient typedef PathGradientBrush

    .inline PathGradientBrush :abs, :vararg {
        this.typeid(PathGradientBrush, _1)(_1, _2)
        mov this.lastResult,eax
        }

    .inline PathGradientBrushPPointF :abs, :abs, :abs=<WrapModeClamp>, :vararg {
        GdipCreatePathGradient(_1, _2, _3, addr this.nativeBrush)
        }
    .inline PathGradientBrushPPoint :abs, :abs, :abs=<WrapModeClamp>, :vararg {
        GdipCreatePathGradientI(_1, _2, _3, addr this.nativeBrush)
        }
    .inline PathGradientBrushPGraphicsPath :ptr GraphicsPath, :vararg {
        mov rcx,rdx
        GdipCreatePathGradientFromPath([rcx].GraphicsPath.nativePath, addr this.nativeBrush)
        }

    .inline GetCenterColor :ptr Color, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetPathGradientCenterColor(this.nativeBrush, rdx)
        .endif
        GdipSetStatus(this)
        }

    .inline SetCenterColor :vararg {
        GdipSetPathGradientCenterColor(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .inline GetPointCount :vararg {
        GdipGetPathGradientPointCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline GetSurroundColorCount :vararg {
        GdipGetPathGradientSurroundColorCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline GetSurroundColors :ptr ARGB, :ptr SINT, :vararg {
        mov eax,InvalidParameter
        .if rdx && r8
            GdipGetPathGradientSurroundColorsWithCount(this.nativeBrush, rdx, r8)
        .endif
        GdipSetStatus(this)
        }

    .inline SetSurroundColors :ptr ARGB, :ptr SINT, :vararg {
        mov eax,InvalidParameter
        .if rdx && r8
            GdipSetPathGradientSurroundColorsWithCount(this.nativeBrush, rdx, r8)
        .endif
        GdipSetStatus(this)
        }

    .inline GetGraphicsPath :ptr GraphicsPath, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetPathGradientPath(this.nativeBrush, [rdx].GraphicsPath.nativePath)
        .endif
        GdipSetStatus(this)
        }

    .inline SetGraphicsPath :ptr GraphicsPath, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipSetPathGradientPath(this.nativeBrush, [rdx].GraphicsPath.nativePath)
        .endif
        GdipSetStatus(this)
        }

    .inline GetCenterPoint :abs, :vararg {
        this.typeid(GetCenterPoint, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline GetCenterPointPPointF :vararg {
        GdipGetPathGradientCenterPoint(this.nativeBrush, _1)
        }
    .inline GetCenterPointPPoint :vararg {
        GdipGetPathGradientCenterPointI(this.nativeBrush, _1)
        }

    .inline SetCenterPoint :abs, :vararg {
        this.typeid(SetCenterPoint, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline SetCenterPointPPointF :vararg {
        GdipSetPathGradientCenterPoint(this.nativeBrush, _1)
        }
    .inline SetCenterPointPPoint :vararg {
        GdipSetPathGradientCenterPointI(this.nativeBrush, _1)
        }

    .inline GetRectangle :abs, :vararg {
        this.typeid(GetRectangle, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline GetRectanglePRectF :vararg {
        GdipGetPathGradientRect(this.nativeBrush, _1)
        }
    .inline GetRectanglePRect :vararg {
        GdipGetPathGradientRectI(this.nativeBrush, _1)
        }

    .inline SetGammaCorrection :vararg {
        GdipSetPathGradientGammaCorrection(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .inline GetGammaCorrection :vararg {
        GdipGetPathGradientGammaCorrection(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline GetBlendCount :vararg {
        mov this.scratch,0
        GdipGetPathGradientBlendCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline GetBlend :vararg {
        GdipGetPathGradientBlend(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .inline SetBlend :vararg {
        GdipSetPathGradientBlend(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .inline GetInterpolationColorCount :vararg {
        mov this.scratch,0
        GdipGetPathGradientPresetBlendCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetInterpolationColors :ptr Color, :ptr REAL, :SINT, :vararg {

        .repeat

            .ifs (r9d < 0 || rdx == NULL)

                mov eax,InvalidParameter
                mov this.lastResult,eax
                .break
            .endif

            .new count:SINT
            .new blendPositions:ptr SINT
            .new color:ptr Color
            .new argbs:ptr ARGB

            mov color,rdx
            mov blendPositions,r8
            mov count,r9d

            imul ecx,r9d,ARGB
            mov argbs,GdipAlloc(rcx)
            .if rax == NULL

                mov eax,OutOfMemory
                mov this.lastResult,eax
                .break
            .endif

            mov     rdx,rsi
            xchg    rax,rdi
            mov     rsi,color
            mov     ecx,count
            rep     movsd
            mov     rdi,rax
            mov     rsi,rdx

            GdipSetPathGradientPresetBlend(this.nativeBrush, argbs, color, count)
            GdipFree(argbs)
            this.GetStatus()
        .until 1
        }

    .inline GetInterpolationColors :ptr Color, :ptr REAL, :SINT, :vararg {

        .repeat

            .ifs (r9d < 0 || rdx == NULL)

                mov eax,InvalidParameter
                mov this.lastResult,eax
                .break
            .endif

            .new count:SINT
            .new blendPositions:ptr SINT
            .new color:ptr Color
            .new argbs:ptr ARGB

            mov color,rdx
            mov blendPositions,r8
            mov count,r9d

            imul ecx,r9d,ARGB
            mov argbs,GdipAlloc(rcx)
            .if rax == NULL

                mov eax,OutOfMemory
                mov this.lastResult,eax
                .break
            .endif
            GdipGetPathGradientPresetBlend(this.nativeBrush, argbs, blendPositions, count)

            mov rdx,rsi
            mov rax,rdi
            mov rdi,argbs
            mov rsi,color
            mov ecx,count
            rep movsd
            mov rdi,rax
            mov rsi,rdx

            GdipFree(argbs)
            this.GetStatus()
        .until 1
        }

    .inline SetBlendBellShape :abs, :abs=<1.0>, :vararg {
        GdipSetPathGradientSigmaBlend(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .inline SetBlendTriangularShape :abs, :abs=<1.0>, :vararg {
        GdipSetPathGradientLinearBlend(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .inline GetTransform :ptr Matrix, :vararg {
        GdipGetPathGradientTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .inline SetTransform :ptr Matrix, :vararg {
        GdipSetPathGradientTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .inline ResetTransform :vararg {
        GdipResetPathGradientTransform(this.nativeBrush)
        GdipSetStatus(this)
        }

    .inline MultiplyTransform :ptr Matrix, :abs=<MatrixOrderPrepend>, :vararg {
        GdipMultiplyPathGradientTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix, _2)
        GdipSetStatus(this)
        }

    .inline TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipTranslatePathGradientTransform(this.nativeBrush, _1, _2, _3)
        GdipSetStatus(this)
        }

    .inline ScaleTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipScalePathGradientTransform(this.nativeBrush, _1, _2, _3)
        GdipSetStatus(this)
        }

    .inline RotateTransform :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipRotatePathGradientTransform(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .inline GetFocusScales :vararg {
        GdipGetPathGradientFocusScales(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .inline SetFocusScales :vararg {
        GdipSetPathGradientFocusScales(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .inline GetWrapMode :vararg {
        GdipGetPathGradientWrapMode(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetWrapMode :vararg {
        GdipSetPathGradientWrapMode(this.nativeBrush, _1)
        GdipSetStatus(this)
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; NOT _GRAPHICSPATH_HPP
