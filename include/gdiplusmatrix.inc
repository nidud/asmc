include winapifamily.inc
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template Matrix ;: public GdiplusBase

    nativeMatrix ptr_t ?
    lastResult   Status ?

    ;; Default constructor is set to identity matrix.

    .operator Matrix {
        mov rax,this
        .if rax == NULL
            GdipAlloc(Matrix)
        .endif
        .new    matrix:ptr
        mov     matrix,rax
        mov     [rax].Matrix.nativeMatrix,NULL
        GdipCreateMatrix(&[rax].Matrix.nativeMatrix)
        mov     this,matrix
        mov     [this].Matrix.lastResult,eax
        mov     rax,this
        retm    <rax>
        }

    .operator = :ptr Matrix {
        mov     [this].Matrix.nativeMatrix,_1
        mov     [this].Matrix.lastResult,Ok
        retm    <this>
        }

    .operator = :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        .new    matrix:ptr
        mov     matrix,this
        mov     [this].Matrix.nativeMatrix,NULL
        GdipCreateMatrix2(_1, _2, _3, _4, _5, _6, &[this].Matrix.nativeMatrix)
        mov     this,matrix
        mov     [this].Matrix.lastResult,eax
        mov     rax,this
        retm    <rax>
        }

    .operator = :ptr RectF, :ptr PointF {
        .new    matrix:ptr
        .new    rect:ptr
        mov     rect,_1
        mov     matrix,this
        mov     [this].Matrix.nativeMatrix,NULL
        GdipCreateMatrix3(&rect, _2, &[this].Matrix.nativeMatrix)
        mov     this,matrix
        mov     [this].Matrix.lastResult,eax
        mov     rax,this
        retm    <rax>
        }

    .operator = :ptr Rect, :ptr Point {
        .new    matrix:ptr
        .new    rect:ptr
        mov     rect,_1
        mov     matrix,this
        mov     [this].Matrix.nativeMatrix,NULL
        GdipCreateMatrix3I(&rect, _2, &[this].Matrix.nativeMatrix)
        mov     this,matrix
        mov     [this].Matrix.lastResult,eax
        mov     rax,this
        retm    <rax>
        }

    .operator Release {
        exitm<GdipDeleteMatrix([this].Matrix.nativeMatrix)>
        }

    .operator Clone {

        .new matrix:ptr
        .new cloneMatrix:ptr

        mov matrix,this
        mov cloneMatrix,NULL
        GdipCloneMatrix([this].Matrix.nativeMatrix, &cloneMatrix)
        mov this,matrix
        mov [this].Matrix.lastResult,eax
        .if eax != Ok
            xor eax,eax
        .else
            GdipAlloc(Matrix)
            mov [rax].Matrix.lastResult,Ok
            mov rdx,cloneMatrix
            mov [rax].Matrix.nativeMatrix,rdx
        .endif
        retm <rax>
        }

    .operator GetElements :ptr REAL {
        exitm<GdipGetMatrixElements([this].Matrix.nativeMatrix, _1)>
        }
    .operator SetElements :REAL, :REAL, :REAL, :REAL, :REAL, :REAL {
        exitm<GdipSetMatrixElements([this].Matrix.nativeMatrix, _1, _2, _3, _4, _5, _6)>
        }

    .operator OffsetX {

        .new elements[6]:REAL

        .if Matrix_GetElements(this, &elements) == Ok
            movss xmm0,elements[4*4]
        .else
            xorps xmm0,xmm0
        .endif
        retm <xmm0>
        }
    .operator OffsetY {

        .new elements[6]:REAL

        .if Matrix_GetElements(this, &elements) == Ok
            movss xmm0,elements[5*4]
        .else
            xorps xmm0,xmm0
        .endif
        retm <xmm0>
        }

    .operator Reset {
        ;; set identity matrix elements
        exitm<GdipSetMatrixElements([this].Matrix.nativeMatrix, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0)>
        }
    .operator Multiply :ptr Matrix, :MatrixOrder {
        exitm<GdipMultiplyMatrix([this].Matrix.nativeMatrix, [_1].Matrix.nativeMatrix, _2)>
        }
    .operator Translate :REAL, :REAL, :MatrixOrder {
        exitm<GdipTranslateMatrix([this].Matrix.nativeMatrix, _1, _2, _3)>
        }
    .operator Scale :REAL, :REAL, :MatrixOrder {
        exitm<GdipScaleMatrix([this].Matrix.nativeMatrix, _1, _2, _3)>
        }
    .operator Rotate :REAL, :MatrixOrder {
        exitm<GdipRotateMatrix([this].Matrix.nativeMatrix, _1, _2)
        }

    .operator RotateAt :REAL, :ptr PointF, :MatrixOrder {

        .new matrix:ptr
        .new order:MatrixOrder
        .new angle:REAL
        .new center:ptr

        movss   angle,_1
        mov     center,_2
        mov     order,_3
        mov     matrix,[this].Matrix.nativeMatrix

        .if _3 == MatrixOrderPrepend
            GdipTranslateMatrix ( matrix, [_2].PointF.X, [_2].PointF.Y, order )
            GdipRotateMatrix    ( matrix, angle, order )
            mov _2,center
            mov eax,[_2].PointF.X
            xor eax,0x80000000
            movd xmm1,eax
            mov eax,[_2].PointF.Y
            xor eax,0x80000000
            movd xmm2,eax
            GdipTranslateMatrix ( matrix, xmm1, xmm2, order )
        .else
            mov eax,[_2].PointF.X
            xor eax,0x80000000
            movd xmm1,eax
            mov eax,[_2].PointF.Y
            xor eax,0x80000000
            movd xmm2,eax
            GdipTranslateMatrix ( matrix, xmm1, xmm2, order )
            GdipRotateMatrix    ( matrix, angle, order )
            mov _2,center
            GdipTranslateMatrix ( matrix, [_2].PointF.X, [_2].PointF.Y, order )
        .endif
        exitm<>
        }
    .operator Shear :REAL, :REAL, :MatrixOrder {
        exitm<GdipShearMatrix([this].Matrix.nativeMatrix, _1, _2, _3)>
        }
    .operator Invert {
        exitm<GdipInvertMatrix([this].Matrix.nativeMatrix)>
        }

    ;; float version
    .operator TransformPoints :ptr PointF, :int_t {
        exitm<GdipTransformMatrixPoints([this].Matrix.nativeMatrix, _1, _2)>
        }
    .operator TransformPoints :ptr Point, :int_t {
        exitm<GdipTransformMatrixPointsI([this].Matrix.nativeMatrix, _1, _2)>
        }
    .operator TransformVectors :ptr PointF, :int_t {
        exitm<GdipVectorTransformMatrixPoints([this].Matrix.nativeMatrix, _1, _2)>
        }
    .operator TransformVectors :ptr Point, :int_t {
       exitm<GdipVectorTransformMatrixPointsI([this].Matrix.nativeMatrix, _1, _2)>
        }
    .operator IsInvertible {

        .new result:BOOL
        .new matrix:ptr

        mov matrix,this
        mov result,FALSE
        GdipIsMatrixInvertible([this].Matrix.nativeMatrix, &result)
        mov this,matrix
        .if eax != Ok
            mov [this].Matrix.lastResult,eax
        .endif
        mov eax,result
        retm <eax>
        }
    .operator IsIdentity {

        .new result:BOOL
        .new matrix:ptr

        mov matrix,this
        mov result,FALSE
        GdipIsMatrixIdentity([this].Matrix.nativeMatrix, &result)
        mov this,matrix
        .if eax != Ok
            mov [this].Matrix.lastResult,eax
        .endif
        mov eax,result
        retm <eax>
        }
    .operator Equals :ptr Matrix {

        .new result:BOOL
        .new matrix:ptr

        mov matrix,this
        mov result,FALSE

        GdipIsMatrixEqual([this].Matrix.nativeMatrix, [_1].Matrix.nativeMatrix, &result)

        mov this,matrix
        .if eax != Ok
            mov [this].Matrix.lastResult,eax
        .endif
        mov eax,result
        retm <eax>
        }
    .operator GetLastStatus {
        mov     eax,[this].Matrix.lastResult
        mov     [this].Matrix.lastResult,Ok
        retm    <eax>
        }
    .operator SetNativeMatrix :ptr Matrix {
        mov     [this].Pen.nativeMatrix,_1
        exitm   <>
        }
    .operator SetStatus :Status {
        mov eax,_1
        .if (eax != Ok)
            mov [this].Matrix.lastResult,eax
        .endif
        retm <eax>
        }
    .ends
    GpMatrix typedef Matrix

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

