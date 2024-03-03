; _TXTOA_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include errno.inc
include tchar.inc

    .code

_txtoa_s proc val:qword, buf:LPTSTR , sizeInTChars:size_t, radix:uint_t, is_neg:int_t

  local convbuf[256]:TCHAR

ifdef _WIN64

    ldr r9d,radix
    ldr r8,sizeInTChars
    ldr rdx,buf
    ldr rcx,val

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

        mov TCHAR ptr [rdx],'-'
        add rdx,TCHAR
        neg rax
    .endif

    .if ( rax == 0 )

        mov TCHAR ptr [rdx],'0'
        mov TCHAR ptr [rdx+TCHAR],0
else

    mov ecx,buf
    .if ( is_neg )

        mov TCHAR ptr [ecx],'-'
        add ecx,TCHAR
        neg edx
        neg eax
        sbb edx,0
    .endif

    .if ( eax == 0 && edx == 0 )

        mov TCHAR ptr [ecx],'0'
        mov TCHAR ptr [ecx+TCHAR],0
endif
       .return
    .endif

ifdef _WIN64

    mov r10,rdx
    mov ecx,sizeof(convbuf)-TCHAR
    mov convbuf[rcx],0

    .while ( rax && ecx )

        xor edx,edx
        div r9
        add dl,'0'
        .ifs dl > '9'
            add dl,('A' - '9' - 1)
        .endif
        sub ecx,TCHAR
        mov convbuf[rcx],_tdl
    .endw

    .for ( rdx = r10, eax = 1 : eax && r8 : r8--, ecx+=TCHAR, rdx+=TCHAR )

        mov [rdx],convbuf[rcx]
    .endf

else

    push ecx

    mov ecx,sizeof(convbuf)-TCHAR
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
        sub ecx,TCHAR
        mov convbuf[ecx],_tbl
    .endf

    pop ebx
    pop edi
    pop esi
    pop edx

    .repeat
        mov _tal,convbuf[ecx]
        add ecx,TCHAR
        mov [edx],_tal
        add edx,TCHAR
        dec sizeInTChars
    .until ( _tal == 0 || sizeInTChars == 0 )

endif

    ; Check for buffer overrun

    .if ( eax )

        mov TCHAR ptr [rdx],0

        _set_errno(ERANGE)
        .return ERANGE
    .endif
    ret

_txtoa_s endp

    end
