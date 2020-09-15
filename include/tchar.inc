ifndef _INC_TCHAR
_INC_TCHAR equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif

_ftcscat		equ <_tcscat>
_ftcschr		equ <_tcschr>
_ftcscpy		equ <_tcscpy>
_ftcscspn		equ <_tcscspn>
_ftcslen		equ <_tcslen>
_ftcsncat		equ <_tcsncat>
_ftcsncpy		equ <_tcsncpy>
_ftcspbrk		equ <_tcspbrk>
_ftcsrchr		equ <_tcsrchr>
_ftcsspn		equ <_tcsspn>
_ftcsstr		equ <_tcsstr>
_ftcstok		equ <_tcstok>

_ftcsdup		equ <_tcsdup>
_ftcsnset		equ <_tcsnset>
_ftcsrev		equ <_tcsrev>
_ftcsset		equ <_tcsset>

_ftcscmp		equ <_tcscmp>
_ftcsicmp		equ <_tcsicmp>
_ftcsnccmp		equ <_tcsnccmp>
_ftcsncmp		equ <_tcsncmp>
_ftcsncicmp		equ <_tcsncicmp>
_ftcsnicmp		equ <_tcsnicmp>

_ftcscoll		equ <_tcscoll>
_ftcsicoll		equ <_tcsicoll>
_ftcsnccoll		equ <_tcsnccoll>
_ftcsncoll		equ <_tcsncoll>
_ftcsncicoll		equ <_tcsncicoll>
_ftcsnicoll		equ <_tcsnicoll>


_ftcsclen		equ <_tcsclen>
_ftcsnccat		equ <_tcsnccat>
_ftcsnccpy		equ <_tcsnccpy>
_ftcsncset		equ <_tcsncset>

_ftcsdec		equ <_tcsdec>
_ftcsinc		equ <_tcsinc>
_ftcsnbcnt		equ <_tcsnbcnt>
_ftcsnccnt		equ <_tcsnccnt>
_ftcsnextc		equ <_tcsnextc>
_ftcsninc		equ <_tcsninc>
_ftcsspnp		equ <_tcsspnp>

_ftcslwr		equ <_tcslwr>
_ftcsupr		equ <_tcsupr>

_ftclen			equ <_tclen>
_ftccpy			equ <_tccpy>
_ftccmp			equ <_tccmp>


ifdef  _UNICODE

include wchar.inc

ifndef _WCTYPE_T_DEFINED
_WCTYPE_T_DEFINED equ <>
wint_t		typedef wchar_t
wctype_t	typedef wchar_t
endif

ifndef __TCHAR_DEFINED
__TCHAR_DEFINED equ <>
_TCHAR		typedef wchar_t
_TSCHAR		typedef wchar_t
_TUCHAR		typedef wchar_t
_TXCHAR		typedef wchar_t
_TINT		typedef wint_t
endif

ifndef _TCHAR_DEFINED
_TCHAR_DEFINED	equ <>
if NOT __STDC__
TCHAR		typedef wchar_t
endif
endif

_TEOF		equ WEOF
if 0
__T	macro x
%	exitm<L&x&>
	endm
endif


_tmain			equ <wmain>
_tWinMain		equ <wWinMain>
_tenviron		equ <_wenviron>
__targv			equ <__wargv>
_tgetmainargs		equ <__wgetmainargs>


;; Formatted i/o

_tprintf		equ <wprintf>
_tprintf_l		equ <_wprintf_l>
_tprintf_s		equ <wprintf_s>
_tprintf_s_l		equ <_wprintf_s_l>
_tprintf_p		equ <_wprintf_p>
_tprintf_p_l		equ <_wprintf_p_l>
_tcprintf		equ <_cwprintf>
_tcprintf_l		equ <_cwprintf_l>
_tcprintf_s		equ <_cwprintf_s>
_tcprintf_s_l		equ <_cwprintf_s_l>
_tcprintf_p		equ <_cwprintf_p>
_tcprintf_p_l		equ <_cwprintf_p_l>
_vtcprintf		equ <_vcwprintf>
_vtcprintf_l		equ <_vcwprintf_l>
_vtcprintf_s		equ <_vcwprintf_s>
_vtcprintf_s_l		equ <_vcwprintf_s_l>
_vtcprintf_p		equ <_vcwprintf_p>
_vtcprintf_p_l		equ <_vcwprintf_p_l>
_ftprintf		equ <fwprintf>
_ftprintf_l		equ <_fwprintf_l>
_ftprintf_s		equ <fwprintf_s>
_ftprintf_s_l		equ <_fwprintf_s_l>
_ftprintf_p		equ <_fwprintf_p>
_ftprintf_p_l		equ <_fwprintf_p_l>
_stprintf		equ <_swprintf>
_stprintf_l		equ <__swprintf_l>
_stprintf_s		equ <swprintf_s>
_stprintf_s_l		equ <_swprintf_s_l>
_stprintf_p		equ <_swprintf_p>
_stprintf_p_l		equ <_swprintf_p_l>
_sctprintf		equ <_scwprintf>
_sctprintf_l		equ <_scwprintf_l>
_sctprintf_p		equ <_scwprintf_p>
_sctprintf_p_l		equ <_scwprintf_p_l>
_sntprintf		equ <_snwprintf>
_sntprintf_l		equ <_snwprintf_l>
_sntprintf_s		equ <_snwprintf_s>
_sntprintf_s_l		equ <_snwprintf_s_l>
_vtprintf		equ <vwprintf>
_vtprintf_l		equ <_vwprintf_l>
_vtprintf_s		equ <vwprintf_s>
_vtprintf_s_l		equ <_vwprintf_s_l>
_vtprintf_p		equ <_vwprintf_p>
_vtprintf_p_l		equ <_vwprintf_p_l>
_vftprintf		equ <vfwprintf>
_vftprintf_l		equ <_vfwprintf_l>
_vftprintf_s		equ <vfwprintf_s>
_vftprintf_s_l		equ <_vfwprintf_s_l>
_vftprintf_p		equ <_vfwprintf_p>
_vftprintf_p_l		equ <_vfwprintf_p_l>
_vstprintf		equ <vswprintf>
_vstprintf_l		equ <_vswprintf_l>
_vstprintf_s		equ <vswprintf_s>
_vstprintf_s_l		equ <_vswprintf_s_l>
_vstprintf_p		equ <_vswprintf_p>
_vstprintf_p_l		equ <_vswprintf_p_l>
_vsctprintf		equ <_vscwprintf>
_vsctprintf_l		equ <_vscwprintf_l>
_vsctprintf_p		equ <_vscwprintf_p>
_vsctprintf_p_l		equ <_vscwprintf_p_l>
_vsntprintf		equ <_vsnwprintf>
_vsntprintf_l		equ <_vsnwprintf_l>
_vsntprintf_s		equ <_vsnwprintf_s>
_vsntprintf_s_l		equ <_vsnwprintf_s_l>

_tscanf			equ <wscanf>
_tscanf_l		equ <_wscanf_l>
_tscanf_s		equ <wscanf_s>
_tscanf_s_l		equ <_wscanf_s_l>
_tcscanf		equ <_cwscanf>
_tcscanf_l		equ <_cwscanf_l>
_tcscanf_s		equ <_cwscanf_s>
_tcscanf_s_l		equ <_cwscanf_s_l>
_ftscanf		equ <fwscanf>
_ftscanf_l		equ <_fwscanf_l>
_ftscanf_s		equ <fwscanf_s>
_ftscanf_s_l		equ <_fwscanf_s_l>
_stscanf		equ <swscanf>
_stscanf_l		equ <_swscanf_l>
_stscanf_s		equ <swscanf_s>
_stscanf_s_l		equ <_swscanf_s_l>
_sntscanf		equ <_snwscanf>
_sntscanf_l		equ <_snwscanf_l>
_sntscanf_s		equ <_snwscanf_s>
_sntscanf_s_l		equ <_snwscanf_s_l>
_vtscanf		equ <vwscanf>
_vtscanf_s		equ <vwscanf_s>
_vftscanf		equ <vfwscanf>
_vftscanf_s		equ <vfwscanf_s>
_vstscanf		equ <vswscanf>
_vstscanf_s		equ <vswscanf_s>

