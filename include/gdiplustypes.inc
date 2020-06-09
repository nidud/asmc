ifndef _GDIPLUSTYPES_H
_GDIPLUSTYPES_H equ <>

;;--------------------------------------------------------------------------
;; Callback functions
;;--------------------------------------------------------------------------

CALLBACK(ImageAbort)

DrawImageAbort          typedef ImageAbort
GetThumbnailImageAbort  typedef ImageAbort

;; Callback for EnumerateMetafile methods.  The parameters are:

;;      recordType      WMF, EMF, or EMF+ record type
;;      flags           (always 0 for WMF/EMF records)
;;      dataSize        size of the record data (in bytes), or 0 if no data
;;      data            pointer to the record data, or NULL if no data
;;      callbackData    pointer to callbackData, if any

;; This method can then call Metafile::PlayRecord to play the
;; record that was just enumerated.  If this method  returns
;; FALSE, the enumeration process is aborted.  Otherwise, it continues.

CALLBACK(EnumerateMetafileProc, :ptr, :UINT, :UINT, :ptr, :ptr)

if (GDIPVER GE 0x0110)
;; This is the main GDI+ Abort interface
.template GdiplusAbort
    Abort   proc
    .ends
endif

;;--------------------------------------------------------------------------
;; Forward declarations of common classes
;;--------------------------------------------------------------------------

Size_t              typedef ptr Size
SizeF_t             typedef ptr SizeF
Point_t             typedef ptr Point
PointF_t            typedef ptr PointF
Rect_t              typedef ptr Rect
RectF_t             typedef ptr RectF
CharacterRange_t    typedef ptr CharacterRange

;;--------------------------------------------------------------------------
;; Primitive data types
;;
;; NOTE:
;;  Types already defined in standard header files:
;;      INT8
;;      UINT8
;;      INT16
;;      UINT16
;;      INT32
;;      UINT32
;;      INT64
;;      UINT64
;;
;;  Avoid using the following types:
;;      LONG - use INT
;;      ULONG - use UINT
;;      DWORD - use UINT32
;;--------------------------------------------------------------------------

REAL            typedef REAL4

REAL_MAX        equ FLT_MAX
REAL_MIN        equ FLT_MIN
REAL_TOLERANCE  equ (FLT_MIN * 100.0)
REAL_EPSILON    equ 1.192092896e-07

;;--------------------------------------------------------------------------
;; Status return values from GDI+ methods
;;--------------------------------------------------------------------------

.enum Status {
    Ok,
    GenericError,
    InvalidParameter,
    OutOfMemory,
    ObjectBusy,
    InsufficientBuffer,
    NotImplemented,
    Win32Error,
    WrongState,
    Aborted,
    FileNotFound,
    ValueOverflow,
    AccessDenied,
    UnknownImageFormat,
    FontFamilyNotFound,
    FontStyleNotFound,
    NotTrueTypeFont,
    UnsupportedGdiplusVersion,
    GdiplusNotInitialized,
    PropertyNotFound,
    PropertyNotSupported,
if (GDIPVER GE 0x0110)
    ProfileNotFound,
endif
    }

;;--------------------------------------------------------------------------
;; Represents a dimension in a 2D coordinate system (floating-point coordinates)
;;--------------------------------------------------------------------------

;; SizeF() : Width = Height = 0.0f;
;; SizeF(SizeF*)
;; SizeF(REAL, REAL)

