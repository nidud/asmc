;
; TASM Clone for ASMC
;
; This is used to build the DOS version of Doszip
; from the Borland 3.1 IDE
;

stklen  equ	128

	.model  small
	.stack  stklen
	.code
	.386

start:  jmp	around
program db	"ASMC.EXE",0
	db	80 - ($ - offset program) dup(0)
command db	4
space	db	' -zf1'
args	db	0Dh
	db	128 - ($ - offset command) dup(0)
fcb_160 db	16 dup(0)
fcb_161 db	16 dup(0)
envseg  dw	0
cmdptr  dw	offset command
	dw	seg _TEXT
fcb_0P  dw	offset fcb_160
	dw	seg _TEXT
fcb_1P  dw	offset fcb_161
	dw	seg _TEXT
cmdline db	128 dup(?)
outfile dw	0
lstfile dw	0
envpath dd	0
option_?:
	mov	al,0
	call	exit
	db	'TASM Clone for ASMC. Public Domain. '
%	db	'(&@Date)',13,10
	db	'Syntax: TASM [options] source [,object] [,listing]',13,10
	db	13,10
	db	'/?',9,9,	'Display this help screen',13,10
	db	'/h',9,9,	'Display ASMC help screen',13,10
	db	'/l',9,9,	'Generate listing',13,10
	db	'/c',9,9,	'Generate cross-reference in listing',13,10
	db	'/n',9,9,	'Suppress symbol tables in listing',13,10
	db	'/x',9,9,	'Include false conditionals in listing',13,10
	db	'/la',9,9,	'Maximize source listing',13,10
	db	'/zd',9,9,	'Debug info: line numbers only',13,10
	db	'/zi',9,9,	'Debug info: line numbers only',13,10
	db	'/dSYM[=VAL]',9,'Define symbol SYM = 0, or = value VAL',13,10
	db	'/iPATH',9,9,	'Search PATH for include files',13,10
	db	'/e',9,9,	'Emulated floating-point instructions',13,10
	db	'/t',9,9,	'Suppress messages if successful assembly',13,10
	db	'/w0,/w1,/w2',9,'Set warning level: w0=none, w1=w2=warnings on',13,10
	db	'$'
	;
	; Options ignored
	;
option_a:
option_s:
option_r:
option_j:
option_k:
option_m:
option_o:
option_p:
option_q:
option_u:
	ret
option_e:
	mov	ax,'- '
	stosw
	mov	ax,'pF'
	stosw
	mov	ax,'i'
	stosb
	ret
option_c:
	mov	ax,'- '
	stosw
	mov	ax,'gS'
	stosw
	ret
option_i:
option_d:
	mov	al,'-'
	push	si
	call	add_string
	pop	si
	ret
option_h:
	mov	ax,'- '
	stosw
	mov	ax,'h'
	stosb
	ret
option_l:
	mov	al,[si+1]
	or	al,20h
	cmp	al,'a'
	je	@F
	mov	ax,'- '
	stosw
	mov	ax,'aS'
	stosw
     @@:
	mov	ax,'- '
	stosw
	mov	ax,'lZ'
	stosw
	ret
option_n:
	mov	ax,'- '
	stosw
	mov	ax,'nS'
	stosw
	ret
option_t:
	mov	ax,'- '
	stosw
	mov	ax,'q'
	stosb
	ret
option_w:
	cmp	byte ptr [si+1],'-'
	je	@F
	mov	al,'W'
	mov	[si],al
	jmp	option_d
     @@:
	ret
option_x:
	mov	ax,'- '
	stosw
	mov	ax,'xS'
	stosw
	ret
option_z:
	mov	al,[si+1]
	or	al,20h
	cmp	al,'i'
	je	@F
	cmp	al,'d'
	je	@F
	mov	word ptr es:[di],'- '
	add	di,2
	mov	ah,'Z'
	xchg	ah,al
	stosw
	ret
     @@:
	mov	ax,'- '
	stosw
	mov	ax,'dZ'
	stosw
	ret
option_label label word
	dw	offset option_a
	dw	offset option_s
	dw	offset option_c
	dw	offset option_d
	dw	offset option_e
	dw	offset option_r
	dw	offset option_h
	dw	offset option_?
	dw	offset option_i
	dw	offset option_j
	dw	offset option_k
	dw	offset option_l
	dw	offset option_m
	dw	offset option_n
	dw	offset option_o
	dw	offset option_p
	dw	offset option_q
	dw	offset option_t
	dw	offset option_u
	dw	offset option_w
	dw	offset option_x
	dw	offset option_z
	dw	offset option_?
option_count = (($ - offset option_label) / 2)
options db	'ascderh?ijklmnopqtuwxz',0
getoutfile:
	push	si
	mov	ah,0
     @@:
	lodsb
	cmp	al,ah
	je	@F
	cmp	al,0Dh
	je	@F
	cmp	al,','
	jne	@B
     @@:
	mov	[si-1],ah
	cmp	al,','
	mov	al,0
	jne	@F
	call	getoutfile
	mov	lstfile,ax
	mov	outfile,si
	mov	ax,si
     @@:
	or	ax,ax
	pop	si
	ret
add_string:
	mov	ah,al
	mov	al,' '
	stosb
	mov	al,ah
     @@:
	stosb
	lodsb
	or	al,al
	jz	@F
	cmp	al,'-'
	je	@F
	cmp	al,'/'
	je	@F
	cmp	al,'+'
	je	@F
	cmp	al,' '
	jne	@B
     @@:
	ret
strcpy:
	push	si
	push	di
	push	ds
	pop	es
	mov	di,ax
	mov	si,dx
	mov	dx,ax
	cld
     @@:
	lodsb
	stosb
	or	al,al
	jnz	@B
	mov	ax,dx
	pop	di
	pop	si
	ret
