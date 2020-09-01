; _XTOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

    _itow::     ; :int_t,  :wstring_t, :int_t
    _ltow::     ; :long_t, :wstring_t, :int_t

    xor r9d,r9d
    .ifs (r8d == 10 && ecx < 0)
        inc r9d
    .endif
    jmp xtox

    _i64tow::   ; :int64_t, :wstring_t, :int_t

    xor r9d,r9d
    .ifs (r8d == 10 && rcx < 0)
        inc r9d
    .endif
    jmp xtox

    _ultow::    ; :ulong_t,  :wstring_t, :int_t

    mov eax,ecx
    mov ecx,eax

    _ui64tow::  ; :uint64_t, :wstring_t, :int_t

    xor r9d,r9d


xtox proc private val:qword, buf:wstring_t , radix:uint_t, is_neg:int_t

  local convbuf[256]:wchar_t

    mov rax,rcx
    .if r9d

        mov wchar_t ptr [rdx],'-'
        add rdx,wchar_t
        neg rax

    .endif

    .if rax == 0

        mov dword ptr [rdx],'0'
        .return buf

    .endif

    mov r9,rdx
    mov ecx,( sizeof(convbuf) - wchar_t )
    mov convbuf[rcx],0

    .while rax && ecx

        xor edx,edx
        div r8
        add dl,'0'
        .ifs dl > '9'
            add dl,('A' - '9' - 1)
        .endif

        sub ecx,wchar_t
        mov convbuf[rcx],dx
    .endw

    mov rdx,r9
    .repeat

        mov ax,convbuf[rcx]
        add ecx,wchar_t
        mov [rdx],ax
        add rdx,wchar_t

    .until ax == 0

    mov rax,buf
    ret

xtox endp

    end
