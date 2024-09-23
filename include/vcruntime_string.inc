include vcruntime.inc
ifndef __midl
memchr      proto __cdecl :ptr, :int_t, :size_t
memcmp      proto __cdecl :ptr, :ptr, :size_t
memcpy      proto __cdecl :ptr, :ptr, :size_t
memmove     proto __cdecl :ptr, :ptr, :size_t
memset      proto __cdecl :ptr, :int_t, :size_t

strchr      proto __cdecl :ptr char_t, :int_t
strrchr     proto __cdecl :ptr char_t, :int_t
strstr      proto __cdecl :ptr char_t, :ptr char_t

wcschr      proto __cdecl :ptr wchar_t, :int_t
wcsrchr     proto __cdecl :ptr wchar_t, :int_t
wcsstr      proto __cdecl :ptr wchar_t, :ptr wchar_t
endif
