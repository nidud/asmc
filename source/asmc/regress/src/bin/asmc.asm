.x64
.model flat, fastcall
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

.pragma asmc(pop)

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

.pragma asmc(push, 0)

    mov eax,LOW S

.pragma asmc(pop)

.for ::
.endf

    end
