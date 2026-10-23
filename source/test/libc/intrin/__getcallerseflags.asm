;; https://msdn.microsoft.com/en-us/library/bkx0x9kc.aspx
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
    endp
 f proc
    g()
    ret
    endp
 main proc
  local i:UINT
    mov i,f()
    mov i,g()
    xor eax,eax
    ret
    endp
    end _tstart
