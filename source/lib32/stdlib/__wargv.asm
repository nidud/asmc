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
    mov eax,[eax]
    .if word ptr [eax+2] != ':'
	free(eax)

	; Get the program name pointer from Win32 Base

	malloc(&[GetModuleFileNameW(0, &pgname, 260)*2+2])

	lea ecx,pgname
	wcscpy(eax, ecx)

	mov ecx,__wargv
	mov [ecx],eax

	.if word ptr [eax] == '"'

	    .for edx = eax : word ptr [edx] : edx += 2

		mov ax,[edx+2]
		mov [edx],ax
	    .endf
	    .if word ptr [edx-4] == '"'
		mov word ptr [edx-4],0
	    .endif
	    mov eax,[ecx]
	.endif
    .endif
    mov _wpgmptr,eax
    ret

Install endp

.pragma init(Install, 4)

    end
