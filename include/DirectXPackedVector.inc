ifndef __DIRECTXPACKEDVECTOR_INC
define __DIRECTXPACKEDVECTOR_INC
include DirectXMath.inc
.pragma list(push, 0)

XMCOLOR union
struct
 b  uint8_t ? ; Blue:    0/255 to 255/255
 g  uint8_t ? ; Green:   0/255 to 255/255
 r  uint8_t ? ; Red:     0/255 to 255/255
 a  uint8_t ? ; Alpha:   0/255 to 255/255
ends
_c  uint32_t ?
XMCOLOR ends

HALF typedef REAL2

XMHALF2 union
struct
 x  HALF ?
 y  HALF ?
ends
v   uint32_t ?
XMHALF2 ends

XMSHORTN2 union
struct
 x  int16_t ?
 y  int16_t ?
ends
v   uint32_t ?
XMSHORTN2 ends

XMSHORT2 union
struct
 x  int16_t ?
 y  int16_t ?
ends
v   uint32_t ?
XMSHORT2 ends

XMUSHORTN2 union
struct
 x  uint16_t ?
 y  uint16_t ?
ends
v   uint32_t ?
XMUSHORTN2 ends

XMUSHORT2 union
struct
 x  uint16_t ?
 y  uint16_t ?
ends
v   uint32_t ?
XMUSHORT2 ends

XMBYTEN2 union
struct
 x  int8_t ?
 y  int8_t ?
ends
v   uint16_t ?
XMBYTEN2 ends

XMBYTE2 union
struct
 x  int8_t ?
 y  int8_t ?
ends
v   uint16_t ?
XMBYTE2 ends

XMUBYTEN2 union
struct
 x  uint8_t ?
 y  uint8_t ?
ends
v   uint16_t ?
XMUBYTEN2 ends

XMUBYTE2 union
struct
 x  uint8_t ?
 y  uint8_t ?
ends
v   uint16_t ?
XMUBYTE2 ends

XMU565 union
struct
 XMU565_X equ 5 ; 0 to 31
 XMU565_Y equ 6 ; 0 to 63
 XMU565_Z equ 5 ; 0 to 31
 b  uint16_t ?
ends
v   uint16_t ?
XMU565 ends

XMFLOAT3PK union
struct
 XMFLOAT3PK_XM  equ 6 ; x-mantissa
 XMFLOAT3PK_XE  equ 5 ; x-exponent
 XMFLOAT3PK_YM  equ 6 ; y-mantissa
 XMFLOAT3PK_YE  equ 5 ; y-exponent
 XMFLOAT3PK_ZM  equ 5 ; z-mantissa
 XMFLOAT3PK_ZE  equ 5 ; z-exponent
 b  uint32_t ?
ends
v   uint32_t ?
XMFLOAT3PK ends

XMFLOAT3SE union
struct
 XMFLOAT3SE_XM equ 9 ; x-mantissa
 XMFLOAT3SE_YM equ 9 ; y-mantissa
 XMFLOAT3SE_ZM equ 9 ; z-mantissa
 XMFLOAT3SE_E  equ 5 ; shared exponent
 b  uint32_t ?
ends
v   uint32_t ?
XMFLOAT3SE ends

XMHALF4 union
struct
 x  HALF ?
 y  HALF ?
 z  HALF ?
 w  HALF ?
ends
v   uint64_t ?
XMHALF4 ends

XMSHORTN4 union
struct
 x  int16_t ?
 y  int16_t ?
 z  int16_t ?
 w  int16_t ?
ends
v   uint64_t ?
XMSHORTN4 ends

XMSHORT4 union
struct
 x  int16_t ?
 y  int16_t ?
 z  int16_t ?
 w  int16_t ?
ends
v   uint64_t ?
XMSHORT4 ends

XMUSHORTN4 union
struct
 x  uint16_t ?
 y  uint16_t ?
 z  uint16_t ?
 w  uint16_t ?
ends
v   uint64_t ?
XMUSHORTN4 ends

XMUSHORT4 union
struct
 x  uint16_t ?
 y  uint16_t ?
 z  uint16_t ?
 w  uint16_t ?
ends
v   uint64_t ?
XMUSHORT4 ends

XMXDECN4 union
struct
 x  uint32_t ?
