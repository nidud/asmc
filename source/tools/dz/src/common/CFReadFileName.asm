include io.inc
include malloc.inc
include string.inc
include stdlib.inc
include cfini.inc
include winbase.inc
include dzlib.inc

    .code

CFReadFileName proc uses esi edi ebx ini:LPINI, index:PVOID, file_flag:UINT

local buffer[1024]:sbyte

    mov eax,index
    mov ebx,[eax]
    xor edi,edi

    .while INIGetEntryID(ini, ebx)

	mov esi,eax
	inc ebx

	mov edi,index
	add edi,4

	.while strchr(esi, ',')

	    mov ecx,esi
	    lea esi,[eax+1]
	    xtol(ecx)
	    stosd
	.endw
	xor edi,edi

	ExpandEnvironmentStrings(esi, strcpy(&buffer, esi), 1024)

	lea esi,buffer
	.if filexist(esi) == file_flag

	    mov edi,_strdup(esi)
	    .break
	.endif
    .endw

    mov eax,index
    mov [eax],ebx
    mov eax,edi
    ret

CFReadFileName endp

    END
