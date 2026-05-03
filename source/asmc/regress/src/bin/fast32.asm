; v 2.23 - proto fastcall :type
; v 2.27 - error removed..

    .386
    .model flat, stdcall
    .code

S1  struc
l1  dd ?
l2  dd ?
S1  ends

foo proto fastcall :ptr S1
bar proto vectorcall :ptr S1
;
; This fails in ML: error A2008: syntax error : panel
;       and JWASM:  Error A2137: Conflicting parameter definition: panel
;       ASMC:   error A2111: conflicting parameter definition : panel
;
foo proc fastcall panel:ptr S1

    mov eax,[panel].S1.l1
    ret
foo endp

bar proc vectorcall panel:ptr S1

    mov eax,[panel].S1.l1
    ret
bar endp

    END
