
    ; 2.32.43 - watcall -- extend byte/word to 32-bit

    .486
    .model flat, watcall
    .code

foo proc a:dword, b:dword, c:sdword, d:sdword
    ; allow byte/word args..
    ret
foo endp

bar proc a:byte, b:sbyte, c:word, d:sword

 local e:byte, f:sbyte, g:word, h:sword

    foo( a, b, c, d )
    foo( e, f, g, h )
    ret
bar endp

main proc

    bar( al, bl, cx, dx )     ; extend to 32-bit
    bar( eax, edx, ebx, ecx ) ; nothing done..
    ret
main endp

    end
