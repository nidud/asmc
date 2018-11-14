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

;include pshpack2.inc	;; set structure packing to 2

PWMFRect16		STRUC 2
Left			dw ?
Top			dw ?
Right			dw ?
Bottom			dw ?
PWMFRect16		ENDS

WmfPlaceableFileHeader	STRUC 2
Key			dd ?
Hmf			dw ?
BoundingBox		PWMFRect16 <>
Inch			dw ?
Reserved		dd ?
Checksum		dw ?
WmfPlaceableFileHeader	ENDS

;include poppack.inc

GDIP_EMFPLUSFLAGS_DISPLAY equ 0x00000001

endif


