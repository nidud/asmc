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

    .inline Pen :abs, :vararg {
        this.typeid(Pen_, _1)(_1, _2)
        mov this.lastResult,eax
        }
    .inline Pen_ptrBrush :ptr Brush, :abs=<1.0>, :vararg {
        mov rcx,rdx
        GdipCreatePen2([rcx].Brush.nativeBrush, _2, UnitWorld, addr this.nativePen)
        }
    .inline Pen_ptrColor :ptr Color, :abs=<1.0>, :vararg {
        mov rcx,rdx
        GdipCreatePen1([rcx].Color.Argb, _2, UnitWorld, addr this.nativePen)
        }
    .inline Pen_Color :abs, :abs=<1.0>, :vararg {
        GdipCreatePen1(_1, _2, UnitWorld, addr this.nativePen)
        }
    .inline Pen_imm :abs, :abs=<1.0>, :vararg {
        GdipCreatePen1(_1, _2, UnitWorld, addr this.nativePen)
        }
    .inline Pen_dword :vararg { this.Pen_imm(_1) }

    .inline Pen_ptrPen :ptr Pen, :Status, :vararg {
        mov this.lastResult,r8d
        this.SetNativePen(rdx)
        }

    .inline Release :vararg {
        GdipDeletePen(this.nativePen)
        }

    .inline New :vararg {
        GdipDeletePen(this.nativePen)
        Pen_Pen(this, _1)
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

    .inline Clone :vararg {
        mov _1.lastResult,0
        GdipClonePen(this.nativePen, addr _1.nativePen)
        mov _1.lastResult,eax
        this.SetStatus()
        lea rax,_1
        }

    .inline SetWidth :vararg {
        GdipSetPenWidth(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetWidth :vararg {
        GdipGetPenWidth(this.nativePen, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    ;; Set/get line caps: start, end, and dash

    ;; Line cap and join APIs by using LineCap and LineJoin enums.

    .inline SetLineCap :vararg { ; :LineCap, :LineCap, :DashCap {
        GdipSetPenLineCap197819(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline SetStartCap :vararg { ; :LineCap {
        GdipSetPenStartCap(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline SetEndCap :vararg { ; :LineCap {
        GdipSetPenEndCap(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline SetDashCap :vararg { ; :DashCap {
        GdipSetPenDashCap197819(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetStartCap :vararg {
        .new PenCap:ptr
        GdipGetPenStartCap(this.nativePen, addr PenCap)
        GdipSetStatus(this)
        mov rax,PenCap
        }

    .inline GetEndCap :vararg { ; {
        .new PenCap:ptr
        GdipGetPenEndCap(this.nativePen, &PenCap)
        GdipSetStatus(this)
        mov rax,PenCap
        }

    .inline GetDashCap :vararg { ; {
        .new PenCap:ptr
        GdipGetPenDashCap197819(this.nativePen, &PenCap)
        GdipSetStatus(this)
        mov rax,PenCap
        }

    .inline SetLineJoin :vararg { ; :LineJoin {
        GdipSetPenLineJoin(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetLineJoin :vararg { ; {
        .new @LineJoin:ptr
        GdipGetPenLineJoin(this.nativePen, &@LineJoin)
        GdipSetStatus(this)
        mov rax,@LineJoin
        exitm<>
        }

    .inline SetCustomStartCap :ptr CustomLineCap, :vararg {
        test    rdx,rdx
        cmovnz  rdx,[rdx].CustomLineCap.nativeCap
        GdipSetPenCustomStartCap(this.nativePen, rdx)
        GdipSetStatus(this)
        }

    .inline GetCustomStartCap :ptr CustomLineCap, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetPenCustomStartCap(this.nativePen, rdx)
        .endif
        GdipSetStatus(this)
        }

    .inline SetCustomEndCap :ptr CustomLineCap, :vararg {
        test    rdx,rdx
        cmovnz  rdx,[rdx].CustomLineCap.nativeCap
        GdipSetPenCustomEndCap(this.nativePen, rdx)
        GdipSetStatus(this)
        }

    .inline GetCustomEndCap :ptr CustomLineCap, :vararg {
        mov eax,InvalidParameter
        .if rdx
            GdipGetPenCustomEndCap(this.nativePen, rdx)
        .endif
        GdipSetStatus(this)
        }

    .inline SetMiterLimit :vararg { ; :REAL {
        GdipSetPenMiterLimit(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetMiterLimit :vararg {
        GdipGetPenLineJoin(this.nativePen, addr this.scratch)
        GdipSetStatus(this)
        movss xmm0,this.scratch
        }

    .inline SetAlignment :vararg { ; :PenAlignment {
        GdipSetPenMode(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetAlignment :vararg {
        GdipGetPenMode(this.nativePen, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetTransform :ptr Matrix, :vararg {
        GdipSetPenTransform(this.nativePen, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .inline GetTransform :ptr Matrix, :vararg {
        GdipGetPenTransform(this.nativePen, [rdx].Matrix.nativeMatrix)
        GdipSetStatus(this)
        }

    .inline ResetTransform :vararg {
        GdipResetPenTransform(this.nativePen)
        GdipSetStatus(this)
        }

    .inline MultiplyTransform :ptr Matrix, :vararg {
        GdipMultiplyPenTransform(this.nativePen, [rdx].Matrix.nativeMatrix, _2)
        GdipSetStatus(this)
        }

    .inline TranslateTransform :vararg { ; :REAL, :REAL, :MatrixOrder {
        GdipTranslatePenTransform(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline ScaleTransform :vararg { ; :REAL, :REAL, :MatrixOrder {
        GdipScalePenTransform(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline RotateTransform :vararg { ; :REAL, :MatrixOrder {
        GdipRotatePenTransform(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetPenType :vararg {
        GdipGetPenFillType(this.nativePen, addr this.scratch)
        GdipSetStatus(this)
        mov eax,this.scratch
        }

    .inline SetColor :vararg { ; :ptr Color {
        GdipSetPenColor(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline SetBrush :vararg { ; :ptr Brush {
        GdipSetPenBrushFill(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetColor :vararg { ; {

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

    .inline GetBrush :abs, :vararg {

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

    .inline GetDashStyle :vararg { ; {

        .new PenDashStyle:int_t

        GdipGetPenDashStyle(this.nativePen, &PenDashStyle)
        GdipSetStatus(this)
        mov eax,PenDashStyle
        }

    .inline SetDashStyle :vararg { ; :DashStyle {
        GdipSetPenDashStyle(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetDashOffset :vararg { ; {

        .new DashOffset:int_t

        GdipGetPenDashOffset(this.nativePen, &DashOffset)
        GdipSetStatus(this)
        mov eax,DashOffset
        }

    .inline SetDashOffset :vararg { ; :REAL {
        GdipSetPenDashOffset([this].Pen.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline SetDashPattern :vararg { ; :ptr REAL, :int_t {
        GdipSetPenDashArray(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetDashPatternCount :vararg { ; {

       .new DashPatternCount:int_t

        mov DashPatternCount,0
        GdipGetPenDashCount(this.nativePen, &DashPatternCount)
        GdipSetStatus(this)
        mov eax,DashPatternCount
        }

    .inline GetDashPattern :ptr REAL, :int_t, :vararg { ; {
        .ifs rdx == NULL || r8d <= 0
            mov eax,InvalidParameter
        .else
            GdipGetPenDashArray(this.nativePen, rdx, r8d)
        .endif
        GdipSetStatus(this)
        }

    .inline SetCompoundArray :vararg { ; :ptr REAL, :int_t {
        GdipSetPenCompoundArray(this.nativePen, _1)
        GdipSetStatus(this)
        }

    .inline GetCompoundArrayCount :vararg { ; {
        .new CompoundArrayCount:int_t
        mov CompoundArrayCount,0
        GdipGetPenCompoundCount(this.nativePen, &CompoundArrayCount)
        GdipSetStatus(this)
        mov eax,CompoundArrayCount
        }

    .inline GetCompoundArray :ptr REAL, :int_t, :vararg { ;
        .ifs rdx == NULL || r8d <= 0
            mov eax,InvalidParameter
        .else
            GdipGetPenCompoundArray(this.nativePen, rdx, r8d)
        .endif
        GdipSetStatus(this)
        }

    .inline GetLastStatus :vararg { ; {
        mov     eax,this.lastResult
        mov     this.lastResult,Ok
        }
    .inline SetNativePen :ptr Pen, :vararg {
        mov     this.nativePen,rdx
        }
    .ends
    GpPen typedef Pen

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
