; _XTOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

    _itoa::     ; :int_t,  :string_t, :int_t
    _ltoa::     ; :long_t, :string_t, :int_t

    xor r9d,r9d
    .ifs (r8d == 10 && ecx < 0)
        inc     r9d
        movsxd  rcx,ecx
    .endif
    jmp xtox

    _i64toa::   ; :int64_t, :string_t, :int_t

    xor r9d,r9d
    .ifs (r8d == 10 && rcx < 0)
        inc r9d
    .endif
    jmp xtox

    _ultoa::    ; :ulong_t,  :string_t, :int_t

    mov eax,ecx
    mov ecx,eax

    _ui64toa::  ; :uint64_t, :string_t, :int_t

    xor r9d,r9d


xtox proc private val:qword, buf:string_t , radix:uint_t, is_neg:int_t

  local convbuf[256]:char_t

    mov rax,rcx
    .if r9d

        mov byte ptr [rdx],'-'
        inc rdx
        neg rax

    .endif

    .if rax == 0

        mov word ptr [rdx],'0'
        .return buf

    .endif

    mov r9,rdx
    mov ecx,lengthof(convbuf)-1
    mov convbuf[rcx],0

    .while rax && ecx

        xor edx,edx
        div r8
        add dl,'0'
        .ifs dl > '9'
            add dl,('A' - '9' - 1)
        .endif
        dec ecx
        mov convbuf[rcx],dl
    .endw

    mov rdx,r9
    .repeat

        mov al,convbuf[rcx]
        inc ecx
        mov [rdx],al
        inc rdx
    .until al == 0
    mov rax,buf
    ret

xtox endp

    end
