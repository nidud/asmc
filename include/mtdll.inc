.pragma list(push, 0)
ifndef _INC_MTDLL
define _INC_MTDLL

include crtdefs.inc
include limits.inc

.pragma pack(push, _CRT_PACKING)

include windows.inc

_IOB_ENTRIES		equ 20

_SIGNAL_LOCK		equ 0
_IOB_SCAN_LOCK		equ 1
_TMPNAM_LOCK		equ 2
_CONIO_LOCK		equ 3
_HEAP_LOCK		equ 4
_UNDNAME_LOCK		equ 5
_TIME_LOCK		equ 6
_ENV_LOCK		equ 7
_EXIT_LOCK1		equ 8
_POPEN_LOCK		equ 9
_LOCKTAB_LOCK		equ 10
_OSFHND_LOCK		equ 11
_SETLOCALE_LOCK		equ 12
_MB_CP_LOCK		equ 13
_TYPEINFO_LOCK		equ 14
_DEBUG_LOCK		equ 15

_STREAM_LOCKS		equ 16

_LAST_STREAM_LOCK	equ (_STREAM_LOCKS+_IOB_ENTRIES-1)
_TOTAL_LOCKS		equ (_LAST_STREAM_LOCK+1)
_LOCK_BIT_INTS		equ (_TOTAL_LOCKS/(uint_t*8))+1

ifndef __assembler

__TRY			equ <>;__try{
__FINALLY		equ <>;}__finally{
__END_TRY_FINALLY	equ <>;}

ifndef _THREADMBCINFO
define _THREADMBCINFO
threadmbcinfo		STRUC
refcount		SINT ?
mbcodepage		SINT ?
ismbcodepage		SINT ?
mbulinfo		dw 6 dup(?)
mbctype			db 257 dup(?)
mbcasemap		db 256 dup(?)
mblocalename		LPWSTR ?
threadmbcinfo		ENDS
pthreadmbcinfo		typedef ptr threadmbcinfo
endif

MAX_LANG_LEN		equ 64
MAX_CTRY_LEN		equ 64
MAX_MODIFIER_LEN	equ 0
MAX_LC_LEN		equ (MAX_LANG_LEN+MAX_CTRY_LEN+MAX_MODIFIER_LEN+3)
MAX_CP_LEN		equ 16
CATNAMES_LEN		equ 57

LC_INT_TYPE		equ 0
LC_STR_TYPE		equ 1
LC_WSTR_TYPE		equ 2

ifndef _SETLOC_STRUCT_DEFINED
define _SETLOC_STRUCT_DEFINED
_is_ctype_compatible	STRUC
id			dd ?
is_clike		SINT ?
_is_ctype_compatible	ENDS

_setloc_struct		STRUC
pchLanguage		LPWSTR ?
pchCountry		LPWSTR ?
iLocState		SINT ?
iPrimaryLen		SINT ?
bAbbrevLanguage		BOOL ?
bAbbrevCountry		BOOL ?
_cachecp		UINT ?
_cachein		wchar_t MAX_LC_LEN dup(?)
_cacheout		wchar_t MAX_LC_LEN dup(?)
_Loc_c			_is_ctype_compatible 5 dup(<>)
_cacheLocaleName	wchar_t LOCALE_NAME_MAX_LENGTH dup(?)
_setloc_struct		ENDS
_psetloc_struct		typedef ptr _setloc_struct

_setloc_downlevel_struct STRUC
iLcidState		SINT ?
lcidLanguage		LCID ?
lcidCountry		LCID ?
_setloc_downlevel_struct ENDS
_psetloc_downlevel_struct typedef ptr _setloc_downlevel_struct
endif

__threadid		proto __cdecl
_threadid		equ <__threadid()>
__threadhandle		proto __cdecl
_threadhandle		equ <__threadhandle()>

