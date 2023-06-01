; TEST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2022-07-11 - added exception info to Linux64
;
include stdio.inc
include signal.inc
ifdef __UNIX__
define __USE_GNU
include ucontext.inc
endif

    .code

myhandle proc sig:int_t

    printf( "myhandle called with sig: %d\n", sig)

    __crtPrintContext()
    mov rcx,__pxcptinfoptrs()
ifdef __UNIX__
    add [rcx].ucontext_t.uc_mcontext.gregs[REG_RIP*size_t],2
else
    mov rcx,[rcx].EXCEPTION_POINTERS.ContextRecord
 ifdef _WIN64
    add [rcx].CONTEXT._Rip,2
 else
    add [ecx].CONTEXT._Eip,2
 endif
endif
    .return(ExceptionContinueExecution)

myhandle endp


main proc

    signal(SIGSEGV, &myhandle)

    printf("create a debug break..\n")

    xor eax,eax
    mov [rax],eax

    printf("still here..\n")
   .return( 0 )

main endp

    end
