ifndef _BASETSD_
define _BASETSD_
ifndef __LIBC_INC
 include libc.inc
endif

INT8		typedef sbyte
PINT8		typedef ptr sbyte
INT16		typedef sword
PINT16		typedef ptr sword
INT32		typedef sdword
PINT32		typedef ptr sdword
INT64		typedef sqword
PINT64		typedef ptr sqword

UINT8		typedef byte
PUINT8		typedef ptr byte
UINT16		typedef word
PUINT16		typedef ptr word
UINT32		typedef dword
PUINT32		typedef ptr dword
UINT64		typedef qword
PUINT64		typedef ptr qword

LONG32		typedef sdword
PLONG32		typedef ptr sdword

ULONG32		typedef dword
PULONG32	typedef ptr dword
DWORD32		typedef dword
PDWORD32	typedef ptr dword

ifdef _WIN64

    INT_PTR	typedef sqword
    PINT_PTR	typedef ptr sqword
    UINT_PTR	typedef qword
    PUINT_PTR	typedef ptr qword

    LONG_PTR	typedef sqword
    PLONG_PTR	typedef ptr sqword
    ULONG_PTR	typedef qword
    PULONG_PTR	typedef ptr qword

    __int3264	typedef sqword ; __int64

else
    INT_PTR	typedef sdword
    PINT_PTR	typedef ptr sdword
    UINT_PTR	typedef dword
    PUINT_PTR	typedef ptr dword

    LONG_PTR	typedef sdword
    PLONG_PTR	typedef ptr sdword
    ULONG_PTR	typedef dword
    PULONG_PTR	typedef ptr dword

    __int3264	typedef sdword ; __int32
endif

ifdef _WIN64

ADDRESS_TAG_BIT		equ 0x40000000000

SHANDLE_PTR		typedef sqword
HANDLE_PTR		typedef qword
UHALF_PTR		typedef dword
PUHALF_PTR		typedef ptr dword
HALF_PTR		typedef sdword
PHALF_PTR		typedef ptr sdword

ifndef __midl
HandleToULong macro h
    exitm<ULONG ptr h>
    endm
HandleToLong macro h
    exitm<LONG ptr h>
    endm
ULongToHandle macro h
    exitm<PVOID ptr h>
    endm
LongToHandle macro h
    exitm<PVOID ptr h>
    endm
PtrToUlong macro p
    exitm<p>
    endm
PtrToUint macro p
    exitm<UINT ptr p>
    endm
PtrToUshort macro p
    exitm<WORD ptr p>
    endm
PtrToLong macro p
    exitm<LONG ptr p>
    endm
PtrToInt macro p
    exitm<SINT ptr p>
    endm
PtrToShort macro p
    exitm<SWORD ptr p>
    endm
IntToPtr macro i
    exitm<PVOID ptr i>
    endm
UIntToPtr macro ui
    exitm<PVOID ptr ui>
    endm
LongToPtr macro l
    exitm<PVOID ptr l>
    endm
ULongToPtr macro ui
    exitm<PVOID ptr ul>
    endm
PtrToPtr64 macro p
    exitm<PVOID ptr p>
    endm
Ptr64ToPtr macro p
    exitm<PVOID ptr p>
    endm
HandleToHandle64 macro h
    exitm<PtrToPtr64( h )>
    endm
Handle64ToHandle macro h
    exitm<Ptr64ToPtr( h )>
    endm
Ptr32ToPtr macro p
    exitm<ptr p>
    endm
Handle32ToHandle macro h
    exitm<ptr h>
    endm
PtrToPtr32 macro p
    exitm<ptr p>
    endm
HandleToHandle32 macro h
    exitm<PtrToPtr32(h)>
    endm

endif

else

ADDRESS_TAG_BIT		equ 0x80000000

UHALF_PTR		typedef word
PUHALF_PTR		typedef ptr word
HALF_PTR		typedef sword
PHALF_PTR		typedef ptr sword

SHANDLE_PTR		typedef sdword
HANDLE_PTR		typedef dword

HandleToULong macro h
    exitm<ULONG ptr h>
    endm
HandleToLong macro h
    exitm<LONG ptr h>
    endm
