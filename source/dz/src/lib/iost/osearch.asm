include iost.inc
include string.inc

    .data

hexstring dd 0
hexstrlen dd 0
externdef searchstring:byte

    .code

searchtxt:
    xor ecx,ecx
    xor edx,edx
    mov dl,searchstring
    bt	STDI.ios_flag,0
    jnc nocase
@@:
    ogetc()
    jz	notfound
    add edi,1
    adc ebx,0
    cmp eax,edx
    je	charfound
    cmp eax,10
    jne @B
    inc ecx
    jmp @B

nocase:
    mov eax,edx
    sub al,'A'
    cmp al,'Z'-'A'+1
    sbb edx,edx
    and edx,'a'-'A'
    add eax,edx
    add eax,'A'
    mov edx,eax	    ; tolower(*searchstring)
@@:
    ogetc()
    jz	notfound
    add edi,1
    adc ebx,0
    sub al,'A'
    cmp al,'Z'-'A'+1
    sbb ah,ah
    and ah,'a'-'A'
    add al,ah
    add al,'A'	    ; tolower(AL)
    cmp al,dl
    je	charfound
    cmp eax,10
    jne @B
    inc ecx
    jmp @B

charfound:
    add STDI.ios_line,ecx
    lea esi,searchstring
    mov eax,hexstrlen
    mov ecx,STDI.ios_c
    sub ecx,STDI.ios_i
    cmp eax,ecx
    jb	compare
    test STDI.ios_flag,IO_MEMBUF
    jnz notfound
    ioread(&STDI)
    jz	notfound

compare:
    ogetc()
    jz	notfound
    add edi,1
    adc ebx,0
    inc esi
    lea edx,searchstring
    mov ecx,eax
    mov al,[esi]
    test    eax,eax
    jz	success
    cmp eax,ecx
    je	compare
    bt	STDI.ios_flag,0 ; IO_SEARCHCASE
    jc	@F
    mov ah,cl
    sub ax,'AA'
    cmp al,'Z'-'A' + 1
    sbb cl,cl
    and cl,'a'-'A'
    cmp ah,'Z'-'A' + 1
    sbb ch,ch
    and ch,'a'-'A'
    add ax,cx
    add ax,'AA'
    cmp al,ah
    je	compare
@@:
    mov eax,esi
    sub eax,edx
    sub edi,eax
    sbb ebx,0
    sub STDI.ios_i,eax
    jmp searchtxt

success:
    mov eax,esi
    sub eax,edx
    inc eax
    sub edi,eax
    sbb ebx,0
    mov eax,edi
    mov edx,ebx
    or	edi,1
    mov ecx,STDI.ios_line
    ret

notfound:
    or	eax,-1
    mov edx,eax
    xor ebx,ebx
    ret

searchhex:
    xor ecx,ecx
    lea esi,searchstring
    mov edx,hexstring
getlen:
    lodhex()
    jz	hexlen
    mov ah,al
    lodhex()
    jnz @F
    xchg al,ah
@@:
    shl ah,4
    or	al,ah
    mov [edx],al
    inc edx
    inc ecx
    jmp getlen
hexlen:
    mov hexstrlen,ecx
scanhex:
    mov eax,hexstring
    movzx edx,byte ptr [eax]
    mov ecx,STDI.ios_line
@@:
    ogetc()
    jz	notfound
    add edi,1	; inc offset
    adc ebx,0
    cmp al,dl
    je	@F
    cmp al,10
    jne @B
    inc ecx ; inc line
    jmp @B
@@:
    mov STDI.ios_line,ecx
    mov esi,hexstring
    mov eax,hexstrlen
    mov ecx,STDI.ios_c
    sub ecx,STDI.ios_i
    cmp eax,ecx
    jb	@F
    test STDI.ios_flag,IO_MEMBUF
    jnz notfound
    ioread(&STDI)
    jz	notfound
@@:
    ogetc()
    jz	notfound
    add edi,1
    adc ebx,0
    inc esi
    mov edx,hexstring
    mov ecx,esi
    sub ecx,edx
    cmp ecx,hexstrlen
    je	success
    cmp al,[esi]
    je	@B
    mov eax,esi
    sub eax,edx
    sub edi,eax
    sbb ebx,0
    sub STDI.ios_i,eax
    jmp scanhex

lodhex:
    mov al,[esi]
    test    al,al
    jz	hexnull
    inc esi
    cmp al,'0'
    jb	lodhex
    cmp al,'9'
    jbe hexdigit
    or	al,20h
    cmp al,'f'
    ja	lodhex
    sub al,27h
hexdigit:
    sub al,'0'
    test esi,esi
hexnull:
    ret

osearch proc uses esi edi ebx

  local hex[128]:byte

    mov eax,dword ptr STDI.ios_offset
    mov edx,dword ptr STDI.ios_offset[4]
    mov ecx,STDI.ios_flag
    and STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)
    .if ecx & IO_SEARCHSET
	xor eax,eax
	xor edx,edx
    .elseif !(ecx & IO_SEARCHCUR)
	add eax,1	; offset++ (continue)
	adc edx,0
    .endif
    ioseek(&STDI, edx::eax, SEEK_SET)
    .ifnz
	mov edi,eax
	mov ebx,edx
	.if STDI.ios_flag & IO_SEARCHHEX
	    lea ecx,hex
	    mov hexstring,ecx
	    searchhex()
	.else
	    strlen(addr searchstring)
	    mov hexstrlen,eax
	    .ifnz
		searchtxt()
	    .endif
	.endif
    .endif
    ret

osearch endp

    END
