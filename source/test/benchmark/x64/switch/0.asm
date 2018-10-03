
    .code

    .if ecx > COUNT
        xor eax,eax
    enum = 0
    repeat  COUNT
    .elseif ecx == enum
        mov eax,enum
    enum = enum + 1
    endm
    .endif
    ret

    end
