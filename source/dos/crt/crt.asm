; CRT.ASM--
;
; Startup module for DOS
;
ifndef __c__
   ifndef __l__
	.err <you must supply a model symbol>
   endif
endif

	.186

_CType	equ <pascal>

FCODE	equ 8000h
FDATA	equ 4000h

  ifdef __c__
	DIST	equ <near>
	MMODEL	equ FDATA+3
  endif

  ifdef __l__
	DIST	equ <far>
	LPROG	equ 1
	MMODEL	equ FCODE+FDATA+4
  endif

  ifdef __WCC__
	C0_main equ <main_>
	main_ proto DIST pascal
  else
	C0_main equ <main>
	main proto DIST c
  endif

__BSS__ equ 1

_TEXT	segment word public 'CODE'
_TEXT	ends
_DATA	segment PARA public 'DATA'
_DATA	ends
_INIT	segment word public 'INIT'
_INIT	ends
_IEND	segment word public 'INIT'
_IEND	ends
_EXIT	segment word public 'EXIT'
_EXIT	ends
_EEND	segment word public 'EXIT'
_EEND	ends
ifdef __WCC__
CONST	segment word public 'DATA'
CONST	ends
CONST2	segment word public 'DATA'
CONST2	ends
endif
ifdef __BSS__
_BSS	segment word public 'BSS'
_BSS	ends
_BSSEND segment word public 'BSSEND'
_BSSEND ends
endif
_STACK	segment STACK 'STACK'
_STACK	ends

 ifdef __WCC__
	DGROUP GROUP _DATA,CONST,CONST2,_EXIT,_EEND,_INIT,_IEND,_BSS,_BSSEND,_STACK
 else
  ifdef __BSS__
	DGROUP GROUP _DATA,_EXIT,_EEND,_INIT,_IEND,_BSS,_BSSEND,_STACK
  else
	DGROUP GROUP _DATA,_EXIT,_EEND,_INIT,_IEND,_STACK
  endif
 endif

	extrn	_stklen: word

_TEXT	segment
	ASSUME	cs:_TEXT
start:	mov	ah,30h
	int	21h
	mov	bp,ds:[0002h]
	mov	bx,ds:[002Ch]
	mov	dx,SEG _DATA
	mov	ds,dx
	ASSUME	ds:DGROUP
	mov	_osversion,ax
	mov	_psp,es
	mov	envseg,bx
	mov	heaptop,bp
	call	SAVE_VECTORS
	mov	ax,envseg
	mov	es,ax
	xor	di,di
	mov	bx,di
	mov	cx,7FFFh
	cld
    get_environ:
	mov	al,0
	repnz	scasb
	or	cx,cx
	jz	bad_environ
	inc	bx
	cmp	es:[di],al
	jnz	get_environ
	or	ch,80h
	neg	cx
	mov	envlen,cx
	shl	bx,2
	add	bx,16
	and	bl,0F0h
	mov	envsize,bx
	mov	dx,ss
	sub	bp,dx
	mov	di,_stklen
	shr	di,4
	inc	di
	cmp	bp,di
	jb	bad_environ
	mov	bx,di
	add	bx,dx
	mov	heapbase,bx
	mov	brklvl,bx
	mov	ax,_psp
	sub	bx,ax
	mov	es,ax
	mov	ax,4A00h
	int	21h
	mov	ax,offset DGROUP:_dsstack
	add	ax,_stklen
	mov	dx,ds
	mov	ss,dx
	mov	sp,ax
	ASSUME	ss:DGROUP
	jmp	init_bss
    bad_environ:
	jmp	abort
    init_bss:
	xor	ax,ax
	mov	bp,ax
  ifdef __BSS__
	mov	dx,ss
	mov	es,dx
	mov	di,offset DGROUP:bdata@
	mov	cx,offset DGROUP:edata@
	sub	cx,di
	cld
	rep	stosb
  endif
	mov	dx,offset DGROUP:InitStart
	mov	ax,offset DGROUP:InitEnd
	call	Initialize
	mov	ax,C0_argc
	mov	bx,C0_argv
	mov	cx,C0_argv+2
  ifdef __WCC__
	push	cx
	push	bx
	push	ax
  else
	push	ax
	push	cx
	push	bx
  endif
;	mov	bp,offset _dsstack
	call	C0_main
	push	ax
	call	exit

Initret dw ?
Initialize:
	pop	cs:Initret
	mov	si,dx
	mov	di,ax
	xor	ax,ax
      @@:
	mov	cx,256
	mov	bx,si
	mov	dx,di
      @1:
	cmp	bx,di
	je	@3
	cmp	[bx],ax
	je	@2
	cmp	cx,[bx+2]
	jb	@2
	mov	cx,[bx+2]
	mov	dx,bx
      @2:
	add	bx,4
	jmp	@1
      @3:
	cmp	dx,di
	je	@F
	mov	bx,dx
	mov	dx,[bx]
	mov	[bx],ax
	call	dx
	xor	ax,ax
	jmp	@B
      @@:
	jmp	cs:Initret

