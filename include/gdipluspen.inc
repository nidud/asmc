ifndef _GDIPLUSPEN_H
_GDIPLUSPEN_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;;--------------------------------------------------------------------------
;; Pen class
;;--------------------------------------------------------------------------

.template Pen

    nativePen   ptr_t ?
    lastResult  Status ?

    Pen proc :vararg
    Pen_Pen macro this, _1, _2:=<1.0>, _3:=<UnitWorld>
        if typeof(_1) eq 8
            GdipCreatePen2(_1, _2, _3, rcx)
        else
            GdipCreatePen1(_1, _2, _3, rcx)
        endif
        mov this.lastResult,eax
        lea rax,this
        retm<rax>
        endm

    .operator Release {
        GdipDeletePen([this].Pen.nativePen)
        exitm<>
        }

    .operator New :vararg {
        GdipDeletePen(this.nativePen)
        exitm<Pen_Pen(this, _1)>
        }

    .operator SetStatus :Status {
        mov     eax,[this].Pen.lastResult
        and     _1,_1
        cmovnz  eax,_1
        mov     [this].Pen.lastResult,eax
        retm    <eax>
        }

    .operator Clone :vararg {
        .new @clone:ptr
        .if GdipAlloc(Pen)
            mov @clone,rax
            .ifd GdipClonePen(this.nativePen, rax)
                mov this.lastResult,eax
            .endif
            mov rcx,@clone
            mov [rcx].Pen.lastResult,eax
            mov rax,rcx
        .endif
        retm<rax>
        }

    .operator SetWidth :vararg {
        .ifs GdipSetPenWidth(this.nativePen, _1)
            mov this.lastResult,eax
        .endif
        retm<eax>
        }

    .operator GetWidth :vararg {
        .new width:int_t
        .if GdipGetPenWidth(this.nativePen, &width)
            mov this.lastResult,eax
        .endif
        mov eax,width
        retm <eax>
        }

    ;; Set/get line caps: start, end, and dash

    ;; Line cap and join APIs by using LineCap and LineJoin enums.

    .operator SetLineCap :vararg { ; :LineCap, :LineCap, :DashCap {
        .ifd GdipSetPenLineCap197819(this.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetStartCap :vararg { ; :LineCap {
        .ifd GdipSetPenStartCap(this.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetEndCap :vararg { ; :LineCap {
        .ifd GdipSetPenEndCap([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetDashCap :vararg { ; :DashCap {
        .ifd GdipSetPenDashCap197819([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetStartCap :vararg {
        .new PenCap:ptr
        .ifd GdipGetPenStartCap([rcx].Pen.nativePen, &PenCap)
            mov this.lastResult,eax
        .endif
        exitm<mov rax,PenCap>
        }

    .operator GetEndCap :vararg { ; {
        .new PenCap:ptr
        .ifd GdipGetPenEndCap([rcx].Pen.nativePen, &PenCap)
            mov this.lastResult,eax
        .endif
        exitm<mov rax,PenCap>
        }

    .operator GetDashCap :vararg { ; {
        .new PenCap:ptr
        .ifd GdipGetPenDashCap197819([rcx].Pen.nativePen, &PenCap)
            mov this.lastResult,eax
        .endif
        exitm<mov rax,PenCap>
        }

    .operator SetLineJoin :vararg { ; :LineJoin {
        .ifd GdipSetPenLineJoin([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetLineJoin :vararg { ; {
        .new @LineJoin:ptr
        .ifd GdipGetPenLineJoin([rcx].Pen.nativePen, &@LineJoin)
            mov this.lastResult,eax
        .endif
        mov rax,@LineJoin
        exitm<>
        }

    .operator SetCustomStartCap :ptr CustomLineCap, :vararg {
        xor eax,eax
        .if rdx
            mov rax,[rdx].CustomLineCap.nativeCap
        .endif
        .ifd GdipSetPenCustomStartCap([rcx].Pen.nativePen, rax)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetCustomStartCap :ptr CustomLineCap, :vararg {
        .if !rdx
            mov eax,InvalidParameter
            mov this.lastResult,eax
        .elseif GdipGetPenCustomStartCap([rcx].Pen.nativePen, rdx)
            mov this.lastResult,eax
        .endif
        retm <eax>
        }

    .operator SetCustomEndCap :ptr CustomLineCap, :vararg {
        xor eax,eax
        .if rdx
            mov rax,[rdx].CustomLineCap.nativeCap
        .endif
        .ifd GdipSetPenCustomEndCap([rcx].Pen.nativePen, rax)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetCustomEndCap :ptr CustomLineCap, :vararg {
        .if !rdx
            mov eax,InvalidParameter
            mov this.lastResult,eax
        .elseif GdipGetPenCustomEndCap([rcx].Pen.nativePen, rdx)
            mov this.lastResult,eax
        .endif
        retm<eax>
        }

    .operator SetMiterLimit :vararg { ; :REAL {
        .ifd GdipSetPenMiterLimit([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetMiterLimit :vararg { ; {

        .new MiterLimit:REAL

        .ifd GdipGetPenLineJoin([rcx].Pen.nativePen, &MiterLimit)
            mov this.lastResult,eax
        .endif
        movss xmm0,MiterLimit
        retm <xmm0>
        }

    .operator SetAlignment :vararg { ; :PenAlignment {
        .ifd GdipSetPenMode([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetAlignment :vararg { ; {

        .new Alignment:int_t

        .ifd GdipGetPenMode([rcx].Pen.nativePen, &Alignment)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,Alignment>
        }

    .operator SetTransform :ptr Matrix, :vararg {
        .ifd GdipSetPenTransform([rcx].Pen.nativePen, [rdx].Matrix.nativeMatrix)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetTransform :ptr Matrix, :vararg {
        .ifd GdipGetPenTransform([rcx].Pen.nativePen, [rdx].Matrix.nativeMatrix)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator ResetTransform :vararg { ; {
        .ifd GdipResetPenTransform([rcx].Pen.nativePen)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator MultiplyTransform :ptr Matrix, :vararg {
        .ifd GdipMultiplyPenTransform([rcx].Pen.nativePen, [rdx].Matrix.nativeMatrix, _2)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator TranslateTransform :vararg { ; :REAL, :REAL, :MatrixOrder {
        .ifd GdipTranslatePenTransform([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator ScaleTransform :vararg { ; :REAL, :REAL, :MatrixOrder {
        .ifd GdipScalePenTransform([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator RotateTransform :vararg { ; :REAL, :MatrixOrder {
        .ifd GdipRotatePenTransform([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetPenType :vararg { ; {

        .new penType:PenType

        .ifd GdipGetPenFillType([rcx].Pen.nativePen, &penType)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,penType>
        }

    .operator SetColor :vararg { ; :ptr Color {
        .ifd GdipSetPenColor([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetBrush :vararg { ; :ptr Brush {
        .ifd GdipSetPenBrushFill([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetColor :vararg { ; {

        .if this.GetPenType() != PenTypeSolidColor

            mov this.lastResult,WrongState
            xor eax,eax

        .else

            .new argb:ARGB

            .ifd GdipGetPenColor(this.nativePen, &argb)
                mov this.lastResult,eax
                xor eax,eax
            .else
                mov eax,argb
            .endif
        .endif
        retm <eax>
        }

    .operator GetBrush :vararg { ; {

        .new brush:ptr Brush

        mov edx,this.GetPenType()
        xor eax,eax
        .switch pascal edx
        .case PenTypeSolidColor
           SolidBrush()
        .case PenTypeHatchFill
           HatchBrush()
        .case PenTypeTextureFill
           TextureBrush()
        .case PenTypePathGradient
           Brush()
        .case PenTypeLinearGradient
           LinearGradientBrush()
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

        .ifd GdipGetPenDashStyle([rcx].Pen.nativePen, &PenDashStyle)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,PenDashStyle>
        }

    .operator SetDashStyle :vararg { ; :DashStyle {
        .ifd GdipSetPenDashStyle([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetDashOffset :vararg { ; {

        .new DashOffset:int_t

        .ifd GdipGetPenDashOffset([rcx].Pen.nativePen, &DashOffset)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,DashOffset>
        }

    .operator SetDashOffset :vararg { ; :REAL {
        .ifd GdipSetPenDashOffset([this].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetDashPattern :vararg { ; :ptr REAL, :int_t {
        .ifd GdipSetPenDashArray([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetDashPatternCount :vararg { ; {

       .new DashPatternCount:int_t

        mov DashPatternCount,0
        .ifd GdipGetPenDashCount([rcx].Pen.nativePen, &DashPatternCount)
            mov this.lastResult,eax
        .endif
        exitm<mov eax,DashPatternCount>
        }

    .operator GetDashPattern :ptr REAL, :int_t, :vararg { ; {
        .ifs rdx == NULL || r8d <= 0
            mov eax,InvalidParameter
            mov this.lastResult,eax
        .elseif GdipGetPenDashArray([rcx].Pen.nativePen, rdx, r8d)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator SetCompoundArray :vararg { ; :ptr REAL, :int_t {
        .ifd GdipSetPenCompoundArray([rcx].Pen.nativePen, _1)
            mov this.lastResult,eax
        .endif
        exitm<>
        }

    .operator GetCompoundArrayCount :vararg { ; {
        .new CompoundArrayCount:int_t
        mov CompoundArrayCount,0
        .ifd GdipGetPenCompoundCount([rcx].Pen.nativePen, &CompoundArrayCount)
            mov this.lastResult,eax
        .endif
        mov eax,CompoundArrayCount
        retm <eax>
        }

    .operator GetCompoundArray :ptr REAL, :int_t, :vararg { ;
        .ifs rdx == NULL || r8d <= 0
            mov eax,InvalidParameter
        .elseif GdipGetPenCompoundArray(this.nativePen, rdx, r8d)
            mov this.lastResult,eax
        .endif
        retm <eax>
        }

    .operator GetLastStatus :vararg { ; {
        mov     eax,this.lastResult
        mov     this.lastResult,Ok
        retm    <eax>
        }
    .operator SetNativePen :ptr Pen {
        mov     [this].Pen.nativePen,_1
        exitm   <>
        }
    .ends
    GpPen typedef Pen

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
