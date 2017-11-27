include string.inc
include malloc.inc
include cfini.inc
include stdlib.inc
include winbase.inc
include dzlib.inc

    .code

__CFExpandCmd proc uses esi edi ini:LPINI, buffer:LPSTR, file:LPSTR

  local tmp

    mov tmp,alloca(0x8000)
    mov edi,eax
    mov esi,eax

    .if strrchr(strcpy(esi, strfn(file)), '.')

	.if byte ptr [eax+1] == 0

	    mov byte ptr [eax],0
	.else

	    lea esi,[eax+1]
	.endif
    .endif

    .if INIGetEntry(ini, esi)

	mov esi,eax
	strcpy(edi, eax)

	ExpandEnvironmentStrings(esi, edi, 0x8000 - 1)
	CFExpandMac(edi, file)
	strxchg(edi, ", ", "\r\n")
	strcpy(buffer, edi)
    .endif
    ret

__CFExpandCmd endp

    END
