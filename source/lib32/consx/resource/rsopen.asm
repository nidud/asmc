; RSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include malloc.inc

rsunzipch proto
rsunzipat proto

    .code

rsopen proc uses esi edi ebx ecx edx idd:ptr S_ROBJ
  local result

    mov esi,idd
    xor eax,eax

    mov al,[esi].S_ROBJ.rs_rect.rc_x
    add al,[esi].S_ROBJ.rs_rect.rc_col
    .if al >= byte ptr _scrcol
        sub al,byte ptr _scrcol
        sub [esi].S_ROBJ.rs_rect.rc_x,al
    .endif

    mov al,[esi].S_ROBJ.rs_rect.rc_y
    add al,[esi].S_ROBJ.rs_rect.rc_row
    mov ah,byte ptr _scrrow
    inc ah
    .if al >= ah
        sub al,ah
        sub [esi].S_ROBJ.rs_rect.rc_y,al
    .endif

    mov ax,[esi+8]  ; rc_rows * rc_cols
    mov edx,eax
    mul ah
    mov idd,eax
    add eax,eax     ; WORD size
    mov edi,eax

    .if word ptr [esi+2] & _D_SHADE
        add dl,dh
        add dl,dh
        mov dh,0
        sub edx,2
        add edi,edx
    .endif

    .repeat

        movzx   eax,word ptr [esi]
        mov     result,malloc(eax)
        mov     ebx,edi
        mov     edi,eax
        mov     edx,eax
        movzx   ecx,word ptr [esi]
        .break .if !eax

        sub     eax,eax
        shr     ecx,1
        rep     stosw
        mov     ecx,edx
        mov     edi,edx
        lodsw           ; skip size
        ; -- copy dialog
        lodsw           ; .flag
        or      eax,_D_SETRC
        push    eax
        stosw           ; .flag
        movsw           ; .count + .index
        movsd           ; .rect
        movzx   eax,byte ptr [esi-6]
        inc     eax
        shl     eax,4       ; * size of objects (16)
        add     eax,ecx     ; + adress
        stosd           ; = .wp (32)
        xchg    edx,eax
        add     eax,16      ; dialog + 16
        stosd           ; = .object
        ; -- copy objects
        add     edx,ebx     ; end of wp = start of object alloc
        movzx   ebx,byte ptr [esi-6]

        .while ebx

            movsd           ; copy 8 byte
            movsd           ; get alloc size of object
            movzx   eax,byte ptr [esi-6]
            shl     eax,4   ; * 16

            .if eax
                xchg eax,edx ; offset of mem (.data)
                stosd
                add edx,eax
                xor eax,eax
            .else
                stosd
            .endif
            stosd
            dec ebx
        .endw

        pop  eax
        push edi
        inc  edi
        mov  ecx,idd

        .if eax & _D_RESAT

            rsunzipat()
        .else
            rsunzipch()
        .endif
        pop edi
        mov ecx,idd
        rsunzipch()

        mov  eax,result
        test eax,eax
    .until 1
    ret

rsopen endp

    END
