ifndef _INC_MBCTYPE
define _INC_MBCTYPE

include crtdefs.inc
include ctype.inc

ifdef _CRTBLD
if defined (_DLL) AND defined (_M_IX86)
__p__mbctype	proto __cdecl
__p__mbcasemap	proto __cdecl
endif
endif

ifndef _M_CEE_PURE
externdef _mbctype:byte
externdef _mbcasemap:byte
else
__p__mbctype	proto __cdecl
__p__mbcasemap	proto __cdecl
_mbctype	equ <__p__mbctype()>
_mbcasemap	equ <__p__mbcasemap()>
endif

ifdef _CRTBLD
externdef		__ptmbcinfo:pthreadmbcinfo
externdef		__globallocalestatus:int_t
externdef		__locale_changed:int_t
externdef		__initialmbcinfo:threadmbcinfo
__updatetmbcinfo	proto __cdecl
endif

_MS			equ 0x01    ;; MBCS single-byte symbol
_MP			equ 0x02    ;; MBCS punct
_M1			equ 0x04    ;; MBCS 1st (lead) byte
_M2			equ 0x08    ;; MBCS 2nd byte

_SBUP			equ 0x10    ;; SBCS upper char
_SBLOW			equ 0x20    ;; SBCS lower char

;; byte types

_MBC_SINGLE		equ 0	    ;; valid single byte char
_MBC_LEAD		equ 1	    ;; lead byte
_MBC_TRAIL		equ 2	    ;; trailing byte
_MBC_ILLEGAL		equ (-1)    ;; illegal byte

_KANJI_CP		equ 932

;; _setmbcp parameter defines
_MB_CP_SBCS		equ 0
_MB_CP_OEM		equ -2
_MB_CP_ANSI		equ -3
_MB_CP_LOCALE		equ -4


ifndef _MBCTYPE_DEFINED
define _MBCTYPE_DEFINED

;; MB control routines

_setmbcp proto __cdecl :int_t
_getmbcp proto __cdecl


;; MBCS character classification function prototypes

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

;; byte routines
_ismbbkalnum	proto __cdecl :uint_t
_ismbbkalnum_l	proto __cdecl :uint_t, :_locale_t
_ismbbkana	proto __cdecl :uint_t
_ismbbkana_l	proto __cdecl :uint_t, :_locale_t
_ismbbkpunct	proto __cdecl :uint_t
_ismbbkpunct_l	proto __cdecl :uint_t, :_locale_t
_ismbbkprint	proto __cdecl :uint_t
_ismbbkprint_l	proto __cdecl :uint_t, :_locale_t
_ismbbalpha	proto __cdecl :uint_t
_ismbbalpha_l	proto __cdecl :uint_t, :_locale_t
_ismbbpunct	proto __cdecl :uint_t
_ismbbpunct_l	proto __cdecl :uint_t, :_locale_t
_ismbbblank	proto __cdecl :uint_t
_ismbbblank_l	proto __cdecl :uint_t, :_locale_t
_ismbbalnum	proto __cdecl :uint_t
_ismbbalnum_l	proto __cdecl :uint_t, :_locale_t
_ismbbprint	proto __cdecl :uint_t
_ismbbprint_l	proto __cdecl :uint_t, :_locale_t
_ismbbgraph	proto __cdecl :uint_t
_ismbbgraph_l	proto __cdecl :uint_t, :_locale_t

ifndef _MBLEADTRAIL_DEFINED
define _MBLEADTRAIL_DEFINED

_ismbblead	proto __cdecl :uint_t
_ismbblead_l	proto __cdecl :uint_t, :_locale_t
_ismbbtrail	proto __cdecl :uint_t
_ismbbtrail_l	proto __cdecl :uint_t, :_locale_t
_ismbslead	proto __cdecl :LPSTR, :LPSTR
_ismbslead_l	proto __cdecl :LPSTR, :LPSTR, :_locale_t
_ismbstrail	proto __cdecl :LPSTR, :LPSTR
_ismbstrail_l	proto __cdecl :LPSTR, :LPSTR, :_locale_t
endif
endif ;; _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
endif ;; _MBCTYPE_DEFINED

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

if defined(_CRT_DISABLE_PERFCRIT_LOCKS) AND ( defined(_DLL) EQ 0 )
_ismgetc macro _c
	movzx eax,byte ptr _c
	lea   r10,_mbctype
	movzx eax,byte ptr [r10+rax+1]
	exitm<eax>
	endm
_ismgetwc macro _c
	movzx edx,byte ptr _c
	mov   r10,_pctype
	movzx eax,word ptr [r10+rdx*2]
	exitm<eax>
	endm
_ismbbkalnum macro _c
	and _ismgetc(_c),_MS
	retm<eax>
	endm
_ismbbkprint macro _c
	and _ismgetc(_c),(_MS OR _MP)
	retm<eax>
	endm
_ismbbkpunct macro _c
	and _ismgetc(_c),_MP
	retm<eax>
	endm

_ismbbalnum macro _c
	.if !(_ismgetwc(_c) & (_ALPHA OR _DIGIT))
	    _ismbbkalnum(dl)
	.endif
	retm<eax>
	endm
_ismbbalpha macro _c
	.if !(_ismgetwc(_c) & _ALPHA)
	    _ismbbkalnum(dl)
	.endif
	retm<eax>
	endm
_ismbbgraph macro _c
	.if !(_ismgetwc(_c) & (_PUNCT OR _ALPHA OR _DIGIT))
	    _ismbbkprint(dl)
	.endif
	retm<eax>
	endm
_ismbbprint macro _c
	.if !(_ismgetwc(_c) & (_BLANK OR _PUNCT OR _ALPHA OR _DIGIT))
	    _ismbbkprint(dl)
	.endif
	retm<eax>
	endm
_ismbbpunct macro _c
	.if !(_ismgetwc(_c) & _PUNCT)
	    _ismbbkpunct(dl)
	.endif
	retm<eax>
	endm
_ismbbblank macro _c
	.if (_c == 9)
	    mov eax,_BLANK
	.else
	    and _ismgetwc(_c),_BLANK
	.endif
	retm<eax>
	endm

_ismbblead macro _c
	and _ismgetc(_c),_M1
	retm<eax>
	endm
_ismbbtrail macro _c
	and _ismgetc(_c),_M2
	retm<eax>
	endm
_ismbbkana macro _c
	and _ismgetc(_c),(_MS OR _MP)
	retm<eax>
	endm
endif ;; defined (_CRT_DISABLE_PERFCRIT_LOCKS) AND NOT defined (_DLL)

ifdef _CRTBLD
if 0
_ismbbalnum_l macro _c, pt
	exitm<>
	endm
_ismbbalpha_l macro _c, pt
	exitm<>
	endm
_ismbbgraph_l macro _c, pt
	exitm<>
	endm
_ismbbprint_l macro _c, pt
	exitm<>
	endm
_ismbbpunct_l macro _c, pt
	exitm<>
	endm
_ismbbblank_l macro _c, pt
	exitm<>
	endm
_ismbblead_l macro _c, p
	exitm<>
	endm
_ismbbtrail_l macro _c, p
	exitm<>
	endm
endif

endif ;; _CRTBLD
endif ;; _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
endif ;; _INC_MBCTYPE