_tprintf		equ <wprintf>
_ftprintf		equ <fwprintf>
_stprintf		equ <swprintf>
_sntprintf		equ <_snwprintf>
_vtprintf		equ <vwprintf>
_vftprintf		equ <vfwprintf>
_vstprintf		equ <vswprintf>
_vsntprintf		equ <_vsnwprintf>
_tscanf			equ <wscanf>
_ftscanf		equ <fwscanf>
_stscanf		equ <swscanf>

;; Unformatted i/o

_fgettc			equ <fgetwc>
_fgettc_nolock		equ <_fgetwc_nolock>
_fgettchar		equ <_fgetwchar>
_fgetts			equ <fgetws>
_fputtc			equ <fputwc>
_fputtc_nolock		equ <_fputwc_nolock>
_fputtchar		equ <_fputwchar>
_fputts			equ <fputws>
_cputts			equ <_cputws>
_cgetts			equ <_cgetws>
_cgetts_s		equ <_cgetws_s>
_gettc			equ <getwc>
_gettc_nolock		equ <_getwc_nolock>
_gettch			equ <_getwch>
_gettch_nolock		equ <_getwch_nolock>
_gettche		equ <_getwche>
_gettche_nolock		equ <_getwche_nolock>
_gettchar		equ <getwchar>
_gettchar_nolock	equ <_getwchar_nolock>
_getts			equ <_getws>
_getts_s		equ <_getws_s>
_puttc			equ <putwc>
_puttc_nolock		equ <_putwc_nolock>
_puttchar		equ <putwchar>
_puttchar_nolock	equ <_putwchar_nolock>
_puttch			equ <_putwch>
_puttch_nolock		equ <_putwch_nolock>
_putts			equ <_putws>
_ungettc		equ <ungetwc>
_ungettc_nolock		equ <_ungetwc_nolock>
_ungettch		equ <_ungetwch>
_ungettch_nolock	equ <_ungetwch_nolock>

;; String conversion functions

_tcstod			equ <wcstod>
_tcstof			equ <wcstof>
_tcstol			equ <wcstol>
_tcstold		equ <wcstold>
_tcstoll		equ <wcstoll>
_tcstoul		equ <wcstoul>
_tcstoull		equ <wcstoull>
_tcstoimax		equ <wcstoimax>
_tcstoumax		equ <wcstoumax>
_tcstoi64		equ <_wcstoi64>
_tcstoui64		equ <_wcstoui64>
_ttof			equ <_wtof>
_tstof			equ <_wtof>
_tstol			equ <_wtol>
_tstoll			equ <_wtoll>
_tstoi			equ <_wtoi>
_tstoi64		equ <_wtoi64>
_tcstod_l		equ <_wcstod_l>
_tcstof_l		equ <_wcstof_l>
_tcstol_l		equ <_wcstol_l>
_tcstold_l		equ <_wcstold_l>
_tcstoll_l		equ <_wcstoll_l>
_tcstoul_l		equ <_wcstoul_l>
_tcstoull_l		equ <_wcstoull_l>
_tcstoi64_l		equ <_wcstoi64_l>
_tcstoui64_l		equ <_wcstoui64_l>
_tcstoimax_l		equ <_wcstoimax_l>
_tcstoumax_l		equ <_wcstoumax_l>
_tstof_l		equ <_wtof_l>
_tstol_l		equ <_wtol_l>
_tstoll_l		equ <_wtoll_l>
_tstoi_l		equ <_wtoi_l>
_tstoi64_l		equ <_wtoi64_l>

_itot_s			equ <_itow_s>
_ltot_s			equ <_ltow_s>
_ultot_s		equ <_ultow_s>
_itot			equ <_itow>
_ltot			equ <_ltow>
_ultot			equ <_ultow>
_ttoi			equ <_wtoi>
_ttol			equ <_wtol>

_ttoi64			equ <_wtoi64>
_i64tot_s		equ <_i64tow_s>
_ui64tot_s		equ <_ui64tow_s>
_i64tot			equ <_i64tow>
_ui64tot		equ <_ui64tow>

;; String functions

_tcscat			equ <wcscat>
_tcscat_s		equ <wcscat_s>
_tcschr			equ <wcschr>
_tcscpy			equ <wcscpy>
_tcscpy_s		equ <wcscpy_s>
_tcscspn		equ <wcscspn>
_tcslen			equ <wcslen>
_tcsncat		equ <wcsncat>
_tcsncat_s		equ <wcsncat_s>
_tcsncat_l		equ <_wcsncat_l>
_tcsncat_s_l		equ <_wcsncat_s_l>
_tcsncpy		equ <wcsncpy>
_tcsncpy_s		equ <wcsncpy_s>
_tcspbrk		equ <wcspbrk>
_tcsrchr		equ <wcsrchr>
_tcsspn			equ <wcsspn>
_tcsstr			equ <wcsstr>
_tcstok			equ <wcstok>
_tcstok_s		equ <wcstok_s>
_tcstok_l		equ <_wcstok_l>
_tcstok_s_l		equ <_wcstok_s_l>
_tcserror		equ <_wcserror>
_tcserror_s		equ <_wcserror_s>
__tcserror		equ <__wcserror>
__tcserror_s		equ <__wcserror_s>

_tcsdup			equ <_wcsdup>
_tcsnset		equ <_wcsnset>
_tcsrev			equ <_wcsrev>
_tcsset			equ <_wcsset>

_tcsdup			equ <_wcsdup>
_tcsnset		equ <_wcsnset>
_tcsnset_s		equ <_wcsnset_s>
_tcsnset_l		equ <_wcsnset_l>
_tcsnset_s_l		equ <_wcsnset_s_l>
_tcsrev			equ <_wcsrev>
_tcsset			equ <_wcsset>
_tcsset_s		equ <_wcsset_s>
_tcsset_l		equ <_wcsset_l>
_tcsset_s_l		equ <_wcsset_s_l>

_tcscmp			equ <wcscmp>
_tcsicmp		equ <_wcsicmp>
_tcsicmp_l		equ <_wcsicmp_l>
_tcsnccmp		equ <wcsncmp>
_tcsncmp		equ <wcsncmp>
_tcsncicmp		equ <_wcsnicmp>
_tcsncicmp_l		equ <_wcsnicmp_l>
_tcsnicmp		equ <_wcsnicmp>
_tcsnicmp_l		equ <_wcsnicmp_l>

_tcscoll		equ <wcscoll>
_tcscoll_l		equ <_wcscoll_l>
_tcsicoll		equ <_wcsicoll>
_tcsicoll_l		equ <_wcsicoll_l>
_tcsnccoll		equ <_wcsncoll>
_tcsnccoll_l		equ <_wcsncoll_l>
_tcsncoll		equ <_wcsncoll>
_tcsncoll_l		equ <_wcsncoll_l>
_tcsncicoll		equ <_wcsnicoll>
_tcsncicoll_l		equ <_wcsnicoll_l>
_tcsnicoll		equ <_wcsnicoll>
_tcsnicoll_l		equ <_wcsnicoll_l>

ifdef _DEBUG
_tcsdup_dbg		equ <_wcsdup_dbg>
endif

;; Execute functions

_texecl			equ <_wexecl>
_texecle		equ <_wexecle>
_texeclp		equ <_wexeclp>
_texeclpe		equ <_wexeclpe>
_texecv			equ <_wexecv>
_texecve		equ <_wexecve>
_texecvp		equ <_wexecvp>
_texecvpe		equ <_wexecvpe>

_tspawnl		equ <_wspawnl>
_tspawnle		equ <_wspawnle>
_tspawnlp		equ <_wspawnlp>
_tspawnlpe		equ <_wspawnlpe>
_tspawnv		equ <_wspawnv>
_tspawnve		equ <_wspawnve>
_tspawnvp		equ <_wspawnvp>
_tspawnvp		equ <_wspawnvp>
_tspawnvpe		equ <_wspawnvpe>

_tsystem		equ <_wsystem>

;; Time functions

_tasctime		equ <_wasctime>
_tctime			equ <_wctime>
_tctime32		equ <_wctime32>
_tctime64		equ <_wctime64>
_tstrdate		equ <_wstrdate>
_tstrtime		equ <_wstrtime>
_tutime			equ <_wutime>
_tutime32		equ <_wutime32>
_tutime64		equ <_wutime64>
_tcsftime		equ <wcsftime>
_tcsftime_l		equ <_wcsftime_l>

