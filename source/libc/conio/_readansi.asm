; _READANSI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdlib.inc

    .code

    assume rbx:PCINPUT

_readansi proc uses rbx csi:PCINPUT

   .new value:int_t
   .new count:int_t
   .new radix:int_t
   .new final[2]:byte

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
    .if ( al != '[' && al != ']' )

        mov [rbx].param,al
        _getch()
        mov [rbx].final,al
       .return( 3 )
    .endif

    mov count,2
    mov ecx,0x5C5C
    .if ( al == '[' )
        mov ecx,0x7E40
    .endif
    mov final[0],cl
    mov final[1],ch
    mov radix,10

    .while 1

        _getch()
        inc count
        mov cl,final[0]
        mov ch,final[1]

        .switch
        .case al >= cl && al <= ch
            mov [rbx].final,al
        .case eax == -1
           .break
        .case al == '/'
            .if ( cl != '\' )
                mov [rbx].inter,al
               .endc
            .endif
        .case al == ';'
            inc     [rbx].count
            movzx   ecx,[rbx].count
            mov     [rbx+rcx*4].n,0
            mov     value,1
           .endc
        .case al >= 0x20 && al <= 0x2F
            mov     [rbx].inter,al
           .endc
        .case al >= 'a' && al <= 'f'
            .endc .if ( radix == 10 )
            sub     al,'a'-10-'0'
        .case al >= '0' && al <= '9'
            sub     al,'0'
            movzx   ecx,[rbx].count
            mov     edx,[rbx].n[rcx*4]
            imul    edx,radix
            add     eax,edx
            mov     [rbx].n[rcx*4],eax
            mov     value,1
           .endc
        .case al == 0x1B
            .if ( cl != '\' )
                _ungetch( eax )
                dec count
               .break
            .endif
            .endc
        .case al == ':' ; \e]d;d;rgb:xxxx/xxxx/xxxx\e\\
            .if ( cl == '\' )
                mov radix,16
               .endc
            .endif
        .default
            mov [rbx].param,al
        .endsw
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
    mov eax,count
    ret

_readansi endp

    end
