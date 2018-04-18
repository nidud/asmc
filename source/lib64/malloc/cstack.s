include string.inc
include stdio.inc
include cheap.inc

    .code

main proc

  local stk:LPCSTACK

  mov stk,CStack::CStack(NULL, 10, @ReservedStack)

  .assert rax
  .assert stk.Alloc(16)
  .assert stk.Free(rax)
  .assert !stk.Alloc(17)
  stk.Release()
  xor eax,eax
  ret

main endp

    end

