include direct.inc
include alloc.inc
include string.inc
include errno.inc
include ctype.inc
include winbase.inc

.code

_fullpath PROC USES esi edi ebx buf:LPSTR, path:LPSTR, maxlen:UINT
local drive:BYTE
local dchar:BYTE

    mov esi,path
    .if !esi || BYTE PTR [esi] == 0
	_getcwd(buf, maxlen)
	jmp @F
    .endif

    mov edi,buf
    .if !edi
	.if !malloc( _MAX_PATH )
	    mov errno,ENOMEM
	    jmp @F
	.endif
	mov edi,eax
	mov maxlen,_MAX_PATH
    .elseif maxlen < _MAX_DRIVE+1
	mov errno,ERANGE
	xor eax,eax
	jmp @F
    .endif

    mov ebx,edi
    mov edx,'\/'
    mov eax,[esi]
    .if ((al == dl || al == dh) && (ah == dl || ah == dh))
	mov ecx,ebx
	add ecx,maxlen
	dec ecx
	xor eax,eax
	.repeat
	    lodsb
	    mov [edi],al
	    .break .if !al
	    .if edi >= ecx
		jmp error_1
	    .endif
	    .if (al == dl || al == dh)
		mov [edi],dl
		inc ah
		.if ah == 2 && BYTE PTR [esi] == 0
		    mov errno,EINVAL
		    jmp error_2
		.endif
		.if ah >= 3
		    .if BYTE PTR [edi-1] == '\'
			mov errno,EINVAL
			jmp error_2
		    .endif
		.endif
	    .endif
	    inc edi
	.until ah == 4
	mov [edi],dl
	mov ecx,edi
    .else
	mov drive,0
	push eax
	movzx eax,al
	test byte ptr _ctype[eax*2+2],_UPPER or _LOWER
	pop eax
	.if !ZERO? && ah == ':'
	    mov [edi],ax
	    add edi,2
	    add esi,2
	    sub al,'A' + 1
	    and al,1Fh
	    mov drive,al
	    GetLogicalDrives()
	    movzx ecx,drive
	    dec ecx
	    shr eax,cl
	    sbb eax,eax
	    and eax,1
	    .if ZERO?
		mov errno,EACCES
		mov oserrno,ERROR_INVALID_DRIVE
		jmp error_2
	    .endif
	.endif
	mov al,[esi]
	.if al == '\' || al == '/'
	    .if drive == 0
		_getdrive()
		add al,'A'- 1
		stosb
		mov al,':'
		stosb
	    .endif
	    inc esi
	.else
	    .if drive
		mov al,[esi-2];	 c = *(path-2);
		mov dchar,al
	    .endif
	    movzx eax,drive
	    .if !_getdcwd(eax, ebx, maxlen)
		jmp error_2
	    .endif
	    strlen(ebx)
	    add eax,ebx
	    mov edi,eax
	    .if drive
		mov al,dchar
		mov [ebx],al;  *RetValue = c;
	    .endif
	    mov al,[edi-1]
	    .if al == '\' || al == '/'
		dec edi
	    .endif
	.endif
	mov BYTE PTR [edi],'\'
	lea ecx,[ebx+2]
    .endif
    .while BYTE PTR [esi] != 0
	mov ax,[esi]
	mov dl,[esi+2]
	.if (al == '.' && ah == '.' && (!dl || dl == '\' || dl == '/'))
	    .repeat
		dec edi
		mov al,[edi]
	    .until (al == '\' || al == '/' || edi <= ecx)
	    .if edi < ecx
		mov errno,EACCES
		jmp error_2
	    .endif
	    add esi,2
	    .if BYTE PTR [esi] != 0
		inc esi
	    .endif
	.elseif (al == '.' && ((ah == '\' || ah == '/') || !ah))
	    inc esi
	    .if BYTE PTR [esi] != 0
		inc esi
	    .endif
	.else
	    mov edx,edi
	    mov al,[esi]
	    .while (al && !(al == '\' || al == '/') && edi < ecx)
		lodsb
		inc edi
		mov [edi],al
	    .endw
	    .if edi >= ecx
		jmp error_1
	    .endif
	    .if edi == edx
		mov errno,EINVAL
		jmp error_2
	    .endif
	    inc edi
	    mov BYTE PTR [edi],'\'
	    mov al,[esi]
	    .if al == '\' || al == '/'
		inc esi
	    .endif
	.endif
    .endw
    .if BYTE PTR [edi-1] == ':'
	inc edi
    .endif
    mov BYTE PTR [edi],0
    mov eax,ebx
@@:
    ret
error_1:
    mov errno,ERANGE
error_2:
    .if !buf
	free( ebx )
    .endif
    xor eax,eax
    jmp @B
_fullpath ENDP

	END

