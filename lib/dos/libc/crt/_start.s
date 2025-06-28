; _START.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Startup module for DOS
;

include dos.inc
include stdlib.inc

main proto __cdecl :int_t, :ptr, :ptr

externdef __xi_a:ptr ; pointers to initialization sections
externdef __xi_z:ptr
externdef _argvcrt:ptr
externdef _environcrt:ptr

.dosseg
.data
 _null      dd 0
 _psp       dw 0
 _envlen    dw 0
 _envseg    dw 0
 _envsize   dw 0
 _heaptop   dw 0
 _heapbase  dw 0
 _heapfree  dw 0
 _brklvl    dw 0
.const
.data?
.stack 128
.code

ifdef __TINY__
    org     0x100
endif

_start::

    mov     bp,ds:[0x02]
    mov     bx,ds:[0x2C]
    mov     ax,DGROUP
    mov     ds,ax
    ASSUME  ds:DGROUP
    mov     _psp,es
    mov     _envseg,bx
    mov     _heaptop,bp

    mov     es,bx
    xor     di,di
    mov     bx,di
    mov     cx,0x7FFF
    cld
.0:
    mov     al,0
    repnz   scasb
    or      cx,cx
    jz      .1
    inc     bx
    cmp     es:[di],al
    jnz     .0
    or      ch,80h
    neg     cx
    mov     _envlen,cx

    shl     bx,2
    add     bx,0x10
    and     bl,0xF0
    mov     _envsize,bx

    mov     dx,ss
    sub     bp,dx
    mov     di,_stklen
    shr     di,4
    inc     di
    cmp     bp,di
    jb      .1
    mov     bx,di
    add     bx,dx
    mov     _heapbase,bx
    mov     _brklvl,bx
    mov     ax,_psp
    sub     bx,ax
    mov     es,ax
    mov     ax,0x4A00
    int     0x21
if (@DataSize eq 0)
    mov     ax,ds
    mov     dx,ss
    sub     dx,ax
    add     di,dx
    mov     ss,ax
endif
    dec     di
    shl     di,4
    mov     sp,di

    invoke  _initterm, addr __xi_a, addr __xi_z
    invoke  main, __argc, _argvcrt, _environcrt
    invoke  exit, ax
.1:
    invoke  abort

    end _start
