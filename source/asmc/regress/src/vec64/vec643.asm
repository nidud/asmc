;
; v2.32.22 - extended call stack for YWORD and ZWORD
;

    option win64:save

    .code

x6 proc a:real16, b:real16, c:real16, d:real16, e:real16, f:real16

    addps xmm4,a ; [rbp+0x10]
    addps xmm4,b ; [rbp+0x20]
    addps xmm4,c ; [rbp+0x30]
    addps xmm4,d ; [rbp+0x40]
    addps xmm4,e ; [rbp+0x50]
    addps xmm4,f ; [rbp+0x60]
    ret
x6 endp
call_x6 proc ; sub rsp, 6*16
    x6(xmm0, xmm1, xmm2, xmm3, xmm4, xmm5)
    ret
call_x6 endp

y4 proc a:yword, b:yword, c:yword, d:yword, e:yword, f:yword

    vaddps ymm4,ymm0,a ; [rbp+0x10]
    vaddps ymm4,ymm0,b ; [rbp+0x30]
    vaddps ymm4,ymm0,c ; [rbp+0x50]
    vaddps ymm4,ymm0,d ; [rbp+0x70]
    vaddps ymm4,ymm0,e ; [rbp+0x90]
    vaddps ymm4,ymm0,f ; [rbp+0xB0]
    ret
y4 endp
call_y4 proc ; sub rsp, 6*32
    y4(ymm0, ymm1, ymm2, ymm3, ymm4, ymm5)
    ret
call_y4 endp

z4 proc a:zword, b:zword, c:zword, d:zword, e:zword, f:zword

    vaddps zmm4,zmm0,a ; [rbp+0x010]
    vaddps zmm4,zmm0,b ; [rbp+0x050]
    vaddps zmm4,zmm0,c ; [rbp+0x090]
    vaddps zmm4,zmm0,d ; [rbp+0x0D0]
    vaddps zmm4,zmm0,e ; [rbp+0x110]
    vaddps zmm4,zmm0,f ; [rbp+0x150]
    ret
z4 endp
call_z4 proc ; sub rsp, 6*64
    z4(zmm0, zmm1, zmm2, zmm3, zmm4, zmm5)
    ret
call_z4 endp

xyz proc a:zword, b:yword, c:real16

    vaddps zmm4,zmm0,a ; [rbp+0x10]
    vaddps ymm4,ymm0,b ; [rbp+0x50]
    vaddps xmm4,xmm0,c ; [rbp+0x90]
    ret
xyz endp
call_xyz proc ; sub rsp, 6*64
    xyz(zmm0, ymm1, xmm2)
    ret
call_xyz endp

    end

