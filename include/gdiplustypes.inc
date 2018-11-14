ifndef _GDIPLUSTYPES_H
_GDIPLUSTYPES_H equ <>

CALLBACK(EnumerateMetafileProc, :ptr, :UINT, :UINT, :ptr, :ptr)

if (GDIPVER GE 0x0110)
endif

REAL			typedef REAL4

REAL_MAX		equ FLT_MAX
REAL_MIN		equ FLT_MIN
REAL_TOLERANCE		equ (FLT_MIN * 100)
REAL_EPSILON		equ 1.192092896e-07

Status			typedef SDWORD
Ok			equ 0
GenericError		equ 1
InvalidParameter	equ 2
OutOfMemory		equ 3
ObjectBusy		equ 4
InsufficientBuffer	equ 5
NotImplemented		equ 6
Win32Error		equ 7
WrongState		equ 8
Aborted			equ 9
FileNotFound		equ 10
ValueOverflow		equ 11
AccessDenied		equ 12
UnknownImageFormat	equ 13
FontFamilyNotFound	equ 14
FontStyleNotFound	equ 15
NotTrueTypeFont		equ 16
UnsupportedGdiplusVersion equ 17
GdiplusNotInitialized	equ 18
PropertyNotFound	equ 19
PropertyNotSupported	equ 20
if (GDIPVER GE 0x0110)
ProfileNotFound		equ 21
endif

endif ;; NOT _GDIPLUSTYPES_HPP

