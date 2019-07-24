; Disassembly of file: qsort.obj
; Sun Jul 21 15:46:10 2019
; Mode: 64 bits
; Syntax: MASM/ML64
; Instruction set: 80386, x64
option dotname

public qsort

extern memxchg: near


_text   SEGMENT PARA 'CODE'                             ; section number 1

qsort   PROC
        mov     qword ptr [rsp+8H], rcx                 ; 0000 _ 48: 89. 4C 24, 08
        mov     qword ptr [rsp+10H], rdx                ; 0005 _ 48: 89. 54 24, 10
        mov     qword ptr [rsp+18H], r8                 ; 000A _ 4C: 89. 44 24, 18
        mov     qword ptr [rsp+20H], r9                 ; 000F _ 4C: 89. 4C 24, 20
        push    rsi                                     ; 0014 _ 56
        push    rdi                                     ; 0015 _ 57
        push    rbx                                     ; 0016 _ 53
        push    rbp                                     ; 0017 _ 55
        mov     rbp, rsp                                ; 0018 _ 48: 8B. EC
        sub     rsp, 40                                 ; 001B _ 48: 83. EC, 28
        mov     rax, qword ptr [rbp+30H]                ; 001F _ 48: 8B. 45, 30
        cmp     rax, 1                                  ; 0023 _ 48: 83. F8, 01
        jbe     ?_018                                   ; 0027 _ 0F 86, 00000183
        dec     rax                                     ; 002D _ 48: FF. C8
        mul     qword ptr [rbp+38H]                     ; 0030 _ 48: F7. 65, 38
        mov     rsi, qword ptr [rbp+28H]                ; 0034 _ 48: 8B. 75, 28
        lea     rdi, [rax+rsi]                          ; 0038 _ 48: 8D. 3C 30
        mov     dword ptr [rbp-4H], 0                   ; 003C _ C7. 45, FC, 00000000
?_001:  mov     rcx, qword ptr [rbp+38H]                ; 0043 _ 48: 8B. 4D, 38
        lea     rax, [rcx+rdi]                          ; 0047 _ 48: 8D. 04 39
        sub     rax, rsi                                ; 004B _ 48: 2B. C6
        jz      ?_002                                   ; 004E _ 74, 0C
        xor     rdx, rdx                                ; 0050 _ 48: 33. D2
        div     rcx                                     ; 0053 _ 48: F7. F1
        shr     rax, 1                                  ; 0056 _ 48: D1. E8
        mul     rcx                                     ; 0059 _ 48: F7. E1
?_002:  sub     rsp, 32                                 ; 005C _ 48: 83. EC, 20
        lea     rbx, [rax+rsi]                          ; 0060 _ 48: 8D. 1C 30
        mov     rdx, rbx                                ; 0064 _ 48: 8B. D3
        mov     rcx, rsi                                ; 0067 _ 48: 8B. CE
        call    qword ptr [rbp+40H]                     ; 006A _ FF. 55, 40
        cmp     eax, 0                                  ; 006D _ 83. F8, 00
        jle     ?_003                                   ; 0070 _ 7E, 0F
        mov     r8, qword ptr [rbp+38H]                 ; 0072 _ 4C: 8B. 45, 38
        mov     rdx, rbx                                ; 0076 _ 48: 8B. D3
        mov     rcx, rsi                                ; 0079 _ 48: 8B. CE
        call    memxchg                                 ; 007C _ E8, 00000000(rel)
?_003:  mov     rdx, rdi                                ; 0081 _ 48: 8B. D7
        mov     rcx, rsi                                ; 0084 _ 48: 8B. CE
        call    qword ptr [rbp+40H]                     ; 0087 _ FF. 55, 40
        cmp     eax, 0                                  ; 008A _ 83. F8, 00
        jle     ?_004                                   ; 008D _ 7E, 0F
        mov     r8, qword ptr [rbp+38H]                 ; 008F _ 4C: 8B. 45, 38
        mov     rdx, rdi                                ; 0093 _ 48: 8B. D7
        mov     rcx, rsi                                ; 0096 _ 48: 8B. CE
        call    memxchg                                 ; 0099 _ E8, 00000000(rel)
