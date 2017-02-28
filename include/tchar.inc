;
; definitions for generic international text functions
;
ifndef _INC_TCHAR
_INC_TCHAR equ 1

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

;; Redundant "logical-character" mappings

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

;; ++++++++++++++++++++ UNICODE ++++++++++++++++++++

include wchar.inc

ifndef _WCTYPE_T_DEFINED
wint_t			typedef wchar_t
wctype_t		typedef wchar_t
_WCTYPE_T_DEFINED	equ 1
endif

ifndef __TCHAR_DEFINED
_TCHAR			typedef wchar_t
_TSCHAR			typedef wchar_t
_TUCHAR			typedef wchar_t
_TXCHAR			typedef wchar_t
_TINT			typedef wint_t
__TCHAR_DEFINED		equ 1
endif

ifndef _TCHAR_DEFINED
if NOT __STDC__
TCHAR			typedef wchar_t
endif
_TCHAR_DEFINED		equ 1
endif

_TEOF			equ WEOF
if 0
__T	macro x
%	exitm<L&x&>
	endm
endif

;; Program

_tmain			equ <wmain>
_tWinMain		equ <wWinMain>
_tenviron		equ <_wenviron>
__targv			equ <__wargv>

;; Formatted i/o

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
_fgettchar		equ <_fgetwchar>
_fgetts			equ <fgetws>
_fputtc			equ <fputwc>
_fputtchar		equ <_fputwchar>
_fputts			equ <fputws>
_gettc			equ <getwc>
_gettchar		equ <getwchar>
_getts			equ <_getws>
_puttc			equ <putwc>
_puttchar		equ <putwchar>
_putts			equ <_putws>
_ungettc		equ <ungetwc>


;; String conversion functions

_tcstod			equ <wcstod>
_tcstol			equ <wcstol>
_tcstoul		equ <wcstoul>

_itot			equ <_itow>
_ltot			equ <_ltow>
_ultot			equ <_ultow>
_ttoi			equ <_wtoi>
_ttol			equ <_wtol>

_ttoi64			equ <_wtoi64>
_i64tot			equ <_i64tow>
_ui64tot		equ <_ui64tow>

;; String functions

_tcscat			equ <wcscat>
_tcschr			equ <wcschr>
_tcscpy			equ <wcscpy>
_tcscspn		equ <wcscspn>
_tcslen			equ <wcslen>
_tcsncat		equ <wcsncat>
_tcsncpy		equ <wcsncpy>
_tcspbrk		equ <wcspbrk>
_tcsrchr		equ <wcsrchr>
_tcsspn			equ <wcsspn>
_tcsstr			equ <wcsstr>
_tcstok			equ <wcstok>

_tcsdup			equ <_wcsdup>
_tcsnset		equ <_wcsnset>
_tcsrev			equ <_wcsrev>
_tcsset			equ <_wcsset>

_tcscmp			equ <wcscmp>
_tcsicmp		equ <_wcsicmp>
_tcsnccmp		equ <wcsncmp>
_tcsncmp		equ <wcsncmp>
_tcsncicmp		equ <_wcsnicmp>
_tcsnicmp		equ <_wcsnicmp>

_tcscoll		equ <wcscoll>
_tcsicoll		equ <_wcsicoll>
_tcsnccoll		equ <_wcsncoll>
_tcsncoll		equ <_wcsncoll>
_tcsncicoll		equ <_wcsnicoll>
_tcsnicoll		equ <_wcsnicoll>


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
_tstrdate		equ <_wstrdate>
_tstrtime		equ <_wstrtime>
_tutime			equ <_wutime>
_tcsftime		equ <wcsftime>


;; Directory functions

_tchdir			equ <_wchdir>
_tgetcwd		equ <_wgetcwd>
_tgetdcwd		equ <_wgetdcwd>
_tmkdir			equ <_wmkdir>
_trmdir			equ <_wrmdir>


;; Environment/Path functions

