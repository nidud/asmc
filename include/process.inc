.pragma list(push, 0)

ifndef _INC_PROCESS
_INC_PROCESS equ <>

include crtdefs.inc

_P_WAIT         equ 0
_P_NOWAIT       equ 1
_OLD_P_OVERLAY  equ 2
_P_NOWAITO      equ 3
_P_DETACH       equ 4

_P_OVERLAY      equ 2

;; Action codes for _cwait(). The action code argument to _cwait is ignored
;; on Win32 though it is accepted for compatibilty with old MS CRT libs

_WAIT_CHILD      equ 0
_WAIT_GRANDCHILD equ 1

.pragma comment(lib, libc, msvcrt)

;; function prototypes

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
_beginthread    proto __cdecl :ptr, :uint_t, :ptr
_endthread      proto __cdecl
_beginthreadex  proto __cdecl :ptr, :uint_t, :ptr, :ptr, :uint_t, :ptr uint_t
_endthreadex    proto __cdecl :uint_t
endif

ifndef _CRT_TERMINATE_DEFINED
_CRT_TERMINATE_DEFINED equ <>
undef   exit
exit    proto __cdecl :int_t
_exit   proto __cdecl :int_t
abort   proto __cdecl
endif

_cexit  proto __cdecl
_c_exit proto __cdecl

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
_getpid     proto __cdecl
_cwait      proto __cdecl :ptr int_t, :intptr_t, :int_t
_execl      proto _CDecl :string_t, :string_t, :vararg
_execle     proto _CDecl :string_t, :string_t, :vararg
_execlp     proto _CDecl :string_t, :string_t, :vararg
_execlpe    proto _CDecl :string_t, :string_t, :vararg
_execv      proto __cdecl :string_t, :ptr string_t
_execve     proto __cdecl :string_t, :ptr string_t, :ptr string_t
_execvp     proto __cdecl :string_t, :ptr string_t
_execvpe    proto __cdecl :string_t, :ptr string_t, :ptr string_t
_spawnl     proto _CDecl :int_t, :string_t, :string_t, :vararg
_spawnle    proto _CDecl :int_t, :string_t, :string_t, :vararg
_spawnlp    proto _CDecl :int_t, :string_t, :string_t, :vararg
_spawnlpe   proto _CDecl :int_t, :string_t, :string_t, :vararg
_spawnv     proto __cdecl :int_t, :string_t, :ptr string_t
_spawnve    proto __cdecl :int_t, :string_t, :string_t, :ptr string_t
_spawnvp    proto __cdecl :int_t, :string_t, :string_t
_spawnvpe   proto __cdecl :int_t, :string_t, :string_t, :ptr string_t

ifndef _CRT_SYSTEM_DEFINED
_CRT_SYSTEM_DEFINED equ <>
system proto __cdecl :string_t
endif

ifndef _WPROCESS_DEFINED
;; wide function prototypes, also declared in wchar.inc
_wexecl     proto _CDecl :wstring_t, :wstring_t, :vararg
_wexecle    proto _CDecl :wstring_t, :wstring_t, :vararg
_wexeclp    proto _CDecl :wstring_t, :wstring_t, :vararg
_wexeclpe   proto _CDecl :wstring_t, :wstring_t, :vararg
_wexecv     proto __cdecl :wstring_t, :ptr wstring_t
_wexecve    proto __cdecl :wstring_t, :ptr wstring_t, :ptr wstring_t
_wexecvp    proto __cdecl :wstring_t, :ptr wstring_t
_wexecvpe   proto __cdecl :wstring_t, :ptr wstring_t, :ptr wstring_t
_wspawnl    proto _CDecl :int_t, :wstring_t, :wstring_t, :vararg
_wspawnle   proto _CDecl :int_t, :wstring_t, :wstring_t, :vararg
_wspawnlp   proto _CDecl :int_t, :wstring_t, :wstring_t, :vararg
_wspawnlpe  proto _CDecl :int_t, :wstring_t, :wstring_t, :vararg
_wspawnv    proto __cdecl :int_t, :wstring_t, :ptr wstring_t
_wspawnve   proto __cdecl :int_t, :wstring_t, :wstring_t, :ptr wstring_t
_wspawnvp   proto __cdecl :int_t, :wstring_t, :wstring_t
_wspawnvpe  proto __cdecl :int_t, :wstring_t, :wstring_t, :ptr wstring_t
ifndef _CRT_WSYSTEM_DEFINED
_CRT_WSYSTEM_DEFINED equ <>
_wsystem proto __cdecl :ptr wchar_t
endif

