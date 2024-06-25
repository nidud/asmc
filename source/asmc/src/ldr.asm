; LDR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include string.inc
include asmc.inc
include proc.inc
include hllext.inc
include expreval.inc
include qfloat.inc
include fastpass.inc

    .code

    assume rbx:token_t

LoadRegister proc __ccall private uses rbx i:int_t, tokenarray:token_t

   .new reg:int_t
   .new string:string_t = NULL
   .new tokpos:string_t

    inc     i
    imul    ebx,i,asm_tok
    add     rbx,tokenarray
    mov     tokpos,[rbx].tokpos
    mov     rax,CurrProc
    movzx   ecx,[rax].asym.langtype

    .ifd ( GetFastcallId(ecx) == 0 )
        jmp move_param
    .endif

    mov reg,[rbx].tokval
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

            AddLineQueueX( " mov %s, %r", string, ecx )
           .return( NOT_ERROR )

        .elseif ( ecx == reg )

            .return( NOT_ERROR )
        .endif
        jmp move_param
    .endif

    .if ( SymSearch( [rbx].string_ptr ) == NULL )

        .return asmerr( 2008, [rbx].string_ptr )

    .elseif ( [rax].asym.flags & S_REGPARAM )

        movzx ecx,[rax].asym.param_reg
        .if ( reg == 0 )
            AddLineQueueX( " mov %s, %r", string, ecx )
        .elseif ( ecx != reg )
            AddLineQueueX( " mov %r, %r", reg, ecx )
        .endif
       .return( NOT_ERROR )
    .endif

move_param:

    AddLineQueueX( " mov %s", tokpos )
    xor eax,eax
    ret

LoadRegister endp


LdrDirective proc __ccall i:int_t, tokenarray:token_t

  local rc:int_t

    .if ( CurrProc == NULL )
        .return asmerr( 2012 )
    .endif

    mov rc,LoadRegister( i, tokenarray )

    .if ModuleInfo.list
        LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), 0)
    .endif
    .if ( ModuleInfo.line_queue.head )
        RunLineQueue()
    .endif
    .return( rc )

LdrDirective endp

    end