?_004:  mov     rdx, rdi                                ; 009E _ 48: 8B. D7
        mov     rcx, rbx                                ; 00A1 _ 48: 8B. CB
        call    qword ptr [rbp+40H]                     ; 00A4 _ FF. 55, 40
        cmp     eax, 0                                  ; 00A7 _ 83. F8, 00
        jle     ?_005                                   ; 00AA _ 7E, 0F
        mov     r8, qword ptr [rbp+38H]                 ; 00AC _ 4C: 8B. 45, 38
        mov     rdx, rdi                                ; 00B0 _ 48: 8B. D7
        mov     rcx, rbx                                ; 00B3 _ 48: 8B. CB
        call    memxchg                                 ; 00B6 _ E8, 00000000(rel)
?_005:  mov     qword ptr [rbp+28H], rsi                ; 00BB _ 48: 89. 75, 28
        mov     qword ptr [rbp+30H], rdi                ; 00BF _ 48: 89. 7D, 30
?_006:  mov     rax, qword ptr [rbp+38H]                ; 00C3 _ 48: 8B. 45, 38
        mov     rax, qword ptr [rbp+38H]                ; 00C7 _ 48: 8B. 45, 38
        add     qword ptr [rbp+28H], rax                ; 00CB _ 48: 01. 45, 28
        cmp     qword ptr [rbp+28H], rdi                ; 00CF _ 48: 39. 7D, 28
        jnc     ?_007                                   ; 00D3 _ 73, 0F
        mov     rdx, rbx                                ; 00D5 _ 48: 8B. D3
        mov     rcx, qword ptr [rbp+28H]                ; 00D8 _ 48: 8B. 4D, 28
        call    qword ptr [rbp+40H]                     ; 00DC _ FF. 55, 40
        cmp     eax, 0                                  ; 00DF _ 83. F8, 00
        jle     ?_006                                   ; 00E2 _ 7E, DF
?_007:  mov     rax, qword ptr [rbp+38H]                ; 00E4 _ 48: 8B. 45, 38
        sub     qword ptr [rbp+30H], rax                ; 00E8 _ 48: 29. 45, 30
        cmp     qword ptr [rbp+30H], rbx                ; 00EC _ 48: 39. 5D, 30
        jbe     ?_008                                   ; 00F0 _ 76, 11
        mov     rdx, rbx                                ; 00F2 _ 48: 8B. D3
        mov     rcx, qword ptr [rbp+30H]                ; 00F5 _ 48: 8B. 4D, 30
        call    qword ptr [rbp+40H]                     ; 00F9 _ FF. 55, 40
        cmp     eax, 0                                  ; 00FC _ 83. F8, 00
        jle     ?_008                                   ; 00FF _ 7E, 02
        jmp     ?_007                                   ; 0101 _ EB, E1

?_008:  mov     rcx, qword ptr [rbp+30H]                ; 0103 _ 48: 8B. 4D, 30
        mov     rax, qword ptr [rbp+28H]                ; 0107 _ 48: 8B. 45, 28
        cmp     rcx, rax                                ; 010B _ 48: 3B. C8
        jc      ?_010                                   ; 010E _ 72, 18
        mov     r8, qword ptr [rbp+38H]                 ; 0110 _ 4C: 8B. 45, 38
        mov     rdx, rax                                ; 0114 _ 48: 8B. D0
        call    memxchg                                 ; 0117 _ E8, 00000000(rel)
        cmp     rbx, qword ptr [rbp+30H]                ; 011C _ 48: 3B. 5D, 30
        jnz     ?_009                                   ; 0120 _ 75, 04
        mov     rbx, qword ptr [rbp+28H]                ; 0122 _ 48: 8B. 5D, 28
?_009:  jmp     ?_006                                   ; 0126 _ EB, 9B

?_010:  mov     rax, qword ptr [rbp+38H]                ; 0128 _ 48: 8B. 45, 38
        add     qword ptr [rbp+30H], rax                ; 012C _ 48: 01. 45, 30
