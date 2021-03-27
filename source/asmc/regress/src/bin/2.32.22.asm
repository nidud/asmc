
    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

LARGE   struct
buf     dd 200 dup(?)
count   dd ?
LARGE   ends

RECT    struct
left    dd ?
top     dd ?
right   dd ?
bottom  dd ?
RECT    ends

RE      struct
rc      RECT <>
name    ptr sbyte ?
RE      ends

D3DMATRIX   STRUC
UNION ; {
STRUC
_11         real4 ?
_12         real4 ?
_13         real4 ?
_14         real4 ?
_21         real4 ?
_22         real4 ?
_23         real4 ?
_24         real4 ?
_31         real4 ?
_32         real4 ?
_33         real4 ?
_34         real4 ?
_41         real4 ?
_42         real4 ?
_43         real4 ?
_44         real4 ?
ENDS ;
m           real4 4 dup(?)
ENDS
D3DMATRIX   ENDS

.code

main proc

    .new s[8]:ptr = { 0 }
    .new l1:LARGE = { 0 }
    .new l2:LARGE = { { 10,,12 }, 1 }
    .new r1:RECT  = { 0 }
    .new r2:RECT  = { 1 , , 3, 4 }
    .new re:RE    = { { 1 , 2 , 3, ebx }, "string" }

    .new matrix:D3DMATRIX = {{{
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
        }}}

    ret

main endp

    end
