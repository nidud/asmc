
;--- using INVOKE with ADDR operator and "far ptr"
;--- fixed in v2.16

	.286
	.model tiny		; use tiny model, allows near code items in printf
	.stack 2048
	.dosseg
	.386

	.const

szFmt1 db "near=>%s<, far=>%ls<",10,0
szStr1 db "abc",0

	.code

if 1
printf proc c fmt:ptr byte, args:vararg
	ret
printf endp
else
	.nolist
	include printf16.inc
	.list
endif

szStr3 db "abc",0

main proc

local szStr2[4]:byte

	mov eax, "cba"
	mov dword ptr szStr2, eax
	invoke printf, offset szFmt1, addr near ptr szStr1, addr far ptr szStr1
	invoke printf, offset szFmt1, addr near ptr szStr2, addr far ptr szStr2
	invoke printf, offset szFmt1, addr near ptr szStr3, addr far ptr szStr3
	ret
main endp

start:
	mov ax, cs   ; @data
	mov ds, ax
	mov dx, ss
	sub dx, ax
	shl dx, 4
	mov ss, ax   ; now CS=DS=SS=dgroup
	add sp, dx
	call main
	mov ax,4c00h
	int 21h

	end start
