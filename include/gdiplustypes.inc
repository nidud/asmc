ifndef _GDIPLUSTYPES_H
define _GDIPLUSTYPES_H

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

;;-------------------------------------------------------------------------------
;; Represents a dimension in a 2D coordinate system (floating-point coordinates)
;;-------------------------------------------------------------------------------

;; SizeF() : Width = Height = 0.0f;
;; SizeF(SizeF&)
;; SizeF(REAL, REAL)

.template SizeF fastcall

    Width   REAL ?
    Height  REAL ?

    .static SizeF :abs=<0.0>, :abs=<0.0> {
      ifidn typeid(_1),<ptrSizeF>
        .err <_1>
      elseifidn typeid(_1),<ptrPointF>
        .err <_1>
      elseifidn typeid(_1),<SizeF>
        mov this.Width,_1.Width
        mov this.Height,_1.Height
      elseifidn typeid(_1),<PointF>
        mov this.Width,_1.X
        mov this.Height,_1.Y
      else
       ifidn typeid(_1),<oword>
        movss this.Width,_1
       else
        mov this.Width,_1
       endif
       ifidn typeid(_2),<oword>
        movss this.Height,_2
       else
        mov this.Height,_2
       endif
      endif
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a dimension in a 2D coordinate system (integer coordinates)
;;--------------------------------------------------------------------------

.template Size fastcall

    Width   int_t ?
    Height  int_t ?

    .static Size :abs=<0>, :abs=<0> {
      ifidn typeid(_1),<ptrSize>
        .err <_1>
      elseifidn typeid(_1),<ptrPoint>
        .err <_1>
      elseifidn typeid(_1),<Size>
        mov this.Width,_1.Width
        mov this.Height,_1.Height
      elseifidn typeid(_1),<Point>
        mov this.Width,_1.X
        mov this.Height,_1.Y
      else
        mov this.Width,_1
        mov this.Height,_2
      endif
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a location in a 2D coordinate system (floating-point coordinates)
;;--------------------------------------------------------------------------

.template PointF fastcall

    X   REAL ?
    Y   REAL ?

    .static PointF :abs=<0.0>, :abs=<0.0> {
      ifidn typeid(_1),<ptrSizeF>
        .err <_1>
      elseifidn typeid(_1),<ptrPointF>
        .err <_1>
      elseifidn typeid(_1),<SizeF>
        mov this.X,_1.Width
        mov this.Y,_1.Height
      elseifidn typeid(_1),<PointF>
        mov this.X,_1.X
        mov this.Y,_1.Y
      else
       ifidn typeid(_1),<oword>
        movss this.X,_1
       else
        mov this.X,_1
       endif
       ifidn typeid(_2),<oword>
        movss this.Y,_2
       else
        mov this.Y,_2
       endif
      endif
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a location in a 2D coordinate system (integer coordinates)
;;--------------------------------------------------------------------------

.template Point fastcall

    X   int_t ?
    Y   int_t ?

    .static Point :abs=<0>, :abs=<0> {
      ifidn typeid(_1),<ptrSize>
        .err <_1>
      elseifidn typeid(_1),<ptrPoint>
        .err <_1>
      elseifidn typeid(_1),<Size>
        mov this.X,_1.Width
        mov this.Y,_1.Height
      elseifidn typeid(_1),<Point>
        mov this.X,_1.X
        mov this.Y,_1.Y
      else
        mov this.X,_1
        mov this.Y,_2
      endif
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a rectangle in a 2D coordinate system (floating-point coordinates)
;;--------------------------------------------------------------------------

.template RectF fastcall

    X       REAL ?
    Y       REAL ?
    Width   REAL ?
    Height  REAL ?

    .static RectF :abs=<0.0>, :abs=<0.0>, :abs=<0.0>, :abs=<0.0> {
      ifidn typeid(_1),<PointF>
        mov     this.X,_1.X
        mov     this.Y,_1.Y
        mov     this.Width,_2.Width
        mov     this.Height,_2.Height
      elseifidn typeid(_1),<ptrPointF>
        .err <_1>
      else
       ifidn typeid(_1),<oword>
        movss   this.X,_1
       else
        mov     this.X,_1
       endif
       ifidn typeid(_2),<oword>
        movss   this.Y,_2
       else
        mov     this.Y,_2
       endif
       ifidn typeid(_3),<oword>
        movss   this.Width,_3
       else
        mov     this.Width,_3
       endif
       ifidn typeid(_4),<oword>
        movss   this.Height,_4
       else
        mov     this.Height,_4
       endif
      endif
        }

    .static Clone {
      local n
       .new n:RectF = { this.X, this.Y, this.Width, this.Height }
        lea rax,n
        }

    .static GetLocation :ptr PointF {
        mov     [_1].PointF.X,this.X
        mov     [_1].PointF.Y,this.Y
        }
    .static GetSize :ptr SizeF {
        mov     [_1].SizeF.Width,this.Width
        mov     [_1].SizeF.Height,this.Height
        }
    .static GetBounds :ptr RectF {
        mov     [_1].RectF.X,this.X
        mov     [_1].RectF.Y,this.Y
        mov     [_1].RectF.Width,this.Width
        mov     [_1].RectF.Height,this.Height
        }
    .static GetLeft {
        movss   xmm0,this.X
        }
    .static GetTop {
        movss   xmm0,this.Y
        }
    .static GetRight {
        movss   xmm0,this.X
        addss   xmm0,this.Width
        }
    .static GetBottom {
        movss   xmm0,this.Y
        addss   xmm0,this.Height
        }
    .static IsEmptyArea {
        xor     eax,eax
        movss   xmm0,this.Width
        comiss  xmm0,REAL_EPSILON
        setbe   al
        movss   xmm0,this.Height
        comiss  xmm0,REAL_EPSILON
        setbe   al
        }
    .static Equals :abs {
      ifdif typeid(_1),<RectF>
        .err <_1 -- RectF::Equals(RectF)>
      endif
        mov     eax,this.X
        sub     eax,_1.X
        add     eax,this.Y
        sub     eax,_1.Y
        add     eax,this.Width
        sub     eax,_1.Width
        add     eax,this.Height
        sub     eax,_1.Height
        mov     eax,0
        setz    al
        }

    .static Contains :abs, :abs {
        xor eax,eax
      ifb <_2>
        movss xmm0,_1.X
        movss xmm1,_1.Y
      else
        movss xmm0,_1
        movss xmm1,_2
      endif
        .if ( xmm0 >= this.X && xmm1 >= this.Y )
            subss xmm0,this.Width
            subss xmm1,this.Height
            .if ( xmm0 < this.X && xmm1 < this.Y )
                inc eax
            .endif
        .endif
        }

    .static Inflate :abs, :abs {
      ifb <_2>
        movss   xmm0,_1.X
        movss   xmm1,_1.Y
      else
        movss   xmm0,_1
        movss   xmm1,_2
      endif
        movss   xmm2,this.X
        movss   xmm3,this.Y
        subss   xmm2,xmm0
        subss   xmm3,xmm1
        movss   this.X,xmm2
        movss   this.Y,xmm3
        addss   xmm0,xmm0
        addss   xmm1,xmm1
        addss   xmm0,this.Width
        addss   xmm1,this.Height
        movss   this.Width,xmm0
        movss   this.Height,xmm1
        }

    .static Intersect :abs, :abs {
      local a,b
       ifb <_2>
        a textequ <this>
        b textequ <_1>
       else
        a textequ <_1>
        b textequ <_2>
       endif
        movss   xmm1,a.GetRight()
        minss   xmm1,b.GetRight()
        movss   xmm2,a.GetBottom()
        minss   xmm2,b.GetBottom()
        movss   xmm0,a.X
        maxss   xmm0,b.X
        movss   this.X,xmm0
        subss   xmm1,xmm0
        movss   this.Width,xmm1
        movss   xmm0,a.Y
        maxss   xmm0,b.Y
        movss   this.Y,xmm0
        subss   xmm2,xmm0
        movss   this.Height,xmm2
        xor     this.IsEmptyArea(),1
        }

    .static IntersectsWith :abs {
      ifdif typeid(_1),<RectF>
        .err <_1 -- RectF::IntersectsWith(RectF)>
      endif
        xor eax,eax
        movss xmm0,this.X
        movss xmm1,xmm0
        addss xmm0,this.Width
        .if ( xmm1 < xmm0 )
            movss xmm2,this.Y
            movss xmm3,xmm2
            addss xmm2,this.Height
            .if ( xmm3 < xmm2 )
                .if ( xmm0 > xmm1 )
                    comiss xmm2,xmm3
                    seta al
                .endif
            .endif
        .endif
        }

    .static _Union :abs, :abs {
      ifdif typeid(_1),<RectF>
        .err <_1 -- RectF::_Union(RectF, RectF)>
      endif
        movss   xmm0,_1.X
        addss   xmm0,_1.Width
        movss   xmm1,_2.X
        addss   xmm1,_2.Width
        maxss   xmm0,xmm1           ; right
        movss   xmm1,_1.Y
        addss   xmm1,_1.Height
        movss   xmm2,_2.Y
        addss   xmm2,_2.Height
        maxss   xmm1,xmm2           ; bottom
        movss   xmm2,_1.X
        minss   xmm2,_2.X           ; left
        movss   xmm3,_1.Y
        minss   xmm3,_2.Y           ; top
        movss   this.X,xmm2         ; left
        movss   this.Y,xmm3         ; top
        subss   xmm0,xmm2           ; right - left
        movss   this.Width,xmm0
        subss   xmm1,xmm3           ; bottom - top
        movss   this.Height,xmm1
        xor     this.IsEmptyArea(),1
        }

    .static _Offset :abs, :abs {
      ifidn typeid(_1),<PointF>
        movss xmm0,_1.X
        movss xmm1,_1.Y
      else
        movss xmm0,_1
        movss xmm1,_2
      endif
        addss xmm0,this.X
        addss xmm1,this.Y
        movss this.X,xmm0
        movss this.Y,xmm1
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a rectangle in a 2D coordinate system (integer coordinates)
;;--------------------------------------------------------------------------

.template Rect fastcall

    X       int_t ?
    Y       int_t ?
    Width   int_t ?
    Height  int_t ?

    .static Rect :abs=<0>, :abs=<0>, :abs=<0>, :abs=<0> {
      ifidn typeid(_1),<Point>
        mov this.X,_1.X
        mov this.Y,_1.Y
        mov this.Width,_2.Width
        mov this.Height,_2.Height
      elseifidn typeid(_1),<ptrPoint>
        .err <_1>
      else
        mov this.X,_1
        mov this.Y,_2
        mov this.Width,_3
        mov this.Height,_4
      endif
        }

    .static Clone {
      local n
       .new n:Rect = { this.X, this.Y, this.Width, this.Height }
        lea rax,n
        }

    .static GetLocation :ptr Point {
        mov     [_1].Point.X,this.X
        mov     [_1].Point.Y,this.Y
        }
    .static GetSize :ptr Size {
        mov     [_1].Size.Width,this.Width
        mov     [_1].Size.Height,this.Height
        }
    .static GetBounds :ptr Rect {
        mov     [_1].Rect.X,this.X
        mov     [_1].Rect.Y,this.Y
        mov     [_1].Rect.Width,this.Width
        mov     [_1].Rect.Height,this.Height
        }
    .static GetLeft {
        mov     eax,this.X
        }
    .static GetTop {
        mov     eax,this.Y
        }
    .static GetRight {
        mov     eax,this.X
        add     eax,this.Width
        }
    .static GetBottom {
        mov     eax,this.Y
        add     eax,this.Height
        }
    .static IsEmptyArea {
        xor     eax,eax
        cmp     eax,this.Width
        setge   al
        cmp     this.Height,0
        setle   al
        }
    .static Equals :abs {
      ifdif typeid(_1),<Rect>
        .err <_1 -- Rect::Equals(Rect)>
      endif
        mov     eax,this.X
        sub     eax,_1.X
        add     eax,this.Y
        sub     eax,_1.Y
        add     eax,this.Width
        sub     eax,_1.Width
        add     eax,this.Height
        sub     eax,_1.Height
        mov     eax,0
        setz    al
        }

    .static Contains :abs, :abs {
        xor eax,eax
      ifb <_2>
        mov ecx,_1.X
        mov edx,_1.Y
      else
        mov ecx,_1
        mov edx,_2
      endif
        .ifs ( ecx >= this.X && edx >= this.Y )
            sub ecx,this.Width
            sub edx,this.Height
            .ifs ( ecx < this.X && edx < this.Y )
                inc eax
            .endif
        .endif
        }

    .static Inflate :abs, :abs {
      ifb <_2>
        mov ecx,_1.X
        mov edx,_1.Y
      else
        mov ecx,_1
        mov edx,_2
      endif
        sub this.X,ecx
        sub this.Y,edx
        add ecx,ecx
        add edx,edx
        add this.Width,ecx
        add this.Height,edx
        }

    .static Intersect :abs, :abs {
      local a,b
       ifb <_2>
        a textequ <this>
        b textequ <_1>
       else
        a textequ <_1>
        b textequ <_2>
       endif
        mov     edx,a.GetRight()
        cmp     edx,b.GetRight()
        cmovl   eax,edx
        mov     this.Width,eax
        mov     edx,a.GetBottom()
        cmp     edx,b.GetBottom()
        cmovl   eax,edx
        mov     this.Height,eax
        mov     edx,a.X
        mov     eax,b.X
        cmp     edx,eax
        cmovg   eax,edx
        mov     this.X,eax
        sub     this.Width,eax
        mov     edx,a.Y
        mov     eax,b.Y
        cmp     edx,eax
        cmovg   eax,edx
        mov     this.Y,eax
        sub     this.Height,eax
        xor     this.IsEmptyArea(),1
        }

    .static IntersectsWith :abs {
        xor eax,eax
        mov ecx,_1.X
        add ecx,_1.Width
        mov edx,_1.Y
        add edx,_1.Height
        .ifs ( this.X < ecx && this.Y < edx )
            mov edx,this.X
            add edx,this.Width
            .if edx > _1.X
                mov edx,this.Y
                add edx,this.Height
                .if edx > _1.Y
                    mov eax,1
                .endif
            .endif
        .endif
        }

    .static _Union a:abs, b:abs {
        mov     edx,a.GetRight()
        cmp     edx,b.GetRight()
        cmovg   eax,edx
        mov     this.Width,eax
        mov     edx,a.GetBottom()
        cmp     edx,b.GetBottom()
        cmovg   eax,edx
        mov     this.Height,eax
        mov     edx,a.X
        mov     eax,b.X
        cmp     edx,eax
        cmovl   eax,edx
        mov     this.X,eax
        sub     this.Width,eax
        mov     edx,a.Y
        mov     eax,b.Y
        cmp     edx,eax
        cmovl   eax,edx
        mov     this.Y,eax
        sub     this.Height,eax
        xor     this.IsEmptyArea(),1
        }

    .static _Offset :abs, :abs {
      ifidn typeid(_1),<Point>
        mov ecx,_1.X
        mov edx,_1.Y
      elseifidn typeid(_1),<ptrPoint>
        .err <_1>
      else
        mov ecx,_1
        mov edx,_2
      endif
        add this.X,ecx
        add this.Y,edx
        }
    .ends


.template PathData fastcall

    Count   int_t ?
    Points  ptr_t ?
    Types   ptr_t ?

    .inline PathData :vararg {
        xor eax,eax
        mov this.Count,  eax
        mov this.Points, rax
        mov this.Types,  rax
        }

    .static Release {
        mov rcx,this.Points
        .if rcx != NULL
            GdipFree(rcx)
        .endif
        mov rcx,this.Types
        .if rcx != NULL
            GdipFree(rcx)
        .endif
        }
    .ends


.template CharacterRange fastcall

    First   int_t ?
    Length  int_t ?

    .static CharacterRange :abs, :abs {
    ifb <_1>
        mov this.First,0
        mov this.Length,0
    elseifidn <CharacterRange>,typeid(_1)
        mov this.First,_1.First
        mov this.Length,_1.Length
    else
        mov this.First,_1
      ifb <_2>
        mov this.Length,0
      else
        mov this.Length,_2
      endif
    endif
        }
    .ends

.enum GDI_Types {
    GDI_Unknown,
    GDI_Int,
    GDI_Real,
    GDI_Size,
    GDI_SizeF,
    GDI_Point,
    GDI_PointF,
    GDI_Rect,
    GDI_RectF,
    GDI_PSize,
    GDI_PSizeF,
    GDI_PPoint,
    GDI_PPointF,
    GDI_PRect,
    GDI_PRectF
    }

GDIType macro arg
ifidn <imm>,typeid(arg)
    exitm<GDI_Int>
elseifidn <sdword>,typeid(arg)
    exitm<GDI_Int>
elseifidn <flt>,typeid(arg)
    exitm<GDI_Real>
elseifidn <real4>,typeid(arg)
    exitm<GDI_Real>
elseifidn <oword>,typeid(arg)
    exitm<GDI_Real>
elseifidn <Size>,typeid(arg)
    exitm<GDI_Size>
elseifidn <SizeF>,typeid(arg)
    exitm<GDI_SizeF>
elseifidn <Point>,typeid(arg)
    exitm<GDI_Point>
elseifidn <PointF>,typeid(arg)
    exitm<GDI_PointF>
elseifidn <Rect>,typeid(arg)
    exitm<GDI_Rect>
elseifidn <RectF>,typeid(arg)
    exitm<GDI_RectF>
elseifidn <ptrSize>,typeid(arg)
    exitm<GDI_PSize>
elseifidn <ptrSizeF>,typeid(arg)
    exitm<GDI_PSizeF>
elseifidn <ptrPoint>,typeid(arg)
    exitm<GDI_PPoint>
elseifidn <ptrPointF>,typeid(arg)
    exitm<GDI_PPointF>
elseifidn <ptrRect>,typeid(arg)
    exitm<GDI_PRect>
elseifidn <ptrRectF>,typeid(arg)
    exitm<GDI_PRectF>
endif
    exitm<GDI_Unknown>
    endm

endif ;; NOT _GDIPLUSTYPES_HPP

