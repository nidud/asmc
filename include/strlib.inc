.pragma list(push, 0)
ifndef __STRLIB_INC
__STRLIB_INC equ <>
ifndef __LIBC_INC
 include libc.inc
endif
ifndef _MSVCRT
.pragma comment(lib, libc)

memxchg		proto __cdecl :string_t, :string_t, :size_t
memstri		proto __cdecl :string_t, :size_t, :string_t, :size_t
memrchr		proto __cdecl :string_t, :size_t, :size_t
memquote	proto __cdecl :string_t, :size_t

strfn		proto __cdecl :string_t
strext		proto __cdecl :string_t
setfext		proto __cdecl :string_t, :string_t
strfcat		proto __cdecl :string_t, :string_t, :string_t
strxchg		proto __cdecl :string_t, :string_t, :string_t
strpath		proto __cdecl :string_t
strnzcpy	proto __cdecl :string_t, :string_t, :size_t
strstart	proto __cdecl :string_t
strspace	proto __cdecl :string_t
strtrim		proto __cdecl :string_t
strtoken	proto __cdecl :string_t
strstri		proto __cdecl :string_t, :string_t
strins		proto __cdecl :string_t, :string_t
strtolx		proto __cdecl :string_t
strmove		proto __cdecl :string_t, :string_t
strchri		proto __cdecl :string_t, :size_t
streol		proto __cdecl :string_t

cmpwarg		proto __cdecl :string_t, :string_t
cmpwargs	proto __cdecl :string_t, :string_t
dostounix	proto __cdecl :string_t
unixtodos	proto __cdecl :string_t

btohex		proto __cdecl :string_t, :int_t
hextob		proto __cdecl :string_t

xtol		proto __cdecl :string_t
_xtoi64		proto __cdecl :string_t
endif ;; _MSVCRT
endif
.pragma list(pop)
