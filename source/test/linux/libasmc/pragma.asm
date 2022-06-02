include stdio.inc

.pragma init(init_proc, 100)
.pragma exit(exit_proc, 100)

.code

init_proc proc
    printf("init function called\n")
    ret
init_proc endp

exit_proc proc
    printf("exit function called\n")
    ret
exit_proc endp

main proc
   .return 0
main endp

    end

