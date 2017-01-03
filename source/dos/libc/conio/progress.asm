; PROGRESS.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include errno.inc
include string.inc
include mouse.inc
include keyb.inc
include confirm.inc
include math.inc

	PUBLIC	progress_dobj
	PUBLIC	progress_size

	.data
	progress_64	dd 0
	progress_size	dd 0
	progress_name	dd 0
	progress_xpos	dw 0
	progress_args	db '%s',10,'  to',0
	progress_dobj	S_DOBJ <_D_STDDLG,0,0,<4,9,72,6>,0,0>

	.code

test_userabort:
	.if getesc()
	    .if confirm_continue(progress_name)
		mov ax,ER_USERABORT
	    .endif
	.endif
	ret

progress_open PROC _CType PUBLIC USES dx ttl:DWORD, function:DWORD
	movmx progress_name,ttl
      ifdef __16__
	xor ax,ax
	mov WORD PTR progress_size,ax
	mov WORD PTR progress_size+2,ax
      else
	xor eax,eax
	mov progress_size,eax
      endif
	mov progress_xpos,4
	.if WORD PTR function
	    mov progress_xpos,9
	.endif
	mov dl,at_background[B_Dialog]
	or  dl,at_foreground[F_Dialog]
	.if dlopen(addr progress_dobj,dx,ttl)
	    invoke dlshow,addr progress_dobj
	    .if WORD PTR function
		mov dl,at_background[B_Dialog]
		or  dl,at_foreground[F_DialogKey]
		invoke scputf,8,11,dx,0,addr progress_args,function
	    .endif
	    invoke scputc,8,13,64,'°'
	.endif
	ret
progress_open ENDP

progress_set PROC _CType PUBLIC USES dx cx bx s1:DWORD, s2:DWORD, len:DWORD
	sub ax,ax
	.if progress_dobj.dl_flag & _D_ONSCR
	    mov bx,progress_xpos
	    mov cx,68
	    sub cx,bx
	    add bx,4
	    .if WORD PTR s1
	      ifndef __16__
		mov eax,len
		mov progress_size,eax
		shr eax,6
		mov progress_64,eax
	      else
		mov ax,WORD PTR len+2
		mov WORD PTR progress_size+2,ax
		mov dl,al
		shr ax,6
		mov WORD PTR progress_64+2,ax
		mov ax,WORD PTR len
		mov WORD PTR progress_size,ax
		shr ax,6
		shl dl,2
		or ah,dl
		mov WORD PTR progress_64,ax
	      endif
		invoke scputc,bx,11,cx,' '
		invoke scpath,bx,11,cx,s1
		invoke scputc,bx,12,cx,' '
		invoke scpath,bx,12,cx,s2
		add bx,4
		sub bx,progress_xpos
		invoke scputc,bx,13,64,'°'
	    .else
		invoke scputc,bx,12,cx,' '
		invoke scpath,bx,12,cx,s2
	    .endif
	    invoke strfn,s1
	    stom progress_name
	    call tupdate
	    call test_userabort
	.endif
	ret
progress_set ENDP

progress_close PROC _CType PUBLIC
	invoke dlclose,addr progress_dobj
	mov ax,dx
	ret
progress_close ENDP

progress_update PROC _CType PUBLIC USES dx cx offs:DWORD
	.if !(progress_dobj.dl_flag & _D_ONSCR)
	    sub ax,ax
	    jmp update_end
	.endif
    ifdef __16__
	push di
	push bx
	mov di,1
	mov ax,WORD PTR progress_64
	mov dx,WORD PTR progress_64+2
	mov bx,WORD PTR offs
	mov cx,WORD PTR offs+2
	.repeat
	    .if dx == cx
		.break .if ax >= bx
	    .endif
	    .break .if dx > cx
	    add ax,WORD PTR progress_64
	    adc dx,WORD PTR progress_64+2
	    inc di
	.until di == 64
	mov cx,di
	pop bx
	pop di
    else
	mov cx,1
	mov eax,progress_64
	mov edx,offs
	.repeat
	    .break .if eax >= edx
	    add eax,progress_64
	    inc cx
	.until cx == 64
    endif
	invoke scputc,8,13,cx,'Û'
	call test_userabort
    update_end:
	ret
progress_update ENDP

	END
