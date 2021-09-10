;; https://msdn.microsoft.com/en-us/library/bkx0x9kc.aspx
;; getcallerseflags.cpp
;; processor: x86, x64
include stdio.inc
include intrin.inc
include tchar.inc
.code

g proc

  local EFLAGS:UINT

    mov EFLAGS,__getcallerseflags()
    printf("EFLAGS 0x%x\n", EFLAGS)
    mov eax,EFLAGS
    ret
g endp

f proc
    g()
    ret
f endp

main proc

  local i:UINT

    mov i,f()
    mov i,g()
    xor eax,eax
    ret
main endp

    end _tstart