ends
v   uint32_t ?
XMXDECN4 ends

XMXDEC4 union
struct
 x  uint32_t ?
ends
v   uint32_t ?
XMXDEC4 ends

XMDECN4 union
struct
 x  uint32_t ?
ends
v   uint32_t ?
XMDECN4 ends

XMDEC4 union
struct
 x  uint32_t ?
ends
v   uint32_t ?
XMDEC4 ends

XMUDECN4 union
struct
 ; uint32_t x  : 10;    // 0/1023 to 1023/1023
 ; uint32_t y  : 10;    // 0/1023 to 1023/1023
 ; uint32_t z  : 10;    // 0/1023 to 1023/1023
 ; uint32_t w  : 2;     //    0/3 to       3/3
 x  uint32_t ?
ends
v   uint32_t ?
XMUDECN4 ends

XMUDEC4 union
struct
 x  uint32_t ?
ends
v   uint32_t ?
XMUDEC4 ends

XMBYTEN4 union
struct
 x  int8_t ?
 y  int8_t ?
 z  int8_t ?
 w  int8_t ?
ends
v   uint32_t ?
XMBYTEN4 ends

XMBYTE4 union
struct
 x  int8_t ?
 y  int8_t ?
 z  int8_t ?
 w  int8_t ?
ends
v   uint32_t ?
XMBYTE4 ends

XMUBYTEN4 union
struct
 x  uint8_t ?
 y  uint8_t ?
 z  uint8_t ?
 w  uint8_t ?
ends
v   uint32_t ?
XMUBYTEN4 ends

XMUBYTE4 union
struct
 x  uint8_t ?
 y  uint8_t ?
 z  uint8_t ?
 w  uint8_t ?
ends
v   uint32_t ?
XMUBYTE4 ends

XMUNIBBLE4 union
struct
 x  uint16_t ?
ends
v   uint16_t ?
XMUNIBBLE4 ends

XMU555 union
struct
 x  uint16_t ?
ends
v   uint16_t ?
XMU555 ends

;float
XMConvertHalfToFloat proto :HALF
;HALF
XMConvertFloatToHalf proto :float
;float*
XMConvertHalfToFloatStream proto :ptr float, :size_t, :ptr HALF, :size_t, :size_t
;HALF*
XMConvertFloatToHalfStream proto :ptr HALF, :size_t, :ptr float, :size_t, :size_t


;XMVECTOR
XMLoadColor     proto XM_CALLCONV :ptr XMCOLOR
XMLoadHalf2     proto XM_CALLCONV :ptr XMHALF2
XMLoadShortN2   proto XM_CALLCONV :ptr XMSHORTN2
XMLoadShort2    proto XM_CALLCONV :ptr XMSHORT2
XMLoadUShortN2  proto XM_CALLCONV :ptr XMUSHORTN2
XMLoadUShort2   proto XM_CALLCONV :ptr XMUSHORT2
XMLoadByteN2    proto XM_CALLCONV :ptr XMBYTEN2
XMLoadByte2     proto XM_CALLCONV :ptr XMBYTE2
XMLoadUByteN2   proto XM_CALLCONV :ptr XMUBYTEN2
XMLoadUByte2    proto XM_CALLCONV :ptr XMUBYTE2

XMLoadU565      proto XM_CALLCONV :ptr XMU565
XMLoadFloat3PK  proto XM_CALLCONV :ptr XMFLOAT3PK
XMLoadFloat3SE  proto XM_CALLCONV :ptr XMFLOAT3SE

