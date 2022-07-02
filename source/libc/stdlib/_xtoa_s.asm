; _XTOA_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; errno_t __cdecl _itoa_s ( int val, char *buf, size_t sizeInTChars, int radix );
; errno_t __cdecl _ltoa_s ( long val, char *buf, size_t sizeInTChars, int radix );
; errno_t __cdecl _ultoa_s ( unsigned long val, char *buf, size_t sizeInTChars, int radix );
; errno_t __cdecl _i64toa_s ( __int64 val, char *buf, size_t sizeInTChars, int radix );
; errno_t __cdecl _ui64toa_s ( unsigned __int64 val, char *buf, size_t sizeInTChars, int radix );
;

include stdlib.inc
include errno.inc

    .code

_xtoa_s proc val:qword, buf:string_t , sizeInTChars:size_t, radix:uint_t, is_neg:int_t

  local convbuf[256]:char_t

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

        mov byte ptr [rdx],'-'
        inc rdx
        neg rax
    .endif

    .if ( rax == 0 )

        mov word ptr [rdx],'0'
else

    mov ecx,buf
    .if ( is_neg )

        mov byte ptr [ecx],'-'
        inc ecx
        neg edx
        neg eax
        sbb edx,0
    .endif

    .if ( eax == 0 && edx == 0 )

        mov word ptr [ecx],'0'
endif
       .return
    .endif

ifdef _WIN64

    mov r10,rdx
    mov ecx,lengthof(convbuf)-1
    mov convbuf[rcx],0

    .while ( rax && ecx )

        xor edx,edx
        div r9
        add dl,'0'
        .ifs dl > '9'
            add dl,('A' - '9' - 1)
        .endif
        dec ecx
        mov convbuf[rcx],dl
    .endw

    .for ( rdx = r10, eax = 1 : al && r8 : r8--, ecx++, rdx++ )

        mov al,convbuf[rcx]
        mov [rdx],al
    .endf

else

    push ecx

    mov ecx,lengthof(convbuf)-1
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
        dec ecx
        mov convbuf[ecx],bl
    .endf

    pop ebx
    pop edi
    pop esi
    pop edx

    .repeat
        mov al,convbuf[ecx]
        inc ecx
        mov [edx],al
        inc edx
        dec sizeInTChars
    .until ( al == 0 || sizeInTChars == 0 )

endif

    ; Check for buffer overrun

    .if ( eax )

        mov byte ptr [rdx],0

        _set_errno(ERANGE)
        .return ERANGE
    .endif
    ret

_xtoa_s endp

    end