_tasctime_s		equ <_wasctime_s>
_tctime_s		equ <_wctime_s>
_tctime32_s		equ <_wctime32_s>
_tctime64_s		equ <_wctime64_s>
_tstrdate_s		equ <_wstrdate_s>
_tstrtime_s		equ <_wstrtime_s>

;; Directory functions

_tchdir			equ <_wchdir>
_tgetcwd		equ <_wgetcwd>
_tgetdcwd		equ <_wgetdcwd>
_tgetdcwd_nolock	equ <_wgetdcwd_nolock>
_tmkdir			equ <_wmkdir>
_trmdir			equ <_wrmdir>

ifdef _DEBUG
_tgetcwd_dbg		equ <_wgetcwd_dbg>
_tgetdcwd_dbg		equ <_wgetdcwd_dbg>
_tgetdcwd_lk_dbg	equ <_wgetdcwd_lk_dbg>
endif

;; Environment/Path functions

_tfullpath		equ <_wfullpath>
_tgetenv		equ <_wgetenv>
_tgetenv_s		equ <_wgetenv_s>
_tdupenv_s		equ <_wdupenv_s>
_tmakepath		equ <_wmakepath>
_tmakepath_s		equ <_wmakepath_s>
_tpgmptr		equ <_wpgmptr>
_get_tpgmptr		equ <_get_wpgmptr>
_tputenv		equ <_wputenv>
_tputenv_s		equ <_wputenv_s>
_tsearchenv		equ <_wsearchenv>
_tsearchenv_s		equ <_wsearchenv_s>
_tsplitpath		equ <_wsplitpath>
_tsplitpath_s		equ <_wsplitpath_s>

ifdef _DEBUG
_tfullpath_dbg		equ <_wfullpath_dbg>
_tdupenv_s_dbg		equ <_wdupenv_s_dbg>
endif

;; Stdio functions

_tfdopen		equ <_wfdopen>
_tfsopen		equ <_wfsopen>
_tfopen			equ <_wfopen>
_tfopen_s		equ <_wfopen_s>
_tfreopen		equ <_wfreopen>
_tfreopen_s		equ <_wfreopen_s>
_tperror		equ <_wperror>
_tpopen			equ <_wpopen>
_ttempnam		equ <_wtempnam>
_ttmpnam		equ <_wtmpnam>
_ttmpnam_s		equ <_wtmpnam_s>

ifdef _DEBUG
_ttempnam_dbg		equ <_wtempnam_dbg>
endif


;; Io functions

_taccess		equ <_waccess>
_taccess_s		equ <_waccess_s>
_tchmod			equ <_wchmod>
_tcreat			equ <_wcreat>
_tfindfirst		equ <_wfindfirst>
_tfindfirst32		equ <_wfindfirst32>
_tfindfirst64		equ <_wfindfirst64>
_tfindfirsti64		equ <_wfindfirsti64>
_tfindfirst32i64	equ <_wfindfirst32i64>
_tfindfirst64i32	equ <_wfindfirst64i32>
_tfindnext		equ <_wfindnext>
_tfindnext32		equ <_wfindnext32>
_tfindnext64		equ <_wfindnext64>
_tfindnexti64		equ <_wfindnexti64>
_tfindnext32i64		equ <_wfindnext32i64>
_tfindnext64i32		equ <_wfindnext64i32>
_tmktemp		equ <_wmktemp>
_tmktemp_s		equ <_wmktemp_s>
_topen			equ <_wopen>
_tremove		equ <_wremove>
_trename		equ <_wrename>
_tsopen			equ <_wsopen>
_tsopen_s		equ <_wsopen_s>
_tunlink		equ <_wunlink>

_tfinddata_t		equ <_wfinddata_t>
_tfinddata32_t		equ <_wfinddata32_t>
_tfinddata64_t		equ <_wfinddata64_t>
_tfinddatai64_t		equ <_wfinddatai64_t>
_tfinddata32i64_t	equ <_wfinddata32i64_t>
_tfinddata64i32_t	equ <_wfinddata64i32_t>


;; Stat functions

_tstat			equ <_wstat>
_tstat32		equ <_wstat32>
_tstat32i64		equ <_wstat32i64>
_tstat64		equ <_wstat64>
_tstat64i32		equ <_wstat64i32>
_tstati64		equ <_wstati64>

;; Setlocale functions

_tsetlocale		equ <_wsetlocale>


;; Redundant "logical-character" mappings

_tcsclen		equ <wcslen>
_tcscnlen		equ <wcsnlen>
_tcsclen_l macro _String, _Locale
	exitm<wcslen(_String)>
	endm
_tcscnlen_l macro _String, _Max_count, _Locale
	exitm<wcsnlen((_String), (_Max_count))>
	endm
_tcsnccat		equ <wcsncat>
_tcsnccat_s		equ <wcsncat_s>
_tcsnccat_l		equ <_wcsncat_l>
_tcsnccat_s_l		equ <_wcsncat_s_l>
_tcsnccpy		equ <wcsncpy>
_tcsnccpy_s		equ <wcsncpy_s>
_tcsnccpy_l		equ <_wcsncpy_l>
_tcsnccpy_s_l		equ <_wcsncpy_s_l>
_tcsncset		equ <_wcsnset>
_tcsncset_s		equ <_wcsnset_s>
_tcsncset_l		equ <_wcsnset_l>
_tcsncset_s_l		equ <_wcsnset_s_l>

_tcsdec			equ <_wcsdec>
_tcsinc			equ <_wcsinc>
_tcsnbcnt		equ <_wcsncnt>
_tcsnccnt		equ <_wcsncnt>
_tcsnextc		equ <_wcsnextc>
_tcsninc		equ <_wcsninc>
_tcsspnp		equ <_wcsspnp>

_tcslwr			equ <_wcslwr>
_tcslwr_l		equ <_wcslwr_l>
_tcslwr_s		equ <_wcslwr_s>
_tcslwr_s_l		equ <_wcslwr_s_l>
_tcsupr			equ <_wcsupr>
_tcsupr_l		equ <_wcsupr_l>
_tcsupr_s		equ <_wcsupr_s>
_tcsupr_s_l		equ <_wcsupr_s_l>
_tcsxfrm		equ <wcsxfrm>
_tcsxfrm_l		equ <_wcsxfrm_l>


if (__STDC__ OR defined(_NO_INLINING)) AND NOT defined(_M_M68K)
_tclen	macro _pc
	exitm<1>
	endm
_tccpy	macro _pc1,_cpc2
	movzx ax,[_cpc2]
	mov [_pc1],ax
	exitm<eax>
	endm
_tccmp	macro _cpc1,_cpc2
	mov ax,[_cpc1]
	sub ax,[_cpc2]
	movsx eax,ax
	exitm<eax>
	endm
else
_tclen proto WINAPI :ptr WORD
_tccpy proto WINAPI :ptr WORD, :ptr WORD
_tccmp proto WINAPI :ptr WORD, :ptr WORD
endif

;; ctype functions

_istalnum		equ <iswalnum>
_istalnum_l		equ <_iswalnum_l>
_istalpha		equ <iswalpha>
_istalpha_l		equ <_iswalpha_l>
_istascii		equ <iswascii>
_istcntrl		equ <iswcntrl>
_istcntrl_l		equ <_iswcntrl_l>
_istdigit		equ <iswdigit>
_istdigit_l		equ <_iswdigit_l>
_istgraph		equ <iswgraph>
_istgraph_l		equ <_iswgraph_l>
_istlower		equ <iswlower>
_istlower_l		equ <_iswlower_l>
_istprint		equ <iswprint>
_istprint_l		equ <_iswprint_l>
_istpunct		equ <iswpunct>
_istpunct_l		equ <_iswpunct_l>
_istblank		equ <iswblank>
_istblank_l		equ <_iswblank_l>
_istspace		equ <iswspace>
_istspace_l		equ <_iswspace_l>
_istupper		equ <iswupper>
_istupper_l		equ <_iswupper_l>
_istxdigit		equ <iswxdigit>
_istxdigit_l		equ <_iswxdigit_l>

_totupper		equ <towupper>
_totupper_l		equ <_towupper_l>
_totlower		equ <towlower>
_totlower_l		equ <_towlower_l>

_istlegal macro _c
	exitm<1>
	endm
