include stdio.inc

    .code

getstring proc id:SINT

    lea rax,@CStr( "string 0" )
    .if id
       lea rax,@CStr( "string 1" )
    .endif
    ret

getstring endp

    end
