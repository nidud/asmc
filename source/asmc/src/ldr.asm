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

    option proc: private

MoveParam proc watcall string:string_t

    AddLineQueueX(" mov %s", rax)
   .return( NOT_ERROR )

MoveParam endp

    assume rbx:token_t

LoadSyscallArg proc uses rsi rdi rbx arg:token_t, reg:token_t

   .new buffer[512]:char_t

    mov rbx,arg
    .if ( [rbx].token == T_REG )

        mov eax,[rbx].tokval
        mov rbx,reg
        .if ( [rbx].token == T_REG && eax == [rbx].tokval )
            .return( NOT_ERROR )
        .endif
       .return( MoveParam( [rbx].tokpos ) )
    .endif

    .if ( SymSearch( [rbx].string_ptr ) == NULL )

        .return asmerr( 2008, [rbx].string_ptr )
    .endif

    .if ( !( [rax].asym.flags & S_REGPARAM ) )

        mov rbx,reg
       .return( MoveParam( [rbx].tokpos ) )
    .endif

    mov rcx,[rbx].tokpos
    mov rbx,reg
    .if ( [rbx].token == T_REG )

        movzx edx,[rax].asym.regist
        .if ( edx == [rbx].tokval )
           .return( NOT_ERROR )
        .endif
        AddLineQueueX( " mov %r,%r", [rbx].tokval, edx )
       .return( NOT_ERROR )
    .endif

    lea rdi,buffer
    mov rsi,[rbx].tokpos
    sub rcx,rsi
    rep movsb
    mov byte ptr [rdi],0
    movzx edx,[rax].asym.regist
    AddLineQueueX( " mov %s%r", &buffer, edx )
   .return( NOT_ERROR )

LoadSyscallArg endp


LoadFastcallArg proc uses rsi rdi rbx arg:token_t, reg:token_t

   .new buffer[512]:char_t

    mov rbx,arg
    .if ( SymSearch( [rbx].string_ptr ) == NULL )

        .return asmerr( 2008, [rbx].string_ptr )
    .endif

    .if ( !( [rax].asym.flags & S_REGPARAM ) )

        mov rbx,reg
       .return( MoveParam( [rbx].tokpos ) )
    .endif

    mov rcx,[rbx].tokpos
    mov rbx,reg
    .if ( [rbx].token == T_REG )

        movzx edx,[rax].asym.regist
        .if ( edx == [rbx].tokval )
           .return( NOT_ERROR )
        .endif
        AddLineQueueX( " mov %r,%r", [rbx].tokval, edx )
       .return( NOT_ERROR )
    .endif

    lea rdi,buffer
    mov rsi,[rbx].tokpos
    sub rcx,rsi
    rep movsb
    mov byte ptr [rdi],0
    movzx edx,[rax].asym.regist
    AddLineQueueX( " mov %s%r", &buffer, edx )
   .return( NOT_ERROR )

LoadFastcallArg endp


LoadWatcallArg proc uses rbx arg:token_t, reg:token_t

    mov rbx,arg
    .if ( [rbx].token == T_REG )

        mov eax,[rbx].tokval
        mov rbx,reg
        .if ( [rbx].token == T_REG && eax == [rbx].tokval )
            .return( NOT_ERROR )
        .endif
    .endif
    .return( MoveParam( [rbx].tokpos ) )

LoadWatcallArg endp


LoadRegister proc uses rbx i:int_t, tokenarray:token_t

    inc i
    imul ebx,i,asm_tok
    add rbx,tokenarray

    mov rdx,CurrProc
    mov cl,[rdx].asym.langtype
    .if ( ModuleInfo.Ofssize != USE64 ||
          ( cl != LANG_FASTCALL   &&
            cl != LANG_VECTORCALL &&
            cl != LANG_SYSCALL    &&
            cl != LANG_WATCALL ) )
        .return( MoveParam( [rbx].tokpos ) )
    .endif

    .for ( rdx = rbx : [rbx].token != T_COMMA : rbx+=asm_tok )
        .break .if ( [rbx].token == T_FINAL )
    .endf
    .if ( [rbx].token != T_COMMA )
        .return asmerr( 2008, [rbx].string_ptr )
    .endif
    add rbx,asm_tok

    .if ( cl == LANG_SYSCALL )
        .return( LoadSyscallArg( rbx, rdx ) )
    .elseif ( cl == LANG_WATCALL )
        .return( LoadWatcallArg( rbx, rdx ) )
    .endif
    .return( LoadFastcallArg( rbx, rdx ) )

LoadRegister endp


    option proc: public

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
