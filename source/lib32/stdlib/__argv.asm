; __ARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc
include winbase.inc

.data
__argv	array_t 0
_pgmptr string_t 0

.code

Install PROC PRIVATE USES edi

  local pgname[260]:SBYTE

    mov __argv,setargv(&__argc, GetCommandLineA())
    mov eax,[eax]
    .if byte ptr [eax+1] != ':'
	free(eax)
	;
	; Get the program name pointer from Win32 Base
	;
	GetModuleFileNameA(0, &pgname, 260)
	malloc(&[eax+1])
	lea ecx,pgname
	strcpy(eax, ecx)
	mov ecx,__argv
	mov [ecx],eax
	.if byte ptr [eax] == '"'
	    mov edi,eax
	    strcpy(edi, &[eax+1])
	    .if strrchr(edi, '"')
		mov byte ptr [eax],0
	    .endif
	    mov eax,edi
	.endif
    .endif
    mov _pgmptr,eax
    ret

Install ENDP

.pragma init(Install, 4)

    end