_tfullpath		equ <_wfullpath>
_tgetenv		equ <_wgetenv>
_tmakepath		equ <_wmakepath>
_tputenv		equ <_wputenv>
_tsearchenv		equ <_wsearchenv>
_tsplitpath		equ <_wsplitpath>


;; Stdio functions

_tfdopen		equ <_wfdopen>
_tfsopen		equ <_wfsopen>
_tfopen			equ <_wfopen>
_tfreopen		equ <_wfreopen>
_tperror		equ <_wperror>
_tpopen			equ <_wpopen>
_ttempnam		equ <_wtempnam>
_ttmpnam		equ <_wtmpnam>


;; Io functions

_taccess		equ <_waccess>
_tchmod			equ <_wchmod>
_tcreat			equ <_wcreat>
_tfindfirst		equ <_wfindfirst>
_tfindfirsti64		equ <_wfindfirsti64>
_tfindnext		equ <_wfindnext>
_tfindnexti64		equ <_wfindnexti64>
_tmktemp		equ <_wmktemp>
_topen			equ <_wopen>
_tremove		equ <_wremove>
_trename		equ <_wrename>
_tsopen			equ <_wsopen>
_tunlink		equ <_wunlink>

_tfinddata_t		equ <_wfinddata_t>
_tfinddatai64_t		equ <_wfinddatai64_t>


;; Stat functions

_tstat			equ <_wstat>
_tstati64		equ <_wstati64>


;; Setlocale functions

_tsetlocale		equ <_wsetlocale>


;; Redundant "logical-character" mappings

_tcsclen		equ <wcslen>
_tcsnccat		equ <wcsncat>
_tcsnccpy		equ <wcsncpy>
_tcsncset		equ <_wcsnset>

_tcsdec			equ <_wcsdec>
_tcsinc			equ <_wcsinc>
_tcsnbcnt		equ <_wcsncnt>
_tcsnccnt		equ <_wcsncnt>
_tcsnextc		equ <_wcsnextc>
_tcsninc		equ <_wcsninc>
_tcsspnp		equ <_wcsspnp>

_tcslwr			equ <_wcslwr>
_tcsupr			equ <_wcsupr>
_tcsxfrm		equ <wcsxfrm>


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
else   ;; __STDC__
_tclen proto _CType :ptr WORD
_tccpy proto _CType :ptr WORD, :ptr WORD
_tccmp proto _CType :ptr WORD, :ptr WORD
endif  ;; __STDC__


;; ctype functions

_istalnum		equ <iswalnum>
_istalpha		equ <iswalpha>
_istascii		equ <iswascii>
_istcntrl		equ <iswcntrl>
_istdigit		equ <iswdigit>
_istgraph		equ <iswgraph>
_istlower		equ <iswlower>
_istprint		equ <iswprint>
_istpunct		equ <iswpunct>
_istspace		equ <iswspace>
_istupper		equ <iswupper>
_istxdigit		equ <iswxdigit>

_totupper		equ <towupper>
_totlower		equ <towlower>

_istlegal macro _c
	exitm<1>
	endm
_istlead macro _c
	exitm<0>
	endm
_istleadbyte macro _c
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
else   ;; __STDC__
_wcsdec		proto :ptr wchar_t, :ptr wchar_t
_wcsinc		proto :ptr wchar_t
_wcsnextc	proto :ptr wchar_t
_wcsninc	proto :ptr wchar_t, :size_t
_wcsncnt	proto :ptr wchar_t, :size_t
_wcsspnp	proto :ptr wchar_t, :ptr wchar_t
endif  ;; __STDC__


else   ;; ndef _UNICODE

;; ++++++++++++++++++++ SBCS and MBCS ++++++++++++++++++++

include string.inc

_TEOF			equ EOF

;__T	macro x
;	exitm<x>
;	endm


;; Program

