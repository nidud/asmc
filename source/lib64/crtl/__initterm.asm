; Disassembly of file: _initterm.obj
; Sat Mar 23 17:48:45 2019
; Mode: 64 bits
; Syntax: MASM/ML64
; Instruction set: 8086, x64
option dotname

public _initterm


_text   SEGMENT PARA 'CODE'                             ; section number 1

_initterm PROC
        push    rsi                                     ; 0000 _ 56
        push    rdi                                     ; 0001 _ 57
        push    rbx                                     ; 0002 _ 53
        sub     rsp, 32                                 ; 0003 _ 48: 83. EC, 20
        mov     rax, rdx                                ; 0007 _ 48: 8B. C2
        sub     rax, rcx                                ; 000A _ 48: 2B. C1
        jz      ?_005                                   ; 000D _ 74, 40
        mov     rsi, rcx                                ; 000F _ 48: 8B. F1
        lea     rdi, [rax+rcx]                          ; 0012 _ 48: 8D. 3C 08
?_001:  xor     eax, eax                                ; 0016 _ 33. C0
        mov     ecx, 256                                ; 0018 _ B9, 00000100
        mov     rbx, rsi                                ; 001D _ 48: 8B. DE
        mov     rdx, rdi                                ; 0020 _ 48: 8B. D7
?_002:  cmp     rbx, rdi                                ; 0023 _ 48: 3B. DF
        jz      ?_004                                   ; 0026 _ 74, 18
        cmp     rax, qword ptr [rbx]                    ; 0028 _ 48: 3B. 03
        jz      ?_003                                   ; 002B _ 74, 0D
        cmp     rcx, qword ptr [rbx+8H]                 ; 002D _ 48: 3B. 4B, 08
        jc      ?_003                                   ; 0031 _ 72, 07
        mov     rcx, qword ptr [rbx+8H]                 ; 0033 _ 48: 8B. 4B, 08
        mov     rdx, rbx                                ; 0037 _ 48: 8B. D3
?_003:  add     rbx, 16                                 ; 003A _ 48: 83. C3, 10
        jmp     ?_002                                   ; 003E _ EB, E3

?_004:  cmp     rdx, rdi                                ; 0040 _ 48: 3B. D7
        jz      ?_005                                   ; 0043 _ 74, 0A
        mov     rbx, qword ptr [rdx]                    ; 0045 _ 48: 8B. 1A
        mov     qword ptr [rdx], rax                    ; 0048 _ 48: 89. 02
        call    rbx                                     ; 004B _ FF. D3
        jmp     ?_001                                   ; 004D _ EB, C7
_initterm ENDP

?_005   LABEL NEAR
        add     rsp, 32                                 ; 004F _ 48: 83. C4, 20
        pop     rbx                                     ; 0053 _ 5B
        pop     rdi                                     ; 0054 _ 5F
        pop     rsi                                     ; 0055 _ 5E
        ret                                             ; 0056 _ C3

_text   ENDS

_data   SEGMENT PARA 'DATA'                             ; section number 2

_data   ENDS

.xdata  SEGMENT ALIGN(8) 'CONST'                        ; section number 3

