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

    mov rax,rcx

    ;; validation section

    .if ( rdx == NULL || r8 == 0 || r9d < 2 || r9d > 36 )

        _set_errno(EINVAL)
        .return EINVAL
    .endif

    mov ecx,1
    add ecx,is_neg
    .if r8 <= rcx

        _set_errno(ERANGE)
        .return ERANGE
    .endif

    .if is_neg

        mov byte ptr [rdx],'-'
        inc rdx
        neg rax
    .endif

    .if rax == 0

        mov word ptr [rdx],'0'

        .return
    .endif

    mov r10,rdx
    mov ecx,lengthof(convbuf)-1
    mov convbuf[rcx],0

    .while rax && ecx

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

    ;; Check for buffer overrun

    .if eax

        mov byte ptr [rdx],0

        _set_errno(ERANGE)
        .return ERANGE
    .endif

    ret

xtox_s endp

_itoa_s::

_ltoa_s proc val:long_t, buffer:string_t, sizeInTChars:size_t, radix:int_t

    xor eax,eax
    .ifs (r9d == 10 && ecx < 0)
        inc eax
    .endif
    xtox_s(rcx, rdx, r8, r9d, eax)
    ret

_ltoa_s endp

_ultoa_s proc val:ulong_t, buffer:string_t, sizeInTChars:size_t, radix:int_t

    xtox_s(rcx, rdx, r8, r9d, 0)
    ret

_ultoa_s endp


_i64toa_s proc val:int64_t,  buffer:string_t, sizeInTChars:size_t, radix:int_t

    xor eax,eax
    .ifs (r9d == 10 && rcx < 0)
        inc eax
    .endif
    xtox_s(rcx, rdx, r8, r9d, eax)
    ret

_i64toa_s endp

_ui64toa_s proc val:int64_t, buffer:string_t, sizeInTChars:size_t, radix:int_t

    xtox_s(rcx, rdx, r8, r9d, 0)
    ret

_ui64toa_s endp

    end
