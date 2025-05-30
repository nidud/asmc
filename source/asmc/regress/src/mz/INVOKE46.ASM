
;--- using INVOKE with ADDR operator and "far ptr" - 32-bit variant
;--- fixed in v2.16

	.386
	.model tiny	; use tiny to allow near code pointers in printf
	.stack 2048
	.dosseg

?REAL equ 0

	.const

szFmt1 db "near text=>%s<, far text=>%ls<",10,0
szStr1 db "abc",0

	.code

ife ?REAL
printf proc c fmt:ptr byte, args:vararg
	ret
printf endp
else
	.nolist
	include printf.inc
	.list
endif

szStr3 db "abc",0

main proc
local szStr2[4]:byte
	mov dword ptr [szStr2], "cba"
	invoke printf, offset szFmt1, addr near ptr szStr1, addr far ptr szStr1
	invoke printf, offset szFmt1, addr near ptr szStr2, addr far ptr szStr2
	invoke printf, offset szFmt1, addr near ptr szStr3, addr far ptr szStr3
	ret
main endp

start32:
	call main
	mov ax, 4C00h
	int 21h

if ?REAL
	.nolist
	include initpm.inc
	.list
else
_TEXT16 segment use16 public 'CODE'
start:
	mov ax,4c00h
	int 21h
_TEXT16 ends
endif

	end start
