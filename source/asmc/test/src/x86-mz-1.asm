
;--- test jwasm -mz option
;--- the _BSS segment, located between
;--- _TEXT and STACK, must "move" the start
;--- of the STACK segment by 100h paragraphs.
;--- value of label stackbottom is not affected,
;--- since _BSS and stack do not belong to a group.

	.286

_TEXT segment word public 'CODE'
_TEXT ends
_BSS   segment para public 'BSS'
ditem db 01000h dup (?)
_BSS   ends

_TEXT segment

start:
	mov ax,STACK
	mov ss,ax
	mov sp,stackbottom
	mov ax,4c00h
	int 21h

_TEXT ends

STACK segment para stack 'STACK'
	db 100h dup (?)
stackbottom label near
STACK ends

	end start
