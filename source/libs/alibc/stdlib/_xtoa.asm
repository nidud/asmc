; _XTOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .code

    _itoa::     ; :int_t,  :string_t, :int_t
    _ltoa::     ; :long_t, :string_t, :int_t

    xor     ecx,ecx
    cmp     edx,10
    jne     xtox
    test    edi,edi
    jns     xtox
    inc     ecx
    movsxd  rdi,edi
    jmp     xtox

    _i64toa::   ; :int64_t, :string_t, :int_t

    xor     ecx,ecx
    cmp     edx,10
    jne     xtox
    test    rdi,rdi
    jns     xtox
    inc     ecx
    jmp     xtox

    _ultoa::    ; :ulong_t,  :string_t, :int_t

    mov     eax,edi
    mov     edi,eax

    _ui64toa::  ; :uint64_t, :string_t, :int_t

    xor     ecx,ecx

xtox proc private val:qword, buf:string_t , radix:uint_t, is_neg:int_t

  local convbuf[256]:char_t

    mov r10,rsi
    mov rax,rdi
    .if ecx

        mov byte ptr [rsi],'-'
        inc rsi
        neg rax
    .endif

    .if rax == 0

        mov word ptr [rsi],'0'
        .return r10
    .endif

    mov r8,rdx
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

    .repeat

        mov al,convbuf[rcx]
        inc ecx
        mov [rsi],al
        inc rsi
    .until al == 0
    mov rax,r10
    ret

xtox endp

    end
