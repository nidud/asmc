ifndef _INC_INTERNAL
_INC_INTERNAL equ <>

include crtdefs.inc
include limits.inc
include windows.inc
include mtdll.inc

.pragma pack(push, _CRT_PACKING)

CALLBACKC(_PVFV)
CALLBACKC(_PIFV)
CALLBACKC(_PVFI, :int_t)

ifdef _M_CEE
CALLBACKC(_PVFVM)
CALLBACKC(_PIFVM)
CALLBACKC(_CPVFV)
endif

if defined (_M_CEE_PURE) OR (defined (_DLL) AND defined (_M_IX86))
__p__commode proto __cdecl
endif
if defined (SPECIAL_CRTEXE) AND defined (_DLL)
externdef _commode:int_t
else
ifndef _M_CEE_PURE
externdef _commode:int_t
else
_commode equ <__p___commode()>
endif
endif

__IOINFO_TM_ANSI	equ 0
__IOINFO_TM_UTF8	equ 1
__IOINFO_TM_UTF16LE	equ 2

LF			equ 10
CR			equ 13
CTRLZ			equ 26

externdef		_lookuptrailbytes:char_t

_msbit macro _c
	exitm<((_c) AND 0x80)>
	endm

_utf8_is_independent macro _c
	exitm<(_msbit(_c) EQ 0)>
	endm

_utf8_is_leadbyte macro _c
	exitm<(_lookuptrailbytes[_c] !!= 0)>
	endm

_utf8_no_of_trailbytes macro _c
	exitm<_lookuptrailbytes[_c]>
	endm

ioinfo			STRUC
osfhnd			intptr_t ?
osfile			char_t ?
pipech			char_t ?
lockinitflag		SINT ?
_lock			CRITICAL_SECTION <>
ifndef _SAFECRT_IMPL
textmode		char_t ? ; textmode : 7, unicode : 1
pipech2			char_t 2 dup(?)
startpos		int64_t ?
utf8translations	BOOL ?
dbcsBuffer		char_t ?
dbcsBufferUsed		BOOL ?
endif
ioinfo			ENDS

IOINFO_L2E		equ 5
IOINFO_ARRAY_ELTS	equ (1 SHL IOINFO_L2E)
IOINFO_ARRAYS		equ 64
_NHANDLE_		equ (IOINFO_ARRAYS * IOINFO_ARRAY_ELTS)
_TZ_STRINGS_SIZE	equ 64
STDIO_HANDLES_COUNT	equ 3
if 0
_pioinfo macro i
	exitm<( __pioinfo[(i) SHR IOINFO_L2E] + ((i) AND (IOINFO_ARRAY_ELTS - 1)) )>
	endm

_osfhnd macro i
	exitm<( _pioinfo(i)- GT osfhnd )>
	endm

_osfile macro i
	exitm<( _pioinfo(i)- GT osfile )>
	endm

_pipech macro i
	exitm<( _pioinfo(i)- GT pipech )>
	endm

_pipech2 macro i
	exitm<( _pioinfo(i)- GT pipech2 )>
	endm

_textmode macro i
	exitm<( _pioinfo(i)- GT textmode )>
	endm

_tm_unicode macro i
	exitm<( _pioinfo(i)- GT unicode )>
	endm

_startpos macro i
	exitm<( _pioinfo(i)- GT startpos )>
	endm

_utf8translations macro i
	exitm<( _pioinfo(i)- GT utf8translations )>
	endm

_dbcsBuffer macro i
	exitm<( _pioinfo(i)- GT dbcsBuffer )>
	endm

_dbcsBufferUsed macro i
	exitm<( _pioinfo(i)- GT dbcsBufferUsed )>
	endm

_pioinfo_safe macro i
	exitm<( (((i) NOT = -1) AND ((i) NOT = -2)) ? _pioinfo(i) : AND __badioinfo )>
	endm

_osfhnd_safe macro i
	exitm<( _pioinfo_safe(i)- GT osfhnd )>
	endm

