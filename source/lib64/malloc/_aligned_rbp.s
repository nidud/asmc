;
; In case RBP/leave is used add RSP is not needed:
;
; *	 add rsp, 48 + @ReservedStack
; *	 leave
;
include stdio.inc
include malloc.inc

    .code

    option cstack:on

main proc

  local a16:oword ; RSP is aligned 16
  local a8: qword
  local a4: dword
  local a1: byte

    lea rdi,a16
    mov eax,1
    .if !(rdi & 16-1)
	dec eax
    .endif
    ret

main endp

    END