_WPROCESS_DEFINED equ <>
endif

endif

;; Security check initialization and failure reporting used by /GS security
;; checks.

ifndef _M_CEE
__security_init_cookie proto __cdecl
ifdef _M_IX86
__security_check_cookie proto fastcall :uintptr_t
__report_gsfailure proto __cdecl
else
__security_check_cookie proto __cdecl :uintptr_t
__report_gsfailure proto __cdecl :uintptr_t
endif
endif
externdef __security_cookie:uintptr_t

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
;; --------- The following functions are OBSOLETE ---------

;; The Win32 API LoadLibrary, FreeLibrary and GetProcAddress should be used
;; instead.

_loaddll        proto __cdecl :string_t
_unloaddll      proto __cdecl :intptr_t
_getdllprocaddr proto __cdecl :intptr_t, :string_t, :intptr_t

;; --------- The preceding functions are OBSOLETE ---------
endif


ifdef _DECL_DLLMAIN
;;
;; Declare DLL notification (initialization/termination) routines
;;      The preferred method is for the user to provide DllMain() which will
;;      be called automatically by the DLL entry point defined by the C run-
;;      time library code.  If the user wants to define the DLL entry point
;;      routine, the user's entry point must call _CRT_INIT on all types of
;;      notifications, as the very first thing on attach notifications and
;;      as the very last thing on detach notifications.
;;
ifdef _WINDOWS_

if defined (MRTDLL) && defined(_CRTBLD)
DllMain     proto __clrcall :HANDLE, :DWORD, :PVOID
_CRT_INIT   proto :HANDLE, :DWORD, :PVOID
else
DllMain     proto WINAPI :HANDLE, :DWORD, :PVOID
_CRT_INIT   proto WINAPI :HANDLE, :DWORD, :PVOID
endif

_wCRT_INIT  proto WINAPI :HANDLE, :DWORD, :PVOID

_pRawDllMain_t typedef proto :HANDLE, :DWORD, LPVOID
externdef  _pRawDllMain:ptr _pRawDllMain_t
else
DllMain     proto :ptr HANDLE, :DWORD, :PVOID
_CRT_INIT   proto :ptr HANDLE, :DWORD, :PVOID
_wCRT_INIT  proto :ptr HANDLE, :DWORD, :PVOID
_pRawDllMain_t typedef proto :PVOID, :DWORD, :PVOID
externdef  _pRawDllMain:ptr _pRawDllMain_t
endif
endif

if __STDC__ eq 0

;; Non-ANSI names for compatibility

P_WAIT          equ _P_WAIT
P_NOWAIT        equ _P_NOWAIT
P_OVERLAY       equ _P_OVERLAY
OLD_P_OVERLAY   equ _OLD_P_OVERLAY
P_NOWAITO       equ _P_NOWAITO
P_DETACH        equ _P_DETACH
WAIT_CHILD      equ _WAIT_CHILD
WAIT_GRANDCHILD equ _WAIT_GRANDCHILD

ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

;; current declarations

getpid      proto __cdecl
cwait       proto __cdecl :ptr int_t, :intptr_t, :int_t
execl       proto _CDecl :string_t, :string_t, :vararg
execle      proto _CDecl :string_t, :string_t, :vararg
execlp      proto _CDecl :string_t, :string_t, :vararg
execlpe     proto _CDecl :string_t, :string_t, :vararg
execv       proto __cdecl :string_t, :ptr string_t
execve      proto __cdecl :string_t, :ptr string_t, :ptr string_t
execvp      proto __cdecl :string_t, :ptr string_t
execvpe     proto __cdecl :string_t, :ptr string_t, :ptr string_t
spawnl      proto _CDecl :int_t, :string_t, :string_t, :vararg
spawnle     proto _CDecl :int_t, :string_t, :string_t, :vararg
spawnlp     proto _CDecl :int_t, :string_t, :string_t, :vararg
spawnlpe    proto _CDecl :int_t, :string_t, :string_t, :vararg
spawnv      proto __cdecl :int_t, :string_t, :ptr string_t
spawnve     proto __cdecl :int_t, :string_t, :string_t, :ptr string_t
spawnvp     proto __cdecl :int_t, :string_t, :string_t
spawnvpe    proto __cdecl :int_t, :string_t, :string_t, :ptr string_t

getpid      proto __cdecl

endif
endif
endif
.pragma list(pop)
