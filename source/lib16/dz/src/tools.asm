; TOOLS.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT
;

include doszip.inc
include ini.inc
include string.inc
include conio.inc
include mouse.inc

PUBLIC	cmtool1
PUBLIC	cmtool2
PUBLIC	cmtool3
PUBLIC	cmtool4
PUBLIC	cmtool5
PUBLIC	cmtool6
PUBLIC	cmtool7
PUBLIC	cmtool8
PUBLIC	cmtool9
PUBLIC	tools_idd

ID_MTOOLS equ 4

_DZIP	segment

stostart:
	lodsb
	cmp	al,' '
	je	stostart
	cmp	al,9
	je	stostart
	dec	si
	ret

readtools:
	mov di,si
      @@:
	.if inientryid([bp+4],di)
	    cld?
	    mov si,ax
	    push ax
	    call stostart
	    push si
	    mov cx,36
	    .while cx
		lodsb
		.break .if !al
		.if al == ',' || al == '<'
		    .if al == ','
			xor ax,ax
			mov [si-1],al	; terminate text line
			call stostart	; start of command tail
			mov cx,[bp+12]
			les bx,[bp-8]
			les bx,es:[bx].S_TOBJ.to_data
			xchg di,bx
			.while cx
			    lodsb
			    .break .if !al || al == ']'
			    .if al == '['
				mov ah,al
				.continue
			    .endif
			    stosb
			    dec cx
			.endw
			mov al,0
			stosb
			mov di,bx
			.if ah
			    les bx,[bp-8]
			    or es:[bx].S_TOBJ.to_flag,_O_FLAGB
			.endif
		    .endif
		    pop si
		    les bx,[bp-4]
		    mov ax,76
		    mul di
		    add ax,78
		    les bx,es:[bx].S_DOBJ.dl_wp
		    add bx,ax
		    .if BYTE PTR [si] == '<'
			invoke wcputw,es::bx,38,00C4h
			les bx,[bp-8]
			and es:[bx].S_TOBJ.to_flag,not _O_FLAGB
		    .else
			add bx,4
			invoke wcputs,es::bx,0,32,ds::si
			les bx,[bp-8]
			mov ax,not _O_STATE
			and es:[bx].S_TOBJ.to_flag,ax
			invoke strchr,ds::si,'&'
			.if ax
			    mov es,dx
			    mov bx,ax
			    inc bx
			    mov al,es:[bx]
			    les bx,[bp-8]
			    mov es:[bx].S_TOBJ.to_ascii,al
			    pop si
			    inc si
			    push si
			.endif
		    .endif
		    pop si
		    add WORD PTR [bp-8],16
		    inc di
		    .if di >= 20
			jmp @F
		    .endif
		    jmp @B
		.endif
		dec cx
	    .endw
	    pop ax
	    pop si
	    invoke inierror,[bp+4],ds::ax
	    sub ax,ax
	    ret
	.endif
      @@:
	test di,di
	ret

tools_idd PROC pascal USES si di l:WORD, p:DWORD, s:DWORD
local buf[450]:BYTE
	.repeat
	    xor si,si
	    mov ax,ID_MTOOLS
	    call open_idd
	    .if !ZERO?
		call readtools
		.if ZERO?
		    mov bx,ID_MTOOLS
		    call close_idd
		    invoke dlclose,[bp-4]
		    .break
		.endif
		les bx,[bp-4]
		mov ax,di
		mov es:[bx].S_DOBJ.dl_count,al
		add al,2
		mov es:[bx].S_DOBJ.dl_rect.S_RECT.rc_row,al
		mov ah,al
		mov al,es:[bx].S_DOBJ.dl_rect.S_RECT.rc_col
		mov dl,al
		mov dh,0
		sub cx,cx
		invoke rcframe,ax::cx,es:[bx].S_DOBJ.dl_wp,dx,cx
		invoke strnzcpy,addr [bp-450],s,16
		mov BYTE PTR [bp-450+16],0
		mov bx,ID_MTOOLS
		call modal_idd
		mov ax,si
		shl ax,4
		les bx,[bp-4]
		add bx,ax
		invoke strnzcpy,addr [bp-450],es:[bx].S_TOBJ.to_data,l
		les bx,[bp-4]
		sub ax,ax
		mov al,es:[bx].S_DOBJ.dl_count
		invoke dlclose,[bp-4]
		.if si && dx >= si
		    lea ax,[bp-450]
		    mov dx,[bp+8]
		    mov cx,[bp+10]
		    .if di == _O_FLAGB
			mov [bp+4],ax
			mov [bp+6],ss
			.continue
		    .endif
		    .if dx
			invoke strcpy,cx::dx,ss::ax
			call msloop
		    .else
			invoke command,ss::ax
			mov si,ax
		    .endif
		.endif
	      ifdef __MOUSE__
		.if mousep()
		    mov si,MOUSECMD
		.endif
	      endif
	    .endif
	    .break
	.until 0
	mov ax,si
	ret
tools_idd ENDP

cmtool PROC _CType PRIVATE USES si di
local tool[128]:BYTE
	.if inientryid(addr cp_tools,ax)
	    mov si,ax
	    mov ax,[si]
	    .if ax != '><'
		.if strchr(ds::si,',')
		    inc ax
		    mov di,ax
		    invoke strstart,ds::di
		    mov bx,ax
		    invoke strnzcpy,addr [bp-128],dx::bx,128
		    .if BYTE PTR [bp-128] == '['
			mov cx,ax
			inc ax
			invoke strcpy,dx::cx,dx::ax
			.if strchr(dx::ax,']')
			    mov bx,ax
			    mov BYTE PTR ss:[bx],0
			    invoke tools_idd,128,0,addr [bp-128]
			.endif
		    .else
			invoke command,dx::ax
		    .endif
		.endif
	    .endif
	.endif
	ret
cmtool	ENDP

CMTOOLP macro q
cmtool&q PROC _CType
	mov ax,q-1
	jmp cmtool
cmtool&q ENDP
	endm

CMTOOLP 1
CMTOOLP 2
CMTOOLP 3
CMTOOLP 4
CMTOOLP 5
CMTOOLP 6
CMTOOLP 7
CMTOOLP 8
CMTOOLP 9

_DZIP	ENDS

	END
