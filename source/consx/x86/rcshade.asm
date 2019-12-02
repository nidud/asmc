; RCSHADE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include malloc.inc

_FG_DEACTIVE equ 8

S_SHADE STRUC
dlwp_B  dd ?
sbuf_B  dd ?
sbuf_R  dd ?
rect_B  S_RECT <?>
rect_R  S_RECT <?>
S_SHADE ENDS

    .code

    option cstack:on
    assume edi:ptr S_SHADE

RCInitShade:

    push    ebp
    mov     ebp,esp

    mov     [edi].rect_B,eax
    mov     [edi].rect_R,eax
    shr     eax,16
    push    eax
    mov     [edi].rect_R.rc_col,2
    dec     [edi].rect_R.rc_row
    inc     [edi].rect_R.rc_y
    add     [edi].rect_R.rc_x,al
    add     [edi].rect_B.rc_y,ah
    mov     [edi].rect_B.rc_row,1
    add     [edi].rect_B.rc_x,2
    mul     ah
    add     eax,eax
    add     eax,ecx
    mov     [edi].dlwp_B,eax
    pop     eax
    movzx   esi,al  ; rc.rc_col
    movzx   eax,ah  ; rc.rc_row
    shl     eax,2
    add     esi,esi
    add     eax,esi
    mov     [edi].sbuf_B,alloca(eax)
    add     eax,esi
    mov     [edi].sbuf_R,eax

    .repeat

        .break .if !rcread([edi].rect_R, [edi].sbuf_R)
        .break .if !rcread([edi].rect_B, [edi].sbuf_B)

        mov     edx,[edi].dlwp_B
        mov     esi,[edi].sbuf_B
        inc     esi
        movzx   ecx,[edi].rect_R.rc_row
        add     ecx,ecx
        add     cl,[edi].rect_B.rc_col

        .if ebx
            .repeat
                mov al,[esi]
                mov [edx],al
                mov al,_FG_DEACTIVE
                mov [esi],al
                add esi,2
                inc edx
            .untilcxz
        .else
            .repeat
                mov al,[edx]
                mov [esi],al
                add esi,2
                inc edx
            .untilcxz
        .endif

        rcwrite([edi].rect_R, [edi].sbuf_R)
        rcwrite([edi].rect_B, [edi].sbuf_B)
    .until 1
    mov esp,ebp
    pop ebp
    ret

rcsetshade proc uses esi edi ebx ecx edx rc, wp:PVOID
  local sh:S_SHADE
    lea edi,sh
    mov eax,rc
    mov ecx,wp
    mov ebx,1
    RCInitShade()
    ret
rcsetshade endp

rcclrshade proc uses esi edi ebx rc, wp:PVOID
  local sh:S_SHADE
    lea edi,sh
    mov eax,rc
    mov ecx,wp
    xor ebx,ebx
    RCInitShade()
    ret
rcclrshade endp

    END
