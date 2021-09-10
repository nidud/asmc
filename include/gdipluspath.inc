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
            this.typeid(GraphicsPath_, _1)(_1, _2)
        else
            this.GraphicsPath_imm(FillModeAlternate)
        endif
        mov this.lastResult,eax
        }
    .inline GraphicsPath_imm :abs {
        GdipCreatePath(_1, this)
        }
    .inline GraphicsPath_ptrPointF :abs, :abs, :abs, :abs=<FillModeAlternate> {
        GdipCreatePath2(_1, _2, _3, _4, this)
        }
    .inline GraphicsPath_ptrPoint :abs, :abs, :abs, :abs=<FillModeAlternate> {
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
        this.typeid(AddLine_, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline AddLine_flt :vararg {
        GdipAddPathLine(this.nativePath, _1)
        }
    .inline AddLine_imm :vararg {
        GdipAddPathLineI(this.nativePath, _1)
        }
    .inline AddLine_oword   :vararg { this.AddLine_flt(_1) }
    .inline AddLine_real4   :vararg { this.AddLine_flt(_1) }
    .inline AddLine_dword   :vararg { this.AddLine_imm(_1) }
    .inline AddLine_sdword  :vararg { this.AddLine_imm(_1) }

    .inline AddLine_ptrPointF :ptr PointF, :ptr PointF, :vararg {
        this.AddLine_flt([rdx].PointF.X, [rdx].PointF.Y, [r8].PointF.X, [r8].PointF.Y)
        }
    .inline AddLine_ptrPoint :ptr Point, :ptr Point, :vararg {
        this.AddLine_imm([rdx].Point.X, [rdx].Point.Y, [r8].Point.X, [r8].Point.Y)
        }

    .inline AddLines :abs, :vararg {
        this.typeid(AddLines_, _1)(_1, _2)
        this.SetStatus()
        }
    .inline AddLines_ptrPointF :vararg {
        GdipAddPathLine2(this.nativePath, _1)
        }
    .inline AddLines_ptrPoint :vararg {
        GdipAddPathLine2I(this.nativePath, _1)
        }

    .inline AddArc :abs, :vararg {
        this.typeid(AddArc_, _1)(_1, _2)
        this.SetStatus()
        }
    .inline AddArc_flt :vararg {
        GdipAddPathArc(this.nativePath, _1)
        }
    .inline AddArc_imm :vararg {
        GdipAddPathArcI(this.nativePath, _1)
        }
    .inline AddArc_oword  :vararg { this.AddArc_flt(_1) }
    .inline AddArc_real4  :vararg { this.AddArc_flt(_1) }
    .inline AddArc_dword  :vararg { this.AddArc_imm(_1) }
    .inline AddArc_sdword :vararg { this.AddArc_imm(_1) }

    .inline AddArc_ptrRectF :ptr RectF, :vararg {
        GdipAddPathArc(this.nativePath, \
            [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height, _2)
        }
    .inline AddArc_ptrRect :ptr Rect, :vararg {
        GdipAddPathArcI(this.nativePath, \
            [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height, _2)
        }

    .inline AddBezier :abs, :vararg {
        this.typeid(AddBezier_, _1)(_1, _2)
        this.SetStatus()
        }
    .inline AddBezier_oword  :vararg { this.AddBezier_flt(_1) }
    .inline AddBezier_real4  :vararg { this.AddBezier_flt(_1) }
    .inline AddBezier_dword  :vararg { this.AddBezier_imm(_1) }
    .inline AddBezier_sdword :vararg { this.AddBezier_imm(_1) }

    .inline AddBezier_flt :vararg {
        GdipAddPathBezier(this.nativePath, _1)
        }
    .inline AddBezier_imm :vararg {
        GdipAddPathBezierI(this.nativePath, _1)
        }
    .inline AddBezier_ptrPointF :ptr PointF, :ptr PointF, :ptr PointF, :ptr PointF, :vararg {
        mov r10,[rsp+8*4]
        GdipAddPathBezier(this.nativePath, [rdx].PointF.X, [rdx].PointF.Y,\
            [r8].PointF.X, [r8].PointF.Y, [r9].PointF.X, [r9].PointF.Y, [r10].PointF.X, [r10].PointF.Y)
        }
    .inline AddBezier_ptrPoint :ptr Point, :ptr Point, :ptr Point, :ptr Point, :vararg {
        mov r10,[rsp+8*4]
        GdipAddPathBezierI(this.nativePath, [rdx].Point.X, [rdx].Point.Y,\
            [r8].Point.X, [r8].Point.Y, [r9].Point.X, [r9].Point.Y, [r10].Point.X, [r10].Point.Y)
        }

    .inline AddBeziers :abs, :vararg {
        this.typeid(AddBeziers_, _1)(_1, _2)
        }
    .inline AddBeziers_ptrPointF :vararg {
        GdipAddPathBeziers(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddBeziers_ptrPoint :vararg {
        GdipAddPathBeziersI(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .inline AddCurve :abs, :vararg {
        this.typeid(AddCurve_, _1)(_1, _2)
        }
    .inline AddCurve_ptrPointF :abs, :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathCurve(this.nativePath, _1, _2)
        elseifb <_4>
            GdipAddPathCurve2(this.nativePath, _1, _2, _3)
        else
            GdipAddPathCurve3(this.nativePath, _1, _2, _3, _4, _5)
        endif
        GdipSetStatus(this)
        }
    .inline AddCurve_ptrPoint :abs, :abs, :abs, :abs, :vararg {
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
        this.typeid(AddClosedCurve_, _1)(_1, _2)
        }
    .inline AddClosedCurve_ptrPointF :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathClosedCurve(this.nativePath, _1, _2)
        else
            GdipAddPathClosedCurve2(this.nativePath, _1, _2, _3)
        endif
        GdipSetStatus(this)
        }
    .inline AddClosedCurve_ptrPoint :abs, :abs, :abs, :vararg {
        ifb <_3>
            GdipAddPathClosedCurveI(this.nativePath, _1, _2)
        else
            GdipAddPathClosedCurve2I(this.nativePath, _1, _2, _3)
        endif
        GdipSetStatus(this)
        }

    .inline AddRectangle :abs, :vararg {
        this.typeid(AddRectangle_, _1)(_1, _2)
        }
    .inline AddRectangle_imm :vararg {
        GdipAddPathRectangleI(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddRectangle_dword  :vararg { this.AddRectangle_imm(_1) }
    .inline AddRectangle_sdword :vararg { this.AddRectangle_imm(_1) }
    .inline AddRectangle_ptrRectF :ptr RectF, :vararg {
        GdipAddPathRectangle(this.nativePath,\
                [rdx].RectF.X, [rdx].RectF.Y, [rdx].RectF.Width, [rdx].RectF.Height)
        GdipSetStatus(this)
        }
    .inline AddRectangle_ptrRect :ptr Rect, :vararg {
        GdipAddPathRectangleI(this.nativePath,\
                [rdx].Rect.X, [rdx].Rect.Y, [rdx].Rect.Width, [rdx].Rect.Height)
        GdipSetStatus(this)
        }

    .inline AddRectangles :abs, :vararg {
        this.typeid(AddRectangles_, _1)(_1, _2)
        }
    .inline AddRectangles_ptrRectF :vararg {
        GdipAddPathRectangles(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddRectangles_ptrRect :vararg {
        GdipAddPathRectanglesI(this.nativePath, _1)
        GdipSetStatus(this)
        }

    .inline AddEllipse :abs, :vararg {
        this.typeid(AddEllipse_, _1)(_1, _2)
        }
    .inline AddEllipse_flt :vararg {
        GdipAddPathEllipse(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddEllipse_imm :vararg {
        GdipAddPathEllipseI(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddEllipse_oword  :vararg { this.AddEllipse_flt(_1) }
    .inline AddEllipse_real4  :vararg { this.AddEllipse_flt(_1) }
    .inline AddEllipse_dword  :vararg { this.AddEllipse_imm(_1) }
    .inline AddEllipse_sdword :vararg { this.AddEllipse_imm(_1) }

    .inline AddPie :abs, :vararg {
        this.typeid(AddPie_, _1)(_1, _2)
        }
    .inline AddPie_flt :vararg {
        GdipAddPathPie(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddPie_imm :vararg {
        GdipAddPathPieI(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddPie_oword  :vararg { this.AddPie_flt(_1) }
    .inline AddPie_real4  :vararg { this.AddPie_flt(_1) }
    .inline AddPie_dword  :vararg { this.AddPie_imm(_1) }
    .inline AddPie_sdword :vararg { this.AddPie_imm(_1) }

    .inline AddPolygon :abs, :vararg {
        this.typeid(AddPolygon_, _1)(_1, _2)
        }
    .inline AddPolygon_ptrPointF :vararg {
        GdipAddPathPolygon(this.nativePath, _1)
        GdipSetStatus(this)
        }
    .inline AddPolygon_ptrPoint :vararg {
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
        this.typeid(AddString_, _6)(_1, _2, _3, _4, _5, _6, _7, _8)
        }

    .inline AddString_ptrPointF :abs, :abs,\
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

    .inline AddString_ptrRectF :abs, :abs, :ptr FontFamily, :abs, :abs, :abs, :ptr StringFormat, :vararg {
        .if r9
            mov r9,[r9].FontFamily.nativeFamily
        .endif
        mov     rax,[rsp+7*8]
        test    rax,rax
        cmovnz  rax,[rax].StringFormat.nativeFormat

        GdipAddPathString(this.nativePath, _1, _2, r9, _4, _5, _6, rax)
        GdipSetStatus(this)
        }

    .inline AddString_ptrPoint :abs, :abs, :ptr FontFamily, :abs, :abs, :ptr Point, :ptr StringFormat, :vararg {

       .new rect:Rect

        mov r10,_6
        mov rect.X,[r10].PointF.X
        mov rect.Y,[r10].PointF.Y
        mov rect.X,0.0
        mov rect.X,0.0
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

    .inline AddString_ptrRect :abs, :abs, :ptr FontFamily, :abs, :abs, :abs, :ptr StringFormat, :vararg {

        .if r9
            mov r9,[r9].FontFamily.nativeFamily
        .endif
        mov r10,[rsp+7*8]
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
        this.typeid(GetBounds_, _1)(_1, _2)
        }
    .inline GetBounds_ptrRectF :ptr RectF, :ptr Matrix, :ptr Pen {
        }
    .inline GetBounds_ptrRect :ptr Rect, :ptr Matrix, :ptr Pen {
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
        this.typeid(GetPathPoints_, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline GetPathPoints_ptrPointF :abs, :vararg {
        GdipGetPathPoints(this.nativePath, _1, _2)
        }
    .inline GetPathPoints_ptrPoint :abs, :vararg {
        GdipGetPathPointsI(this.nativePath, _1, _2)
        }

    .inline GetLastStatus :vararg {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }

    .inline IsVisible :abs, :vararg {
        this.typeid(IsVisible_, _1)(_1, _2)
        }
    .inline IsVisible_imm :vararg {
        mov eax,NotImplemented
        }
    .inline IsVisible_flt :vararg {
        mov eax,NotImplemented
        }
    .inline IsVisible_ptrPoint :ptr Point, :vararg {
        this.IsVisible([rdx].Point.X, [rdx].Point.Y, _2)
        }
    .inline IsVisible_ptrPointF :ptr PointF, :vararg {
        this.IsVisible([rdx].PointF.X, [rdx].PointF.Y, _2)
        }

    .inline IsOutlineVisible :abs, :vararg {
        this.typeid(IsOutlineVisible_, _1)(_1, _2)
        }
    .inline IsOutlineVisible_imm :vararg {
        mov eax,NotImplemented
        }
    .inline IsOutlineVisible_flt :vararg {
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
        this.typeid(NextSubpath_, _1)(_1, _2)
        }
    .inline NextSubpath_ptrsdword :vararg {
        GdipPathIterNextSubpath(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline NextSubpath_ptrGraphicsPath :ptr GraphicsPath, :vararg {
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
        this.typeid(NextMarker_, _1)(_1, _2)
        }
    .inline NextMarker_ptrsdword :vararg {
        GdipPathIterNextMarker(this.nativeIterator, addr this.scratch, _1)
        this.SetStatus()
        mov eax,this.scratch
        }
    .inline NextMarker_ptrGraphicsPath :ptr GraphicsPath, :vararg {
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
        this.typeid(PathGradientBrush_, _1)(_1, _2)
        mov this.lastResult,eax
        }

    .inline PathGradientBrush_ptrPointF :abs, :abs, :abs=<WrapModeClamp>, :vararg {
        GdipCreatePathGradient(_1, _2, _3, addr this.nativeBrush)
        }
    .inline PathGradientBrush_ptrPoint :abs, :abs, :abs=<WrapModeClamp>, :vararg {
        GdipCreatePathGradientI(_1, _2, _3, addr this.nativeBrush)
        }
    .inline PathGradientBrush_ptrGraphicsPath :ptr GraphicsPath, :vararg {
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
        this.typeid(GetCenterPoint_, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline GetCenterPoint_ptrPointF :vararg {
        GdipGetPathGradientCenterPoint(this.nativeBrush, _1)
        }
    .inline GetCenterPoint_ptrPoint :vararg {
        GdipGetPathGradientCenterPointI(this.nativeBrush, _1)
        }

    .inline SetCenterPoint :abs, :vararg {
        this.typeid(SetCenterPoint_, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline SetCenterPoint_ptrPointF :vararg {
        GdipSetPathGradientCenterPoint(this.nativeBrush, _1)
        }
    .inline SetCenterPoint_ptrPoint :vararg {
        GdipSetPathGradientCenterPointI(this.nativeBrush, _1)
        }

    .inline GetRectangle :abs, :vararg {
        this.typeid(GetRectangle_, _1)(_1, _2)
        GdipSetStatus(this)
        }
    .inline GetRectangle_ptrRectF :vararg {
        GdipGetPathGradientRect(this.nativeBrush, _1)
        }
    .inline GetRectangle_ptrRect :vararg {
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