_istlead macro _c
	exitm<0>
	endm
_istleadbyte macro _c
	exitm<0>
	endm
_istleadbyte_l macro _c, _L
	exitm<0>
	endm


if     (__STDC__ OR defined(_NO_INLINING)) AND NOT defined(_M_M68K)
_wcsdec macro _cpc1,_cpc2
	mov rax,_cpc1
	.if rax >= _cpc2
		xor rax,rax
	.else
		lea rax,[rdx-2]
	.endif
	exitm<rax>
	endm
_wcsinc macro _pc
	mov rax,_pc
	add rax,2
	exitm<rax>
	endm
_wcsnextc macro _cpc
	mov rax,_cpc
	movzx eax,word ptr [rax]
	exitm<eax>
	endm
_wcsninc macro _pc,_sz
	mov rax,_pc
	add rax,_sz
	add rax,_sz
	exitm<rax>
	endm
_wcsncnt macro _cpc,_sz
	.if wcslen(_cpc) > _sz
		mov rax,_sz
	.endif
	exitm<rax>
	endm
_wcsspnp macro _cpc1,_cpc2
	wcsspn(_cpc1,_cpc2)
	add rax,_cpc1
	.if word ptr [rax] == 0
		xor rax,rax
	.endif
	exitm<rax>
	endm
else
_wcsdec		proto :ptr wchar_t, :ptr wchar_t
_wcsinc		proto :ptr wchar_t
_wcsnextc	proto :ptr wchar_t
_wcsninc	proto :ptr wchar_t, :size_t
_wcsncnt	proto :ptr wchar_t, :size_t
_wcsspnp	proto :ptr wchar_t, :ptr wchar_t
endif


else


include string.inc

_TEOF			equ EOF

;__T	macro x

_tmain			equ <main>
_tWinMain		equ <WinMain>
ifdef  _POSIX_
_tenviron		equ <environ>
else
_tenviron		equ <_environ>
endif
__targv			equ <__argv>
_tgetmainargs		equ <__getmainargs>

;; Formatted i/o

_tprintf		equ <printf>
_tprintf_l		equ <_printf_l>
_tprintf_s		equ <printf_s>
_tprintf_s_l		equ <_printf_s_l>
_tprintf_p		equ <_printf_p>
_tprintf_p_l		equ <_printf_p_l>
_tcprintf		equ <_cprintf>
_tcprintf_l		equ <_cprintf_l>
_tcprintf_s		equ <_cprintf_s>
_tcprintf_s_l		equ <_cprintf_s_l>
_tcprintf_p		equ <_cprintf_p>
_tcprintf_p_l		equ <_cprintf_p_l>
_vtcprintf		equ <_vcprintf>
_vtcprintf_l		equ <_vcprintf_l>
_vtcprintf_s		equ <_vcprintf_s>
_vtcprintf_s_l		equ <_vcprintf_s_l>
_vtcprintf_p		equ <_vcprintf_p>
_vtcprintf_p_l		equ <_vcprintf_p_l>
_ftprintf		equ <fprintf>
_ftprintf_l		equ <_fprintf_l>
_ftprintf_s		equ <fprintf_s>
_ftprintf_s_l		equ <_fprintf_s_l>
_ftprintf_p		equ <_fprintf_p>
_ftprintf_p_l		equ <_fprintf_p_l>
_stprintf		equ <sprintf>
_stprintf_l		equ <_sprintf_l>
_stprintf_s		equ <sprintf_s>
_stprintf_s_l		equ <_sprintf_s_l>
_stprintf_p		equ <_sprintf_p>
_stprintf_p_l		equ <_sprintf_p_l>
_sctprintf		equ <_scprintf>
_sctprintf_l		equ <_scprintf_l>
_sctprintf_p		equ <_scprintf_p>
_sctprintf_p_l		equ <_scprintf_p_l>
_sntprintf		equ <_snprintf>
_sntprintf_l		equ <_snprintf_l>
_sntprintf_s		equ <_snprintf_s>
_sntprintf_s_l		equ <_snprintf_s_l>
_vtprintf		equ <vprintf>
_vtprintf_l		equ <_vprintf_l>
_vtprintf_s		equ <vprintf_s>
_vtprintf_s_l		equ <_vprintf_s_l>
_vtprintf_p		equ <_vprintf_p>
_vtprintf_p_l		equ <_vprintf_p_l>
_vftprintf		equ <vfprintf>
_vftprintf_l		equ <_vfprintf_l>
_vftprintf_s		equ <vfprintf_s>
_vftprintf_s_l		equ <_vfprintf_s_l>
_vftprintf_p		equ <_vfprintf_p>
_vftprintf_p_l		equ <_vfprintf_p_l>
_vstprintf		equ <vsprintf>
_vstprintf_l		equ <_vsprintf_l>
_vstprintf_s		equ <vsprintf_s>
_vstprintf_s_l		equ <_vsprintf_s_l>
_vstprintf_p		equ <_vsprintf_p>
_vstprintf_p_l		equ <_vsprintf_p_l>
_vsctprintf		equ <_vscprintf>
_vsctprintf_l		equ <_vscprintf_l>
_vsctprintf_p		equ <_vscprintf_p>
_vsctprintf_p_l		equ <_vscprintf_p_l>
_vsntprintf		equ <_vsnprintf>
_vsntprintf_l		equ <_vsnprintf_l>
_vsntprintf_s		equ <_vsnprintf_s>
_vsntprintf_s_l		equ <_vsnprintf_s_l>

_tscanf			equ <scanf>
_tscanf_l		equ <_scanf_l>
_tscanf_s		equ <scanf_s>
_tscanf_s_l		equ <_scanf_s_l>
_tcscanf		equ <_cscanf>
_tcscanf_l		equ <_cscanf_l>
_tcscanf_s		equ <_cscanf_s>
_tcscanf_s_l		equ <_cscanf_s_l>
_ftscanf		equ <fscanf>
_ftscanf_l		equ <_fscanf_l>
_ftscanf_s		equ <fscanf_s>
_ftscanf_s_l		equ <_fscanf_s_l>
_stscanf		equ <sscanf>
_stscanf_l		equ <_sscanf_l>
_stscanf_s		equ <sscanf_s>
_stscanf_s_l		equ <_sscanf_s_l>
_sntscanf		equ <_snscanf>
_sntscanf_l		equ <_snscanf_l>
_sntscanf_s		equ <_snscanf_s>
_sntscanf_s_l		equ <_snscanf_s_l>
_vtscanf		equ <vscanf>
_vtscanf_s		equ <vscanf_s>
_vftscanf		equ <vfscanf>
_vftscanf_s		equ <vfscanf_s>
_vstscanf		equ <vsscanf>
_vstscanf_s		equ <vsscanf_s>


;; Unformatted i/o

_fgettc			equ <fgetc>
_fgettc_nolock		equ <_fgetc_nolock>
_fgettchar		equ <_fgetchar>
_fgetts			equ <fgets>
_fputtc			equ <fputc>
_fputtc_nolock		equ <_fputc_nolock>
_fputtchar		equ <_fputchar>
_fputts			equ <fputs>
_cputts			equ <_cputs>
_gettc			equ <getc>
_gettc_nolock		equ <_getc_nolock>
_gettch			equ <_getch>
_gettch_nolock		equ <_getch_nolock>
_gettche		equ <_getche>
_gettche_nolock		equ <_getche_nolock>
_gettchar		equ <getchar>
_gettchar_nolock	equ <_getchar_nolock>
_getts			equ <gets>
_getts_s		equ <gets_s>
_cgetts			equ <_cgets>
_cgetts_s		equ <_cgets_s>
_puttc			equ <putc>
_puttc_nolock		equ <_putc_nolock>
_puttchar		equ <putchar>
_puttchar_nolock	equ <_putchar_nolock>
_puttch			equ <_putch>
_puttch_nolock		equ <_putch_nolock>
_putts			equ <puts>
_ungettc		equ <ungetc>
_ungettc_nolock		equ <_ungetc_nolock>
_ungettch		equ <_ungetch>
_ungettch_nolock	equ <_ungetch_nolock>

;; String conversion functions

