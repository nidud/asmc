; _XTOW_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include errno.inc

    .code

_xtow_s proc val:qword, buf:wstring_t , sizeInTChars:size_t, radix:uint_t, is_neg:int_t

  local convbuf[256]:wchar_t

ifdef _WIN64
    mov rax,rcx

    ; validation section

    .if ( rdx == NULL || r8 == 0 || r9d < 2 || r9d > 36 )
else

    mov eax,dword ptr val[0]
    mov edx,dword ptr val[4]

    .if ( buf == NULL || sizeInTChars == 0 || radix < 2 || radix > 36 )
endif

        _set_errno(EINVAL)
        .return EINVAL
    .endif

    mov ecx,1
    add ecx,is_neg

ifdef _WIN64
    .if ( r8 <= rcx )
else
    .if ( sizeInTChars <= ecx )
endif

        _set_errno(ERANGE)
        .return ERANGE
    .endif

ifdef _WIN64
    .if ( is_neg )

        mov wchar_t ptr [rdx],'-'
        add rdx,wchar_t
        neg rax
    .endif

    .if ( rax == 0 )

        mov dword ptr [rdx],'0'
else

    mov ecx,buf
    .if ( is_neg )

        mov wchar_t ptr [ecx],'-'
        add ecx,wchar_t
        neg edx
        neg eax
        sbb edx,0
    .endif

    .if ( eax == 0 && edx == 0 )

        mov dword ptr [ecx],'0'
endif
       .return
    .endif

ifdef _WIN64

    mov r10,rdx
    mov ecx,sizeof(convbuf)-2
    mov convbuf[rcx],0

    .while ( rax && ecx )

        xor edx,edx
        div r9
        add dl,'0'
        .ifs dl > '9'
            add dl,('A' - '9' - 1)
        .endif
        sub ecx,wchar_t
        mov convbuf[rcx],dx
    .endw

    .for ( rdx = r10, eax = 1 : ax && r8 : r8--, ecx+=2, rdx+=2 )

        mov ax,convbuf[rcx]
        mov [rdx],ax
    .endf

else

    push ecx

    mov ecx,sizeof(convbuf)-2
    mov convbuf[ecx],0

    push esi
    push edi
    push ebx

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
        sub ecx,wchar_t
        mov convbuf[ecx],bx
    .endf

    pop ebx
    pop edi
    pop esi
    pop edx

    .repeat
        mov ax,convbuf[ecx]
        add ecx,wchar_t
        mov [edx],ax
        add edx,wchar_t
        dec sizeInTChars
    .until ( ax == 0 || sizeInTChars == 0 )

endif

    ; Check for buffer overrun

    .if ( eax )

        mov wchar_t ptr [rdx],0

        _set_errno(ERANGE)
        .return ERANGE
    .endif
    ret

_xtow_s endp

    end