_tmain			equ <main>
_tWinMain		equ <WinMain>
ifdef  _POSIX_
_tenviron		equ <environ>
else
_tenviron		equ <_environ>
endif
__targv			equ <__argv>


;; Formatted i/o

_tprintf		equ <printf>
_ftprintf		equ <fprintf>
_stprintf		equ <sprintf>
_sntprintf		equ <_snprintf>
_vtprintf		equ <vprintf>
_vftprintf		equ <vfprintf>
_vstprintf		equ <vsprintf>
_vsntprintf		equ <_vsnprintf>
_tscanf			equ <scanf>
_ftscanf		equ <fscanf>
_stscanf		equ <sscanf>


;; Unformatted i/o

_fgettc			equ <fgetc>
_fgettchar		equ <_fgetchar>
_fgetts			equ <fgets>
_fputtc			equ <fputc>
_fputtchar		equ <_fputchar>
_fputts			equ <fputs>
_gettc			equ <getc>
_gettchar		equ <getchar>
_getts			equ <gets>
_puttc			equ <putc>
_puttchar		equ <putchar>
_putts			equ <puts>
_ungettc		equ <ungetc>


;; String conversion functions

_tcstod			equ <strtod>
_tcstol			equ <strtol>
_tcstoul		equ <strtoul>

_itot			equ <_itoa>
_ltot			equ <_ltoa>
_ultot			equ <_ultoa>
_ttoi			equ <atoi>
_ttol			equ <atol>

_ttoi64			equ <_atoi64>
_i64tot			equ <_i64toa>
_ui64tot		equ <_ui64toa>

;; String functions

;; Note that _mbscat, _mbscpy and _mbsdup are functionally equivalent to
;; strcat, strcpy and strdup, respectively.

_tcscat			equ <strcat>
_tcscpy			equ <strcpy>
_tcsdup			equ <_strdup>

_tcslen			equ <strlen>
_tcsxfrm		equ <strxfrm>


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
_tstrdate		equ <_strdate>
_tstrtime		equ <_strtime>
_tutime			equ <_utime>
_tcsftime		equ <strftime>


;; Directory functions

_tchdir			equ <_chdir>
_tgetcwd		equ <_getcwd>
_tgetdcwd		equ <_getdcwd>
_tmkdir			equ <_mkdir>
_trmdir			equ <_rmdir>


;; Environment/Path functions

_tfullpath		equ <_fullpath>
_tgetenv		equ <getenv>
_tmakepath		equ <_makepath>
_tputenv		equ <_putenv>
_tsearchenv		equ <_searchenv>
_tsplitpath		equ <_splitpath>


;; Stdio functions

ifdef  _POSIX_
_tfdopen		equ <fdopen>
else
_tfdopen		equ <_fdopen>
endif
_tfsopen		equ <_fsopen>
_tfopen			equ <fopen>
_tfreopen		equ <freopen>
_tperror		equ <perror>
_tpopen			equ <_popen>
_ttempnam		equ <_tempnam>
_ttmpnam		equ <tmpnam>


;; Io functions

_tchmod			equ <_chmod>
_tcreat			equ <_creat>
_tfindfirst		equ <_findfirst>
_tfindfirsti64		equ <_findfirsti64>
_tfindnext		equ <_findnext>
_tfindnexti64		equ <_findnexti64>
_tmktemp		equ <_mktemp>

ifdef  _POSIX_
_topen			equ <open>
_taccess		equ <access>
else
_topen			equ <_open>
_taccess		equ <_access>
endif

_tremove		equ <remove>
_trename		equ <rename>
_tsopen			equ <_sopen>
_tunlink		equ <_unlink>

_tfinddata_t		equ <_finddata_t>
_tfinddatai64_t		equ <_finddatai64_t>


;; ctype functions

_istascii		equ <isascii>
_istcntrl		equ <iscntrl>
_istxdigit		equ <isxdigit>


;; Stat functions

_tstat			equ <_stat>
_tstati64		equ <_stati64>


;; Setlocale functions

