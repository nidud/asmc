include stdlib.inc
include malloc.inc
include io.inc
include cfini.inc
include string.inc
include process.inc
include dzlib.inc

extern	__comspec:byte

    .code

__CFGetComspec proc uses esi edi ebx ini:LPINI, value:UINT

local buffer[512]:byte

    mov esi,value
    mov comspec_type,esi

    __initcomspec()
    strcpy(__pCommandArg, "/C")

    .if esi

	.if INIGetSection(ini, addr __comspec)

	    mov esi,eax
	    lea ebx,buffer

	    .if INIGetEntryID(esi, 0)

		.if !_access(expenviron(strcpy(ebx, eax)), 0)

		    free(__pCommandCom)
		    mov __pCommandCom,_strdup(ebx)

		    mov eax,__pCommandArg
		    mov byte ptr [eax],0

		    .if INIGetEntryID(esi, 1)

			expenviron(strcpy(ebx, eax))
			strncpy(__pCommandArg, eax, 64-1)
		    .endif
		.endif
	    .endif
	.endif
    .endif
    mov eax,__pCommandCom
    ret

__CFGetComspec endp

    END
