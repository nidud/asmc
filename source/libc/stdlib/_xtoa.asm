; _XTOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

ifdef _WIN64

_xtoa proc val:qword, buffer:string_t, radix:int_t, is_neg:int_t

   .new convbuf[256]:char_t

    mov r10,rdx
    mov rax,rcx

    .if ( r9d )

        mov byte ptr [rdx],'-'
        inc rdx
        neg rax
    .endif

    .if ( rax == 0 )

        mov word ptr [rdx],'0'
       .return( r10 )
    .endif

    mov ecx,lengthof(convbuf)-1
    mov convbuf[rcx],0

    .fors ( r9 = rdx : rax && ecx : )

        xor edx,edx
        div r8
        add dl,'0'
        .ifs ( dl > '9' )
            add dl,('A' - '9' - 1)
        .endif
        dec ecx
        mov convbuf[rcx],dl
    .endf

    .repeat
        mov al,convbuf[rcx]
        inc ecx
        mov [r9],al
        inc r9
    .until ( al == 0 )
    .return( r10 )

_xtoa endp

else

_xtoa proc uses esi edi ebx val:qword, buffer:string_t, radix:int_t, is_neg:int_t

   .new convbuf[128]:char_t

    mov eax,dword ptr val[0]
    mov edx,dword ptr val[4]

    mov edi,buffer

    .ifs ( is_neg )

        mov byte ptr [edi],'-'
        inc edi

        neg edx
        neg eax
        sbb edx,0
    .endif

    .if ( eax == 0 && edx == 0 )

        mov word ptr [edi],'0'
       .return( buffer )
    .endif

    mov ecx,lengthof(convbuf)-1
    mov convbuf[ecx],0

    push edi

    .fors ( : ( eax || edx ) && ecx : )

        .if ( !edx || !radix )

            div radix
            mov ebx,edx
            xor edx,edx

        .else

            .for ( ebx = 64, esi = 0, edi = 0 : ebx : ebx-- )

                add eax,eax
                adc edx,edx
                adc esi,esi
                adc edi,edi

                .if ( edi || esi >= radix )

                    sub esi,radix
                    sbb edi,0
                    inc eax
                .endif
            .endf
            mov ebx,esi
        .endif

        add ebx,'0'
        .ifs ( ebx > '9' )
            add bl,('A' - '9' - 1)
        .endif
        dec ecx
        mov convbuf[ecx],bl
    .endf
    pop edi

    .repeat
        mov al,convbuf[ecx]
        inc ecx
        mov [edi],al
        inc edi
    .until ( al == 0 )
    .return( buffer )

_xtoa endp

endif

    end
