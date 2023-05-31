ifndef _INC_MBSTRING
define _INC_MBSTRING

include crtdefs.inc

.pragma pack(push, _CRT_PACKING)

ifndef _FILE_DEFINED
define _FILE_DEFINED
_iobuf		struct size_t
_ptr		LPTSTR ?
_cnt		SINT ?
_base		LPSTR ?
_flag		SINT ?
_file		SINT ?
if defined(_WIN64) or not defined(__UNIX__)
_charbuf	SINT ?
endif
_bufsiz		SINT ?
if defined(__UNIX__) and not defined(_WIN64)
_ungotten	dw ?
else
_tmpfname	LPTSTR ?
endif
_iobuf		ends
FILE		typedef _iobuf
LPFILE		typedef ptr _iobuf
endif

ifdef _CRTBLD
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
externdef __ptmbcinfo:pthreadmbcinfo
__updatetmbcinfo proto __cdecl
endif

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

ifndef _MBSTRING_DEFINED

if defined (_DEBUG) AND defined (_CRTDBG_MAP_ALLOC)
.pragma push_macro("_mbsdup")
undef _mbsdup
endif

_mbsdup proto __cdecl :string_t

if defined (_DEBUG) AND defined (_CRTDBG_MAP_ALLOC)
.pragma pop_macro("_mbsdup")
endif

_mbbtombc	proto __cdecl :uint_t
_mbbtombc_l	proto __cdecl :uint_t, :_locale_t
_mbbtype	proto __cdecl :uint_t, :int_t
_mbbtype_l	proto __cdecl :uint_t, :int_t, :_locale_t
_mbctombb	proto __cdecl :uint_t
_mbctombb_l	proto __cdecl :uint_t, :_locale_t
_mbsbtype	proto __cdecl :string_t, :size_t
_mbsbtype_l	proto __cdecl :string_t, :size_t, :_locale_t
_mbscat_s	proto __cdecl :string_t, :size_t, :string_t
_mbscat_s_l	proto __cdecl :string_t, :size_t, :string_t, :_locale_t
_mbschr		proto __cdecl :string_t, :uint_t
_mbschr_l	proto __cdecl :string_t, :uint_t, :_locale_t
_mbscmp		proto __cdecl :string_t, :string_t
_mbscmp_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbscoll	proto __cdecl :string_t, :string_t
_mbscoll_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbscpy_s	proto __cdecl :string_t, :size_t, :string_t
_mbscpy_s_l	proto __cdecl :string_t, :size_t, :string_t, :_locale_t
_mbscspn	proto __cdecl :string_t, :string_t
_mbscspn_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbsdec		proto __cdecl :string_t, :string_t
_mbsdec_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbsicmp	proto __cdecl :string_t, :string_t
_mbsicmp_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbsicoll	proto __cdecl :string_t, :string_t
_mbsicoll_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbsinc		proto __cdecl :string_t
_mbsinc_l	proto __cdecl :string_t, :_locale_t

endif  ;; _MBSTRING_DEFINED

_mbslen		proto __cdecl :string_t
_mbslen_l	proto __cdecl :string_t, :_locale_t
_mbsnlen	proto __cdecl :string_t, :size_t
_mbsnlen_l	proto __cdecl :string_t, :size_t, :_locale_t

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

