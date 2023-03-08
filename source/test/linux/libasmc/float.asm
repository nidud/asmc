include stdio.inc

pi equ <3.141592653589793238462643383279502884197169399375105820974945>

.code

main proc

   .new q:real16 = pi ; __float128  - 'll'
   .new l:real10 = pi ; long double - 'L'
   .new d:real8  = pi ; double

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

   .return( 0 )

main endp

    end