_tcstod			equ <strtod>
_tcstof			equ <strtof>
_tcstol			equ <strtol>
_tcstold		equ <strtold>
_tcstoll		equ <strtoll>
_tcstoul		equ <strtoul>
_tcstoull		equ <strtoull>
_tcstoimax		equ <strtoimax>
_tcstoumax		equ <strtoumax>
_ttof			equ <atof>
_tstof			equ <atof>
_tstol			equ <atol>
_tstoll			equ <atoll>
_tstoi			equ <atoi>
_tstoi64		equ <_atoi64>
_tcstod_l		equ <_strtod_l>
_tcstof_l		equ <_strtof_l>
_tcstol_l		equ <_strtol_l>
_tcstold_l		equ <_strtold_l>
_tcstoll_l		equ <_strtoll_l>
_tcstoul_l		equ <_strtoul_l>
_tcstoull_l		equ <_strtoull_l>
_tcstoimax_l		equ <_strtoimax_l>
_tcstoumax_l		equ <_strtoumax_l>
_tstof_l		equ <_atof_l>
_tstol_l		equ <_atol_l>
_tstoll_l		equ <_atoll_l>
_tstoi_l		equ <_atoi_l>
_tstoi64_l		equ <_atoi64_l>

_itot_s			equ <_itoa_s>
_ltot_s			equ <_ltoa_s>
_ultot_s		equ <_ultoa_s>
_itot			equ <_itoa>
_ltot			equ <_ltoa>
_ultot			equ <_ultoa>
_ttoi			equ <atoi>
_ttol			equ <atol>
_ttoll			equ <atoll>

_ttoi64			equ <_atoi64>
_tcstoi64		equ <_strtoi64>
_tcstoi64_l		equ <_strtoi64_l>
_tcstoui64		equ <_strtoui64>
_tcstoui64_l		equ <_strtoui64_l>
_i64tot_s		equ <_i64toa_s>
_ui64tot_s		equ <_ui64toa_s>
_i64tot			equ <_i64toa>
_ui64tot		equ <_ui64toa>

;; String functions

;; Note that _mbscat, _mbscpy and _mbsdup are functionally equivalent to
;; strcat, strcpy and strdup, respectively.

_tcscat			equ <strcat>
_tcscat_s		equ <strcat_s>
_tcscpy			equ <strcpy>
_tcscpy_s		equ <strcpy_s>
_tcsdup			equ <_strdup>
_tcslen			equ <strlen>
_tcsnlen		equ <strnlen>
_tcsxfrm		equ <strxfrm>
_tcsxfrm_l		equ <_strxfrm_l>
_tcserror		equ <strerror>
_tcserror_s		equ <strerror_s>
__tcserror		equ <_strerror>
__tcserror_s		equ <_strerror_s>

ifdef _DEBUG
_tcsdup_dbg		equ <_strdup_dbg>
endif

;; Execute functions

_texecl			equ <_execl>
_texecle		equ <_execle>
_texeclp		equ <_execlp>
_texeclpe		equ <_execlpe>
_texecv			equ <_execv>
_texecve		equ <_execve>
_texecvp		equ <_execvp>
_texecvpe		equ <_execvpe>

_tspawnl		equ <_spawnl>
_tspawnle		equ <_spawnle>
_tspawnlp		equ <_spawnlp>
_tspawnlpe		equ <_spawnlpe>
_tspawnv		equ <_spawnv>
_tspawnve		equ <_spawnve>
_tspawnvp		equ <_spawnvp>
_tspawnvpe		equ <_spawnvpe>

_tsystem		equ <system>

;; Time functions

_tasctime		equ <asctime>
_tctime			equ <ctime>
_tctime32		equ <_ctime32>
_tctime64		equ <_ctime64>
_tstrdate		equ <_strdate>
_tstrtime		equ <_strtime>
_tutime			equ <_utime>
_tutime32		equ <_utime32>
_tutime64		equ <_utime64>
_tcsftime		equ <strftime>
_tcsftime_l		equ <_strftime_l>

_tasctime_s		equ <asctime_s>
_tctime_s		equ <ctime_s>
_tctime32_s		equ <_ctime32_s>
_tctime64_s		equ <_ctime64_s>
_tstrdate_s		equ <_strdate_s>
_tstrtime_s		equ <_strtime_s>

;; Directory functions

_tchdir			equ <_chdir>
_tgetcwd		equ <_getcwd>
_tgetdcwd		equ <_getdcwd>
_tgetdcwd_nolock	equ <_getdcwd_nolock>
_tmkdir			equ <_mkdir>
_trmdir			equ <_rmdir>

ifdef _DEBUG
_tgetcwd_dbg		equ <_getcwd_dbg>
_tgetdcwd_dbg		equ <_getdcwd_dbg>
_tgetdcwd_lk_dbg	equ <_getdcwd_lk_dbg>
endif

;; Environment/Path functions

_tfullpath		equ <_fullpath>
_tgetenv		equ <getenv>
_tgetenv_s		equ <getenv_s>
_tdupenv_s		equ <_dupenv_s>
_tmakepath		equ <_makepath>
_tmakepath_s		equ <_makepath_s>
_tpgmptr		equ <_pgmptr>
_get_tpgmptr		equ <_get_pgmptr>
_tputenv		equ <_putenv>
_tputenv_s		equ <_putenv_s>
_tsearchenv		equ <_searchenv>
_tsearchenv_s		equ <_searchenv_s>
_tsplitpath		equ <_splitpath>
_tsplitpath_s		equ <_splitpath_s>

ifdef _DEBUG
_tfullpath_dbg		equ <_fullpath_dbg>
_tdupenv_s_dbg		equ <_dupenv_s_dbg>
endif

;; Stdio functions

_tfdopen		equ <_fdopen>
_tfsopen		equ <_fsopen>
_tfopen			equ <fopen>
_tfopen_s		equ <fopen_s>
_tfreopen		equ <freopen>
_tfreopen_s		equ <freopen_s>
_tperror		equ <perror>
_tpopen			equ <_popen>
_ttempnam		equ <_tempnam>
_ttmpnam		equ <tmpnam>
_ttmpnam_s		equ <tmpnam_s>

ifdef _DEBUG
_ttempnam_dbg		equ <_tempnam_dbg>
endif


;; Io functions

_tchmod			equ <_chmod>
_tcreat			equ <_creat>
_tfindfirst		equ <_findfirst>
_tfindfirst32		equ <_findfirst32>
_tfindfirst64		equ <_findfirst64>
_tfindfirsti64		equ <_findfirsti64>
_tfindfirst32i64	equ <_findfirst32i64>
_tfindfirst64i32	equ <_findfirst64i32>
_tfindnext		equ <_findnext>
_tfindnext32		equ <_findnext32>
_tfindnext64		equ <_findnext64>
_tfindnexti64		equ <_findnexti64>
_tfindnext32i64		equ <_findnext32i64>
_tfindnext64i32		equ <_findnext64i32>
_tmktemp		equ <_mktemp>
_tmktemp_s		equ <_mktemp_s>

_topen			equ <_open>
_taccess		equ <_access>
_taccess_s		equ <_access_s>

_tremove		equ <remove>
_trename		equ <rename>
_tsopen			equ <_sopen>
_tsopen_s		equ <_sopen_s>
_tunlink		equ <_unlink>

_tfinddata_t		equ <_finddata_t>
_tfinddata32_t		equ <_finddata32_t>
_tfinddata64_t		equ <__finddata64_t>
_tfinddatai64_t		equ <_finddatai64_t>
_tfinddata32i64_t	equ <_finddata32i64_t>
_tfinddata64i32_t	equ <_finddata64i32_t>

;; ctype functions

_istascii		equ <__isascii>
_istcntrl		equ <iscntrl>
_istcntrl_l		equ <_iscntrl_l>
_istxdigit		equ <isxdigit>
_istxdigit_l		equ <_isxdigit_l>

;; Stat functions

_tstat			equ <_stat>
_tstat32		equ <_stat32>
_tstat32i64		equ <_stat32i64>
_tstat64		equ <_stat64>
_tstat64i32		equ <_stat64i32>
_tstati64		equ <_stati64>


;; Setlocale functions

_tsetlocale		equ <setlocale>

ifdef  _MBCS

include mbstring.inc

ifndef __TCHAR_DEFINED
_TCHAR			typedef sbyte
_TSCHAR			typedef sbyte
_TUCHAR			typedef byte
_TXCHAR			typedef byte
_TINT			typedef dword
__TCHAR_DEFINED		equ 1
endif

