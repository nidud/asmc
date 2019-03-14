ifndef _INC_MBDATA
_INC_MBDATA equ <>

include crtdefs.inc

.pragma pack(push, _CRT_PACKING)

ifdef _WIN32
NUM_ULINFO equ 6  ;; multibyte full-width-latin upper/lower info
else
NUM_ULINFO equ 12 ;; multibyte full-width-latin upper/lower info
endif

ifndef _THREADMBCINFO
_THREADMBCINFO equ <>
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
_THREADLOCALEINFO equ <>

ifndef LPSHORT
LPINT			typedef ptr sdword
LPSHORT			typedef ptr sword
endif
locrefcount		STRUC
locale			LPSTR ?
wlocale			LPWSTR ?
refcount		LPINT ?
wrefcount		LPINT ?
locrefcount		ENDS

threadlocinfo		STRUC
refcount		SINT ?
lc_codepage		dd ?
lc_collate_cp		dd ?
lc_time_cp		dd ?
lc_category		locrefcount 6 dup(<>)
lc_clike		SINT ?
mb_cur_max		SINT ?
lconv_intl_refcount	LPINT ?
lconv_num_refcount	LPINT ?
lconv_mon_refcount	LPINT ?
ctype1_refcount		LPINT ?
ctype1			LPSHORT ?
pctype			LPSHORT ?
pclmap			LPSTR ?
pcumap			LPSTR ?
lc_time_curr		ptr_t ?
locale_name		LPWSTR 6 dup(?)
threadlocinfo		ENDS
pthreadlocinfo		typedef ptr threadlocinfo
endif

externdef		__mbcodepage:int_t
externdef		__ismbcodepage:int_t
externdef		__mbulinfo:ushort_t
externdef		__ptmbcinfo:pthreadmbcinfo
__updatetmbcinfo	proto __cdecl

_ISMBCP			equ <__ismbcodepage NOT = 0>
_ISNOTMBCP		equ <__ismbcodepage EQ 0>

_ISMBCP_MT macro p
	exitm<.err>
	endm
_ISNOTMBCP_MT macro p
	exitm<.err>
	endm

_ismbbtruelead macro _lb,_ch
	exitm<.err>
	endm

_mbbisupper macro _c
	exitm<.err>
	endm
_mbbislower macro _c
	exitm<.err>
	endm

_mbbtolower macro _c
	exitm<.err>
	endm
_mbbtoupper macro _c
	exitm<.err>
	endm

_ismbbtruelead_l macro _lb,_ch,p
	exitm<.err>
	endm
_mbbisupper_l macro _c, p
	exitm<.err>
	endm
_mbbislower_l macro _c, p
	exitm<.err>
	endm
_mbbtolower_l macro _c, p
	exitm<.err>
	endm
_mbbtoupper_l macro _c, p
	exitm<.err>
	endm

_MBUPPERLOW1		equ <__mbulinfo[0]>
_MBUPPERHIGH1		equ <__mbulinfo[1]>
_MBCASEDIFF1		equ <__mbulinfo[2]>

_MBUPPERLOW2		equ <__mbulinfo[3]>
_MBUPPERHIGH2		equ <__mbulinfo[4]>
_MBCASEDIFF2		equ <__mbulinfo[5]>

_MBUPPERLOW1_MT macro p
	exitm<.err>
	endm
_MBUPPERHIGH1_MT macro p
	exitm<.err>
	endm
_MBCASEDIFF1_MT macro p
	exitm<.err>
	endm

_MBUPPERLOW2_MT macro p
	exitm<.err>
	endm
_MBUPPERHIGH2_MT macro p
	exitm<.err>
	endm
_MBCASEDIFF2_MT macro p
	exitm<.err>
	endm

ifndef _WIN32
_MBLOWERLOW1		equ <__mbulinfo[6]>
_MBLOWERHIGH1		equ <__mbulinfo[7]>
_MBLOWERLOW2		equ <__mbulinfo[8]>
_MBLOWERHIGH2		equ <__mbulinfo[9]>
_MBDIGITLOW		equ <__mbulinfo[10]>
_MBDIGITHIGH		equ <__mbulinfo[11]>
endif

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
