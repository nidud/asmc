include errno.inc
include quadmath.inc
include asmc.inc
include expreval.inc
include symbols.inc

    .code

    assume ebx:expr_t

quad_resize proc uses ebx opnd:expr_t, size:uint_t

    mov errno,0
    mov ebx,opnd
    mov eax,size

    .switch eax
    .case 10
        __cvtq_ld(ebx, ebx)
        .endc
    .case 8
        .if ( [ebx].chararray[15] & 0x80 )
            or  [ebx].flags,E_NEGATIVE
            and [ebx].chararray[15],0x7F
        .endif
        __cvtq_sd(ebx, ebx)
        .if ( [ebx].flags & E_NEGATIVE )
            or [ebx].chararray[7],0x80
        .endif
        mov [ebx].mem_type,MT_REAL8
        .endc
    .case 4
        .if ( [ebx].chararray[15] & 0x80 )
            or  [ebx].flags,E_NEGATIVE
            and [ebx].chararray[15],0x7F
        .endif
        __cvtq_ss(ebx, ebx)
        .if ( [ebx].flags & E_NEGATIVE )
            or [ebx].chararray[3],0x80
        .endif
        mov [ebx].mem_type,MT_REAL4
        .endc
    .case 2
        .if ( [ebx].chararray[15] & 0x80 )
            or  [ebx].flags,E_NEGATIVE
            and [ebx].chararray[15],0x7F
        .endif
        __cvtq_h(ebx, ebx)
        .if ( [ebx].flags & E_NEGATIVE )
            or [ebx].chararray[1],0x80
        .endif
        mov [ebx].mem_type,MT_REAL2
        .endc
    .endsw

    .if ( errno )
        asmerr( 2071 )
    .endif
    ret

quad_resize endp

    end

