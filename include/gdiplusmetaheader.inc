ifndef _GDIPLUSMETAHEADER_H
_GDIPLUSMETAHEADER_H equ <>

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

    .operator GetType {
	mov	eax,[this].MetafileHeader.Type
	retm	<eax>
	}
    .operator GetMetafileSize {
	mov	eax,[this].MetafileHeader.Size
	retm	<eax>
	}

    ;; If IsEmfPlus, this is the EMF+ version; else it is the WMF or EMF ver

    .operator GetVersion {
	mov	eax,[this].MetafileHeader.Version
	retm	<eax>
	}

    ;; Get the EMF+ flags associated with the metafile

    .operator GetEmfPlusFlags {
	mov	eax,[this].MetafileHeader.EmfPlusFlags
	retm	<eax>
	}

    .operator GetDpiX {
	movss	xmm0,[this].MetafileHeader.DpiX
	retm	<xmm0>
	}
    .operator GetDpiY {
	movss	xmm0,[this].MetafileHeader.DpiY
	retm	<xmm0>
	}

    .operator GetBounds :ptr Rect {
	mov	[_1].Rect.X,[this].MetafileHeader.X
	mov	[_1].Rect.Y,[this].MetafileHeader.Y
	mov	[_1].Rect.Width,[this].MetafileHeader.Width
	mov	[_1].Rect.Height,[this].MetafileHeader.Height
	retm	<this>
	}

    ;; Is it any type of WMF (standard or Placeable Metafile)?

    .operator IsWmf {
	xor eax,eax
	mov edx,[this].MetafileHeader.Type
	.if ( ( edx == MetafileTypeWmf ) || ( edx == MetafileTypeWmfPlaceable ) )
	    inc eax
	.endif
	retm <eax>
	}

    ;; Is this an Placeable Metafile?

    .operator IsWmfPlaceable {
	xor eax,eax
	mov edx,[this].MetafileHeader.Type
	.if edx == MetafileTypeWmfPlaceable
	    inc eax
	.endif
	retm <eax>
	}

    ;; Is this an EMF (not an EMF+)?

    .operator IsEmf {
	xor eax,eax
	mov edx,[this].MetafileHeader.Type
	.if edx == MetafileTypeEmf
	    inc eax
	.endif
	retm <eax>
	}

    ;; Is this an EMF or EMF+ file?

    .operator IsEmfOrEmfPlus {
	xor eax,eax
	.if [this].MetafileHeader.Type >= MetafileTypeEmf
	    inc eax
	.endif
	retm <eax>
	}

    ;; Is this an EMF+ file?

    .operator IsEmfPlus {
	xor eax,eax
	.if [this].MetafileHeader.Type >= MetafileTypeEmfPlusOnly
	    inc eax
	.endif
	retm <eax>
	}

    ;; Is this an EMF+ dual (has dual, down-level records) file?

    .operator IsEmfPlusDual {
	xor eax,eax
	.if [this].MetafileHeader.Type == MetafileTypeEmfPlusDual
	    inc eax
	.endif
	retm <eax>
	}

    ;; Is this an EMF+ only (no dual records) file?

    .operator IsEmfPlusOnly {
	xor eax,eax
	.if [this].MetafileHeader.Type == MetafileTypeEmfPlusOnly
	    inc eax
	.endif
	retm <eax>
	}

    ;; If it's an EMF+ file, was it recorded against a display Hdc?

    .operator IsDisplay {
	xor eax,eax
	.if [this].MetafileHeader.Type >= MetafileTypeEmfPlusOnly && \
	    [this].MetafileHeader.EmfPlusFlags & GDIP_EMFPLUSFLAGS_DISPLAY
	    inc eax
	.endif
	retm <eax>
	}

    ;; Get the WMF header of the metafile (if it is a WMF)

    .operator GetWmfHeader {
	xor eax,eax
	mov edx,[this].MetafileHeader.Type
	.if edx == MetafileTypeWmf || edx == MetafileTypeWmfPlaceable
	    lea rax,[this].MetafileHeader.WmfHeader
	.endif
	retm <rax>
	}

    ;; Get the EMF header of the metafile (if it is an EMF)

    .operator GetEmfHeader {
	xor eax,eax
	.if [this].MetafileHeader.Type >= MetafileTypeEmf
	    lea rax,[this].MetafileHeader.EmfHeader
	.endif
	retm <eax>
	}
    .ends

endif


