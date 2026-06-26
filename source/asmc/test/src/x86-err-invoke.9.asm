
;--- v2.16: this test case demonstrates a deliberate Masm incompatibility:
;--- Masm converts near pointers to far pointers by additionally pushing
;--- register SS - JWasm emits error "argument type mismatch".
;
;--- The jwasm behavior is implemented since v2.11. Previous
;--- versions did accept the code below ( but pushed a word per
;--- argument only, which was definitely a bug ).

	.286
	.model small
	.stack 2048
	.dosseg

	.code

x1 proc far pascal a1:far ptr, a2:far ptr
	ret
x1 endp

x2 proc pascal p1:ptr, p2:ptr

	invoke x1, p1, p2
	ret
x2 endp

start:
	mov ax, 4C00h
	int 21h


	end start
