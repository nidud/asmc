    ;
    ; v2.25 - REAL16 and float const parameters
    ;
    .486
    .model flat
    .data

    real16 1.e1     ; 0x40024000000000000000000000000000
    real16 1.e2     ; 0x40059000000000000000000000000000
    real16 1.e4     ; 0x400C3880000000000000000000000000
    real16 1.e8     ; 0x40197D78400000000000000000000000
    real16 1.e16    ; 0x40341C37937E08000000000000000000
    real16 1.e32    ; 0x40693B8B5B5056E16B3BE04000000000
    real16 1.e64    ; 0x40D384F03E93FF9F4DAA797ED6E38ED6
    real16 1.e128   ; 0x41A827748F9301D319BF8CDE66D86D62
    real16 1.e256   ; 0x435154FDD7F73BF3BD1BBB77203731FE FD - 2.27.19
    real16 1.e512   ; 0x46A3C633415D4C1D238D98CAB8A978A1 A0 - 2.27.19
    real16 1.e1024  ; 0x4D4892ECEB0D02EA182ECA1A7A51E317 16 - 2.27.19
    real16 1.e2048  ; 0x5A923D1676BB8A7ABBC94E9A519C6536 35 - 2.27.19
    real16 1.e4096  ; 0x752588C0A40514412F3592982A7F0095 - F00949524
    real16 1.e8192  ; 0x7FFF0000000000000000000000000000 - Infinity

    REAL16 0.0      ; 0x00000000000000000000000000000000
    REAL16 -0.0     ; 0x80000000000000000000000000000000
    REAL16 1.0      ; 0x3FFF0000000000000000000000000000
    REAL16 -2.0     ; 0xC0000000000000000000000000000000
    ;
    ; 0x7FFEFFFFFFFFFFFFFFFFFFFFFFFFFFFF - max quadruple precision
    ;
    ; 0x7FFB9999999999999999999999999997
    ;
    REAL16 1.189731495357231765085759326628007e4931
    ;
    ; 0x4000921FB54442D18469898CC51701B8
    ;
    REAL16 3.1415926535897932384626433832795028

    .code

p1  proc c a1:real4, a2:real8, a3:real10, a4:real16, a5:oword
    lea eax,a1
    lea eax,a2
    lea eax,a3
    lea eax,a4
    lea eax,a5
    ret
p1  endp

p2  proc stdcall a1:real4, a2:real8, a3:real10, a4:real16, a5:oword
    lea eax,a1
    lea eax,a2
    lea eax,a3
    lea eax,a4
    lea eax,a5
    ret
p2  endp

p3  proc pascal a1:real4, a2:real8, a3:real10, a4:real16, a5:oword
    lea eax,a1
    lea eax,a2
    lea eax,a3
    lea eax,a4
    lea eax,a5
    ret
p3  endp

    p1(1.0, 2.0, 3.0, 4.0, 5.0)
    p2(0.1, 0.2, 0.3, 0.4, 0.5)
    p3(10.1, 10.2, 10.3, 10.4, 10.5)

    end