_osfile_safe macro i
	exitm<( _pioinfo_safe(i)- GT osfile )>
	endm

_pipech_safe macro i
	exitm<( _pioinfo_safe(i)- GT pipech )>
	endm

_pipech2_safe macro i
	exitm<( _pioinfo_safe(i)- GT pipech2 )>
	endm
endif
ifdef _SAFECRT_IMPL
_textmode_safe macro i
	exitm<__IOINFO_TM_ANSI>
	endm
_tm_unicode_safe macro i
	exitm<0>
	endm
_startpos_safe macro i
	exitm<( 0 )>
	endm
_utf8translations_safe macro i
	exitm<( FALSE )>
	endm
else
_textmode_safe macro i
	exitm<( _pioinfo_safe(i)- GT textmode )>
	endm
_tm_unicode_safe macro i
	exitm<( _pioinfo_safe(i)- GT unicode )>
	endm
_startpos_safe macro i
	exitm<( _pioinfo_safe(i)- GT startpos )>
	endm
_utf8translations_safe macro i
	exitm<( _pioinfo_safe(i)- GT utf8translations )>
	endm
endif

ifndef _M_CEE_PURE
ifdef _SAFECRT_IMPL
externdef		__badioinfo:ioinfo
externdef		__pioinfo:ptr ioinfo
else
externdef		__badioinfo:ioinfo
externdef		__pioinfo:ptr ioinfo
endif
endif

externdef		_nhandle:int_t

;int
_alloc_osfhnd proto WINAPI
;int
_free_osfhnd proto WINAPI \
		      : SINT

;int
_set_osfhnd proto WINAPI \
		      : SINT,
		      : intptr_t


_NO_CONSOLE_FILENO	equ -2


externdef		__dnames:char_t
externdef		__mnames:char_t

externdef		_days:int_t
externdef		_lpdays:int_t

__loctotime32_t		proto __cdecl :int_t, :int_t, :int_t, :int_t, :int_t, :int_t, :int_t
__loctotime64_t		proto __cdecl :int_t, :int_t, :int_t, :int_t, :int_t, :int_t, :int_t

ifdef _TM_DEFINED
_isindst		proto __cdecl :ptr
endif

__tzset			proto __cdecl
_validdrive		proto __cdecl :uint_t

IS_LEAP_YEAR macro y
	exitm<(((y) % 4 EQ 0 AND (y) % 100 NOT = 0) OR (y) % 400 EQ 0)>
	endm

__getgmtimebuf		proto __cdecl

externdef		_acfinfo:char_t

CFI_LENGTH		equ 12

include isa_availability.inc
externdef		__isa_available:int_t

if defined (_M_IX86) OR defined (_M_X64)
externdef		__isa_enabled:int_t
externdef		__favor:int_t
endif

ifndef _FILE_DEFINED
_FILE_DEFINED		equ <>
_iobuf			STRUC
_ptr			string_t ?
_cnt			int_t ?
_base			string_t ?
_flag			int_t ?
_file			int_t ?
_charbuf		int_t ?
_bufsiz			int_t ?
_tmpfname		string_t ?
_iobuf			ENDS
FILE			typedef _iobuf
LPFILE			typedef ptr _iobuf
endif

if NOT defined (_FILEX_DEFINED) AND defined (_WINDOWS_)

_FILEX			STRUC
f			FILE <>
_lock			CRITICAL_SECTION <>
_FILEX			ENDS
_FILEX_DEFINED		equ 1
endif
externdef		_nstream:int_t
externdef		__piob:ptr

_getstream		proto __cdecl
_openfile		proto __cdecl :ptr char_t, :ptr char_t, :int_t, :ptr FILE
_wopenfile		proto __cdecl :ptr wchar_t, :ptr wchar_t, :int_t, :ptr FILE

