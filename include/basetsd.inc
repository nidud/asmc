ifndef _BASETSD_
_BASETSD_ equ <>
ifndef __LIBC_INC
 include libc.inc
endif
.xlist
if (defined(_M_MRX000) OR defined(_M_AMD64) OR defined(_M_IA64)) AND (_MSC_VER GE 1100) AND NOT defined(MIDL_PASS)
 POINTER_64 equ <ptr>
 POINTER_64_INT typedef qword
 ifdef _WIN64
  POINTER_32 equ <ptr>
 else
  POINTER_32 equ <>
 endif
else
  if (_MSC_VER GE 1300) AND NOT defined(MIDL_PASS)
   POINTER_64 equ <ptr>
  else
   POINTER_64 equ <>
  endif
 POINTER_64_INT typedef dword
 POINTER_32 equ <>
endif

if defined(_IA64_) OR defined(_AMD64_)
FIRMWARE_PTR equ <>
else
FIRMWARE_PTR equ <POINTER_32>
endif


if 0 AND (_MSC_FULL_VER GE 140041204) AND NOT defined(MIDL_PASS)
POINTER_SIGNED	 equ <__sptr>
POINTER_UNSIGNED equ <__uptr>
else
POINTER_SIGNED	 equ <>
POINTER_UNSIGNED equ <>
endif

SPOINTER_32 equ <POINTER_32 POINTER_SIGNED>
UPOINTER_32 equ <POINTER_32 POINTER_UNSIGNED>

if _MSC_VER GT 1000
;pragma once
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
if not defined(__midl) and (defined(_X86_) or defined(_M_IX86)) and _MSC_VER GE 1300
_W64		equ <__w64>
else
_W64		equ <>
endif
endif

if 0
if ( 501 < __midl )

    typedef [public] __int3264 INT_PTR, *PINT_PTR;
    typedef [public] unsigned __int3264 UINT_PTR, *PUINT_PTR;

    typedef [public] __int3264 LONG_PTR, *PLONG_PTR;
    typedef [public] unsigned __int3264 ULONG_PTR, *PULONG_PTR;

else  
endif
endif

ifdef _WIN64

    INT_PTR	typedef sqword
    PINT_PTR	typedef ptr sqword
    UINT_PTR	typedef qword
    PUINT_PTR	typedef ptr qword

    LONG_PTR	typedef sqword
    PLONG_PTR	typedef ptr sqword
    ULONG_PTR	typedef qword
    PULONG_PTR	typedef ptr qword

    __int3264	equ <sqword> ; __int64

else

    INT_PTR	typedef sdword;_W64 SINT
    PINT_PTR	typedef ptr sdword
    UINT_PTR	typedef dword;_W64 UINT
    PUINT_PTR	typedef ptr dword;UINT_PTR

    LONG_PTR	typedef sdword;_W64 LONG
    PLONG_PTR	typedef ptr sdword;LONG_PTR
    ULONG_PTR	typedef dword;_W64 ULONG
    PULONG_PTR	typedef ptr dword;ULONG_PTR

    __int3264	equ <sdword> ; __int32

endif
;endif 


ifdef _WIN64

ADDRESS_TAG_BIT		equ 0x40000000000

SHANDLE_PTR		typedef sqword ; __int64
HANDLE_PTR		typedef qword  ; unsigned __int64
UHALF_PTR		typedef dword  ; unsigned int
PUHALF_PTR		typedef ptr dword
HALF_PTR		typedef sdword ; int
PHALF_PTR		typedef ptr sdword

ifndef __midl
;__inline
;unsigned long
HandleToULong macro h ; const void *h
    exitm<ULONG ptr h>
    endm
;long
HandleToLong macro h ; const void *h
    exitm<LONG ptr h>
    endm
;void *
ULongToHandle macro h ; const unsigned long h
    exitm<PVOID ptr h>
    endm
;void *
LongToHandle macro h ; const long h
    exitm<PVOID ptr h>
    endm
;unsigned long
PtrToUlong macro p ; const void *p
    exitm<ULONG ptr p>
    endm
;unsigned int
PtrToUint macro p ; const void *p
    exitm<UINT ptr p>
    endm
