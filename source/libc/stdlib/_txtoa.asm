; _TXTOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tmacro.inc

    .code

ifdef _WIN64

_txtoa proc val:qword, buffer:LPTSTR, radix:int_t, is_neg:int_t

   .new convbuf[256]:TCHAR

    ldr r8d,radix
    ldr r9d,is_neg
    ldr rcx,val
    ldr rdx,buffer

    mov r10,rdx
    mov rax,rcx

    .if ( r9d )

        mov TCHAR ptr [rdx],'-'
        add rdx,TCHAR
        neg rax
    .endif

    .if ( rax == 0 )

        mov TCHAR ptr [rdx],'0'
        mov TCHAR ptr [rdx+TCHAR],0
       .return( r10 )
    .endif

    mov ecx,sizeof(convbuf)-TCHAR
    mov convbuf[rcx],0

    .fors ( r9 = rdx : rax && ecx : )

        xor edx,edx
        div r8
        add dl,'0'
        .ifs ( dl > '9' )
            add dl,('A' - '9' - 1)
        .endif
        sub ecx,TCHAR
        mov convbuf[rcx],__d
    .endf

    .repeat
        mov __a,convbuf[rcx]
        add ecx,TCHAR
        mov [r9],__a
        add r9,TCHAR
    .until ( __a == 0 )
    .return( r10 )

_txtoa endp

else

_txtoa proc uses esi edi ebx val:qword, buffer:LPTSTR, radix:int_t, is_neg:int_t

   .new convbuf[128]:TCHAR

    mov eax,dword ptr val[0]
    mov edx,dword ptr val[4]

    mov edi,buffer

    .ifs ( is_neg )

        mov TCHAR ptr [edi],'-'
        add edi,TCHAR

        neg edx
        neg eax
        sbb edx,0
    .endif

    .if ( eax == 0 && edx == 0 )

        mov TCHAR ptr [edi],'0'
        mov TCHAR ptr [edi+TCHAR],0
       .return( buffer )
    .endif

    mov ecx,sizeof(convbuf)-TCHAR
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
        sub ecx,TCHAR
        mov convbuf[ecx],__b
    .endf
    pop edi

    .repeat
        mov __a,convbuf[ecx]
        add ecx,TCHAR
        mov [edi],__a
        add edi,TCHAR
    .until ( __a == 0 )
    .return( buffer )

_txtoa endp

endif

    end
