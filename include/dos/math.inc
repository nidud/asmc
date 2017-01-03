.xlist

_mul10 PROTO _CType	; (e)dx:(e)ax * 10	--> dx:ax
_mul32 PROTO _CType	; dx:ax * cx:bx		--> cx:bx:dx:ax
_div32 PROTO _CType	; dx:ax / cx:bx		--> dx:ax.cx
_shl32 PROTO		; dx:ax << cl		--> dx:ax
_shr32 PROTO		; dx:ax >> cl		--> dx:ax
_div64 PROTO		; edx:eax / ecx		--> edx:eax.ecx
_mul64 PROTO		; edx:eax * ecx:ebx	--> ecx:ebx:edx:eax
_shl64 PROTO		; edx:eax << cl		--> edx:eax
_shr64 PROTO		; edx:eax >> cl		--> edx:eax

.list
