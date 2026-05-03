
; v2.36.44 - bit-field errors

.386
.model flat, c

ifdef __ASMC__
option masm:on
endif

option casemap:none

R record a:1, b:16, d:8

.data
r R <>
.code

foo proc

    local s:R

    ; no error

    mov eax,s
    mov eax,r
    mov eax,mask s.a
    mov eax,mask r.a
    mov eax,width s.a
    mov eax,width r.a

    ; error

    mov eax,s.a
    mov eax,r.a
    mov s.a,eax
    mov r.a,eax
    mov r.a,1
    ret

foo endp

    end
