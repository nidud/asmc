include stdio.inc

.data

n equ <3.141592653589793238462643383279502884197169399375105820974945>

d REAL8  n
l REAL10 n
q REAL16 n

.code

main proc
    printf("- format %%g, %%Lg, %%llg\n")
    printf("%g\n",     d)
    printf("%Lg\n",    l)
    printf("%llg\n",   q)
    printf("- format %%f, %%Lf, %%llf\n")
    printf("%f\n",     d)
    printf("%Lf\n",    l)
    printf("%llf\n",   q)
    printf("- format %%e, %%Le, %%lle\n")
    printf("%e\n",     d)
    printf("%Le\n",    l)
    printf("%lle\n",   q)
    printf("- format %%.34f, %%.34Lf, %%.34llf\n")
    printf("%.34f\n",  d)
    printf("%.34Lf\n", l)
    printf("%.34llf\n",q)
    ret
main endp

    end

