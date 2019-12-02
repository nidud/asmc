include consx.inc
include errno.inc
include string.inc
include confirm.inc
include zip.inc
include strlib.inc
include crtl.inc

PUBLIC	progress_dobj
PUBLIC	progress_size

    .data

progress_size	dq 0
progress_name	dd 0
progress_xpos	dd 0
progress_loop	dd 0
progress_args	db '%s',10,'  to',0
progress_dobj	S_DOBJ <_D_STDDLG,0,0,<4,9,72,6>,0,0>
old_console	dd 0

    .code

test_userabort proc
    .if getkey() == KEY_ESC
	.if confirm_continue(progress_name)
	    mov eax,ER_USERABORT
	.endif
    .endif
    test    eax,eax
    ret
test_userabort endp

progress_open proc uses edx ttl, function

    mov eax,console
    mov old_console,eax
    and console,not CON_SLEEP
    mov eax,ttl
    mov progress_name,eax
    xor eax,eax
    mov dword ptr progress_size,eax
    mov dword ptr progress_size[4],eax
    mov progress_xpos,4

    .if word ptr function
	mov progress_xpos,9
    .endif
    mov dl,at_background[B_Dialog]
    or	dl,at_foreground[F_Dialog]

    .if dlopen(&progress_dobj, edx, ttl)
	dlshow(&progress_dobj)
	.if word ptr function
	    mov dl,at_background[B_Dialog]
	    or	dl,at_foreground[F_DialogKey]
	    scputf(8, 11, edx, 0, &progress_args, function)
	.endif
	scputc(8, 13, 64, '°')
    .endif
    ret
progress_open endp

progress_set proc uses edx ecx ebx s1, s2, len:qword
    xor eax,eax
    .if progress_dobj.dl_flag & _D_ONSCR
	mov progress_loop,eax
	mov ebx,progress_xpos
	mov ecx,68
	sub ecx,ebx
	add ebx,4
	.if s1 != eax
	    strfn (s1)
	    mov progress_name,eax
	    mov eax,dword ptr len
	    mov dword ptr progress_size,eax
	    mov eax,dword ptr len[4]
	    mov dword ptr progress_size[4],eax
	    scpathl(ebx, 11, ecx, s1)
	    .if s2
		scpathl(ebx, 12, ecx, s2)
	    .endif
	    add ebx,4
	    sub ebx,progress_xpos
	    scputc(ebx, 13, 64, '°')
	.else
	    scpathl(ebx, 12, ecx, s2)
	.endif
	tupdate()
	test_userabort()
    .endif
    ret
progress_set endp

progress_close proc
    .if dlclose(&progress_dobj)
	mov eax,old_console
	and eax,CON_SLEEP
	or  console,eax
	xor eax,eax
	mov old_console,eax
    .endif
    mov eax,edx
    ret
progress_close endp

progress_update proc uses edx ecx ebx edi offs:qword
    local progress_64_0:dword
    local progress_64_4:dword
    movzx eax,progress_dobj.dl_flag
    and eax,_D_ONSCR
    .if eax
	mov edx,dword ptr progress_size[4]
	mov eax,dword ptr progress_size
	shrd	eax,edx,6
	shr edx,6
	mov progress_64_0,eax
	mov progress_64_4,edx
	mov ebx,eax
	mov edi,edx
	mov ecx,1
	mov edx,dword ptr offs[4]
	mov eax,dword ptr offs
	.while	edi < edx || ebx < eax
	    add ebx,progress_64_0
	    adc edi,progress_64_4
	    inc ecx
	    .break .if ecx == 64
	.endw
	mov eax,ecx
	.if eax != progress_loop
	    .if eax < progress_loop
		scputc(8, 13, 64, '°')
	    .endif
	    mov progress_loop,eax
	    scputc(8, 13, eax, 'Û')
	.endif
	test_userabort()
    .endif
    ret
progress_update endp

    END