_mbslwr_s	proto __cdecl :string_t, :size_t
_mbslwr_s_l	proto __cdecl :string_t, :size_t, :_locale_t
_mbsnbcat_s	proto __cdecl :string_t, :size_t, :string_t, :size_t
_mbsnbcat_s_l	proto __cdecl :string_t, :size_t, :string_t, :size_t, :_locale_t
_mbsnbcmp	proto __cdecl :string_t, :string_t, :size_t
_mbsnbcmp_l	proto __cdecl :string_t, :string_t, :size_t, :_locale_t
_mbsnbcoll	proto __cdecl :string_t, :string_t, :size_t
_mbsnbcoll_l	proto __cdecl :string_t, :string_t, :size_t, :_locale_t
_mbsnbcnt	proto __cdecl :string_t, :size_t
_mbsnbcnt_l	proto __cdecl :string_t, :size_t, :_locale_t
_mbsnbcpy_s	proto __cdecl :string_t, :size_t, :string_t, :size_t
_mbsnbcpy_s_l	proto __cdecl :string_t, :size_t, :string_t, :size_t, :_locale_t
_mbsnbicmp	proto __cdecl :string_t, :string_t, :size_t
_mbsnbicmp_l	proto __cdecl :string_t, :string_t, :size_t, :_locale_t
_mbsnbicoll	proto __cdecl :string_t, :string_t, :size_t
_mbsnbicoll_l	proto __cdecl :string_t, :string_t, :size_t, :_locale_t
_mbsnbset_s	proto __cdecl :string_t, :size_t, :uint_t, :size_t
_mbsnbset_s_l	proto __cdecl :string_t, :size_t, :uint_t, :size_t, :_locale_t
_mbsncat_s	proto __cdecl :string_t, :size_t, :string_t, :size_t
_mbsncat_s_l	proto __cdecl :string_t, :size_t, :string_t, :size_t, :_locale_t
_mbsnccnt	proto __cdecl :string_t, :size_t
_mbsnccnt_l	proto __cdecl :string_t, :size_t, :_locale_t
_mbsncmp	proto __cdecl :string_t, :string_t, :size_t
_mbsncmp_l	proto __cdecl :string_t, :string_t, :size_t, :_locale_t
_mbsncoll	proto __cdecl :string_t, :string_t, :size_t
_mbsncoll_l	proto __cdecl :string_t, :string_t, :size_t, :_locale_t
_mbsncpy_s	proto __cdecl :string_t, :size_t, :string_t, :size_t
_mbsncpy_s_l	proto __cdecl :string_t, :size_t, :string_t, :size_t, :_locale_t
_mbsnextc	proto __cdecl :string_t
_mbsnextc_l	proto __cdecl :string_t, :_locale_t
_mbsnicmp	proto __cdecl :string_t, :string_t, :size_t
_mbsnicmp_l	proto __cdecl :string_t, :string_t, :size_t, :_locale_t
_mbsnicoll	proto __cdecl :string_t, :string_t, :size_t
_mbsnicoll_l	proto __cdecl :string_t, :string_t, :size_t, :_locale_t
_mbsninc	proto __cdecl :string_t, :size_t
_mbsninc_l	proto __cdecl :string_t, :size_t, :_locale_t
_mbsnset_s	proto __cdecl :string_t, :size_t, :uint_t, :size_t
_mbsnset_s_l	proto __cdecl :string_t, :size_t, :uint_t, :size_t, :_locale_t
_mbspbrk	proto __cdecl :string_t, :string_t
_mbspbrk_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbsrchr	proto __cdecl :string_t, :uint_t
_mbsrchr_l	proto __cdecl :string_t, :uint_t, :_locale_t
_mbsrev		proto __cdecl :string_t
_mbsrev_l	proto __cdecl :string_t, :_locale_t
_mbsset_s	proto __cdecl :string_t, :size_t, :uint_t
_mbsset_s_l	proto __cdecl :string_t, :size_t, :uint_t, :_locale_t
_mbsspn		proto __cdecl :string_t, :string_t
_mbsspn_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbsspnp	proto __cdecl :string_t, :string_t
_mbsspnp_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbsstr		proto __cdecl :string_t, :string_t
_mbsstr_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbstok		proto __cdecl :string_t, :string_t
_mbstok_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbstok_s	proto __cdecl :string_t, :string_t, :ptr string_t
_mbstok_s_l	proto __cdecl :string_t, :string_t, :ptr string_t, :_locale_t
_mbsupr_s	proto __cdecl :string_t, :size_t
_mbsupr_s_l	proto __cdecl :string_t, :size_t, :_locale_t

endif  ;; _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

_mbclen		proto __cdecl :string_t
_mbclen_l	proto __cdecl :string_t, :_locale_t

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

