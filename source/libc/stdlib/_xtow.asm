; _XTOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

ifdef _WIN64

_xtow proc val:qword, buffer:wstring_t, radix:int_t, is_neg:int_t

   .new convbuf[256]:wchar_t

    ldr r9d,is_neg
    ldr r8d,radix
    ldr rdx,buffer
    ldr rcx,val

    mov r10,rdx
    mov rax,rcx

    .if ( r9d )

        mov wchar_t ptr [rdx],'-'
        add rdx,wchar_t
        neg rax
    .endif

    .if ( rax == 0 )

        mov dword ptr [rdx],'0'
       .return( r10 )
    .endif

    mov ecx,sizeof(convbuf)-2
    mov convbuf[rcx],0

    .fors ( r9 = rdx : rax && ecx : )

        xor edx,edx
        div r8
        add dl,'0'
        .ifs ( dl > '9' )
            add dl,('A' - '9' - 1)
        .endif
        sub ecx,2
        mov convbuf[rcx],dx
    .endf

    .repeat
        mov ax,convbuf[rcx]
        add ecx,2
        mov [r9],ax
        add r9,2
    .until ( ax == 0 )
    .return( r10 )

_xtow endp

else

_xtow proc uses esi edi ebx val:qword, buffer:wstring_t, radix:int_t, is_neg:int_t

   .new convbuf[128]:wchar_t

    mov eax,dword ptr val[0]
    mov edx,dword ptr val[4]

    mov edi,buffer

    .ifs ( is_neg )

        mov wchar_t ptr [edi],'-'
        add edi,2

        neg edx
        neg eax
        sbb edx,0
    .endif

    .if ( eax == 0 && edx == 0 )

        mov dword ptr [edi],'0'
       .return( buffer )
    .endif

    mov ecx,sizeof(convbuf)-2
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
        sub ecx,2
        mov convbuf[ecx],bx
    .endf
    pop edi

    .repeat
        mov ax,convbuf[ecx]
        add ecx,2
        mov [edi],ax
        add edi,2
    .until ( ax == 0 )
    .return( buffer )

_xtow endp

endif

    end