_getbuf			proto WINAPI :ptr FILE
_filwbuf		proto WINAPI :ptr FILE
_flswbuf		proto WINAPI :SINT, :ptr FILE
_freebuf		proto WINAPI :ptr FILE
_stbuf			proto __cdecl :ptr FILE
_ftbuf			proto __cdecl :SINT, :ptr FILE

ifdef _SAFECRT_IMPL
_output			proto WINAPI :ptr FILE, :ptr char_t, :va_list
_woutput		proto WINAPI :ptr FILE, :ptr wchar_t, :va_list
_output_s		proto WINAPI :ptr FILE, :ptr char_t: :va_list
_output_p		proto WINAPI :ptr FILE, :ptr char_t: :va_list
_woutput_s		proto WINAPI :ptr FILE, :ptr wchar_t, :va_list
_woutput_p		proto WINAPI :ptr FILE, :ptr wchar_t, :va_list
CALLBACK(OUTPUTFN, :ptr FILE, :ptr char_t, :va_list)
CALLBACK(WOUTPUTFN, :ptr FILE, :ptr wchar_t, :va_list)
else

_output_l proto WINAPI \
		 _File: ptr FILE,
	       _Format: ptr char_t,
	       _Locale: _locale_t,
	      _ArgList: va_list

_woutput_l proto WINAPI \
		 _File: ptr FILE,
	       _Format: ptr wchar_t,
	       _Locale: _locale_t,
	      _ArgList: va_list

_output_s_l proto WINAPI \
		 _File: ptr FILE,
	       _Format: ptr char_t,
	       _Locale: _locale_t,
	      _ArgList: va_list

_output_p_l proto WINAPI \
		 _File: ptr FILE,
	       _Format: ptr char_t,
	       _Locale: _locale_t,
	      _ArgList: va_list

_woutput_s_l proto WINAPI \
		 _File: ptr FILE,
	       _Format: ptr wchar_t,
	       _Locale: _locale_t,
	      _ArgList: va_list

_woutput_p_l proto WINAPI \
		 _File: ptr FILE,
	       _Format: ptr wchar_t,
	       _Locale: _locale_t,
	      _ArgList: va_list

endif

ifdef _SAFECRT_IMPL

_input proto WINAPI \
		 _File: ptr FILE,
	       _Format: LPSTR,
	      _ArgList: va_list

_winput proto WINAPI \
		 _File: ptr FILE,
	       _Format: ptr wchar_t,
	      _ArgList: va_list

_input_s proto WINAPI \
		 _File: ptr FILE,
	       _Format: LPSTR,
	      _ArgList: va_list

_winput_s proto WINAPI \
		 _File: ptr FILE,
	       _Format: ptr wchar_t,
	      _ArgList: va_list

CALLBACK(OUTPUTFN, :ptr FILE, :string_t, :va_list)
CALLBACK(WOUTPUTFN, :ptr FILE, :ptr wchar_t, :va_list)

else

;int
_input_l proto WINAPI \
		 _File: ptr FILE,
		      : LPSTR,
	       _Locale: _locale_t,
	      _ArgList: va_list

;int
_winput_l proto WINAPI \
		 _File: ptr FILE,
		      : ptr wchar_t,
	       _Locale: _locale_t,
	      _ArgList: va_list

;int
_input_s_l proto WINAPI \
		 _File: ptr FILE,
		      : LPSTR,
	       _Locale: _locale_t,
	      _ArgList: va_list

;int
_winput_s_l proto WINAPI \
		 _File: ptr FILE,
		      : ptr wchar_t,
	       _Locale: _locale_t,
	      _ArgList: va_list

CALLBACK(INPUTFN, :ptr FILE, :ptr uchar_t, :_locale_t, :va_list)
CALLBACK(WINPUTFN, :ptr FILE, :ptr wchar_t, :_locale_t, :va_list)

ifdef _UNICODE
TINPUTFN		equ <WINPUTFN>
else
TINPUTFN		equ <INPUTFN>
endif

