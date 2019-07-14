; MEM2MEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include token.inc
include hll.inc

    .code

    assume ebx:tok_t

mem2mem proc uses esi edi ebx op1:dword, op2:dword, tokenarray:tok_t

  local op:int_t

    mov eax,op1
    mov edx,op2
    and eax,OP_MS
    and edx,OP_MS

    .repeat

        .break .if ( !eax || eax != edx )
        .break .if ( ModuleInfo.strict_masm_compat == 1 )

        mov esi,T_RAX
        .switch
          .case eax & OP_M08: mov esi,T_AL  : .endc
          .case eax & OP_M16: mov esi,T_AX  : .endc
          .case eax & OP_M32: mov esi,T_EAX : .endc
        .endsw

        mov edi,T_EAX
        .if ModuleInfo.Ofssize == USE64
            mov edi,T_RAX
        .elseif ModuleInfo.Ofssize == USE16
            mov edi,T_AX
        .endif

        mov ebx,tokenarray
        mov eax,[ebx].tokval
        mov op,eax
        add ebx,16

        .for ( edx = ebx : [edx].asmtok.token != T_FINAL : edx += 16 )

            .break(1) .if ( [edx].asmtok.tokval == edi )

            .if ( [edx].asmtok.token == T_COMMA )

                mov edx,[edx].asmtok.tokpos
                push edx
                AddLineQueueX( " mov %r%s", esi, edx )
                pop edx
                .break
            .endif
        .endf

        xchg ebx,edx
        mov al,[ebx]
        push eax
        mov byte ptr [ebx],0
        AddLineQueueX( " %r %s,%r", op, [edx].asmtok.tokpos, esi )
        pop eax
        mov [ebx],al

        .if ModuleInfo.list
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
        RunLineQueue()
        .return NOT_ERROR

    .until 1
    asmerr(2070)
    ret

mem2mem endp

    end
