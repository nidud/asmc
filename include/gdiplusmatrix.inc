include winapifamily.inc
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.template Matrix

    nativeMatrix ptr_t ?
    lastResult   Status ?
    scratch      int_t ?

    ;; Default constructor is set to identity matrix.

    .operator Matrix :abs, :vararg {
        mov this.nativeMatrix,NULL
        ifb <_1>
            GdipCreateMatrix(addr this.nativeMatrix)
        else
            this.typeid(Matrix, _1)(_1, _2)
        endif
        mov this.lastResult,eax
        }

    .operator Matrix?flt :vararg {
        GdipCreateMatrix2(_1, addr this.nativeMatrix)
        }
    .operator Matrix?pRectF :ptr RectF, :ptr PointF, :vararg {
        mov rcx,rdx
        mov rdx,r8
        GdipCreateMatrix3(rcx, rdx, addr this.nativeMatrix)
        }
    .operator Matrix?pRect :ptr Rect, :ptr Point, :vararg {
        mov rcx,rdx
        mov rdx,r8
        GdipCreateMatrix3I(rcx, rdx, addr this.nativeMatrix)
        }

    .operator Release {
        GdipDeleteMatrix([this].Matrix.nativeMatrix)
        }

    .operator Clone :vararg {

        .new clone:Matrix

        GdipCloneMatrix(this.nativeMatrix, addr clone.nativeMatrix)
        mov this.lastResult,eax
        lea rax,clone
        }

    .operator GetElements :abs, :vararg {
        GdipGetMatrixElements(this.nativeMatrix, _1)
        this.SetStatus()
        }
    .operator SetElements :vararg {
        GdipSetMatrixElements(this.nativeMatrix, _1)
        this.SetStatus()
        }

    .operator OffsetX :vararg {

        .new elements[6]:REAL

        .if this.GetElements(&elements) == Ok
            movss xmm0,elements[4*4]
        .else
            xorps xmm0,xmm0
        .endif
        }

    .operator OffsetY :vararg {

        .new elements[6]:REAL

        .if this.GetElements(&elements) == Ok
            movss xmm0,elements[5*4]
        .else
            xorps xmm0,xmm0
        .endif
        }

    .operator Reset :vararg {
        ;; set identity matrix elements
        GdipSetMatrixElements(this.nativeMatrix, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0)
        this.SetStatus()
        }
    .operator Multiply :ptr Matrix, :abs, :vararg {
        GdipMultiplyMatrix(this.nativeMatrix, [rdx].Matrix.nativeMatrix, _2)
        this.SetStatus()
        }
    .operator Translate :vararg {
        GdipTranslateMatrix(this.nativeMatrix, _1)
        this.SetStatus()
        }
    .operator Scale :vararg {
        GdipScaleMatrix(this.nativeMatrix, _1)
        this.SetStatus()
        }
    .operator Rotate :vararg {
        GdipRotateMatrix(this.nativeMatrix, _1)
        this.SetStatus()
        }

    .operator RotateAt :REAL, :ptr PointF, :MatrixOrder, :vararg {

        .new order:MatrixOrder
        .new angle:REAL
        .new center:ptr

        movss   angle,xmm1
        mov     center,r8
        mov     order,r9d

        .if r9d == MatrixOrderPrepend

            mov r10,r8
            GdipTranslateMatrix ( this.nativeMatrix, [r10].PointF.X, [r10].PointF.Y, r9d )
            GdipRotateMatrix    ( this.nativeMatrix, angle, order )
            mov r8,center
            mov eax,[r8].PointF.X
            xor eax,0x80000000
            movd xmm1,eax
            mov eax,[r8].PointF.Y
            xor eax,0x80000000
            movd xmm2,eax
            GdipTranslateMatrix ( this.nativeMatrix, xmm1, xmm2, order )

        .else

            mov eax,[r8].PointF.X
            xor eax,0x80000000
            movd xmm1,eax
            mov eax,[r8].PointF.Y
            xor eax,0x80000000
            movd xmm2,eax
            GdipTranslateMatrix ( this.nativeMatrix, xmm1, xmm2, order )
            GdipRotateMatrix    ( this.nativeMatrix, angle, order )
            mov r10,center
            GdipTranslateMatrix ( this.nativeMatrix, [r10].PointF.X, [r10].PointF.Y, order )

        .endif
        this.SetStatus()
        }

    .operator Shear :vararg {
        GdipShearMatrix(this.nativeMatrix, _1)
        this.SetStatus()
        }
    .operator Invert :vararg {
        GdipInvertMatrix(this.nativeMatrix)
        this.SetStatus()
        }

    ;; float version

    .operator TransformPoints :abs, :vararg {
        this.typeid(TransformPoints, _1)(_1, _2)
        this.SetStatus()
        }
    .operator TransformPoints?pPointF :vararg {
        GdipTransformMatrixPoints(this.nativeMatrix, _1)
        }
    .operator TransformPoints?pPoint :vararg {
        GdipTransformMatrixPointsI(this.nativeMatrix, _1)
        }

    .operator TransformVectors :abs, :vararg {
        this.typeid(TransformVectors, _1)(_1, _2)
        this.SetStatus()
        }
    .operator TransformVectors?pPointF :vararg {
        GdipVectorTransformMatrixPoints(this.nativeMatrix, _1)
        }
    .operator TransformVectors?pPoint :vararg {
        GdipVectorTransformMatrixPointsI(this.nativeMatrix, _1)
        }

    .operator IsInvertible :vararg {
        mov this.scratch,FALSE
        GdipIsMatrixInvertible(this.nativeMatrix, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator IsIdentity :vararg {
        mov this.scratch,FALSE
        GdipIsMatrixIdentity(this.nativeMatrix, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator Equals :ptr Matrix, :vararg {
        mov this.scratch,FALSE
        GdipIsMatrixEqual(this.nativeMatrix, [rcx].Matrix.nativeMatrix, addr this.scratch)
        this.SetStatus()
        mov eax,this.scratch
        }

    .operator GetLastStatus {
        mov eax,[this].Matrix.lastResult
        mov [this].Matrix.lastResult,Ok
        }

    .operator SetNativeMatrix :ptr Matrix {
        mov [this].Matrix.nativeMatrix,_1
        }

    .operator SetStatus :vararg {
        ifnb <_1>
         ifdif <_1>,<eax>
            mov eax,_1
         endif
        endif
        test eax,eax
        cmovz eax,this.lastResult
        mov this.lastResult,eax
        }
    .ends
    GpMatrix typedef Matrix

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

