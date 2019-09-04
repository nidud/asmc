include stdio.inc

pi equ <3.141592653589793238462643383279502884197169399375105820974945>

.data
d REAL8  pi
l REAL10 pi
q REAL16 pi

.code

main proc

    printf("%.34llf - %%.34llf\n", q)
    printf("%g - %%g\n", d)
    printf("%Lg - %%Lg\n", l)
    printf("%llg - %%llg\n", q)
    printf("%f - %%f\n", d)
    printf("%Lf - %%Lf\n", l)
    printf("%llf - %%llf\n", q)
    printf("%e - %%e\n", d)
    printf("%Le - %%Le\n", l)
    printf("%lle - %%lle\n", q)
    printf("%.20f - %%.20f\n", d)
    printf("%.24Lf - %%.24Lf\n", l)
    xor eax,eax
    ret

main endp

    end
