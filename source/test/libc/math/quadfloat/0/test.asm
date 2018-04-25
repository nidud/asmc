include stdio.inc

.data

pi equ <3.141592653589793238462643383279502884197169399375105820974945>

d real16 pi / 2.0
l real16 pi / 3.0
q real16 pi

.code

main proc

    printf("Quadfloat format %%ll[e|f|g]\n")
    printf("%llg\n", q)
    printf("%llf\n", q)
    printf("%lle\n", q)
    printf("%.32llf\n", q)
    printf("%.32llf\n", d)
    printf("%.32llf\n", l)
    ret

main endp

    end