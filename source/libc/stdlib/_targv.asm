; _TARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include winbase.inc
include tchar.inc

.data
__targv	 LPTSTR 0
_tpgmptr LPTSTR 0

.code

ifndef __UNIX__

init_argv proc private

  local pgname[260]:TCHAR

    mov __targv,_tsetargv(&__argc, GetCommandLine())

    mov rax,[rax]

    .if ( TCHAR ptr [rax+TCHAR] != ':' )

	free(rax)

	; Get the program name pointer from Win32 Base

	mov rcx,malloc(&[GetModuleFileName(0, &pgname, 260)*TCHAR+TCHAR])
	_tcscpy(rcx, &pgname)

	mov rcx,__targv
	mov [rcx],rax

	.if ( TCHAR ptr [rax] == '"' )

	    .for ( rdx = rax : TCHAR ptr [rdx] : rdx+=TCHAR )

		mov [rdx],TCHAR ptr [rdx+TCHAR]
	    .endf
	    .if ( TCHAR ptr [rdx-TCHAR*2] == '"' )
		mov TCHAR ptr [rdx-TCHAR*2],0
	    .endif
	    mov rax,[rcx]
	.endif
    .endif
    mov _tpgmptr,rax
    ret

init_argv endp

.pragma init(init_argv, 4)

endif
    end