_mbccpy		proto __cdecl :string_t, :string_t
_mbccpy_l	proto __cdecl :string_t, :string_t, :_locale_t
_mbccpy_s	proto __cdecl :string_t, :size_t, :ptr int_t, :string_t
_mbccpy_s_l	proto __cdecl :string_t, :size_t, :ptr int_t, :string_t, :_locale_t
_mbccmp macro _cpc1, _cpc2
	exitm<_mbsncmp((_cpc1),(_cpc2),1)>
	endm

;; character routines

_ismbcalnum	proto __cdecl :uint_t
_ismbcalnum_l	proto __cdecl :uint_t, :_locale_t
_ismbcalpha	proto __cdecl :uint_t
_ismbcalpha_l	proto __cdecl :uint_t, :_locale_t
_ismbcdigit	proto __cdecl :uint_t
_ismbcdigit_l	proto __cdecl :uint_t, :_locale_t
_ismbcgraph	proto __cdecl :uint_t
_ismbcgraph_l	proto __cdecl :uint_t, :_locale_t
_ismbclegal	proto __cdecl :uint_t
_ismbclegal_l	proto __cdecl :uint_t, :_locale_t
_ismbclower	proto __cdecl :uint_t
_ismbclower_l	proto __cdecl :uint_t, :_locale_t
_ismbcprint	proto __cdecl :uint_t
_ismbcprint_l	proto __cdecl :uint_t, :_locale_t
_ismbcpunct	proto __cdecl :uint_t
_ismbcpunct_l	proto __cdecl :uint_t, :_locale_t
_ismbcblank	proto __cdecl :uint_t
_ismbcblank_l	proto __cdecl :uint_t, :_locale_t
_ismbcspace	proto __cdecl :uint_t
_ismbcspace_l	proto __cdecl :uint_t, :_locale_t
_ismbcupper	proto __cdecl :uint_t
_ismbcupper_l	proto __cdecl :uint_t, :_locale_t

_mbctolower	proto __cdecl :uint_t
_mbctolower_l	proto __cdecl :uint_t, :_locale_t
_mbctoupper	proto __cdecl :uint_t
_mbctoupper_l	proto __cdecl :uint_t, :_locale_t

_MBSTRING_DEFINED equ 1
endif

ifndef _MBLEADTRAIL_DEFINED
define _MBLEADTRAIL_DEFINED
_ismbblead	proto __cdecl :uint_t
_ismbblead_l	proto __cdecl :uint_t, :_locale_t
_ismbbtrail	proto __cdecl :uint_t
_ismbbtrail_l	proto __cdecl :uint_t, :_locale_t
_ismbslead	proto __cdecl :string_t, :string_t
_ismbslead_l	proto __cdecl :string_t, :string_t, :_locale_t
_ismbstrail	proto __cdecl :string_t, :string_t
_ismbstrail_l	proto __cdecl :string_t, :string_t, :_locale_t
endif

;;  Kanji specific prototypes.

_ismbchira	proto __cdecl :uint_t
_ismbchira_l	proto __cdecl :uint_t, :_locale_t
_ismbckata	proto __cdecl :uint_t
_ismbckata_l	proto __cdecl :uint_t, :_locale_t
_ismbcsymbol	proto __cdecl :uint_t
_ismbcsymbol_l	proto __cdecl :uint_t, :_locale_t
_ismbcl0	proto __cdecl :uint_t
_ismbcl0_l	proto __cdecl :uint_t, :_locale_t
_ismbcl1	proto __cdecl :uint_t
_ismbcl1_l	proto __cdecl :uint_t, :_locale_t
_ismbcl2	proto __cdecl :uint_t
_ismbcl2_l	proto __cdecl :uint_t, :_locale_t
_mbcjistojms	proto __cdecl :uint_t
_mbcjistojms_l	proto __cdecl :uint_t, :_locale_t
_mbcjmstojis	proto __cdecl :uint_t
_mbcjmstojis_l	proto __cdecl :uint_t, :_locale_t
_mbctohira	proto __cdecl :uint_t
_mbctohira_l	proto __cdecl :uint_t, :_locale_t
_mbctokata	proto __cdecl :uint_t
_mbctokata_l	proto __cdecl :uint_t, :_locale_t

endif ;; _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

.pragma pack(pop)

endif ;; _INC_MBSTRING
