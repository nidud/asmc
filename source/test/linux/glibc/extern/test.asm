include stdio.inc
include stdlib.inc

getstring proto :SINT

    .code

main proc

    puts(getstring(0))
    puts(getstring(1))
    exit(0)
    ret

main endp

    end