endif  ;; _SAFECRT_IMPL

_flush			proto WINAPI :ptr FILE
_endstdio		proto WINAPI

_sopen_helper		proto __cdecl :ptr char_t, :int_t, :int_t, :int_t, :ptr int_t, :int_t
_wsopen_helper		proto __cdecl :ptr wchar_t, :int_t, :int_t, :int_t, :ptr int_t, :int_t
_sopen_nolock		proto __cdecl :ptr int_t, :ptr int_t, :ptr char_t, :int_t, :int_t, :int_t, :int_t
_wsopen_nolock		proto __cdecl :ptr int_t, :ptr int_t, :ptr wchar_t, :int_t, :int_t, :int_t, :int_t

ifndef CRTDLL
externdef		_cflush:int_t
endif
externdef		_tempoff:uint_t
externdef		_old_pfxlen:uint_t
externdef		_umaskval:int_t
;externdef		_pipech:char_t
externdef		_exitflag:char_t
externdef		_C_Termination_Done:int_t

_getpath		proto :string_t, :string_t, :size_t
_wgetpath		proto :ptr wchar_t, :ptr wchar_t, :size_t

externdef		_dowildcard:int_t

ifndef _PNH_DEFINED
_PNH typedef proto __cdecl :size_t
_PNH_DEFINED equ 1
endif

ifdef _M_CEE
ifndef __MPNH_DEFINED
__MPNH typedef proto :size_t
__MPNH_DEFINED equ 1
endif
endif

;int
_callnewh proto WINAPI _Size:size_t

externdef		_newmode:int_t

ifndef _M_CEE_PURE
externdef		__winitenv:ptr wchar_t
externdef		__initenv:ptr char_t
endif

_calloca macro count, size
	exitm<((count LE 0 OR size LE 0 OR (((_HEAP_MAXREQ) / (count)) LT (size)))? NULL : _malloca(count * size))>
	endm

;; startup set values
externdef _aenvptr:ptr char_t
externdef _wenvptr:ptr wchar_t

if defined (_DLL)
__p__acmdln proto __cdecl
__p__wcmdln proto __cdecl
endif
ifndef _M_CEE_PURE
externdef _acmdln:ptr char_t
externdef _wcmdln:ptr wchar_t
else
_acmdln equ <__p__acmdln()>
_wcmdln equ <__p__wcmdln()>
endif

;int
_cwild proto WINAPI
;int
_wcwild proto WINAPI
;int
_mtinit proto WINAPI
;void
_mtterm proto WINAPI
;int
_mtinitlocks proto WINAPI
;void
_mtdeletelocks proto WINAPI
;int
_mtinitlocknum proto WINAPI :int_t


_CRT_SPINCOUNT		equ 4000

;void
_amsg_exit proto WINAPI :SINT
__crtExitProcess proto WINAPI :SINT
__crtCorExitProcess proto WINAPI :SINT
__crtdll_callstaticterminators proto WINAPI

ifdef _CRT_APP
_exit_app	proto __cdecl
endif

_cinit		proto WINAPI :SINT
__doinits	proto WINAPI
__doterms	proto WINAPI
__dopreterms	proto WINAPI
_fpmath		proto WINAPI :SINT
_fptrap		proto WINAPI
__freeCrtMemory proto WINAPI
_heap_init	proto WINAPI
_heap_term	proto WINAPI
_heap_abort	proto WINAPI
__initconin	proto WINAPI
__initconout	proto WINAPI
_ioinit		proto WINAPI
_ioterm		proto WINAPI
_GET_RTERRMSG	proto __cdecl :int_t
_setargv	proto WINAPI
__setargv	proto WINAPI
_wsetargv	proto WINAPI
__wsetargv	proto WINAPI
_setenvp	proto WINAPI
_wsetenvp	proto WINAPI
__setmbctable	proto WINAPI :uint_t



