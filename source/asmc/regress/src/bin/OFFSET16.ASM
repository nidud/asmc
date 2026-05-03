
;--- v2.16: warning level 3 "magnitude of offset exceeds 16-bit"
;--- before v2.16, it was an error.
;--- this is the case cs=use32, ds=use16, offset>64k

	.386
	.model small
	.stack 2048
	.dosseg

seg16 segment use16 public 'DATA'
seg16 ends

	.code

	assume ds:seg16

	mov eax,ds:[0BEEFh]
	mov eax,ds:[0DEADBEEFh]
	mov eax,es:[0DEADBEEFh]	;this should pass without warning, since no "16-bit assume" for es
	ret

	END

