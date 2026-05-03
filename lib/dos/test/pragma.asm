include stdio.inc

.code

init_proc proc
    printf("init function called\n")
    ret
init_proc endp

exit_proc1 proc
    printf("exit function 1 called\n")
    ret
exit_proc1 endp

exit_proc2 proc
    printf("exit function 2 called\n")
    ret
exit_proc2 endp

main proc

   xor ax,ax
   ret

main endp

.pragma init(init_proc, 100)
.pragma exit(exit_proc1, 1)
.pragma exit(exit_proc2, 2)

    end

