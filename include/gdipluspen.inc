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
    memState    Status ?

    .operator Pen {

        .new pen:ptr Pen

        mov rax,this
        .repeat
            .if rax == NULL
                .break .if !GdipAlloc(Pen)
                mov [rax].Pen.memState,Ok
            .else
                mov [rax].Pen.memState,NotImplemented
            .endif
            mov [rax].Pen.nativePen,NULL
            mov [rax].Pen.lastResult,NotImplemented
        .until 1
        retm <rax>
        }

    .operator Release {
        mov pen,this
        GdipDeletePen([this].Pen.nativePen)
        mov this,pen
        .if [this].Pen.memState != NotImplemented
            GdipFree(this)
        .endif
        exitm<>
        }

    .operator Delete {
        exitm<GdipDeletePen([this].Pen.nativePen)>
        }

    .operator CreatePen :ARGB, :REAL {
        mov pen,this
        GdipCreatePen1(_1, _2, UnitWorld, &[this].Pen.nativePen)
        exitm<pen.SetStatus(eax)>
        }

    .operator NewPen :abs, :abs {
        mov pen,this
        GdipDeletePen([this].Pen.nativePen)
        GdipCreatePen1(_1, _2, UnitWorld, pen)
        exitm<pen.SetStatus(eax)>
        }

    .operator CreatePen2 :ptr Brush, :REAL {
        mov pen,this
        GdipCreatePen2(_1, _2, UnitWorld, &[this].Pen.nativePen)
        exitm<pen.SetStatus(eax)>
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
        mov pen,this
        GdipSetPenWidth([this].Pen.nativePen, _1)
        pen.SetStatus(eax)
        retm<eax>
        }

    .operator GetWidth {

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
        mov pen,this
        GdipSetPenLineCap197819([this].Pen.nativePen, _1, _2, _3)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetStartCap :LineCap {
        mov pen,this
        GdipSetPenStartCap([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetEndCap :LineCap {
        mov pen,this
        GdipSetPenEndCap([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetDashCap :DashCap {
        mov pen,this
        GdipSetPenDashCap197819([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetStartCap {

        .new PenCap:ptr

        mov pen,this
        GdipGetPenStartCap([this].Pen.nativePen, &PenCap)
        pen.SetStatus(eax)
        mov rax,PenCap
        retm<rax>
        }

    .operator GetEndCap {

        .new PenCap:ptr

        mov pen,this
        GdipGetPenEndCap([this].Pen.nativePen, &PenCap)
        pen.SetStatus(eax)
        mov rax,PenCap
        retm<rax>
        }

    .operator GetDashCap {

        .new PenCap:ptr

        mov pen,this
        GdipGetPenDashCap197819([this].Pen.nativePen, &PenCap)
        pen.SetStatus(eax)
        mov rax,PenCap
        retm<rax>
        }

    .operator SetLineJoin :LineJoin {
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
        mov pen,this
        xor eax,eax
        .if _1
            mov rax,[_1].CustomLineCap.nativeCap
        .endif
        GdipSetPenCustomStartCap([this].Pen.nativePen, rax)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetCustomStartCap :ptr CustomLineCap {
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
        xor eax,eax
        mov pen,this
        .if _1
            mov rax,[_1].CustomLineCap.nativeCap
        .endif
        GdipSetPenCustomEndCap([this].Pen.nativePen, rax)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetCustomEndCap :ptr CustomLineCap {
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
        mov pen,this
        GdipSetPenMiterLimit([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetMiterLimit {

        .new MiterLimit:REAL

        mov pen,this
        GdipGetPenLineJoin([this].Pen.nativePen, &MiterLimit)
        pen.SetStatus(eax)
        movss xmm0,MiterLimit
        retm <xmm0>
        }

    .operator SetAlignment :PenAlignment {
        mov pen,this
        GdipSetPenMode([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetAlignment {

        .new Alignment:int_t

        mov pen,this
        GdipGetPenMode([this].Pen.nativePen, &Alignment)
        pen.SetStatus(eax)
        mov eax,Alignment
        retm<eax>
        }

    .operator SetTransform :ptr Matrix {
        mov pen,this
        GdipSetPenTransform([this].Pen.nativePen, [_1].Matrix.nativeMatrix)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetTransform :ptr Matrix {
        mov pen,this
        GdipGetPenTransform([this].Pen.nativePen, [_1].Matrix.nativeMatrix)
        exitm<pen.SetStatus(eax)>
        }

    .operator ResetTransform {
        mov pen,this
        GdipResetPenTransform([this].Pen.nativePen)
        exitm<pen.SetStatus(eax)>
        }

    .operator MultiplyTransform :ptr Matrix, :MatrixOrder {
        mov pen,this
        GdipMultiplyPenTransform([this].Pen.nativePen, [_1].Matrix.nativeMatrix, _2)
        exitm<pen.SetStatus(eax)>
        }

    .operator TranslateTransform :REAL, :REAL, :MatrixOrder {
        mov pen,this
        GdipTranslatePenTransform([this].Pen.nativePen, _1, _2, _3)
        exitm<pen.SetStatus(eax)>
        }

    .operator ScaleTransform :REAL, :REAL, :MatrixOrder {
        mov pen,this
        GdipScalePenTransform([this].Pen.nativePen, _1, _2, _3)
        exitm<pen.SetStatus(eax)>
        }

    .operator RotateTransform :REAL, :MatrixOrder {
        mov pen,this
        GdipRotatePenTransform([this].Pen.nativePen, _1, _2)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetPenType {

        .new penType:PenType

        mov pen,this
        GdipGetPenFillType([this].Pen.nativePen, &penType)
        pen.SetStatus(eax)
        mov eax,penType
        retm <eax>
        }

    .operator SetColor :ptr Color {
        mov pen,this
        GdipSetPenColor([this].Pen.nativePen, [_1].Color.Argb)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetBrush :ptr Brush {
        mov pen,this
        GdipSetPenBrushFill([this].Pen.nativePen, [_1].Brush.nativeBrush)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetColor :ptr Color {

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

        .new brush:ptr Brush

        mov pen,this
        mov edx,pen.GetPenType()
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
           mov this,pen
           GdipGetPenBrushFill([this].Pen.nativePen, &[rax].Pen.nativePen)
           pen.SetStatus(eax)
           mov rax,brush
       .endif
       retm <rax>
       }

    .operator GetDashStyle {

        .new PenDashStyle:int_t

        mov pen,this
        GdipGetPenDashStyle([this].Pen.nativePen, &PenDashStyle)
        pen.SetStatus(eax)
        mov eax,PenDashStyle
        retm <eax>
        }

    .operator SetDashStyle :DashStyle {
        mov pen,this
        GdipSetPenDashStyle([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetDashOffset {

        .new DashOffset:int_t

        mov pen,this
        GdipGetPenDashOffset([this].Pen.nativePen, &DashOffset)
        pen.SetStatus(eax)
        mov eax,DashOffset
        retm <eax>
        }

    .operator SetDashOffset :REAL {
        mov pen,this
        GdipSetPenDashOffset([this].Pen.nativePen, _1)
        exitm<pen.SetStatus(eax)>
        }

    .operator SetDashPattern :ptr REAL, :int_t {
        mov pen,this
        GdipSetPenDashArray([this].Pen.nativePen, _1, _2)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetDashPatternCount {

        .new DashPatternCount:int_t

        mov pen,this
        mov DashPatternCount,0
        GdipGetPenDashCount([this].Pen.nativePen, &DashPatternCount)
        pen.SetStatus(eax)
        mov eax,DashPatternCount
        retm <eax>
        }

    .operator GetDashPattern :ptr REAL, :SINT {
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
        mov pen,this
        GdipSetPenCompoundArray([this].Pen.nativePen, _1, _2)
        exitm<pen.SetStatus(eax)>
        }

    .operator GetCompoundArrayCount {

        .new CompoundArrayCount:int_t

        mov pen,this
        mov CompoundArrayCount,0
        GdipGetPenCompoundCount([this].Pen.nativePen, &CompoundArrayCount)
        pen.SetStatus(eax)
        mov eax,CompoundArrayCount
        retm <eax>
        }

    .operator GetCompoundArray :ptr REAL, :int_t {
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
