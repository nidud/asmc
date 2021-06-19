ifndef _INTTYPE_H_INCLUDED_
_INTTYPE_H_INCLUDED_ equ <>

;; assumptions:
;; - [unsigned] char  is 8-bit
;; - [unsigned] short is 16-bit
;; - [unsigned] int   is either 16- or 32-bit
;; - [unsigned] long  is either 32- or 64-bit

uint_8	 typedef byte
int_8	 typedef sbyte
uint_16	 typedef word
int_16	 typedef sword
uint_32	 typedef dword
int_32	 typedef sdword
uint_64	 typedef qword
int_64	 typedef sqword

;; 32-bit integer format specifier
ifdef __I86__
I32_SPEC equ <"l">
else
I32_SPEC equ <"">
endif

;; 64-bit integer format specifier
if defined(LONG_IS_64BITS) or defined(__LP64__)
I64_SPEC equ <"l">
elseif defined(__UNIX__) or defined(__CYGWIN__) or defined(__DJGPP__)
I64_SPEC equ <"ll">
else
I64_SPEC equ <"I64">
endif

endif
