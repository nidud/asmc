    .code

strchr::

    xor eax,eax
    .repeat

	mov al,[rcx]
	.break .if !al

	inc rcx
	.continue(0) .if al != dl

	lea rax,[rcx-1]
    .until 1
    ret

    END
