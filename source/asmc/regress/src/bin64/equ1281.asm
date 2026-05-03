
    ; 2.31.51 - __int128:
    ;
    ; ADD, SUB, MUL, DIV, MOD, NOT, SAL, SHL, SAR, SHR, AND, OR, XOR
    ;
    ; __float128:
    ; 2.34.02 - added sqrt
    ;
    ; +, -, *, /, EQ, NE, LT, LE, GT, GE, SQRT
    ;
ifndef __ASMC64__
    .x64
    .model flat
endif

    p = 3.14159265358979323846264338327950288419716939937511
    n = -2.0

    sqrt_approx macro f

      local x

        x = f sub 00010000000000000000000000000000r
        x = x shr 1
        x = x add 20000000000000000000000000000000r
        exitm<x>
        endm

    .code

    mov rdx,HIGH64( p )
    mov rax,LOW64 ( p )

    mov rdx,HIGH64( sqrt( p ) )
    mov rax,LOW64 ( sqrt( p ) )

    mov rdx,HIGH64( sqrt_approx( p ) )
    mov rax,LOW64 ( sqrt_approx( p ) )

    mov rdx,HIGH64( not p )
    mov rax,LOW64 ( not p )

    mov rdx,HIGH64( n and -0.0 )
    mov rax,LOW64 ( n and not -0.0 )

    mov rdx,HIGH64( p or -0.0 )
    mov rax,LOW64 ( p or not -0.0 )

    mov rdx,HIGH64( n xor -0.0 )
    mov rax,LOW64 ( n xor not -0.0 )

    mov rdx,HIGH64( -0.0 sar 127 )
    mov rax,LOW64 ( -0.0 shr 127 )

    mov rdx,HIGH64( 00000000000000000000000000000001r sal 127 )
    mov rax,LOW64 ( 00000000000000000000000000000001r shl 127 )

    mov rdx,HIGH64( 00000000000000000000000000000010r mul p )
    mov rax,LOW64 ( 00000000000000000000000000000010r mul p )

    mov rdx,HIGH64( p div 00000000000000000000000000000010r )
    mov rax,LOW64 ( p div 00000000000000000000000000000010r )

    mov rdx,HIGH64( p mod 00000000000000000000000000000010r )
    mov rax,LOW64 ( p mod 00000000000000000000000000000010r )

    mov rdx,HIGH64( p mul 2 )
    mov rax,LOW64 ( p mul 2 )

    mov rdx,HIGH64( p div 2 )
    mov rax,LOW64 ( p div 2 )

    mov rdx,HIGH64( p mod 2 )
    mov rax,LOW64 ( p mod 2 )

    end
