; v2.34.73 - ASMCALL

    .x64
    .model flat, asmcall
    .code

    float  typedef real4
    double typedef real8

inl proto :float,:float,:byte,:float,:float,:word,:double,:double,:double,:dword,:qword,
          :float,:float,:float,:float,:ptr,:float,:ptr,:ptr,:float,:float,:float,:float {

    movq rax,_1     ; xmm0
    movq rax,_2     ; xmm1
    inc _3          ; al
    movq rax,_4     ; xmm2
    movq rax,_5     ; xmm3
    inc _6          ; dx
    movq rax,_7     ; xmm4
    movq rax,_8     ; xmm5
    movq rax,_9     ; xmm6
    inc _10         ; ecx
    inc _11         ; r8
    movq rax,_12    ; xmm7
    movq rax,_13    ; xmm8
    movq rax,_14    ; xmm9
    movq rax,_15    ; xmm10
    inc _16         ; r9
    movq rax,_17    ; xmm11
    inc _18         ; r10
    inc _19         ; r11
    movq rax,_20    ; xmm12
    movq rax,_21    ; xmm13
    movq rax,_22    ; xmm14
    movq rax,_23    ; xmm15
    }

stk proto :byte, :word, :dword, :qword, :ptr, :ptr, :ptr, :ptr {
    add rax,_8      ; [rsp]
    }

i16 proto :oword, :oword, :oword, :ptr {
    add rax,_1      ; rax - high qword in rdx
    add rax,_2      ; rcx - high qword in r8
    add rax,_3      ; r9  - high qword in r10
    add rax,_4      ; r11
    }

main proc

    inl(xmm0,xmm1,al,xmm2,xmm3,dx,xmm4,xmm5,xmm6,ecx,r8,xmm7,xmm8,xmm9,xmm10,r9,xmm11,r10,r11,xmm12,xmm13,xmm14,xmm15)
    inl(0.0,1.0,2,3.0,4.0,5,6.0,7.0,8.0,9,10,11.0,12.0,13.0,14.0,15,16.0,17,18,19.0,20.0,21.0,22.0)

    ; push    rax
    ; movzx   edx, dx
    ; movzx   eax, al

    stk(al,dx,ecx,r8,r9,r10,r11,rax)

    ; add     rsp, 8

    i16(rdx::rax, r8::rcx, r10::r9, r11)
    i16(rax, r8::rcx, r10::r9, r11)
    i16(1, 2, 3, 4)
    ret

main endp

    end
