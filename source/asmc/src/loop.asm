; LOOP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description:  Implements FOR/IRP, FORC/IRPC, REPEAT/REPT, WHILE
;

include malloc.inc

include asmc.inc
include memalloc.inc
include parser.inc
include input.inc
include equate.inc
include expreval.inc
include tokenize.inc
include macro.inc
include listing.inc
include reswords.inc

    .code

    assume rbx:ptr asm_tok
    B equ <byte ptr>

LoopDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local directive:int_t
  local arg_loc:int_t
  local parmstring:string_t
  local is_exitm:int_t
  local opnd:expr
  local macinfo:macro_info
  local tmpmacro:dsym
  local buffer[4]:char_t

    inc i ; skip directive
    imul ebx,i,asm_tok
    add rbx,tokenarray

    .if ( ModuleInfo.list == TRUE )
        LstWriteSrcLine()
    .endif

    mov directive,[rbx-asm_tok].tokval

    .switch eax
    .case T_WHILE
        mov arg_loc,i

        ; no break

    .case T_REPT
    .case T_REPEAT

        ; the expression is "critical", that is, no forward
        ; referenced symbols may be used here!

        EvalOperand( &i, tokenarray, TokenCount, &opnd, EXPF_NOUNDEF )

        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( eax == ERROR )

            mov opnd.value,0
            mov i,TokenCount
            imul ebx,i,asm_tok
            add rbx,tokenarray

        .elseif ( opnd.kind != EXPR_CONST ) ; syntax <REPEAT|WHILE 'A'> is valid!

            asmerr( 2026 )
            mov opnd.value,0

        .elseif ( [rbx].token != T_FINAL )

            asmerr( 2008, [rbx].tokpos )
            mov opnd.value,0
        .endif
        .endc

    .default

        ; FOR, FORC, IRP, IRPC
        ; get the formal parameter and the argument list
        ; the format parameter will become a macro parameter, so it can
        ; be a simple T_ID, but also an instruction or something else.
        ; v2.02: And it can begin with a '.'!

        .if ( [rbx].token == T_FINAL )
            .return( asmerr( 2008, [rbx-asm_tok].tokpos ) )
        .endif

        ; v2.02: allow parameter name to begin with a '.'

        mov rcx,[rbx].string_ptr
        .if ( !isdotlabel( [rcx], ModuleInfo.dotname ) )
            .return( asmerr( 2008, [rbx].tokpos ) )
        .endif

        mov arg_loc,i
        inc i
        add rbx,asm_tok

        .if ( directive == T_FORC || directive == T_IRPC )

            .if( [rbx].token != T_COMMA )

                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif

            inc i
            add rbx,asm_tok

            ; FORC/IRPC accepts anything as "argument list", even nothing!

            .if ( [rbx].token == T_STRING && [rbx].string_delim == '<' )

                mov rdi,[rbx+asm_tok].tokpos
                mov rsi,[rbx].tokpos
                sub rdi,rsi
                dec rdi
                mov parmstring,alloca( edi )
                mov rcx,rdi
                mov rdi,rax
                inc rsi
                rep movsb
                dec rdi

                .while ( B[rdi] != '>' )
                    dec rdi
                .endw
                mov B[rdi],NULLC

                ; v2.02: if there's additional stuff behind the <> literal,
                ; it's an error!

                .if ( [rbx+asm_tok].token != T_FINAL )

                    asmerr( 2008, [rbx+asm_tok].tokpos )
                .endif
            .else

                mov rdi,[rbx].tokpos
                mov rsi,rdi

                ; this is what Masm does: use the string until a space
                ; is detected. Anything beyond the space is ignored.

                .while ( B[rdi] && !( islspace( [rdi] ) ) )
                    inc rdi
                .endw

                sub rdi,rsi
                lea ecx,[rdi+1]
                mov parmstring,alloca( ecx )
                mov rcx,rdi
                mov rdi,rax
                rep movsb
                mov B[rdi],NULLC
            .endif

        .else

            ; for FOR/IRP, skip everything between the name and the comma!
            ; these items will be stored as (first) macro parameter.
            ; for example, valid syntax is:
            ; FOR xxx,<a, ...>
            ; FOR xxx:REQ,<a, ...>

            .while ( [rbx].token != T_FINAL && [rbx].token != T_COMMA )
                inc i
                add rbx,asm_tok
            .endw

            .if ( [rbx].token != T_COMMA )
                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif

            inc i
            add rbx,asm_tok

            ; FOR/IRP accepts a literal enclosed in <> only

            .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
                .return( asmerr( 2008, [rbx].tokpos ) )
            .endif

            ; v2.03: also ensure that the literal is the last item

            .if ( [rbx+asm_tok].token != T_FINAL )
                .return( asmerr( 2008, [rbx+asm_tok].tokpos ) )
            .endif

            ; v2.08: use myalloca() instead of a fixed-length buffer.
            ; the loop directives are often nested, they call RunMacro()
            ; and hence should be careful with stack usage because of JWASMR!

            mov parmstring,[rbx].string_ptr
        .endif

        ; to run StoreMacro(), tokenarray must be setup correctly.
        ; clear contents beginning with the comma!

        dec i
        sub rbx,asm_tok
        mov [rbx].token,T_FINAL
        mov TokenCount,i
        mov i,arg_loc
    .endsw

    ; now make a temporary macro

    lea rdi,tmpmacro
    xor eax,eax
    mov ecx,sizeof(tmpmacro)
    rep stosb
    lea rdi,macinfo
    mov ecx,sizeof(macinfo)
    rep stosb

    mov tmpmacro.name,&@CStr("")
    mov tmpmacro.macroinfo,&macinfo
    mov macinfo.srcfile,get_curr_srcfile()
    lea rdi,tmpmacro

    .ifd ( StoreMacro( rdi, i, tokenarray, TRUE ) == ERROR )

        ReleaseMacroData( rdi )
       .return( ERROR )
    .endif

    ; EXITM <> is allowed inside a macro loop.
    ; This doesn't make the loop a macro function, reset the bit!

    and [rdi].asym.mac_flag,not M_ISFUNC

    ; now run the just created macro in a loop

    ; don't run the macro if there are no lines (macroinfo->data == NULL)!
    ; this isn't exactly what Masm does; an empty 'WHILE 1'
    ; will loop "forever" in Masm,

    mov rbx,tokenarray

    .if ( macinfo.lines ) ; added in v2.01

        .switch ( directive )
        .case T_REPEAT
        .case T_REPT

            ; negative repeat counts are accepted and are treated like 0

            .for ( : [rdi].asym.value < opnd.value : [rdi].asym.value++ )

                ; v2.10: TokenCount becomes volatile if MF_NOSAVE is set

                mov [rbx].token,T_FINAL
                mov TokenCount,0
                RunMacro( rdi, 0, rbx, NULL, MF_NOSAVE, &is_exitm )
               .endc .if ( is_exitm )
            .endf
            .endc

        .case T_WHILE

            .while ( opnd.kind == EXPR_CONST && opnd.value != 0 )

                RunMacro( rdi, TokenCount, rbx, NULL, 0, &is_exitm )
               .endc .if ( is_exitm )

                mov i,arg_loc

               .endc .ifd ( EvalOperand( &i, rbx, TokenCount, &opnd, 0 ) == ERROR )
                inc [rdi].asym.value
            .endw
            .endc

        .case T_FORC
        .case T_IRPC

            .for( rsi = parmstring: B[rsi] : rsi++, [rdi].asym.value++ )

                mov [rbx].token,T_STRING
                mov [rbx].string_delim,NULLC
                mov [rbx].string_ptr,&buffer
                mov [rbx].tokpos,rax;&buffer
                mov [rbx+asm_tok].token,T_FINAL
                mov buffer[2],NULLC
                mov TokenCount,1

                .if ( B[rsi] == '!' )

                    lodsb
                    mov buffer[0],al
                    mov al,[rsi]
                    mov buffer[1],al
                    .if ( B[rsi] == NULLC ) ; ensure the macro won't go beyond the 00
                        dec rsi
                    .endif
                    mov [rbx].stringlen,2
                    mov [rbx+asm_tok].tokpos,&buffer[2]

                .elseif ( islspace( B[rsi] ) )

                    mov buffer[0],'!'
                    mov buffer[1],B[rsi]
                    mov [rbx].stringlen,2
                    mov [rbx+asm_tok].tokpos,&buffer[2]

                .else

                    mov buffer[0],B[rsi]
                    mov [rbx].stringlen,1
                    mov [rbx+asm_tok].tokpos,&buffer[1]
                    mov buffer[1],NULLC
                .endif
                RunMacro( rdi, 0, rbx, NULL, MF_NOSAVE, &is_exitm )
                .endc .if ( is_exitm )
            .endf
            .endc

        .default ; T_FOR, T_IRP

            mov esi,TokenCount
            inc esi
            mov TokenCount,Tokenize( parmstring, esi, tokenarray, TOK_RESCAN or TOK_NOCURLBRACES )

            imul ebx,eax,asm_tok
            add rbx,tokenarray

            ; v2.09: if a trailing comma is followed by white space(s), add a blank token

            mov rdx,[rbx-asm_tok].tokpos
            .if ( esi != TokenCount && [rbx-asm_tok].token == T_COMMA && ( B[rdx+1] ) )

                mov [rbx].token,T_STRING
                mov [rbx].string_delim,NULLC
                mov [rbx].stringlen,tstrlen( [rbx].tokpos )
                mov ecx,[rbx].stringlen
                add rcx,[rbx].tokpos
                add rbx,asm_tok
                mov [rbx].tokpos,rcx
                inc TokenCount
                mov [rbx].token,T_FINAL
            .endif

            ; a FOR/IRP parameter can be a macro function call
            ; that's why the macro calls must be run synchronously
            ; v2.05: reset an optional VARARG attribute for the macro
            ; parameter.
            ; take care of a trailing comma, this is to make another
            ; RunMacro() call with a "blank" argument.

            and [rdi].asym.mac_flag,not M_ISVARARG

            ; v2.09: flag MF_IGNARGS introduced. This allows RunMacro() to
            ; parse the full argument and trigger macro expansion if necessary.
            ; No need anymore to count commas here.

            .for ( : esi < TokenCount : esi++, [rdi].asym.value++ )
                mov esi,RunMacro( rdi, esi, tokenarray, NULL, MF_IGNARGS, &is_exitm )
                .break .ifs ( esi < 0 || is_exitm )
            .endf
        .endsw
    .endif

    ReleaseMacroData( rdi )
   .return( NOT_ERROR )

LoopDirective endp

    end
