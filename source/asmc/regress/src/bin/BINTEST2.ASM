
;--- regression in v2.12
;--- offsets within a group weren't calculated correctly
;--- if the image started with ORG != 0

_TEXT segment 'CODE'
    ORG 100h
    mov ax, offset v1
    mov ax, offset v2
    ret
_TEXT ends

_DATA segment 
v1  db 16 dup (1)
_DATA ends

CONST segment
v2  db 16 dup (2)
CONST ends

DGROUP group _TEXT, _DATA, CONST

    END
