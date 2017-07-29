ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_addnd	proto __cdecl :ptr, :ptr, :dword
_subnd	proto __cdecl :ptr, :ptr, :dword
_mulnd	proto __cdecl :ptr, :ptr, :ptr, :dword
_divnd	proto __cdecl :ptr, :ptr, :ptr, :dword
_idivn	proto __cdecl :ptr, :ptr, :ptr, :dword
_cmpnd	proto __cdecl :ptr, :ptr, :dword
_icmpn	proto __cdecl :ptr, :ptr, :dword
_shrnd	proto __cdecl :ptr, :dword, :dword
_shlnd	proto __cdecl :ptr, :dword, :dword
_bsfnd	proto __cdecl :ptr, :dword
_bsrnd	proto __cdecl :ptr, :dword
_negnd	proto __cdecl :ptr, :dword
_cpynd	proto __cdecl :ptr, :ptr, :dword
_atond	proto __cdecl :ptr, :ptr, :dword, :dword
_ndtoa	proto __cdecl :ptr, :ptr, :dword, :dword

.list
