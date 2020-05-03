ifndef _GDIPLUSREGION_H
_GDIPLUSREGION_H equ <>
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;.pragma list(push, 1)

CreateRegion macro

    .new region:ptr Region

    .if GdipAlloc(Region)

        mov region,rax
        GdipCreateRegion(&[rax].Region.nativeRegion)
        region.SetStatus(eax)
        mov rax,rcx
    .endif
    retm <rax>
    endm

CreateRegionRect proto :ptr RectF {

    .new region:ptr Region

    mov region,this
    .if GdipAlloc(Region)

        mov this,region
        mov region,rax
        GdipCreateRegionRect(this, &[rax].Region.nativeRegion)
        region.SetStatus(eax)
        mov rax,this
    .endif
    retm <rax>
    }

CreateRegionRectI proto :ptr Rect {

    .new region:ptr Region

    mov region,this
    .if GdipAlloc(Region)

        mov this,region
        mov region,rax
        GdipCreateRegionRectI(this, &[rax].Region.nativeRegion)
        region.SetStatus(eax)
        mov rax,this
    .endif
    retm <rax>
    }

CreateRegionPath proto :ptr GraphicsPath {

    .new region:ptr Region

    mov region,this
    .if GdipAlloc(Region)

        mov this,region
        mov region,rax
        GdipCreateRegionPath([this].GraphicsPath.nativePath, &[rax].Region.nativeRegion)
        region.SetStatus(eax)
        mov rax,this
    .endif
    retm <rax>
    }

CreateRegionRgnData proto :ptr byte, :int_t {

    .new region:ptr Region
    .new size:int_t

    mov region,this
    mov size,_1

    .if GdipAlloc(Region)

        mov this,region
        mov region,rax
        GdipCreateRegionRgnData(this, size, &[rax].Region.nativeRegion)
        region.SetStatus(eax)
        mov rax,this
    .endif
    retm <rax>
    }

CreateRegionHrgn proto :HRGN {

    .new region:ptr Region

    mov region,this
    .if GdipAlloc(Region)

        mov this,region
        mov [rax].Region.nativeRegion,NULL
        mov region,rax
        GdipCreateRegionHrgn(this, &[rax].Region.nativeRegion)
        region.SetStatus(eax)
        mov rax,this
    .endif
    retm <rax>
    }

Region_Region macro this
    exitm<CreateRegion()>
    endm
Region_Region1 macro this, _1
    exitm<CreateRegionRect(_1)>
    endm
Region_Region2 macro this, _1
    exitm<CreateRegionRectI(_1)>
    endm
Region_Region3 macro this, _1
    exitm<CreateRegionPath(_1)>
    endm
Region_Region4 macro this, _1, _2
    mov this,_1
    exitm<CreateRegionRgnData(this, _2)>
    endm
Region_Region5 macro this, _1
    exitm<CreateRegionHrgn(_1)>
    endm

Region_FromHRGN macro this, _1

    .new region:ptr Region

    mov region,NULL
    mov this,_1

    .ifd GdipCreateRegionHrgn(this, &region) == Ok

        .if GdipAlloc(Region) == NULL

            GdipDeleteRegion(region)
            xor eax,eax

        .else
            mov this,region
            mov [rax].Region.nativeRegion,this
            mov [rax].Region.lastResult,Ok
        .endif
    .endif
    retm <rax>
    endm

Region_Release macro this

    .new region:ptr Region

    mov region,this
    GdipDeleteRegion([this].Region.nativeRegion)
    GdipFree(region)
    exitm<>
    endm

;inline Status
Region_SetStatus macro this, _1
    mov eax,_1
    .if eax != Ok
        mov [this].Region.lastResult,eax
    .endif
    retm <eax>
    endm

;inline Region*
Region_Clone macro this

    .new clone:ptr Region
    .new region:ptr Region

    mov region,this
    mov clone,NULL

    GdipCloneRegion([this].Region.nativeRegion, &clone)
    region.SetStatus(eax)
    .if GdipAlloc(Region) == NULL
        GdipDeleteRegion(clone)
        xor eax,eax
    .else
        mov rdx,clone
        mov [rax].Region.nativeRegion,rdx
        mov this,region
        mov edx,[this].Region.lastResult
        mov [rax].Region.lastResult,edx
    .endif
    retm<rax>
    endm