if NOT defined (_CRT_APP) OR defined (_KERNELX) OR defined (_DEBUG)
_FF_MSGBANNER	proto WINAPI
_NMSG_WRITE	proto WINAPI :SINT
endif

ifdef _MBCS
__initmbctable	proto WINAPI
endif

ifndef _MANAGED_MAIN
main		proto WINAPI :SINT, :ptr, :ptr
wmain		proto WINAPI :SINT, :ptr, :ptr wchar_t
endif

__mbtow_environ proto WINAPI
__wtomb_environ proto WINAPI
__crtsetenv	proto WINAPI :ptr, :SINT
__crtwsetenv	proto WINAPI :ptr ptr wchar_t, :SINT


if defined (_DLL) OR defined (CRTDLL)

ifndef _STARTUP_INFO_DEFINED
_startupinfo		STRUC
newmode			SINT ?
_startupinfo		ENDS
_STARTUP_INFO_DEFINED equ 1
endif
__getmainargs		proto __cdecl :ptr, :ptr, :ptr, :int_t, :ptr
__wgetmainargs		proto __cdecl :ptr, :ptr, :ptr, :int_t, :ptr
endif

_UNKNOWN_APP		equ 0
_CONSOLE_APP		equ 1
_GUI_APP		equ 2

externdef		__app_type:int_t

ifndef _M_CEE_PURE

__enative_startup_state typedef SDWORD
__uninitialized		equ 0
__initializing		equ 1
__initialized		equ 2

externdef		__native_startup_state:__enative_startup_state
externdef		__native_startup_lock:ptr

__NO_REASON		equ UINT_MAX
externdef		__native_dllmain_reason:uint_t

endif  ;; NOT defined (_M_CEE_PURE)

externdef		__error_mode:int_t

if NOT defined (_CRT_APP) OR defined (_KERNELX)
__set_app_type		proto __cdecl :int_t
endif

_cenvarg		proto __cdecl :ptr char_t, :ptr char_t, :ptr char_t, :ptr char_t, :ptr char_t
_wcenvarg		proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t

_dosmaperr		proto __cdecl :DWORD
_get_errno_from_oserr	proto __cdecl :DWORD

_dospawn		proto __cdecl :int_t, :ptr char_t, :ptr char_t, :ptr char_t
_wdospawn		proto __cdecl :int_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_cenvarg		proto __cdecl :ptr char_t, :ptr char_t, :ptr char_t, :ptr char_t, :ptr char_t
_wcenvarg		proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
ifndef _M_IX86
_capture_argv		proto __cdecl :ptr va_list, :ptr char_t, :ptr char_t, :size_t
_wcapture_argv		proto __cdecl :ptr va_list, :ptr wchar_t, :ptr wchar_t, :size_t
endif

__get_sigabrt		proto _cdecl :_PHNDLR

NTSTATUS		typedef LONG

ifndef STATUS_INVALID_PARAMETER
STATUS_INVALID_PARAMETER equ ((NTSTATUS)0xC000000DL)
endif

ifndef STATUS_FATAL_APP_EXIT
STATUS_FATAL_APP_EXIT	equ (0x40000015)
endif

include crtdbg.inc
include errno.inc

__STR2WSTR macro s
	exitm<L"&s&">
	endm

_STR2WSTR macro s
	exitm<__STR2WSTR(s)>
	endm

__FILEW__		equ <_STR2WSTR(__FILE__)>
__FUNCTIONW__		equ <_STR2WSTR(__FUNCTION__)>

if NOT defined (_SECURECRT_FILL_BUFFER)
ifdef _DEBUG
_SECURECRT_FILL_BUFFER	equ 1
else
_SECURECRT_FILL_BUFFER	equ 0
endif
endif

if defined (_M_IX86) OR defined (_M_X64)
_call_reportfault proto WINAPI nDbgHookCode:SINT, dwExceptionCode:DWORD, dwExceptionFlags:DWORD
endif

