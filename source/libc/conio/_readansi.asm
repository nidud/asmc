; _READANSI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdlib.inc

    .code

    assume rbx:ptr AnsiEscapeCode

_readansi proc uses rbx csi:ptr AnsiEscapeCode

   .new value:int_t
   .new count:int_t

    ldr rbx,csi

    xor eax,eax
    mov value,eax
    mov count,eax
    mov [rbx].final,al
    mov [rbx].count,al
    mov [rbx].param,al
    mov [rbx].inter,al
    mov [rbx].n,eax

    .ifd ( _getch() == -1 )

        .return( 0 )
    .endif

    .if ( eax != VK_ESCAPE )

        lea rcx,_lookuptrailbytes
        mov cl,byte ptr [rcx+rax]

        .if ( cl == 0 )

            and eax,0x7F

        .elseif ( cl == 1 )

            and eax,0x1F
            shl eax,6
            mov value,eax

            .ifd ( _getch() == -1 )

                .return( 0 )
            .endif
            and eax,0x3F
            or  eax,value
            mov [rbx].count,ah

        .elseif ( cl == 2 )

            and eax,0x0F
            shl eax,12
            mov value,eax

            .ifd ( _getch() == -1 )

                .return( 0 )
            .endif
            and eax,0x3F
            shl eax,6
            or  value,eax

            .ifd ( _getch() == -1 )

                .return( 0 )
            .endif
            and eax,0x3F
            or  eax,value
            mov [rbx].count,ah
        .endif
        mov [rbx].final,al

       .return( 1 )
    .endif

    .ifd ( _kbhit() == 0 )

        mov [rbx].final,VK_ESCAPE
       .return( 1 )
    .endif

    _getch()
    mov count,2

    .if ( al == '[' )

        .while 1

            _getch()
            inc count

            .if ( al >= 0x40 && al <= 0x7E )

                mov [rbx].final,al
               .break
            .endif

            .if ( al >= 0x30 && al <= 0x3F )

                .if ( al <= '9' )

                    sub     al,'0'
                    movzx   ecx,[rbx].count
                    imul    edx,[rbx].n[rcx*4],10
                    add     eax,edx
                    mov     [rbx].n[rcx*4],eax
                    mov     value,1

                .elseif ( al == ';' )

                    inc [rbx].count
                    movzx ecx,[rbx].count
                    mov [rbx+rcx*4].n,0
                    mov value,1
                .else
                    mov [rbx].param,al
                .endif

            .elseif ( al >= 0x20 || al <= 0x2F )
                mov [rbx].inter,al
            .else
                .break
            .endif
        .endw
        mov ecx,value
        add [rbx].count,cl

        .if ( [rbx].final == 'M' )

            _getch()
            mov [rbx].param,al
            _getch()
            sub eax,0x21
            mov [rbx].n[0],eax
            _getch()
            sub eax,0x21
            mov [rbx].n[4],eax
            add count,3
        .endif

    .else

        mov [rbx].param,al
        _getch()
        inc count
        mov [rbx].final,al
    .endif

    mov eax,count
    ret

_readansi endp

    end
