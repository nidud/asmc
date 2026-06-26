
;--- segment defined by ".code" should be first in the binary,
;--- name ".text"; works since v2.13.

	.386
	.model flat
	option dotname
	option casemap:none

	.code .text$1
	db 1
	.code .text$2
	db 2
	.code
_start:
	ret

	END _start
