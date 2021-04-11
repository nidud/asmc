
    ; Extended stack size

    option frame:auto

    RECT    struc
    left    dd ?
    top     dd ?
    right   dd ?
    bottom  dd ?
    RECT    ends

type2 macro id, type, frame
&type&_&id&_2&frame& proc type frame uses rbx a:RECT, b:real4
    lea rax,a
    lea rax,b
    ret
&type&_&id&_2&frame& endp
    endm

type7 macro id, type, frame
&type&_&id&_7&frame& proc type frame uses rbx a:RECT, b:real4, c:real8, d:real16, e:dword, f:qword, g:RECT
    lea rax,a
    lea rax,b
    lea rax,c
    lea rax,d
    lea rax,e
    lea rax,f
    lea rax,g
    ret
&type&_&id&_7&frame& endp
    endm

makeid macro id
    type2 id, fastcall
    type2 id, fastcall, frame
    type2 id, vectorcall
    type2 id, vectorcall, frame
    type7 id, fastcall
    type7 id, fastcall, frame
    type7 id, vectorcall
    type7 id, vectorcall, frame
    endm

callid macro id
    fastcall_&id&_2(a, b)
    fastcall_&id&_2frame(a, b)
    vectorcall_&id&_2(a, b)
    vectorcall_&id&_2frame(a, b)
    fastcall_&id&_7(a, b, c, d, e, f, a)
    fastcall_&id&_7frame(a, b, c, d, e, f, a)
    vectorcall_&id&_7(a, b, c, d, e, f, a)
    vectorcall_&id&_7frame(a, b, c, d, e, f, a)
    endm

    .code

    option win64:1
    option cstack:off
    makeid rbp_1_0
    option cstack:on
    makeid rbp_1_1

    option win64:3
    option cstack:off
    makeid rbp_3_0
    option cstack:on
    makeid rbp_3_1

    option win64:rsp save noauto
    option cstack:off
    makeid rsp_1_0
    option cstack:on
    makeid rsp_1_1

    option win64:rsp save auto
    option cstack:off
    makeid rsp_3_0
    option cstack:on
    makeid rsp_3_1

    option win64:rbp auto save align

main proc

  local a:RECT, b:real4, c:real8, d:real16, e:dword, f:qword

    for q,<a,b,c,d,e,f>
        lea rax,q
        endm
    for i,<rbp_1_0,rbp_1_1,rbp_3_0,rbp_3_1,rsp_1_0,rsp_1_1,rsp_3_0,rsp_3_1>
        callid i
        endm
    ret

main endp

    end
