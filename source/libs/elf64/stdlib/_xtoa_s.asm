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

include errno.inc

    .code

xtox_s proc private val:qword, buf:string_t , sizeInTChars:size_t, radix:uint_t, is_neg:int_t

  local convbuf[256]:char_t

    mov rax,rdi

    ;; validation section

    .if ( rsi == NULL || rdx == 0 || ecx < 2 || ecx > 36 )

        _set_errno(EINVAL)
        .return EINVAL
    .endif

    mov edi,1
    add edi,is_neg
    .if rdx <= rdi

        _set_errno(ERANGE)
        .return ERANGE
    .endif

    .if is_neg

        mov byte ptr [rsi],'-'
        inc rsi
        neg rax
    .endif

    .if rax == 0

        mov word ptr [rsi],'0'

        .return
    .endif

    mov r8,rdx
    mov edi,lengthof(convbuf)-1
    mov convbuf[rdi],0

    .while rax && edi

        xor edx,edx
        div rcx
        add dl,'0'
        .ifs dl > '9'
            add dl,('A' - '9' - 1)
        .endif
        dec edi
        mov convbuf[rdi],dl
    .endw

    .for ( eax = 1 : al && r8 : r8--, edi++, rsi++ )

        mov al,convbuf[rdi]
        mov [rsi],al
    .endf

    ;; Check for buffer overrun

    .if eax

        mov byte ptr [rsi],0

        _set_errno(ERANGE)
        .return ERANGE
    .endif
    ret

xtox_s endp

_itoa_s::

_ltoa_s proc val:long_t, buffer:string_t, sizeInTChars:size_t, radix:int_t

    xor eax,eax
    .ifs ( ecx == 10 && edi < 0 )
        inc eax
    .endif
    xtox_s(rdi, rsi, rdx, ecx, eax)
    ret

_ltoa_s endp

_ultoa_s proc val:ulong_t, buffer:string_t, sizeInTChars:size_t, radix:int_t

    xtox_s(rdi, rsi, rdx, ecx, 0)
    ret

_ultoa_s endp


_i64toa_s proc val:int64_t,  buffer:string_t, sizeInTChars:size_t, radix:int_t

    xor eax,eax
    .ifs ( ecx == 10 && rdi < 0 )
        inc eax
    .endif
    xtox_s(rdi, rsi, rdx, ecx, eax)
    ret

_i64toa_s endp

_ui64toa_s proc val:int64_t, buffer:string_t, sizeInTChars:size_t, radix:int_t

    xtox_s(rdi, rsi, rdx, ecx, 0)
    ret

_ui64toa_s endp

    end
