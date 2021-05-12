;
; v2.28: HIGH64 and LOW64
;
ifndef __ASMC64__
    .x64
    .model flat
endif

    INT128_MIN  equ -170141183460469231731687303715884105728
    INT128_MAX  equ  170141183460469231731687303715884105727
    UINT128_MAX equ  340282366920938463463374607431768211455

    .code

    mov rax,LOW64  1
    mov rdx,HIGH64 1

    mov rax,LOW64  -1
    mov rdx,HIGH64 -1

    mov rax,LOW64  1.0
    mov rdx,HIGH64 1.0

    mov rax,LOW64  INT128_MIN
    mov rdx,HIGH64 INT128_MIN
    mov rax,LOW64  INT128_MAX
    mov rdx,HIGH64 INT128_MAX
    mov rax,LOW64  UINT128_MAX
    mov rdx,HIGH64 UINT128_MAX

    end