;inline Status
Region_MakeInfinite macro this

    .new region:ptr Region

    mov region,this
    GdipSetInfinite([this].Region.nativeRegion)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_MakeEmpty macro this

    .new region:ptr Region

    mov region,this
    GdipSetEmpty([this].Region.nativeRegion)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Intersect1 macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRect([this].Region.nativeRegion, _1, CombineModeIntersect)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Intersect2 macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRectI([this].Region.nativeRegion, _1, CombineModeIntersect)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Intersect3 macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionPath([this].Region.nativeRegion, [_1].GraphicsPath.nativePath, CombineModeIntersect)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Intersect4 macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRegion([this].Region.nativeRegion, [_1].Region.nativeRegion, CombineModeIntersect)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Union macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRect([this].Region.nativeRegion, _1, CombineModeUnion)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Union macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRectI([this].Region.nativeRegion, _1, CombineModeUnion)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Union macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionPath([this].Region.nativeRegion, [_1].GraphicsPath.nativePath, CombineModeUnion)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Union macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRegion([this].Region.nativeRegion, region->nativeRegion, CombineModeUnion)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Xor macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRect([this].Region.nativeRegion, _1, CombineModeXor)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Xor macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRectI([this].Region.nativeRegion, _1, CombineModeXor)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Xor macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionPath([this].Region.nativeRegion, [_1].GraphicsPath.nativePath, CombineModeXor)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Xor macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRegion([this].Region.nativeRegion, region->nativeRegion, CombineModeXor)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Exclude macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRect([this].Region.nativeRegion, _1, CombineModeExclude)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Exclude macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRectI([this].Region.nativeRegion, _1, CombineModeExclude)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Exclude macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionPath([this].Region.nativeRegion, [_1].GraphicsPath.nativePath, CombineModeExclude)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Exclude macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRegion([this].Region.nativeRegion, region->nativeRegion, CombineModeExclude)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Complement macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRect([this].Region.nativeRegion, _1, CombineModeComplement)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Complement macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRectI([this].Region.nativeRegion, _1, CombineModeComplement)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Complement macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionPath([this].Region.nativeRegion, [_1].GraphicsPath.nativePath, CombineModeComplement)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Complement macro this, _1

    .new region:ptr Region

    mov region,this
    GdipCombineRegionRegion([this].Region.nativeRegion, [_1].Region.nativeRegion, CombineModeComplement)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Translate2 macro this, _1, _2

    .new region:ptr Region

    mov region,this
    GdipTranslateRegion([this].Region.nativeRegion, _1, _2)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Translate1 macro this, _1, _2

    .new region:ptr Region

    mov region,this
    GdipTranslateRegionI([this].Region.nativeRegion, _1, _2)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_Transform macro this, _1

    .new region:ptr Region

    mov region,this
    GdipTransformRegion([this].Region.nativeRegion, [_1].Matrix.nativeMatrix)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_GetBounds2 macro this, _1, _2

    .new region:ptr Region

    mov region,this
    GdipGetRegionBounds([this].Region.nativeRegion, [_1].Graphics.nativeGraphics, rect)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_GetBounds1 macro this, _1, _2

    .new region:ptr Region

    mov region,this
    GdipGetRegionBoundsI([this].Region.nativeRegion, [_1].Graphics.nativeGraphics, rect)
    exitm<region.SetStatus(eax)>
    endm

;inline HRGN
Region_GetHRGN macro this, _1

    .new region:ptr Region
    .new hrgn:HRGN

    mov region,this

    GdipGetRegionHRgn([this].Region.nativeRegion, [_1].Graphics.nativeGraphics, &hrgn)
    region.SetStatus(eax)

    mov rax,hrgn
    retm<rax>
    endm

;inline BOOL
Region_IsEmpty macro this, _1

    .new region:ptr Region
    .new booln:BOOL

    mov region,this
    mov booln,FALSE

    GdipIsEmptyRegion([this].Region.nativeRegion, [_1].Graphics.nativeGraphics, &booln)
    region.SetStatus(eax)
    mov eax,booln
    retm <eax>
    endm

;inline BOOL
Region_IsInfinite macro this, _1

    .new region:ptr Region
    .new booln:BOOL

    mov region,this
    mov booln,FALSE

    GdipIsInfiniteRegion([this].Region.nativeRegion, [_1].Graphics.nativeGraphics, &booln)
    region.SetStatus(eax)
    mov eax,booln
    retm <eax>
    endm

;inline BOOL
Region_Equals macro this, _1, _2

    .new region:ptr Region
    .new booln:BOOL

    mov region,this
    mov booln,FALSE

    GdipIsEqualRegion([this].Region.nativeRegion, [_1].Region.nativeRegion, [_2].Graphics.nativeGraphics, &booln)
    region.SetStatus(eax)
    mov eax,booln
    retm <eax>
    endm

