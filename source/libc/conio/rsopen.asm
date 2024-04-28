; RSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

    assume rbx:PIDD
    assume rdi:PDOBJ

rsopen proc uses rsi rdi rbx idd:PIDD

   .new dlg:PDOBJ
   .new flags:int_t
   .new size:int_t
   .new count:int_t
   .new rsize:int_t
   .new dsize:int_t
   .new rc:TRECT

    ldr rbx,idd

    mov     rc,[rbx].rc
    movzx   eax,[rbx].flags
    mov     flags,eax
    or      eax,W_UNICODE
    mov     rsize,_rcmemsize([rbx].rc, eax)
    movzx   eax,[rbx].count
    mov     count,eax
    inc     eax
    imul    eax,eax,TOBJ
    mov     dsize,eax

    .for ( ecx = 0, eax = 0, rsi = &[rbx+RIDD] : ecx < count : ecx++, rsi+=ROBJ )

        movzx edx,[rsi].ROBJ.count
        add eax,edx
    .endf
    shl eax,4
    add eax,rsize
    add eax,dsize
    mov size,eax

    .if ( malloc(eax) == NULL )

        .return
    .endif

    mov dlg,rax
    mov rdi,rax
    mov ecx,size
    xor eax,eax
    rep stosb

    mov rdi,dlg
    mov eax,dword ptr [rbx]
    or  eax,W_RCNEW or W_MYBUF or W_ISOPEN
    mov [rdi],eax
    mov [rdi].rc,[rbx].rc
    mov eax,dsize
    add rax,rdi
    mov [rdi].window,rax
    mov edx,rsize
    add edx,dsize
    add rdx,rdi

    add rbx,RIDD
    add rdi,DOBJ

    .if ( count )

        mov [rdi-DOBJ].object,rdi

        assume rbx:PROBJ
        assume rdi:PTOBJ

        .for ( ecx = 0 : ecx < count : ecx++, rbx+=ROBJ, rdi+=TOBJ )

            mov [rdi],size_t ptr [rbx]
ifndef _WIN64
            mov [rdi].rc,[rbx].rc
endif
            movzx eax,[rdi].count
            .if ( eax )

                mov [rdi].data,rdx
                shl eax,4
                add rdx,rax
            .endif
        .endf
    .endif
    _rcunzip(rc, rdi, rbx, flags)
    mov rax,dlg
    ret

rsopen endp

    end
