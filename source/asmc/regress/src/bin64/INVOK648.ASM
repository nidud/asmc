
;--- test 64-bit invoke with float/double parameter

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
	option win64:2

	.data

flt1	real4 1.0
dbl1	real8 1.0

	.code

p1 proc a1:real8
p1 endp

p5 proc a1:real8, a2:real4, a3:real4, a4:real8, a5:real8
p5 endp

	invoke p1, dbl1
	invoke p1, 1.0

	invoke p5, dbl1, flt1, flt1, dbl1, dbl1
	invoke p5, 1.0, 2.0, 3.0, 4.0, 5.0
	ret

	end