INT24_HANDLER:
	push	ds
	push	ss
	pop	ds
	mov	sys_erflag,ah
	mov	sys_erdrive,al
	mov	ax,di
	mov	ah,0
	mov	sys_ercode,ax
	mov	word ptr sys_erdevice,si
	mov	word ptr sys_erdevice+2,bp
	mov	al,3
	cmp	word ptr sys_erproc,0
	je	INT24_00
	; PUSH ES BX CX DX
	call	sys_erproc
	; POP DX CX BX ES
INT24_00:
	pop	ds

INT23_HANDLER:
	iret

SAVE_VECTORS:
	mov	ax,3523h
	int	21h
	mov	word ptr Interrupt_23,bx
	mov	word ptr Interrupt_23+2,es
	mov	ax,3524h
	int	21h
	mov	word ptr Interrupt_24,bx
	mov	word ptr Interrupt_24+2,es
	push	ds
	push	cs
	pop	ds
	mov	ax,2523h
	mov	dx,offset INT23_HANDLER
	int	21h
	mov	ax,2524h
	mov	dx,offset INT24_HANDLER
	int	21h
	pop	ds
	ret

stderrmsg proc public
	mov	ah,40h
	mov	bx,2
	int	21h
	ret
stderrmsg endp

abort	proc DIST _CType public
	mov	cx,sizeabortmsg
	mov	dx,offset DGROUP:abortmsg
	call	stderrmsg
	push	3
	call	exit
abort	endp

terminate proc DIST _CType public errorlevel:word
	mov	ax,errorlevel
	mov	ah,4Ch
	int	21h
terminate endp

exit	proc DIST _CType public errorlevel:word
	call	_restorezero
	invoke	terminate,errorlevel
exit	endp

_restorezero proc public
	push	ss
	pop	ds
	mov	dx,offset DGROUP:ExitStart
	mov	ax,offset DGROUP:ExitEnd
	call	Initialize
	push	ds
	lds	dx,Interrupt_23
	mov	ax,2523h
	int	21h
	pop	ds
	push	ds
	lds	dx,Interrupt_24
	mov	ax,2524h
	int	21h
	pop	ds
	ret
_restorezero endp

ifdef DEBUG
__MMODEL dw	MMODEL
	public	__MMODEL
endif

_TEXT	ends

_DATA	segment
ifdef DEBUG
DATASEG@ label	byte
	public	DATASEG@
endif
NULL	label	word
cp_null		db	0,0,0,0
abortmsg	db	'Abnormal program termination', 13, 10
sizeabortmsg	= $ - abortmsg
C0_argc		dw	0
C0_argv		dw	0
		dw	0
_psp		dw	0
envlen		dw	0
envseg		dw	0
envsize		dw	0
_osversion	label	word
_osmajor	db	0
_osminor	db	0
errno		dw	0
doserrno	dw	0
ifdef LPROG
 sys_erproc	dd	0
else
 sys_erproc	dw	0
endif
sys_erdevice	dd	0
sys_ercode	dw	0
sys_erflag	db	0
sys_erdrive	db	0
Interrupt_24	dd	?
Interrupt_23	dd	?
heaptop		dw	0
heapbase	dw	0
heapfree	dw	0
brklvl		dw	0

	public	C0_argc
	public	C0_argv
	public	_psp
	public	envseg
	public	envlen
	public	envsize
	public	_osversion
	public	_osminor
	public	_osmajor
	public	errno
	public	doserrno
	public	sys_erdevice
	public	sys_ercode
	public	sys_erflag
	public	sys_erdrive
	public	sys_erproc
	public	heaptop
	public	heapbase
	public	heapfree
	public	brklvl

_DATA	ends

_EXIT	segment word public 'EXIT'
ExitStart label byte
_EXIT	ends
_EEND	segment word public 'EXIT'
ExitEnd label byte
_EEND	ends
_INIT	segment word public 'INIT'
InitStart label byte
_INIT	ends
_IEND	segment word public 'INIT'
InitEnd label byte
_IEND	ends
ifdef __BSS__
_BSS	segment word public 'BSS'
bdata@	label byte
_BSS	ends
_BSSEND segment word public 'BSSEND'
edata@	label byte
_BSSEND ends
endif

_STACK	segment
_dsstack label word
	public	_dsstack
	db	124 dup(?)
	dd	564A4A0Ah
_STACK	ends

	end	start
