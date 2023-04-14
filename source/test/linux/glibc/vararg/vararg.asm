include stdio.inc

    .code

xsprintf proc buffer:string_t, format:string_t, argptr:vararg

    vsprintf(buffer, format, &argptr)
    ret

xsprintf endp

main proc

  local string[256]:char_t
  local r0:real8, r1:real8

    xsprintf( &string, "const %d.%d\n", 1, 2 )
    printf( &string )

    mov rax,3.0
    mov rdx,2.0
    mov r0,rax
    mov r1,rdx

    movsd xmm2,r0
    divsd xmm2,r1

    xsprintf( &string, "%f / %f = %f\n", r0, r1, xmm2 )
    printf( &string )
    ret

main endp

    end
