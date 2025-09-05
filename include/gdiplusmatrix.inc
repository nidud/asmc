ifndef _WINAPIFAMILY_
include winapifamily.inc
endif
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

; Default constructor is set to identity matrix.
;
; Matrix()
; Matrix(REAL m11, REAL m12, REAL m21, REAL m22, REAL dx, REAL dy)
; Matrix(RectF& rect, PointF* dstplg)
; Matrix(Rect& rect, Point* dstplg)

.template Matrix fastcall

    nativeMatrix ptr_t ?
    lastResult   Status ?
    scratch      int_t ?

    .static Matrix :abs, :abs, :abs, :abs, :abs, :abs {
      ifb <_1>
        GdipCreateMatrix(addr this.nativeMatrix)
      elseifidn <RectF>,typeid(_1)
        GdipCreateMatrix3(addr _1, _2, addr this.nativeMatrix)
      elseifidn <Rect>,typeid(_1)
        GdipCreateMatrix3I(addr _1, _2, addr this.nativeMatrix)
      else
        GdipCreateMatrix2(_1, _2, _3, _4, _5, _6, addr this.nativeMatrix)
      endif
        mov this.lastResult,eax
        }

    .static Release {
        GdipDeleteMatrix(this.nativeMatrix)
        }

    .static SetStatus watcall :size_t {
        test    eax,eax
        cmovz   eax,this.lastResult
        mov     this.lastResult,eax
        }

    .static Clone {
       .new clone:Matrix
        GdipCloneMatrix(this.nativeMatrix, addr clone.nativeMatrix)
        mov this.lastResult,eax
        lea rax,clone
        }

    .static GetElements :abs {
        this.SetStatus(GdipGetMatrixElements(this.nativeMatrix, _1))
        }

    .static SetElements :abs, :abs, :abs, :abs, :abs, :abs {
        this.SetStatus(GdipSetMatrixElements(this.nativeMatrix, _1, _2, _3, _4, _5, _6))
        }

    .static OffsetX {
        .new elements[6]:REAL
        .if this.GetElements(&elements) == Ok
            movss xmm0,elements[4*4]
        .else
            xorps xmm0,xmm0
        .endif
        }

    .static OffsetY {
        .new elements[6]:REAL
        .if this.GetElements(&elements) == Ok
            movss xmm0,elements[5*4]
        .else
            xorps xmm0,xmm0
        .endif
        }

    .static Reset {
        ;; set identity matrix elements
        this.SetStatus(GdipSetMatrixElements(this.nativeMatrix, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0))
        }
    .static Multiply :ptr Matrix, :abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipMultiplyMatrix(this.nativeMatrix, [_1].Matrix.nativeMatrix, _2))
        }
    .static Translate offsetX:abs, offsetY:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipTranslateMatrix(this.nativeMatrix, offsetX, offsetY, order))
        }
    .static Scale scaleX:abs, scaleY:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipScaleMatrix(this.nativeMatrix, scaleX, scaleY, order))
        }
    .static Rotate angle:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipRotateMatrix(this.nativeMatrix, angle, order))
        }

    .static RotateAt angle:abs, center:abs, order:abs=<MatrixOrderPrepend> {
      local x,y
       .new x:real4, y:real4
        mov eax,order
        .if eax == MatrixOrderPrepend
            GdipTranslateMatrix ( this.nativeMatrix, center.X, center.Y, order )
            GdipRotateMatrix    ( this.nativeMatrix, angle, order )
            mov eax,center.X
            xor eax,0x80000000
            mov x,eax
            mov eax,center.Y
            xor eax,0x80000000
            mov y,eax
            GdipTranslateMatrix ( this.nativeMatrix, x, y, order )
        .else
            mov eax,center.X
            xor eax,0x80000000
            movd x,eax
            mov eax,center.Y
            xor eax,0x80000000
            movd y,eax
            GdipTranslateMatrix ( this.nativeMatrix, x, y, order )
            GdipRotateMatrix    ( this.nativeMatrix, angle, order )
            GdipTranslateMatrix ( this.nativeMatrix, center.X, center.Y, order )
        .endif
        this.SetStatus()
        }

    .static Shear shearX:abs, shearY:abs, order:abs=<MatrixOrderPrepend> {
        this.SetStatus(GdipShearMatrix(this.nativeMatrix, shearX, shearY, order))
        }
    .static Invert {
        this.SetStatus(GdipInvertMatrix(this.nativeMatrix))
        }

    ;; float version

    .static TransformPoints pts:abs, count:abs=<1> {
      ifidn <ptrPointF>,typeid(pts)
        this.SetStatus(GdipTransformMatrixPoints(this.nativeMatrix, pts, count))
      elseifidn <ptrPoint>,typeid(pts)
        this.SetStatus(GdipTransformMatrixPointsI(this.nativeMatrix, pts, count))
      else
        .err <pts>
      endif
        }

    .static TransformVectors pts:abs, count:abs=<1> {
      ifidn <ptrPointF>,typeid(pts)
        this.SetStatus(GdipVectorTransformMatrixPoints(this.nativeMatrix, pts, count))
      elseifidn <ptrPoint>,typeid(pts)
        this.SetStatus(GdipVectorTransformMatrixPointsI(this.nativeMatrix, pts, count))
      else
        .err <pts>
      endif
        }

    .static IsInvertible {
        mov this.scratch,FALSE
        this.SetStatus(GdipIsMatrixInvertible(this.nativeMatrix, addr this.scratch))
        mov eax,this.scratch
        }
    .static IsIdentity {
        mov this.scratch,FALSE
        this.SetStatus(GdipIsMatrixIdentity(this.nativeMatrix, addr this.scratch))
        mov eax,this.scratch
        }
    .static Equals :ptr Matrix {
        mov this.scratch,FALSE
        this.SetStatus(GdipIsMatrixEqual(this.nativeMatrix, [_1].Matrix.nativeMatrix, addr this.scratch))
        mov eax,this.scratch
        }
    .static GetLastStatus {
        mov eax,this.lastResult
        mov this.lastResult,Ok
        }

    .static SetNativeMatrix :ptr Matrix {
        mov this.nativeMatrix,_1
        }
    .ends
    GpMatrix typedef Matrix

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

