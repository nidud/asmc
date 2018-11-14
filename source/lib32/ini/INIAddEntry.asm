; INIADDENTRY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include ini.inc
include ltype.inc
include string.inc
include strlib.inc

    .code

INIAddEntry proc __cdecl uses esi edi ebx cf:LPINI, string:LPSTR

    xor edi,edi
    mov esi,string

    movzx eax,byte ptr [esi]
    .while _ltype[eax+1] & _SPACE

	add esi,1
	mov al,[esi]
    .endw

    .repeat
	.if al == ';'

	    .break .if !INIAlloc()

	    mov edi,eax
	    strtrim(esi)
	    mov [edi].S_INI.flags,INI_COMMENT
	    mov [edi].S_INI.entry,_strdup(esi)
	    mov eax,edi

	.elseif strchr(esi, '=')

	    mov byte ptr [eax],0
	    lea edi,[eax+1]

	    movzx eax,byte ptr [edi]
	    .while _ltype[eax+1] & _SPACE

		add edi,1
		mov al,[edi]
	    .endw

	    .break .if !strtrim(esi)
	    mov ebx,eax
	    .break .if !strtrim(edi)
	    lea ebx,[ebx+eax+2]

	    .if INIGetEntry(cf, esi)

		mov eax,[ecx].S_INI.next
		.if !edx
		    mov edx,cf
		    mov [edx].S_INI.value,eax
		.else
		    mov [edx].S_INI.next,eax
		.endif
		push ecx
		free([ecx].S_INI.entry)
		pop eax
		free(eax)
	    .endif
	    .break .if !INIAlloc()

	    xchg ebx,eax
	    .break .if !malloc(eax)

	    mov [ebx].S_INI.entry,eax
	    strcat(strcat(strcpy(eax, esi), "="), edi)
	    strchr(eax, '=')
	    mov byte ptr [eax],0
	    inc eax
	    mov [ebx].S_INI.value,eax

	    mov eax,ebx
	    mov [eax].S_INI.flags,INI_ENTRY
	.endif

	mov edx,cf
	mov ecx,[edx].S_INI.value
	.if ecx
	    .while [ecx].S_INI.next

		mov ecx,[ecx].S_INI.next
	    .endw
	    mov [ecx].S_INI.next,eax
	.else
	    mov [edx].S_INI.value,eax
	.endif
    .until 1
    ret

INIAddEntry endp

    END
