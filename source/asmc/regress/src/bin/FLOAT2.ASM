
;--- test improved float support of v2.05

	.386
	.model flat

	.code

	dw .TYPE 25.1
	dw .TYPE (25.1)
	mov eax, 1.0
	real4 1.0, +1.0, -1.0
	dt real4 ptr 1.0, real4 ptr -1.0

	END
