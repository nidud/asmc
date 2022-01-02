; _LTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ltype.inc

    public  _ltype

    .data

_ltype byte 0,          ; -1 EOF
    _CONTROL,           ; 00 (NUL)
    _CONTROL,           ; 01 (SOH)
    _CONTROL,           ; 02 (STX)
    _CONTROL,           ; 03 (ETX)
    _CONTROL,           ; 04 (EOT)
    _CONTROL,           ; 05 (ENQ)
    _CONTROL,           ; 06 (ACK)
    _CONTROL,           ; 07 (BEL)
    _CONTROL,           ; 08 (BS)
    _SPACE+_CONTROL,    ; 09 (HT)
    _SPACE+_CONTROL,    ; 0A (LF)
    _SPACE+_CONTROL,    ; 0B (VT)
    _SPACE+_CONTROL,    ; 0C (FF)
    _SPACE+_CONTROL,    ; 0D (CR)
    _CONTROL,           ; 0E (SI)
    _CONTROL,           ; 0F (SO)
    _CONTROL,           ; 10 (DLE)
    _CONTROL,           ; 11 (DC1)
    _CONTROL,           ; 12 (DC2)
    _CONTROL,           ; 13 (DC3)
    _CONTROL,           ; 14 (DC4)
    _CONTROL,           ; 15 (NAK)
    _CONTROL,           ; 16 (SYN)
    _CONTROL,           ; 17 (ETB)
    _CONTROL,           ; 18 (CAN)
    _CONTROL,           ; 19 (EM)
    _CONTROL,           ; 1A (SUB)
    _CONTROL,           ; 1B (ESC)
    _CONTROL,           ; 1C (FS)
    _CONTROL,           ; 1D (GS)
    _CONTROL,           ; 1E (RS)
    _CONTROL,           ; 1F (US)
    _SPACE,             ; 20 SPACE
    _PUNCT,             ; 21 !
    _PUNCT,             ; 22 ""
    _PUNCT,             ; 23 #
    _PUNCT+_LABEL,      ; 24 $
    _PUNCT,             ; 25 %
    _PUNCT,             ; 26 &
    _PUNCT,             ; 27 '
    _PUNCT,             ; 28 (
    _PUNCT,             ; 29 )
    _PUNCT,             ; 2A *
    _PUNCT,             ; 2B +
    _PUNCT,             ; 2C
    _PUNCT,             ; 2D -
    _PUNCT,             ; 2E .
    _PUNCT,             ; 2F /
    _DIGIT+_HEX,        ; 30 0
    _DIGIT+_HEX,        ; 31 1
    _DIGIT+_HEX,        ; 32 2
    _DIGIT+_HEX,        ; 33 3
    _DIGIT+_HEX,        ; 34 4
    _DIGIT+_HEX,        ; 35 5
    _DIGIT+_HEX,        ; 36 6
    _DIGIT+_HEX,        ; 37 7
    _DIGIT+_HEX,        ; 38 8
    _DIGIT+_HEX,        ; 39 9
    _PUNCT,             ; 3A :
    _PUNCT,             ; 3B ;
    _PUNCT,             ; 3C <
    _PUNCT,             ; 3D =
    _PUNCT,             ; 3E >
    _PUNCT+_LABEL,      ; 3F ?
    _PUNCT+_LABEL,      ; 40 @
    _UPPER+_LABEL+_HEX, ; 41 A
    _UPPER+_LABEL+_HEX, ; 42 B
    _UPPER+_LABEL+_HEX, ; 43 C
    _UPPER+_LABEL+_HEX, ; 44 D
    _UPPER+_LABEL+_HEX, ; 45 E
    _UPPER+_LABEL+_HEX, ; 46 F
    _UPPER+_LABEL,      ; 47 G
    _UPPER+_LABEL,      ; 48 H
    _UPPER+_LABEL,      ; 49 I
    _UPPER+_LABEL,      ; 4A J
    _UPPER+_LABEL,      ; 4B K
    _UPPER+_LABEL,      ; 4C L
    _UPPER+_LABEL,      ; 4D M
    _UPPER+_LABEL,      ; 4E N
    _UPPER+_LABEL,      ; 4F O
    _UPPER+_LABEL,      ; 50 P
    _UPPER+_LABEL,      ; 51 Q
    _UPPER+_LABEL,      ; 52 R
    _UPPER+_LABEL,      ; 53 S
    _UPPER+_LABEL,      ; 54 T
    _UPPER+_LABEL,      ; 55 U
    _UPPER+_LABEL,      ; 56 V
    _UPPER+_LABEL,      ; 57 W
    _UPPER+_LABEL,      ; 58 X
    _UPPER+_LABEL,      ; 59 Y
    _UPPER+_LABEL,      ; 5A Z
    _PUNCT,             ; 5B [
    _PUNCT,             ; 5C \
    _PUNCT,             ; 5D ]
    _PUNCT,             ; 5E ^
    _PUNCT+_LABEL,      ; 5F _
    _PUNCT,             ; 60 `
    _LOWER+_LABEL+_HEX, ; 61 a
    _LOWER+_LABEL+_HEX, ; 62 b
    _LOWER+_LABEL+_HEX, ; 63 c
    _LOWER+_LABEL+_HEX, ; 64 d
    _LOWER+_LABEL+_HEX, ; 65 e
    _LOWER+_LABEL+_HEX, ; 66 f
    _LOWER+_LABEL,      ; 67 g
    _LOWER+_LABEL,      ; 68 h
    _LOWER+_LABEL,      ; 69 i
    _LOWER+_LABEL,      ; 6A j
    _LOWER+_LABEL,      ; 6B k
    _LOWER+_LABEL,      ; 6C l
    _LOWER+_LABEL,      ; 6D m
    _LOWER+_LABEL,      ; 6E n
    _LOWER+_LABEL,      ; 6F o
    _LOWER+_LABEL,      ; 70 p
    _LOWER+_LABEL,      ; 71 q
    _LOWER+_LABEL,      ; 72 r
    _LOWER+_LABEL,      ; 73 s
    _LOWER+_LABEL,      ; 74 t
    _LOWER+_LABEL,      ; 75 u
    _LOWER+_LABEL,      ; 76 v
    _LOWER+_LABEL,      ; 77 w
    _LOWER+_LABEL,      ; 78 x
    _LOWER+_LABEL,      ; 79 y
    _LOWER+_LABEL,      ; 7A z
    _PUNCT,             ; 7B {
    _PUNCT,             ; 7C |
    _PUNCT,             ; 7D }
    _PUNCT,             ; 7E ~
    _CONTROL            ; 7F (DEL)

    db 128 dup(0)       ; and the rest are 0...

    .code

    option dotname
    option win64:rsp noauto nosave

tmemcpy proc fastcall uses rdi dst:ptr, src:ptr, z:uint_t

    mov     rax,rcx ; -- return value
    xchg    rsi,rdx
    mov     ecx,r8d
    mov     rdi,rax
    rep     movsb
    mov     rsi,rdx
    ret

tmemcpy endp

tmemmove proc fastcall uses rsi rdi dst:ptr, src:ptr, z:uint_t

    mov     rax,rcx ; -- return value
    mov     rsi,rdx
    mov     ecx,r8d
    mov     rdi,rax
    cmp     rax,rsi
    ja      .0
    rep     movsb
    jmp     .1
.0:
    lea     rsi,[rsi+rcx-1]
    lea     rdi,[rdi+rcx-1]
    std
    rep     movsb
    cld
.1:
    ret

tmemmove endp

tstrlen proc fastcall string:string_t

    push    rcx
    xorps   xmm0,xmm0
.0:
    movups  xmm1,[rcx]
    pcmpeqb xmm1,xmm0
    pmovmskb eax,xmm1
    add     rcx,16
    test    eax,eax
    jz      .0
    bsf     eax,eax
    lea     rax,[rax+rcx-16]
    pop     rcx
    sub     rax,rcx
    ret

tstrlen endp

tstrcmp proc fastcall a:string_t, b:string_t

    mov     eax,1
.0:
    test    al,al
    jz      .1
    mov     al,[rcx]
    inc     rdx
    inc     rcx
    cmp     al,[rdx-1]
    je      .0
    sbb     eax,eax
    sbb     eax,-1
.1:
    ret

tstrcmp endp

tmemcmp proc fastcall uses rsi rdi dst:ptr, src:ptr, size:size_t

    mov     rdi,rcx
    mov     rsi,rdx
    mov     ecx,r8d
    xor     eax,eax
    repe    cmpsb
    je      .0
    sbb     eax,eax
    sbb     eax,-1
.0:
    ret

tmemcmp endp

tmemicmp proc fastcall uses rsi rdi dst:ptr, src:ptr, size:size_t

    mov     rsi,rcx
    mov     rdi,rdx
    mov     eax,r8d
.0:
    test    eax,eax
    jz      .1

    mov     cl,[rsi]
    mov     dl,[rdi]
    inc     rsi
    inc     rdi
    dec     eax
    cmp     cl,dl
    je      .0

    mov     ch,cl
    sub     cl,'a'
    cmp     cl,'Z'-'A'+1
    sbb     cl,cl
    and     cl,'a'-'A'
    xor     cl,ch

    mov     dh,dl
    sub     dl,'a'
    cmp     dl,'Z'-'A'+1
    sbb     dl,dl
    and     dl,'a'-'A'
    xor     dl,dh

    cmp     cl,dl
    je      .0

    sbb     eax,eax
    sbb     eax,-1
.1:
    ret

tmemicmp endp

tstricmp proc fastcall uses rsi rdi a:string_t, b:string_t

    mov     rsi,rcx
    mov     rdi,rdx
    mov     eax,1
.0:
    test    al,al
    jz      .1

    mov     al,[rsi]
    mov     cl,[rdi]
    inc     rsi
    inc     rdi
    cmp     al,cl
    je      .0

    mov     dl,al
    sub     al,'a'
    cmp     al,'Z'-'A'+1
    sbb     al,al
    and     al,'a'-'A'
    xor     al,dl

    mov     dl,cl
    sub     cl,'a'
    cmp     cl,'Z'-'A'+1
    sbb     cl,cl
    and     cl,'a'-'A'
    xor     cl,dl

    cmp     al,cl
    je      .0

    sbb     eax,eax
    sbb     eax,-1
.1:
    ret

tstricmp endp


tstrupr proc fastcall string:string_t

    push     rcx
.0:
    mov     al,[rcx]
    test    al,al
    jz      .1

    sub     al,'a'
    cmp     al,'Z'-'A'+1
    sbb     al,al
    and     al,'a'-'A'
    xor     [rcx],al
    inc     rcx
    jmp     .0
.1:
    pop     rax
    ret

tstrupr endp

tstrstart proc watcall string:string_t

    movzx   ecx,byte ptr [rax]
    lea     rdx,_ltype
.0:
    test    byte ptr[rdx+rcx+1],_SPACE
    jz      .1
    inc     rax
    mov     cl,[rax]
    jmp     .0
.1:
    ret

tstrstart endp

tstrstartr proc watcall string:string_t

    movzx   ecx,byte ptr [rax]
    lea     rdx,_ltype
.0:
    test    byte ptr[rdx+rcx+1],_SPACE
    jz      .1
    dec     rax
    mov     cl,[rax]
    jmp     .0
.1:
    ret

tstrstartr endp

    end