$xdatasym label byte
        db 01H, 07H, 04H, 00H, 07H, 32H, 03H, 30H       ; 0000 _ .....2.0
        db 02H, 70H, 01H, 60H                           ; 0008 _ .p.`

.xdata  ENDS

.drectve SEGMENT BYTE 'CONST'                           ; section number 5

        db 2DH, 64H, 65H, 66H, 61H, 75H, 6CH, 74H       ; 0000 _ -default
        db 6CH, 69H, 62H, 3AH, 6CH, 69H, 62H, 63H       ; 0008 _ lib:libc
        db 2EH, 6CH, 69H, 62H, 20H, 2DH, 64H, 65H       ; 0010 _ .lib -de
        db 66H, 61H, 75H, 6CH, 74H, 6CH, 69H, 62H       ; 0018 _ faultlib
        db 3AH, 6EH, 74H, 64H, 6CH, 6CH, 2EH, 6CH       ; 0020 _ :ntdll.l
        db 69H, 62H, 20H, 2DH, 64H, 65H, 66H, 61H       ; 0028 _ ib -defa
        db 75H, 6CH, 74H, 6CH, 69H, 62H, 3AH, 75H       ; 0030 _ ultlib:u
        db 75H, 69H, 64H, 2EH, 6CH, 69H, 62H, 20H       ; 0038 _ uid.lib 
        db 2DH, 64H, 65H, 66H, 61H, 75H, 6CH, 74H       ; 0040 _ -default
        db 6CH, 69H, 62H, 3AH, 6BH, 65H, 72H, 6EH       ; 0048 _ lib:kern
        db 65H, 6CH, 33H, 32H, 2EH, 6CH, 69H, 62H       ; 0050 _ el32.lib
        db 20H, 2DH, 64H, 65H, 66H, 61H, 75H, 6CH       ; 0058 _  -defaul
        db 74H, 6CH, 69H, 62H, 3AH, 61H, 64H, 76H       ; 0060 _ tlib:adv
        db 61H, 70H, 69H, 33H, 32H, 2EH, 6CH, 69H       ; 0068 _ api32.li
        db 62H, 20H, 2DH, 64H, 65H, 66H, 61H, 75H       ; 0070 _ b -defau
        db 6CH, 74H, 6CH, 69H, 62H, 3AH, 67H, 64H       ; 0078 _ ltlib:gd
        db 69H, 33H, 32H, 2EH, 6CH, 69H, 62H, 20H       ; 0080 _ i32.lib 
        db 2DH, 64H, 65H, 66H, 61H, 75H, 6CH, 74H       ; 0088 _ -default
        db 6CH, 69H, 62H, 3AH, 75H, 73H, 65H, 72H       ; 0090 _ lib:user
        db 33H, 32H, 2EH, 6CH, 69H, 62H, 20H, 2DH       ; 0098 _ 32.lib -
        db 64H, 65H, 66H, 61H, 75H, 6CH, 74H, 6CH       ; 00A0 _ defaultl
        db 69H, 62H, 3AH, 76H, 65H, 72H, 73H, 69H       ; 00A8 _ ib:versi
        db 6FH, 6EH, 2EH, 6CH, 69H, 62H, 20H, 2DH       ; 00B0 _ on.lib -
        db 64H, 65H, 66H, 61H, 75H, 6CH, 74H, 6CH       ; 00B8 _ defaultl
        db 69H, 62H, 3AH, 6DH, 70H, 72H, 2EH, 6CH       ; 00C0 _ ib:mpr.l
        db 69H, 62H, 20H, 2DH, 64H, 65H, 66H, 61H       ; 00C8 _ ib -defa
        db 75H, 6CH, 74H, 6CH, 69H, 62H, 3AH, 77H       ; 00D0 _ ultlib:w
        db 69H, 6EH, 6DH, 6DH, 2EH, 6CH, 69H, 62H       ; 00D8 _ inmm.lib
        db 20H, 2DH, 64H, 65H, 66H, 61H, 75H, 6CH       ; 00E0 _  -defaul
        db 74H, 6CH, 69H, 62H, 3AH, 6EH, 65H, 74H       ; 00E8 _ tlib:net
        db 61H, 70H, 69H, 33H, 32H, 2EH, 6CH, 69H       ; 00F0 _ api32.li
        db 62H, 20H, 2DH, 64H, 65H, 66H, 61H, 75H       ; 00F8 _ b -defau
        db 6CH, 74H, 6CH, 69H, 62H, 3AH, 72H, 70H       ; 0100 _ ltlib:rp
        db 63H, 72H, 74H, 34H, 2EH, 6CH, 69H, 62H       ; 0108 _ crt4.lib
        db 20H, 2DH, 64H, 65H, 66H, 61H, 75H, 6CH       ; 0110 _  -defaul
        db 74H, 6CH, 69H, 62H, 3AH, 73H, 68H, 65H       ; 0118 _ tlib:she
        db 6CH, 6CH, 33H, 32H, 2EH, 6CH, 69H, 62H       ; 0120 _ ll32.lib
        db 20H, 2DH, 64H, 65H, 66H, 61H, 75H, 6CH       ; 0128 _  -defaul
        db 74H, 6CH, 69H, 62H, 3AH, 63H, 6FH, 6DH       ; 0130 _ tlib:com
        db 64H, 6CH, 67H, 33H, 32H, 2EH, 6CH, 69H       ; 0138 _ dlg32.li
        db 62H, 20H, 2DH, 64H, 65H, 66H, 61H, 75H       ; 0140 _ b -defau
        db 6CH, 74H, 6CH, 69H, 62H, 3AH, 6FH, 6CH       ; 0148 _ ltlib:ol
        db 65H, 33H, 32H, 2EH, 6CH, 69H, 62H, 20H       ; 0150 _ e32.lib 
        db 2DH, 64H, 65H, 66H, 61H, 75H, 6CH, 74H       ; 0158 _ -default
        db 6CH, 69H, 62H, 3AH, 6FH, 6CH, 65H, 61H       ; 0160 _ lib:olea
        db 75H, 74H, 33H, 32H, 2EH, 6CH, 69H, 62H       ; 0168 _ ut32.lib
        db 20H                                          ; 0170 _  

.drectve ENDS

END