filexist:
	push	bx
	mov	dx,ax
	mov	ax,4300h
	int	21h
	pop	bx
	mov	ax,-1
	jc	@F
	mov	ax,cx
     @@:
	inc	ax
	jz	@F
	dec	ax	; 1 = file
	and	ax,10h  ; 2 = subdir
	shr	ax,4
	inc	ax
     @@:
	ret
searchp:
	lea	ax,program
	call	filexist
	jz	@F
	ret
     @@:
	les	di,envpath
	test	di,di
	jnz	searchp_do
	ret
    searchp_do:
	lea	si,cmdline
     @@:
	mov	al,es:[di]
	test	al,al
	jz	@F
	cmp	al,';'
	je	@F
	mov	[si],al
	inc	di
	inc	si
	jmp	@B
     @@:
	mov	al,'\'
	mov	[si],al
	inc	si
	lea	bx,program
     @@:
	mov	al,[bx]
	test	al,al
	jz	@F
	mov	[si],al
	inc	bx
	inc	si
	jmp	@B
     @@:
	lea	ax,cmdline
	call	filexist
	jz	@F
	lea	ax,program
	lea	dx,cmdline
	call	strcpy
	test	ax,ax
	ret
     @@:
	mov	al,es:[di]
	cmp	al,';'
	jne	@F
	inc	di
	jmp	searchp_do
     @@:
	xor	ax,ax
	ret
around:
	mov	ax,cs
	mov	ds,ax
	mov	bx,002Ch
	mov	bp,es
	mov	ax,es:[bx]
	assume  ds:_TEXT
	mov	envseg,ax
	mov	dx,ss
	mov	bx,((stklen shr 4) + 1)
	add	bx,dx
	mov	ax,es
	sub	bx,ax
	mov	es,ax
	mov	ah,4Ah
	int	21h
	mov	bx,envseg
	mov	es,bx
	xor	ax,ax
	mov	di,ax
	mov	cx,7FFFh
	cld
cmppath:
	cmp	DWORD PTR es:[di],'HTAP'	; 'PATH'
	jne	@F
	cmp	BYTE PTR es:[di+4],'='
	jne	@F
	mov	dx,di
	add	dx,5
	mov	WORD PTR envpath,dx
	mov	WORD PTR envpath+2,es
     @@:
	repnz	scasb
	or	cx,cx
	jz	errorlevel_10
	cmp	es:[di],al
	jne	cmppath
	call	searchp
	jnz	parse_command_line
	mov	al,2
	call	exit
	db	'File not found: ASMC.EXE',13,10,'$'
    errorlevel_10:
	mov	al,10
	call	exit
	db	'Environment invalid',13,10,'$'
    parse_command_line:
	mov	ax,ds
	mov	es,ax
	mov	si,offset program
	mov	di,offset fcb_160
	mov	ax,2901h
	int	21h
	mov	si,offset program
	mov	di,offset fcb_161
	mov	ax,2901h
	int	21h
	mov	ds,bp
	mov	di,offset cmdline
	mov	si,128
	mov	cx,64
	rep	movsw
	mov	ax,es
	mov	ds,ax
	mov	di,offset args
	mov	si,offset cmdline
	lodsb
	or	al,al
	jz	option_?
	lodsb
	call	getoutfile
	jz	command_getc
	mov	bx,ax
	mov	ax,'- '
	stosw
	mov	ax,'oF'
	stosw
     @@:
	mov	al,[bx]
	inc	bx
	stosb
	or	al,al
	jnz	@B
	dec	di
	mov	bx,lstfile
	or	bx,bx
	jz	command_getc
	mov	ax,'- '
	stosw
	mov	ax,'lF'
	stosw
	mov	al,'='
	stosb
     @@:
	mov	al,[bx]
	inc	bx
	stosb
	or	al,al
	jnz	@B
	dec	di
    command_getc:
	lodsb
	cmp	al,' '
	je	command_getc
	cmp	al,'+'
	je	command_getc
	cmp	al,';'
	je	command_eol
	or	al,al
	jz	command_eol
	cmp	al,'-'
	je	case_switch
	cmp	al,'/'
	je	case_switch
	call	add_string
	dec	si
	mov	ax,'a.'
	cmp	[si-4],al
	je	command_getc
	stosw
	mov	ax,'ms'
	stosw
	jmp	command_getc
    case_switch:
	xor	ax,ax
	mov	bx,ax
	mov	al,[si]
	or	al,20h
     @@:
	cmp	[bx+options],al
	je	@F
	inc	bx
	cmp	[bx+options],ah
	jne	@B
	jmp	command_next
     @@:
	add	bx,bx
	call	option_label[bx]
    command_next:
	lodsb
	cmp	al,' '
	je	@F
	or	al,al
	jz	@F
	cmp	al,'-'
	je	@F
	cmp	al,'/'
	jne	command_next
     @@:
	or	al,al
	jnz	command_getc
    command_eol:
	mov	ax,0Dh
	stosw
	mov	ax,di
	sub	ax,offset command
	mov	command,al
	mov	bx,offset envseg
	mov	dx,offset program
	mov	ax,4B00h
	int	21h
	mov	ah,4Dh
	int	21h
	mov	si,ax		; errorlevel
	mov	dx,offset space ; invoke STDOUT and STDERR
	mov	cx,1
	mov	bx,cx
	mov	ah,40h
	int	21h
	inc	bx
	mov	ah,40h
	int	21h
	mov	ax,si
	jmp	terminate
exit:
	pop	dx
	push	ax
	mov	ah,09h
	int	21h
	pop	ax
terminate:
	mov	ah,4Ch
	int	21h
	end	start
