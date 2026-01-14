include strsafe.inc

.code

 main proc

   .new buffer[128]:char_t

    StringCchGetsA(&buffer, 128)
    puts(&buffer)
    xor eax,eax
    ret
    endp

    end

