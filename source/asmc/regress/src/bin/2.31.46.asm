
    .x64
    .model flat, fastcall
    .code

    option casemap:none, win64:auto

    stack typedef ptr qword

.template stack
    .operator leave { mov rcx,this }
    .ends
    .code

main proc
    ;
    ; failed without argument(s)
    ;
    stack::leave()

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
%   ifidn <typeid(?, rax)typeid(?, rax)>,<?r64?r64>
        mov eax,0
    else
        mov eax,-1
    endif
    ret

main endp

    end
