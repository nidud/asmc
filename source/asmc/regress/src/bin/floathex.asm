
; v2.37.45: Hexadecimal floating literals (C++17)

   .486
   .model flat

define M_PI         3.14159265358979323846264338327950288419716939937511
define M_PI_2       1.57079632679489661923132169163975144209858469968755
define M_SQRTPI     1.77245385090551602729816748334114518279754945612239
define X_PI         0x3.243f6a8885a308d313198a2e03707344ap
define X_PI_2       0x3.243f6a8885a308d313198a2e03707344ap-1

   .data
    real16 M_PI
    real16 X_PI
    real16 M_PI_2
    real16 X_PI_2
    real16 M_SQRTPI
    real16 sqrt(M_PI)
    real16 sqrt(X_PI)
    real16 0xF.FFFFFEp+127
    real16 0xF.FFFFFFFFFFFFFp+1020
    real16 0x1.0p+16383
    real16 0x1.0p-16383
    real16 0x1.0p-126
    real16 0x1.Fp-1
    real16 0x0.3p10

    real10 0x3.243f6a8885a308d313198a2e03707344ap-1L
    align 16
    real10 M_PI_2
    align 16
    real8 0x3.243f6a8885a308d313198a2e03707344ap-1
    real8 M_PI_2
    real4 0x3.243f6a8885a308d313198a2e03707344ap-1
    real4 M_PI_2

    end
