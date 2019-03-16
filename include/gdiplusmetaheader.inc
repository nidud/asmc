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

endif


