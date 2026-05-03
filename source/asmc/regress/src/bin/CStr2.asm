;
; v2.30.33 -- @Cstr( n ) - get label of prev strings
;
    .386
    .model flat

    S equ <@CStr>

    .code

    lea eax,S("A")
    lea ebx,S("B")
    lea ecx,S("C")

    mov cl,S(0) ; DS0002
    mov bl,S(1) ; DS0001
    mov al,S(2) ; DS0000

    lea ecx,S( "A\\B")
    lea ecx,S(L"A\\B")

    mov ax,S(0) ; DS0004

    mov al,sizeof(S(1))   ; 4
    mov dl,sizeof(S(0))   ; 8

    mov al,lengthof(S(1)) ; 4
    mov dl,lengthof(S(0)) ; 4

    end

