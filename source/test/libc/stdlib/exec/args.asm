; args.asm
; Illustrates the following variables used for accessing
; command-line arguments and environment variables:
; argc  argv  envp
; This program will be executed by exec which follows.

include stdio.inc

.code

main proc argc:int_t,   ; Number of strings in array argv
argv:array_t,           ; Array of command-line argument strings
envp:array_t            ; Array of environment variable strings

    ; Display each command-line argument.
    printf( "\nCommand-line arguments:\n" )
    .for( ebx = 0 : ebx < argc : ebx++ )
        mov rcx,argv
        printf( "  argv[%d]   %s\n", ebx, [rcx+rbx*array_t] )
    .endf

    ; Display each environment variable.
    printf( "\nEnvironment variables:\n" )
    mov rbx,envp
    mov argc,4
    .while( argc && array_t ptr [rbx] != NULL )
        printf( "  %s\n", [rbx] )
        add rbx,array_t
        dec argc
    .endw
    xor eax,eax
    ret

main endp

    end

