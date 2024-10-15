; _RCZIP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

define W_MENUS 0x0001 ; menus color (gray), no title

    .code

_rczip proc uses rsi rdi rbx rc:TRECT, dst:ptr, src:PCHAR_INFO, flags:uint_t

   .new count:int_t
   .new tmp:int_t
   .new window:PCHAR_INFO

    ldr eax,rc
    ldr rbx,src

    shr eax,16
    mul ah
    mov count,eax
    shl eax,2
    mov rdi,malloc(eax)
    mov window,rax
    mov ecx,count
    mov rsi,rbx
    rep movsd

    mov rsi,window
    mov edx,flags
    and edx,W_RESBITS
    mov ecx,count
    lea rdi,at_foreground
    lea rbx,at_background
    mov al,[rbx+BG_MENU]
    or  al,[rdi+FG_MENU]
    .if ( al == [rsi+2] )
        or edx,W_MENUS
    .endif

    .repeat

        .if ( [rsi].CHAR_INFO.Char.UnicodeChar == 0 )

            mov [rsi].CHAR_INFO.Char.UnicodeChar,' '
        .endif

        mov al,[rsi+2]
        mov ah,al

        .if ( edx & W_RESAT )

            and ax,0x0FF0

            .if ( edx & W_MENUS )

                mov al,BG_MENU shl 4
                .if ah == [rdi+FG_MENUKEY]
                    mov ah,FG_MENUKEY
                .elseif ah != 8
                    mov ah,FG_MENU
                .endif

            .elseif al == [rbx+BG_DIALOG]

                .if ah == [rdi+FG_DIALOGKEY]
                    mov ah,FG_DIALOGKEY
                .elseif ah == [rdi+FG_DIALOG]
                    mov ah,FG_DIALOG
                .endif
                mov al,BG_DIALOG shl 4

                .if ( [rsi].CHAR_INFO.Char.UnicodeChar == 0x2580 ||
                      [rsi].CHAR_INFO.Char.UnicodeChar == 0x2584 )
                    mov ah,FG_PBSHADE
                .endif

            .elseif al == [rbx+BG_TITLE]

                mov al,BG_TITLE shl 4
                .if ah == [rdi+FG_TITLEKEY]
                    mov ah,FG_TITLEKEY
                .elseif ah != 8
                    mov ah,FG_TITLE
                .endif

            .elseif al == [rbx+BG_PBUTTON]

                mov al,BG_PBUTTON shl 4
                .if ah == [rdi+FG_TITLEKEY]
                    mov ah,FG_TITLEKEY
                .elseif ah != 8
                    mov ah,FG_TITLE
                .endif
            .endif
            or  al,ah
            mov [rsi+2],al
        .endif

        .if !( edx & W_UNICODE )

            mov     tmp,ecx
            movzx   eax,word ptr [rsi]
            lea     rdi,_unicode850
            mov     ecx,256
            repnz   scasw
            mov     eax,256
            sub     eax,ecx
            dec     eax
            mov     [rsi],ax
            lea     rdi,at_foreground
            mov     ecx,tmp
        .endif
        add rsi,4
    .untilcxz

    .if ( flags & W_UNICODE )

        mov rdi,dst
        mov rsi,window
        mov ecx,count
        compress()
        mov rsi,window
        inc rsi
        mov ecx,count
        compress()
        mov rsi,window
        add rsi,2
        mov ecx,count
        compress()
        mov rsi,window
        add rsi,3
        mov ecx,count
        compress()

    .else

        mov rdi,dst
        mov rsi,window
        add rsi,2
        mov ecx,count
        compress()
        mov rsi,window
        mov ecx,count
        compress()
    .endif
    mov rbx,rdi
    sub rbx,dst
    free(window)
    mov eax,ebx
    ret

    option dotname

compress:

    mov     al,[rsi]
    mov     dl,al
    mov     dh,al
    and     dh,0xF0
    cmp     al,[rsi+4]
    jnz     .1
    mov     ebx,0xF001
    jmp     .3
.1:
    cmp     dh,0xF0
    jnz     .7
    mov     eax,0x01F0
    jmp     .6
.2:
    inc     ebx
    add     rsi,4
    mov     al,[rsi]
    cmp     al,[rsi+4]
    jne     .4
.3:
    dec     ecx
    jnz     .2
.4:
    mov     eax,ebx
    cmp     ebx,0xF002
    jnz     .5
    cmp     dh,0xF0
    jz      .5
    mov     al,dl
    stosb
    jmp     .7
.5:
    xchg    ah,al
.6:
    stosw
    mov     al,dl
.7:
    stosb
    test    ecx,ecx
    jz      .8
    add     rsi,4
    dec     ecx
    jnz     compress
.8:
    retn

_rczip endp

    end
