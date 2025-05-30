
    ; 2.34.42 - Tokenize quote failed on text macro

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    lea ebx,[ebx*2]
    lea ebx,[rbx*2]
    lea ebx,[ebx*4]
    lea ebx,[rbx*4]

    end