_tiddata		STRUC
_tid			uint_t ?
_thandle		uintptr_t ?
_terrno			int_t ?
_tdoserrno		uint_t ?
_fpds			uint_t ?
_holdrand		uint_t ?
_token			string_t ?
_wtoken			wstring_t ?
_mtoken			ustring_t ?
_errmsg			string_t ?
_werrmsg		wstring_t ?
_namebuf0		string_t ?
_wnamebuf0		wstring_t ?
_namebuf1		string_t ?
_wnamebuf1		wstring_t ?
_asctimebuf		string_t ?
_wasctimebuf		wstring_t ?
_gmtimebuf		ptr_t ?
_cvtbuf			string_t ?
_con_ch_buf		uchar_t MB_LEN_MAX dup(?)
_ch_buf_used		ushort_t ?
_initaddr		ptr_t ?
_initarg		ptr_t ?
_pxcptacttab		ptr_t ?
_tpxcptinfoptrs		ptr_t ?
_tfpecode		int_t ?
ptmbcinfo		pthreadmbcinfo ?
ptlocinfo		pthreadlocinfo ?
_ownlocale		int_t ?
_NLG_dwCode		uint_t ?
_terminate		ptr_t ?
_unexpected		ptr_t ?
_translator		ptr_t ?
_purecall		ptr_t ?
_curexception		ptr_t ?
_curcontext		ptr_t ?
_ProcessingThrow	int_t ?
_curexcspec		ptr_t ?
if defined (_M_X64) OR defined (_M_ARM)
_pExitContext		ptr_t ?
_pUnwindContext		ptr_t ?
_pFrameInfoChain	ptr_t ?
ifdef _WIN64
_ImageBase		int64_t ?
_ThrowImageBase		int64_t ?
else
_ImageBase		int_t ?
_ThrowImageBase		int_t ?
endif
_pForeignException	ptr_t ?
elseifdef _M_IX86
_pFrameInfoChain	ptr_t ?
endif
_setloc_data		_setloc_struct <>
_reserved1		ptr_t ?
_reserved2		ptr_t ?
_reserved3		ptr_t ?
ifdef _M_IX86
_reserved4		ptr_t ?
_reserved5		ptr_t ?
endif
_cxxReThrow		int_t ?
__initDomain		uint_t ?
if defined(_CRT_APP) AND NOT defined(_KERNELX)
_winRTThreadHandle	HANDLE ?
else
_initapartment		int_t ?
endif
_setloc_downlevel_data	_psetloc_downlevel_struct ?
_tiddata		ENDS
_ptiddata		typedef ptr _tiddata

externdef		__flsindex:DWORD

_lock_fh macro fh
	exitm<__lock_fhandle(fh)>
	endm
_lock_str macro s
	exitm<_lock_file(s)>
	endm
_lock_str2 macro i,s
	exitm<_lock_file2(i,s)>
	endm
_mlock macro l
	exitm<_lock(l)>
	endm
_munlock macro l
	exitm<_unlock(l)>
	endm
_unlock_fh macro fh
	exitm<_unlock_fhandle(fh)>
	endm
_unlock_str macro s
	exitm<_unlock_file(s)>
	endm
_unlock_str2 macro i,s
	exitm<_unlock_file2(i,s)>
	endm

ifdef _M_CEE
ifndef _CRT_MSVCR_CURRENT
ifdef _DEBUG
_CRT_MSVCR_CURRENT	equ <"msvcr120D.dll">
else
_CRT_MSVCR_CURRENT	equ <"msvcr120.dll">
endif
endif
else
_INTEROPSERVICES_DLLIMPORT macro _DllName , _EntryPoint , _CallingConvention
	exitm<>
	endm
_SUPPRESS_UNMANAGED_CODE_SECURITY equ 1
_CALLING_CONVENTION_CDECL	equ 1
_CALLING_CONVENTION_WINAPI	equ 1
_RELIABILITY_CONTRACT		equ 1
ASSERT_UNMANAGED_CODE_ATTRIBUTE equ 1
SECURITYCRITICAL_ATTRIBUTE	equ 1
SECURITYSAFECRITICAL_ATTRIBUTE	equ 1
endif

_lock			proto WINAPI _File:SINT
_lock_file2		proto WINAPI _Index:SINT, _File:ptr void

_lockexit		proto WINAPI
_unlock			proto WINAPI _File: SINT
_unlock_file2		proto WINAPI _Index:SINT, _File:ptr void
_unlockexit		proto WINAPI
_mtinitlocknum		proto WINAPI _LockNum: SINT
_getptd			proto __cdecl
_getptd_noexit		proto __cdecl
_freefls		proto WINAPI _PerFiberData:ptr
_freeptd		proto WINAPI _Ptd:_ptiddata
_initptd		proto __cdecl _Ptd:_ptiddata, _Locale:pthreadlocinfo
__get_flsindex		proto __cdecl

endif ;; __assembler

.pragma pack(pop)

endif ;; _INC_MTDLL
.pragma list(pop)
