; _XTOW_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; errno_t __cdecl _itow_s ( int val, wchar_t *buf, size_t sizeInTChars, int radix );
; errno_t __cdecl _ltow_s ( long val, wchar_t *buf, size_t sizeInTChars, int radix );
; errno_t __cdecl _ultow_s ( unsigned long val, wchar_t *buf, size_t sizeInTChars, int radix );
; errno_t __cdecl _i64tow_s ( __int64 val, wchar_t *buf, size_t sizeInTChars, int radix );
; errno_t __cdecl _ui64tow_s ( unsigned __int64 val, wchar_t *buf, size_t sizeInTChars, int radix );
;

include errno.inc

    .code

xtox_s proc private val:qword, buf:wstring_t , sizeInTChars:size_t, radix:uint_t, is_neg:int_t

  local convbuf[256]:wchar_t

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

        mov wchar_t ptr [rdx],'-'
        add rdx,wchar_t
        neg rax
    .endif

    .if rax == 0

        mov wchar_t ptr [rdx],'0'
        mov [rdx+wchar_t],ax

        .return
    .endif

    mov r10,rdx
    mov ecx,sizeof(convbuf) - wchar_t
    mov convbuf[rcx],0

    .while rax && ecx

        xor edx,edx
        div r9
        add dl,'0'
        .ifs dl > '9'
            add dl,('A' - '9' - 1)
        .endif
        sub ecx,wchar_t
        mov convbuf[rcx],dx
    .endw

    .for ( rdx = r10, eax = 1 : ax && r8 : r8--, ecx += wchar_t, rdx += wchar_t )

        mov ax,convbuf[rcx]
        mov [rdx],ax
    .endf

    ;; Check for buffer overrun

    .if eax

        mov wchar_t ptr [rdx],0

        _set_errno(ERANGE)
        .return ERANGE
    .endif

    ret

xtox_s endp

_itow_s::

_ltow_s proc val:long_t, buffer:wstring_t, sizeInTChars:size_t, radix:int_t

    xor eax,eax
    .ifs (r9d == 10 && ecx < 0)
        inc eax
    .endif
    xtox_s(rcx, rdx, r8, r9d, eax)
    ret

_ltow_s endp

_ultow_s proc val:ulong_t, buffer:wstring_t, sizeInTChars:size_t, radix:int_t

    xtox_s(rcx, rdx, r8, r9d, 0)
    ret

_ultow_s endp


_i64tow_s proc val:int64_t,  buffer:wstring_t, sizeInTChars:size_t, radix:int_t

    xor eax,eax
    .ifs (r9d == 10 && rcx < 0)
        inc eax
    .endif
    xtox_s(rcx, rdx, r8, r9d, eax)
    ret

_i64tow_s endp

_ui64tow_s proc val:int64_t, buffer:wstring_t, sizeInTChars:size_t, radix:int_t

    xtox_s(rcx, rdx, r8, r9d, 0)
    ret

_ui64tow_s endp

    end
