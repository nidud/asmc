
; v2.39.14: fixup for Hexadecimal floating literals (C++17)

.data
 REAL4	0x1.8p4			; 00 00 C0 41
 align	8
 REAL8	0x1.0p-48		; 00 00 00 00 00 00 F0 3C
 REAL8	0x1.0p1			; 04000000000000000h
 REAL8	0x1.0p16		; 040F0000000000000h
 REAL8	0x1.0p-2		; 03FD0000000000000h
 REAL16 0x1.0p4095		; Requires Exponent Bit 11 set (+2048)
 REAL16 0x1.0p-4096		; Requires Exponent Bit 12 set (-4096)

.code
 movss xmm0, 0x1.0p1		; 0x40000000 2.0
 movss xmm1, 0x1.8p4		; 0x41C00000 1.5 * 2^4 = 24.0
 movss xmm2, 0x1.0p-16		; 0x38000000 2^-16 = 0.0000152587890625
 movss xmm3, 0x1.fffffep127	; 0x7F7FFFFF ~3.4028235e+38
 movsd xmm0, 0x1.0p1		; 0x4000000000000000 2.0
 movsd xmm1, 0x1.0p16		; 0x40F0000000000000 65536.0
 movsd xmm2, 0x1.0p-2		; 0x3FD0000000000000 0.25
 movsd xmm3, 0x1.8p3		; 0x4028000000000000 1.5 * 2^3 = 12.0
 movsd xmm4, 0x1.0p128		; 0x47F0000000000000 3.402823669209385e+38
 movsd xmm5, 0x1.0p-48		; 0x3CF0000000000000 2^-48
 movsd xmm2, 0x1.0p-16
 end