_tsetlocale		equ <setlocale>


ifdef  _MBCS

;; ++++++++++++++++++++ MBCS ++++++++++++++++++++

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

;; use mb functions directly - types must match

;; String functions

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


;; "logical-character" mappings

_tcsclen		equ <_mbslen>
_tcsnccat		equ <_mbsncat>
_tcsnccpy		equ <_mbsncpy>
_tcsncset		equ <_mbsnset>


;; MBCS-specific mappings

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


else ;; _MB_MAP_DIRECT

_PUC			equ ptr byte
_CPUC			equ ptr byte
_PC			equ ptr sbyte
_CPC			equ ptr sbyte
_UI			equ dword

if     (__STDC__ OR defined(_NO_INLINING)) AND NOT defined(_M_M68K)

;; use type-safe linked-in function thunks

;; String functions

_tcschr		proto _CType :_CPC, :_UI
_tcscspn	proto _CType :_CPC, :_CPC
_tcsncat	proto _CType :_PC, :_CPC, :size_t
_tcsncpy	proto _CType :_PC, :_CPC, :size_t
_tcspbrk	proto _CType :_CPC, :_CPC
_tcsrchr	proto _CType :_CPC, :_UI
_tcsspn		proto _CType :_CPC, :_CPC
_tcsstr		proto _CType :_CPC, :_CPC
_tcstok		proto _CType :_PC, :_CPC
_tcsnset	proto _CType :_PC, :_UI, :size_t
_tcsrev		proto _CType :_PC
_tcsset		proto _CType :_PC, :_UI
_tcscmp		proto _CType :_CPC, :_CPC
_tcsicmp	proto _CType :_CPC, :_CPC
_tcsnccmp	proto _CType :_CPC, :_CPC, :size_t
_tcsncmp	proto _CType :_CPC, :_CPC, :size_t
_tcsncicmp	proto _CType :_CPC, :_CPC, :size_t
_tcsnicmp	proto _CType :_CPC, :_CPC, :size_t
_tcscoll	proto _CType :_CPC, :_CPC
_tcsicoll	proto _CType :_CPC, :_CPC
_tcsnccoll	proto _CType :_CPC, :_CPC, :size_t
_tcsncoll	proto _CType :_CPC, :_CPC, :size_t
_tcsncicoll	proto _CType :_CPC, :_CPC, :size_t
_tcsnicoll	proto _CType :_CPC, :_CPC, :size_t

;; "logical-character" mappings

_tcsclen	proto _CType :_CPC
_tcsnccat	proto _CType :_PC, :_CPC, :size_t
_tcsnccpy	proto _CType :_PC, :_CPC, :size_t
_tcsncset	proto _CType :_PC, :_UI, :size_t

;; MBCS-specific mappings

_tcsdec		proto _CType :_CPC, :_CPC
_tcsinc		proto _CType :_CPC
_tcsnbcnt	proto _CType :_CPC, :size_t
_tcsnccnt	proto _CType :_CPC, :size_t
_tcsninc	proto _CType :_CPC, :size_t
_tcsspnp	proto _CType :_CPC, :_CPC
_tcslwr		proto _CType :_PC
_tcsupr		proto _CType :_PC
_tclen		proto _CType :_CPC
_tccpy		proto _CType :_PC, :_CPC
_tcsnextc	proto _CType :_CPC

else   ;; __STDC__

;; the default: use type-safe inline function thunks

;; String functions

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


;; "logical-character" mappings

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


;; MBCS-specific mappings

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


;; inline helper
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

endif  ;; __STDC__

endif  ;; _MB_MAP_DIRECT


;; MBCS-specific mappings

_tccmp macro _cp1,_cp2
	exitm<_tcsnccmp(_cp1,_cp2,1)>
	endm


;; ctype functions

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

else   ;; NOT _MBCS

;; ++++++++++++++++++++ SBCS ++++++++++++++++++++


