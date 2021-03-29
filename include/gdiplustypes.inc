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

    .inline SizeF :vararg {
        ifidn typeid(this),<SizeF>
            this.TT(_1)
        else
            [rcx].SizeF.typeid(T, this)(_1)
        endif
        }
        .inline TT :abs, :vararg {
            this.typeid(TT, _1)(_1, _2)
            }
            .inline TTIMM0   :vararg { this.TTIMMFLT() }
            .inline TTDWORD  :vararg { this.TTIMMFLT(_1) }
            .inline TTSDWORD :vararg { this.TTIMMFLT(_1) }
            .inline TTREG32  :vararg { this.TTIMMFLT(_1) }
            .inline TTREG128 :vararg { this.TTREAL4(_1) }
            .inline TTIMMFLT :abs=<0.0>, :abs=<0.0>, :vararg {
                mov this.Width,_1
                mov this.Height,_2
                }
            .inline TTREAL4 :real4, :real4, :vararg {
                movss this.Width,xmm1
                movss this.Height,xmm2
                }
            .inline TTPPointF :ptr PointF {
                mov qword ptr [this],[_1]
                }
            .inline TTPSizeF :ptr SizeF {
                mov qword ptr [this],[_1]
                }
        .inline TIMM32 :vararg {
          local t
           .new t:SizeF
            t.TT(_1)
            lea rax,t
            }

    .inline + :ptr SizeF {
        movss   xmm0,[_1].SizeF.Width
        movss   xmm1,[_1].SizeF.Height
        addss   xmm0,[this].SizeF.Width
        addss   xmm1,[this].SizeF.Height
        movss   [this].SizeF.Width,xmm0
        movss   [this].SizeF.Height,xmm1
        }
    .inline - :ptr SizeF {
        movss   xmm0,[this].SizeF.Width
        movss   xmm1,[this].SizeF.Height
        subss   xmm0,[_1].SizeF.Width
        subss   xmm1,[_1].SizeF.Height
        movss   [this].SizeF.Width,xmm0
        movss   [this].SizeF.Height,xmm1
        }
    .inline Equals :ptr SizeF {
        mov   rax,[this]
        sub   rax,[_1]
        mov   eax,0
        setz  al
        }
    .inline Empty {
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

    .inline Size :vararg {
        ifidn typeid(this),<Size>
            this.TT(_1)
        else
            [rcx].Size.typeid(T, this)(_1)
        endif
        }
        .inline TT :abs, :vararg {
            this.typeid(TT, _1)(_1, _2)
            }
            .inline TTIMM0   :vararg { this.TTIMM32() }
            .inline TTREG32  :vararg { this.TTIMM32(_1) }
            .inline TTDWORD  :vararg { this.TTIMM32(_1) }
            .inline TTSDWORD :vararg { this.TTIMM32(_1) }
            .inline TTIMM32  :abs=<0>, :abs=<0>, :vararg {
                mov this.Width,_1
                mov this.Height,_2
                }
            .inline TTPPoint :ptr Point {
                mov qword ptr [this],[_1]
                }
            .inline TTPSize :ptr Size {
                mov qword ptr [this],[_1]
                }
        .inline TIMM32 :vararg {
          local t
           .new t:Size
            t.TT(_1)
            lea rax,t
            }

    .inline + :ptr Size {
        add [this].Size.Width,  [_1].Size.Width
        add [this].Size.Height, [_1].Size.Height
        }
    .inline - :ptr Size {
        sub [this].Size.Width,  [_1].Size.Width
        sub [this].Size.Height, [_1].Size.Height
        }
    .inline Equals :ptr Size {
        mov   rax,[this]
        sub   rax,[_1]
        mov   eax,0
        setz  al
        }
    .inline Empty {
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

    .inline PointF :vararg {
        ifidn typeid(this),<PointF>
            this.TT(_1)
        else
            [rcx].PointF.typeid(T, this)(_1)
        endif
        }
        .inline TT :abs, :vararg {
            this.typeid(TT, _1)(_1, _2)
            }
            .inline TTIMM0   :vararg { this.TTIMMFLT() }
            .inline TTDWORD  :vararg { this.TTIMMFLT(_1) }
            .inline TTSDWORD :vararg { this.TTIMMFLT(_1) }
            .inline TTREG32  :vararg { this.TTIMMFLT(_1) }
            .inline TTREG128 :vararg { this.TTREAL4(_1) }
            .inline TTIMMFLT :abs=<0.0>, :abs=<0.0>, :vararg {
                mov this.X,_1
                mov this.Y,_2
                }
            .inline TTREAL4 :real4, :real4, :vararg {
                movss this.X,xmm1
                movss this.Y,xmm2
                }
            .inline TTPPointF :ptr PointF {
                mov qword ptr [this],[_1]
                }
            .inline TTPSizeF :ptr SizeF {
                mov qword ptr [this],[_1]
                }
        .inline TIMM32 :vararg {
          local t
           .new t:PointF
            t.TT(_1)
            lea rax,t
            }

    .inline + :ptr PointF {
        movss   xmm0,[_1].PointF.X
        movss   xmm1,[_1].PointF.Y
        addss   xmm0,[this].PointF.X
        addss   xmm1,[this].PointF.Y
        movss   [this].PointF.X,xmm0
        movss   [this].PointF.Y,xmm1
        }
    .inline - :ptr PointF {
        movss   xmm0,[this].PointF.X
        movss   xmm1,[this].PointF.Y
        subss   xmm0,[_1].PointF.X
        subss   xmm1,[_1].PointF.Y
        movss   [this].PointF.X,xmm0
        movss   [this].PointF.Y,xmm1
        }
    .inline Equals :ptr PointF {
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

    .inline Point :vararg {
        ifidn typeid(this),<Point>
            this.TT(_1)
        else
            [rcx].Point.typeid(T, this)(_1)
        endif
        }
        .inline TT :abs, :vararg {
            this.typeid(TT, _1)(_1, _2)
            }
            .inline TTIMM0   :vararg { this.TTIMM32() }
            .inline TTREG32  :vararg { this.TTIMM32(_1) }
            .inline TTDWORD  :vararg { this.TTIMM32(_1) }
            .inline TTSDWORD :vararg { this.TTIMM32(_1) }
            .inline TTIMM32 :abs=<0>, :abs=<0>, :vararg {
                mov this.X,_1
                mov this.Y,_2
                }
            .inline TTPPoint :ptr Point {
                mov qword ptr [this],[_1]
                }
            .inline TTPSize :ptr Size {
                mov qword ptr [this],[_1]
                }
        .inline TIMM32 :vararg {
          local t
           .new t:Point
            t.TT(_1)
            lea rax,t
            }

    .inline + :ptr Point {
        add [this].Point.X,[_1].Point.X
        add [this].Point.Y,[_1].Point.Y
        }
    .inline - :ptr Point {
        sub [this].Point.X,[_1].Point.X
        sub [this].Point.Y,[_1].Point.Y
        }
    .inline Equals :ptr Point {
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

    .inline RectF :vararg {
        ifidn typeid(this),<RectF>
            this.TT(_1)
        else
            [rcx].RectF.typeid(T, this)(_1)
        endif
        }
        .inline TIMM32 :vararg {
          local t
           .new t:RectF
            t.TT(_1)
            lea rax,t
            }
        .inline TT :abs, :vararg {
            this.typeid(TT, _1)(_1, _2)
            }
            .inline TTIMMFLT :abs=<0.0>, :abs=<0.0>, :abs=<0.0>, :abs=<0.0>, :vararg {
                mov this.X,_1
                mov this.Y,_2
                mov this.Width,_3
                mov this.Height,_4
                }
            .inline TTIMM0   :vararg { this.TTIMMFLT() }
            .inline TTDWORD  :vararg { this.TTIMMFLT(_1) }
            .inline TTSDWORD :vararg { this.TTIMMFLT(_1) }
            .inline TTREAL4  :vararg { this.TTIMMFLT(_1) }
            .inline TTREG128 :REAL, :REAL, :REAL, :REAL, :vararg {
                movss this.X,xmm1
                movss this.Y,xmm2
                movss this.Width,xmm3
                mov   this.Height,[rsp+32]
                }
            .inline TTPPointF :ptr PointF, :ptr SizeF {
                mov qword ptr [this+0],[_1]
                mov qword ptr [this+8],[_2]
                }

    .inline Clone :ptr RectF {
      local t
       .new t:RectF
        mov qword ptr [t+0],[_1+0]
        mov qword ptr [t+8],[_1+8]
        lea rax,t
        }

    .inline GetLocation :ptr PointF {
        mov qword ptr [_1],[this]
        }
    .inline GetSize :ptr SizeF {
        mov qword ptr [_1],[this+8]
        }
    .inline GetBounds :ptr RectF {
        mov qword ptr [_1],[this]
        mov qword ptr [_1+8],[this+8]
        }
    .inline GetLeft {
        movss xmm0,[this].RectF.X
        }
    .inline GetTop {
        movss xmm0,[this].RectF.Y
        }
    .inline GetRight {
        movss xmm0,[this].RectF.X
        addss xmm0,[this].RectF.Width
        }
    .inline GetBottom {
        movss xmm0,[this].RectF.Y
        addss xmm0,[this].RectF.Height
        }
    .inline IsEmptyArea {
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
    .inline Equals :ptr RectF {
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

    .inline Contains :vararg {
        ifidn typeid(this),<RectF>
            this.ContainsT(_1)
        else
            [rcx].RectF.typeid(Contains, this)(_1)
        endif
        }
        .inline ContainsT :abs, :vararg {
            this.typeid(ContainsT, _1)(_1, _2)
            }
            .inline ContainsTREAL4 :abs, :abs, :vararg {
                this.ContainsPRectFREAL4(_1, _2)
                }
            .inline ContainsTPPointF :ptr PointF, :vararg {
                this.ContainsPRectFREAL4([rdx].PointF.X, [rdx].PointF.Y)
                }
            .inline ContainsTPRectF :abs, :vararg {
                this.ContainsPRectFPRectF(_1)
                }
        .inline ContainsPRectF :abs, :abs {
            [rcx].RectF.typeid(ContainsPRectF, _1)(_1, _2)
            }
            .inline ContainsPRectFREAL4 :real4, :real4 {
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
            .inline ContainsPRectFPPointF :ptr PointF {
                [this].RectF.ContainsPRectFREAL4([_1].PointF.X, [_1].PointF.Y)
                }
            .inline ContainsPRectFPRectF :ptr RectF {
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

    .inline Inflate :vararg {
        ifidn typeid(this),<RectF>
            this.InflateT(_1)
        else
            [rcx].RectF.typeid(Inflate, this)(_1)
        endif
        }
        .inline InflateT :abs, :vararg {
            this.typeid(InflateT, _1)(_1, _2)
            }
            .inline InflateTREAL4 :abs, :abs, :vararg {
                this.InflatePRectFREAL4(_1, _2)
                }
            .inline InflateTPPointF :ptr PointF, :vararg {
                this.InflatePRectFREAL4([rdx].PointF.X, [rdx].PointF.Y)
                }
        .inline InflatePRectF :abs, :vararg {
            [rcx].RectF.typeid(InflatePRectF, _1)(_1, _2)
            }
            .inline InflatePRectFREAL4 :real4, :real4 {
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
            .inline InflatePRectFPPointF :ptr PointF {
                cvtsi2ss xmm1,[_1].Point.X
                cvtsi2ss xmm2,[_1].Point.Y
                [this].RectF.InflatePRectFREAL4(xmm1, xmm2)
                }

    .inline Intersect :vararg {
        ifidn typeid(this),<RectF>
            this.IntersectT(_1)
        else
            [rcx].RectF.typeid(Intersect, this)(_1)
        endif
        }
        .inline IntersectT :abs, :abs, :vararg {
            this.typeid(IntersectT, _1)typeid(_2)(_1, _2, _3)
            }
            .inline IntersectTPRectFIMM0 :abs, :vararg {
                lea rcx,this
                [rcx].RectF.IntersectPRectFPRectFPRectF(rcx, _1)
                }
            .inline IntersectTPRectFPRectF :abs, :abs, :vararg {
                lea rcx,this
                [rcx].RectF.IntersectPRectFPRectFPRectF(_1, _2)
                }
        .inline IntersectPRectF :abs, :abs {
            [rcx].RectF.typeid(IntersectPRectF, _1)typeid(_2)(_1, _2)
            }
            .inline IntersectPRectFPRectFIMM0 :abs {
                [rcx].RectF.IntersectPRectFPRectFPRectF(rcx, _1)
                }
            .inline IntersectPRectFPRectFPRectF :ptr RectF, :ptr RectF {
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


    .inline IntersectsWith :ptr RectF {
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

    .inline _Union :ptr RectF, :ptr RectF {
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

    .inline _Offset :vararg {
        ifidn typeid(this),<RectF>
            this._OffsetT(_1)
        else
            [rcx].RectF.typeid(_Offset, this)(_1)
        endif
        }
        .inline _OffsetT :abs, :vararg {
            this.typeid(_OffsetT, _1)(_1, _2)
            }
            .inline _OffsetTPPointF :ptr PointF, :vararg {
                this._OffsetTREAL4([rdx].RectF.X, [rdx].RectF.Y)
                }
            .inline _OffsetTIMMFLT :abs, :abs, :vararg {
                this._OffsetTREAL4(_1, _2)
                }
            .inline _OffsetTREAL4 :real4, :real4, :vararg {
                addss xmm1,this.X
                addss xmm2,this.Y
                movss this.X,xmm1
                movss this.Y,xmm2
                }
        .inline _OffsetPRectF :abs, :abs {
            [this].RectF.typeid(_OffsetPRectF, _1)(_1, _2)
            }
            .inline _OffsetPRectFPPointF :ptr PointF {
                [this].RectF._OffsetPRectFREAL4([_1].RectF.X, [_1].RectF.Y)
                }
            .inline _OffsetPRectFIMMFLT :abs, :abs {
                [this].RectF._OffsetPRectFREAL4(_1, _2)
                }
            .inline _OffsetPRectFREAL4 :real4, :real4 {
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

    .inline Rect :vararg {
        ifidn typeid(this),<Rect>
            this.TT(_1)
        else
            [rcx].Rect.typeid(T, this)(_1)
        endif
        }
        .inline TT :abs, :vararg {
            this.typeid(TT, _1)(_1, _2)
            }
        .inline TIMM32 :vararg {
          local t
           .new t:Rect
            t.TT(_1)
            lea rax,t
            }
        .inline TTIMM32 :abs=<0>, :abs=<0>, :abs=<0>, :abs=<0>, :vararg {
            mov this.X,_1
            mov this.Y,_2
            mov this.Width,_3
            mov this.Height,_4
            }
        .inline TTIMM0   :vararg { this.TTIMM32() }
        .inline TTREG32  :vararg { this.TTIMM32(_1) }
        .inline TTDWORD  :vararg { this.TTIMM32(_1) }
        .inline TTSDWORD :vararg { this.TTIMM32(_1) }
        .inline TTPPoint :ptr Point, :ptr Size {
            mov qword ptr [this+0],[_1]
            mov qword ptr [this+8],[_2]
            }

    .inline Clone :ptr Rect {
      local t
       .new t:Rect
        mov qword ptr [t+0],[_1+0]
        mov qword ptr [t+8],[_1+8]
        lea rax,t
        }
    .inline GetLocation :ptr Point {
        mov qword ptr [_1],[this+0]
        }
    .inline GetSize :ptr Size {
        mov qword ptr [_1],[this+8]
        }
    .inline GetBounds :ptr Rect {
        mov qword ptr [_1+0],[this+0]
        mov qword ptr [_1+8],[this+8]
        }
    .inline GetLeft {
        mov eax,[this].Rect.X
        }
    .inline GetTop {
        mov eax,[this].Rect.Y
        }
    .inline GetRight {
        mov eax,[this].Rect.X
        add eax,[this].Rect.Width
        }
    .inline GetBottom {
        mov eax,[this].Rect.Y
        add eax,[this].Rect.Height
        }
    .inline IsEmptyArea {
        xor eax,eax
        .ifs [this].Rect.Width <= eax || [this].Rect.Height <= eax
            inc eax
        .endif
        }
    .inline Equals :ptr Rect {
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

    .inline Contains :vararg {
        ifidn typeid(this),<Rect>
            this.ContainsT(_1)
        else
            [rcx].Rect.typeid(Contains, this)(_1)
        endif
        }
        .inline ContainsT :abs, :vararg {
            this.typeid(ContainsT, _1)(_1, _2)
            }
        .inline ContainsPRect :abs, :vararg {
            [rcx].Rect.typeid(ContainsPRect, _1)(_1, _2)
            }

        .inline ContainsTSDWORD :int_t, :int_t, :vararg {
            xor eax,eax
            .ifs ( edx >= this.X && r8d >= this.Y )
                sub edx,this.Width
                sub r8d,this.Height
                .ifs ( edx < this.X && r8d < this.Y )
                    inc eax
                .endif
            .endif
            }
        .inline ContainsTPPoint :ptr Point, :vararg {
            this.ContainsTSDWORD([rdx].Point.X, [rdx].Point.Y)
            }
        .inline ContainsTPRect :ptr Rect, :vararg {
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
        .inline ContainsPRectSDWORD :int_t, :int_t {
            xor eax,eax
            .ifs ( _1 >= [this].Rect.X && _2 >= [this].Rect.Y )
                sub _1,[this].Rect.Width
                sub _2,[this].Rect.Height
                .ifs ( _1 < [this].Rect.X && _2 < [this].Rect.Y )
                    inc eax
                .endif
            .endif
            }
        .inline ContainsPRectPPoint :ptr Point {
            [this].Rect.ContainsPRectSDWORD([_1].Point.X, [_1].Point.Y)
            }
        .inline ContainsPRectPRect :ptr Rect {
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

    .inline Inflate :vararg {
        ifidn typeid(this),<Rect>
            this.InflateT(_1)
        else
            [rcx].Rect.typeid(Inflate, this)(_1)
        endif
        }
        .inline InflateT :abs, :vararg {
            this.typeid(InflateT, _1)(_1, _2)
            }
        .inline InflatePRect :abs, :vararg {
            [rcx].Rect.typeid(InflatePRect, _1)(_1, _2)
            }
        .inline InflateTSDWORD :int_t, :int_t, :vararg {
            sub this.X,edx
            sub this.Y,r8d
            add edx,edx
            add r8d,r8d
            add this.Width,edx
            add this.Height,r8d
            }
        .inline InflatePRectSDWORD :int_t, :int_t {
            sub [this].Rect.X,edx
            sub [this].Rect.Y,r8d
            add edx,edx
            add r8d,r8d
            add [this].Rect.Width,edx
            add [this].Rect.Height,r8d
            }
        .inline InflateTPPoint :ptr Point, :vararg {
            this.InflateTSDWORD([rdx].Point.X, [rdx].Point.Y)
            }
        .inline InflatePRectPPoint :ptr Point {
            [this].Rect.InflatePRectSDWORD([_1].Point.X, [_1].Point.Y)
            }

    .inline Intersect :vararg {
        ifidn typeid(this),<Rect>
            this.IntersectT(_1)
        else
            [rcx].Rect.typeid(Intersect, this)(_1)
        endif
        }
        .inline IntersectT :abs, :abs, :vararg {
            this.typeid(IntersectT, _1)typeid(_2)(_1, _2, _3)
            }
        .inline IntersectPRect :abs, :abs {
            [rcx].Rect.typeid(IntersectPRect, _1)typeid(_2)(_1, _2)
            }
        .inline IntersectTPRectIMM0 :abs, :vararg {
            lea rcx,this
            [rcx].Rect.IntersectPRectPRectPRect(rcx, _1)
            }
        .inline IntersectTPRectPRect :abs, :abs, :vararg {
            lea rcx,this
            [rcx].Rect.IntersectPRectPRectPRect(_1, _2)
            }
        .inline IntersectPRectPRectIMM0 :abs {
            [rcx].Rect.IntersectPRectPRectPRect(rcx, _1)
            }
        .inline IntersectPRectPRectPRect :ptr Rect, :ptr Rect {
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

    .inline IntersectsWith :ptr Rect {
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
    .inline _Union :ptr Rect, :ptr Rect {
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

    .inline _Offset :vararg {
        ifidn typeid(this),<Rect>
            this._OffsetT(_1)
        else
            [rcx].Rect.typeid(_Offset, this)(_1)
        endif
        }
        .inline _OffsetT :abs, :vararg {
            this.typeid(_OffsetT, _1)(_1, _2)
            }
        .inline _OffsetTPPoint :ptr Point, :vararg {
            this._OffsetTIMM32([rdx].Rect.X, [rdx].Rect.Y)
            }
        .inline _OffsetTSDWORD :int_t, :int_t, :vararg {
            add this.X,edx
            add this.Y,r8d
            }
        .inline _OffsetTIMM32 :abs, :abs, :vararg {
            add this.X,_1
            add this.Y,_2
            }
        .inline _OffsetPRect :abs, :abs {
            [this].Rect.typeid(_OffsetPRect, _1)(_1, _2)
            }
        .inline _OffsetPRectPPoint :ptr Point {
            [this].Rect._OffsetPRectIMM32([_1].Rect.X, [_1].Rect.Y)
            }
        .inline _OffsetPRectSDWORD :int_t, :int_t {
            add [this].Rect.X,_1
            add [this].Rect.Y,_2
            }
        .inline _OffsetPRectIMM32 :abs, :abs {
            add [this].Rect.X,_1
            add [this].Rect.Y,_2
            }

    .ends


.template PathData

    Count   int_t ?
    Points  ptr_t ?
    Types   ptr_t ?

    .inline PathData :vararg {
        xor eax,eax
        mov this.Count,  eax
        mov this.Points, rax
        mov this.Types,  rax
        }
    .inline Release :vararg {
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

    .inline CharacterRange :vararg {
        ifidn typeid(this),<CharacterRange>
            this.TT(_1)
        else
            [rcx].CharacterRange.typeid(T, this)(_1)
        endif
        }
        .inline TIMM32 :vararg {
          local t
           .new t:CharacterRange
            t.TT(_1)
            lea rax,t
            }
        .inline TT :abs, :vararg {
            this.typeid(TT, _1)(_1, _2)
            }
            .inline TTIMM32 :abs, :abs=<0>, :vararg {
                mov this.First, _1
                mov this.Length,_2
                }
            .inline TTIMM0 :vararg {
                this.TTIMM32(0, 0)
                }
            .inline TTPCharacterRange :ptr CharacterRange, :vararg {
                mov this.First, [rdx].CharacterRange.First
                mov this.Length,[rdx].CharacterRange.Length
                }
    .ends

endif ;; NOT _GDIPLUSTYPES_HPP

