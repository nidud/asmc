.xlist

__LIBC_INC	equ 1

ifndef __c__
   ifndef __l__
       __l__	equ 1
   endif
endif

ifdef	__l__
	_CDecl	equ <far c>
	_CType	equ <far pascal>
	_CFast	equ <far fastcall>
else
	_CDecl	equ <c>
	_CType	equ <pascal>
	_CFast	equ <fastcall>
endif

ifdef	__c__
	p?	equ <dw>	; Proc Pointer
	size_p	equ <WORD>	; - as Parameter
else
	p?	equ <dd>
	size_p	equ <DWORD>
endif

size_l	equ <2>
size_t	equ <WORD>
;__3__	equ 1			; remove this to create the .186 version

	.model compact
ifdef __3__
	.386
else
	.186
	__16__	equ 1
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

cld?	equ <>
ifdef __l__
	movl	equ <mov>
	pushl	equ <push>
	popl	equ <pop>
	retx	equ <retf>
else
	movl	macro v:VARARG
	endm
	pushl	macro v:VARARG
	endm
	popl	macro v:VARARG
	endm
	retx	equ <ret>
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

lodm	macro m,s,o
	ifnb <o>
	    mov o,WORD PTR m
	    mov s,WORD PTR m+2
	else
	    mov ax,WORD PTR m
	    mov dx,WORD PTR m+2
	endif
	endm

stom	macro m,s,o
	ifnb <o>
	    mov WORD PTR m,o
	    mov WORD PTR m+2,s
	else
	    mov WORD PTR m,ax
	    mov WORD PTR m+2,dx
	endif
	endm

pushm	macro v:VARARG
ifdef __16__
	push WORD PTR v+2
	push WORD PTR v
else
	push DWORD PTR v
endif
	endm

movmx	macro m1,m2
ifdef __16__
	mov ax,WORD PTR m2+2
	mov WORD PTR m1+2,ax
	mov ax,WORD PTR m2
	mov WORD PTR m1,ax
else
	mov eax,DWORD PTR m2
	mov DWORD PTR m1,eax
endif
	endm

movp	macro fp,lp
ifdef __l__
	mov WORD PTR fp+2,cs
endif
	mov WORD PTR fp,offset lp
	endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ifdef	__DZ__
	__ROT__		equ 1
	__ZIP__		equ 1	; ZIP
	__TE__		equ 1	; Text Edit
	__MEMVIEW__	equ 1
endif
ifndef	__X__
	__CLIP__	equ 1
	__MOUSE__	equ 1
	__LFN__		equ 1
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

pragma_init macro pp, priority
_INIT	segment WORD PUBLIC 'INIT'
	dw pp
	dw priority
_INIT	ENDS
	endm

pragma_exit macro pp, priority
_EXIT	segment WORD PUBLIC 'EXIT'
	dw pp
	dw priority
_EXIT	ENDS
	endm

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; Debug macros
;
ifdef	DEBUG
 assert_exit PROTO _CType
 DADD	equ <add>
 DSUB	equ <sub>
 DMOV	equ <mov>
 DPUSH	equ <push>
 DPOP	equ <pop>
else
 DADD	macro	v:VARARG
	endm
 DSUB	macro	v:VARARG
	endm
 DMOV	macro	v:VARARG
	endm
 DPUSH	macro	v:VARARG
	endm
 DPOP	macro	v:VARARG
	endm
endif

assert	macro A,B,J,message
	local @@
  ifdef DEBUG
	pushf
	cmp &A,&B
	&J @@
	popf
	call assert_exit
%	db "cmp &A&,&B& (&J&)  -: ",message,0
	@@:
	popf
  endif
	endm

assertf macro J,message
	local @@
  ifdef DEBUG
	&J @@
	call assert_exit
	db "flag (&J&) - ",message,0
	@@:
  endif
	endm

.list
