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

;;-------------------------------------------------------------------------------
;; Represents a dimension in a 2D coordinate system (floating-point coordinates)
;;-------------------------------------------------------------------------------

;; SizeF() : Width = Height = 0.0f;
;; SizeF(SizeF*)
;; SizeF(REAL, REAL)

.template SizeF

    Width   REAL ?
    Height  REAL ?

    .operator SizeF :vararg {
        ifidn typeid(?, this),<?SizeF>
            this.T?T(_1)
        else
            [rcx].SizeF.typeid(T, this)(_1)
        endif
        }
        .operator T?T :abs, :vararg {
            this.typeid(T?T, _1)(_1, _2)
            }
            .operator T?T?i0     :vararg { this.T?T?flt() }
            .operator T?T?dword  :vararg { this.T?T?flt(_1) }
            .operator T?T?sdword :vararg { this.T?T?flt(_1) }
            .operator T?T?r32    :vararg { this.T?T?flt(_1) }
            .operator T?T?r128   :vararg { this.T?T?real4(_1) }
            .operator T?T?flt :abs=<0.0>, :abs=<0.0>, :vararg {
                mov this.Width,_1
                mov this.Height,_2
                }
            .operator T?T?real4 :real4, :real4, :vararg {
                movss this.Width,xmm1
                movss this.Height,xmm2
                }
            .operator T?T?pPointF :ptr PointF {
                mov qword ptr [this],[_1]
                }
            .operator T?T?pSizeF :ptr SizeF {
                mov qword ptr [this],[_1]
                }
        .operator T?i32 :vararg {
          local t
           .new t:SizeF
            t.T?T(_1)
            lea rax,t
            }

    .operator + :ptr SizeF {
        movss   xmm0,[_1].SizeF.Width
        movss   xmm1,[_1].SizeF.Height
        addss   xmm0,[this].SizeF.Width
        addss   xmm1,[this].SizeF.Height
        movss   [this].SizeF.Width,xmm0
        movss   [this].SizeF.Height,xmm1
        }
    .operator - :ptr SizeF {
        movss   xmm0,[this].SizeF.Width
        movss   xmm1,[this].SizeF.Height
        subss   xmm0,[_1].SizeF.Width
        subss   xmm1,[_1].SizeF.Height
        movss   [this].SizeF.Width,xmm0
        movss   [this].SizeF.Height,xmm1
        }
    .operator Equals :ptr SizeF {
        mov   rax,[this]
        sub   rax,[_1]
        mov   eax,0
        setz  al
        }
    .operator Empty {
        mov   rax,[this]
        test  rax,rax
        mov   eax,0
        setz  al
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a dimension in a 2D coordinate system (integer coordinates)
;;--------------------------------------------------------------------------

.template Size

    Width   int_t ?
    Height  int_t ?

    .operator Size :vararg {
        ifidn typeid(?, this),<?Size>
            this.T?T(_1)
        else
            [rcx].Size.typeid(T, this)(_1)
        endif
        }
        .operator T?T :abs, :vararg {
            this.typeid(T?T, _1)(_1, _2)
            }
            .operator T?T?i0     :vararg { this.T?T?i32() }
            .operator T?T?r32    :vararg { this.T?T?i32(_1) }
            .operator T?T?dword  :vararg { this.T?T?i32(_1) }
            .operator T?T?sdword :vararg { this.T?T?i32(_1) }
            .operator T?T?i32 :abs=<0>, :abs=<0>, :vararg {
                mov this.Width,_1
                mov this.Height,_2
                }
            .operator T?T?pPoint :ptr Point {
                mov qword ptr [this],[_1]
                }
            .operator T?T?pSize :ptr Size {
                mov qword ptr [this],[_1]
                }
        .operator T?i32 :vararg {
          local t
           .new t:Size
            t.T?T(_1)
            lea rax,t
            }

    .operator + :ptr Size {
        add [this].Size.Width,  [_1].Size.Width
        add [this].Size.Height, [_1].Size.Height
        }
    .operator - :ptr Size {
        sub [this].Size.Width,  [_1].Size.Width
        sub [this].Size.Height, [_1].Size.Height
        }
    .operator Equals :ptr Size {
        mov   rax,[this]
        sub   rax,[_1]
        mov   eax,0
        setz  al
        }
    .operator Empty {
        mov   rax,[this]
        test  rax,rax
        mov   eax,0
        setz  al
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a location in a 2D coordinate system (floating-point coordinates)
;;--------------------------------------------------------------------------

.template PointF

    X   REAL ?
    Y   REAL ?

    .operator PointF :vararg {
        ifidn typeid(?, this),<?PointF>
            this.T?T(_1)
        else
            [rcx].PointF.typeid(T, this)(_1)
        endif
        }
        .operator T?T :abs, :vararg {
            this.typeid(T?T, _1)(_1, _2)
            }
            .operator T?T?i0     :vararg { this.T?T?flt() }
            .operator T?T?dword  :vararg { this.T?T?flt(_1) }
            .operator T?T?sdword :vararg { this.T?T?flt(_1) }
            .operator T?T?r32    :vararg { this.T?T?flt(_1) }
            .operator T?T?r128   :vararg { this.T?T?real4(_1) }
            .operator T?T?flt :abs=<0.0>, :abs=<0.0>, :vararg {
                mov this.X,_1
                mov this.Y,_2
                }
            .operator T?T?real4 :real4, :real4, :vararg {
                movss this.X,xmm1
                movss this.Y,xmm2
                }
            .operator T?T?pPointF :ptr PointF {
                mov qword ptr [this],[_1]
                }
            .operator T?T?pSizeF :ptr SizeF {
                mov qword ptr [this],[_1]
                }
        .operator T?i32 :vararg {
          local t
           .new t:PointF
            t.T?T(_1)
            lea rax,t
            }

    .operator + :ptr PointF {
        movss   xmm0,[_1].PointF.X
        movss   xmm1,[_1].PointF.Y
        addss   xmm0,[this].PointF.X
        addss   xmm1,[this].PointF.Y
        movss   [this].PointF.X,xmm0
        movss   [this].PointF.Y,xmm1
        }
    .operator - :ptr PointF {
        movss   xmm0,[this].PointF.X
        movss   xmm1,[this].PointF.Y
        subss   xmm0,[_1].PointF.X
        subss   xmm1,[_1].PointF.Y
        movss   [this].PointF.X,xmm0
        movss   [this].PointF.Y,xmm1
        }
    .operator Equals :ptr PointF {
        mov   rax,[this]
        sub   rax,[_1]
        mov   eax,0
        setz  al
        }
    .ends

;;--------------------------------------------------------------------------
;; Represents a location in a 2D coordinate system (integer coordinates)
;;--------------------------------------------------------------------------

.template Point

    X   int_t ?
    Y   int_t ?

    .operator Point :vararg {
        ifidn typeid(?, this),<?Point>
            this.T?T(_1)
        else
            [rcx].Point.typeid(T, this)(_1)
        endif
        }
        .operator T?T :abs, :vararg {
            this.typeid(T?T, _1)(_1, _2)
            }
            .operator T?T?i0     :vararg { this.T?T?i32() }
            .operator T?T?r32    :vararg { this.T?T?i32(_1) }
            .operator T?T?dword  :vararg { this.T?T?i32(_1) }
            .operator T?T?sdword :vararg { this.T?T?i32(_1) }
            .operator T?T?i32 :abs=<0>, :abs=<0>, :vararg {
                mov this.X,_1
                mov this.Y,_2
                }
            .operator T?T?pPoint :ptr Point {
                mov qword ptr [this],[_1]
                }
            .operator T?T?pSize :ptr Size {
                mov qword ptr [this],[_1]
                }
        .operator T?i32 :vararg {
          local t
           .new t:Point
            t.T?T(_1)
            lea rax,t
            }

    .operator + :ptr Point {
        add [this].Point.X,[_1].Point.X
        add [this].Point.Y,[_1].Point.Y
        }
    .operator - :ptr Point {
        sub [this].Point.X,[_1].Point.X
        sub [this].Point.Y,[_1].Point.Y
        }
    .operator Equals :ptr Point {
        mov   rax,[this]
        sub   rax,[_1]
        mov   eax,0
        setz  al
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

    .operator RectF :vararg {
        ifidn typeid(?, this),<?RectF>
            this.T?T(_1)
        else
            [rcx].RectF.typeid(T, this)(_1)
        endif
        }
        .operator T?i32 :vararg {
          local t
           .new t:RectF
            t.T?T(_1)
            lea rax,t
            }
        .operator T?T :abs, :vararg {
            this.typeid(T?T, _1)(_1, _2)
            }
            .operator T?T?flt :abs=<0.0>, :abs=<0.0>, :abs=<0.0>, :abs=<0.0>, :vararg {
                mov this.X,_1
                mov this.Y,_2
                mov this.Width,_3
                mov this.Height,_4
                }
            .operator T?T?i0     :vararg { this.T?T?flt() }
            .operator T?T?dword  :vararg { this.T?T?flt(_1) }
            .operator T?T?sdword :vararg { this.T?T?flt(_1) }
            .operator T?T?real4  :vararg { this.T?T?flt(_1) }
            .operator T?T?r128 :REAL, :REAL, :REAL, :REAL, :vararg {
                movss this.X,xmm1
                movss this.Y,xmm2
                movss this.Width,xmm3
                mov   this.Height,[rsp+32]
                }
            .operator T?T?pPointF :ptr PointF, :ptr SizeF {
                mov qword ptr [this+0],[_1]
                mov qword ptr [this+8],[_2]
                }

    .operator Clone :ptr RectF {
      local t
       .new t:RectF
        mov qword ptr [t+0],[_1+0]
        mov qword ptr [t+8],[_1+8]
        lea rax,t
        }

    .operator GetLocation :ptr PointF {
        mov qword ptr [_1],[this]
        }
    .operator GetSize :ptr SizeF {
        mov qword ptr [_1],[this+8]
        }
    .operator GetBounds :ptr RectF {
        mov qword ptr [_1],[this]
        mov qword ptr [_1+8],[this+8]
        }
    .operator GetLeft {
        movss xmm0,[this].RectF.X
        }
    .operator GetTop {
        movss xmm0,[this].RectF.Y
        }
    .operator GetRight {
        movss xmm0,[this].RectF.X
        addss xmm0,[this].RectF.Width
        }
    .operator GetBottom {
        movss xmm0,[this].RectF.Y
        addss xmm0,[this].RectF.Height
        }
    .operator IsEmptyArea {
        xor    eax,eax
        movss  xmm0,[this].RectF.Width
        comiss xmm0,REAL_EPSILON
        setna  al
        .ifa
            movss  xmm0,[this].RectF.Height
            comiss xmm0,REAL_EPSILON
            setna  al
        .endif
        }
    .operator Equals :ptr RectF {
        xor    eax,eax
        mov    r10,[this]
        sub    r10,[_1]
        setnz  al
        mov    r10,[this+8]
        sub    r10,[_1+8]
        setnz  r10b
        or     al,r10b
        setz   al
        }

    .operator Contains :vararg {
        ifidn typeid(?, this),<?RectF>
            this.Contains?T(_1)
        else
            [rcx].RectF.typeid(Contains, this)(_1)
        endif
        }
        .operator Contains?T :abs, :vararg {
            this.typeid(Contains?T, _1)(_1, _2)
            }
            .operator Contains?T?real4 :abs, :abs, :vararg {
                this.Contains?pRectF?real4(_1, _2)
                }
            .operator Contains?T?pPointF :ptr PointF, :vararg {
                this.Contains?pRectF?real4([rdx].PointF.X, [rdx].PointF.Y)
                }
            .operator Contains?T?pRectF :abs, :vararg {
                this.Contains?pRectF?pRectF(_1)
                }
        .operator Contains?pRectF :abs, :abs {
            [rcx].RectF.typeid(Contains?pRectF, _1)(_1, _2)
            }
            .operator Contains?pRectF?real4 :real4, :real4 {
                xor    eax,eax
                comiss xmm1,[this].RectF.X
                .ifnb
                    comiss xmm2,[this].RectF.Y
                    .ifnb
                        movss  xmm0,[this].RectF.Width
                        addss  xmm0,[this].RectF.X
                        comiss xmm1,xmm0
                        .ifb
                            movss  xmm0,[this].RectF.Height
                            addss  xmm0,[this].RectF.Y
                            comiss xmm2,xmm0
                            setb   al
                        .endif
                    .endif
                .endif
                }
            .operator Contains?pRectF?pPointF :ptr PointF {
                [this].RectF.Contains?pRectF?real4([_1].PointF.X, [_1].PointF.Y)
                }
            .operator Contains?pRectF?pRectF :ptr RectF {
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

    .operator Inflate :vararg {
        ifidn typeid(?, this),<?RectF>
            this.Inflate?T(_1)
        else
            [rcx].RectF.typeid(Inflate, this)(_1)
        endif
        }
        .operator Inflate?T :abs, :vararg {
            this.typeid(Inflate?T, _1)(_1, _2)
            }
            .operator Inflate?T?real4 :abs, :abs, :vararg {
                this.Inflate?pRectF?real4(_1, _2)
                }
            .operator Inflate?T?pPointF :ptr PointF, :vararg {
                this.Inflate?pRectF?real4([rdx].PointF.X, [rdx].PointF.Y)
                }
        .operator Inflate?pRectF :abs, :vararg {
            [rcx].RectF.typeid(Inflate?pRectF, _1)(_1, _2)
            }
            .operator Inflate?pRectF?real4 :real4, :real4 {
                movss   xmm0,[this].RectF.X
                subss   xmm0,_1
                movss   [this].RectF.X,xmm0
                movss   xmm0,[this].RectF.Y
                subss   xmm0,_2
                movss   [this].RectF.Y,xmm0
                mulss   _1,2.0
                mulss   _2,2.0
                addss   _1,[this].RectF.Width
                addss   _2,[this].RectF.Height
                movss   [this].RectF.Width,_1
                movss   [this].RectF.Height,_2
                }
            .operator Inflate?pRectF?pPointF :ptr PointF {
                cvtsi2ss xmm1,[_1].Point.X
                cvtsi2ss xmm2,[_1].Point.Y
                [this].RectF.Inflate?pRectF?real4(xmm1, xmm2)
                }

    .operator Intersect :vararg {
        ifidn typeid(?, this),<?RectF>
            this.Intersect?T(_1)
        else
            [rcx].RectF.typeid(Intersect, this)(_1)
        endif
        }
        .operator Intersect?T :abs, :abs, :vararg {
            this.typeid(Intersect?T, _1)typeid(?, _2)(_1, _2, _3)
            }
            .operator Intersect?T?pRectF?i0 :abs, :vararg {
                lea rcx,this
                [rcx].RectF.Intersect?pRectF?pRectF?pRectF(rcx, _1)
                }
            .operator Intersect?T?pRectF?pRectF :abs, :abs, :vararg {
                lea rcx,this
                [rcx].RectF.Intersect?pRectF?pRectF?pRectF(_1, _2)
                }
        .operator Intersect?pRectF :abs, :abs {
            [rcx].RectF.typeid(Intersect?pRectF, _1)typeid(?, _2)(_1, _2)
            }
            .operator Intersect?pRectF?pRectF?i0 :abs {
                [rcx].RectF.Intersect?pRectF?pRectF?pRectF(rcx, _1)
                }
            .operator Intersect?pRectF?pRectF?pRectF :ptr RectF, :ptr RectF {
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


    .operator IntersectsWith :ptr RectF {
        xor     eax,eax
        movss   xmm0,[this].RectF.X
        movss   xmm1,xmm0
        addss   xmm0,[this].RectF.Width
        comiss  xmm1,xmm0
        .ifb
            movss  xmm2,[this].RectF.Y
            movss  xmm3,xmm2
            addss  xmm2,[this].RectF.Height
            comiss xmm3,xmm2
            .ifb
                comiss xmm0,xmm1
                .ifa
                    comiss xmm2,xmm3
                    seta   al
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
        xor     [this].RectF.IsEmptyArea(),1
        }

    .operator _Offset :vararg {
        ifidn typeid(?, this),<?RectF>
            this._Offset?T(_1)
        else
            [rcx].RectF.typeid(_Offset, this)(_1)
        endif
        }
        .operator _Offset?T :abs, :vararg {
            this.typeid(_Offset?T, _1)(_1, _2)
            }
            .operator _Offset?T?pPointF :ptr PointF, :vararg {
                this._Offset?T?real4([rdx].RectF.X, [rdx].RectF.Y)
                }
            .operator _Offset?T?flt :abs, :abs, :vararg {
                this._Offset?T?real4(_1, _2)
                }
            .operator _Offset?T?real4 :real4, :real4, :vararg {
                addss xmm1,this.X
                addss xmm2,this.Y
                movss this.X,xmm1
                movss this.Y,xmm2
                }
        .operator _Offset?pRectF :abs, :abs {
            [this].RectF.typeid(_Offset?pRectF, _1)(_1, _2)
            }
            .operator _Offset?pRectF?pPointF :ptr PointF {
                [this].RectF._Offset?pRectF?real4([_1].RectF.X, [_1].RectF.Y)
                }
            .operator _Offset?pRectF?flt :abs, :abs {
                [this].RectF._Offset?pRectF?real4(_1, _2)
                }
            .operator _Offset?pRectF?real4 :real4, :real4 {
                addss _1,[this].RectF.X
                addss _2,[this].RectF.Y
                movss [this].RectF.X,_1
                movss [this].RectF.Y,_2
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

    .operator Rect :vararg {
        ifidn typeid(?, this),<?Rect>
            this.T?T(_1)
        else
            [rcx].Rect.typeid(T, this)(_1)
        endif
        }
        .operator T?T :abs, :vararg {
            this.typeid(T?T, _1)(_1, _2)
            }
        .operator T?i32 :vararg {
          local t
           .new t:Rect
            t.T?T(_1)
            lea rax,t
            }
        .operator T?T?i32 :abs=<0>, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
            mov this.X,_1
            mov this.Y,_2
            mov this.Width,_3
            mov this.Height,_4
            }
        .operator T?T?i0     :vararg { this.T?T?i32() }
        .operator T?T?r32    :vararg { this.T?T?i32(_1) }
        .operator T?T?dword  :vararg { this.T?T?i32(_1) }
        .operator T?T?sdword :vararg { this.T?T?i32(_1) }
        .operator T?T?pPoint :ptr Point, :ptr Size {
            mov qword ptr [this+0],[_1]
            mov qword ptr [this+8],[_2]
            }

    .operator Clone :ptr Rect {
      local t
       .new t:Rect
        mov qword ptr [t+0],[_1+0]
        mov qword ptr [t+8],[_1+8]
        lea rax,t
        }
    .operator GetLocation :ptr Point {
        mov qword ptr [_1],[this+0]
        }
    .operator GetSize :ptr Size {
        mov qword ptr [_1],[this+8]
        }
    .operator GetBounds :ptr Rect {
        mov qword ptr [_1+0],[this+0]
        mov qword ptr [_1+8],[this+8]
        }
    .operator GetLeft {
        mov eax,[this].Rect.X
        }
    .operator GetTop {
        mov eax,[this].Rect.Y
        }
    .operator GetRight {
        mov eax,[this].Rect.X
        add eax,[this].Rect.Width
        }
    .operator GetBottom {
        mov eax,[this].Rect.Y
        add eax,[this].Rect.Height
        }
    .operator IsEmptyArea {
        xor eax,eax
        .ifs [this].Rect.Width <= eax || [this].Rect.Height <= eax
            inc eax
        .endif
        }
    .operator Equals :ptr Rect {
        xor    eax,eax
        mov    r10,[this]
        sub    r10,[_1]
        setnz  al
        mov    r10,[this+8]
        sub    r10,[_1+8]
        setnz  r10b
        or     al,r10b
        setz   al
        }

    .operator Contains :vararg {
        ifidn typeid(?, this),<?Rect>
            this.Contains?T(_1)
        else
            [rcx].Rect.typeid(Contains, this)(_1)
        endif
        }
        .operator Contains?T :abs, :vararg {
            this.typeid(Contains?T, _1)(_1, _2)
            }
        .operator Contains?pRect :abs, :vararg {
            [rcx].Rect.typeid(Contains?pRect, _1)(_1, _2)
            }

        .operator Contains?T?sdword :int_t, :int_t, :vararg {
            xor eax,eax
            .ifs ( edx >= this.X && r8d >= this.Y )
                sub edx,this.Width
                sub r8d,this.Height
                .ifs ( edx < this.X && r8d < this.Y )
                    inc eax
                .endif
            .endif
            }
        .operator Contains?T?pPoint :ptr Point, :vararg {
            this.Contains?T?sdword([rdx].Point.X, [rdx].Point.Y)
            }
        .operator Contains?T?pRect :ptr Rect, :vararg {
            mov r8d,[rdx].Rect.X
            add r8d,[rdx].Rect.Width
            mov r9d,this.X
            add r9d,this.Width
            .ifs ( this.X <= [rdx].Rect.X && this.Y <= [rdx].Rect.Y && r8d <= r9d )
                xor eax,eax
                mov r9d,[rdx].Rect.Y
                add r9d,[rdx].Rect.Height
                mov r8d,this.Y
                add r8d,this.Height
                .ifs ( r9d <= r8d )
                    mov eax,1
                .endif
            .else
                xor eax,eax
            .endif
            }
        .operator Contains?pRect?sdword :int_t, :int_t {
            xor eax,eax
            .ifs ( _1 >= [this].Rect.X && _2 >= [this].Rect.Y )
                sub _1,[this].Rect.Width
                sub _2,[this].Rect.Height
                .ifs ( _1 < [this].Rect.X && _2 < [this].Rect.Y )
                    inc eax
                .endif
            .endif
            }
        .operator Contains?pRect?pPoint :ptr Point {
            [this].Rect.Contains?pRect?sdword([_1].Point.X, [_1].Point.Y)
            }
        .operator Contains?pRect?pRect :ptr Rect {
            mov r8d,[_1].Rect.X
            add r8d,[_1].Rect.Width
            mov r9d,[this].Rect.X
            add r9d,[this].Rect.Width
            .ifs ( [this].Rect.X <= [_1].Rect.X && [this].Rect.Y <= [_1].Rect.Y && r8d <= r9d )
                xor eax,eax
                mov r9d,[_1].Rect.Y
                add r9d,[_1].Rect.Height
                mov r8d,[this].Rect.Y
                add r8d,[this].Rect.Height
                .ifs ( r9d <= r8d )
                    mov eax,1
                .endif
            .else
                xor eax,eax
            .endif
            }

    .operator Inflate :vararg {
        ifidn typeid(?, this),<?Rect>
            this.Inflate?T(_1)
        else
            [rcx].Rect.typeid(Inflate, this)(_1)
        endif
        }
        .operator Inflate?T :abs, :vararg {
            this.typeid(Inflate?T, _1)(_1, _2)
            }
        .operator Inflate?pRect :abs, :vararg {
            [rcx].Rect.typeid(Inflate?pRect, _1)(_1, _2)
            }
        .operator Inflate?T?sdword :int_t, :int_t, :vararg {
            sub this.X,edx
            sub this.Y,r8d
            add edx,edx
            add r8d,r8d
            add this.Width,edx
            add this.Height,r8d
            }
        .operator Inflate?pRect?sdword :int_t, :int_t {
            sub [this].Rect.X,edx
            sub [this].Rect.Y,r8d
            add edx,edx
            add r8d,r8d
            add [this].Rect.Width,edx
            add [this].Rect.Height,r8d
            }
        .operator Inflate?T?pPoint :ptr Point, :vararg {
            this.Inflate?T?sdword([rdx].Point.X, [rdx].Point.Y)
            }
        .operator Inflate?pRect?pPoint :ptr Point {
            [this].Rect.Inflate?pRect?sdword([_1].Point.X, [_1].Point.Y)
            }

    .operator Intersect :vararg {
        ifidn typeid(?, this),<?Rect>
            this.Intersect?T(_1)
        else
            [rcx].Rect.typeid(Intersect, this)(_1)
        endif
        }
        .operator Intersect?T :abs, :abs, :vararg {
            this.typeid(Intersect?T, _1)typeid(?, _2)(_1, _2, _3)
            }
        .operator Intersect?pRect :abs, :abs {
            [rcx].Rect.typeid(Intersect?pRect, _1)typeid(?, _2)(_1, _2)
            }
        .operator Intersect?T?pRect?i0 :abs, :vararg {
            lea rcx,this
            [rcx].Rect.Intersect?pRect?pRect?pRect(rcx, _1)
            }
        .operator Intersect?T?pRect?pRect :abs, :abs, :vararg {
            lea rcx,this
            [rcx].Rect.Intersect?pRect?pRect?pRect(_1, _2)
            }
        .operator Intersect?pRect?pRect?i0 :abs {
            [rcx].Rect.Intersect?pRect?pRect?pRect(rcx, _1)
            }
        .operator Intersect?pRect?pRect?pRect :ptr Rect, :ptr Rect {
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

    .operator IntersectsWith :ptr Rect {
        xor eax,eax
        mov r8d,[_1].Rect.X
        add r8d,[_1].Rect.Width
        mov r9d,[_1].Rect.Y
        add r9d,[_1].Rect.Height
        .ifs ( [this].Rect.X < r8d && [this].Rect.Y < r9d )
            mov r9d,[this].Rect.X
            add r9d,[this].Rect.Width
            .if r9d > [_1].Rect.X
                mov r9d,[this].Rect.Y
                add r9d,[this].Rect.Height
                .if r9d > [_1].Rect.Y
                    mov eax,1
                .endif
            .endif
        .endif
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

    .operator _Offset :vararg {
        ifidn typeid(?, this),<?Rect>
            this._Offset?T(_1)
        else
            [rcx].Rect.typeid(_Offset, this)(_1)
        endif
        }
        .operator _Offset?T :abs, :vararg {
            this.typeid(_Offset?T, _1)(_1, _2)
            }
        .operator _Offset?T?pPoint :ptr Point, :vararg {
            this._Offset?T?i32([rdx].Rect.X, [rdx].Rect.Y)
            }
        .operator _Offset?T?sdword :int_t, :int_t, :vararg {
            add this.X,edx
            add this.Y,r8d
            }
        .operator _Offset?T?i32 :abs, :abs, :vararg {
            add this.X,_1
            add this.Y,_2
            }
        .operator _Offset?pRect :abs, :abs {
            [this].Rect.typeid(_Offset?pRect, _1)(_1, _2)
            }
        .operator _Offset?pRect?pPoint :ptr Point {
            [this].Rect._Offset?pRect?i32([_1].Rect.X, [_1].Rect.Y)
            }
        .operator _Offset?pRect?sdword :int_t, :int_t {
            add [this].Rect.X,_1
            add [this].Rect.Y,_2
            }
        .operator _Offset?pRect?i32 :abs, :abs {
            add [this].Rect.X,_1
            add [this].Rect.Y,_2
            }

    .ends


.template PathData

    Count   int_t ?
    Points  ptr_t ?
    Types   ptr_t ?

    .operator PathData :vararg {
        xor eax,eax
        mov this.Count,  eax
        mov this.Points, rax
        mov this.Types,  rax
        }
    .operator Release :vararg {
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


.template CharacterRange

    First   int_t ?
    Length  int_t ?

    .operator CharacterRange :vararg {
        ifidn typeid(?, this),<?CharacterRange>
            this.T?T(_1)
        else
            [rcx].CharacterRange.typeid(T, this)(_1)
        endif
        }
        .operator T?i32 :vararg {
          local t
           .new t:CharacterRange
            t.T?T(_1)
            lea rax,t
            }
        .operator T?T :abs, :vararg {
            this.typeid(T?T, _1)(_1, _2)
            }
            .operator T?T?i32 :abs, :abs=<0>, :vararg {
                mov this.First, _1
                mov this.Length,_2
                }
            .operator T?T?i0 :vararg {
                this.T?T?i32(0, 0)
                }
            .operator T?T?pCharacterRange :ptr CharacterRange, :vararg {
                mov this.First, [rdx].CharacterRange.First
                mov this.Length,[rdx].CharacterRange.Length
                }
    .ends

endif ;; NOT _GDIPLUSTYPES_HPP

