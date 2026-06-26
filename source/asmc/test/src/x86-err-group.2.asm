
    .model small
    .dosseg
    option casemap:none
    .stack 5120

DGROUP group _TEXT
DGROUP group _TEXT32	;segment added to group BEFORE it is defined

    .code

start16 proc
	mov ax,4c00h
	int 21h
start16 endp

    .386

_TEXT32 segment para use32 public 'CODE'	;should cause an error "segment word sizes differ"
	nop
_TEXT32 ends


    end start16
