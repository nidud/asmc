ifndef _INTSAFE_H_INCLUDED_
_INTSAFE_H_INCLUDED_ equ <>

include specstrings.inc

ifdef _WIN64
    __fastcall equ <>
    ifdef _LINUX
        __bytereg  equ <dil>
        __wordreg  equ <di>
        __dwordreg equ <edi>
        __qwordreg equ <rdi>
    else
        __bytereg  equ <cl>
        __wordreg  equ <cx>
        __dwordreg equ <ecx>
        __qwordreg equ <rcx>
    endif
else
    __fastcall equ <watcall>
    __bytereg  equ <al>
    __wordreg  equ <ax>
    __dwordreg equ <eax>
endif

CHAR                    typedef sbyte
INT8                    typedef sbyte
UCHAR                   typedef byte
UINT8                   typedef byte
INT16                   typedef sword
SSHORT                  typedef sword
USHORT                  typedef word
UINT16                  typedef word
INT32                   typedef sdword
UINT                    typedef dword
UINT32                  typedef dword
LONG                    typedef sdword
ULONG                   typedef dword
LONGLONG                typedef sqword
LONG64                  typedef sqword
INT64                   typedef sqword
ULONGLONG               typedef qword
DWORDLONG               typedef qword
ULONG64                 typedef qword
DWORD64                 typedef qword
UINT64                  typedef qword

ifdef _WIN64
INT_PTR                 typedef sqword
UINT_PTR                typedef qword
LONG_PTR                typedef sqword
ULONG_PTR               typedef qword
else
INT_PTR                 typedef sdword
UINT_PTR                typedef dword
LONG_PTR                typedef sdword
ULONG_PTR               typedef dword
endif

ifdef _WIN64
ptrdiff_t               typedef sqword
size_t                  typedef qword
else
ptrdiff_t               typedef sdword
size_t                  typedef dword
endif

DWORD_PTR               typedef ULONG_PTR
SSIZE_T                 typedef LONG_PTR
SIZE_T                  typedef ULONG_PTR

undef _USE_INTRINSIC_MULTIPLY128

if NOT defined(_M_CEE) AND (defined(_AMD64_) OR (defined(_IA64_) AND (_MSC_VER GE 1400)))
_USE_INTRINSIC_MULTIPLY128 equ 1
endif

if defined(_USE_INTRINSIC_MULTIPLY128)

UnsignedMultiply128     equ <_umul128>

endif

HRESULT                 typedef LONG

SUCCEEDED macro hr
        exitm<(sdword ptr hr !>= 0)>
        endm
FAILED macro hr
        exitm<(sdword ptr hr !< 0)>
        endm

S_OK equ 0

INTSAFE_E_ARITHMETIC_OVERFLOW equ 0x80070216
ifndef SORTPP_PASS
C_ASSERT macro e
    if e
      exitm<>
    endif
    .err <e>
    endm
else
C_ASSERT macro e
    exitm<1>
    endm
endif

if defined(MIDL_PASS) OR defined(RC_INVOKED) OR defined(_M_CEE_PURE) OR defined(_68K_) OR defined(_MPPC_) OR defined(_M_IA64) OR defined(_M_AMD64)
UInt32x32To64 macro a, b
        mov eax,a
        imul eax,b
        retm<eax>
        endm
elseif defined(_M_IX86)
UInt32x32To64 macro a, b
        mov eax,a
        imul eax,b
        retm<eax>
        endm
else
.err <Must define a target architecture.>
endif

INT8_MIN                equ (-127i8 - 1)
SHORT_MIN               equ (-32768)
INT16_MIN               equ (-32767i16 - 1)
INT_MIN                 equ (-2147483647 - 1)
INT32_MIN               equ (-2147483647i32 - 1)
LONG_MIN                equ (-2147483647 - 1)
LONGLONG_MIN            equ (-9223372036854775807i64 - 1)
LONG64_MIN              equ (-9223372036854775807i64 - 1)
INT64_MIN               equ (-9223372036854775807i64 - 1)
INT128_MIN              equ (-170141183460469231731687303715884105727i128 - 1)

ifdef _WIN64
INT_PTR_MIN             equ (-9223372036854775807i64 - 1)
LONG_PTR_MIN            equ (-9223372036854775807i64 - 1)
PTRDIFF_T_MIN           equ (-9223372036854775807i64 - 1)
SSIZE_T_MIN             equ (-9223372036854775807i64 - 1)
else
INT_PTR_MIN             equ (-2147483647 - 1)
LONG_PTR_MIN            equ (-2147483647 - 1)
PTRDIFF_T_MIN           equ (-2147483647 - 1)
SSIZE_T_MIN             equ (-2147483647 - 1)
endif

INT8_MAX                equ 127
UINT8_MAX               equ 0xffu
BYTE_MAX                equ 0xff
SHORT_MAX               equ 32767
INT16_MAX               equ 32767
USHORT_MAX              equ 0xffff
UINT16_MAX              equ 0xffff
WORD_MAX                equ 0xffff
INT_MAX                 equ 2147483647
INT32_MAX               equ 2147483647
UINT_MAX                equ 0xffffffff
UINT32_MAX              equ 0xffffffff
LONG_MAX                equ 2147483647
ULONG_MAX               equ 0xffffffff
DWORD_MAX               equ 0xffffffff
LONGLONG_MAX            equ 9223372036854775807
LONG64_MAX              equ 9223372036854775807
INT64_MAX               equ 9223372036854775807
ULONGLONG_MAX           equ 0xffffffffffffffff
DWORDLONG_MAX           equ 0xffffffffffffffff
ULONG64_MAX             equ 0xffffffffffffffff
DWORD64_MAX             equ 0xffffffffffffffff
UINT64_MAX              equ 0xffffffffffffffff
INT128_MAX              equ 170141183460469231731687303715884105727
UINT128_MAX             equ 0xffffffffffffffffffffffffffffffff

undef SIZE_T_MAX

ifdef _WIN64
INT_PTR_MAX             equ 9223372036854775807
UINT_PTR_MAX            equ 0xffffffffffffffff
LONG_PTR_MAX            equ 9223372036854775807
ULONG_PTR_MAX           equ 0xffffffffffffffff
DWORD_PTR_MAX           equ 0xffffffffffffffff
PTRDIFF_T_MAX           equ 9223372036854775807
SIZE_T_MAX              equ 0xffffffffffffffff
SSIZE_T_MAX             equ 9223372036854775807
_SIZE_T_MAX             equ 0xffffffffffffffff
else
INT_PTR_MAX             equ 2147483647
UINT_PTR_MAX            equ 0xffffffff
LONG_PTR_MAX            equ 2147483647
ULONG_PTR_MAX           equ 0xffffffff
DWORD_PTR_MAX           equ 0xffffffff
PTRDIFF_T_MAX           equ 2147483647
SIZE_T_MAX              equ 0xffffffff
SSIZE_T_MAX             equ 2147483647
_SIZE_T_MAX             equ 0xffffffff
endif


INT8_ERROR              equ (-1)
UINT8_ERROR             equ 0xff
BYTE_ERROR              equ 0xff
SHORT_ERROR             equ (-1)
INT16_ERROR             equ (-1)
USHORT_ERROR            equ 0xffff
UINT16_ERROR            equ 0xffff
WORD_ERROR              equ 0xffff
INT_ERROR               equ (-1)
INT32_ERROR             equ (-1)
UINT_ERROR              equ 0xffffffff
UINT32_ERROR            equ 0xffffffff
LONG_ERROR              equ (-1)
ULONG_ERROR             equ 0xffffffff
DWORD_ERROR             equ 0xffffffff
LONGLONG_ERROR          equ (-1)
LONG64_ERROR            equ (-1)
INT64_ERROR             equ (-1)
ULONGLONG_ERROR         equ 0xffffffffffffffff
DWORDLONG_ERROR         equ 0xffffffffffffffff
ULONG64_ERROR           equ 0xffffffffffffffff
UINT64_ERROR            equ 0xffffffffffffffff

ifdef _WIN64
INT_PTR_ERROR           equ (-1)
UINT_PTR_ERROR          equ 0xffffffffffffffff
LONG_PTR_ERROR          equ (-1)
ULONG_PTR_ERROR         equ 0xffffffffffffffff
DWORD_PTR_ERROR         equ 0xffffffffffffffff
PTRDIFF_T_ERROR         equ (-1)
SIZE_T_ERROR            equ 0xffffffffffffffff
SSIZE_T_ERROR           equ (-1)
_SIZE_T_ERROR           equ 0xffffffffffffffff
else
INT_PTR_ERROR           equ (-1)
UINT_PTR_ERROR          equ 0xffffffff
LONG_PTR_ERROR          equ (-1)
ULONG_PTR_ERROR         equ 0xffffffff
DWORD_PTR_ERROR         equ 0xffffffff
PTRDIFF_T_ERROR         equ (-1)
SIZE_T_ERROR            equ 0xffffffff
SSIZE_T_ERROR           equ (-1)
_SIZE_T_ERROR           equ 0xffffffff
endif


C_ASSERT(sizeof(USHORT) eq 2)
C_ASSERT(sizeof(SINT) eq 4)
C_ASSERT(sizeof(UINT) eq 4)
C_ASSERT(sizeof(LONG) eq 4)
C_ASSERT(sizeof(ULONG) eq 4)
C_ASSERT(sizeof(UINT_PTR) eq sizeof(ULONG_PTR))