ifndef __TCHAR_DEFINED
_TCHAR			typedef sbyte
_TSCHAR			typedef sbyte
_TUCHAR			typedef byte
_TXCHAR			typedef sbyte
_TINT			typedef sdword
__TCHAR_DEFINED		equ 1
endif

ifndef _TCHAR_DEFINED
if NOT __STDC__
TCHAR			typedef sbyte
endif
_TCHAR_DEFINED		equ 1
endif


;; String functions

_tcschr			equ <strchr>
_tcscspn		equ <strcspn>
_tcsncat		equ <strncat>
_tcsncpy		equ <strncpy>
_tcspbrk		equ <strpbrk>
_tcsrchr		equ <strrchr>
_tcsspn			equ <strspn>
_tcsstr			equ <strstr>
_tcstok			equ <strtok>

_tcsnset		equ <_strnset>
_tcsrev			equ <_strrev>
_tcsset			equ <_strset>

_tcscmp			equ <strcmp>
_tcsicmp		equ <_stricmp>
_tcsnccmp		equ <strncmp>
_tcsncmp		equ <strncmp>
_tcsncicmp		equ <_strnicmp>
_tcsnicmp		equ <_strnicmp>

_tcscoll		equ <strcoll>
_tcsicoll		equ <_stricoll>
_tcsnccoll		equ <_strncoll>
_tcsncoll		equ <_strncoll>
_tcsncicoll		equ <_strnicoll>
_tcsnicoll		equ <_strnicoll>


;; "logical-character" mappings

_tcsclen		equ <strlen>
_tcsnccat		equ <strncat>
_tcsnccpy		equ <strncpy>
_tcsncset		equ <_strnset>


;; MBCS-specific functions

_tcsdec			equ <_strdec>
_tcsinc			equ <_strinc>
_tcsnbcnt		equ <_strncnt>
_tcsnccnt		equ <_strncnt>
_tcsnextc		equ <_strnextc>
_tcsninc		equ <_strninc>
_tcsspnp		equ <_strspnp>

_tcslwr			equ <_strlwr>
_tcsupr			equ <_strupr>
_tcsxfrm		equ <strxfrm>

_istlead macro _c
	exitm<(0)>
	endm
_istleadbyte macro _c
	exitm<(0)>
	endm

if     (__STDC__ OR defined(_NO_INLINING)) AND NOT defined(_M_M68K)
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

else   ;; __STDC__
_tclen proto _CType :ptr SBYTE
_tccpy proto _CType :ptr SBYTE, :ptr SBYTE
_tccmp proto _CType :ptr SBYTE, :ptr SBYTE
endif  ;; __STDC__


;; ctype-functions

_istalnum		equ <isalnum>
_istalpha		equ <isalpha>
_istdigit		equ <isdigit>
_istgraph		equ <isgraph>
_istlower		equ <islower>
_istprint		equ <isprint>
_istpunct		equ <ispunct>
_istspace		equ <isspace>
_istupper		equ <isupper>

_totupper		equ <toupper>
_totlower		equ <tolower>

_istlegal macro _c
	exitm<(1)>
	endm


;; the following is optional if functional versions are available

;; define NULL pointer value

ifndef NULL
NULL			equ 0
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
else   ;; __STDC__
_strdec		proto :ptr SBYTE, :ptr SBYTE
_strinc		proto :ptr SBYTE
_strnextc	proto :ptr SBYTE
_strninc	proto :ptr SBYTE, :size_t
_strncnt	proto :ptr SBYTE, :size_t
_strspnp	proto :ptr SBYTE, :ptr SBYTE
endif  ;; __STDC__


endif  ;; _MBCS
endif  ;; _UNICODE


;; Generic text macros to be used with string literals and character constants.
;; Will also allow symbolic constants that resolve to same.
if 0
_T	macro x
	exitm<__T(x)>
	endm
_TEXT	macro x
	exitm<__T(x)>
	endm
endif
endif  ;; _INC_TCHAR