;; Get the size of the buffer needed for the GetData method
;inline UINT
Region_GetDataSize macro this

    .new region:ptr Region
    .new bufferSize:UINT

    mov region,this
    mov bufferSize,0

    GdipGetRegionDataSize([this].Region.nativeRegion, &bufferSize)
    region.SetStatus(eax)

    mov eax,bufferSize;
    retm <eax>
    endm

;; buffer     - where to put the data
;; bufferSize - how big the buffer is (should be at least as big as GetDataSize())
;; sizeFilled - if not NULL, this is an OUT param that says how many bytes
;;              of data were written to the buffer.
;inline Status
Region_GetData macro this, _1, _2, _3

    .new region:ptr Region

    mov region,this
    GdipGetRegionData([this].Region.nativeRegion, _1, _2, _3)
    exitm<region.SetStatus(eax)>
    endm

;;
;; Hit testing operations
;;
;inline BOOL
Region_IsVisible macro this, _1, _2

    .new region:ptr Region
    .new booln:BOOL

    mov region,this
    mov booln,FALSE
    .if _2
        mov _2,[_2].Graphics.nativeGraphics
    .endif
    GdipIsVisibleRegionPoint([this].Region.nativeRegion, [_1].Point.X, [_1].Point.Y, _2, &booln)
    region.SetStatus(eax)
    mov eax,booln
    retm <eax>
    endm

;inline BOOL
Region_IsVisible macro this, _1, _2

    .new region:ptr Region
    .new booln:BOOL

    mov region,this
    mov booln,FALSE
    .if _2
        mov _2,[_2].Graphics.nativeGraphics
    .endif
    GdipIsVisibleRegionRect([this].Region.nativeRegion, [_1].Rect.X, [_1].Rect.Y, \
            [_1].Rect.Width, [_1].Rect.Height, _2, &booln)
    region.SetStatus(eax)
    mov eax,booln
    retm <eax>
    endm

;inline BOOL
Region_IsVisible macro this, _1, _2

    .new region:ptr Region
    .new booln:BOOL

    mov region,this
    mov booln,FALSE

    GdipIsVisibleRegionPointI([this].Region.nativeRegion, point.X,point.Y,
                                                   (g == NULL)
                                                    ? NULL : g->nativeGraphics,
                                                   &booln)
    region.SetStatus(eax)
    mov eax,booln
    retm <eax>
    endm

;inline BOOL
Region_IsVisible macro this, _1, _2

    .new region:ptr Region
    .new booln:BOOL

    mov region,this
    mov booln,FALSE

    GdipIsVisibleRegionRectI([this].Region.nativeRegion,
                                                  rect.X,
                                                  rect.Y,
                                                  rect.Width,
                                                  rect.Height,
                                                  (g == NULL)
                                                    ? NULL : g->nativeGraphics,
                                                  &booln)
    region.SetStatus(eax)
    mov eax,booln
    retm <eax>
    endm

;inline UINT
Region_GetRegionScansCount macro this, _1

    .new region:ptr Region
    .new count:UINT

    mov region,this
    mov count,0
    GdipGetRegionScansCount([this].Region.nativeRegion, &count, [_1].Matrix.nativeMatrix)
    region.SetStatus(eax)
    mov eax,count
    retm <eax>
    endm

;; If rects is NULL, return the count of rects in the region.
;; Otherwise, assume rects is big enough to hold all the region rects
;; and fill them in and return the number of rects filled in.
;; The rects are returned in the units specified by the matrix
;; (which is typically a world-to-device transform).
;; Note that the number of rects returned can vary, depending on the
;; matrix that is used.

;inline Status
Region_GetRegionScans macro this, _1, _2, _3

    .new region:ptr Region

    mov region,this
    mov rax,_3
    GdipGetRegionScans([this].Region.nativeRegion, _2, rax, [_1].Matrix.nativeMatrix)
    exitm<region.SetStatus(eax)>
    endm

;inline Status
Region_GetRegionScans macro this, _1, _2, _3

    .new region:ptr Region

    mov region,this
    GdipGetRegionScansI([this].Region.nativeRegion, _2, _3, [_1].Matrix.nativeMatrix)
    exitm<region.SetStatus(eax)>
    endm

Region_Region10 macro this, _1

    .new region:ptr Region

    mov region,this
    SetNativeRegion([this].Region.nativeRegion)
    exitm<region.SetStatus(eax)>
    endm

;inline VOID
Region_SetNativeRegion macro this, _1
    mov     [this].Region.nativeRegion,_1
    exitm   <>
    endm

;inline Status
Region_GetLastStatus macro this
    mov     eax,[this].Region.lastResult
    mov     [this].Region.lastResult,Ok
    retm    <eax>
    endm


;.pragma list(pop)

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif ;; NOT _GDIPLUSREGION_H
