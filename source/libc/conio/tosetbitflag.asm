; TOSETBITFLAG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

tosetbitflag proc uses rsi rbx tobj:PTOBJ, count:int_t, flag:uint_t, bitflag:uint_t

    ldr rbx,tobj
    ldr eax,flag
    ldr esi,count
    ldr edx,bitflag

    mov ecx,eax
    not eax

    .while esi
        ;
        ; Remove the flag from Object
        ;
        and [rbx].TOBJ.flag,ax
        ;
        ; Max 32 object flags
        ;
        shr edx,1
        .ifc
            or [rbx].TOBJ.flag,cx
        .endif
        add rbx,TOBJ
        dec esi
    .endw
    ret

tosetbitflag endp

    end
