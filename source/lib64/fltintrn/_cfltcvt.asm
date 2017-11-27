include fltintrn.inc
include crtl.inc

XAM_INVALID     EQU 0001h
XAM_DENORMAL    EQU 0002h
XAM_ZERODIVIDE  EQU 0004h
XAM_OVERFLOW    EQU 0008h
XAM_UNDERFLOW   EQU 0010h
XAM_PRECISION   EQU 0020h
XAM_STACKFAULT  EQU 0040h
XAM_INTREQUEST  EQU 0080h
XAM_C0          EQU 0100h
XAM_C1          EQU 0200h
XAM_C2          EQU 0400h
XAM_TOP         EQU 3800h
XAM_C3          EQU 4000h
XAM_BUSY        EQU 8000h
XAM_CMASK       EQU 4700h

.data

convbuf     db 64 dup(0)
BCD_MAX     dq 1.0E18
int10       dd 10
tempw       dw 0
BCD_E17     dq 1.0E17
exponent    dd 0
state       dw 0
BCD         dt 0
sign        db 0

.code

__fconv proc private uses rsi rdi rbx buffer:LPSTR, ch_type:SINT, precision:SINT, capexp:SINT

    mov     sign,0
    fxam                    ; Test real
    fstsw   state           ; Store FPU status word
    movsx   eax,state
    .if eax & XAM_C1        ; check FXAM flags

        inc sign
    .endif

    and eax,XAM_CMASK       ; Condition flag
    .if eax != XAM_C2       ; +normal

        .if eax != XAM_C1 or XAM_C2 ; -normal

            mov eax,[rcx]
            add eax,[rcx+4]
            jnz infinity
            fldz
            mov exponent,0
            jmp unload_BCD
        .endif
    .endif

    fabs                    ; force number positive
    fxtract                 ; extract exponent
    fxch    st(1)           ; put exponent on top
    fldlg2                  ; form power of 10
    fmulp   st(1),st(0)
    fld     st(0)
    frndint
    fist    tempw
    movsx   eax,tempw
    mov     exponent,eax

    fsubp   st(1),st(0)     ; find fractional part of
    fldl2t                  ; load log2(10)
    fmulp   st(1),st(0)     ; log2(10) * argument
    fld     st(0)           ; duplicate product
    frndint                 ; get int part of product
    fld     st(0)           ; duplicate integer part
    fxch    st(2)           ; get original product
    fsubrp  st(1),st(0)     ; find fractional part
    fld1
    fchs
    fxch    st(1)           ; scale fractional part
    fscale
    fstp    st(1)           ; discard coprocessor junk
    f2xm1                   ; raise 2 to power-1
    fld1
    faddp   st(1),st(0)     ; correct for the -1
    fmul    st(0),st(0)     ; square result
    fscale                  ; scale by int part
    fstp    st(1)           ; discard coprocessor junk
    fmulp   st(1),st(0)     ; find fractional part of
    ;fld    BCD_MAX
    ;fmulp  st(1),st
    fmul    BCD_MAX         ; then times mantissa
    frndint                 ; zap any remaining fraction
@@:
    ;fld    BCD_E17
    ;fcomp  st(1)
    fcom    BCD_E17         ; is mantissa < 1.0e17?
    fstsw   tempw
    mov     ax,tempw
    sahf
    jpe     error
    ja      @F              ; no, proceed
    fimul   int10           ; yes, mantissa * 10
    dec     exponent        ; and decrement exponent
    jmp     @B
@@:
    ;fld    BCD_MAX
    ;fcomp  st(1)
    fcom    BCD_MAX         ; is mantissa < 1.0e18?
    fstsw   tempw
    mov     ax,tempw
    sahf
    jpe     error
    jb      unload_BCD      ; yes, proceed
    fidiv   int10           ; yes, mantissa / 10
    inc     exponent        ; and increment exponent
    jmp     @B

unload_BCD:

    fbstp   BCD             ; unload BCD in mantissa
    lea     rbx,BCD         ; convert BCD byte to ASCII
    mov     ecx,9
    lea     r8,convbuf
    xor     eax,eax
    .repeat
        mov al,[rbx]
        mov ah,al
        shr al,4
        and ah,0Fh
        add eax,'00'
        mov WORD PTR [r8+rcx*2-2],ax
        inc rbx
    .untilcxz

    mov rbx,buffer
    .if sign

        mov byte ptr [rbx],'-'
        inc rbx
    .endif

    lea rdx,convbuf
    mov ecx,exponent

    .if byte ptr ch_type != 'e' && ecx < 7

        .if ecx
            .repeat
                mov al,[rdx]
                mov [rbx],al
                inc rdx
                inc rbx
            .untilcxz
        .else
            mov byte ptr [rbx],'0'
            inc rbx
        .endif

        mov byte ptr [rbx],'.'
        inc rbx
        mov rax,rdx
        lea rcx,convbuf
        sub rax,rcx
        add rax,rdi
        mov rcx,rdi

        .if eax >= 18

            mov ecx,17
        .endif
        .repeat
            mov al,[rdx]
            mov [rbx],al
            inc rdx
            inc rbx
        .untilcxz

        .if byte ptr ch_type == 'g'

            mov eax,'0'
            .while [rbx-1] == al

                mov [rbx-1],ah
                dec rbx
            .endw

            .if byte ptr [rbx-1] == '.'

                mov [rbx-1],ah
                dec rbx
            .endif
        .endif
    .else

        mov eax,'0'
        mov rcx,rdi
        .if exponent

            mov al,[rdx]
            inc rdx
            inc exponent
        .endif

        .if byte ptr tempw == 'g'

            mov [rbx],al
            inc rbx
        .else
            mov ah,'.'
            mov [rbx],ax
            add rbx,2
            .repeat
                mov al,[rdx]
                mov [rbx],al
                inc rdx
                inc rbx
            .untilcxz
        .endif

        mov al,'e'      ; store 'e' for exponent
        .if capexp

            mov al,'E'  ; store 'E' for exponent
        .endif

        mov ecx,exponent    ; test sign of exponent
        mov ah,'+'
        .ifs    ecx < 0
            mov ah,'-'
            neg ecx
        .endif

        mov [rbx],ax    ; store sign of exponent
        add rbx,2
        sub ecx,2
        mov esi,4
        mov eax,ecx
        mov ecx,esi
        mov edi,10
        .repeat
            xor edx,edx
            div edi
            add dl,'0'
            mov [rbx+rcx-1],dl
        .untilcxz
        add rbx,rsi
    .endif

    .if convbuf == '-'
        inc buffer
    .endif
done:
    sub rbx,buffer
    mov eax,ebx
toend:
    ret
error:
    mov rbx,buffer

infinity:
    mov eax,'FNI+'
    .if sign

        mov al,'-'
    .endif
    mov rbx,buffer
    mov [rbx],eax
    add rbx,4
    jmp done
__fconv endp

_cldcvt proc fp:LPLONGDOUBLE, buffer:LPSTR, ch_type:SINT, precision:SINT, capexp:SINT

    mov     rcx,fp
    fld     TBYTE PTR [rcx]
    invoke  __fconv,buffer, ch_type, precision, capexp
    ret

_cldcvt endp

_cfltcvt proc fp:LPDOUBLE, buffer:LPSTR, ch_type:SINT, precision:SINT, capexp:SINT
local ld:REAL10

    mov     rax,fp
    lea     rdx,ld
    call    _iFDLD
    lea     rcx,ld
    fld     TBYTE PTR [rcx]
    invoke  __fconv,buffer, ch_type, precision, capexp
    ret

_cfltcvt endp

    END
