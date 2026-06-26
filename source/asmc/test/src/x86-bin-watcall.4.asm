
    ; 2.33.20 watcall -- extend imm-qword to 32-bit

    .486
    .model flat, watcall
    .code

foo proc a:qword, b:qword
    ; edx:eax, ecx:ebx
    ret
foo endp

bar proc

 local a:qword

    foo( a, 0x8000000000000000 )
    ret
bar endp

    end
