ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;
; Type definitions for the basic sized types.
;
ifndef _BASETSD_
_BASETSD_ equ 1

;
; The following types are guaranteed to be signed and 32 bits wide.
;
LONG32		typedef sdword
PLONG32		typedef ptr sdword
INT32		typedef sdword
PINT32		typedef ptr sdword

;
; The following types are guaranteed to be unsigned and 32 bits wide.
;
ULONG32		typedef dword
PULONG32	typedef ptr dword
DWORD32		typedef dword
PDWORD32	typedef ptr dword
UINT32		typedef dword
PUINT32		typedef ptr dword

;
; The INT_PTR is guaranteed to be the same size as a pointer.	Its
; size with change with pointer size (32/64).	It should be used
; anywhere that a pointer is cast to an integer type. UINT_PTR is
; the unsigned variation.
;
; HALF_PTR is half the size of a pointer it intended for use with
; within strcuture which contain a pointer and two small fields.
; UHALF_PTR is the unsigned variation.
;

ifdef _WIN64

INT_PTR		typedef sqword
PINT_PTR	typedef ptr sqword

UINT_PTR	typedef qword
PUINT_PTR	typedef ptr qword

MAXINT_PTR	equ 0x7fffffffffffffff
MININT_PTR	equ 0x8000000000000000
MAXUINT_PTR	equ 0xffffffffffffffff

UHALF_PTR	typedef dword
PUHALF_PTR	typedef ptr dword

HALF_PTR	typedef sdword
PHALF_PTR	typedef ptr sdword

MAXUHALF_PTR	equ 0xffffffff
MAXHALF_PTR	equ 0x7fffffff
MINHALF_PTR	equ 0x80000000

else

INT_PTR		typedef sdword
PINT_PTR	typedef ptr sdword

UINT_PTR	typedef dword
PUINT_PTR	typedef ptr dword

MAXINT_PTR	equ 0x7fffffff
MININT_PTR	equ 0x80000000
MAXUINT_PTR	equ 0xffffffff

UHALF_PTR	typedef dword
PUHALF_PTR	typedef ptr dword

HALF_PTR	typedef sdword
PHALF_PTR	typedef ptr sdword

MAXUHALF_PTR	equ 0xffff
MAXHALF_PTR	equ 0x7fff
MINHALF_PTR	equ 0x8000

endif

;
; SIZE_T used for counts or ranges which need to span the range of
; of a pointer.	 SSIZE_T is the signed variation.
;

SIZE_T		typedef UINT_PTR
PSIZE_T		typedef ptr UINT_PTR
SSIZE_T		typedef INT_PTR
PSSIZE_T	typedef ptr INT_PTR

;
; The following types are guaranteed to be signed and 64 bits wide.
;

LONG64		typedef sqword
PLONG64		typedef ptr sqword
INT64		typedef sqword
PINT64		typedef ptr sqword

;
; The following types are guaranteed to be unsigned and 64 bits wide.
;

ULONG64		typedef qword
PULONG64	typedef ptr qword
DWORD64		typedef qword
PDWORD64	typedef ptr qword
UINT64		typedef qword
PUINT64		typedef ptr qword

endif ; _BASETSD_

.list
