ifndef _GDIPLUSPEN_H
define _GDIPLUSPEN_H
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Pen class
;;
;; Pen(ARGB, REAL = 1.0)
;; Pen(Brush*, REAL = 1.0)
;;
;;--------------------------------------------------------------------------

.template Pen fastcall

    nativePen   ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .static Pen :abs, :abs=<1.0> {
      ifidn <ptrBrush>,typeid(_1)
        LOADARGPTRCX(_1)
        GdipCreatePen2([rcx].Brush.nativeBrush, _2, UnitWorld, addr this.nativePen)
      elseifidn <ptrColor>,typeid(_1)
        LOADARGPTRCX(_1)
        GdipCreatePen1([rcx].Color.Argb, _2, UnitWorld, addr this.nativePen)
      else
        GdipCreatePen1(_1, _2, UnitWorld, addr this.nativePen)
      endif
        mov this.lastResult,eax
        }

    .static Release {
        GdipDeletePen(this.nativePen)
        }

    .static SetStatus watcall :size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static Clone :abs {
        mov _1.lastResult,0
        GdipClonePen(this.nativePen, addr _1.nativePen)
        mov _1.lastResult,eax
        this.SetStatus()
        lea rax,_1
        }

    .static SetWidth :abs {
        this.SetStatus(GdipSetPenWidth(this.nativePen, _1))
        }
    .static GetWidth {
        this.SetStatus(GdipGetPenWidth(this.nativePen, addr this.scratch))
        mov eax,this.scratch
        }

    ;; Set/get line caps: start, end, and dash

    ;; Line cap and join APIs by using LineCap and LineJoin enums.

    .static SetLineCap startCap:abs, endCap:abs, dashCap:abs {
        this.SetStatus(GdipSetPenLineCap197819(this.nativePen, startCap, endCap, dashCap))
        }
    .static SetStartCap :abs {
        this.SetStatus(GdipSetPenStartCap(this.nativePen, _1))
        }
    .static SetEndCap :abs {
        this.SetStatus(GdipSetPenEndCap(this.nativePen, _1))
        }
    .static SetDashCap :abs {
        this.SetStatus(GdipSetPenDashCap197819(this.nativePen, _1))
        }
    .static GetStartCap {
       .new PenCap:ptr
        this.SetStatus(GdipGetPenStartCap(this.nativePen, addr PenCap))
        mov rax,PenCap
        }
    .static GetEndCap {
       .new PenCap:ptr
        this.SetStatus(GdipGetPenEndCap(this.nativePen, &PenCap))
        mov rax,PenCap
        }
    .static GetDashCap {
       .new PenCap:ptr
        this.SetStatus(GdipGetPenDashCap197819(this.nativePen, &PenCap))
        mov rax,PenCap
        }
    .static SetLineJoin :abs {
        this.SetStatus(GdipSetPenLineJoin(this.nativePen, _1))
        }
    .static GetLineJoin {
       .new lineJoin:ptr
        this.SetStatus(GdipGetPenLineJoin(this.nativePen, &lineJoin))
        mov rax,lineJoin
        }
    .static SetCustomStartCap :ptr CustomLineCap {
        .if _1
            mov _1,[_1].CustomLineCap.nativeCap
        .endif
        this.SetStatus(GdipSetPenCustomStartCap(this.nativePen, _1))
        }
    .static GetCustomStartCap :ptr CustomLineCap {
        mov eax,InvalidParameter
        .if _1
            GdipGetPenCustomStartCap(this.nativePen, _1)
        .endif
        this.SetStatus()
        }
    .static SetCustomEndCap :ptr CustomLineCap {
        .if _1
            mov _1,[_1].CustomLineCap.nativeCap
        .endif
        this.SetStatus(GdipSetPenCustomEndCap(this.nativePen, _1))
        }
    .static GetCustomEndCap :ptr CustomLineCap {
        mov eax,InvalidParameter
        .if _1
            GdipGetPenCustomEndCap(this.nativePen, _1)
        .endif
        this.SetStatus()
        }
    .static SetMiterLimit :abs {
        this.SetStatus(GdipSetPenMiterLimit(this.nativePen, _1))
        }
    .static GetMiterLimit {
        this.SetStatus(GdipGetPenLineJoin(this.nativePen, addr this.scratch))
        movss xmm0,this.scratch
        }
    .static SetAlignment :abs {
        this.SetStatus(GdipSetPenMode(this.nativePen, _1))
        }
    .static GetAlignment :vararg {
        this.SetStatus(GdipGetPenMode(this.nativePen, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetTransform :ptr Matrix {
        this.SetStatus(GdipSetPenTransform(this.nativePen, [_1].Matrix.nativeMatrix))
        }
    .static GetTransform :ptr Matrix {
        this.SetStatus(GdipGetPenTransform(this.nativePen, [_1].Matrix.nativeMatrix))
        }
    .static ResetTransform {
        this.SetStatus(GdipResetPenTransform(this.nativePen))
        }
    .static MultiplyTransform :ptr Matrix, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipMultiplyPenTransform(this.nativePen, [_1].Matrix.nativeMatrix, order))
        }
    .static TranslateTransform x:abs, y:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipTranslatePenTransform(this.nativePen, x, y, order))
        }
    .static ScaleTransform x:abs, y:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipScalePenTransform(this.nativePen, x, y, order))
        }
    .static RotateTransform angle:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipRotatePenTransform(this.nativePen, angle, order))
        }
    .static GetPenType {
        this.SetStatus(GdipGetPenFillType(this.nativePen, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetColor :abs {
        this.SetStatus(GdipSetPenColor(this.nativePen, _1))
        }
    .static SetBrush :abs {
        this.SetStatus(GdipSetPenBrushFill(this.nativePen, _1))
        }

    .static GetColor {
        .if this.GetPenType() != PenTypeSolidColor
            mov this.lastResult,WrongState
            xor eax,eax
        .else
            .ifd GdipGetPenColor(this.nativePen, addr this.scratch)
                mov this.lastResult,eax
                xor eax,eax
            .else
                mov eax,this.scratch
            .endif
        .endif
        }

    .static GetBrush {
      local brush
       .new brush:Brush()
        .ifd GdipGetPenBrushFill(this.nativePen, addr brush)
            mov this.lastResult,eax
        .endif
        lea rax,brush
        }

    .static GetDashStyle {
        this.SetStatus(GdipGetPenDashStyle(this.nativePen, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetDashStyle :abs {
        this.SetStatus(GdipSetPenDashStyle(this.nativePen, _1))
        }
    .static GetDashOffset {
        this.SetStatus(GdipGetPenDashOffset(this.nativePen, addr this.scratch))
        mov eax,this.scratch
        }
    .static SetDashOffset :abs {
        this.SetStatus(GdipSetPenDashOffset(this.nativePen, _1))
        }
    .static SetDashPattern :abs, :abs {
        this.SetStatus(GdipSetPenDashArray(this.nativePen, _1, _2))
        }
    .static GetDashPatternCount {
        mov this.scratch,0
        this.SetStatus(GdipGetPenDashCount(this.nativePen, addr this.scratch))
        mov eax,this.scratch
        }
    .static GetDashPattern :ptr REAL, :int_t {
        .ifs _1 == NULL || _2 <= 0
            mov eax,InvalidParameter
        .else
            GdipGetPenDashArray(this.nativePen, _1, _2)
        .endif
        this.SetStatus()
        }
    .static SetCompoundArray :abs, :abs {
        this.SetStatus(GdipSetPenCompoundArray(this.nativePen, _1, _2))
        }
    .static GetCompoundArrayCount {
        mov this.scratch,0
        this.SetStatus(GdipGetPenCompoundCount(this.nativePen, addr this.scratch))
        mov eax,this.scratch
        }
    .static GetCompoundArray :ptr REAL, :int_t {
        .ifs _1 == NULL || _2 <= 0
            mov eax,InvalidParameter
        .else
            GdipGetPenCompoundArray(this.nativePen, _1, _2)
        .endif
        this.SetStatus()
        }
    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }
    .static SetNativePen :ptr Pen {
        mov this.nativePen,_1
        }
    .ends
    GpPen typedef Pen

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
