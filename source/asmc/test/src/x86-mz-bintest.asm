
    .286

S1 segment 'DATA'
    db 1
S1 ends

S2 segment 'DATA'
    org 40h
S2 ends

S3 segment 'DATA'
vb  db 2
S3 ends

DGROUP group S1,S2,S3

_TEXT segment 'CODE'
start:
    mov ax, offset vb	;offset should be 0050h
_TEXT ends

STACK segment stack
	db 16 dup (?)
STACK ends

    END start
