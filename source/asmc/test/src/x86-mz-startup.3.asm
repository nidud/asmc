
; v2.36.25 - (bugthis) -- SMALL, C, OS_DOS

	.286
	.model small, c, OS_DOS
	.stack 100h

	.code

	.startup
	.exit 1+2+3

	END
