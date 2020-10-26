include stdio.inc
include time.inc

    .code

main proc

  local timer:time_t

    time(&timer)
    printf("%s\n", asctime(localtime(&timer)))
    ret

main endp

    end
