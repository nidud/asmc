; LDR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc

include asmc.inc
include proc.inc
include segment.inc
include hll.inc
include lqueue.inc
include listing.inc
include expreval.inc
include qfloat.inc
include fastpass.inc
include parser.inc

    .code

    assume rbx:token_t

LoadRegister proc __ccall private uses rbx i:int_t, tokenarray:token_t

   .new reg:int_t
   .new inst:int_t = T_MOV
   .new string:string_t = NULL
   .new tokpos:string_t
   .new fc:byte

    inc i
    imul ebx,i,asm_tok
    add rbx,tokenarray
    mov tokpos,[rbx].tokpos
    mov reg,[rbx].tokval
    mov rcx,CurrProc
    mov al,[get_fasttype([rcx].asym.segoffsize, [rcx].asym.langtype)].fc_info.flags
    and al,_P_FASTCALL
    mov fc,al

    .if ( [rbx].token != T_REG )
        .if ( [rbx].token != T_ID || [rbx+asm_tok].token != T_COMMA )
            jmp move_param
        .endif
        mov string,[rbx].string_ptr
        mov reg,0
    .endif

    .for ( : [rbx].token != T_COMMA && [rbx].token != T_FINAL : rbx+=asm_tok )
    .endf
    .if ( [rbx].token != T_COMMA )
        .return asmerr( 2008, [rbx].string_ptr )
    .endif
    add rbx,asm_tok

    .if ( [rbx].token == T_REG )

        mov ecx,[rbx].tokval
        .if ( reg == 0 )

            AddLineQueueX( " %r %s, %r", T_MOV, string, ecx )
           .return( NOT_ERROR )
        .elseif ( ecx == reg )
            .return( NOT_ERROR )
        .elseif ( ecx == T_ES && [rbx+asm_tok].token == T_COLON )
            mov inst,T_LES
        .endif
        jmp move_param
    .elseif ( MODULE.Ofssize == USE16 && [rbx].token == T_OP_SQ_BRACKET )
        jmp move_param
    .endif

    .if ( SymSearch( [rbx].string_ptr ) == NULL )

        .return asmerr( 2008, [rbx].string_ptr )

    .elseif ( fc && [rax].asym.regparam )

        movzx ecx,[rax].asym.param_reg
        .if ( reg == 0 )
            AddLineQueueX( " %r %s, %r", T_MOV, string, ecx )
        .elseif ( ecx != reg )
            mov ebx,T_MOV
            .if ( [rax].asym.mem_type & MT_FLOAT )
                ; v2.35.06
                .if ( [rax].asym.total_size <= 4 )
                    mov ebx,T_MOVSS
                .elseif ( [rax].asym.total_size == 8 )
                    mov ebx,T_MOVSD
                .elseif ( [rax].asym.total_size == 16 )
                    mov ebx,T_MOVAPS
                .else
                    mov ebx,T_VMOVAPS
                .endif
            .endif
            AddLineQueueX( " %r %r, %r", ebx, reg, ecx )
        .endif
        .return( NOT_ERROR )
    .endif

    ; v2.37.12: added for DOS near/far param -- assume ds:si and es:r16

    .if ( MODULE.Ofssize == USE16 && reg && [rax].asym.is_ptr )

        mov cl,MODULE._model
        .if ( [rax].asym.total_size == 4 || ( [rax].asym.state == SYM_EXTERNAL &&
              ( cl == MODEL_COMPACT || cl == MODEL_LARGE || cl == MODEL_HUGE ) ) )
            mov inst,T_LES
            .if ( reg == T_SI )
                mov inst,T_LDS
            .endif
        .endif
    .endif

move_param:

    AddLineQueueX( " %r %s", inst, tokpos )
    xor eax,eax
    ret

LoadRegister endp


LdrDirective proc __ccall i:int_t, tokenarray:token_t

  local rc:int_t

    .if ( CurrProc == NULL )
        .return asmerr( 2012 )
    .endif

    mov rc,LoadRegister( i, tokenarray )

    .if MODULE.list
        LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), 0)
    .endif
    .if ( MODULE.line_queue.head )
        RunLineQueue()
    .endif
    .return( rc )

LdrDirective endp

    end
