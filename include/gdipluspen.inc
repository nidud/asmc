ifndef _GDIPLUSPEN_H
_GDIPLUSPEN_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Pen class
;;
;; Pen(ARGB, REAL = 1.0)
;; Pen(Brush*, REAL = 1.0)
;;
;;--------------------------------------------------------------------------

.template Pen

    nativePen   ptr_t ?
    lastResult  Status ?
    scratch     int_t ?

    .operator Pen :abs, :vararg {
        this.typeid(Pen, _1)(_1, _2)
        mov this.lastResult,eax
        }
    .operator Pen?pBrush :ptr Brush, :abs=<1.0>, :vararg {
        mov rcx,rdx
        GdipCreatePen2([rcx].Brush.nativeBrush, _2, UnitWorld, addr this.nativePen)
        }
    .operator Pen?pColor :ptr Color, :abs=<1.0>, :vararg {
        mov rcx,rdx
        GdipCreatePen1([rcx].Color.Argb, _2, UnitWorld, addr this.nativePen)
        }
    .operator Pen?Color :abs, :abs=<1.0>, :vararg {
        GdipCreatePen1(_1, _2, UnitWorld, addr this.nativePen)
        }
    .operator Pen?i32 :abs, :abs=<1.0>, :vararg {
        GdipCreatePen1(_1, _2, UnitWorld, addr this.nativePen)
        }
    .operator Pen?r32   :vararg { this.Pen?i32(_1) }
    .operator Pen?dword :vararg { this.Pen?i32(_1) }

    .operator Pen?pPen :ptr Pen, :Status, :vararg {
        mov this.lastResult,r8d
        this.SetNativePen(rdx)
        }

    .operator Release :vararg {
        GdipDeletePen(this.nativePen)
        }

    .operator New :vararg {
        GdipDeletePen(this.nativePen)
        Pen_Pen(this, _1)
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

    .operator Clone :vararg {
        mov _1.lastResult,0
        GdipClonePen(this.nativePen, addr _1.nativePen)
        mov _1.lastResult,eax
        this.SetStatus()
        lea rax,_1
        }

    .operator SetWidth :vararg {
        GdipSetPenWidth(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetWidth :vararg {
        GdipGetPenWidth(this.nativePen, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    ;; Set/get line caps: start, end, and dash

    ;; Line cap and join APIs by using LineCap and LineJoin enums.

    .operator SetLineCap :vararg { ; :LineCap, :LineCap, :DashCap {
        GdipSetPenLineCap197819(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator SetStartCap :vararg { ; :LineCap {
        GdipSetPenStartCap(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator SetEndCap :vararg { ; :LineCap {
        GdipSetPenEndCap(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator SetDashCap :vararg { ; :DashCap {
        GdipSetPenDashCap197819(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetStartCap :vararg {
        .new PenCap:ptr
        GdipGetPenStartCap(this.nativePen, addr PenCap)
        GdipSetStatus(this)
        mov rax,PenCap
        }

    .operator GetEndCap :vararg { ; {
        .new PenCap:ptr
        GdipGetPenEndCap(this.nativePen, &PenCap)
        GdipSetStatus(this)
        mov rax,PenCap
        }

    .operator GetDashCap :vararg { ; {
        .new PenCap:ptr
        GdipGetPenDashCap197819(this.nativePen, &PenCap)
        GdipSetStatus(this)
        mov rax,PenCap
        }

    .operator SetLineJoin :vararg { ; :LineJoin {
        GdipSetPenLineJoin(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetLineJoin :vararg { ; {
        .new @LineJoin:ptr
        GdipGetPenLineJoin(this.nativePen, &@LineJoin)
        GdipSetStatus(this)
        mov rax,@LineJoin
        exitm<>
        }

    .operator SetCustomStartCap :ptr CustomLineCap, :vararg {
        test    rdx,rdx
        cmovnz  rdx,[rdx].CustomLineCap.nativeCap
        GdipSetPenCustomStartCap(this.nativePen, rdx)
        GdipSetStatus(this)
        }

    .operator GetCustomStartCap :ptr CustomLineCap, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetPenCustomStartCap(this.nativePen, rdx)
        .endif
        GdipSetStatus(this)
        }

    .operator SetCustomEndCap :ptr CustomLineCap, :vararg {
        test    rdx,rdx
        cmovnz  rdx,[rdx].CustomLineCap.nativeCap
        GdipSetPenCustomEndCap(this.nativePen, rdx)
        GdipSetStatus(this)
        }

    .operator GetCustomEndCap :ptr CustomLineCap, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetPenCustomEndCap(this.nativePen, rdx)
        .endif
        GdipSetStatus(this)
        }

    .operator SetMiterLimit :vararg { ; :REAL {
        GdipSetPenMiterLimit(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetMiterLimit :vararg {
        GdipGetPenLineJoin(this.nativePen, addr this.scratch)
        GdipSetStatus(this)
        movss xmm0,this.scratch
        }

    .operator SetAlignment :vararg { ; :PenAlignment {
        GdipSetPenMode(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetAlignment :vararg {
        GdipGetPenMode(this.nativePen, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetTransform :ptr Matrix, :vararg {
        GdipSetPenTransform(this.nativePen, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .operator GetTransform :ptr Matrix, :vararg {
        GdipGetPenTransform(this.nativePen, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .operator ResetTransform :vararg {
        GdipResetPenTransform(this.nativePen)
        GdipSetStatus(this)
        }

    .operator MultiplyTransform :ptr Matrix, :vararg {
        GdipMultiplyPenTransform(this.nativePen, [rdx].Matrix.nativeMatrix, _2)
        GdipSetStatus(this)
        }

    .operator TranslateTransform :vararg { ; :REAL, :REAL, :MatrixOrder {
        GdipTranslatePenTransform(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator ScaleTransform :vararg { ; :REAL, :REAL, :MatrixOrder {
        GdipScalePenTransform(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator RotateTransform :vararg { ; :REAL, :MatrixOrder {
        GdipRotatePenTransform(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetPenType :vararg {
        GdipGetPenFillType(this.nativePen, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .operator SetColor :vararg { ; :ptr Color {
        GdipSetPenColor(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator SetBrush :vararg { ; :ptr Brush {
        GdipSetPenBrushFill(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetColor :vararg { ; {

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

    .operator GetBrush :abs, :vararg {

        .new brush:Brush

        mov edx,this.GetPenType()
        xor eax,eax
        .switch pascal edx
        .case PenTypeSolidColor
           SolidBrush_SolidBrush(brush, _1)
        .case PenTypeHatchFill
           HatchBrush_HatchBrush(brush, _1)
        .case PenTypeTextureFill
           TextureBrush_TextureBrush(brush, _1)
        .case PenTypePathGradient
           Brush_Brush(brush, _1)
        .case PenTypeLinearGradient
           LinearGradientBrush_LinearGradientBrush(brush, _1)
        .endsw
        .if rax
            mov brush,rax
            .ifd GdipGetPenBrushFill(this.nativePen, rax)
                mov this.lastResult,eax
            .endif
            mov rax,brush
       .endif
       retm<rax>
       }

    .operator GetDashStyle :vararg { ; {

        .new PenDashStyle:int_t

        GdipGetPenDashStyle(this.nativePen, &PenDashStyle)
        GdipSetStatus(this)
        mov eax,PenDashStyle
        }

    .operator SetDashStyle :vararg { ; :DashStyle {
        GdipSetPenDashStyle(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetDashOffset :vararg { ; {

        .new DashOffset:int_t

        GdipGetPenDashOffset(this.nativePen, &DashOffset)
        GdipSetStatus(this)
        mov eax,DashOffset
        }

    .operator SetDashOffset :vararg { ; :REAL {
        GdipSetPenDashOffset([this].Pen.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator SetDashPattern :vararg { ; :ptr REAL, :int_t {
        GdipSetPenDashArray(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetDashPatternCount :vararg { ; {

       .new DashPatternCount:int_t

        mov DashPatternCount,0
        GdipGetPenDashCount(this.nativePen, &DashPatternCount)
        GdipSetStatus(this)
        mov eax,DashPatternCount
        }

    .operator GetDashPattern :ptr REAL, :int_t, :vararg { ; {
        .ifs rdx == NULL || r8d <= 0
            mov eax,InvalidParameter
        .else
            GdipGetPenDashArray(this.nativePen, rdx, r8d)
        .endif
        GdipSetStatus(this)
        }

    .operator SetCompoundArray :vararg { ; :ptr REAL, :int_t {
        GdipSetPenCompoundArray(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .operator GetCompoundArrayCount :vararg { ; {
        .new CompoundArrayCount:int_t
        mov CompoundArrayCount,0
        GdipGetPenCompoundCount(this.nativePen, &CompoundArrayCount)
        GdipSetStatus(this)
        mov eax,CompoundArrayCount
        }

    .operator GetCompoundArray :ptr REAL, :int_t, :vararg { ;
        .ifs rdx == NULL || r8d <= 0
            mov eax,InvalidParameter
        .else
            GdipGetPenCompoundArray(this.nativePen, rdx, r8d)
        .endif
        GdipSetStatus(this)
        }

    .operator GetLastStatus :vararg { ; {
        mov     eax,this.lastResult
        mov     this.lastResult,Ok
        }
    .operator SetNativePen :ptr Pen, :vararg {
        mov     this.nativePen,rdx
        }
    .ends
    GpPen typedef Pen

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