ifndef _TCHAR_DEFINED
if NOT __STDC__
TCHAR			typedef sbyte
endif
_TCHAR_DEFINED		equ 1
endif


ifdef  _MB_MAP_DIRECT

_tcschr			equ <_mbschr>
_tcscspn		equ <_mbscspn>
_tcsncat		equ <_mbsnbcat>
_tcsncpy		equ <_mbsnbcpy>
_tcspbrk		equ <_mbspbrk>
_tcsrchr		equ <_mbsrchr>
_tcsspn			equ <_mbsspn>
_tcsstr			equ <_mbsstr>
_tcstok			equ <_mbstok>

_tcsnset		equ <_mbsnbset>
_tcsrev			equ <_mbsrev>
_tcsset			equ <_mbsset>

_tcscmp			equ <_mbscmp>
_tcsicmp		equ <_mbsicmp>
_tcsnccmp		equ <_mbsncmp>
_tcsncmp		equ <_mbsnbcmp>
_tcsncicmp		equ <_mbsnicmp>
_tcsnicmp		equ <_mbsnbicmp>

_tcscoll		equ <_mbscoll>
_tcsicoll		equ <_mbsicoll>
_tcsnccoll		equ <_mbsncoll>
_tcsncoll		equ <_mbsnbcoll>
_tcsncicoll		equ <_mbsnicoll>
_tcsnicoll		equ <_mbsnbicoll>

_tcsclen		equ <_mbslen>
_tcsnccat		equ <_mbsncat>
_tcsnccpy		equ <_mbsncpy>
_tcsncset		equ <_mbsnset>

_tcsdec			equ <_mbsdec>
_tcsinc			equ <_mbsinc>
_tcsnbcnt		equ <_mbsnbcnt>
_tcsnccnt		equ <_mbsnccnt>
_tcsnextc		equ <_mbsnextc>
_tcsninc		equ <_mbsninc>
_tcsspnp		equ <_mbsspnp>

_tcslwr			equ <_mbslwr>
_tcsupr			equ <_mbsupr>

_tclen			equ <_mbclen>
_tccpy			equ <_mbccpy>

_tccmp macro _cpuc1,_cpuc2
	exitm<_tcsnccmp(_cpuc1,_cpuc2,1)>
	endm

else

_PUC			equ ptr byte
_CPUC			equ ptr byte
_PC			equ ptr sbyte
_CPC			equ ptr sbyte
_UI			equ dword

if     (__STDC__ OR defined(_NO_INLINING)) AND NOT defined(_M_M68K)

_tcschr		proto WINAPI :_CPC, :_UI
_tcscspn	proto WINAPI :_CPC, :_CPC
_tcsncat	proto WINAPI :_PC, :_CPC, :size_t
_tcsncpy	proto WINAPI :_PC, :_CPC, :size_t
_tcspbrk	proto WINAPI :_CPC, :_CPC
_tcsrchr	proto WINAPI :_CPC, :_UI
_tcsspn		proto WINAPI :_CPC, :_CPC
_tcsstr		proto WINAPI :_CPC, :_CPC
_tcstok		proto WINAPI :_PC, :_CPC
_tcsnset	proto WINAPI :_PC, :_UI, :size_t
_tcsrev		proto WINAPI :_PC
_tcsset		proto WINAPI :_PC, :_UI
_tcscmp		proto WINAPI :_CPC, :_CPC
_tcsicmp	proto WINAPI :_CPC, :_CPC
_tcsnccmp	proto WINAPI :_CPC, :_CPC, :size_t
_tcsncmp	proto WINAPI :_CPC, :_CPC, :size_t
_tcsncicmp	proto WINAPI :_CPC, :_CPC, :size_t
_tcsnicmp	proto WINAPI :_CPC, :_CPC, :size_t
_tcscoll	proto WINAPI :_CPC, :_CPC
_tcsicoll	proto WINAPI :_CPC, :_CPC
_tcsnccoll	proto WINAPI :_CPC, :_CPC, :size_t
_tcsncoll	proto WINAPI :_CPC, :_CPC, :size_t
_tcsncicoll	proto WINAPI :_CPC, :_CPC, :size_t
_tcsnicoll	proto WINAPI :_CPC, :_CPC, :size_t


_tcsclen	proto WINAPI :_CPC
_tcsnccat	proto WINAPI :_PC, :_CPC, :size_t
_tcsnccpy	proto WINAPI :_PC, :_CPC, :size_t
_tcsncset	proto WINAPI :_PC, :_UI, :size_t


_tcsdec		proto WINAPI :_CPC, :_CPC
_tcsinc		proto WINAPI :_CPC
_tcsnbcnt	proto WINAPI :_CPC, :size_t
_tcsnccnt	proto WINAPI :_CPC, :size_t
_tcsninc	proto WINAPI :_CPC, :size_t
_tcsspnp	proto WINAPI :_CPC, :_CPC
_tcslwr		proto WINAPI :_PC
_tcsupr		proto WINAPI :_PC
_tclen		proto WINAPI :_CPC
_tccpy		proto WINAPI :_PC, :_CPC
_tcsnextc	proto WINAPI :_CPC

else



_tcschr macro _s1,_c
	exitm<_mbschr(_s1,_c)>
	endm
_tcscspn macro _s1,_c
	exitm<_mbscspn(_s1,_s2)>
	endm
_tcsncat macro _s1,_s2,_n
	exitm<_mbsnbcat(_s1,_s2,_n)>
	endm
_tcsncpy macro _s1,_s2,_n
	exitm<_mbsnbcpy(_s1,_s2,_n)>
	endm
_tcspbrk macro _s1,_s2
	exitm<_mbspbrk(_s1,_s2)>
	endm
_tcsrchr macro _s1,_c
	exitm<_mbsrchr(_s1,_c)>
	endm
_tcsspn macro _s1,_s2
	exitm<_mbsspn(_s1,_s2)>
	endm
_tcsstr macro _s1,_s2
	exitm<_mbsstr(_s1,_s2)>
	endm
_tcstok macro _s1,_s2,_n
	exitm<_mbstok(_s1,_s2)>
	endm

_tcsnset macro _s1,_c,_n
	exitm<_mbsnbset(_s1,_c,_n)>
	endm
_tcsrev macro _s1
	exitm<_mbsrev(_s1)>
	endm
_tcsset macro _s1
	exitm<_mbsset(_s1,_c)>
	endm

_tcscmp macro _s1,_s2
	exitm<_mbscmp(_s1,_s2)>
	endm
_tcsicmp macro _s1,_s2
	exitm<_mbsicmp(_s1,_s2)>
	endm
_tcsnccmp macro _s1,_s2,_n
	exitm<_mbsncmp(_s1,_s2,_n)>
	endm
_tcsncmp macro _s1,_s2,_n
	exitm<_mbsnbcmp(_s1,_s2,_n)>
	endm
_tcsncicmp macro _s1,_s2,_n
	exitm<_mbsnicmp(_s1,_s2,_n)>
	endm
_tcsnicmp macro _s1,_s2,_n
	exitm<_mbsnbicmp(_s1,_s2,_n)>
	endm

_tcscoll macro _s1,_s2
	exitm<_mbscoll(_s1,_s2)>
	endm
_tcsicoll macro _s1,_s2
	exitm<_mbsicoll(_s1,_s2)>
	endm
_tcsnccoll macro _s1,_s2,_n
	exitm<_mbsncoll(_s1,_s2,_n)>
	endm
_tcsncoll macro _s1,_s2,_n
	exitm<_mbsnbcoll(_s1,_s2,_n)>
	endm
_tcsncicoll macro _s1,_s2,_n
	exitm<_mbsnicoll(_s1,_s2,_n)>
	endm
_tcsnicoll macro _s1,_s2,_n
	exitm<_mbsnbicoll(_s1,_s2,_n)>
	endm

_tcsclen macro _s1,_s2
	exitm<_mbslen(_s1)>
	endm
_tcsnccat macro _s1,_s2,_n
	exitm<_mbsncat(_s1,_s2,_n)>
	endm
_tcsnccpy macro _s1,_s2,_n
	exitm<_mbsncpy(_s1,_s2,_n)>
	endm
_tcsncset macro _s1,_c,_n
	exitm<_mbsnset(_s1,_c,_n)>
	endm

