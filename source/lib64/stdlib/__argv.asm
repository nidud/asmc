; __ARGV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc
include winbase.inc

.data
__argv	dq 0
_pgmptr dq 0

.code

Install proc private
    mov __argv,setargv(addr __argc, GetCommandLineA())
    mov rcx,[rax]
    mov _pgmptr,rcx
    ret
Install endp

.pragma(init(Install, 4))

    end
