
    ; 2.32.60 watcall -- extend byte/word to 32-bit

.code

foo proc watcall a:dword, b:dword, c:sdword, d:sdword
    ; allow byte/word args..
    ret
    endp

bar proc watcall a:byte, b:sbyte, c:word, d:sword

 local e:byte, f:sbyte, g:word, h:sword

    foo( a, b, c, d )
    foo( e, f, g, h )
    ret
    endp

main proc

    bar( al, al, dx, dx )     ; extend to 32-bit
    bar( eax, edx, ebx, ecx ) ; nothing done..
    ret
    endp

    end
