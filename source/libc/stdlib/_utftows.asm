; _UTFTOWS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert UTF8 to Wide char string
;
; Return:
;  - RAX buffer to converted string
;  - ECX size (in bytes) of converted string
;
include stdlib.inc

    .data?
          wchar_t 0x0004 dup(?) ; \\?\
     wbuf wchar_t 0x2000 dup(?)

    .code

    option dotname

_utftows proc uses rdi rbx path:string_t

    ldr     rcx,path
    lea     rdx,_lookuptrailbytes
    lea     rdi,wbuf
.0:
    movzx   eax,byte ptr [rcx]
    test    eax,eax
    jz      .4
    cmp     ah,[rdx+rax]
    jne     .2
    and     eax,0x7F
    inc     rcx
.1:
    stosw
    jmp     .0
.2:
    cmp     byte ptr [rdx+rax],1
    ja      .3
    and     eax,0x1F
    shl     eax,6
    movzx   ebx,byte ptr [rcx+1]
    and     ebx,0x3F
    or      eax,ebx
    add     rcx,2
    jmp     .1
.3:
    and     eax,0x0F
    shl     eax,12
    movzx   ebx,byte ptr [rcx+1]
    and     ebx,0x3F
    shl     ebx,6
    or      eax,ebx
    movzx   ebx,byte ptr [rcx+2]
    and     ebx,0x3F
    or      eax,ebx
    add     rcx,3
    jmp     .1
.4:
    stosw
    lea     rax,wbuf
    mov     rcx,rax
    sub     rcx,rdi
    ret

_utftows endp

    end
