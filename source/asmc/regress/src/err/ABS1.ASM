
;--- invalid operator arguments

	.286
	.model small

	.code

v1	db 0

	mov ax, typeof 0	;ok

	mov ax, seg    0
	mov ax, offset 0;ok

	mov ax, LENGTH 0
	mov ax, SIZE	0
	mov ax, lengthof 0
	mov ax, sizeof 0

	mov ax, seg    bx
	mov ax, offset bx
	mov ax, LENGTH bx
	mov ax, SIZE	bx
	mov ax, lengthof bx
	mov ax, sizeof bx
	mov al, HIGH	bx
	mov al, LOW	bx]
	mov ax, HIGHWORD bx
	mov ax, LOWWORD	 bx

	mov ax, seg    [bx]
	mov ax, offset [bx]
	mov ax, LENGTH [bx]
	mov ax, SIZE	[bx]
	mov ax, lengthof [bx]
	mov ax, sizeof [bx]
	mov al, HIGH	[bx]
	mov al, LOW	[bx]
	mov ax, HIGHWORD [bx]
	mov ax, LOWWORD	 [bx]

	mov ax, seg    _TEXT	;ok
	mov ax, offset _TEXT	;ok
	mov ax, LENGTH _TEXT ;expected data label
	mov ax, SIZE	_TEXT	 ;expected data label
	mov ax, lengthof _TEXT	;expected data label
	mov ax, sizeof _TEXT	;expected data label
	mov al, HIGH	_TEXT	;should be an error
	mov al, LOW	_TEXT	;should be an error
	mov ax, HIGHWORD _TEXT
	mov ax, LOWWORD	 _TEXT	;should be an error

	mov ax, LENGTH (v1+1)	;should be an error, but is currently accepted

	end
