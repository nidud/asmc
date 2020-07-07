ifndef _GDIPLUSPATH_H
_GDIPLUSPATH_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template GraphicsPath

    nativePath  ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .operator GraphicsPath :abs, :vararg {
        ifnb <_1>
            this.typeid(GraphicsPath, _1)(_1, _2)
        else
            this.GraphicsPath?i32(FillModeAlternate)
        endif
        mov this.lastResult,eax
        }
    .operator GraphicsPath?i32 :abs {
        GdipCreatePath(_1, this)
        }
    .operator GraphicsPath?pPointF :abs, :abs, :abs, :abs=<FillModeAlternate> {
        GdipCreatePath2(_1, _2, _3, _4, this)
        }
    .operator GraphicsPath?pPoint :abs, :abs, :abs, :abs=<FillModeAlternate> {
        GdipCreatePath2I(_1, _2, _3, _4, this)
        }

    .operator Release :vararg {
        GdipDeletePath(this.nativePath)
        }

    .operator SetNativePath :ptr GraphicsPath, :vararg {
        mov this.nativePath,rdx
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

    ;; Reset the path object to empty (and fill mode to FillModeAlternate)

    .operator Reset :vararg {
        GdipResetPath(this.nativePath)
        GdipSetStatus(this)
        }

    .operator GetFillMode :vararg {
        mov this.scratch,FillModeAlternate
        GdipGetPathFillMode(this.nativePath, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetFillMode :vararg {
        GdipSetPathFillMode(this.nativePath, _1)
        GdipSetStatus(this)
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
        GdipStartPathFigure(this.nativePath)
        GdipSetStatus(this)
        }

    .operator CloseFigure :vararg {
        GdipClosePathFigure(this.nativePath)
        GdipSetStatus(this)
        }

    .operator CloseAllFigures :vararg {
        GdipClosePathFigures(this.nativePath)
        GdipSetStatus(this)
        }

    .operator SetMarker :vararg {
        GdipSetPathMarker(this.nativePath)
        GdipSetStatus(this)
        }

    .operator ClearMarkers :vararg {
        GdipClearPathMarkers(this.nativePath)
        GdipSetStatus(this)
        }

    .operator Reverse :vararg {
        GdipReversePath(this.nativePath)
        GdipSetStatus(this)
        }

    .operator GetLastPoint :vararg {
        GdipGetPathLastPoint(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .operator AddLine :abs, :vararg {
        this.typeid(AddLine, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator AddLine?flt :vararg {
        GdipAddPathLine(this.nativePath, _1)
        }
    .operator AddLine?i32 :vararg {
        GdipAddPathLineI(this.nativePath, _1)
        }
    .operator AddLine?r128   :vararg { this.AddLine?flt(_1) }
    .operator AddLine?real4  :vararg { this.AddLine?flt(_1) }
    .operator AddLine?r32    :vararg { this.AddLine?i32(_1) }
    .operator AddLine?sdword :vararg { this.AddLine?i32(_1) }

    .operator AddLine?pPointF :ptr PointF, :ptr PointF, :vararg {
        this.AddLine?flt([rdx].PointF.X, [rdx].PointF.Y, [r8].PointF.X, [r8].PointF.Y)
        }
    .operator AddLine?pPoint :ptr Point, :ptr Point, :vararg {
        this.AddLine?i32([rdx].Point.X, [rdx].Point.Y, [r8].Point.X, [r8].Point.Y)
        }

    .operator AddLines :abs, :vararg {
        this.typeid(AddLines, _1)(_1, _2)
        this.SetStatus()
        }
    .operator AddLines?pPointF :vararg {
        GdipAddPathLine2(this.nativePath, _1)
        }
    .operator AddLines?pPoint :vararg {
        GdipAddPathLine2I(this.nativePath, _1)
        }

    .operator AddArc :abs, :vararg {
        this.typeid(AddArc, _1)(_1, _2)
        this.SetStatus()
        }
    .operator AddArc?flt :vararg {
        GdipAddPathArc(this.nativePath, _1)
        }
    .operator AddArc?i32 :vararg {
        GdipAddPathArcI(this.nativePath, _1)
        }
    .operator AddArc?r128   :vararg { this.AddArc?flt(_1) }
    .operator AddArc?real4  :vararg { this.AddArc?flt(_1) }
    .operator AddArc?r32    :vararg { this.AddArc?i32(_1) }
    .operator AddArc?sdword :vararg { this.AddArc?i32(_1) }

    .operator AddArc?pRectF :ptr RectF, :vararg {
        GdipAddPathArc(this.nativePath, \
            [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, _2)
        }
    .operator AddArc?pRect :ptr Rect, :vararg {
        GdipAddPathArcI(this.nativePath, \
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
        }

    .operator AddBezier :abs, :vararg {
        this.typeid(AddBezier, _1)(_1, _2)
        this.SetStatus()
        }
    .operator AddBezier?r128   :vararg { this.AddBezier?flt(_1) }
    .operator AddBezier?real4  :vararg { this.AddBezier?flt(_1) }
    .operator AddBezier?r32    :vararg { this.AddBezier?i32(_1) }
    .operator AddBezier?sdword :vararg { this.AddBezier?i32(_1) }

    .operator AddBezier?flt :vararg {
        GdipAddPathBezier(this.nativePath, _1)
        }
    .operator AddBezier?i32 :vararg {
        GdipAddPathBezierI(this.nativePath, _1)
        }
    .operator AddBezier?pPointF :ptr PointF, :ptr PointF, :ptr PointF, :ptr PointF, :vararg {
        mov r10,[rsp+8*4]
        GdipAddPathBezier(this.nativePath, [rdx].PointF.X, [rdx].PointF.Y,\
            [r8].PointF.X, [r8].PointF.Y, [r9].PointF.X, [r9].PointF.Y, [r10].PointF.X, [r10].PointF.Y)
        }
    .operator AddBezier?pPoint :ptr Point, :ptr Point, :ptr Point, :ptr Point, :vararg {
        mov r10,[rsp+8*4]
        GdipAddPathBezierI(this.nativePath, [rdx].Point.X, [rdx].Point.Y,\
            [r8].Point.X, [r8].Point.Y, [r9].Point.X, [r9].Point.Y, [r10].Point.X, [r10].Point.Y)
        }

    .operator AddBeziers :abs, :vararg {
        this.typeid(AddBeziers, _1)(_1, _2)
        }
    .operator AddBeziers?pPointF :vararg {
        GdipAddPathBeziers(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .operator AddBeziers?pPoint :vararg {
        GdipAddPathBeziersI(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .operator AddCurve :abs, :vararg {
        this.typeid(AddCurve, _1)(_1, _2)
        }
    .operator AddCurve?pPointF :abs, :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathCurve(this.nativePath, _1, _2)
        elseifb <_4>
            GdipAddPathCurve2(this.nativePath, _1, _2, _3)
        else
            GdipAddPathCurve3(this.nativePath, _1, _2, _3, _4, _5)
        endif
        GdipSetStatus(this)
        }
    .operator AddCurve?pPoint :abs, :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathCurveI(this.nativePath, _1, _2)
        elseifb <_4>
            GdipAddPathCurve2I(this.nativePath, _1, _2, _3)
        else
            GdipAddPathCurve3I(this.nativePath, _1, _2, _3, _4, _5)
        endif
        GdipSetStatus(this)
        }

    .operator AddClosedCurve :abs, :vararg {
        this.typeid(AddClosedCurve, _1)(_1, _2)
        }
    .operator AddClosedCurve?pPointF :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathClosedCurve(this.nativePath, _1, _2)
        else
            GdipAddPathClosedCurve2(this.nativePath, _1, _2, _3)
        endif
        GdipSetStatus(this)
        }
    .operator AddClosedCurve?pPoint :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathClosedCurveI(this.nativePath, _1, _2)
        else
            GdipAddPathClosedCurve2I(this.nativePath, _1, _2, _3)
        endif
        GdipSetStatus(this)
        }

    .operator AddRectangle :abs, :vararg {
        this.typeid(AddRectangle, _1)(_1, _2)
        }
    .operator AddRectangle?pRectF :ptr RectF, :vararg {
        GdipAddPathRectangle(this.nativePath,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height)
        GdipSetStatus(this)
        }
    .operator AddRectangle?pRect :ptr Rect, :vararg {
        GdipAddPathRectangleI(this.nativePath,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height)
        GdipSetStatus(this)
        }

    .operator AddRectangles :abs, :vararg {
        this.typeid(AddRectangles, _1)(_1, _2)
        }
    .operator AddRectangles?pRectF :vararg {
        GdipAddPathRectangles(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .operator AddRectangles?pRect :vararg {
        GdipAddPathRectanglesI(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .operator AddEllipse :abs, :vararg {
        this.typeid(AddEllipse, _1)(_1, _2)
        }
    .operator AddEllipse?flt :vararg {
        GdipAddPathEllipse(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .operator AddEllipse?i32 :vararg {
        GdipAddPathEllipseI(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .operator AddEllipse?r128   :vararg { this.AddEllipse?flt(_1) }
    .operator AddEllipse?real4  :vararg { this.AddEllipse?flt(_1) }
    .operator AddEllipse?r32    :vararg { this.AddEllipse?i32(_1) }
    .operator AddEllipse?sdword :vararg { this.AddEllipse?i32(_1) }

    .operator AddPie :abs, :vararg {
        this.typeid(AddPie, _1)(_1, _2)
        }
    .operator AddPie?flt :vararg {
        GdipAddPathPie(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .operator AddPie?i32 :vararg {
        GdipAddPathPieI(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .operator AddPie?r128   :vararg { this.AddPie?flt(_1) }
    .operator AddPie?real4  :vararg { this.AddPie?flt(_1) }
    .operator AddPie?r32    :vararg { this.AddPie?i32(_1) }
    .operator AddPie?sdword :vararg { this.AddPie?i32(_1) }

    .operator AddPolygon :abs, :vararg {
        this.typeid(AddPolygon, _1)(_1, _2)
        }
    .operator AddPolygon?pPointF :vararg {
        GdipAddPathPolygon(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .operator AddPolygon?pPoint :vararg {
        GdipAddPathPolygonI(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .operator AddPath :ptr GraphicsPath, :vararg {
        test    rdx,rdx
        cmovnz  rdx,[rdx].GraphicsPath.nativePath
        GdipAddPathPath(this.nativePath, rdx, _2)
        GdipSetStatus(this)
        }

    .operator AddString :abs, :abs, :abs, :abs, :abs, :abs, :abs, :vararg {
        this.typeid(AddString, _6)(_1, _2, _3, _4, _5, _6, _7, _8)
        }

    .operator AddString?pPointF :abs, :abs,\
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

    .operator AddString?pRectF :abs, :abs, :ptr FontFamily, :abs, :abs, :abs, :ptr StringFormat, :vararg {
        .if r9
            mov r9,[r9].FontFamily.nativeFamily
        .endif
        mov     rax,[rsp+7*8]
        test    rax,rax
        cmovnz  rax,[rax].StringFormat.nativeFormat

        GdipAddPathString(this.nativePath, _1, _2, r9, _4, _5, _6, rax)
        GdipSetStatus(this)
        }

    .operator AddString?pPoint :abs, :abs, :ptr FontFamily, :abs, :abs, :ptr Point, :ptr StringFormat, :vararg {

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

    .operator AddString?pRect :abs, :abs, :ptr FontFamily, :abs, :abs, :abs, :ptr StringFormat, :vararg {

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

    .operator Transform :ptr Matrix, :vararg {
        mov eax,Ok
        .if rdx
            GdipTransformPath(this.nativePath, [rdx].Matrix.nativeMatrix)
            GdipSetStatus(this)
        .endif
        }

    ;; This is not always the tightest bounds.

    .operator GetBounds :abs, :vararg {
        this.typeid(GetBounds, _1)(_1, _2)
        }
    .operator GetBounds?pRectF :ptr RectF, :ptr Matrix, :ptr Pen {
        }
    .operator GetBounds?pRect :ptr Rect, :ptr Matrix, :ptr Pen {
        }

    ;; Once flattened, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL the
    ;; identity matrix is assumed.

    .operator Flatten :ptr Matrix, :vararg {
        .if rdx
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        GdipFlattenPath(this.nativePath, rdx, _2)
        GdipSetStatus(this)
        }

    .operator Widen :ptr Pen, :ptr Matrix, :vararg {
        .if r8
            mov r8,[r8].Matrix.nativeMatrix
        .endif
        GdipWidenPath(this.nativePath, [rdx].Pen.nativePen, r8, _3)
        GdipSetStatus(this)
        }

    .operator Outline :ptr Matrix, :vararg {
        .if rdx
            mov rdx,[rdx].Matrix.nativeMatrix
        .endif
        GdipWindingModeOutline(this.nativePath, rdx, _2)
        GdipSetStatus(this)
        }

    ;; Once this is called, the resultant path is made of line segments and
    ;; the original path information is lost.  When matrix is NULL, the
    ;; identity matrix is assumed.

    .operator Warp :abs, :abs, :ptr RectF, :abs=<0>, :abs=<WarpModePerspective>, :vararg {

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

    .operator GetPointCount :vararg {
        mov this.scratch,0
        GdipGetPointCount(this.nativePath, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetPathTypes :vararg {
        GdipGetPathTypes(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .operator GetPathPoints :abs, :vararg {
        this.typeid(GetPathPoints, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator GetPathPoints?pPointF :abs, :vararg {
        GdipGetPathPoints(this.nativePath, _1, _2)
        }
    .operator GetPathPoints?pPoint :abs, :vararg {
        GdipGetPathPointsI(this.nativePath, _1, _2)
        }

    .operator GetLastStatus :vararg {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }

    .operator IsVisible :abs, :vararg {
        this.typeid(IsVisible, _1)(_1, _2)
        }
    .operator IsVisible?i32 :vararg {
        mov eax,NotImplemented
        }
    .operator IsVisible?flt :vararg {
        mov eax,NotImplemented
        }
    .operator IsVisible?pPoint :ptr Point, :vararg {
        this.IsVisible([rdx].Point.X, [rdx].Point.Y, _2)
        }
    .operator IsVisible?pPointF :ptr PointF, :vararg {
        this.IsVisible([rdx].PointF.X, [rdx].PointF.Y, _2)
        }

    .operator IsOutlineVisible :abs, :vararg {
        this.typeid(IsOutlineVisible, _1)(_1, _2)
        }
    .operator IsOutlineVisible?i32 :vararg {
        mov eax,NotImplemented
        }
    .operator IsOutlineVisible?flt :vararg {
        mov eax,NotImplemented
        }
    .operator IsOutlineVisible3 :ptr PointF, :vararg {
        this.IsOutlineVisible4([rdx].Point.X, [rdx].Point.Y, _2)
        }
    .operator IsOutlineVisible4 :ptr Point, :vararg {
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

    .operator GraphicsPathIterator :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx].GraphicsPath.nativePath
        .endif
        GdipCreatePathIter(addr this.nativeIterator, rdx)
        this.SetStatus()
        }

    .operator Release :vararg {
        GdipDeletePathIter(this.nativeIterator)
        }

    .operator SetNativeIterator :ptr GraphicsPath, :vararg {
        mov     this.nativeIterator,_1
        }
    .operator SetStatus :abs, :vararg {
        ifnb <_1>
        ifdif <_1>,<eax>
            mov eax,_1
        endif
        endif
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }


    .operator NextSubpath :abs, :vararg {
        this.typeid(NextSubpath, _1)(_1, _2)
        }
    .operator NextSubpath?psdword :vararg {
        GdipPathIterNextSubpath(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }
    .operator NextSubpath?pGraphicsPath :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx].GraphicsPath.nativePath
        .endif
        GdipPathIterNextSubpathPath(this.nativeIterator, addr this.scratch, rdx, _2)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator NextPathType :vararg {
        GdipPathIterNextPathType(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator NextMarker :abs, :vararg {
        this.typeid(NextMarker, _1)(_1, _2)
        }
    .operator NextMarker?psdword :vararg {
        GdipPathIterNextMarker(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }
    .operator NextMarker?pGraphicsPath :ptr GraphicsPath, :vararg {
        .if rdx
            mov rdx,[rdx].GraphicsPath.nativePath
        .endif
        GdipPathIterNextMarkerPath(this.nativeIterator, addr this.scratch, rdx, _2)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetCount :vararg {
        GdipPathIterGetCount(this.nativeIterator, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetSubpathCount :vararg {
        GdipPathIterGetSubpathCount(this.nativeIterator, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator HasCurve :vararg {
        GdipPathIterHasCurve(this.nativeIterator, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator Rewind :vararg {
        GdipPathIterRewind(this.nativeIterator)
        this.SetStatus()
        }

    .operator Enumerate :vararg {
        GdipPathIterEnumerate(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator CopyData :vararg {
        GdipPathIterCopyData(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetLastStatus :vararg {
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

    .operator PathGradientBrush :abs, :vararg {
        this.typeid(PathGradientBrush, _1)(_1, _2)
        mov this.lastResult,eax
        }

    .operator PathGradientBrush?pPointF :abs, :abs, :abs=<WrapModeClamp>, :vararg {
        GdipCreatePathGradient(_1, _2, _3, addr this.nativeBrush)
        }
    .operator PathGradientBrush?pPoint :abs, :abs, :abs=<WrapModeClamp>, :vararg {
        GdipCreatePathGradientI(_1, _2, _3, addr this.nativeBrush)
        }
    .operator PathGradientBrush?pGraphicsPath :ptr GraphicsPath, :vararg {
        mov rcx,rdx
        GdipCreatePathGradientFromPath([rcx].GraphicsPath.nativePath, addr this.nativeBrush)
        }

    .operator GetCenterColor :ptr Color, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetPathGradientCenterColor(this.nativeBrush, rdx)
        .endif
        GdipSetStatus(this)
        }

    .operator SetCenterColor :vararg {
        GdipSetPathGradientCenterColor(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetPointCount :vararg {
        GdipGetPathGradientPointCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetSurroundColorCount :vararg {
        GdipGetPathGradientSurroundColorCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetSurroundColors :ptr ARGB, :ptr SINT, :vararg {
        mov eax,InvalidParameter
        .if rdx && r8
            GdipGetPathGradientSurroundColorsWithCount(this.nativeBrush, rdx, r8)
        .endif
        GdipSetStatus(this)
        }

    .operator SetSurroundColors :ptr ARGB, :ptr SINT, :vararg {
        mov eax,InvalidParameter
        .if rdx && r8
            GdipSetPathGradientSurroundColorsWithCount(this.nativeBrush, rdx, r8)
        .endif
        GdipSetStatus(this)
        }

    .operator GetGraphicsPath :ptr GraphicsPath, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetPathGradientPath(this.nativeBrush, [rdx].GraphicsPath.nativePath)
        .endif
        GdipSetStatus(this)
        }

    .operator SetGraphicsPath :ptr GraphicsPath, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipSetPathGradientPath(this.nativeBrush, [rdx].GraphicsPath.nativePath)
        .endif
        GdipSetStatus(this)
        }

    .operator GetCenterPoint :abs, :vararg {
        this.typeid(GetCenterPoint, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator GetCenterPoint?pPointF :vararg {
        GdipGetPathGradientCenterPoint(this.nativeBrush, _1)
        }
    .operator GetCenterPoint?pPoint :vararg {
        GdipGetPathGradientCenterPointI(this.nativeBrush, _1)
        }

    .operator SetCenterPoint :abs, :vararg {
        this.typeid(SetCenterPoint, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator SetCenterPoint?pPointF :vararg {
        GdipSetPathGradientCenterPoint(this.nativeBrush, _1)
        }
    .operator SetCenterPoint?pPoint :vararg {
        GdipSetPathGradientCenterPointI(this.nativeBrush, _1)
        }

    .operator GetRectangle :abs, :vararg {
        this.typeid(GetRectangle, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .operator GetRectangle?pRectF :vararg {
        GdipGetPathGradientRect(this.nativeBrush, _1)
        }
    .operator GetRectangle?pRect :vararg {
        GdipGetPathGradientRectI(this.nativeBrush, _1)
        }

    .operator SetGammaCorrection :vararg {
        GdipSetPathGradientGammaCorrection(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetGammaCorrection :vararg {
        GdipGetPathGradientGammaCorrection(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetBlendCount :vararg {
        mov this.scratch,0
        GdipGetPathGradientBlendCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator GetBlend :vararg {
        GdipGetPathGradientBlend(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator SetBlend :vararg {
        GdipSetPathGradientBlend(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetInterpolationColorCount :vararg {
        mov this.scratch,0
        GdipGetPathGradientPresetBlendCount(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetInterpolationColors :ptr Color, :ptr REAL, :SINT, :vararg {

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

    .operator GetInterpolationColors :ptr Color, :ptr REAL, :SINT, :vararg {

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

    .operator SetBlendBellShape :abs, :abs=<1.0>, :vararg {
        GdipSetPathGradientSigmaBlend(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .operator SetBlendTriangularShape :abs, :abs=<1.0>, :vararg {
        GdipSetPathGradientLinearBlend(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .operator GetTransform :ptr Matrix, :vararg {
        GdipGetPathGradientTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .operator SetTransform :ptr Matrix, :vararg {
        GdipSetPathGradientTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .operator ResetTransform :vararg {
        GdipResetPathGradientTransform(this.nativeBrush)
        GdipSetStatus(this)
        }

    .operator MultiplyTransform :ptr Matrix, :abs=<MatrixOrderPrepend>, :vararg {
        GdipMultiplyPathGradientTransform(this.nativeBrush, [rdx].Matrix.nativeMatrix, _2)
        GdipSetStatus(this)
        }

    .operator TranslateTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipTranslatePathGradientTransform(this.nativeBrush, _1, _2, _3)
        GdipSetStatus(this)
        }

    .operator ScaleTransform :abs, :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipScalePathGradientTransform(this.nativeBrush, _1, _2, _3)
        GdipSetStatus(this)
        }

    .operator RotateTransform :abs, :abs=<MatrixOrderPrepend>, :vararg {
        GdipRotatePathGradientTransform(this.nativeBrush, _1, _2)
        GdipSetStatus(this)
        }

    .operator GetFocusScales :vararg {
        GdipGetPathGradientFocusScales(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator SetFocusScales :vararg {
        GdipSetPathGradientFocusScales(this.nativeBrush, _1)
        GdipSetStatus(this)
        }

    .operator GetWrapMode :vararg {
        GdipGetPathGradientWrapMode(this.nativeBrush, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetWrapMode :vararg {
        GdipSetPathGradientWrapMode(this.nativeBrush, _1)
        GdipSetStatus(this)
        }
    .ends

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; NOT _GRAPHICSPATH_HPP
