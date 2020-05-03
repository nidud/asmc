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

    .operator Pen {
        .if GdipAlloc(Pen)
            mov [rax].Pen.nativePen,NULL
            mov [rax].Pen.lastResult,Ok
        .endif
        retm <rax>
        }
    .operator SetStatus :Status {
        mov eax,_1
        .if eax != Ok
            mov [this].Pen.lastResult,eax
        .endif
        retm <eax>
        }
    .operator = :ptr Pen, :Status {
        mov     [this].Pen.nativePen,_1
        mov     [this].Pen.lastResult,_2
        retm    <this>
        }

    .operator Pen1 :ptr Color, :REAL {

        .new stack:Stack

        movss stack.float,_2
        mov stack.r_edi,[_1].Color.Argb

        .if GdipAlloc(Pen)

            mov stack.r_rbx,rax
            GdipCreatePen1(stack.r_edi, stack.float, UnitWorld, &[rax].Pen.nativePen)
            mov this,stack.r_rbx
            mov [this].Pen.lastResult,eax
            mov rax,this
        .endif
        retm <rax>
        }

    .operator Pen2 :ptr Brush, :REAL {

        .new stack:Stack

        movss stack.float,_2
        mov stack.r_rdi,[_1].Brush.nativeBrush

        .if GdipAlloc(Pen)

            mov stack.r_rbx,rax
            GdipCreatePen2(stack.r_rdi, stack.float, UnitWorld, &[rax].Pen.nativePen)
            mov this,stack.r_rbx
            mov [this].Pen.lastResult,eax
            mov rax,this
        .endif
        retm <rax>
        }

    .operator Release {

        .new stack:Stack

        mov stack.r_rcx,this

        GdipDeletePen([this].Pen.nativePen)
        GdipFree(stack.r_rcx)
        exitm   <>
        }

    .operator Clone {

        .new stack:Stack

        mov stack.r_rsi,rsi
        mov stack.r_rdi,rdi
        mov rsi,this

        .if GdipAlloc(Pen)

            mov rdi,rax
            .ifd GdipClonePen([rsi].Pen.nativePen, &[rdi].Pen.nativePen)

                mov [rsi].Pen.lastResult,eax
            .endif
            mov [rdi].Pen.lastResult,[rsi].Pen.lastResult
            mov rax,rdi
        .endif
        mov rsi,stack.r_rsi
        mov rdi,stack.r_rdi
        retm<rax>
        }

    .operator SetWidth :REAL {

        .new pen:ptr Pen

        mov pen,this

        GdipSetPenWidth([this].Pen.nativePen, _1)
        pen.SetStatus(eax)
        retm<eax>
        }

    .operator GetWidth {

        .new pen:ptr Pen
        .new width:int_t

        mov pen,this

        GdipGetPenWidth([this].Pen.nativePen, &width)
        pen.SetStatus(eax)
        mov eax,width
        retm <eax>
        }

    ;; Set/get line caps: start, end, and dash

    ;; Line cap and join APIs by using LineCap and LineJoin enums.

    .operator SetLineCap :LineCap, :LineCap, :DashCap {

        .new pen:ptr Pen

        mov pen,this

        GdipSetPenLineCap197819([this].Pen.nativePen, _1, _2, _3)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetStartCap :LineCap {

        .new pen:ptr Pen

        mov pen,this

        GdipSetPenStartCap([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetEndCap :LineCap {

        .new pen:ptr Pen

        mov pen,this

        GdipSetPenEndCap([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetDashCap :DashCap {

        .new pen:ptr Pen

        mov pen,this

        GdipSetPenDashCap197819([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetStartCap {

        .new pen:ptr Pen
        .new PenCap:ptr

        mov pen,this

        GdipGetPenStartCap([this].Pen.nativePen, &PenCap)
        pen.SetStatus(eax)

        mov rax,PenCap
        retm<rax>
        }

    .operator GetEndCap {

        .new pen:ptr Pen
        .new PenCap:ptr

        mov pen,this
        GdipGetPenEndCap([this].Pen.nativePen, &PenCap)
        pen.SetStatus(eax)

        mov rax,PenCap
        retm<rax>
        }

    .operator GetDashCap {

        .new pen:ptr Pen
        .new PenCap:ptr

        mov pen,this
        GdipGetPenDashCap197819([this].Pen.nativePen, &PenCap)
        pen.SetStatus(eax)

        mov rax,PenCap
        retm<rax>
        }

    .operator SetLineJoin :LineJoin {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenLineJoin([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetLineJoin {

        .new stack:Stack

        mov stack.r_rcx,this

        GdipGetPenLineJoin([this].Pen.nativePen, &stack.r_rbx)
        Pen_SetStatus(stack.r_rcx, eax)

        mov rax,stack.r_rbx
        retm<rax>
        }

    .operator SetCustomStartCap :ptr CustomLineCap {

        .new pen:ptr Pen

        mov pen,this
        xor eax,eax
        .if _1
            mov rax,[_1].CustomLineCap.nativeCap
        .endif
        GdipSetPenCustomStartCap([this].Pen.nativePen, rax)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetCustomStartCap :ptr CustomLineCap {

        .new pen:ptr Pen

        mov pen,this

        .if !_1
            pen.SetStatus(InvalidParameter)
        .else
            GdipGetPenCustomStartCap([this].Pen.nativePen, &[_1].CustomLineCap.nativeCap)
            pen.SetStatus(eax)
        .endif
        retm <eax>
        }

    .operator SetCustomEndCap :ptr CustomLineCap {

        .new pen:ptr Pen

        xor eax,eax
        mov pen,this
        .if _1
            mov rax,[_1].CustomLineCap.nativeCap
        .endif
        GdipSetPenCustomEndCap([this].Pen.nativePen, rax)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetCustomEndCap :ptr CustomLineCap {

        .new pen:ptr Pen

        mov pen,this
        .if !_1
            pen.SetStatus(InvalidParameter)
        .else
            GdipGetPenCustomEndCap([this].Pen.nativePen, &[_1].CustomLineCap.nativeCap)
            pen.SetStatus(eax)
        .endif
        retm<eax>
        }

    .operator SetMiterLimit :REAL {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenMiterLimit([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetMiterLimit {

        .new pen:ptr Pen
        .new MiterLimit:REAL

        mov pen,this
        GdipGetPenLineJoin([this].Pen.nativePen, &MiterLimit)
        pen.SetStatus(eax)

        movss xmm0,MiterLimit
        retm <xmm0>
        }

    .operator SetAlignment :PenAlignment {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenMode([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetAlignment {

        .new pen:ptr Pen
        .new Alignment:int_t

        mov pen,this
        GdipGetPenMode([this].Pen.nativePen, &Alignment)
        pen.SetStatus(eax)

        mov eax,Alignment
        retm<eax>
        }

    .operator SetTransform :ptr Matrix {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenTransform([this].Pen.nativePen, [_1].Matrix.nativeMatrix)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetTransform :ptr Matrix {

        .new pen:ptr Pen

        mov pen,this
        GdipGetPenTransform([this].Pen.nativePen, [_1].Matrix.nativeMatrix)
        exitm<pen.SetStatus(eax)>
        }

    .operator ResetTransform {

        .new pen:ptr Pen

        mov pen,this
        GdipResetPenTransform([this].Pen.nativePen)
        exitm<pen.SetStatus(eax)>
        }

    .operator MultiplyTransform :ptr Matrix, :MatrixOrder {

        .new pen:ptr Pen

        mov pen,this
        GdipMultiplyPenTransform([this].Pen.nativePen, [_1].Matrix.nativeMatrix, _2)
        exitm<pen.SetStatus(eax)>
        }

    .operator TranslateTransform :REAL, :REAL, :MatrixOrder {

        .new pen:ptr Pen

        mov pen,this
        GdipTranslatePenTransform([this].Pen.nativePen, _1, _2, _3)
        exitm<pen.SetStatus(eax)>
        }

    .operator ScaleTransform :REAL, :REAL, :MatrixOrder {

        .new pen:ptr Pen

        mov pen,this
        GdipScalePenTransform([this].Pen.nativePen, _1, _2, _3)
        exitm<pen.SetStatus(eax)>
        }

    .operator RotateTransform :REAL, :MatrixOrder {

        .new pen:ptr Pen

        mov pen,this
        GdipRotatePenTransform([this].Pen.nativePen, _1, _2)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetPenType {

        .new pen:ptr Pen
        .new penType:PenType

        mov pen,this
        GdipGetPenFillType([this].Pen.nativePen, &penType)
        pen.SetStatus(eax)

        mov eax,penType
        retm <eax>
        }

    .operator SetColor :ptr Color {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenColor([this].Pen.nativePen, [_1].Color.Argb)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetBrush :ptr Brush {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenBrushFill([this].Pen.nativePen, [_1].Brush.nativeBrush)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetColor :ptr Color {

        .new pen:ptr Pen
        .new color:ptr Color

        mov pen,this

        .if _1 == NULL

            pen.SetStatus(InvalidParameter)

        .else

            mov color,_1

            .if pen.GetPenType() != PenTypeSolidColor

                pen.SetStatus(WrongState)

            .else

                .new argb:ARGB

                GdipGetPenColor([this].Pen.nativePen, &argb)
                pen.SetStatus(eax)

                .if eax == Ok
                    mov _1,color
                    mov [_1].Color.Argb,argb
                    mov eax,Ok
                .endif
            .endif
        .endif
        retm <eax>
        }

    .operator GetBrush {

        .new pen:ptr Pen
        .new brush:ptr Brush

        mov pen,this
        mov edx,pen.GetPenType()
        xor eax,eax
       .switch pascal edx
       .case PenTypeSolidColor
           SolidBrush_SolidBrush(0)
       .case PenTypeHatchFill
           HatchBrush_HatchBrush(0)
       .case PenTypeTextureFill
           TextureBrush_TextureBrush(0)
       .case PenTypePathGradient
           Brush_Brush(0)
       .case PenTypeLinearGradient
           LinearGradientBrush_LinearGradientBrush(0)
       .endsw

       .if rax

           mov brush,rax
           mov this,pen
           GdipGetPenBrushFill([this].Pen.nativePen, &[rax].Pen.nativePen)
           pen.SetStatus(eax)
           mov rax,brush
       .endif
       retm <rax>
       }

    .operator GetDashStyle {

        .new pen:ptr Pen
        .new PenDashStyle:int_t

        mov pen,this
        GdipGetPenDashStyle([this].Pen.nativePen, &PenDashStyle)
        pen.SetStatus(eax)

        mov eax,PenDashStyle
        retm <eax>
        }

    .operator SetDashStyle :DashStyle {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenDashStyle([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetDashOffset {

        .new pen:ptr Pen
        .new DashOffset:int_t

        mov pen,this
        GdipGetPenDashOffset([this].Pen.nativePen, &DashOffset)
        pen.SetStatus(eax)

        mov eax,DashOffset
        retm <eax>
        }

    .operator SetDashOffset :REAL {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenDashOffset([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetDashPattern :ptr REAL, :int_t {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenDashArray([this].Pen.nativePen, _1, _2)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetDashPatternCount {

        .new pen:ptr Pen
        .new DashPatternCount:int_t

        mov pen,this
        mov DashPatternCount,0

        GdipGetPenDashCount([this].Pen.nativePen, &DashPatternCount)
        pen.SetStatus(eax)

        mov eax,DashPatternCount
        retm <eax>
        }

    .operator GetDashPattern :ptr REAL, :SINT {

        .new pen:ptr Pen

        mov pen,this
        .ifs _1 == NULL || _2 <= 0
            pen.SetStatus(InvalidParameter)
        .else
            GdipGetPenDashArray([this].Pen.nativePen, _1, _2)
            pen.SetStatus(eax)
        .endif
        retm <eax>
        }

    .operator SetCompoundArray :ptr REAL, :int_t {

        .new pen:ptr Pen

        mov pen,this
        GdipSetPenCompoundArray([this].Pen.nativePen, _1, _2)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetCompoundArrayCount {

        .new pen:ptr Pen
        .new CompoundArrayCount:int_t

        mov pen,this
        mov CompoundArrayCount,0

        GdipGetPenCompoundCount([this].Pen.nativePen, &CompoundArrayCount)
        pen.SetStatus(eax)

        mov eax,CompoundArrayCount
        retm <eax>
        }

    .operator GetCompoundArray :ptr REAL, :int_t {

        .new pen:ptr Pen

        mov pen,this
        .ifs _1 == NULL || _2 <= 0
            pen.SetStatus(InvalidParameter)
        .else
            GdipGetPenCompoundArray([this].Pen.nativePen, _1, _2)
            pen.SetStatus(eax)
        .endif
        retm <eax>
        }

    .operator GetLastStatus {
        mov     eax,[this].Pen.lastResult
        mov     [this].Pen.lastResult,Ok
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