ULongToHandle macro h
    exitm<PVOID ptr h>
    endm
LongToHandle macro h
    exitm<PVOID ptr h>
    endm
PtrToUlong macro p
    exitm<ULONG ptr p>
    endm
PtrToUint macro p
    exitm<UINT ptr p>
    endm
PtrToUshort macro p
    exitm<WORD ptr p>
    endm
PtrToLong macro p
    exitm<LONG ptr p>
    endm
PtrToInt macro p
    exitm<SINT ptr p>
    endm
PtrToShort macro p
    exitm<SWORD ptr p>
    endm
IntToPtr macro i
    exitm<PVOID ptr i>
    endm
UIntToPtr macro ui
    exitm<PVOID ptr ui>
    endm
LongToPtr macro l
    exitm<PVOID ptr l>
    endm
ULongToPtr macro ui
    exitm<PVOID ptr ul>
    endm

ifndef __midl
PtrToPtr64 macro p
    exitm<ptr p>
    endm
Ptr64ToPtr macro p
    exitm<ptr p>
    endm
HandleToHandle64 macro h
    exitm<PtrToPtr64( h )>
    endm
Handle64ToHandle macro h
    exitm<Ptr64ToPtr( h )>
    endm
endif

Ptr32ToPtr macro p
    exitm<ptr p>
    endm
Handle32ToHandle macro h
    exitm<ptr h>
    endm
PtrToPtr32 macro p
    exitm<ptr p>
    endm
HandleToHandle32 macro h
    exitm<PtrToPtr32(h)>
    endm

endif

ifdef _WIN64
MAXUHALF_PTR	equ 0xffffffff
MAXUINT_PTR	equ 0xffffffffffffffff
else
MAXUHALF_PTR	equ 0xffff
MAXUINT_PTR	equ 0xffffffff
endif

MAXINT_PTR	equ MAXUINT_PTR shr 1
MININT_PTR	equ MAXINT_PTR + 1

MAXULONG_PTR	equ MAXUINT_PTR
MAXLONG_PTR	equ MAXINT_PTR
MINLONG_PTR	equ MININT_PTR

MAXHALF_PTR	equ MAXUHALF_PTR shr 1
MINHALF_PTR	equ MAXHALF_PTR + 1

if _WIN32_WINNT GE 0x0600

MAXUINT8	equ 0xff
MAXINT8		equ MAXUINT8 shr 1
MININT8		equ MAXINT8 + 1

MAXUINT16	equ 0xffff
MAXINT16	equ MAXUINT16 shr 1
MININT16	equ MAXINT16 + 1

MAXUINT32	equ 0xffffffff
MAXINT32	equ MAXUINT32 shr 1
MININT32	equ MAXINT32 + 1

MAXUINT64	equ 0xffffffffffffffff
MAXINT64	equ MAXUINT64 shr 1
MININT64	equ MAXINT64 + 1

MAXULONG32	equ 0xffffffff
MAXLONG32	equ MAXULONG32 shr 1
MINLONG32	equ MAXLONG32 + 1

MAXULONG64	equ 0xffffffffffffffff
MAXLONG64	equ MAXULONG64 shr 1
MINLONG64	equ MAXLONG64 + 1

MAXULONGLONG	equ MAXULONG64
MINLONGLONG	equ MINLONG64

MAXSIZE_T	equ MAXUINT_PTR
MAXSSIZE_T	equ MAXSIZE_T shr 1
MINSSIZE_T	equ MAXSSIZE_T + 1

MAXUINT		equ 0xffffffff
MAXINT		equ MAXUINT shr 1
MININT		equ MAXINT + 1

MAXDWORD32	equ MAXULONG32
MAXDWORD64	equ MAXULONG64

endif

DWORD_PTR	typedef ULONG_PTR
PDWORD_PTR	typedef ptr ULONG_PTR

LONG64		typedef sqword
PLONG64		typedef ptr sqword

ULONG64		typedef qword
PULONG64	typedef ptr qword
DWORD64		typedef qword
PDWORD64	typedef ptr qword

KAFFINITY	typedef ULONG_PTR
PKAFFINITY	typedef ptr KAFFINITY

endif
