ifndef __STRLIB_INC
__STRLIB_INC equ <>
ifndef __LIBC_INC
 include libc.inc
endif
.xlist
ifndef __PE__

memxchg		proto __cdecl :LPSTR, :LPSTR, :SIZE_T
memstri		proto __cdecl :LPSTR, :SIZE_T, :LPSTR, :SIZE_T
memrchr		proto __cdecl :LPSTR, :SIZE_T, :SIZE_T
memquote	proto __cdecl :LPSTR, :SIZE_T
memzero		proto __cdecl :LPSTR, :SIZE_T

strfn		proto __cdecl :LPSTR
strext		proto __cdecl :LPSTR
setfext		proto __cdecl :LPSTR, :LPSTR
strfcat		proto __cdecl :LPSTR, :LPSTR, :LPSTR
strxchg		proto __cdecl :LPSTR, :LPSTR, :LPSTR
strpath		proto __cdecl :LPSTR
strnzcpy	proto __cdecl :LPSTR, :LPSTR, :SIZE_T
strstart	proto __cdecl :LPSTR
strspace	proto __cdecl :LPSTR
strtrim		proto __cdecl :LPSTR
strtoken	proto __cdecl :LPSTR
strstri		proto __cdecl :LPSTR, :LPSTR
strins		proto __cdecl :LPSTR, :LPSTR
strtolx		proto __cdecl :LPSTR
strmove		proto __cdecl :LPSTR, :LPSTR
strchri		proto __cdecl :LPSTR, :SIZE_T
streol		proto __cdecl :LPSTR

cmpwarg		proto __cdecl :LPSTR, :LPSTR
cmpwargs	proto __cdecl :LPSTR, :LPSTR
dostounix	proto __cdecl :LPSTR
unixtodos	proto __cdecl :LPSTR

endif ;; __PE__
.list
endif ;; __STRLIB_INC
