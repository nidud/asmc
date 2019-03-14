ifndef __INC_CONIO
 include conio.inc
endif

TIMAXSCRLINE	equ 256		; max screen size

getxya		proto __cdecl :int_t, :int_t
getxyc		proto __cdecl :int_t, :int_t
getxyw		proto __cdecl :int_t, :int_t
scputa		proto __cdecl :int_t, :int_t, :int_t, :int_t
scputfg		proto __cdecl :int_t, :int_t, :int_t, :int_t
scputbg		proto __cdecl :int_t, :int_t, :int_t, :int_t
scputc		proto __cdecl :int_t, :int_t, :int_t, :int_t
scputw		proto __cdecl :int_t, :int_t, :int_t, :int_t
scputs		proto __cdecl :int_t, :int_t, :int_t, :int_t, :string_t
scpath		proto __cdecl :int_t, :int_t, :int_t, :string_t
scenter		proto __cdecl :int_t, :int_t, :int_t, :string_t
scputf		proto _CDecl  :int_t, :int_t, :int_t, :int_t, :string_t, :vararg

