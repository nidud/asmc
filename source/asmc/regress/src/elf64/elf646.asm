;
; v2.31 - vararg and stack param
;

    .code

    option win64:auto

foo proto format:ptr, argptr:vararg

bar proc

  local p:ptr sbyte, x:word, b:byte

    foo(rdi,esi,edx,ecx,r8d,r9d) ; no stack

    foo(rdi,esi,edx,ecx,r8d,r9d,al)
    foo(rdi,esi,edx,ecx,r8d,r9d,al,al)
    foo(rdi,esi,edx,ecx,r8d,r9d,ax,eax)
    foo(rdi,rsi,rdx,rcx,r8,r9,p)
    foo(rdi,rsi,rdx,rcx,r8,r9,x,b,[rbx],"string",L"WideString")
    ret

bar endp

    end