?_011:  mov     rax, qword ptr [rbp+38H]                ; 0130 _ 48: 8B. 45, 38
        sub     qword ptr [rbp+30H], rax                ; 0134 _ 48: 29. 45, 30
        cmp     qword ptr [rbp+30H], rsi                ; 0138 _ 48: 39. 75, 30
        jbe     ?_012                                   ; 013C _ 76, 10
        mov     rdx, rbx                                ; 013E _ 48: 8B. D3
        mov     rcx, qword ptr [rbp+30H]                ; 0141 _ 48: 8B. 4D, 30
        call    qword ptr [rbp+40H]                     ; 0145 _ FF. 55, 40
        test    eax, eax                                ; 0148 _ 85. C0
        jnz     ?_012                                   ; 014A _ 75, 02
        jmp     ?_011                                   ; 014C _ EB, E2

?_012:  add     rsp, 32                                 ; 014E _ 48: 83. C4, 20
        mov     rdx, qword ptr [rbp+28H]                ; 0152 _ 48: 8B. 55, 28
        mov     rax, qword ptr [rbp+30H]                ; 0156 _ 48: 8B. 45, 30
        sub     rax, rsi                                ; 015A _ 48: 2B. C6
        mov     rcx, rdi                                ; 015D _ 48: 8B. CF
        sub     rcx, rdx                                ; 0160 _ 48: 2B. CA
        cmp     rax, rcx                                ; 0163 _ 48: 3B. C1
        jge     ?_015                                   ; 0166 _ 7D, 1D
        mov     rcx, qword ptr [rbp+30H]                ; 0168 _ 48: 8B. 4D, 30
        cmp     rdx, rdi                                ; 016C _ 48: 3B. D7
        jnc     ?_013                                   ; 016F _ 73, 05
        push    rdx                                     ; 0171 _ 52
        push    rdi                                     ; 0172 _ 57
        inc     dword ptr [rbp-4H]                      ; 0173 _ FF. 45, FC
?_013:  cmp     rsi, rcx                                ; 0176 _ 48: 3B. F1
        jnc     ?_014                                   ; 0179 _ 73, 08
        mov     rdi, rcx                                ; 017B _ 48: 8B. F9
        jmp     ?_001                                   ; 017E _ E9, FFFFFEC0

?_014:  jmp     ?_017                                   ; 0183 _ EB, 1B

?_015:  mov     rcx, qword ptr [rbp+30H]                ; 0185 _ 48: 8B. 4D, 30
        cmp     rsi, rcx                                ; 0189 _ 48: 3B. F1
        jnc     ?_016                                   ; 018C _ 73, 05
        push    rsi                                     ; 018E _ 56
        push    rcx                                     ; 018F _ 51
        inc     dword ptr [rbp-4H]                      ; 0190 _ FF. 45, FC
?_016:  cmp     rdx, rdi                                ; 0193 _ 48: 3B. D7
        jnc     ?_017                                   ; 0196 _ 73, 08
        mov     rsi, rdx                                ; 0198 _ 48: 8B. F2
        jmp     ?_001                                   ; 019B _ E9, FFFFFEA3

?_017:  cmp     dword ptr [rbp-4H], 0                   ; 01A0 _ 83. 7D, FC, 00
        jz      ?_018                                   ; 01A4 _ 74, 0A
        dec     dword ptr [rbp-4H]                      ; 01A6 _ FF. 4D, FC
        pop     rdi                                     ; 01A9 _ 5F
        pop     rsi                                     ; 01AA _ 5E
        jmp     ?_001                                   ; 01AB _ E9, FFFFFE93
qsort   ENDP

?_018   LABEL NEAR
        leave                                           ; 01B0 _ C9
        pop     rbx                                     ; 01B1 _ 5B
        pop     rdi                                     ; 01B2 _ 5F
        pop     rsi                                     ; 01B3 _ 5E
        ret                                             ; 01B4 _ C3

_text   ENDS

_data   SEGMENT PARA 'DATA'                             ; section number 2

_data   ENDS

.drectve SEGMENT BYTE 'CONST'                           ; section number 3

        db 2DH, 64H, 65H, 66H, 61H, 75H, 6CH, 74H       ; 0000 _ -default
        db 6CH, 69H, 62H, 3AH, 6CH, 69H, 62H, 63H       ; 0008 _ lib:libc
        db 2EH, 6CH, 69H, 62H, 20H                      ; 0010 _ .lib 

.drectve ENDS

END