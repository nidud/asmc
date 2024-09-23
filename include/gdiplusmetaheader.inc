ifndef _GDIPLUSMETAHEADER_H
define _GDIPLUSMETAHEADER_H

ENHMETAHEADER3		STRUC
iType			dd ?
nSize			dd ?
rclBounds		RECTL <>
rclFrame		RECTL <>
dSignature		dd ?
nVersion		dd ?
nBytes			dd ?
nRecords		dd ?
nHandles		dw ?
sReserved		dw ?
nDescription		dd ?
offDescription		dd ?
nPalEntries		dd ?
szlDevice		SIZEL <>
szlMillimeters		SIZEL <>
ENHMETAHEADER3		ENDS

.pragma pack(push, 2)

PWMFRect16		STRUC
Left			dw ?
Top			dw ?
Right			dw ?
Bottom			dw ?
PWMFRect16		ENDS

WmfPlaceableFileHeader	STRUC
Key			dd ?
Hmf			dw ?
BoundingBox		PWMFRect16 <>
Inch			dw ?
Reserved		dd ?
Checksum		dw ?
WmfPlaceableFileHeader	ENDS

.pragma pack(pop)

GDIP_EMFPLUSFLAGS_DISPLAY equ 0x00000001

.template MetafileHeader

    Type		MetafileType ?
    Size		UINT ?		; Size of the metafile (in bytes)
    Version		UINT ?		; EMF+, EMF, or WMF version
    EmfPlusFlags	UINT ?
    DpiX		REAL ?
    DpiY		REAL ?
    X			SINT ?		; Bounds in device units
    Y			SINT ?
    Width		SINT ?
    Height		SINT ?
    union
	WmfHeader	METAHEADER <>
	EmfHeader	ENHMETAHEADER3 <>
    ends
    EmfPlusHeaderSize	SINT ?		; size of the EMF+ header in file
    LogicalDpiX		SINT ?		; Logical Dpi of reference Hdc
    LogicalDpiY		SINT ?		; usually valid only for EMF+

    .inline GetType {
	mov	eax,[this].MetafileHeader.Type
	}
    .inline GetMetafileSize {
	mov	eax,[this].MetafileHeader.Size
	}

    ;; If IsEmfPlus, this is the EMF+ version; else it is the WMF or EMF ver

    .inline GetVersion {
	mov	eax,[this].MetafileHeader.Version
	}

    ;; Get the EMF+ flags associated with the metafile

    .inline GetEmfPlusFlags {
	mov	eax,[this].MetafileHeader.EmfPlusFlags
	}

    .inline GetDpiX {
	movss	xmm0,[this].MetafileHeader.DpiX
	}
    .inline GetDpiY {
	movss	xmm0,[this].MetafileHeader.DpiY
	}

    .inline GetBounds :ptr Rect {
	mov	[_1].Rect.X,[this].MetafileHeader.X
	mov	[_1].Rect.Y,[this].MetafileHeader.Y
	mov	[_1].Rect.Width,[this].MetafileHeader.Width
	mov	[_1].Rect.Height,[this].MetafileHeader.Height
	}

    ;; Is it any type of WMF (standard or Placeable Metafile)?

    .inline IsWmf {
	xor eax,eax
	mov edx,[this].MetafileHeader.Type
	.if ( ( edx == MetafileTypeWmf ) || ( edx == MetafileTypeWmfPlaceable ) )
	    inc eax
	.endif
	}

    ;; Is this an Placeable Metafile?

    .inline IsWmfPlaceable {
	xor eax,eax
	mov edx,[this].MetafileHeader.Type
	.if edx == MetafileTypeWmfPlaceable
	    inc eax
	.endif
	}

    ;; Is this an EMF (not an EMF+)?

    .inline IsEmf {
	xor eax,eax
	mov edx,[this].MetafileHeader.Type
	.if edx == MetafileTypeEmf
	    inc eax
	.endif
	}

    ;; Is this an EMF or EMF+ file?

    .inline IsEmfOrEmfPlus {
	xor eax,eax
	.if [this].MetafileHeader.Type >= MetafileTypeEmf
	    inc eax
	.endif
	}

    ;; Is this an EMF+ file?

    .inline IsEmfPlus {
	xor eax,eax
	.if [this].MetafileHeader.Type >= MetafileTypeEmfPlusOnly
	    inc eax
	.endif
	}

    ;; Is this an EMF+ dual (has dual, down-level records) file?

    .inline IsEmfPlusDual {
	xor eax,eax
	.if [this].MetafileHeader.Type == MetafileTypeEmfPlusDual
	    inc eax
	.endif
	}

    ;; Is this an EMF+ only (no dual records) file?

    .inline IsEmfPlusOnly {
	xor eax,eax
	.if [this].MetafileHeader.Type == MetafileTypeEmfPlusOnly
	    inc eax
	.endif
	}

    ;; If it's an EMF+ file, was it recorded against a display Hdc?

    .inline IsDisplay {
	xor eax,eax
	.if ( [this].MetafileHeader.Type >= MetafileTypeEmfPlusOnly && [this].MetafileHeader.EmfPlusFlags & GDIP_EMFPLUSFLAGS_DISPLAY )
	    inc eax
	.endif
	}

    ;; Get the WMF header of the metafile (if it is a WMF)

    .inline GetWmfHeader {
	xor eax,eax
	mov edx,[this].MetafileHeader.Type
	.if edx == MetafileTypeWmf || edx == MetafileTypeWmfPlaceable
	    lea rax,[this].MetafileHeader.WmfHeader
	.endif
	}

    ;; Get the EMF header of the metafile (if it is an EMF)

    .inline GetEmfHeader {
	xor eax,eax
	.if [this].MetafileHeader.Type >= MetafileTypeEmf
	    lea rax,[this].MetafileHeader.EmfHeader
	.endif
	}
    .ends

endif


