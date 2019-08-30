; MEM2MEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include parser.inc
include hll.inc
include operands.inc
include listing.inc
include lqueue.inc
include segment.inc

    .code

    assume ebx:tok_t

mem2mem proc uses esi edi ebx op1:dword, op2:dword, tokenarray:tok_t

  local op:int_t

    mov eax,op1
    mov edx,op2
    and eax,OP_MS
    and edx,OP_MS

    .repeat

        .break .if ( !eax || !edx )
        .break .if ( ModuleInfo.strict_masm_compat == 1 )

        mov esi,T_RAX
        mov edi,T_RAX
        .switch
          .case eax & OP_M08: mov edi,T_AL  : .endc
          .case eax & OP_M16: mov edi,T_AX  : .endc
          .case eax & OP_M32: mov edi,T_EAX : .endc
        .endsw
        .switch
          .case edx & OP_M08: mov esi,T_AL  : .endc
          .case edx & OP_M16: mov esi,T_AX  : .endc
          .case edx & OP_M32: mov esi,T_EAX : .endc
        .endsw
        mov ecx,T_EAX
        .if ModuleInfo.Ofssize == USE64
            mov ecx,T_RAX
        .elseif ModuleInfo.Ofssize == USE16
            mov ecx,T_AX
        .endif

        mov ebx,tokenarray
        mov eax,[ebx].tokval
        mov op,eax
        add ebx,16

        .for ( edx = ebx : [edx].asm_tok.token != T_FINAL : edx += 16 )

            .break(1) .if ( [edx].asm_tok.tokval == ecx )

            .if ( [edx].asm_tok.token == T_COMMA )

                mov edx,[edx].asm_tok.tokpos
                push edx
                mov ecx,T_MOV
                .if edi > esi
                    .if esi < T_EAX
                        mov ecx,T_MOVZX
                        mov esi,T_EAX
                    .endif
                .endif
                AddLineQueueX( " %r %r%s", ecx, esi, edx )
                pop edx
                .break
            .endif
        .endf

        xchg ebx,edx
        mov al,[ebx]
        push eax
        mov byte ptr [ebx],0
        AddLineQueueX( " %r %s,%r", op, [edx].asm_tok.tokpos, edi )
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
