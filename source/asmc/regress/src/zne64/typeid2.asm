
    ; 2.35.55 - typeid( struct field, record )

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option casemap:none
;    option win64:auto

define T_imm 1
define T_ptrS 2

.template S
    x dd ?
    y dd ?
   .ends
   PS typedef ptr S

.template R
    record
     x db : 4 ?
     y db : 5 ?
    ends
   .ends
   PS typedef ptr S

    .code

main proc

    local s:S
    local r:R
    local ps:PS

    mov eax,typeid(T_, S)
    mov eax,typeid(T_, R)
    mov eax,typeid(T_, ps)
    mov eax,typeid(T_, S.y)
    mov eax,typeid(T_, R.y)
    mov eax,typeid(s.y)
    mov eax,typeid(r.y)
    mov eax,MASK typeid(r.y)
    ret

main endp

    end
