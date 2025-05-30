ifndef _INC_MEMORY
define _INC_MEMORY

include stdlib.inc
include crtdefs.inc

.pragma comment(lib, libc, msvcrt)

ifndef _CRT_MEMORY_DEFINED
define _CRT_MEMORY_DEFINED
_memccpy	proto __cdecl :ptr, :ptr, :int_t, :size_t
memchr		proto __cdecl :ptr, :int_t, :size_t
_memicmp	proto __cdecl :ptr, :ptr, :size_t
_memicmp_l	proto __cdecl :ptr, :ptr, :size_t, :_locale_t
memcmp		proto __cdecl :ptr, :ptr, :size_t
;_CRT_INSECURE_DEPRECATE_MEMORY(memcpy_s)
memcpy		proto __cdecl :ptr, :ptr, :size_t
if __STDC_WANT_SECURE_LIB__
memcpy_s	proto __cdecl :ptr, :rsize_t, :ptr, :rsize_t
endif
memset		proto __cdecl :ptr, :int_t, :size_t
ife __STDC__
memccpy		proto __cdecl :ptr, :ptr, :int_t, :size_t
memicmp		proto __cdecl :ptr, :ptr, :size_t
endif
endif ;; _CRT_MEMORY_DEFINED
endif ;; _INC_MEMORY
