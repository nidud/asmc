include stdio.inc

n equ <3.141592653589793238462643383279502884197169399375105820974945>

.data
d REAL8  n
l REAL10 n
q REAL16 n

.code

main proc
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
    printf("%.34llf - %%.34llf\n", q)
    xor eax,eax
    ret
main endp

    end

3.14159265358979310000 - %.20f - msvc
3.14159265358979311600 - %.20f - 32-bit
3.14159265358978956330 - %.20f - 64-bit
