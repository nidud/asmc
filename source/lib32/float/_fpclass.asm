; _FPCLASS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_fpclass proc __cdecl x:REAL8

    mov eax,dword ptr x
    mov edx,dword ptr x[4]
    mov ecx,edx
    shl edx,DBL_EXPBITS
    or  edx,eax
    shr ecx,32 - DBL_EXPBITS - 1
    mov eax,ecx
    and ecx,DBL_EXPMASK
    and eax,DBL_EXPMASK + 1
    ;;
    ;; With 0x7ff, it can only be infinity or NaN
    ;;
    .if ecx == DBL_EXPMASK

        .if !edx

            .if !eax
                mov eax,_FPCLASS_PINF
            .else
                mov eax,_FPCLASS_NINF
            .endif
        .else
            ;;
            ;; Windows will never return Signaling NaN
            ;;
            mov eax,_FPCLASS_QNAN
        .endif

    .elseif !ecx
        ;;
        ;; With 0, it can only be zero or denormalized number
        ;;
        .if !edx
            .if !eax
                mov eax,_FPCLASS_PZ
            .else
                mov eax,_FPCLASS_NZ
            .endif
        .elseif !eax
            mov eax,_FPCLASS_PD
        .else
            mov eax,_FPCLASS_ND
        .endif
    .else
        ;;
        ;; Only remain normalized numbers
        ;;
        .if !eax
            mov eax,_FPCLASS_PN
        .else
            mov eax,_FPCLASS_NN
        .endif
    .endif
    ret

_fpclass endp

    end
