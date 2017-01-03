; CLIP.ASM--
; Copyright (C) 2015 Doszip Developers

include clip.inc
include string.inc
include conio.inc
include alloc.inc

.data
winoldap  dw ?
clipbsize dw ?
clipboard dd ?

.code

OpenClipboard PROC PRIVATE
	sub ax,ax
	.if winoldap != ax
	    mov ax,1701h	; OPEN CLIPBOARD
	    int 2Fh		; nonzero success, else already open
	    inc ax
	.endif
	ret
OpenClipboard ENDP

CloseClipboard PROC PRIVATE
	push	dx
	push	ax
	mov	ax,1708h	; INT 2F - MS Windows - CloseClipboard
	int	2Fh
	pop	ax
	pop	dx
	ret
CloseClipboard ENDP

ClearClipboard PROC PRIVATE
	invoke	free,clipboard
	sub	ax,ax
	mov	clipbsize,ax
	mov	dx,ax
	stom	clipboard
	ret
ClearClipboard ENDP

ClipboardFree PROC _CType PUBLIC
	invoke	ClearClipboard
	ret
ClipboardFree ENDP

ClipboardCopy PROC _CType PUBLIC USES si di bx string:DWORD, len:size_t
	mov di,len
	call ClearClipboard
	.if console & CON_CLIPB
	    call OpenClipboard
	    .if !ZERO?
		mov ax,1702h	; EMPTY CLIPBOARD
		int 2Fh		; AX nonzero clipboard has been emptied
		mov dx,1	; set type to text
		mov cx,di	; SI:CX = size of data
		xor si,si	; HSIZE = 0
		les bx,string	; ES:BX = data
		mov ax,1703h	; SET CLIPBOARD DATA
		int 2Fh
		call CloseClipboard
		test ax,ax	; nonzero data copied into the Clipboard
		mov  ax,di
		jnz  @F
	    .endif
	    mov ax,di
	    inc ax
	    .if malloc(ax)
		stom clipboard
		mov clipbsize,di
		mov es,dx
		mov bx,ax
		add bx,di
		mov BYTE PTR es:[bx],0
		invoke memcpy,dx::ax,string,di
		mov ax,di
	    .endif
	.endif
      @@:
	ret
ClipboardCopy ENDP

ClipboardPaste PROC _CType PUBLIC USES bx
	.if (console & CON_CLIPB)
	    mov ax,1701h	; OPEN CLIPBOARD
	    int 2Fh		; nonzero success, else already open
	    mov ax,1704h	; GET CLIPBOARD DATA SIZE
	    mov dx,1		; DX = clipboard format supported
	    int 2Fh		; DX:AX = size of data in bytes
	    .if dx
		sub ax,ax	; to big..
	    .endif
	    call CloseClipboard
	    .if !ax || ax >= MAXCLIPSIZE
		sub ax,ax
		.if clipbsize != ax
		    lodm clipboard
		.endif
	    .else
		push ax
		push ax
		call ClearClipboard
		call malloc
		pop cx
		.if ax
		    mov clipbsize,cx
		    stom clipboard
		    invoke memzero,dx::ax,cx
		    mov ax,1701h
		    int 2Fh
		    mov dx,1
		    les bx,clipboard
		    mov ax,1705h
		    int 2Fh
		    call CloseClipboard
		    lodm clipboard
		.endif
	    .endif
	.else
	    .if clipbsize
		lodm clipboard
	    .else
		sub ax,ax
		cwd
	    .endif
	.endif
	test ax,ax
	ret
ClipboardPaste ENDP

Install:
	.if console & CON_CLIPB
	    mov ax,1700h
	    int 2Fh
	    mov dx,ax
	    xor ax,ax		; AX <> 1700h
	    .if dx != 1700h	; - AL = WINOLDAP major version
		inc ax		; - AH = WINOLDAP minor version
	    .endif
	    mov winoldap,ax
	.endif
	ret

_TEXT	ENDS

pragma_init Install,12

	END