_tcsdec macro _s1,_s2
	exitm<_mbsdec(_s1,_s2)>
	endm
_tcsinc macro _s1
	exitm<_mbsinc(_s1)>
	endm
_tcsnbcnt macro _s1,_n
	exitm<_mbsnbcnt(_s1,_n)>
	endm
_tcsnccnt macro _s1,_n
	exitm<_mbsnccnt(_s1,_n)>
	endm
_tcsninc macro _s1,_n
	exitm<_mbsninc(_s1,_n)>
	endm
_tcsspnp macro _s1,_s2
	exitm<_mbsspnp(_s1,_s2)>
	endm
_tcslwr macro _s1
	exitm<_mbslwr(_s1)>
	endm
_tcsupr macro _s1
	exitm<_mbsupr(_s1)>
	endm
_tclen macro _s1
	exitm<_mbclen(_s1)>
	endm
_tccpy macro _s1,_s2
	_mbccpy(_s1,_s2)
	endm

_tcsnextc macro _s1
	mov rax,_s1
	movzx eax,byte ptr [rax]
	.if _ismbblead(eax)
		mov ah,[_s1]
		add _s1,1
		mov al,[_s1]
	.endif
	exitm<eax>
	endm

endif

endif

_tccmp macro _cp1,_cp2
	exitm<_tcsnccmp(_cp1,_cp2,1)>
	endm



_istalnum		equ <_ismbcalnum>
_istalpha		equ <_ismbcalpha>
_istdigit		equ <_ismbcdigit>
_istgraph		equ <_ismbcgraph>
_istlegal		equ <_ismbclegal>
_istlower		equ <_ismbclower>
_istprint		equ <_ismbcprint>
_istpunct		equ <_ismbcpunct>
_istspace		equ <_ismbcspace>
_istupper		equ <_ismbcupper>

_totupper		equ <_mbctoupper>
_totlower		equ <_mbctolower>

_istlead		equ <_ismbblead>
_istleadbyte		equ <isleadbyte>

else

ifndef __TCHAR_DEFINED
__TCHAR_DEFINED equ <>
_TCHAR			typedef sbyte
_TSCHAR			typedef sbyte
_TUCHAR			typedef byte
_TXCHAR			typedef sbyte
_TINT			typedef sdword
endif

ifndef _TCHAR_DEFINED
_TCHAR_DEFINED equ <>
if NOT __STDC__
TCHAR			typedef sbyte
endif
endif

ifdef _MB_MAP_DIRECT

;; use mb functions directly - types must match

;; String functions

_tcschr			equ <_mbschr>
_tcscspn		equ <_mbscspn>
_tcsncat		equ <_mbsnbcat>
_tcsncat_s		equ <_mbsnbcat_s>
_tcsncat_l		equ <_mbsnbcat_l>
_tcsncat_s_l		equ <_mbsnbcat_s_l>
_tcsncpy		equ <_mbsnbcpy>
_tcsncpy_s		equ <_mbsnbcpy_s>
_tcsncpy_l		equ <_mbsnbcpy_l>
_tcsncpy_s_l		equ <_mbsnbcpy_s_l>
_tcspbrk		equ <_mbspbrk>
_tcsrchr		equ <_mbsrchr>
_tcsspn			equ <_mbsspn>
_tcsstr			equ <_mbsstr>
_tcstok			equ <_mbstok>
_tcstok_s		equ <_mbstok_s>
_tcstok_l		equ <_mbstok_l>
_tcstok_s_l		equ <_mbstok_s_l>

_tcsnset		equ <_mbsnbset>
_tcsnset_l		equ <_mbsnbset_l>
_tcsnset_s		equ <_mbsnbset_s>
_tcsnset_s_l		equ <_mbsnbset_s_l>
_tcsrev			equ <_mbsrev>
_tcsset			equ <_mbsset>
_tcsset_s		equ <_mbsset_s>
_tcsset_l		equ <_mbsset_l>
_tcsset_s_l		equ <_mbsset_s_l>

_tcscmp			equ <_mbscmp>
_tcsicmp		equ <_mbsicmp>
_tcsicmp_l		equ <_mbsicmp_l>
_tcsnccmp		equ <_mbsncmp>
_tcsncmp		equ <_mbsnbcmp>
_tcsncicmp		equ <_mbsnicmp>
_tcsncicmp_l		equ <_mbsnicmp_l>
_tcsnicmp		equ <_mbsnbicmp>
_tcsnicmp_l		equ <_mbsnbicmp_l>

_tcscoll		equ <_mbscoll>
_tcscoll_l		equ <_mbscoll_l>
_tcsicoll		equ <_mbsicoll>
_tcsicoll_l		equ <_mbsicoll_l>
_tcsnccoll		equ <_mbsncoll>
_tcsnccoll_l		equ <_mbsncoll_l>
_tcsncoll		equ <_mbsnbcoll>
_tcsncoll_l		equ <_mbsnbcoll_l>
_tcsncicoll		equ <_mbsnicoll>
_tcsncicoll_l		equ <_mbsnicoll_l>
_tcsnicoll		equ <_mbsnbicoll>
_tcsnicoll_l		equ <_mbsnbicoll_l>

;; "logical-character" mappings

_tcsclen		equ <_mbslen>
_tcscnlen		equ <_mbsnlen>
_tcsclen_l		equ <_mbslen_l>
_tcscnlen_l		equ <_mbsnlen_l>
_tcsnccat		equ <_mbsncat>
_tcsnccat_s		equ <_mbsncat_s>
_tcsnccat_l		equ <_mbsncat_l>
_tcsnccat_s_l		equ <_mbsncat_s_l>
_tcsnccpy		equ <_mbsncpy>
_tcsnccpy_s		equ <_mbsncpy_s>
_tcsnccpy_l		equ <_mbsncpy_l>
_tcsnccpy_s_l		equ <_mbsncpy_s_l>
_tcsncset		equ <_mbsnset>
_tcsncset_s		equ <_mbsnset_s>
_tcsncset_l		equ <_mbsnset_l>
_tcsncset_s_l		equ <_mbsnset_s_l>

;; MBCS-specific mappings

_tcsdec			equ <_mbsdec>
_tcsinc			equ <_mbsinc>
_tcsnbcnt		equ <_mbsnbcnt>
_tcsnccnt		equ <_mbsnccnt>
_tcsnextc		equ <_mbsnextc>
_tcsninc		equ <_mbsninc>
_tcsspnp		equ <_mbsspnp>

_tcslwr			equ <_mbslwr>
_tcslwr_l		equ <_mbslwr_l>
_tcslwr_s		equ <_mbslwr_s>
_tcslwr_s_l		equ <_mbslwr_s_l>
_tcsupr			equ <_mbsupr>
_tcsupr_l		equ <_mbsupr_l>
_tcsupr_s		equ <_mbsupr_s>
_tcsupr_s_l		equ <_mbsupr_s_l>

_tclen			equ <_mbclen>
_tccpy			equ <_mbccpy>
_tccpy_l		equ <_mbccpy_l>
_tccpy_s		equ <_mbccpy_s>
_tccpy_s_l		equ <_mbccpy_s_l>

else ;; _MB_MAP_DIRECT

;; String functions

_tcschr			equ <strchr>
_tcscspn		equ <strcspn>
_tcsncat		equ <strncat>
_tcsncat_s		equ <strncat_s>
_tcsncat_l		equ <_strncat_l>
_tcsncat_s_l		equ <_strncat_s_l>
_tcsncpy		equ <strncpy>
_tcsncpy_s		equ <strncpy_s>
_tcsncpy_l		equ <_strncpy_l>
_tcsncpy_s_l		equ <_strncpy_s_l>
_tcspbrk		equ <strpbrk>
_tcsrchr		equ <strrchr>
_tcsspn			equ <strspn>
_tcsstr			equ <strstr>
_tcstok			equ <strtok>
_tcstok_s		equ <strtok_s>
_tcstok_l		equ <_strtok_l>
_tcstok_s_l		equ <_strtok_s_l>

_tcsnset		equ <_strnset>
_tcsnset_s		equ <_strnset_s>
_tcsnset_l		equ <_strnset_l>
_tcsnset_s_l		equ <_strnset_s_l>
_tcsrev			equ <_strrev>
_tcsset			equ <_strset>
_tcsset_s		equ <_strset_s>
_tcsset_l		equ <_strset_l>
_tcsset_s_l		equ <_strset_s_l>

