include stdio.inc
ifdef _MT
define LIBC <"(ASMC/Linux)">
else
define LIBC <"(GNU/Linux)">
endif
.code

main proc

    puts("Statically linked " LIBC "\n")
    xor eax,eax
    ret
    endp

    end
