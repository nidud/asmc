.pragma list(push, 0)

ifndef _INC_PROCESS
define _INC_PROCESS

include stdlib.inc

define _P_WAIT          0
define _P_NOWAIT        1
define _OLD_P_OVERLAY   2
define _P_NOWAITO       3
define _P_DETACH        4

define _P_OVERLAY       2

define _WAIT_CHILD      0
define _WAIT_GRANDCHILD 1

.pragma comment(lib, libc, msvcrt)

_beginthread    proto __cdecl :ptr, :uint_t, :ptr
_endthread      proto __cdecl
_beginthreadex  proto __cdecl :ptr, :uint_t, :ptr, :ptr, :uint_t, :ptr uint_t
_endthreadex    proto __cdecl :uint_t

ifndef _CRT_TERMINATE_DEFINED
define _CRT_TERMINATE_DEFINED
exit    proto __cdecl :int_t
_exit   proto __cdecl :int_t
abort   proto __cdecl
endif
_cexit  proto __cdecl
_c_exit proto __cdecl

ifdef __UNIX__
define _getpid <getpid>
else
_getpid     proto __cdecl
endif
_cwait      proto __cdecl :ptr int_t, :intptr_t, :int_t

ifdef __UNIX__
define _execl       <execl>
define _execle      <execle>
define _execlp      <execlp>
define _execlpe     <execlpe>
define _execv       <execv>
define _execve      <execve>
define _execvp      <execvp>
define _execvpe     <execvpe>
define _spawnl      <spawnl>
define _spawnle     <spawnle>
define _spawnlp     <spawnlp>
define _spawnlpe    <spawnlpe>
define _spawnv      <spawnv>
define _spawnve     <spawnve>
define _spawnvp     <spawnvp>
define _spawnvpe    <spawnvpe>
else
_execl      proto __Cdecl :string_t, :string_t, :vararg
_execle     proto __Cdecl :string_t, :string_t, :vararg
_execlp     proto __Cdecl :string_t, :string_t, :vararg
_execlpe    proto __Cdecl :string_t, :string_t, :vararg
_execv      proto __cdecl :string_t, :array_t
_execve     proto __cdecl :string_t, :array_t, :array_t
_execvp     proto __cdecl :string_t, :array_t
_execvpe    proto __cdecl :string_t, :array_t, :array_t
_spawnl     proto __Cdecl :int_t, :string_t, :string_t, :vararg
_spawnle    proto __Cdecl :int_t, :string_t, :string_t, :vararg
_spawnlp    proto __Cdecl :int_t, :string_t, :string_t, :vararg
_spawnlpe   proto __Cdecl :int_t, :string_t, :string_t, :vararg
_spawnv     proto __cdecl :int_t, :string_t, :array_t
_spawnve    proto __cdecl :int_t, :string_t, :array_t, :array_t
_spawnvp    proto __cdecl :int_t, :string_t, :array_t
_spawnvpe   proto __cdecl :int_t, :string_t, :array_t, :array_t
endif

ifndef _CRT_SYSTEM_DEFINED
define _CRT_SYSTEM_DEFINED
system proto __cdecl :string_t
endif

ifndef _WPROCESS_DEFINED
define _WPROCESS_DEFINED
_wexecl     proto __Cdecl :wstring_t, :wstring_t, :vararg
_wexecle    proto __Cdecl :wstring_t, :wstring_t, :vararg
_wexeclp    proto __Cdecl :wstring_t, :wstring_t, :vararg
_wexeclpe   proto __Cdecl :wstring_t, :wstring_t, :vararg
_wexecv     proto __cdecl :wstring_t, :warray_t
_wexecve    proto __cdecl :wstring_t, :warray_t, :warray_t
_wexecvp    proto __cdecl :wstring_t, :warray_t
_wexecvpe   proto __cdecl :wstring_t, :warray_t, :warray_t
_wspawnl    proto __Cdecl :int_t, :wstring_t, :wstring_t, :vararg
_wspawnle   proto __Cdecl :int_t, :wstring_t, :wstring_t, :vararg
_wspawnlp   proto __Cdecl :int_t, :wstring_t, :wstring_t, :vararg
_wspawnlpe  proto __Cdecl :int_t, :wstring_t, :wstring_t, :vararg
_wspawnv    proto __cdecl :int_t, :wstring_t, :warray_t
_wspawnve   proto __cdecl :int_t, :wstring_t, :warray_t, :warray_t
_wspawnvp   proto __cdecl :int_t, :wstring_t, :warray_t
_wspawnvpe  proto __cdecl :int_t, :wstring_t, :warray_t, :warray_t
ifndef _CRT_WSYSTEM_DEFINED
define _CRT_WSYSTEM_DEFINED
_wsystem proto __cdecl :ptr wchar_t
endif
endif

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

_loaddll        proto __cdecl :string_t
_unloaddll      proto __cdecl :intptr_t
_getdllprocaddr proto __cdecl :intptr_t, :string_t, :intptr_t

define P_WAIT          _P_WAIT
define P_NOWAIT        _P_NOWAIT
define P_OVERLAY       _P_OVERLAY
define OLD_P_OVERLAY   _OLD_P_OVERLAY
define P_NOWAITO       _P_NOWAITO
define P_DETACH        _P_DETACH
define WAIT_CHILD      _WAIT_CHILD
define WAIT_GRANDCHILD _WAIT_GRANDCHILD

ifndef __UNIX__
getpid      proto __cdecl
endif
cwait       proto __cdecl :ptr int_t, :intptr_t, :int_t

execl       proto __Cdecl :string_t, :string_t, :vararg
execle      proto __Cdecl :string_t, :string_t, :vararg
execlp      proto __Cdecl :string_t, :string_t, :vararg
execlpe     proto __Cdecl :string_t, :string_t, :vararg
execv       proto __cdecl :string_t, :array_t
execve      proto __cdecl :string_t, :array_t, :array_t
execvp      proto __cdecl :string_t, :array_t
execvpe     proto __cdecl :string_t, :array_t, :array_t
spawnl      proto __Cdecl :int_t, :string_t, :string_t, :vararg
spawnle     proto __Cdecl :int_t, :string_t, :string_t, :vararg
spawnlp     proto __Cdecl :int_t, :string_t, :string_t, :vararg
spawnlpe    proto __Cdecl :int_t, :string_t, :string_t, :vararg
spawnv      proto __cdecl :int_t, :string_t, :array_t
spawnve     proto __cdecl :int_t, :string_t, :array_t, :array_t
spawnvp     proto __cdecl :int_t, :string_t, :array_t
spawnvpe    proto __cdecl :int_t, :string_t, :array_t, :array_t

if not defined(_MSVCRT) or defined(_CRTBLD)
_dospawn    proto __cdecl :int_t, :string_t, :string_t, :string_t
_wdospawn   proto __cdecl :int_t, :wstring_t, :wstring_t, :wstring_t
ifdef _UNICODE
define _tdospawn  <_wdospawn>
else
define _tdospawn  <_dospawn>
endif
endif

endif
.pragma list(pop)
