
    ; 2.32.60 watcall -- extend byte/word to 32-bit
ifndef __ASMC64__
    .x64
    .model flat, watcall
endif
    .code

foo proc watcall a:dword, b:dword, c:sdword, d:sdword
    ; allow byte/word args..
    ret
foo endp

bar proc watcall a:byte, b:sbyte, c:word, d:sword

 local e:byte, f:sbyte, g:word, h:sword

    foo( a, b, c, d )
    foo( e, f, g, h )
    ret
bar endp

main proc

    bar( al, al, dx, dx )     ; extend to 32-bit
    bar( eax, edx, ebx, ecx ) ; nothing done..
    ret
main endp

    end
