;
; v2.32.22 - extended call stack for YWORD and ZWORD
;

    option win64:save

    .code

p4 proc a:ptr, b:ptr, c:ptr, d:ptr

    ; mov [rsp+0x20], r9
    ; mov [rsp+0x18], r8
    ; mov [rsp+0x10], rdx
    ; mov [rsp+0x08], rcx

    add rax,a ; [rbp+0x10]
    add rax,b ; [rbp+0x18]
    add rax,c ; [rbp+0x20]
    add rax,d ; [rbp+0x28]
    ret
p4 endp
call_p4 proc  ; sub rsp, 4*8
    p4(rcx, rdx, r8, r9)
    ret
call_p4 endp

x4 proc a:real16, b:real16, c:real16, d:real16

    ; movaps [rsp+0x38], xmm3
    ; movaps [rsp+0x28], xmm2
    ; movaps [rsp+0x18], xmm1
    ; movaps [rsp+0x08], xmm0

    addps xmm4,a ; [rbp+0x10]
    addps xmm4,b ; [rbp+0x20]
    addps xmm4,c ; [rbp+0x30]
    addps xmm4,d ; [rbp+0x40]
    ret
x4 endp
call_x4 proc ; sub rsp, 4*16
    x4(xmm0, xmm1, xmm2, xmm3)
    ret
call_x4 endp

y4 proc a:yword, b:yword, c:yword, d:yword

    ; vmovups [rsp+0x68], ymm3
    ; vmovups [rsp+0x48], ymm2
    ; vmovups [rsp+0x28], ymm1
    ; vmovups [rsp+0x08], ymm0

    vaddps ymm4,ymm0,a ; [rbp+0x10]
    vaddps ymm4,ymm0,b ; [rbp+0x30]
    vaddps ymm4,ymm0,c ; [rbp+0x50]
    vaddps ymm4,ymm0,d ; [rbp+0x70]
    ret
y4 endp
call_y4 proc ; sub rsp, 4*32
    y4(ymm0, ymm1, ymm2, ymm3)
    ret
call_y4 endp

z4 proc a:zword, b:zword, c:zword, d:zword

    ; vmovups [rsp+0xC8], zmm3
    ; vmovups [rsp+0x88], zmm2
    ; vmovups [rsp+0x48], zmm1
    ; vmovups [rsp+0x08], zmm0

    vaddps zmm4,zmm0,a ; [rbp+0x10]
    vaddps zmm4,zmm0,b ; [rbp+0x50]
    vaddps zmm4,zmm0,c ; [rbp+0x90]
    vaddps zmm4,zmm0,d ; [rbp+0xD0]
    ret
z4 endp
call_z4 proc ; sub rsp, 4*64
    z4(zmm0, zmm1, zmm2, zmm3)
    ret
call_z4 endp

xyz proc a:zword, b:yword, c:real16

    ; vmovups [rsp+0xC8], zmm3
    ; vmovups [rsp+0x88], zmm2
    ; vmovups [rsp+0x48], zmm1
    ; vmovups [rsp+0x08], zmm0

    vaddps zmm4,zmm0,a ; [rbp+0x10]
    vaddps ymm4,ymm0,b ; [rbp+0x50]
    vaddps xmm4,xmm0,c ; [rbp+0x90]
    ret
xyz endp
call_xyz proc ; sub rsp, 4*64
    xyz(zmm0, ymm1, xmm2)
    ret
call_xyz endp

r3 proc a:real2, b:real4, c:real8

    ; movq [rsp+0x18], xmm2
    ; movd [rsp+0x10], xmm1
    ; movd [rsp+0x08], xmm0

    mov ax,a
    addss xmm4,b
    addsd xmm4,c
    ret

r3 endp
call_r3 proc ; sub rsp, 4*8
    r3(xmm0, xmm1, xmm2)
    ret
call_r3 endp

    end

