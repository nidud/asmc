
    ; 2.31.46

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option casemap:none, win64:auto

    .code

main proc

    ; @easycode: typeof(<float>) failed within a macro()
    ;
    ; returned 16 (size of real16)
    ;
    mov eax,@CatStr(<!">, %(typeof(5.0)), <!">)
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

main endp

    end
