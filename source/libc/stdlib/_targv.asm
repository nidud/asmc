; _TARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
ifndef __UNIX__
include winbase.inc
endif
include tchar.inc

.data
 __targv tstring_t 0

.code

ifndef __UNIX__

__initargv proc private

  local pgname[260]:tchar_t

    mov __targv,_tsetargv(&__argc, GetCommandLine())

    mov rax,[rax]

    .if ( tchar_t ptr [rax+tchar_t] != ':' )

	free(rax)

	; Get the program name pointer from Win32 Base

	mov rcx,malloc(&[GetModuleFileName(0, &pgname, 260)*tchar_t+tchar_t])
	_tcscpy(rcx, &pgname)

	mov rcx,__targv
	mov [rcx],rax

	.if ( tchar_t ptr [rax] == '"' )

	    .for ( rdx = rax : tchar_t ptr [rdx] : rdx+=tchar_t )

		mov [rdx],tchar_t ptr [rdx+tchar_t]
	    .endf
	    .if ( tchar_t ptr [rdx-tchar_t*2] == '"' )
		mov tchar_t ptr [rdx-tchar_t*2],0
	    .endif
	    mov rax,[rcx]
	.endif
    .endif
    ret

__initargv endp

.pragma init(__initargv, 4)

endif
    end
