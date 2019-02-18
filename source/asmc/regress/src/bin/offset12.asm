;
; v2.28: negative offset extended to 64-bit
;
    .x64
    .model flat
    .code

    BUFFERSIZE equ 512

foo proc

  local buffer[BUFFERSIZE]:byte

    lea rax,buffer[BUFFERSIZE]
    ret

foo endp

    end

