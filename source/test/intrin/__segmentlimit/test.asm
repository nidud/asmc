;; https://msdn.microsoft.com/en-us/library/twk0b398.aspx
include stdio.inc
include intrin.inc

ifdef _M_IX86
READETYPE typedef DWORD
else
READETYPE typedef QWORD
endif

EFLAGS_ZF       equ 0x00000040
KGDT_R3_DATA    equ 0x0020
RPL_MASK        equ 0x3

.code

main proc

  local eflags:READETYPE
  local sl:SDWORD
  initsl = 0xbaadbabe

    mov eflags,0
    mov sl,initsl

    printf("Before: segment limit =0x%x eflags =0x%x\n", sl, eflags);
    mov sl,__segmentlimit(KGDT_R3_DATA + RPL_MASK)

    mov eflags,__readeflags()
    lea r9,@CStr( "clear" )
    .if (eflags & EFLAGS_ZF)
        lea r9,@CStr( "set" )
    .endif
    printf("After: segment limit =0x%x eflags =0x%x eflags.zf = %s\n", sl, eflags, r9)

    ;; If ZF is set, the call to lsl succeeded; if ZF is clear, the call failed.
    lea rdx,@CStr( "Fail!" )
    .if (eflags & EFLAGS_ZF)
        lea rdx,@CStr( "Success!" )
    .endif
    printf("%s\n", rdx)

    ;; You can verify the value of sl to make sure that the instruction wrote to it
    lea rdx,@CStr( "changed" )
    .if (sl == initsl)
        lea rdx,@CStr( "unchanged" )
    .endif
    printf("sl was %s\n", rdx)
    xor eax,eax
    ret

main endp

    end main
