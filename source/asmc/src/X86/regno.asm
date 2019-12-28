; REGISTERS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include parser.inc
include reswords.inc
include memalloc.inc

    .code

get_register proc uses ecx reg:int_t, size:int_t

    .if GetValueSp(reg) & OP_XMM
        mov size,16
    .endif
    movzx ecx,GetRegNo(reg)
    mov eax,reg

    .switch size
    .case 1
        .switch ecx
        .case 0,1,2,3
            .return(&[ecx+T_AL])
        .case 4,5,6,7,8,9,10,11,12,13,14,15
            .return(&[ecx+T_SPL-4])
        .endsw
        .endc
    .case 2
        .switch ecx
        .case 0,1,2,3,4,5,6,7
            .return(&[ecx+T_AX])
        .case 8,9,10,11,12,13,14,15
            .return(&[ecx+T_R8W-8])
        .endsw
        .endc
    .case 4
        .switch ecx
        .case 0,1,2,3,4,5,6,7
            .return(&[ecx+T_EAX])
        .case 8,9,10,11,12,13,14,15
            .return(&[ecx+T_R8D-8])
        .endsw
        .endc
    .case 8
        .switch ecx
        .case 0,1,2,3,4,5,6,7
            .return(&[ecx+T_RAX])
        .case 8,9,10,11,12,13,14,15
            .return(&[ecx+T_R8-8])
        .endsw
        .endc
    .endsw
    ret

get_register endp

get_regname proc reg:int_t, size:int_t

    mov reg,get_register(reg, size)
    GetResWName(reg, LclAlloc(8))
    ret

get_regname endp

    end