;unsigned short
PtrToUshort macro p ; const void *p
    exitm<WORD ptr p>
    endm
;long
PtrToLong macro p ; const void *p
    exitm<LONG ptr p>
    endm
;int
PtrToInt macro p ; const void *p
    exitm<SINT ptr p>
    endm
;short
PtrToShort macro p ; const void *p
    exitm<SWORD ptr p>
    endm
;void *
IntToPtr macro i ; const int i
    exitm<PVOID ptr i>
    endm
;void *
UIntToPtr macro ui ; const unsigned int ui
    exitm<PVOID ptr ui>
    endm
;void *
LongToPtr macro l ; const long l
    exitm<PVOID ptr l>
    endm
;void *
ULongToPtr macro ui ; const unsigned long ui
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
;void *
Ptr32ToPtr macro p ; const void * POINTER_32 p
    exitm<PVOID ptr p>
    endm
;void *
Handle32ToHandle macro h ; const void * POINTER_32 h
    exitm<PVOID ptr h>
    endm
;void * POINTER_32
PtrToPtr32 macro p ; const void *p
    exitm<PVOID ptr p>
    endm
HandleToHandle32 macro h
    exitm<PtrToPtr32(h)>
    endm

endif 

else  

ADDRESS_TAG_BIT		equ 0x80000000

UHALF_PTR		typedef word  ; unsigned short
PUHALF_PTR		typedef ptr word
HALF_PTR		typedef sword ; short
PHALF_PTR		typedef ptr sword

SHANDLE_PTR		typedef sdword ; long
HANDLE_PTR		typedef dword  ; unsigned long

;unsigned long
HandleToULong macro h ; const void *h
    exitm<ULONG ptr h>
    endm
;long
HandleToLong macro h ; const void *h
    exitm<LONG ptr h>
    endm
;void *
ULongToHandle macro h ; const unsigned long h
    exitm<PVOID ptr h>
    endm
;void *
LongToHandle macro h ; const long h
    exitm<PVOID ptr h>
    endm
;unsigned long
PtrToUlong macro p ; const void *p
    exitm<ULONG ptr p>
    endm
;unsigned int
PtrToUint macro p ; const void *p
    exitm<UINT ptr p>
    endm
;unsigned short
PtrToUshort macro p ; const void *p
    exitm<WORD ptr p>
    endm
;long
PtrToLong macro p ; const void *p
    exitm<LONG ptr p>
    endm
;int
PtrToInt macro p ; const void *p
    exitm<SINT ptr p>
    endm
;short
PtrToShort macro p ; const void *p
    exitm<SWORD ptr p>
    endm
;void *
IntToPtr macro i ; const int i
    exitm<PVOID ptr i>
    endm
;void *
UIntToPtr macro ui ; const unsigned int ui
    exitm<PVOID ptr ui>
    endm
;void *
LongToPtr macro l ; const long l
    exitm<PVOID ptr l>
    endm
;void *
ULongToPtr macro ui ; const unsigned long ui
    exitm<PVOID ptr ul>
    endm

ifndef __midl
;__inline
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
endif

;void *
Ptr32ToPtr macro p ; const void * POINTER_32 p
    exitm<PVOID ptr p>
    endm
;void *
Handle32ToHandle macro h ; const void * POINTER_32 h
    exitm<PVOID ptr h>
    endm
;void * POINTER_32
PtrToPtr32 macro p ; const void *p
    exitm<PVOID ptr p>
    endm
HandleToHandle32 macro h
    exitm<PtrToPtr32(h)>
    endm

endif 


HandleToUlong	equ <HandleToULong>
UlongToHandle	equ <ULongToHandle>
UlongToPtr	equ <ULongToPtr>
UintToPtr	equ <UIntToPtr>

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


SIZE_T		typedef ULONG_PTR
PSIZE_T		typedef ptr ULONG_PTR

SSIZE_T		typedef LONG_PTR
PSSIZE_T	typedef ptr LONG_PTR

if _WIN32_WINNT GE 0x0600 ;|| (defined(__cplusplus) && defined(WINDOWS_ENABLE_CPLUSPLUS))

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

.list
endif 