_tcscmp			equ <strcmp>
_tcsicmp		equ <_stricmp>
_tcsicmp_l		equ <_stricmp_l>
_tcsnccmp		equ <strncmp>
_tcsncmp		equ <strncmp>
_tcsncicmp		equ <_strnicmp>
_tcsncicmp_l		equ <_strnicmp_l>
_tcsnicmp		equ <_strnicmp>
_tcsnicmp_l		equ <_strnicmp_l>

_tcscoll		equ <strcoll>
_tcscoll_l		equ <_strcoll_l>
_tcsicoll		equ <_stricoll>
_tcsicoll_l		equ <_stricoll_l>
_tcsnccoll		equ <_strncoll>
_tcsnccoll_l		equ <_strncoll_l>
_tcsncoll		equ <_strncoll>
_tcsncoll_l		equ <_strncoll_l>
_tcsncicoll		equ <_strnicoll>
_tcsncicoll_l		equ <_strnicoll_l>
_tcsnicoll		equ <_strnicoll>
_tcsnicoll_l		equ <_strnicoll_l>

;; "logical-character" mappings

_tcsclen		equ <strlen>
_tcscnlen		equ <strnlen>
_tcsclen_l macro _String, _Locale
	exitm<strlen(_String)>
	endm
_tcscnlen_l macro _String, _Max_count, _Locale
	exitm<strnlen((_String), (_Max_count))>
	endm
_tcsnccat		equ <strncat>
_tcsnccat_s		equ <strncat_s>
_tcsnccat_l		equ <_strncat_l>
_tcsnccat_s_l		equ <_strncat_s_l>
_tcsnccpy		equ <strncpy>
_tcsnccpy_s		equ <strncpy_s>
_tcsnccpy_l		equ <_strncpy_l>
_tcsnccpy_s_l		equ <_strncpy_s_l>
_tcsncset		equ <_strnset>
_tcsncset_s		equ <_strnset_s>
_tcsncset_l		equ <_strnset_l>
_tcsncset_s_l		equ <_strnset_s_l>

;; MBCS-specific functions

_tcsdec			equ <_strdec>
_tcsinc			equ <_strinc>
_tcsnbcnt		equ <_strncnt>
_tcsnccnt		equ <_strncnt>
_tcsnextc		equ <_strnextc>
_tcsninc		equ <_strninc>
_tcsspnp		equ <_strspnp>

_tcslwr			equ <_strlwr>
_tcslwr_l		equ <_strlwr_l>
_tcslwr_s		equ <_strlwr_s>
_tcslwr_s_l		equ <_strlwr_s_l>
_tcsupr			equ <_strupr>
_tcsupr_l		equ <_strupr_l>
_tcsupr_s		equ <_strupr_s>
_tcsupr_s_l		equ <_strupr_s_l>
_tcsxfrm		equ <strxfrm>
_tcsxfrm_l		equ <_strxfrm_l>

_istlead macro _c
	exitm<(0)>
	endm
_istleadbyte macro _c
	exitm<(0)>
	endm
_istleadbyte_l macro _c
	exitm<(0)>
	endm

if (__STDC__ OR defined(_NO_INLINING)) AND NOT defined(_M_M68K)
_tclen macro _pc
	exitm<1>
	endm
_tccpy macro _pc1,_cpc2
	mov rax,_pc2
	mov rdx,_pc1
	movzx eax,[rax]
	mov [rdx],al
	exitm<eax>
	endm
_tccmp macro _cpc1,_cpc2
	mov rax,_pc2
	mov rdx,_pc1
	movzx eax,[rax]
	movzx edx,[rdx]
	sub eax,edx
	exitm<eax>
	endm

else
_tclen proto WINAPI :ptr SBYTE
_tccpy proto WINAPI :ptr SBYTE, :ptr SBYTE
_tccmp proto WINAPI :ptr SBYTE, :ptr SBYTE
endif

endif ;; _MB_MAP_DIRECT

;; ctype-functions

_istalnum		equ <isalnum>
_istalnum_l		equ <_isalnum_l>
_istalpha		equ <isalpha>
_istalpha_l		equ <_isalpha_l>
_istdigit		equ <isdigit>
_istdigit_l		equ <_isdigit_l>
_istgraph		equ <isgraph>
_istgraph_l		equ <_isgraph_l>
_istlower		equ <islower>
_istlower_l		equ <_islower_l>
_istprint		equ <isprint>
_istprint_l		equ <_isprint_l>
_istpunct		equ <ispunct>
_istpunct_l		equ <_ispunct_l>
_istblank		equ <isblank>
_istblank_l		equ <_isblank_l>
_istspace		equ <isspace>
_istspace_l		equ <_isspace_l>
_istupper		equ <isupper>
_istupper_l		equ <_isupper_l>

_totupper		equ <toupper>
_totupper_l		equ <_toupper_l>
_totlower		equ <tolower>
_totlower_l		equ <_tolower_l>

_istlegal macro _c
	exitm<(1)>
	endm

ifndef NULL
NULL equ 0
endif

if     (__STDC__ OR defined(_NO_INLINING)) AND NOT defined(_M_M68K)
_strdec macro _cpc1,_cpc2
	mov rax,_cpc1
	.if rax >= _cpc2
		xor rax,rax
	.else
		lea rax,[rdx-1]
	.endif
	exitm<rax>
	endm
_strinc macro _pc
	mov rax,_pc
	add rax,1
	exitm<rax>
	endm
_strnextc macro _cpc
	mov rax,_cpc
	movzx eax,byte ptr [rax]
	exitm<eax>
	endm
_strninc macro _pc,_sz
	mov rax,_pc
	add rax,_sz
	exitm<rax>
	endm
_strncnt macro _cpc,_sz
	.if strlen(_cpc) > _sz
		mov rax,_sz
	.endif
	exitm<rax>
	endm
_strspnp macro _cpc1,_cpc2
	strspn(_cpc1,_cpc2)
	add rax,_cpc1
	.if byte ptr [rax] == 0
		xor rax,rax
	.endif
	exitm<rax>
	endm
else
_strdec		proto :ptr SBYTE, :ptr SBYTE
_strinc		proto :ptr SBYTE
_strnextc	proto :ptr SBYTE
_strninc	proto :ptr SBYTE, :size_t
_strncnt	proto :ptr SBYTE, :size_t
_strspnp	proto :ptr SBYTE, :ptr SBYTE
endif

endif
endif


if 0
_T	macro x
	exitm<__T(x)>
	endm
_TEXT	macro x
	exitm<__T(x)>
	endm
endif

ifndef _WIN64
ifndef _REGS6432
    rax equ <eax>
    rbx equ <ebx>
    rcx equ <ecx>
    rdx equ <edx>
    rdi equ <edi>
    rsi equ <esi>
    rbp equ <ebp>
    rsp equ <esp>
_REGS6432 equ 1
endif
endif

ifdef __PE__

ifdef _WIN64
option	win64:3
endif

ifndef _M_CEE_PURE

ifdef __GUI__

	.code

mainCRTStartup proc

    mov rbx,GetModuleHandle(0)
    ExitProcess(_tWinMain(rbx, 0, GetCommandLine(), SW_SHOWDEFAULT))

else

ifndef __STDLIB_INC
include stdlib.inc
endif

	.data
	_startup  db 128 dup(0)
	__argc	  int_t 0,0
  ifdef _UNICODE
	__targv	  warray_t 0
	_tenviron warray_t 0
  else
	__targv	  array_t 0
	_tenviron array_t 0
  endif
	.code

mainCRTStartup proc

	.if !_tgetmainargs( addr __argc, addr __targv, addr _tenviron, 0, addr _startup )
		mov	ecx,__argc
ifdef	_WIN64
		mov	rdx,__targv
		mov	r8,_tenviron
else
		mov	edx,__targv
		mov	ebx,_tenviron
		push	ebx
		push	edx
		push	ecx
endif
		_tmain()
	.endif

	exit(eax)

endif ; __GUI__

mainCRTStartup endp

_tstart equ <mainCRTStartup>

else

_tstart equ <>

endif ; _M_CEE_PURE
endif ; __PE__

.pragma list(pop)
endif
