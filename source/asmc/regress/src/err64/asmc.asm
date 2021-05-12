ifndef __ASMC64__
.x64
.model flat, fastcall
endif
.data
R RECORD a:1, b:2
S struc
l1 db ?
l2 dw ?
l4 dd ?
S ends
D dd 0

.code

foo proc p:ptr
    ret
foo endp

.pragma asmc(push, 0)

.for ::
.endf
.switch
.endsw
.if foo(0)
.endif

    .NAME text
    .TITLE text
    .SUBTITLE text

    mov eax,.LOW S
    mov eax,.HIGH S
    mov eax,.SIZE S
    mov eax,.LENGTH D
    mov eax,.THIS S
    mov eax,.MASK R
    mov eax,.WIDTH R.a

.pragma asmc(pop)

    NAME text
    TITLE text
    SUBTITLE text

    mov eax,LOW S
    mov eax,HIGH S
    mov eax,SIZE S
    mov eax,LENGTH D
    mov eax,THIS S
    mov eax,MASK R
    mov eax,WIDTH R.a

.pragma asmc(push, 0)

.for ::
.endf

.pragma asmc(pop)

    mov eax,LOW S

    end