.template SizeF

    Width   REAL ?
    Height  REAL ?

    .operator SizeF :abs, :vararg {
        ifb <_1>
            mov this.Width,0.0
            mov this.Height,0.0
        else
            this.typeid(SizeF, _1)(_1, _2)
        endif
        }
    .operator SizeF?flt :abs, :vararg {
        mov this.Width,_1
        mov this.Height,_2
        }
    .operator SizeF?r128 :REAL, :REAL {
        movss   [this].SizeF.Width,  _1
        movss   [this].SizeF.Height, _2
        }
    .operator SizeF?pSizeF :ptr SizeF {
        mov     [this].SizeF.Width,  [_1].SizeF.Width
        mov     [this].SizeF.Height, [_1].SizeF.Height
        }

    .operator + :SizeF_t {
        movss   xmm0,[_1].SizeF.Width
        movss   xmm1,[_1].SizeF.Height
        addss   [this].SizeF.Width,xmm0
        addss   [this].SizeF.Height,xmm1
        }
    .operator - :SizeF_t {
        movss   xmm0,[_1].SizeF.Width
        movss   xmm1,[_1].SizeF.Height
        subss   [this].SizeF.Width,xmm0
        subss   [this].SizeF.Height,xmm1
        }
    .operator Equals :SizeF_t {
        .if [this].SizeF.Width == [_1].SizeF.Width && [this].SizeF.Height == [_1].SizeF.Height
            mov eax,1
        .else
            xor eax,eax
        .elseif
        }
    .operator Empty {
        xor eax,eax
        .if [this].SizeF.Width == eax && [this].SizeF.Height == eax
            inc eax
        .elseif
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a dimension in a 2D coordinate system (integer coordinates)
;;--------------------------------------------------------------------------

.template Size

    Width   int_t ?
    Height  int_t ?

    .operator Size :abs, :vararg {
        ifb <_1>
            mov this.Width,0
            mov this.Height,0
        else
            this.typeid(Size, _1)(_1, _2)
        endif
        }
    .operator Size?i32 :abs, :vararg {
        mov this.Width,_1
        mov this.Height,_2
        }
    .operator Size?r32 :int_t, :int_t {
        movss   [this].Size.Width,  _1
        movss   [this].Size.Height, _2
        }
    .operator Size?pSize :ptr Size {
        mov     [this].Size.Width,  [_1].Size.Width
        mov     [this].Size.Height, [_1].Size.Height
        }

    .operator + :Size_t {
        add     [this].Size.Width,  [_1].Size.Width
        add     [this].Size.Height, [_1].Size.Height
        }
    .operator - :Size_t {
        sub     [this].Size.Width,  [_1].Size.Width
        sub     [this].Size.Height, [_1].Size.Height
        }
    .operator Equals :Size_t {
        .if [this].Size.Width == [_1].Size.Width && [this].Size.Height == [_1].Size.Height
            mov eax,1
        .else
            xor eax,eax
        .elseif
        retm<eax>
        }
    .operator Empty {
        xor eax,eax
        .if [this].Size.Width == eax && [this].Size.Height == eax
            inc eax
        .elseif
        retm<eax>
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a location in a 2D coordinate system (floating-point coordinates)
;;--------------------------------------------------------------------------
;.pragma list(push, 1)

.template PointF

    X   REAL ?
    Y   REAL ?

    .operator PointF :abs, :vararg {
        ifb <_1>
            mov this.X,0.0
            mov this.Y,0.0
        else
            this.typeid(PointF, _1)(_1, _2)
        endif
        }
    .operator PointF?flt :abs, :abs, :vararg {
        mov     this.X,_1
        mov     this.Y,_2
        }
    .operator PointF?r128 :REAL, :REAL {
        movss   [this].PointF.X,_1
        movss   [this].PointF.Y,_2
        }
    .operator PointF?pPointF :ptr PointF {
        mov     [this].PointF.X,[_1].PointF.X
        mov     [this].PointF.Y,[_1].PointF.Y
        }
    .operator PointF?pSizeF :ptr SizeF {
        mov     [this].PointF.X,[_1].SizeF.Width
        mov     [this].PointF.Y,[_1].SizeF.Height
        }
    .operator + :PointF_t {
        movss   xmm0,[_1].PointF.X
        movss   xmm1,[_1].PointF.Y
        addss   [this].PointF.X,xmm0
        addss   [this].PointF.Y,xmm1
        }
    .operator - :PointF_t {
        movss   xmm0,[_1].PointF.X
        movss   xmm1,[_1].PointF.Y
        subss   [this].PointF.X,xmm0
        subss   [this].PointF.Y,xmm1
        }
    .operator Equals :PointF_t {
        .if [this].PointF.X == [_1].PointF.X && [this].PointF.Y == [_1].PointF.Y
            mov eax,1
        .else
            xor eax,eax
        .elseif
        retm<eax>
        }
    .ends
;.pragma list(pop)

;;--------------------------------------------------------------------------
;; Represents a location in a 2D coordinate system (integer coordinates)
;;--------------------------------------------------------------------------

.template Point

    X   int_t ?
    Y   int_t ?

    .operator Point :abs, :vararg {
        ifb <_1>
            mov this.X,0
            mov this.Y,0
        else
            this.typeid(Point, _1)(_1, _2)
        endif
        }
    .operator Point?i32 :abs, :vararg {
        mov     this.X,_1
        mov     this.Y,_2
        }
    .operator Point?r32 :int_t, :int_t {
        mov     [this].Point.X,_1
        mov     [this].Point.Y,_2
        }
    .operator Point?sdword :int_t, :int_t {
        mov     [this].Point.X,_1
        mov     [this].Point.Y,_2
        }
    .operator Point?pPoint :ptr Point {
        mov     [this].Point.X,[_1].Point.X
        mov     [this].Point.Y,[_1].Point.Y
        }
    .operator Point?pSize :ptr Size {
        mov     [this].Point.X,[_1].Size.Width
        mov     [this].Point.Y,[_1].Size.Height
        }
    .operator + :ptr {
        add     [this].Point.X,[_1].Point.X
        add     [this].Point.Y,[_1].Point.Y
        }
    .operator - :ptr {
        sub     [this].Point.X,[_1].Point.X
        sub     [this].Point.Y,[_1].Point.Y
        }
    .operator Equals :ptr {
        .if [this].Point.X == [_1].Point.X && [this].Point.Y == [_1].Point.Y
            mov eax,1
        .else
            xor eax,eax
        .elseif
        retm<eax>
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a rectangle in a 2D coordinate system (floating-point coordinates)
;;--------------------------------------------------------------------------

.template RectF

    X       REAL ?
    Y       REAL ?
    Width   REAL ?
    Height  REAL ?

    .operator RectF :abs, :vararg {
        ifb <_1>
            xor eax,eax
            mov qword ptr this[0],rax
            mov qword ptr this[8],rax
        else
            this.typeid(RectF, _1)(_1, _2)
        endif
        }
    .operator RectF?flt :abs, :abs, :abs, :abs {
        mov     [this].RectF.X,_1
        mov     [this].RectF.Y,_2
        mov     [this].RectF.Width,_3
        mov     [this].RectF.Height,_4
        }
    .operator RectF?real8 :vararg {
        this.RectF?flt(_1)
        }
    .operator RectF?r128 :REAL, :REAL, :REAL, :REAL {
        movss   [this].RectF.X,_1
        movss   [this].RectF.Y,_2
        movss   [this].RectF.Width,_3
        movss   [this].RectF.Height,_4
        }
    .operator RectF?pPointF :ptr PointF, :ptr SizeF {
        mov     qword ptr [this],[_1]
        mov     qword ptr [this+8],[_2]
        }

    .operator Clone {
        exitm<.err>
        }
    .operator GetLocation :ptr PointF {
        mov     [_1].PointF.X, [this].RectF.X
        mov     [_1].PointF.Y, [this].RectF.Y
        }
    .operator GetSize :ptr SizeF {
        mov     [_1].SizeF.Width,   [this].RectF.Width
        mov     [_1].SizeF.Height,  [this].RectF.Height
        }
    .operator GetBounds :ptr RectF {
        mov     [_1].RectF.X,       [this].RectF.X
        mov     [_1].RectF.Y,       [this].RectF.Y
        mov     [_1].RectF.Width,   [this].RectF.Width
        mov     [_1].RectF.Height,  [this].RectF.Height
        }
    .operator GetLeft {
        movss   xmm0,[this].RectF.X
        }
    .operator GetTop {
        movss   xmm0,[this].RectF.Y
        }
    .operator GetRight {
        movss   xmm0,[this].RectF.X
        addss   xmm0,[this].RectF.Width
        }
    .operator GetBottom {
        movss   xmm0,[this].RectF.Y
        addss   xmm0,[this].RectF.Height
        }
    .operator IsEmptyArea {
        mov     eax,REAL_EPSILON
        movd    xmm1,eax
        movss   xmm0,[this].RectF.Width
        comiss  xmm0,xmm1
        .ifna
            mov eax,1
        .else
            movss   xmm0,[this].RectF.Height
            comiss  xmm0,xmm1
            mov     eax,0
            setna   al
        .endif
        }
    .operator Equals :ptr {
        .if [this].RectF.X      == [_1].RectF.X && \
            [this].RectF.Y      == [_1].RectF.Y && \
            [this].RectF.Width  == [_1].RectF.Width && \
            [this].RectF.Height == [_1].RectF.Height
            mov eax,1
        .else
            xor eax,eax
        .elseif
        }
    .operator Contains :REAL, :REAL {
        xor     eax,eax
        comiss  xmm0,[this].RectF.X
        .ifnb
            comiss xmm1,[this].RectF.Y
            .ifnb
                movss xmm2,[this].RectF.Width
                addss xmm2,[this].RectF.X
                comiss xmm0,xmm2
                .ifb
                    movss xmm2,[this].RectF.Height
                    addss xmm2,[this].RectF.Y
                    comiss xmm1,xmm2
                    setb al
                .endif
            .endif
        .endif
        }
    .operator ContainsP :ptr PointF {
        [this].RectF.Contains([_1].PointF.X, [_1].PointF.Y)
        }
    .operator ContainsR :ptr RectF {
        xor     eax,eax
        movss   xmm0,[this].RectF.X
        comiss  xmm0,[_1].RectF.X
        .ifna
            movss   xmm1,[this].RectF.Y
            comiss  xmm1,[_1].RectF.Y
            .ifna
                movss   xmm0,[_1].RectF.X
                addss   xmm0,[_1].RectF.Width
                movss   xmm1,[this].RectF.X
                addss   xmm1,[this].RectF.Width
                comiss  xmm0,xmm1
                .ifna
                    movss   xmm0,[_1].RectF.Y
                    addss   xmm0,[_1].RectF.Height
                    movss   xmm1,[this].RectF.Y
                    addss   xmm1,[this].RectF.Height
                    comiss  xmm0,xmm1
                    setna   al
                .endif
            .endif
        .endif
        }
    .operator Inflate :REAL, :REAL {
        subss   [this].RectF.X,_1
        subss   [this].RectF.Y,_2
        mov     eax,2.0
        movd    xmm0,eax
        mulss   _1,xmm0
        mulss   _2,xmm0
        addss   [this].RectF.Width,_1
        addss   [this].RectF.Height,_2
        }
    .operator InflateP :ptr Point {
        cvtsi2ss xmm1,[_1].Point.X
        cvtsi2ss xmm2,[_1].Point.Y
        [this].RectF.Inflate(xmm1, xmm2)
        }
    .operator Intersect :ptr RectF, :ptr RectF {
        movss   xmm0,[_1].RectF.X
        addss   xmm0,[_1].RectF.Width
        movss   xmm1,[_2].RectF.X
        addss   xmm1,[_2].RectF.Width
        minss   xmm0,xmm1           ; right
        movss   xmm1,[_1].RectF.Y
        addss   xmm1,[_1].RectF.Height
        movss   xmm2,[_2].RectF.Y
        addss   xmm2,[_2].RectF.Height
        minss   xmm1,xmm2           ; bottom
        movss   xmm2,[_1].RectF.X
        maxss   xmm2,[_2].RectF.X   ; left
        movss   xmm3,[_1].RectF.Y
        maxss   xmm3,[_2].RectF.Y   ; top
        movss   [this].RectF.X,xmm2 ; left
        movss   [this].RectF.Y,xmm3 ; top
        subss   xmm0,xmm2           ; right - left
        movss   [this].RectF.Width,xmm0
        subss   xmm1,xmm3           ; bottom - top
        movss   [this].RectF.Height,xmm1
        xor     [this].RectF.IsEmptyArea(),1
    }
    .operator IntersectR :ptr RectF {
        [this].RectF.Intersect(this, _1)
        }
    .operator IntersectsWith :ptr RectF {
        xor     eax,eax
        movss   xmm1,RectF::GetLeft(this)
        comiss  xmm1,RectF::GetRight(_1)
        .ifb
            movss xmm1,RectF::GetTop(this)
            comiss xmm1,RectF::GetBottom(_1)
            .ifb
                movss xmm1,RectF::GetRight(this)
                comiss xmm1,RectF::GetLeft(_1)
                .ifa
                    movss xmm1,RectF::GetBottom(this)
                    comiss xmm1,RectF::GetTop(_1)
                    seta al
                .endif
            .endif
        .endif
        }
    .operator _Union :ptr RectF, :ptr RectF {
        movss   xmm0,[_1].RectF.X
        addss   xmm0,[_1].RectF.Width
        movss   xmm1,[_2].RectF.X
        addss   xmm1,[_2].RectF.Width
        maxss   xmm0,xmm1           ; right
        movss   xmm1,[_1].RectF.Y
        addss   xmm1,[_1].RectF.Height
        movss   xmm2,[_2].RectF.Y
        addss   xmm2,[_2].RectF.Height
        maxss   xmm1,xmm2           ; bottom
        movss   xmm2,[_1].RectF.X
        minss   xmm2,[_2].RectF.X   ; left
        movss   xmm3,[_1].RectF.Y
        minss   xmm3,[_2].RectF.Y   ; top
        movss   [this].RectF.X,xmm2 ; left
        movss   [this].RectF.Y,xmm3 ; top
        subss   xmm0,xmm2           ; right - left
        movss   [this].RectF.Width,xmm0
        subss   xmm1,xmm3           ; bottom - top
        movss   [this].RectF.Height,xmm1
        xor     RectF::IsEmptyArea(this),1
        }
    .operator _Offset :REAL, :REAL {
        addss   [this].RectF.X,_1
        addss   [this].RectF.Y,_2
        }
    .operator OffsetP :ptr PointF {
        [this].RectF._Offset([_1].RectF.X, [_1].RectF.Y)
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a rectangle in a 2D coordinate system (integer coordinates)
;;--------------------------------------------------------------------------

.template Rect

    X       int_t ?
    Y       int_t ?
    Width   int_t ?
    Height  int_t ?

    .operator Rect :abs, :vararg {
        ifb <_1>
            xor eax,eax
            mov qword ptr this[0],rax
            mov qword ptr this[8],rax
        else
            this.typeid(Rect, _1)(_1, _2)
        endif
        }
    .operator Rect?i32 :abs, :abs, :abs, :abs {
        mov     [this].Rect.X,_1
        mov     [this].Rect.Y,_2
        mov     [this].Rect.Width,_3
        mov     [this].Rect.Height,_4
        }
    .operator Rect?r32    :vararg { this.Rect?i32(_1) }
    .operator Rect?dword  :vararg { this.Rect?i32(_1) }
    .operator Rect?sdword :vararg { this.Rect?i32(_1) }
    .operator Rect?pPoint :ptr Point, :ptr Size {
        mov     qword ptr [this],[_1]
        mov     qword ptr [this+8],[_2]
        }

    .operator Clone :ptr Rect {
        mov     qword ptr [this+0],[_1+0]
        mov     qword ptr [this+8],[_1+8]
        }
    .operator GetLocation :ptr Point {
        mov     qword ptr [_1],[this+0]
        }
    .operator GetSize :ptr Size {
        mov     qword ptr [_1],[this+8]
        }
    .operator GetBounds :ptr Rect {
        mov     qword ptr [_1+0],[this+0]
        mov     qword ptr [_1+8],[this+8]
        }
    .operator GetLeft {
        mov     eax,[this].Rect.X
        }
    .operator GetTop {
        mov     eax,[this].Rect.Y
        }
    .operator GetRight {
        mov     eax,[this].Rect.X
        add     eax,[this].Rect.Width
        }
    .operator GetBottom {
        mov     eax,[this].Rect.Y
        add     eax,[this].Rect.Height
        }
    .operator IsEmptyArea {
        xor eax,eax
        .if [this].Rect.Width <= eax || [this].Rect.Height <= eax
            inc eax
        .endif
        }
    .operator Equals :ptr Rect {
        .if [this].Rect.X == [_1].Rect.X && \
            [this].Rect.Y == [_1].Rect.Y && \
            [this].Rect.Width == [_1].Rect.Width && \
            [this].Rect.Height == [_1].Rect.Height
            mov eax,1
        .else
            xor eax,eax
        .endif
        }
    .operator Contains :int_t, :int_t {
        xor eax,eax
        .if ( _1 >= [this].Rect.X && _2 >= [this].Rect.Y )
            sub _1,[this].Rect.Width
            sub _2,[this].Rect.Height
            .if ( _1 < [this].Rect.X && _2 < [this].Rect.Y )
                inc eax
            .endif
        .endif
        }
    .operator ContainsP :ptr Point {
        [this].Rect.Contains([_1].Point.X, [_1].Point.Y)
        }
    .operator ContainsR :ptr Rect {
        push    rsi
        push    rdi
        mov     edi,[_1].Rect.X
        add     edi,[_1].Rect.Width
        mov     esi,[this].Rect.X
        add     esi,[this].Rect.Width
        .ifs ( [this].Rect.X <= [_1].Rect.X && [this].Rect.Y <= [_1].Rect.Y && edi <= esi )
            xor eax,eax
            mov esi,[_1].Rect.Y
            add esi,[_1].Rect.Height
            mov edi,[this].Rect.Y
            add edi,[this].Rect.Height
            .ifs ( esi <= edi )
                mov eax,1
            .endif
        .else
            xor eax,eax
        .endif
        pop     rdi
        pop     rsi
        }
    .operator Inflate :int_t, :int_t {
        sub     [this].Rect.X,_1
        sub     [this].Rect.Y,_2
        add     _1,_1
        add     _2,_2
        add     [this].Rect.Width,_1
        add     [this].Rect.Height,_2
        }
    .operator InflateP :ptr Point {
        [this].Rect.Inflate([_1].Point.X, [_1].Point.Y)
        }
    .operator Intersect :ptr Rect, :ptr Rect {
        mov     eax,[_1].Rect.X
        add     eax,[_1].Rect.Width
        cvtsi2ss xmm0,eax
        mov     eax,[_2].Rect.X
        add     eax,[_2].Rect.Width
        cvtsi2ss xmm1,eax
        minss   xmm0,xmm1           ; right
        mov     eax,[_1].Rect.Y
        add     eax,[_1].Rect.Height
        cvtsi2ss xmm1,eax
        mov     eax,[_2].Rect.Y
        add     eax,[_2].Rect.Height
        cvtsi2ss xmm2,eax
        minss   xmm1,xmm2           ; bottom
        cvtsi2ss xmm2,[_1].Rect.X
        cvtsi2ss xmm3,[_2].Rect.X
        maxss   xmm2,xmm3           ; left
        cvtsi2ss xmm3,[_1].Rect.Y
        cvtsi2ss xmm4,[_2].Rect.Y
        maxss   xmm3,xmm4           ; top
        cvtss2si eax,xmm2
        mov     [this].Rect.X,eax   ; left
        cvtss2si eax,xmm3
        mov     [this].Rect.Y,eax   ; top
        subss   xmm0,xmm2           ; right - left
        cvtss2si eax,xmm0
        mov     [this].Rect.Width,eax
        subss   xmm1,xmm3           ; bottom - top
        cvtss2si eax,xmm1
        mov     [this].Rect.Height,eax
        xor     [this].Rect.IsEmptyArea(),1
    }
    .operator IntersectR :ptr Rect {
        [this].Rect.Intersect(this, _1)
        }
    .operator IntersectsWith :ptr Rect {
        xor     eax,eax
        push    rsi
        push    rdi
        mov     edi,[_1].Rect.X
        add     edi,[_1].Rect.Width
        mov     esi,[_1].Rect.Y
        add     esi,[_1].Rect.Height
        .ifs ( [this].Rect.X < edi && [this].Rect.Y < esi )
            mov esi,[this].Rect.X
            add esi,[this].Rect.Width
            .if esi > [_1].Rect.X
                mov esi,[this].Rect.Y
                add esi,[this].Rect.Height
                .if esi > [_1].Rect.Y
                    mov eax,1
                .endif
            .endif
        .endif
        pop     rdi
        pop     rsi
        }
    .operator _Union :ptr Rect, :ptr Rect {
        mov     eax,[_1].Rect.X
        add     eax,[_1].Rect.Width
        cvtsi2ss xmm0,eax
        mov     eax,[_2].Rect.X
        add     eax,[_2].Rect.Width
        cvtsi2ss xmm1,eax
        maxss   xmm0,xmm1           ; right
        mov     eax,[_1].Rect.Y
        add     eax,[_1].Rect.Height
        cvtsi2ss xmm1,eax
        mov     eax,[_2].Rect.Y
        add     eax,[_2].Rect.Height
        cvtsi2ss xmm2,eax
        maxss   xmm1,xmm2           ; bottom
        cvtsi2ss xmm2,[_1].Rect.X
        cvtsi2ss xmm3,[_2].Rect.X
        minss   xmm2,xmm3           ; left
        cvtsi2ss xmm3,[_1].Rect.Y
        cvtsi2ss xmm4,[_2].Rect.Y
        minss   xmm3,xmm4           ; top
        cvtss2si eax,xmm2
        mov     [this].Rect.X,eax   ; left
        cvtss2si eax,xmm3
        mov     [this].Rect.Y,eax   ; top
        subss   xmm0,xmm2           ; right - left
        cvtss2si eax,xmm0
        mov     [this].Rect.Width,eax
        subss   xmm1,xmm3           ; bottom - top
        cvtss2si eax,xmm1
        mov     [this].Rect.Height,eax
        xor     [this].Rect.IsEmptyArea(),1
        }
    .operator _Offset :int_t, :int_t {
        add     [this].Rect.X,_1
        add     [this].Rect.Y,_2
        }
    .operator OffsetP :ptr Point {
        [this].Rect._Offset([_1].Rect.X, [_1].Rect.Y)
        }
    .ends

.template PathData

    Count   int_t ?
    Points  ptr_t ?
    Types   ptr_t ?

    .operator PathData {
        mov     [this].PathData.Count,0
        mov     [this].PathData.Points,NULL
        mov     [this].PathData.Types,NULL
        }
    .operator Release {
        .if ([this].PathData.Points != NULL)
            ;delete [] Points;
        .endif
        .if ([this].PathData.Types != NULL)
            ;delete [] Types;
        .endif
        exitm   <>
        }
    .operator = :ptr {
        exitm   <>
        }
    .ends

.template CharacterRange

    First   int_t ?
    Length  int_t ?

    .operator CharacterRange :abs, :vararg {
        this.typeid(CharacterRange, _1)(_1, _2)
        }
    .operator CharacterRange?i32 :abs, :abs {
        mov     [this].CharacterRange.First,_1
        mov     [this].CharacterRange.Length,_2
        }
    .operator CharacterRange?pCharacterRange :ptr CharacterRange {
        mov     [this].CharacterRange.First,  [_1].CharacterRange.First
        mov     [this].CharacterRange.Length, [_1].CharacterRange.Length
        }
    .ends

endif ;; NOT _GDIPLUSTYPES_HPP

