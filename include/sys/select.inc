; SELECT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef __SELECT_INC
define __SELECT_INC

include time.inc
include signal.inc

define NFDBITS 1024

.template fd_set
    bits db NFDBITS / 8 dup(?)
   .ends

FD_ZERO proto fastcall s:ptr fd_set {
    xor     eax,eax
    mov     rdx,rdi
    mov     rdi,rcx
    mov     ecx,fd_set/4
    rep     stosd
    mov     rdi,rdx
    }

FD_SET proto fastcall d:int_t, s:ptr fd_set {
    mov     eax,ecx
    shr     eax,3
    add     rdx,rax
    and     ecx,3
    mov     eax,1
    shl     eax,cl
    or      [rdx],al
    }

FD_CLR proto fastcall d:int_t, s:ptr fd_set {
    mov     eax,ecx
    shr     eax,3
    add     rdx,rax
    and     ecx,3
    mov     eax,1
    shl     eax,cl
    not     eax
    and     [rdx],al
    }

FD_ISSET proto fastcall d:int_t, s:ptr fd_set {
    mov     eax,ecx
    shr     eax,3
    add     rdx,rax
    and     ecx,3
    mov     eax,1
    shl     eax,cl
    test    al,[rdx]
    setnz   al
    }

select  proto __cdecl :int_t, :ptr fd_set, :ptr fd_set, :ptr fd_set, :ptr timeval
pselect proto __cdecl :int_t, :ptr fd_set, :ptr fd_set, :ptr fd_set, :ptr timespec, :ptr sigset_t

endif
