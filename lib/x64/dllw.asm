include string.inc
include stdio.inc
include winbase.inc
include tchar.inc

    .code

main proc
    mov rsi,rdx
    .if rcx == 2
	mov rdi,[rsi+8]
	.if LoadLibrary(rdi)
	    mov r12,rax
	    mov rbx,strcpy(strrchr(rdi,'.'),".lbc")
	    .if fopen(rdi,"wt")
		mov r13,rax
		mov byte ptr [rbx],0
		_strupr(rdi)
		mov eax,[r12+0x3C]
		add rax,r12
		mov eax,[rax].IMAGE_NT_HEADERS.OptionalHeader.DataDirectory.VirtualAddress
		add rax,r12
		mov ebx,[rax+0x18]
		mov esi,[rax+0x20]
		add rsi,r12
		.while ebx
		    lodsd
		    add rax,r12
		    fprintf(r13,"++%s.\'%s.dll\'\n",rax,rdi)
		    dec ebx
		.endw
		fclose(r13)
	    .endif
	    FreeLibrary(r12)
	    xor eax,eax
	.else
	    printf("DLL not found: %s\n\n",rdi)
	    mov eax,1
	.endif
    .else
	printf("\nUsage: DLBC <dllname>.dll\n\n")
	mov eax,1
    .endif
    ret
main endp

    end _tstart
