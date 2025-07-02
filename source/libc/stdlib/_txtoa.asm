; _TXTOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

ifdef _WIN64

_txtoa proc val:qword, buffer:tstring_t, radix:int_t, is_neg:int_t

   .new convbuf[256]:tchar_t

    ldr r8d,radix
    ldr r9d,is_neg
    ldr rcx,val
    ldr rdx,buffer

    mov r10,rdx
    mov rax,rcx

    .if ( r9d )

        mov tchar_t ptr [rdx],'-'
        add rdx,tchar_t
        neg rax
    .endif

    .if ( rax == 0 )

        mov tchar_t ptr [rdx],'0'
        mov tchar_t ptr [rdx+tchar_t],0
       .return( r10 )
    .endif

    mov ecx,sizeof(convbuf)-tchar_t
    mov convbuf[rcx],0

    .fors ( r9 = rdx : rax && ecx : )

        xor edx,edx
        div r8
        add dl,'0'
        .ifs ( dl > '9' )
            add dl,('A' - '9' - 1)
        .endif
        sub ecx,tchar_t
        mov convbuf[rcx],_tdl
    .endf

    .repeat
        mov _tal,convbuf[rcx]
        add ecx,tchar_t
        mov [r9],_tal
        add r9,tchar_t
    .until ( _tal == 0 )
    .return( r10 )

_txtoa endp

else

_txtoa proc uses esi edi ebx val:qword, buffer:tstring_t, radix:int_t, is_neg:int_t

   .new convbuf[128]:tchar_t

    mov eax,dword ptr val[0]
    mov edx,dword ptr val[4]

    mov edi,buffer

    .ifs ( is_neg )

        mov tchar_t ptr [edi],'-'
        add edi,tchar_t

        neg edx
        neg eax
        sbb edx,0
    .endif

    .if ( eax == 0 && edx == 0 )

        mov tchar_t ptr [edi],'0'
        mov tchar_t ptr [edi+tchar_t],0
       .return( buffer )
    .endif

    mov ecx,sizeof(convbuf)-tchar_t
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
        sub ecx,tchar_t
        mov convbuf[ecx],_tbl
    .endf
    pop edi

    .repeat
        mov _tal,convbuf[ecx]
        add ecx,tchar_t
        mov [edi],_tal
        add edi,tchar_t
    .until ( _tal == 0 )
    .return( buffer )

_txtoa endp

endif

    end
