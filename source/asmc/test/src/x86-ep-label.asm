
; v2.37.83: missing label for option -EP

.386
.model flat,c

.code

foo proc
_1:mov eax,1 ; label stripped...
jz _1
ret
foo endp

end