_invoke_watson_if_error proto WINAPI \
      _ExpressionError: errno_t,
	   _Expression: ptr wchar_t,
	     _Function: ptr wchar_t,
		 _File: ptr wchar_t,
		 _Line: SINT,
	     _Reserved: uintptr_t

_invoke_watson_if_oneof proto WINAPI \
      _ExpressionError: errno_t,
	  _ErrorValue1: errno_t,
	  _ErrorValue2: errno_t,
	   _Expression: ptr wchar_t,
	     _Function: ptr wchar_t,
		 _File: ptr wchar_t,
		 _Line: SINT,
	     _Reserved: uintptr_t

ifdef _DEBUG
_CALL_INVALID_PARAMETER macro expr
	exitm<_invalid_parameter(expr, __FUNCTIONW__, __FILEW__, __LINE__, 0)>
	endm
_INVOKE_WATSON_IF_ERROR macro expr
	exitm<_invoke_watson_if_error((expr), __STR2WSTR(#expr), __FUNCTIONW__, __FILEW__, __LINE__, 0)>
	endm
_INVOKE_WATSON_IF_ONEOF macro expr, errvalue1, errvalue2
	exitm<_invoke_watson_if_oneof(expr, (errvalue1), (errvalue2), __STR2WSTR(#expr), __FUNCTIONW__, __FILEW__, __LINE__, 0)>
	endm
else
_CALL_INVALID_PARAMETER macro expr
	exitm<_invalid_parameter_noinfo()>
	endm
_INVOKE_WATSON_IF_ERROR macro expr
	exitm<_invoke_watson_if_error(expr, NULL, NULL, NULL, 0, 0)>
	endm
_INVOKE_WATSON_IF_ONEOF macro expr, errvalue1, errvalue2
	exitm<_invoke_watson_if_oneof((expr), (errvalue1), (errvalue2), NULL, NULL, NULL, 0, 0)>
	endm
endif

_INVALID_PARAMETER macro expr
	exitm<_CALL_INVALID_PARAMETER(expr)>
	endm

_VALIDATE_RETURN_VOID macro expr, errorcode
	exitm<>
	endm

ifndef _VALIDATE_RETURN
_VALIDATE_RETURN macro expr, errorcode, retexpr
    local x, s1, val
	for z,<expr>
	    x SubStr <z>,1,1
	    ifidn x,<!">
		s1 equ <z>
	    else
		val equ <z>
	    endif
	    endm
	if (val eq 0)
	    mov errno,errorcode
	    _INVALID_PARAMETER(_CRT_WIDE(s1))
	    mov eax,retexpr
	endif
	retm<eax>
	endm
endif

ifndef _VALIDATE_RETURN_NOEXC
_VALIDATE_RETURN_NOEXC macro expr, errorcode, retexpr
	exitm<>
	endm
endif

_VALIDATE_SETRET macro expr, errorcode, retval, retexpr
	exitm<>
	endm

_CHECK_FH_RETURN macro handle, errorcode, retexpr
	exitm<>
	endm

_VALIDATE_STREAM_ANSI_RETURN macro stream, errorcode, retexpr
	exitm<>
	endm

_VALIDATE_STREAM_ANSI_SETRET macro stream, errorcode, retval, retexpr
	exitm<>
	endm

_VALIDATE_RETURN_NOERRNO macro expr, retexpr
	exitm<>
	endm

_VALIDATE_RETURN_ERRCODE macro expr, errorcode
	exitm<>
	endm

_VALIDATE_RETURN_ERRCODE_NOEXC macro expr, errorcode
	exitm<>
	endm

_VALIDATE_CLEAR_OSSERR_RETURN macro expr, errorcode, retexpr
	exitm<>
	endm

_CHECK_FH_CLEAR_OSSERR_RETURN macro handle, errorcode, retexpr
	exitm<>
	endm

_VALIDATE_CLEAR_OSSERR_RETURN_ERRCODE macro expr, errorcode
	exitm<>
	endm

_CHECK_FH_CLEAR_OSSERR_RETURN_ERRCODE macro handle, retexpr
	exitm<>
	endm

ifdef _DEBUG
externdef		__crtDebugFillThreshold:size_t
endif

if NOT defined (_SECURECRT_FILL_BUFFER_THRESHOLD)
ifdef _DEBUG
_SECURECRT_FILL_BUFFER_THRESHOLD equ <__crtDebugFillThreshold>
else
_SECURECRT_FILL_BUFFER_THRESHOLD equ <>
endif
endif

if _SECURECRT_FILL_BUFFER
_SECURECRT__FILL_STRING macro _String, _Size, _Offset
	exitm<>
	endm
else  ;; _SECURECRT_FILL_BUFFER
_SECURECRT__FILL_STRING macro _String, _Size, _Offset
	exitm<>
	endm
endif

if _SECURECRT_FILL_BUFFER
_SECURECRT__FILL_BYTE macro _Position
	exitm<>
	endm
else
_SECURECRT__FILL_BYTE macro _Position
	exitm<>
	endm
endif

ifdef __cplusplus
_REDIRECT_TO_L_VERSION_FUNC_PROLOGUE equ <>
else
_REDIRECT_TO_L_VERSION_FUNC_PROLOGUE equ <>
endif

_REDIRECT_TO_L_VERSION_1 macro _ReturnType, _FunctionName, _Type1
	exitm<>
	endm

_REDIRECT_TO_L_VERSION_2 macro _ReturnType, _FunctionName, _Type1, _Type2
	exitm<>
	endm

_REDIRECT_TO_L_VERSION_3 macro _ReturnType, _FunctionName, _Type1, _Type2, _Type3
	exitm<>
	endm

_REDIRECT_TO_L_VERSION_4 macro _ReturnType, _FunctionName, _Type1, _Type2, _Type3, _Type4
	exitm<>
	endm

_REDIRECT_TO_L_VERSION_5 macro _ReturnType, _FunctionName, _Type1, _Type2, _Type3, _Type4, _Type5
	exitm<>
	endm

_REDIRECT_TO_L_VERSION_6 macro _ReturnType, _FunctionName, _Type1, _Type2, _Type3, _Type4, _Type5, _Type6
	exitm<>
	endm

_init_pointers	proto WINAPI
EncodePointer	proto WINAPI :ptr
DecodePointer	proto WINAPI :ptr


_BEGIN_SECURE_CRT_DEPRECATION_DISABLE equ <>
_END_SECURE_CRT_DEPRECATION_DISABLE equ <>

_ERRCHECK macro e
	exitm<>
	endm

_ERRCHECK_EINVAL macro e
	exitm<_INVOKE_WATSON_IF_ONEOF(e, EINVAL, EINVAL)>
	endm

_ERRCHECK_EINVAL_ERANGE macro e
	exitm<>
	endm

_ERRCHECK_SPRINTF macro _PrintfCall
	exitm<>
	endm

_wgetenv_helper_nolock proto __cdecl :ptr wchar_t
_getenv_helper_nolock proto __cdecl :ptr char_t

;BOOL
_ValidateImageBase proto WINAPI \
	    pImageBase: PBYTE

_FindPESection proto __cdecl :PBYTE, :DWORD_PTR
;BOOL
_IsNonwritableInCurrentImage proto WINAPI \
	       pTarget: PBYTE


;BOOL
__copy_path_to_wide_string proto WINAPI \
		  _Str: ptr char_t,
		 _WStr: ptr wchar_t

;BOOL
__copy_to_char proto WINAPI \
	      inString: ptr wchar_t,
	     outString: ptr


CRT_WARNING_DISABLE_PUSH macro x,y
	__pragma(warning(push))
	exitm<__pragma(warning(disable: x))>
	endm
CRT_WARNING_POP		equ <__pragma(warning(pop))>

.pragma pack(pop)

endif  ;; _INC_INTERNAL
