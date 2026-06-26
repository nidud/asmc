
;--- PUBLIC must not accept local labels if -Zm isn't set

	.286
	.model tiny

	public lbl1

	.code

p1 proc
	mov ax, 1
lbl1:
	ret
p1 endp


	END

