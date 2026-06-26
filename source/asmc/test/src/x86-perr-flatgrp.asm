
;--- v2.17: mixing 32- and 64-bit segments in ".model flat"
;--- ensure that a near call still throws an error.

    .386
    .model flat

    .code

main proc c
	call main64
main endp

	.x64

_TEXT64 segment use64 'CODE'
_TEXT64 ends

	.code _TEXT64

main64 proc
    ret
main64 endp

	end main
