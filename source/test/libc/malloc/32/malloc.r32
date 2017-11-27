include malloc.inc

	.data
	core dd 20 dup(?)
	diff dd 20 dup(?)
	memp dd 20 dup(?)
	.code
	getcore macro i
		call	__coreleft
		mov	core[i*4],eax
		endm
	getmemp macro i,z
		.assert malloc(z)
		mov	memp[i*4],eax
		endm
	setdiff macro i,x
		mov	eax,core
		sub	eax,core[x*4]
		mov	diff[i*4],eax
		endm
	getcdm macro i,d,m
		getcore i
		setdiff d,d+1
		getmemp m,_HEAP_GROWSIZE / 16
		endm

main	proc c
;	int 3
	.assert malloc(8)
	.assert free(eax)
	getcore 0

	.assert _aligned_malloc( _SEGSIZE_, _SEGSIZE_ )
	free(eax)

	getmemp 0,124
	getcore 1
	setdiff 0,1
	.assert eax

	free(memp)
	getcore 2
	setdiff 1,2
	.assert !eax

	getmemp 1,_HEAP_GROWSIZE - 1
	getcore 3
	setdiff 2,3
	free(memp[1*4])
	getcore 4
	setdiff 3,4
	.assert !eax

	getmemp 2,_HEAP_GROWSIZE / 16
	getcdm	5,4,3
	getcdm	6,5,4
	getcdm	7,6,5
	getcdm	8,7,6
	getcdm	9,8,7
	getcdm	10,9,8
	getcore 11
	setdiff 10,11
	getmemp 9,_HEAP_GROWSIZE / 32
	getcore 12
	setdiff 11,12
	getmemp 10,_HEAP_GROWSIZE / 64
	getcore 13
	setdiff 12,13
	free(memp[2*4])
	free(memp[3*4])
	free(memp[4*4])
	free(memp[5*4])
	free(memp[6*4])
	free(memp[7*4])
	free(memp[8*4])
	free(memp[9*4])
	free(memp[10*4])
	getcore 14
	setdiff 13,14
	.assert !eax

	.assert _aligned_malloc( _SEGSIZE_, _SEGSIZE_ )
	.assert !ax
	.assert free(eax)

	mov	eax,_amblksiz
	add	eax,eax
	.assert malloc(eax)
	.assert free(eax)
	xor	eax,eax
	ret
main	endp

	end
