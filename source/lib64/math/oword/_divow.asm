; _divow() - Divide (OWORD)
;
; Unsigned binary division of dividend by source.
;
; Note: The quotient is stored in dividend.
;
include intn.inc

option win64:rsp nosave noauto

.code

_divow proc dividend:ptr, divisor:ptr, reminder:ptr

    mov rax,[rcx]
    mov [r8],rax
    mov rax,[rcx+8]
    mov [r8+8],rax
    xor rax,rax
    mov [rcx],rax
    mov [rcx+8],rax

    .repeat

        or rax,[rdx]
        or rax,[rdx+8]
        .ifz
            mov [r8],rax
            mov [r8+8],rax
            .break
        .endif

        mov rax,[rdx+8]
        sub rax,[r8+8]
        .ifz
            mov rax,[rdx]
            sub rax,[r8]
        .endif
        .ifa
            ;
            ; divisor > dividend : reminder = dividend, quotient = 0
            ;
            .break
        .else
            .ifz
                ;
                ; divisor == dividend : reminder = 0, quotient = 1
                ;
                mov [r8],rax
                mov [r8+8],rax
                inc byte ptr [rcx]
                .break
            .endif
        .endif

        mov rax,[rdx]       ; divisor
        mov rdx,[rdx+8]
        xor r9d,r9d         ; bit-count
        .while 1
            add rax,rax
            adc rdx,rdx
            jc  @F
            .if rdx == [r8+8]
                cmp rax,[r8]
            .endif
            ja  @F
            inc r9d
        .endw

        .while 1
            mov r10,[rcx]
            adc [rcx],r10
            mov r10,[rcx+8]
            adc [rcx+8],r10
            dec r9d
            .break .ifs
         @@:
            rcr rdx,1
            rcr rax,1
            sub [r8],rax
            sbb [r8+8],rdx
            cmc
            .continue .ifc
            .repeat
                mov r10,[rcx]
                add [rcx],r10
                mov r10,[rcx+8]
                adc [rcx+8],r10
                dec r9d
                .ifs
                    add [r8],rax
                    adc [r8+8],rdx
                    .break(1)
                .endif
                shr rdx,1
                rcr rax,1
                add [r8],rax
                adc [r8+8],rdx
            .until CARRY?
        .endw
    .until 1
    ret

_divow endp

    end
