; __WARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc
include winbase.inc

.data
__wargv	 warray_t 0
_wpgmptr wstring_t 0

.code

Install proc private

  local pgname[260]:WCHAR

    mov __wargv,setwargv(&__argc, GetCommandLineW())

    mov rax,[rax]

    .if ( word ptr [rax+1] != ':' )

	free(rax)

	; Get the program name pointer from Win32 Base

	mov rcx,malloc(&[GetModuleFileNameW(0, &pgname, 260)*2+2])
	wcscpy(rcx, &pgname)

	mov rcx,__wargv
	mov [rcx],rax

	.if ( word ptr [rax] == '"' )

	    .for ( rdx = rax : word ptr [rdx] : rdx += 2 )

		mov ax,[rdx+2]
		mov [rdx],ax
	    .endf
	    .if ( word ptr [rdx-4] == '"' )
		mov word ptr [rdx-4],0
	    .endif
	    mov rax,[rcx]
	.endif
    .endif
    mov _wpgmptr,rax
    ret

Install endp

.pragma(init(Install, 4))

    end
