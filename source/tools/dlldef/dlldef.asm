include string.inc
include stdio.inc
include stdlib.inc
include winbase.inc
include tchar.inc

    .code

main proc
    .if rcx == 2
	mov rdi,[rdx+8]
	.if LoadLibrary(rdi)
	    mov r12,rax
	    mov rbx,strcpy(strrchr(rdi,'.'),".def")
	    .if fopen(rdi,"wt")
		mov r13,rax
		mov byte ptr [rbx],0
		fprintf(r13,"LIBRARY %s\nEXPORTS\n",rdi)
		mov eax,[r12+0x3C]
		mov eax,[r12+rax].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
		mov ebx,[r12+rax+0x18]
		mov esi,[r12+rax+0x20]
		add rsi,r12
		.while ebx
		    lodsd
		    fprintf(r13,"\"%s\"\n",addr [rax+r12])
		    dec ebx
		.endw
		fclose(r13)
	    .endif
	    FreeLibrary(r12)
	.endif
    .else
	printf("\nUsage: DLLDEF <dllname>.dll\n\n")
    .endif
    xor eax,eax
    ret
main endp

    end _tstart