XMLoadHalf4     proto XM_CALLCONV :ptr XMHALF4
XMLoadShortN4   proto XM_CALLCONV :ptr XMSHORTN4
XMLoadShort4    proto XM_CALLCONV :ptr XMSHORT4
XMLoadUShortN4  proto XM_CALLCONV :ptr XMUSHORTN4
XMLoadUShort4   proto XM_CALLCONV :ptr XMUSHORT4
XMLoadXDecN4    proto XM_CALLCONV :ptr XMXDECN4
XMLoadXDec4     proto XM_CALLCONV :ptr XMXDEC4
XMLoadDecN4     proto XM_CALLCONV :ptr XMDECN4
XMLoadDec4      proto XM_CALLCONV :ptr XMDEC4
XMLoadUDecN4    proto XM_CALLCONV :ptr XMUDECN4
XMLoadUDecN4_XR proto XM_CALLCONV :ptr XMUDECN4
XMLoadUDec4     proto XM_CALLCONV :ptr XMUDEC4
XMLoadByteN4    proto XM_CALLCONV :ptr XMBYTEN4
XMLoadByte4     proto XM_CALLCONV :ptr XMBYTE4
XMLoadUByteN4   proto XM_CALLCONV :ptr XMUBYTEN4
XMLoadUByte4    proto XM_CALLCONV :ptr XMUBYTE4
XMLoadUNibble4  proto XM_CALLCONV :ptr XMUNIBBLE4
XMLoadU555      proto XM_CALLCONV :ptr XMU555

;void
XMStoreColor    proto XM_CALLCONV :ptr XMCOLOR, :FXMVECTOR

XMStoreHalf2    proto XM_CALLCONV :ptr XMHALF2, :FXMVECTOR
XMStoreShortN2  proto XM_CALLCONV :ptr XMSHORTN2, :FXMVECTOR
XMStoreShort2   proto XM_CALLCONV :ptr XMSHORT2, :FXMVECTOR
XMStoreUShortN2 proto XM_CALLCONV :ptr XMUSHORTN2, :FXMVECTOR
XMStoreUShort2  proto XM_CALLCONV :ptr XMUSHORT2, :FXMVECTOR
XMStoreByteN2   proto XM_CALLCONV :ptr XMBYTEN2, :FXMVECTOR
XMStoreByte2    proto XM_CALLCONV :ptr XMBYTE2, :FXMVECTOR
XMStoreUByteN2  proto XM_CALLCONV :ptr XMUBYTEN2, :FXMVECTOR
XMStoreUByte2   proto XM_CALLCONV :ptr XMUBYTE2, :FXMVECTOR

XMStoreU565     proto XM_CALLCONV :ptr XMU565, :FXMVECTOR
XMStoreFloat3PK proto XM_CALLCONV :ptr XMFLOAT3PK, :FXMVECTOR
XMStoreFloat3SE proto XM_CALLCONV :ptr XMFLOAT3SE, :FXMVECTOR

XMStoreHalf4    proto XM_CALLCONV :ptr XMHALF4, :FXMVECTOR
XMStoreShortN4  proto XM_CALLCONV :ptr XMSHORTN4, :FXMVECTOR
XMStoreShort4   proto XM_CALLCONV :ptr XMSHORT4, :FXMVECTOR
XMStoreUShortN4 proto XM_CALLCONV :ptr XMUSHORTN4, :FXMVECTOR
XMStoreUShort4  proto XM_CALLCONV :ptr XMUSHORT4, :FXMVECTOR
XMStoreXDecN4   proto XM_CALLCONV :ptr XMXDECN4, :FXMVECTOR
XMStoreXDec4    proto XM_CALLCONV :ptr XMXDEC4, :FXMVECTOR
XMStoreDecN4    proto XM_CALLCONV :ptr XMDECN4, :FXMVECTOR
XMStoreDec4     proto XM_CALLCONV :ptr XMDEC4, :FXMVECTOR
XMStoreUDecN4   proto XM_CALLCONV :ptr XMUDECN4, :FXMVECTOR
XMStoreUDecN4_XR proto XM_CALLCONV :ptr XMUDECN4, :FXMVECTOR
XMStoreUDec4    proto XM_CALLCONV :ptr XMUDEC4, :FXMVECTOR
XMStoreByteN4   proto XM_CALLCONV :ptr XMBYTEN4, :FXMVECTOR
XMStoreByte4    proto XM_CALLCONV :ptr XMBYTE4, :FXMVECTOR
XMStoreUByteN4  proto XM_CALLCONV :ptr XMUBYTEN4, :FXMVECTOR
XMStoreUByte4   proto XM_CALLCONV :ptr XMUBYTE4, :FXMVECTOR
XMStoreUNibble4 proto XM_CALLCONV :ptr XMUNIBBLE4, :FXMVECTOR
XMStoreU555     proto XM_CALLCONV :ptr XMU555, :FXMVECTOR

include DirectXPackedVector.inl

.pragma list(pop)
endif
