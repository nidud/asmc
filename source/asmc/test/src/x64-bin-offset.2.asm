;
; v2.28: negative offset extended to 64-bit
;
    .code

    BUFFERSIZE equ 512

foo proc

  local buffer[BUFFERSIZE]:byte

    lea rax,buffer[BUFFERSIZE]
    ret
    endp

    end

