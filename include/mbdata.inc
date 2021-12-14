ifndef _INC_MBDATA
define _INC_MBDATA

include crtdefs.inc

.pragma pack(push, _CRT_PACKING)

ifdef _WIN32
NUM_ULINFO equ 6  ;; multibyte full-width-latin upper/lower info
else
NUM_ULINFO equ 12 ;; multibyte full-width-latin upper/lower info
endif

ifndef _THREADMBCINFO
define _THREADMBCINFO
threadmbcinfo	STRUC
refcount	int_t ?
mbcodepage	int_t ?
ismbcodepage	int_t ?
mbulinfo	dw 6 dup(?)
mbctype		db 257 dup(?)
mbcasemap	db 256 dup(?)
mblocalename	wstring_t ?
threadmbcinfo	ENDS
pthreadmbcinfo	typedef ptr threadmbcinfo
endif

ifndef _THREADLOCALEINFO
define _THREADLOCALEINFO
ifndef LPSHORT
LPINT	typedef ptr sdword
LPSHORT typedef ptr sword
endif
.template locrefcount
    locale		LPSTR ?
    wlocale		LPWSTR ?
    refcount		LPINT ?
    wrefcount		LPINT ?
   .ends
.template threadlocinfo
    refcount		SINT ?
    lc_codepage		UINT ?
    lc_collate_cp	UINT ?
    lc_time_cp		UINT ?
    lc_category		locrefcount 6 dup(<>)
    lc_clike		SINT ?
    mb_cur_max		SINT ?
    lconv_intl_refcount LPINT ?
    lconv_num_refcount	LPINT ?
    lconv_mon_refcount	LPINT ?
    lconvp		PVOID ?
    ctype1_refcount	LPINT ?
    ctype1		LPSHORT ?
    pctype		LPSHORT ?
    pclmap		LPSTR ?
    pcumap		LPSTR ?
    lc_time_curr	ptr __lc_time_data ?
    locale_name		LPWSTR ? 6 dup(?)
   .ends
    pthreadmbcinfo	typedef ptr threadmbcinfo
endif

externdef		__mbcodepage:int_t
externdef		__ismbcodepage:int_t
externdef		__mbulinfo:ushort_t
externdef		__ptmbcinfo:pthreadmbcinfo
__updatetmbcinfo	proto __cdecl

_MBHIRALOW		equ 0x829f
_MBHIRAHIGH		equ 0x82f1
_MBKATALOW		equ 0x8340
_MBKATAHIGH		equ 0x8396
_MBKATAEXCEPT		equ 0x837f
_MBKIGOULOW		equ 0x8141
_MBKIGOUHIGH		equ 0x81ac
_MBKIGOUEXCEPT		equ 0x817f

.pragma pack(pop)

endif ;; _INC_MBDATA