Int8ToUChar proto __fastcall :INT8, :ptr UCHAR {

    .ifs (this >= 0)
        mov UCHAR ptr [_1],this
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

Int8ToUInt8 proto __fastcall :INT8, :ptr UINT8 {

    .ifs (this >= 0)
        mov UINT8 ptr [_1],this
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

Int8ToByte equ <Int8ToUInt8>

Int8ToUShort proto __fastcall :INT8, :ptr USHORT {

    .ifs (this >= 0)
        mov USHORT ptr [_1],this
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

Int8ToUInt16 equ <Int8ToUShort>
Int8ToWord   equ <Int8ToUShort>

Int8ToUInt proto __fastcall :INT8, :ptr UINT {

    .ifs (this >= 0)
        mov UINT ptr [_1],this
        mov eax,S_OK
    .else
        mov UINT ptr [_1],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

Int8ToUInt32 equ <Int8ToUInt>

Int8ToUIntPtr proto __fastcall :INT8, :ptr UINT_PTR {

    .ifs (this >= 0)
        mov UINT_PTR ptr [_1],this
        mov eax,S_OK
    .else
        mov UINT_PTR ptr [_1],UINT_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }


Int8ToULong proto __fastcall :INT8, :ptr ULONG {

    .ifs (this >= 0)
        mov ULONG ptr [_1],this
        mov eax,S_OK
    .else
        mov ULONG ptr [_1],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }


Int8ToULongPtr proto __fastcall :INT8, :ptr ULONG_PTR {

    .ifs (this >= 0)
        mov ULONG_PTR ptr [_1],this
        mov eax,S_OK
    .else
        mov ULONG_PTR ptr [_1],ULONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

Int8ToDWord     equ <Int8ToULong>
Int8ToDWordPtr  equ <Int8ToULongPtr>

Int8ToULongLong proto __fastcall :INT8, :ptr ULONGLONG {

    .ifs (this >= 0)
        mov ULONGLONG ptr [_1],this
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_1],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

Int8ToDWordLong equ <Int8ToULongLong>
Int8ToULong64   equ <Int8ToULongLong>
Int8ToDWord64   equ <Int8ToULongLong>
Int8ToUInt64    equ <Int8ToULongLong>
Int8ToSizeT     equ <Int8ToUIntPtr>
Int8ToSIZET     equ <Int8ToULongPtr>

UInt8ToInt8 proto __fastcall :UINT8, :ptr INT8 {

    .ifs (this <= INT8_MAX)
        mov INT8 ptr [_1],this
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UInt8ToChar proto __fastcall :UINT8, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    mov CHAR ptr [_1],this
    mov eax,S_OK
else
    UInt8ToInt8(this, _1)
endif
    }

ByteToInt8 proto __fastcall :BYTE, :ptr INT8 {

    .ifs (this <= INT8_MAX)
        mov INT8 ptr [_1],this
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ByteToChar proto __fastcall :BYTE, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    mov CHAR ptr [_1],this
    mov eax,S_OK
else
    ByteToInt8(this, _1)
endif
    }

ShortToInt8 proto __fastcall :SSHORT, :ptr INT8 {

    .ifs (this >= INT8_MIN && this <= INT8_MAX)
        mov INT8 ptr [_1],this
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }


ShortToUChar proto __fastcall :SSHORT, :ptr UCHAR {

    .ifs (this >= 0 && this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ShortToChar proto __fastcall :SSHORT, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    ShortToUChar(this, _1)
else
    ShortToInt8(this, _1)
endif
    }

ShortToUInt8 proto __fastcall :SSHORT, :ptr UINT8 {

    .ifs (this >= 0 && this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }


ShortToByte equ <ShortToUInt8>

ShortToUShort proto __fastcall :SSHORT, :ptr USHORT {

    .ifs (this >= 0)
        mov USHORT ptr [_1],this
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ShortToUInt16 equ <ShortToUShort>
ShortToWord   equ <ShortToUShort>

ShortToUInt proto __fastcall :SSHORT, :ptr UINT {

    .ifs (this >= 0)
        movzx eax,this
        mov [_1],eax
        mov eax,S_OK
    .else
        mov UINT ptr [_1],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ShortToUInt32 equ <ShortToUInt>

ShortToUIntPtr proto __fastcall :SSHORT, :ptr UINT_PTR {

    .ifs (this >= 0)
        movzx eax,this
        mov [_1],eax
        mov eax,S_OK
    .else
        mov UINT_PTR ptr [_1],UINT_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ShortToULong proto __fastcall :SSHORT, :ptr ULONG {

    .ifs (this >= 0)
        movzx eax,this
        mov [_1],eax
        mov eax,S_OK
    .else
        mov ULONG ptr [_1],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ShortToULongPtr proto __fastcall :SSHORT, :ptr ULONG_PTR {

    .ifs (this >= 0)
        movzx eax,this
        mov [_1],eax
        mov eax,S_OK
    .else
        mov ULONG_PTR ptr [_1],ULONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ShortToDWord equ <ShortToULong>

ShortToDWordPtr proto __fastcall :SSHORT, :ptr DWORD_PTR {

    .ifs (this >= 0)
        movzx eax,this
        mov [_1],eax
        mov eax,S_OK
    .else
        mov DWORD_PTR ptr [_1],DWORD_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ShortToULongLong proto __fastcall :SSHORT, :ptr ULONGLONG {

    .ifs (this >= 0)
        movzx eax,this
        mov [_1],rax
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_1],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ShortToDWordLong        equ <ShortToULongLong>
ShortToULong64          equ <ShortToULongLong>
ShortToDWord64          equ <ShortToULongLong>
ShortToUInt64           equ <ShortToULongLong>
ShortToSizeT            equ <ShortToUIntPtr>
ShortToSIZET            equ <ShortToULongPtr>
Int16ToChar             equ <ShortToChar>
Int16ToInt8             equ <ShortToInt8>
Int16ToUChar            equ <ShortToUChar>
Int16ToUInt8            equ <ShortToUInt8>
Int16ToByte             equ <ShortToUInt8>
Int16ToUShort           equ <ShortToUShort>
Int16ToUInt16           equ <ShortToUShort>
Int16ToWord             equ <ShortToUShort>
Int16ToUInt             equ <ShortToUInt>
Int16ToUInt32           equ <ShortToUInt>
Int16ToUIntPtr          equ <ShortToUIntPtr>
Int16ToULong            equ <ShortToULong>
Int16ToULongPtr         equ <ShortToULongPtr>
Int16ToDWord            equ <ShortToULong>
Int16ToDWordPtr         equ <ShortToULongPtr>
Int16ToULongLong        equ <ShortToULongLong>
Int16ToDWordLong        equ <ShortToULongLong>
Int16ToULong64          equ <ShortToULongLong>
Int16ToDWord64          equ <ShortToULongLong>
Int16ToUInt64           equ <ShortToULongLong>
Int16ToSizeT            equ <ShortToUIntPtr>
Int16ToSIZET            equ <ShortToULongPtr>

UShortToInt8 proto __fastcall :USHORT, :ptr INT8 {

    .ifs (this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UShortToUChar proto __fastcall :USHORT, :ptr UCHAR {

    .ifs (this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UShortToChar proto __fastcall :USHORT, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    UShortToUChar(this, _1)
else
    UShortToInt8(this, _1)
endif
    }

UShortToUInt8 proto __fastcall :USHORT, :ptr UINT8 {

    .ifs (this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UShortToByte equ <UShortToUInt8>

UShortToShort proto __fastcall :USHORT, :ptr SSHORT {

    .ifs (this <= SSHORT_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UShortToInt16           equ <UShortToShort>
UInt16ToChar            equ <UShortToChar>
UInt16ToInt8            equ <UShortToInt8>
UInt16ToUChar           equ <UShortToUChar>
UInt16ToUInt8           equ <UShortToUInt8>
UInt16ToByte            equ <UShortToUInt8>
UInt16ToShort           equ <UShortToShort>
UInt16ToInt16           equ <UShortToShort>
WordToInt8              equ <UShortToInt8>
WordToChar              equ <UShortToChar>
WordToUChar             equ <UShortToUChar>
WordToUInt8             equ <UShortToUInt8>
WordToByte              equ <UShortToUInt8>
WordToShort             equ <UShortToShort>
WordToInt16             equ <UShortToShort>

IntToInt8 proto :int_t, :ptr INT8 {

    .ifs (this >= INT8_MIN && this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntToUChar proto __fastcall :SINT, :ptr UCHAR {

    .ifs (this >= 0 && this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntToChar proto __fastcall :int_t, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    IntToUChar(this, _1)
else
    IntToInt8(this, _1)
endif
    }

IntToByte equ <IntToUInt8>

IntToUInt8 proto __fastcall :int_t, :ptr UINT8 {

    .ifs (this >= 0 && this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntToShort proto __fastcall :int_t, :ptr SSHORT {

    .ifs (this >= SSHORT_MIN && this <= SSHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SSHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntToInt16 equ <IntToShort>

IntToUShort proto __fastcall :int_t, :ptr USHORT {

    .ifs (this >= 0 && this <= USHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntToUInt16 equ <IntToUShort>
IntToWord   equ <IntToUShort>

IntToUInt proto __fastcall :int_t, :ptr UINT {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov UINT ptr [_1],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
IntToUIntPtr equ <IntToULongLong>
else
IntToUIntPtr equ <IntToUInt>
endif

IntToULong proto __fastcall :int_t, :ptr ULONG {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONG ptr [_1],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
IntToULongPtr equ <IntToULongLong>
else
IntToULongPtr equ <IntToULong>
endif
IntToDWord    equ <IntToULong>
IntToDWordPtr equ <IntToULongPtr>

IntToULongLong proto __fastcall :int_t, :ptr ULONGLONG {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_1],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntToDWordLong          equ <IntToULongLong>
IntToULong64            equ <IntToULongLong>
IntToDWord64            equ <IntToULongLong>
IntToUInt64             equ <IntToULongLong>
IntToSizeT              equ <IntToUIntPtr>
IntToSIZET              equ <IntToULongPtr>
Int32ToChar             equ <IntToChar>
Int32ToInt8             equ <IntToInt8>
Int32ToUChar            equ <IntToUChar>
Int32ToByte             equ <IntToUInt8>
Int32ToUInt8            equ <IntToUInt8>
Int32ToShort            equ <IntToShort>
Int32ToInt16            equ <IntToShort>
Int32ToUShort           equ <IntToUShort>
Int32ToUInt16           equ <IntToUShort>
Int32ToWord             equ <IntToUShort>
Int32ToUInt             equ <IntToUInt>
Int32ToUInt32           equ <IntToUInt>
Int32ToUIntPtr          equ <IntToUIntPtr>
Int32ToULong            equ <IntToULong>
Int32ToULongPtr         equ <IntToULongPtr>
Int32ToDWord            equ <IntToULong>
Int32ToDWordPtr         equ <IntToULongPtr>
Int32ToULongLong        equ <IntToULongLong>
Int32ToDWordLong        equ <IntToULongLong>
Int32ToULong64          equ <IntToULongLong>
Int32ToDWord64          equ <IntToULongLong>
Int32ToUInt64           equ <IntToULongLong>
Int32ToSizeT            equ <IntToUIntPtr>
Int32ToSIZET            equ <IntToULongPtr>

IntPtrToInt8 proto __fastcall :INT_PTR, :ptr INT8 {

    .ifs (this >= INT8_MIN && this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntPtrToUChar proto __fastcall :INT_PTR, :ptr UCHAR {

    .ifs (this >= 0 && this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntPtrToChar proto __fastcall :INT_PTR, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    IntPtrToUChar(this, _1)
else
    IntPtrToInt8(this, _1)
endif
    }

IntPtrToUInt8 proto __fastcall :INT_PTR, :ptr UINT8 {

    .ifs (this >= 0 && this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntPtrToByte equ <IntPtrToUInt8>

IntPtrToShort proto __fastcall :INT_PTR, :ptr SSHORT {

    .ifs (this >= SSHORT_MIN && this <= SSHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SSHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntPtrToInt16 equ <IntPtrToShort>

IntPtrToUShort proto __fastcall :INT_PTR, :ptr USHORT {

    .ifs (this >= 0 && this <= USHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

IntPtrToUInt16 equ <IntPtrToUShort>
IntPtrToWord   equ <IntPtrToUShort>

ifdef _WIN64
IntPtrToInt    equ <LongLongToInt>
else
IntPtrToInt proto __fastcall :INT_PTR, :ptr SINT {

    mov [_1],this
    mov eax,S_OK
    }
endif

IntPtrToInt32 equ <IntPtrToInt>
ifdef _WIN64
IntPtrToUInt  equ <LongLongToUInt>
else
IntPtrToUInt proto __fastcall :INT_PTR, :ptr UINT {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov UINT ptr [_1],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

IntPtrToUInt32  equ <IntPtrToUInt>
ifdef _WIN64
IntPtrToUIntPtr equ <LongLongToULongLong>
else
IntPtrToUIntPtr proto __fastcall :INT_PTR, :ptr UINT_PTR {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov UINT_PTR ptr [_1],UINT_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

ifdef _WIN64
IntPtrToLong equ <LongLongToLong>
else
IntPtrToLong proto __fastcall :INT_PTR, :ptr LONG {
    mov [_1],this
    mov eax,S_OK
    }
endif

IntPtrToLongPtr proto __fastcall :INT_PTR, :ptr LONG_PTR {
    mov [_1],this
    mov eax,S_OK
    }

ifdef _WIN64
IntPtrToULong equ <LongLongToULong>
else
IntPtrToULong proto __fastcall :INT_PTR, :ptr ULONG {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONG ptr [_1],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

ifdef _WIN64
IntPtrToULongPtr equ <LongLongToULongLong>
else
IntPtrToULongPtr proto __fastcall :INT_PTR, :ptr ULONG_PTR {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONG_PTR ptr [_1],ULONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

IntPtrToDWord     equ <IntPtrToULong>
IntPtrToDWordPtr  equ <IntPtrToULongPtr>

ifdef _WIN64
IntPtrToULongLong equ <LongLongToULongLong>
else
IntPtrToULongLong proto __fastcall :INT_PTR, :ptr ULONGLONG {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_1],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

IntPtrToDWordLong equ <IntPtrToULongLong>
IntPtrToULong64   equ <IntPtrToULongLong>
IntPtrToDWord64   equ <IntPtrToULongLong>
IntPtrToUInt64    equ <IntPtrToULongLong>
IntPtrToSizeT     equ <IntPtrToUIntPtr>
IntPtrToSIZET     equ <IntPtrToULongPtr>

UIntToInt8 proto __fastcall :UINT, :ptr INT8 {

    .ifs (this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntToUChar proto __fastcall :UINT, :ptr UCHAR {

    .ifs (this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntToChar proto __fastcall :UINT, :ptr {
ifdef _CHAR_UNSIGNED
    UIntToUChar(this, _1)
else
    UIntToInt8(this, _1)
endif
    }

UIntToUInt8 proto __fastcall :UINT, :ptr UINT8 {

    .ifs (this <= UINT8_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntToByte equ <UIntToUInt8>

UIntToShort proto __fastcall :UINT, :ptr SSHORT {

    .ifs (this <= SSHORT_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SSHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntToInt16 equ <UIntToShort>

UIntToUShort proto __fastcall :UINT, :ptr USHORT {

    .ifs (this <= USHORT_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntToUInt16 equ <UIntToUShort>
UIntToWord   equ <UIntToUShort>

UIntToInt proto __fastcall :UINT, :ptr SINT {

    .ifs (this <= INT_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov SINT ptr [_1],INT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntToInt32 equ <UIntToInt>

ifdef _WIN64
UIntToIntPtr proto __fastcall :UINT, :ptr INT_PTR {
    mov [_1],this
    mov eax,S_OK
    }
else
UIntToIntPtr equ <UIntToInt>
endif

UIntToLong proto __fastcall :UINT, :ptr LONG {

    .ifs (this <= LONG_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov LONG ptr [_1],LONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
UIntToLongPtr proto __fastcall :UINT, :ptr LONG_PTR {
    mov [_1],this
    mov eax,S_OK
    }
else
UIntToLongPtr equ <UIntToLong>
endif

UIntToPtrdiffT          equ <UIntToIntPtr>
UIntToSSIZET            equ <UIntToLongPtr>
UInt32ToChar            equ <UIntToChar>
UInt32ToInt8            equ <UIntToInt8>
UInt32ToUChar           equ <UIntToUChar>
UInt32ToUInt8           equ <UIntToUInt8>
UInt32ToByte            equ <UInt32ToUInt8>
UInt32ToShort           equ <UIntToShort>
UInt32ToInt16           equ <UIntToShort>
UInt32ToUShort          equ <UIntToUShort>
UInt32ToUInt16          equ <UIntToUShort>
UInt32ToWord            equ <UIntToUShort>
UInt32ToInt             equ <UIntToInt>
UInt32ToIntPtr          equ <UIntToIntPtr>
UInt32ToInt32           equ <UIntToInt>
UInt32ToLong            equ <UIntToLong>
UInt32ToLongPtr         equ <UIntToLongPtr>
UInt32ToPtrdiffT        equ <UIntToPtrdiffT>
UInt32ToSSIZET          equ <UIntToSSIZET>

UIntPtrToInt8 proto __fastcall :UINT_PTR, :ptr INT8 {

    .ifs (this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntPtrToUChar proto __fastcall :UINT_PTR, :ptr UCHAR {

    .ifs (this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntPtrToChar proto __fastcall :UINT_PTR, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    UIntPtrToUChar(this, _1)
else
    UIntPtrToInt8(this, _1)
endif
    }

UIntPtrToUInt8 proto __fastcall :UINT_PTR, :ptr UINT8 {

    .ifs (this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntPtrToByte equ <UIntPtrToUInt8>

UIntPtrToShort proto __fastcall :UINT_PTR, :ptr SSHORT {

    .ifs (this <= SSHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SSHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntPtrToInt16 proto __fastcall :UINT_PTR, :ptr INT16 {

    .ifs (this <= SSHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov INT16 ptr [_1],INT16_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntPtrToUShort proto __fastcall :UINT_PTR, :ptr USHORT {

    .ifs (this <= USHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntPtrToUInt16 proto __fastcall :UINT_PTR, :ptr UINT16 {

    .ifs (this <= UINT16_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov UINT16 ptr [_1],UINT16_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntPtrToWord equ <UIntPtrToUShort>

UIntPtrToInt proto __fastcall :UINT_PTR, :ptr SINT {

    .ifs (this <= INT_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov SINT ptr [_1],INT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntPtrToInt32 equ <UIntPtrToInt>

UIntPtrToIntPtr proto __fastcall :UINT_PTR, :ptr INT_PTR {

    .ifs (this <= INT_PTR_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov INT_PTR ptr [_1],INT_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
UIntPtrToUInt equ <ULongLongToUInt>
else
UIntPtrToUInt proto __fastcall :UINT_PTR, :ptr UINT {
    mov [_1],__dwordreg
    mov eax,S_OK
    }
endif

UIntPtrToUInt32 equ <UIntPtrToUInt>

UIntPtrToLong proto __fastcall :UINT_PTR, :ptr LONG {

    .ifs (this <= LONG_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov LONG ptr [_1],LONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UIntPtrToLongPtr proto __fastcall :UINT_PTR, :ptr LONG_PTR {

    .ifs (this <= LONG_PTR_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov LONG_PTR ptr [_1],LONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
UIntPtrToULong equ <ULongLongToULong>
else
UIntPtrToULong proto __fastcall :UINT_PTR, :ptr ULONG {
    mov [_1],this
    mov eax,S_OK
    }
endif
UIntPtrToDWord equ <UIntPtrToULong>

ifdef _WIN64
UIntPtrToLongLong equ <ULongLongToLongLong>
else
UIntPtrToLongLong proto __fastcall :UINT_PTR, :ptr LONGLONG {
    mov [_1],this
    mov eax,S_OK
    }
endif

UIntPtrToLong64   equ <UIntPtrToLongLong>
UIntPtrToInt64    equ <UIntPtrToLongLong>
UIntPtrToPtrdiffT equ <UIntPtrToIntPtr>
UIntPtrToSSIZET   equ <UIntPtrToLongPtr>

LongToInt8 proto __fastcall :LONG, :ptr INT8 {

    .ifs (this >= INT8_MIN && this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongToUChar proto __fastcall :LONG, :ptr UCHAR {

    .ifs (this >= 0 && this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongToChar proto __fastcall :LONG, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    LongToUChar(this, _1)
else
    LongToInt8(this, _1)
endif
    }

LongToUInt8 proto __fastcall :LONG, :ptr UINT8 {

    .ifs (this >= 0 && this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongToByte equ <LongToUInt8>

LongToShort proto __fastcall :LONG, :ptr SSHORT {

    .ifs (this >= SSHORT_MIN && this <= SSHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SSHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongToInt16 equ <LongToShort>

LongToUShort proto __fastcall :LONG, :ptr USHORT {

    .ifs (this >= 0 && this <= USHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongToUInt16 equ <LongToUShort>
LongToWord   equ <LongToUShort>

LongToInt proto __fastcall :LONG, :ptr SINT {

    C_ASSERT(sizeof(SINT) eq sizeof(LONG))
    mov [_1],this
    mov eax,S_OK
    }

LongToInt32 equ <LongToInt>

ifdef _WIN64
LongToIntPtr proto __fastcall :LONG, :ptr INT_PTR {
    mov [_1],this
    mov eax,S_OK
    }
else
LongToIntPtr equ <LongToInt>
endif

LongToUInt proto __fastcall :LONG, :ptr UINT {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov UINT ptr [_1],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongToUInt32 equ <LongToUInt>

ifdef _WIN64
LongToUIntPtr proto __fastcall :LONG, :ptr UINT_PTR {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov UINT_PTR ptr [_1],UINT_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
else
LongToUIntPtr equ <LongToUInt>
endif

LongToULong proto __fastcall :LONG, :ptr ULONG {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONG ptr [_1],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
LongToULongPtr proto __fastcall :LONG, :ptr ULONG_PTR {

    .ifs (this >= 0)
        mov [_1],__qwordreg
        mov eax,S_OK
    .else
        mov ULONG_PTR ptr [_1],ULONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
else
LongToULongPtr equ <LongToULong>
endif

LongToDWord    equ <LongToULong>
LongToDWordPtr equ <LongToULongPtr>

LongToULongLong proto __fastcall :LONG, :ptr ULONGLONG {

    .ifs (this >= 0)
ifdef _WIN64
        mov [_1],__qwordreg
else
        mov [_1],this
endif
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_1],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongToDWordLong         equ <LongToULongLong>
LongToULong64           equ <LongToULongLong>
LongToDWord64           equ <LongToULongLong>
LongToUInt64            equ <LongToULongLong>
LongToPtrdiffT          equ <LongToIntPtr>
LongToSizeT             equ <LongToUIntPtr>
LongToSIZET             equ <LongToULongPtr>

LongPtrToInt8 proto __fastcall :LONG_PTR, :ptr INT8 {

    .ifs (this >= INT8_MIN && this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongPtrToUChar proto __fastcall :LONG_PTR, :ptr UCHAR {

    .ifs (this >= 0 && this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongPtrToChar proto __fastcall :LONG_PTR, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    LongPtrToUChar(this, _1)
else
    LongPtrToInt8(this, _1)
endif
    }

LongPtrToUInt8 proto __fastcall :LONG_PTR, :ptr UINT8 {

    .ifs (this >= 0 && this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongPtrToByte equ <LongPtrToUInt8>

LongPtrToShort proto __fastcall :LONG_PTR, :ptr SSHORT {

    .ifs (this >= SHORT_MIN && this <= SHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongPtrToInt16 equ <LongPtrToShort>

LongPtrToUShort proto __fastcall :LONG_PTR, :ptr USHORT {

    .ifs (this >= 0 && this <= USHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongPtrToUInt16 equ <LongPtrToUShort>
LongPtrToWord   equ <LongPtrToUShort>
ifdef _WIN64
LongPtrToInt    equ <LongLongToInt>
else
LongPtrToInt proto __fastcall :LONG_PTR, :ptr SINT {

    C_ASSERT(sizeof(SINT) eq sizeof(LONG_PTR))
    mov [_1],__dwordreg
    mov eax,S_OK
    }
endif

LongPtrToInt32 equ <LongPtrToInt>

LongPtrToIntPtr proto __fastcall :LONG_PTR, :ptr INT_PTR {

    C_ASSERT(sizeof(LONG_PTR) eq sizeof(INT_PTR))
    mov [_1],this
    mov eax,S_OK
    }

ifdef _WIN64
LongPtrToUInt equ <LongLongToUInt>
else
LongPtrToUInt proto __fastcall :LONG_PTR, :ptr UINT {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov UINT ptr [_1],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

LongPtrToUInt32 equ <LongPtrToUInt>

LongPtrToUIntPtr proto __fastcall :LONG_PTR, :ptr UINT_PTR {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov UINT_PTR ptr [_1],UINT_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
LongPtrToLong equ <LongLongToLong>
else
LongPtrToLong proto __fastcall :LONG_PTR, :ptr LONG {
    mov [_1],this
    mov eax,S_OK
    }
endif

ifdef _WIN64
LongPtrToULong equ <LongLongToULong>
else
LongPtrToULong proto __fastcall :LONG_PTR, :ptr ULONG {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONG ptr [_1],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

LongPtrToULongPtr proto __fastcall :LONG_PTR, :ptr ULONG_PTR {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONG_PTR ptr [_1],ULONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongPtrToDWord    equ <LongPtrToULong
LongPtrToDWordPtr equ <LongPtrToULongPtr

LongPtrToULongLong proto __fastcall :LONG_PTR, :ptr ULONGLONG {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_1],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongPtrToDWordLong      equ <LongPtrToULongLong>
LongPtrToULong64        equ <LongPtrToULongLong>
LongPtrToDWord64        equ <LongPtrToULongLong>
LongPtrToUInt64         equ <LongPtrToULongLong>
LongPtrToSizeT          equ <LongPtrToUIntPtr>
LongPtrToSIZET          equ <LongPtrToULongPtr>

ULongToInt8 proto __fastcall :ULONG, :ptr INT8 {

    .ifs (this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongToUChar proto __fastcall :ULONG, :ptr UCHAR {

    .ifs (this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongToChar proto __fastcall :ULONG, :ptr {
ifdef _CHAR_UNSIGNED
    ULongToUChar(this, _1)
else
    ULongToInt8(this, _1)
endif
    }

ULongToUInt8 proto __fastcall :ULONG, :ptr UINT8 {

    .ifs (this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongToByte equ <ULongToUInt8>

ULongToShort proto __fastcall :ULONG, :ptr SSHORT {

    .ifs (this <= SHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongToInt16 equ <ULongToShort>

ULongToUShort proto __fastcall :ULONG, :ptr USHORT {

    .ifs (this <= USHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongToUInt16 equ <ULongToUShort>
ULongToWord   equ <ULongToUShort>

ULongToInt proto __fastcall :ULONG, :ptr SINT {

    .ifs (this <= INT_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov SINT ptr [_1],INT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongToInt32 equ <ULongToInt>

ifdef _WIN64
ULongToIntPtr proto __fastcall :ULONG, :ptr INT_PTR {
    mov [_1],__qwordreg
    mov eax,S_OK
    }
else
ULongToIntPtr equ <ULongToInt>
endif

ULongToUInt proto __fastcall :ULONG, :ptr UINT {

    C_ASSERT(sizeof(ULONG) eq sizeof(UINT))
    mov [_1],this
    mov eax,S_OK
    }

ULongToUInt32 equ <ULongToUInt>

ifdef _WIN64
ULongToUIntPtr proto __fastcall :ULONG, :ptr UINT_PTR {
    C_ASSERT(sizeof(UINT_PTR) gt sizeof(ULONG))
    mov [_1],__qwordreg
    mov eax,S_OK
    }
else
ULongToUIntPtr equ <ULongToUInt>
endif

ULongToLong proto __fastcall :ULONG, :ptr LONG {

    .ifs (this <= LONG_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov LONG ptr [_1],LONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
ULongToLongPtr proto __fastcall :ULONG, :ptr LONG_PTR {
    C_ASSERT(sizeof(LONG_PTR) gt sizeof(ULONG))
    mov [_1],__qwordreg
    mov eax,S_OK
    }
else
ULongToLongPtr equ <ULongToLong>
endif

ULongToPtrdiffT equ <ULongToIntPtr>
ULongToSSIZET   equ <ULongToLongPtr>

ULongPtrToInt8 proto __fastcall :ULONG_PTR, :ptr INT8 {

    .ifs (this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongPtrToUChar proto __fastcall :ULONG_PTR, :ptr UCHAR {

    .ifs (this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongPtrToChar proto __fastcall :ULONG_PTR, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    ULongPtrToUChar(this, _1)
else
    ULongPtrToInt8(this, _1)
endif
    }

ULongPtrToUInt8 proto __fastcall :ULONG_PTR, :ptr UINT8 {

    .ifs (this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongPtrToByte equ <ULongPtrToUInt8>

ULongPtrToShort proto __fastcall :ULONG_PTR, :ptr SSHORT {

    .ifs (this <= SHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongPtrToInt16 equ <ULongPtrToShort>

ULongPtrToUShort proto __fastcall :ULONG_PTR, :ptr USHORT {

    .ifs (this <= USHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongPtrToUInt16 equ <ULongPtrToUShort>
ULongPtrToWord   equ <ULongPtrToUShort>

ULongPtrToInt proto __fastcall :ULONG_PTR, :ptr SINT {

    .ifs (this <= INT_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov SINT ptr [_1],INT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongPtrToInt32 equ <ULongPtrToInt>

ULongPtrToIntPtr proto __fastcall :ULONG_PTR, :ptr INT_PTR {

    .ifs (this <= INT_PTR_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov INT_PTR ptr [_1],INT_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
ULongPtrToUInt equ <ULongLongToUInt>
else
ULongPtrToUInt proto __fastcall :ULONG_PTR, :ptr UINT {
    C_ASSERT(sizeof(ULONG_PTR) eq sizeof(UINT))
    mov [_1],this
    mov eax,S_OK
    }
endif

ULongPtrToUInt32 equ <ULongPtrToUInt>

ULongPtrToUIntPtr proto __fastcall :ULONG_PTR, :ptr UINT_PTR {
    mov [_1],this
    mov eax,S_OK
    }

ULongPtrToLong proto __fastcall :ULONG_PTR, :ptr LONG {

    .ifs (this <= LONG_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov LONG ptr [_1],LONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongPtrToLongPtr proto __fastcall :ULONG_PTR, :ptr LONG_PTR {

    .ifs (this <= LONG_PTR_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov LONG_PTR ptr [_1],LONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
ULongPtrToULong equ <ULongLongToULong>
else
ULongPtrToULong proto __fastcall :ULONG_PTR, :ptr ULONG {
    mov [_1],this
    mov eax,S_OK
    }
endif

ULongPtrToDWord equ <ULongPtrToULong>

ifdef _WIN64
ULongPtrToLongLong equ <ULongLongToLongLong>
else
ULongPtrToLongLong proto __fastcall :ULONG_PTR, :ptr LONGLONG {
    mov [_1],this
    mov eax,S_OK
    }
endif

ULongPtrToLong64        equ <ULongPtrToLongLong>
ULongPtrToInt64         equ <ULongPtrToLongLong>
ULongPtrToPtrdiffT      equ <ULongPtrToIntPtr>
ULongPtrToSSIZET        equ <ULongPtrToLongPtr>
DWordToInt8             equ <ULongToInt8>
DWordToChar             equ <ULongToChar>
DWordToUChar            equ <ULongToUChar>
DWordToUInt8            equ <ULongToUInt8>
DWordToByte             equ <ULongToUInt8>
DWordToShort            equ <ULongToShort>
DWordToInt16            equ <ULongToShort>
DWordToUShort           equ <ULongToUShort>
DWordToUInt16           equ <ULongToUShort>
DWordToWord             equ <ULongToUShort>
DWordToInt              equ <ULongToInt>
DWordToInt32            equ <ULongToInt>
DWordToIntPtr           equ <ULongToIntPtr>
DWordToUInt             equ <ULongToUInt>
DWordToUInt32           equ <ULongToUInt>
DWordToUIntPtr          equ <ULongToUIntPtr>
DWordToLong             equ <ULongToLong>
DWordToLongPtr          equ <ULongToLongPtr>
DWordToPtrdiffT         equ <ULongToIntPtr>
DWordToSSIZET           equ <ULongToLongPtr>
DWordPtrToInt8          equ <ULongPtrToInt8>
DWordPtrToUChar         equ <ULongPtrToUChar>
DWordPtrToChar          equ <ULongPtrToChar>
DWordPtrToUInt8         equ <ULongPtrToUInt8>
DWordPtrToByte          equ <ULongPtrToUInt8>
DWordPtrToShort         equ <ULongPtrToShort>
DWordPtrToInt16         equ <ULongPtrToShort>
DWordPtrToUShort        equ <ULongPtrToUShort>
DWordPtrToUInt16        equ <ULongPtrToUShort>
DWordPtrToWord          equ <ULongPtrToUShort>
DWordPtrToInt           equ <ULongPtrToInt>
DWordPtrToInt32         equ <ULongPtrToInt>
DWordPtrToIntPtr        equ <ULongPtrToIntPtr>
DWordPtrToUInt          equ <ULongPtrToUInt>
DWordPtrToUInt32        equ <ULongPtrToUInt>
DWordPtrToUIntPtr       equ <ULongPtrToUIntPtr>
DWordPtrToLong          equ <ULongPtrToLong>
DWordPtrToLongPtr       equ <ULongPtrToLongPtr>
DWordPtrToULong         equ <ULongPtrToULong>
DWordPtrToDWord         equ <ULongPtrToULong>
DWordPtrToLongLong      equ <ULongPtrToLongLong>
DWordPtrToLong64        equ <ULongPtrToLongLong>
DWordPtrToInt64         equ <ULongPtrToLongLong>
DWordPtrToPtrdiffT      equ <ULongPtrToIntPtr>
DWordPtrToSSIZET        equ <ULongPtrToLongPtr>

LongLongToInt8 proto __fastcall :LONGLONG, :ptr INT8 {

    .ifs (this >= INT8_MIN && this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongLongToUChar proto __fastcall :LONGLONG, :ptr UCHAR {

    .ifs (this >= 0 && this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongLongToChar proto __fastcall :LONGLONG, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    LongLongToUChar(this, _1)
else
    LongLongToInt8(this, _1)
endif
    }

LongLongToUInt8 proto __fastcall :LONGLONG, :ptr UINT8 {

    .ifs (this >= 0 && this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongLongToByte equ <LongLongToUInt8>

LongLongToShort proto __fastcall :LONGLONG, :ptr SSHORT {

    .ifs (this >= SHORT_MIN && this <= SHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongLongToInt16 equ <LongLongToShort>

LongLongToUShort proto __fastcall :LONGLONG, :ptr USHORT {

    .ifs (this >= 0 && this <= USHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongLongToUInt16 equ <LongLongToUShort>
LongLongToWord   equ <LongLongToUShort>

LongLongToInt proto __fastcall :LONGLONG, :ptr SINT {

    .ifs (this >= INT_MIN && this <= INT_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov SINT ptr [_1],INT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongLongToInt32 equ <LongLongToInt>

ifdef _WIN64
LongLongToIntPtr proto __fastcall :LONGLONG, :ptr INT_PTR {
    mov [_1],this
    mov eax,S_OK
    }
else
LongLongToIntPtr equ <LongLongToInt>
endif

LongLongToUInt proto __fastcall :LONGLONG, :ptr UINT {

    .ifs (this >= 0 && this <= UINT_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov UINT ptr [_1],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongLongToUInt32  equ <LongLongToUInt>
ifdef _WIN64
LongLongToUIntPtr equ <LongLongToULongLong>
else
LongLongToUIntPtr equ <LongLongToUInt>
endif

LongLongToLong proto __fastcall :LONGLONG, :ptr LONG {

    .ifs (this >= LONG_MIN && this <= LONG_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov LONG ptr [_1],LONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
LongLongToLongPtr proto __fastcall :LONGLONG, :ptr LONG_PTR {
    mov [_1],this
    mov eax,S_OK
    }
else
LongLongToLongPtr equ <LongLongToLong>
endif

LongLongToULong proto __fastcall :LONGLONG, :ptr ULONG {

    .ifs (this >= 0 && this <= ULONG_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov ULONG ptr [_1],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
LongLongToULongPtr equ <LongLongToULongLong>
else
LongLongToULongPtr equ <LongLongToULong>
endif

LongLongToDWord    equ <LongLongToULong>
LongLongToDWordPtr equ <LongLongToULongPtr>

LongLongToULongLong proto __fastcall :LONGLONG, :ptr ULONGLONG {

    .ifs (this >= 0)
        mov [_1],this
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_1],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

LongLongToDWordLong     equ <LongLongToULongLong>
LongLongToULong64       equ <LongLongToULongLong>
LongLongToDWord64       equ <LongLongToULongLong>
LongLongToUInt64        equ <LongLongToULongLong>
LongLongToPtrdiffT      equ <LongLongToIntPtr>
LongLongToSizeT         equ <LongLongToUIntPtr>
LongLongToSSIZET        equ <LongLongToLongPtr>
LongLongToSIZET         equ <LongLongToULongPtr>
Long64ToChar            equ <LongLongToChar>
Long64ToInt8            equ <LongLongToInt8>
Long64ToUChar           equ <LongLongToUChar>
Long64ToUInt8           equ <LongLongToUInt8>
Long64ToByte            equ <LongLongToUInt8>
Long64ToShort           equ <LongLongToShort>
Long64ToInt16           equ <LongLongToShort>
Long64ToUShort          equ <LongLongToUShort>
Long64ToUInt16          equ <LongLongToUShort>
Long64ToWord            equ <LongLongToUShort>
Long64ToInt             equ <LongLongToInt>
Long64ToInt32           equ <LongLongToInt>
Long64ToIntPtr          equ <LongLongToIntPtr>
Long64ToUInt            equ <LongLongToUInt>
Long64ToUInt32          equ <LongLongToUInt>
Long64ToUIntPtr         equ <LongLongToUIntPtr>
Long64ToLong            equ <LongLongToLong>
Long64ToLongPtr         equ <LongLongToLongPtr>
Long64ToULong           equ <LongLongToULong>
Long64ToULongPtr        equ <LongLongToULongPtr>
Long64ToDWord           equ <LongLongToULong>
Long64ToDWordPtr        equ <LongLongToULongPtr>
Long64ToULongLong       equ <LongLongToULongLong>
Long64ToPtrdiffT        equ <LongLongToIntPtr>
Long64ToSizeT           equ <LongLongToUIntPtr>
Long64ToSSIZET          equ <LongLongToLongPtr>
Long64ToSIZET           equ <LongLongToULongPtr>
Int64ToChar             equ <LongLongToChar>
Int64ToInt8             equ <LongLongToInt8>
Int64ToUChar            equ <LongLongToUChar>
Int64ToUInt8            equ <LongLongToUInt8>
Int64ToByte             equ <LongLongToUInt8>
Int64ToShort            equ <LongLongToShort>
Int64ToInt16            equ <LongLongToShort>
Int64ToUShort           equ <LongLongToUShort>
Int64ToUInt16           equ <LongLongToUShort>
Int64ToWord             equ <LongLongToUShort>
Int64ToInt              equ <LongLongToInt>
Int64ToInt32            equ <LongLongToInt>
Int64ToIntPtr           equ <LongLongToIntPtr>
Int64ToUInt             equ <LongLongToUInt>
Int64ToUInt32           equ <LongLongToUInt>
Int64ToUIntPtr          equ <LongLongToUIntPtr>
Int64ToLong             equ <LongLongToLong>
Int64ToLongPtr          equ <LongLongToLongPtr>
Int64ToULong            equ <LongLongToULong>
Int64ToULongPtr         equ <LongLongToULongPtr>
Int64ToDWord            equ <LongLongToULong>
Int64ToDWordPtr         equ <LongLongToULongPtr>
Int64ToULongLong        equ <LongLongToULongLong>
Int64ToDWordLong        equ <LongLongToULongLong>
Int64ToULong64          equ <LongLongToULongLong>
Int64ToDWord64          equ <LongLongToULongLong>
Int64ToUInt64           equ <LongLongToULongLong>
Int64ToPtrdiffT         equ <LongLongToIntPtr>
Int64ToSizeT            equ <LongLongToUIntPtr>
Int64ToSSIZET           equ <LongLongToLongPtr>
Int64ToSIZET            equ <LongLongToULongPtr>

ULongLongToInt8 proto __fastcall :ULONGLONG, :ptr INT8 {

    .ifs (this <= INT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov INT8 ptr [_1],INT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToUChar proto __fastcall :ULONGLONG, :ptr UCHAR {

    .ifs (this <= 255)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UCHAR ptr [_1],0
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToChar proto __fastcall :ULONGLONG, :ptr CHAR {
ifdef _CHAR_UNSIGNED
    ULongLongToUChar(this, _1)
else
    ULongLongToInt8(this, _1)
endif
    }

ULongLongToUInt8 proto __fastcall :ULONGLONG, :ptr UINT8 {

    .ifs (this <= UINT8_MAX)
        mov [_1],__bytereg
        mov eax,S_OK
    .else
        mov UINT8 ptr [_1],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToByte equ <ULongLongToUInt8>

ULongLongToShort proto __fastcall :ULONGLONG, :ptr SSHORT {

    .ifs (this <= SHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov SSHORT ptr [_1],SHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToInt16 equ <ULongLongToShort>

ULongLongToUShort proto __fastcall :ULONGLONG, :ptr USHORT {

    .ifs (this <= USHORT_MAX)
        mov [_1],__wordreg
        mov eax,S_OK
    .else
        mov USHORT ptr [_1],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToUInt16 equ <ULongLongToUShort>
ULongLongToWord   equ <ULongLongToUShort>

ULongLongToInt proto __fastcall :ULONGLONG, :ptr SINT {

    .ifs (this <= INT_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov SINT ptr [_1],INT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToInt32  equ <ULongLongToInt>
ifdef _WIN64
ULongLongToIntPtr equ <ULongLongToLongLong>
else
ULongLongToIntPtr equ <ULongLongToInt>
endif

ULongLongToUInt proto __fastcall :ULONGLONG, :ptr UINT {

    .if (this <= UINT_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov UINT ptr [_1],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToUInt32 equ <ULongLongToUInt>

ifdef _WIN64
ULongLongToUIntPtr proto __fastcall :ULONGLONG, :ptr UINT_PTR {
    mov [_1],this
    mov eax,S_OK
    }
else
ULongLongToUIntPtr equ <ULongLongToUInt>
endif

ULongLongToLong proto __fastcall :ULONGLONG, :ptr LONG {

    .ifs (this <= LONG_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov LONG ptr [_1],LONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToLongPtr proto __fastcall :ULONGLONG, :ptr LONG_PTR {

    .ifs (this <= LONG_PTR_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov LONG_PTR ptr [_1],LONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToULong proto __fastcall :ULONGLONG, :ptr ULONG {

    .ifs (this <= ULONG_MAX)
        mov [_1],__dwordreg
        mov eax,S_OK
    .else
        mov ULONG ptr [_1],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
ULongLongToULongPtr proto __fastcall :ULONGLONG, :ptr ULONG_PTR {
    mov [_1],this
    mov eax,S_OK
    }
else
ULongLongToULongPtr equ <ULongLongToULong>
endif
ULongLongToDWord    equ <ULongLongToULong>
ULongLongToDWordPtr equ <ULongLongToULongPtr>

ULongLongToLongLong proto __fastcall :ULONGLONG, :ptr LONGLONG {

    .ifs (this <= LONGLONG_MAX)
        mov [_1],this
        mov eax,S_OK
    .else
        mov LONGLONG ptr [_1],LONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ULongLongToInt64        equ <ULongLongToLongLong>
ULongLongToLong64       equ <ULongLongToLongLong>
ULongLongToPtrdiffT     equ <ULongLongToIntPtr>
ULongLongToSizeT        equ <ULongLongToUIntPtr>
ULongLongToSSIZET       equ <ULongLongToLongPtr>
ULongLongToSIZET        equ <ULongLongToULongPtr>
DWordLongToChar         equ <ULongLongToChar>
DWordLongToInt8         equ <ULongLongToInt8>
DWordLongToUChar        equ <ULongLongToUChar>
DWordLongToUInt8        equ <ULongLongToUInt8>
DWordLongToByte         equ <ULongLongToUInt8>
DWordLongToShort        equ <ULongLongToShort>
DWordLongToInt16        equ <ULongLongToShort>
DWordLongToUShort       equ <ULongLongToUShort>
DWordLongToUInt16       equ <ULongLongToUShort>
DWordLongToWord         equ <ULongLongToUShort>
DWordLongToInt          equ <ULongLongToInt>
DWordLongToInt32        equ <ULongLongToInt>
DWordLongToIntPtr       equ <ULongLongToIntPtr>
DWordLongToUInt         equ <ULongLongToUInt>
DWordLongToUInt32       equ <ULongLongToUInt>
DWordLongToUIntPtr      equ <ULongLongToUIntPtr>
DWordLongToLong         equ <ULongLongToLong>
DWordLongToLongPtr      equ <ULongLongToLongPtr>
DWordLongToULong        equ <ULongLongToULong>
DWordLongToULongPtr     equ <ULongLongToULongPtr>
DWordLongToDWord        equ <ULongLongToULong>
DWordLongToDWordPtr     equ <ULongLongToULongPtr>
DWordLongToLongLong     equ <ULongLongToLongLong>
DWordLongToLong64       equ <ULongLongToLongLong>
DWordLongToInt64        equ <ULongLongToLongLong>
DWordLongToPtrdiffT     equ <ULongLongToIntPtr>
DWordLongToSizeT        equ <ULongLongToUIntPtr>
DWordLongToSSIZET       equ <ULongLongToLongPtr>
DWordLongToSIZET        equ <ULongLongToULongPtr>
ULong64ToChar           equ <ULongLongToChar>
ULong64ToInt8           equ <ULongLongToInt8>
ULong64ToUChar          equ <ULongLongToUChar>
ULong64ToUInt8          equ <ULongLongToUInt8>
ULong64ToByte           equ <ULongLongToUInt8>
ULong64ToShort          equ <ULongLongToShort>
ULong64ToInt16          equ <ULongLongToShort>
ULong64ToUShort         equ <ULongLongToUShort>
ULong64ToUInt16         equ <ULongLongToUShort>
ULong64ToWord           equ <ULongLongToUShort>
ULong64ToInt            equ <ULongLongToInt>
ULong64ToInt32          equ <ULongLongToInt>
ULong64ToIntPtr         equ <ULongLongToIntPtr>
ULong64ToUInt           equ <ULongLongToUInt>
ULong64ToUInt32         equ <ULongLongToUInt>
ULong64ToUIntPtr        equ <ULongLongToUIntPtr>
ULong64ToLong           equ <ULongLongToLong>
ULong64ToLongPtr        equ <ULongLongToLongPtr>
ULong64ToULong          equ <ULongLongToULong>
ULong64ToULongPtr       equ <ULongLongToULongPtr>
ULong64ToDWord          equ <ULongLongToULong>
ULong64ToDWordPtr       equ <ULongLongToULongPtr>
ULong64ToLongLong       equ <ULongLongToLongLong>
ULong64ToLong64         equ <ULongLongToLongLong>
ULong64ToInt64          equ <ULongLongToLongLong>
ULong64ToPtrdiffT       equ <ULongLongToIntPtr>
ULong64ToSizeT          equ <ULongLongToUIntPtr>
ULong64ToSSIZET         equ <ULongLongToLongPtr>
ULong64ToSIZET          equ <ULongLongToULongPtr>
DWord64ToChar           equ <ULongLongToChar>
DWord64ToInt8           equ <ULongLongToInt8>
DWord64ToUChar          equ <ULongLongToUChar>
DWord64ToUInt8          equ <ULongLongToUInt8>
DWord64ToByte           equ <ULongLongToUInt8>
DWord64ToShort          equ <ULongLongToShort>
DWord64ToInt16          equ <ULongLongToShort>
DWord64ToUShort         equ <ULongLongToUShort>
DWord64ToUInt16         equ <ULongLongToUShort>
DWord64ToWord           equ <ULongLongToUShort>
DWord64ToInt            equ <ULongLongToInt>
DWord64ToInt32          equ <ULongLongToInt>
DWord64ToIntPtr         equ <ULongLongToIntPtr>
DWord64ToUInt           equ <ULongLongToUInt>
DWord64ToUInt32         equ <ULongLongToUInt>
DWord64ToUIntPtr        equ <ULongLongToUIntPtr>
DWord64ToLong           equ <ULongLongToLong>
DWord64ToLongPtr        equ <ULongLongToLongPtr>
DWord64ToULong          equ <ULongLongToULong>
DWord64ToULongPtr       equ <ULongLongToULongPtr>
DWord64ToDWord          equ <ULongLongToULong>
DWord64ToDWordPtr       equ <ULongLongToULongPtr>
DWord64ToLongLong       equ <ULongLongToLongLong>
DWord64ToLong64         equ <ULongLongToLongLong>
DWord64ToInt64          equ <ULongLongToLongLong>
DWord64ToPtrdiffT       equ <ULongLongToIntPtr>
DWord64ToSizeT          equ <ULongLongToUIntPtr>
DWord64ToSSIZET         equ <ULongLongToLongPtr>
DWord64ToSIZET          equ <ULongLongToULongPtr>
UInt64ToChar            equ <ULongLongToChar>
UInt64ToInt8            equ <ULongLongToInt8>
UInt64ToUChar           equ <ULongLongToUChar>
UInt64ToUInt8           equ <ULongLongToUInt8>
UInt64ToByte            equ <ULongLongToUInt8>
UInt64ToShort           equ <ULongLongToShort>
UInt64ToInt16           equ <ULongLongToShort>
UInt64ToUShort          equ <ULongLongToUShort>
UInt64ToUInt16          equ <ULongLongToUShort>
UInt64ToWord            equ <ULongLongToUShort>
UInt64ToInt             equ <ULongLongToInt>
UInt64ToInt32           equ <ULongLongToInt>
UInt64ToIntPtr          equ <ULongLongToIntPtr>
UInt64ToUInt            equ <ULongLongToUInt>
UInt64ToUInt32          equ <ULongLongToUInt>
UInt64ToUIntPtr         equ <ULongLongToUIntPtr>
UInt64ToLong            equ <ULongLongToLong>
UInt64ToLongPtr         equ <ULongLongToLongPtr>
UInt64ToULong           equ <ULongLongToULong>
UInt64ToULongPtr        equ <ULongLongToULongPtr>
UInt64ToDWord           equ <ULongLongToULong>
UInt64ToDWordPtr        equ <ULongLongToULongPtr>
UInt64ToLongLong        equ <ULongLongToLongLong>
UInt64ToLong64          equ <ULongLongToLongLong>
UInt64ToInt64           equ <ULongLongToLongLong>
UInt64ToPtrdiffT        equ <ULongLongToIntPtr>
UInt64ToSizeT           equ <ULongLongToUIntPtr>
UInt64ToSSIZET          equ <ULongLongToLongPtr>
UInt64ToSIZET           equ <ULongLongToULongPtr>
PtrdiffTToChar          equ <IntPtrToChar>
PtrdiffTToInt8          equ <IntPtrToInt8>
PtrdiffTToUChar         equ <IntPtrToUChar>
PtrdiffTToUInt8         equ <IntPtrToUInt8>
PtrdiffTToByte          equ <IntPtrToUInt8>
PtrdiffTToShort         equ <IntPtrToShort>
PtrdiffTToInt16         equ <IntPtrToShort>
PtrdiffTToUShort        equ <IntPtrToUShort>
PtrdiffTToUInt16        equ <IntPtrToUShort>
PtrdiffTToWord          equ <IntPtrToUShort>
PtrdiffTToInt           equ <IntPtrToInt>
PtrdiffTToInt32         equ <IntPtrToInt>
PtrdiffTToUInt          equ <IntPtrToUInt>
PtrdiffTToUInt32        equ <IntPtrToUInt>
PtrdiffTToUIntPtr       equ <IntPtrToUIntPtr>
PtrdiffTToLong          equ <IntPtrToLong>
PtrdiffTToLongPtr       equ <IntPtrToLongPtr>
PtrdiffTToULong         equ <IntPtrToULong>
PtrdiffTToULongPtr      equ <IntPtrToULongPtr>
PtrdiffTToDWord         equ <IntPtrToULong>
PtrdiffTToDWordPtr      equ <IntPtrToULongPtr>
PtrdiffTToULongLong     equ <IntPtrToULongLong>
PtrdiffTToDWordLong     equ <IntPtrToULongLong>
PtrdiffTToULong64       equ <IntPtrToULongLong>
PtrdiffTToDWord64       equ <IntPtrToULongLong>
PtrdiffTToUInt64        equ <IntPtrToULongLong>
PtrdiffTToSizeT         equ <IntPtrToUIntPtr>
PtrdiffTToSIZET         equ <IntPtrToULongPtr>
SizeTToInt8             equ <UIntPtrToInt8>
SizeTToUChar            equ <UIntPtrToUChar>
SizeTToChar             equ <UIntPtrToChar>
SizeTToUInt8            equ <UIntPtrToUInt8>
SizeTToByte             equ <UIntPtrToUInt8>
SizeTToShort            equ <UIntPtrToShort>
SizeTToInt16            equ <UIntPtrToShort>
SizeTToUShort           equ <UIntPtrToUShort>
SizeTToUInt16           equ <UIntPtrToUShort>
SizeTToWord             equ <UIntPtrToUShort>
SizeTToInt              equ <UIntPtrToInt>
SizeTToInt32            equ <UIntPtrToInt>
SizeTToIntPtr           equ <UIntPtrToIntPtr>
SizeTToUInt             equ <UIntPtrToUInt>
SizeTToUInt32           equ <UIntPtrToUInt>
SizeTToLong             equ <UIntPtrToLong>
SizeTToLongPtr          equ <UIntPtrToLongPtr>
SizeTToULong            equ <UIntPtrToULong>
SizeTToDWord            equ <UIntPtrToULong>
SizeTToLongLong         equ <UIntPtrToLongLong>
SizeTToLong64           equ <UIntPtrToLongLong>
SizeTToInt64            equ <UIntPtrToLongLong>
SizeTToPtrdiffT         equ <UIntPtrToIntPtr>
SizeTToSSIZET           equ <UIntPtrToLongPtr>
SSIZETToInt8            equ <LongPtrToInt8>
SSIZETToUChar           equ <LongPtrToUChar>
SSIZETToChar            equ <LongPtrToChar>
SSIZETToUInt8           equ <LongPtrToUInt8>
SSIZETToByte            equ <LongPtrToUInt8>
SSIZETToShort           equ <LongPtrToShort>
SSIZETToInt16           equ <LongPtrToShort>
SSIZETToUShort          equ <LongPtrToUShort>
SSIZETToUInt16          equ <LongPtrToUShort>
SSIZETToWord            equ <LongPtrToUShort>
SSIZETToInt             equ <LongPtrToInt>
SSIZETToInt32           equ <LongPtrToInt>
SSIZETToIntPtr          equ <LongPtrToIntPtr>
SSIZETToUInt            equ <LongPtrToUInt>
SSIZETToUInt32          equ <LongPtrToUInt>
SSIZETToUIntPtr         equ <LongPtrToUIntPtr>
SSIZETToLong            equ <LongPtrToLong>
SSIZETToULong           equ <LongPtrToULong>
SSIZETToULongPtr        equ <LongPtrToULongPtr>
SSIZETToDWord           equ <LongPtrToULong>
SSIZETToDWordPtr        equ <LongPtrToULongPtr>
SSIZETToULongLong       equ <LongPtrToULongLong>
SSIZETToDWordLong       equ <LongPtrToULongLong>
SSIZETToULong64         equ <LongPtrToULongLong>
SSIZETToDWord64         equ <LongPtrToULongLong>
SSIZETToUInt64          equ <LongPtrToULongLong>
SSIZETToSizeT           equ <LongPtrToUIntPtr>
SSIZETToSIZET           equ <LongPtrToULongPtr>
SIZETToInt8             equ <ULongPtrToInt8>
SIZETToUChar            equ <ULongPtrToUChar>
SIZETToChar             equ <ULongPtrToChar>
SIZETToUInt8            equ <ULongPtrToUInt8>
SIZETToByte             equ <ULongPtrToUInt8>
SIZETToShort            equ <ULongPtrToShort>
SIZETToInt16            equ <ULongPtrToShort>
SIZETToUShort           equ <ULongPtrToUShort>
SIZETToUInt16           equ <ULongPtrToUShort>
SIZETToWord             equ <ULongPtrToUShort>
SIZETToInt              equ <ULongPtrToInt>
SIZETToInt32            equ <ULongPtrToInt>
SIZETToIntPtr           equ <ULongPtrToIntPtr>
SIZETToUInt             equ <ULongPtrToUInt>
SIZETToUInt32           equ <ULongPtrToUInt>
SIZETToUIntPtr          equ <ULongPtrToUIntPtr>
SIZETToLong             equ <ULongPtrToLong>
SIZETToLongPtr          equ <ULongPtrToLongPtr>
SIZETToULong            equ <ULongPtrToULong>
SIZETToDWord            equ <ULongPtrToULong>
SIZETToLongLong         equ <ULongPtrToLongLong>
SIZETToLong64           equ <ULongPtrToLongLong>
SIZETToInt64            equ <ULongPtrToLongLong>
SIZETToPtrdiffT         equ <ULongPtrToIntPtr>
SIZETToSSIZET           equ <ULongPtrToLongPtr>


;;=============================================================================
;; Addition functions
;;=============================================================================

UInt8Add proto __fastcall :UINT8, :UINT8, :ptr UINT8 {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov UINT8 ptr [_2],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UShortAdd proto __fastcall :USHORT, :USHORT, :ptr USHORT {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov USHORT ptr [_2],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UInt16Add equ <UShortAdd>
WordAdd   equ <UShortAdd>

UIntAdd proto __fastcall :UINT, :UINT, :ptr UINT {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov UINT ptr [_2],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UInt32Add  equ <UIntAdd>
ifdef _WIN64
UIntPtrAdd equ <ULongLongAdd>
else
UIntPtrAdd proto __fastcall :UINT_PTR, :UINT_PTR, :ptr UINT_PTR {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov UINT_PTR ptr [_2],UINT_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

ULongAdd proto __fastcall :ULONG, :ULONG, :ptr ULONG {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov ULONG ptr [_2],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
ULongPtrAdd equ <ULongLongAdd>
else
ULongPtrAdd proto __fastcall :ULONG_PTR, :ULONG_PTR, :ptr ULONG_PTR {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov ULONG_PTR ptr [_2],ULONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

DWordAdd    equ <ULongAdd>
ifdef _WIN64
DWordPtrAdd equ <ULongLongAdd>
else
DWordPtrAdd proto __fastcall :DWORD_PTR, :DWORD_PTR, :ptr DWORD_PTR {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov DWORD_PTR ptr [_2],DWORD_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

SizeTAdd proto __fastcall :size_t, :size_t, :ptr size_t {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov SIZE_T ptr [_2],SIZE_T_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
SIZETAdd equ <ULongLongAdd>
else
SIZETAdd proto __fastcall :SIZE_T, :SIZE_T, :ptr SIZE_T {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov SIZE_T ptr [_2],_SIZE_T_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

ULongLongAdd proto __fastcall :ULONGLONG, :ULONGLONG, :ptr ULONGLONG {

    add _1,this
    .ifs (_1 >= this)
        mov [_2],_1
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_2],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

DWordLongAdd equ <ULongLongAdd>
ULong64Add   equ <ULongLongAdd>
DWord64Add   equ <ULongLongAdd>
UInt64Add    equ <ULongLongAdd>


;;=============================================================================
;; Subtraction functions
;;=============================================================================

UInt8Sub proto __fastcall :UINT8, :UINT8, :ptr UINT8 {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov UINT8 ptr [_2],UINT8_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UShortSub proto __fastcall :USHORT, :USHORT, :ptr USHORT {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov USHORT ptr [_2],USHORT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UInt16Sub equ <UShortSub>
WordSub   equ <UShortSub>

UIntSub proto __fastcall :UINT, :UINT, :ptr UINT {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov UINT ptr [_2],UINT_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

UInt32Sub  equ <UIntSub>
ifdef _WIN64
UIntPtrSub equ <ULongLongSub>
else
UIntPtrSub proto __fastcall :UINT_PTR, :UINT_PTR, :ptr UINT_PTR {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov UINT_PTR ptr [_2],UINT_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

ULongSub proto __fastcall :ULONG, :ULONG, :ptr ULONG {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov ULONG ptr [_2],ULONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
ULongPtrSub equ <ULongLongSub>
else
ULongPtrSub proto __fastcall :ULONG_PTR, :ULONG_PTR, :ptr ULONG_PTR {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov ULONG_PTR ptr [_2],ULONG_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

DWordSub    equ <ULongSub>
ifdef _WIN64
DWordPtrSub equ <ULongLongSub>
else
DWordPtrSub proto __fastcall :DWORD_PTR, :DWORD_PTR, :ptr DWORD_PTR {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov DWORD_PTR ptr [_2],DWORD_PTR_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

SizeTSub proto __fastcall :size_t, :size_t, :ptr size_t {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov SIZE_T ptr [_2],SIZE_T_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

ifdef _WIN64
SIZETSub equ <ULongLongSub>
else
SIZETSub proto __fastcall :SIZE_T, :SIZE_T, :ptr SIZE_T {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov SIZE_T ptr [_2],_SIZE_T_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }
endif

ULongLongSub proto __fastcall :ULONGLONG, :ULONGLONG, :ptr ULONGLONG {

    .ifs (this >= _1)
        sub this,_1
        mov [_2],this
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_2],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
    }

DWordLongSub equ <ULongLongSub>
ULong64Sub   equ <ULongLongSub>
DWord64Sub   equ <ULongLongSub>
UInt64Sub    equ <ULongLongSub>


;;=============================================================================
;; Multiplication functions
;;=============================================================================

UInt8Mult proto __fastcall :UINT8, :UINT8, :ptr UINT8 {
    mov al,this
    mul _1
    UIntToUInt8(al, _2)
    }

UShortMult proto __fastcall :USHORT, :USHORT, :ptr USHORT {
    movzx eax,this
    movzx ecx,_1
    mul   ecx
    ULongToUShort(eax, _2)
    }

UInt16Mult equ <UShortMult>
WordMult   equ <UShortMult>

UIntMult proto __fastcall :UINT, :UINT, :ptr UINT {
    UInt32x32To64(this, _1)
    ULongLongToUInt(rax, _2)
    }

UInt32Mult  equ <UIntMult>
ifdef _WIN64
UIntPtrMult equ <ULongLongMult>
else
UIntPtrMult proto __fastcall :UINT_PTR, :UINT_PTR, :ptr UINT_PTR {
    UInt32x32To64(this, _1)
    ULongLongToUIntPtr(rax, _2)
    }
endif

ULongMult proto __fastcall :ULONG, :ULONG, :ptr ULONG {
    UInt32x32To64(this, _1)
    ULongLongToULong(rax, _2)
    }

ifdef _WIN64
ULongPtrMult equ <ULongLongMult>
else
ULongPtrMult proto __fastcall :ULONG_PTR, :ULONG_PTR, :ptr ULONG_PTR {
    UInt32x32To64(this, _1)
    ULongLongToULongPtr(rax, _2)
    }
endif

DWordMult equ <ULongMult>

ifdef _WIN64
DWordPtrMult equ <ULongLongMult>
else
DWordPtrMult proto __fastcall :DWORD_PTR, :DWORD_PTR, :ptr DWORD_PTR {
    UInt32x32To64(this, _1)
    ULongLongToDWordPtr(rax, _2)
    }
endif

ifdef _WIN64
SizeTMult equ <ULongLongMult>
else
SizeTMult proto __fastcall :size_t, :size_t, :ptr size_t {
    UInt32x32To64(this, _1)
    ULongLongToSizeT(rax, _2)
    }
endif

ifdef _WIN64
SIZETMult equ <ULongLongMult>
else
SIZETMult proto __fastcall :SIZE_T, :SIZE_T, :ptr SIZE_T {
    UInt32x32To64(this, _1)
    ULongLongToSIZET(rax, _2)
    }
endif

ULongLongMult proto __fastcall :ULONGLONG, :ULONGLONG, :ptr ULONGLONG {
if defined(_USE_INTRINSIC_MULTIPLY128)
   .new ullResultHigh:ULONGLONG
   .new ullResultLow:ULONGLONG
    push _2
    UnsignedMultiply128(this, _1, addr ullResultHigh)
    pop _2
    .if (ullResultHigh == 0)
        mov [_2],rax
        mov eax,S_OK
    .else
        mov ULONGLONG ptr [_2],ULONGLONG_ERROR
        mov eax,INTSAFE_E_ARITHMETIC_OVERFLOW
    .endif
else
endif
    }

DWordLongMult equ <ULongLongMult>
ULong64Mult   equ <ULongLongMult>
DWord64Mult   equ <ULongLongMult>
UInt64Mult    equ <ULongLongMult>


if defined(ENABLE_INTSAFE_SIGNED_FUNCTIONS)

if defined(_USE_INTRINSIC_MULTIPLY128)
Multiply128 equ <_mul128>
endif

;;=============================================================================
;; Signed addition functions
;;=============================================================================

Int8Add proto __fastcall :INT8, :INT8, :ptr INT8 {
    C_ASSERT(sizeof(LONG) gt sizeof(INT8))
    add this,_1
    LongToInt8(this, _2)
    }

ShortAdd proto __fastcall :SSHORT, :SSHORT, :ptr SSHORT {
    C_ASSERT(sizeof(LONG) gt sizeof(SSHORT))
    LongToShort(((LONG)sAugend) + ((LONG)sAddend), psResult)
    }

Int16Add equ <ShortAdd>

IntAdd proto __fastcall :int_t, :int_t, :ptr SINT {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(SINT))
    LongLongToInt(((LONGLONG)iAugend) + ((LONGLONG)iAddend), piResult)
    }

Int32Add equ <IntAdd>

ifdef _WIN64
IntPtrAdd equ <LongLongAdd>
else
IntPtrAdd proto __fastcall :INT_PTR, :INT_PTR, :ptr INT_PTR {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(INT_PTR))
    LongLongToIntPtr(((LONGLONG)iAugend) + ((LONGLONG)iAddend), piResult)
    }
endif

LongAdd proto __fastcall :LONG, :LONG, :ptr LONG {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(LONG))
    LongLongToLong(((LONGLONG)lAugend) + ((LONGLONG)lAddend), plResult)
    }

Long32Add  equ <IntAdd>
ifdef _WIN64
LongPtrAdd equ <LongLongAdd>
else
LongPtrAdd proto __fastcall :LONG_PTR, :LONG_PTR, :ptr LONG_PTR {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(LONG_PTR))
    LongLongToLongPtr(((LONGLONG)lAugend) + ((LONGLONG)lAddend), plResult)
    }
endif

LongLongAdd proto __fastcall :LONGLONG, :LONGLONG, :ptr LONGLONG {
    }

Long64Add equ <LongLongAdd>
Int64Add  equ <LongLongAdd>
ifdef _WIN64
PtrdiffTAdd equ <LongLongAdd>
else
PtrdiffTAdd proto __fastcall :ptrdiff_t, :ptrdiff_t, :ptr ptrdiff_t {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(ptrdiff_t))
    LongLongToPtrdiffT(((LONGLONG)Augend) + ((LONGLONG)Addend), pResult)
    }
endif

ifdef _WIN64
SSIZETAdd equ <LongLongAdd>
else
SSIZETAdd proto __fastcall :SSIZE_T, :SSIZE_T, :ptr SSIZE_T {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(SSIZE_T))
    LongLongToSSIZET(((LONGLONG)Augend) + ((LONGLONG)Addend), pResult)
    }
endif


;;=============================================================================
;; Signed subtraction functions
;;=============================================================================

Int8Sub proto __fastcall :INT8, :INT8, :ptr INT8 {
    C_ASSERT(sizeof(LONG) gt sizeof(INT8))
    LongToInt8(((LONG)i8Minuend) - ((LONG)i8Subtrahend), pi8Result)
    }

ShortSub proto __fastcall :SSHORT, :SSHORT, :ptr SSHORT {
    C_ASSERT(sizeof(LONG) gt sizeof(SSHORT))
    LongToShort(((LONG)sMinuend) - ((LONG)sSubtrahend), psResult)
    }

Int16Sub equ <ShortSub>

IntSub proto __fastcall :int_t, :int_t, :ptr SINT {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(SINT))
    LongLongToInt(((LONGLONG)iMinuend) - ((LONGLONG)iSubtrahend), piResult)
    }

Int32Sub  equ <IntSub>

ifdef _WIN64
IntPtrSub equ <LongLongSub>
else
IntPtrSub proto __fastcall :INT_PTR, :INT_PTR, :ptr INT_PTR {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(INT_PTR))
    LongLongToIntPtr(((LONGLONG)iMinuend) - ((LONGLONG)iSubtrahend), piResult)
    }
endif

LongSub proto __fastcall :LONG, :LONG, :ptr LONG {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(LONG))
    LongLongToLong(((LONGLONG)lMinuend) - ((LONGLONG)lSubtrahend), plResult)
    }

Long32Sub  equ <IntSub>
ifdef _WIN64
LongPtrSub equ <LongLongSub>
else
LongPtrSub proto __fastcall :LONG_PTR, :LONG_PTR, :ptr LONG_PTR {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(LONG_PTR))
    LongLongToLongPtr(((LONGLONG)lMinuend) - ((LONGLONG)lSubtrahend), plResult)
    }
endif

LongLongSub proto __fastcall :LONGLONG, :LONGLONG, :ptr LONGLONG {
    }
Long64Sub equ <LongLongSub>
Int64Sub  equ <LongLongSub>

ifdef _WIN64
PtrdiffTSub equ <LongLongSub>
else
PtrdiffTSub proto __fastcall :ptrdiff_t, :ptrdiff_t, :ptr ptrdiff_t {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(ptrdiff_t))
    LongLongToPtrdiffT(((LONGLONG)Minuend) - ((LONGLONG)Subtrahend), pResult)
    }
endif

ifdef _WIN64
SSIZETSub equ <LongLongSub>
else
SSIZETSub proto __fastcall :SSIZE_T, :SSIZE_T, :ptr SSIZE_T {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(SSIZE_T))
    LongLongToSSIZET(((LONGLONG)Minuend) - ((LONGLONG)Subtrahend), pResult)
    }
endif


;;=============================================================================
;; Signed multiplication functions
;;=============================================================================

Int8Mult proto __fastcall :INT8, :INT8, :ptr INT8 {
    C_ASSERT(sizeof(LONG) gt sizeof(INT8))
    LongToInt8(((LONG)i8Multiplier) * ((LONG)i8Multiplicand), pi8Result)
    }

ShortMult proto __fastcall :SSHORT, :SSHORT, :ptr SSHORT {
    C_ASSERT(sizeof(LONG) gt sizeof(SSHORT))
    LongToShort(((LONG)sMultiplicand) * ((LONG)sMultiplier), psResult)
    }

Int16Mult equ <ShortMult>

IntMult proto __fastcall :int_t, :int_t, :ptr SINT {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(SINT))
    LongLongToInt(((LONGLONG)iMultiplicand) * ((LONGLONG)iMultiplier), piResult)
    }

Int32Mult  equ <IntMult>

ifdef _WIN64
IntPtrMult equ <LongLongMult>
else
IntPtrMult proto __fastcall :INT_PTR, :INT_PTR, :ptr INT_PTR {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(INT_PTR))
    LongLongToIntPtr(((LONGLONG)iMultiplicand) * ((LONGLONG)iMultiplier), piResult)
    }
endif

LongMult proto __fastcall :LONG, :LONG, :ptr LONG {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(LONG))
    LongLongToLong(((LONGLONG)lMultiplicand) * ((LONGLONG)lMultiplier), plResult)
    }

Long32Mult  equ <IntMult>
ifdef _WIN64
LongPtrMult equ <LongLongMult>
else
LongPtrMult proto __fastcall  :LONG_PTR, :LONG_PTR, :ptr LONG_PTR {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(LONG_PTR))
    LongLongToLongPtr(((LONGLONG)lMultiplicand) * ((LONGLONG)lMultiplier), plResult)
    }
endif

LongLongMult proto __fastcall :LONGLONG, :LONGLONG, :ptr LONGLONG {
if defined(_USE_INTRINSIC_MULTIPLY128)
else
endif
    }

Long64Mult equ <LongLongMult>
Int64Mult  equ <LongLongMult>
ifdef _WIN64
PtrdiffTMult equ <LongLongMult>
else
PtrdiffTMult proto __fastcall :ptrdiff_t, :ptrdiff_t, :ptr ptrdiff_t {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(ptrdiff_t))
    LongLongToPtrdiffT(((LONGLONG)Multiplicand) * ((LONGLONG)Multiplier), pResult)
    }
endif

ifdef _WIN64
SSIZETMult equ <LongLongMult>
else
SSIZETMult proto __fastcall :SSIZE_T, :SSIZE_T, :ptr SSIZE_T {
    C_ASSERT(sizeof(LONGLONG) gt sizeof(SSIZE_T))
    LongLongToSSIZET(((LONGLONG)Multiplicand) * ((LONGLONG)Multiplier), pResult)
    }
endif

endif ;; ENABLE_INTSAFE_SIGNED_FUNCTIONS
if 0
LOWORD macro _dw
        exitm<((((DWORD_PTR)(_dw)) AND 0xffff))>
        endm
HIWORD macro _dw
        exitm<(((((DWORD_PTR)(_dw)) SHR 16) AND 0xffff))>
        endm
LODWORD macro _qw
        exitm<((_qw))>
        endm
HIDWORD macro _qw
        exitm<((((_qw) SHR 32) AND 0xffffffff))>
        endm
endif
endif ;; _INTSAFE_H_INCLUDED_

