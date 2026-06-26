
    ; 2.31.46

   .code

    option casemap:none, win64:auto

    .code

main proc

    ; @easycode: TYPE(<float>) failed within a macro()
    ;
    ; returned 16 (size of real16)
    ;
    mov eax,@CatStr(<!">, %(TYPEOF(5.0)), <!">)
    ;
    ; recursive typeid(?, ...)typeid(?, ...)
    ;
    ; skippes <?> as part of <name>
    ;
%   ifidn <typeid(rax)typeid(rax)>,<qwordqword>
        mov eax,0
    else
        mov eax,-1
    endif
    ret
    endp

    end
