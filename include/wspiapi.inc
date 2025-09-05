ifndef _WSPIAPI_H_
define _WSPIAPI_H_

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if (NTDDI_VERSION GE NTDDI_WIN2K)

include stdio.inc	;; sprintf()
include stdlib.inc	;; calloc(), strtoul()
include malloc.inc	;; calloc()
include string.inc	;; strlen(), strcmp(), strstr()

if defined(__GOT_SECURE_LIB__) AND __GOT_SECURE_LIB__ GE 200402

_WSPIAPI_STRCPY_S	equ <strcpy_s>
_WSPIAPI_STRCAT_S	equ <strcat_s>
_WSPIAPI_STRNCPY_S	equ <strncpy_s>
_WSPIAPI_SPRINTF_S_1	equ <sprintf_s>

else

_WSPIAPI_STRCPY_S macro _Dst, _Size, _Src
	exitm<strcpy((_Dst), (_Src))>
	endm
_WSPIAPI_STRCAT_S macro _Dst, _Size, _Src
	exitm<strcat((_Dst), (_Src))>
	endm
_WSPIAPI_STRNCPY_S macro _Dst, _Size, _Src, _Count
	strncpy((_Dst), (_Src), (_Count))
	exitm<(_Dst)[(_Size) - 1] = 0>
	endm
_WSPIAPI_SPRINTF_S_1 macro _Dst, _Size, _Format, _Arg1
	exitm<sprintf((_Dst), (_Format), (_Arg1))>
	endm

endif

ifndef _WSPIAPI_COUNTOF
_WSPIAPI_COUNTOF macro _Array
	exitm<lengthof(_Array)>
	endm
endif

WspiapiMalloc macro tSize
	exitm<calloc(1, (tSize))>
	endm
WspiapiFree macro p
	exitm<free(p)>
	endm
WspiapiSwap macro a, b, c
	exitm<{ (c) = (a); (a) = (b); (b) = (c); }>
	endm

;getaddrinfo		equ <WspiapiGetAddrInfo>
;getnameinfo		equ <WspiapiGetNameInfo>
;freeaddrinfo		equ <WspiapiFreeAddrInfo>

CALLBACK(WSPIAPI_PGETADDRINFO, :ptr, :ptr, :ptr, :ptr)
CALLBACK(WSPIAPI_PGETNAMEINFO, :ptr, :socklen_t, :ptr, :size_t, :ptr, :size_t, :SINT)
CALLBACK(WSPIAPI_PFREEADDRINFO, :ptr)

endif ;; if (NTDDI_VERSION GE WIN2K)
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
endif ;; _WSPIAPI_H_
