; METAFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include windows.inc
include gdiplus.inc

    .code

main proc

    local hdc:HDC
    local hWmf:HMETAFILE
    local hEmf:HENHMETAFILE
    local pWCHAR:ptr WCHAR
    local pIStream:ptr IStream
    local pRect:ptr Rect
    local pRectF:ptr RectF
    local pWmfPlaceableFileHeader:ptr WmfPlaceableFileHeader
    local pMetafileHeader:ptr MetafileHeader
    local pBYTE:ptr BYTE
    local pGraphics:ptr Graphics
    local pINT:ptr sdword

    .new p:Metafile(hWmf, pWmfPlaceableFileHeader, FALSE)
    .new p:Metafile(hEmf, FALSE)
    .new p:Metafile(pWCHAR)
    .new p:Metafile(pWCHAR, pWmfPlaceableFileHeader)
    .new p:Metafile(pIStream)
    .new p:Metafile(hdc, 0, pWCHAR)
    .new p:Metafile(hdc, pRectF, 0, 0, pWCHAR)
    .new p:Metafile(hdc, pRect, 0, 0, pWCHAR)
    .new p:Metafile(pWCHAR, hdc, 0, pWCHAR)
    .new p:Metafile(pWCHAR, hdc, pRectF, 0, 0, pWCHAR)
    .new p:Metafile(pWCHAR, hdc, pRect, 0, 0, pWCHAR)
    .new p:Metafile(pIStream, hdc, 0, pWCHAR)
    .new p:Metafile(pIStream, hdc, pRectF, 0, 0, pWCHAR)
    .new p:Metafile(pIStream, hdc, pRect, 0, 0, pWCHAR)

    p.Release()
    p.GetMetafileHeader(hWmf, pWmfPlaceableFileHeader, pMetafileHeader)
    p.GetMetafileHeader(hEmf, pMetafileHeader)
    p.GetMetafileHeader(pWCHAR, pMetafileHeader)
    p.GetMetafileHeader(pIStream, pMetafileHeader)
    p.GetMetafileHeader(pMetafileHeader)
    p.GetHENHMETAFILE()
    p.PlayRecord(0, 0, 0, pBYTE)
    p.SetDownLevelRasterizationLimit(0)
    p.GetDownLevelRasterizationLimit()
    p.EmfToWmfBits(hEmf, 0, pBYTE, 0, 0)
    p.ConvertToEmfPlus(pGraphics, pINT, 0, pWCHAR)
    p.ConvertToEmfPlus(pGraphics, pWCHAR, pINT, 0, pWCHAR)
    p.ConvertToEmfPlus(pGraphics, pIStream, pINT, 0, pWCHAR)
    ret

main endp

    end
