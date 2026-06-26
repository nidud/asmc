
;--- test jwasm -mz option
;--- 3 segments, segments 1 + 3 in same group
;--- bug until jwasm v2.12

	.286

_TEXT segment word public 'CODE'
_TEXT ends
_DATA1 segment para public 'DATA'
ditem1 db 16 dup ('1')
_DATA1 ends
_DATA2 segment para public 'DATA'
ditem2 db 16 dup ('2')
_DATA2 ends
_DATA3 segment para public 'DATA'
ditem3 db 16 dup ('3')
_DATA3 ends
_DATA4 segment para public 'DATA'
ditem4 db 16 dup ('4')
_DATA4 ends
_DATA5 segment para public 'DATA'
ditem5 db 16 dup ('5')
_DATA5 ends

GROUP1 group _DATA1, _DATA3, _DATA5

_TEXT segment

start:
	mov ax,offset ditem1
	mov ax,offset ditem2
	mov ax,offset ditem3
	mov ax,offset ditem4
	mov ax,offset ditem5
	mov ax,4c00h
	int 21h

_TEXT ends

STACK segment para stack 'STACK'
	db 100h dup (?)
STACK ends

	end start
