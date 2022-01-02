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

    assume ebx:ptr asm_tok
    B equ <byte ptr>

LoopDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local directive:int_t
  local arg_loc:int_t
  local parmstring:string_t
  local is_exitm:int_t
  local opnd:expr
  local macinfo:macro_info
  local tmpmacro:dsym
  local buffer[4]:char_t

    inc i ;; skip directive
    imul ebx,i,asm_tok
    add ebx,tokenarray

    .if ( ModuleInfo.list == TRUE )
        LstWriteSrcLine()
    .endif

    mov directive,[ebx-16].tokval
    .switch eax
    .case T_WHILE
        mov arg_loc,i
        ;; no break
    .case T_REPT
    .case T_REPEAT
        ;; the expression is "critical", that is, no forward
        ;; referenced symbols may be used here!
        EvalOperand( &i, tokenarray, Token_Count, &opnd, EXPF_NOUNDEF )
        imul ebx,i,asm_tok
        add ebx,tokenarray

        .if ( eax == ERROR )
            mov opnd.value,0
            mov i,Token_Count
            imul ebx,i,asm_tok
            add ebx,tokenarray
        .elseif ( opnd.kind != EXPR_CONST ) ;; syntax <REPEAT|WHILE 'A'> is valid!
            asmerr( 2026 )
            mov opnd.value,0
        .elseif ( [ebx].token != T_FINAL )
            asmerr( 2008, [ebx].tokpos )
            mov opnd.value,0
        .endif
        .endc
    .default
        ;; FOR, FORC, IRP, IRPC
        ;; get the formal parameter and the argument list
        ;; the format parameter will become a macro parameter, so it can
        ;; be a simple T_ID, but also an instruction or something else.
        ;; v2.02: And it can begin with a '.'!

        .if ( [ebx].token == T_FINAL )
            .return( asmerr( 2008, [ebx-16].tokpos ) )
        .endif
        ;; v2.02: allow parameter name to begin with a '.'
        mov ecx,[ebx].string_ptr
        .if ( !is_valid_id_first_char( [ecx] ) )
            .return( asmerr( 2008, [ebx].tokpos ) )
        .endif
        mov arg_loc,i
        inc i
        add ebx,asm_tok
        .if ( directive == T_FORC || directive == T_IRPC )
            .if( [ebx].token != T_COMMA )
                .return( asmerr( 2008, [ebx].tokpos ) )
            .endif
            inc i
            add ebx,asm_tok

            ;; FORC/IRPC accepts anything as "argument list", even nothing!

            .if ( [ebx].token == T_STRING && [ebx].string_delim == '<' )

                mov edi,[ebx+16].tokpos
                mov esi,[ebx].tokpos
                sub edi,esi
                dec edi
                mov parmstring,alloca( edi )
                mov ecx,edi
                mov edi,eax
                inc esi
                rep movsb
                dec edi
                .while ( B[edi] != '>' )
                    dec edi
                .endw
                mov B[edi],NULLC

                ;; v2.02: if there's additional stuff behind the <> literal,
                ;; it's an error!

                .if ( [ebx+16].token != T_FINAL )
                    asmerr(2008, [ebx+16].tokpos )
                .endif
            .else

                mov edi,[ebx].tokpos
                mov esi,edi
                ;; this is what Masm does: use the string until a space
                ;; is detected. Anything beyond the space is ignored.

                .while ( B[edi] && !( islspace( [edi] ) ) )
                    inc edi
                .endw
                sub edi,esi
                mov parmstring,alloca( &[edi+1] )
                mov ecx,edi
                mov edi,eax
                rep movsb
                mov B[edi],NULLC
            .endif

        .else

            ;; for FOR/IRP, skip everything between the name and the comma!
            ;; these items will be stored as (first) macro parameter.
            ;; for example, valid syntax is:
            ;; FOR xxx,<a, ...>
            ;; FOR xxx:REQ,<a, ...>

            .while ( [ebx].token != T_FINAL && [ebx].token != T_COMMA )
                inc i
                add ebx,asm_tok
            .endw
            .if ( [ebx].token != T_COMMA )
                .return( asmerr( 2008, [ebx].tokpos ) )
            .endif
            inc i
            add ebx,asm_tok
            ;; FOR/IRP accepts a literal enclosed in <> only
            .if ( [ebx].token != T_STRING || [ebx].string_delim != '<' )
                .return( asmerr( 2008, [ebx].tokpos ) )
            .endif
            ;; v2.03: also ensure that the literal is the last item
            .if ( [ebx+16].token != T_FINAL )
                .return( asmerr( 2008, [ebx+16].tokpos ) )
            .endif
            ;; v2.08: use myalloca() instead of a fixed-length buffer.
            ;; the loop directives are often nested, they call RunMacro()
            ;; and hence should be careful with stack usage because of JWASMR!

            mov parmstring,[ebx].string_ptr
        .endif
        ;; to run StoreMacro(), tokenarray must be setup correctly.
        ;; clear contents beginning with the comma!
        dec i
        sub ebx,asm_tok
        mov [ebx].token,T_FINAL
        mov Token_Count,i
        mov i,arg_loc
    .endsw

    ;; now make a temporary macro
    lea edi,tmpmacro
    xor eax,eax
    mov ecx,sizeof(tmpmacro)
    rep stosb
    lea edi,macinfo
    mov ecx,sizeof(macinfo)
    rep stosb

    mov tmpmacro.name,&@CStr("")
    mov tmpmacro.macroinfo,&macinfo
    mov macinfo.srcfile,get_curr_srcfile()
    lea edi,tmpmacro

    .if ( StoreMacro( edi, i, tokenarray, TRUE ) == ERROR )
        ReleaseMacroData( edi )
        .return( ERROR )
    .endif
    ;; EXITM <> is allowed inside a macro loop.
    ;; This doesn't make the loop a macro function, reset the bit!

    and [edi].asym.mac_flag,not M_ISFUNC

    ;; now run the just created macro in a loop

    ;; don't run the macro if there are no lines (macroinfo->data == NULL)!
    ;; this isn't exactly what Masm does; an empty 'WHILE 1'
    ;; will loop "forever" in Masm,

    mov ebx,tokenarray

    .if ( macinfo.lines ) ;; added in v2.01
    .switch ( directive )
    .case T_REPEAT
    .case T_REPT
        ;; negative repeat counts are accepted and are treated like 0
        .for ( : [edi].asym.value < opnd.value : [edi].asym.value++ )
            ;; v2.10: Token_Count becomes volatile if MF_NOSAVE is set
            mov [ebx].token,T_FINAL
            mov Token_Count,0
            RunMacro( edi, 0, ebx, NULL, MF_NOSAVE, &is_exitm )
            .endc .if ( is_exitm )
        .endf
        .endc
    .case T_WHILE
        .while ( opnd.kind == EXPR_CONST && opnd.value != 0 )
            RunMacro( edi, Token_Count, ebx, NULL, 0, &is_exitm )
            .endc .if ( is_exitm )
            mov i,arg_loc
            .endc .if ( EvalOperand( &i, ebx, Token_Count, &opnd, 0 ) == ERROR )
            inc [edi].asym.value
        .endw
        .endc
    .case T_FORC
    .case T_IRPC
        .for( esi = parmstring: B[esi] : esi++, [edi].asym.value++ )
            mov [ebx].token,T_STRING
            mov [ebx].string_delim,NULLC
            mov [ebx].string_ptr,&buffer
            mov [ebx].tokpos,eax;&buffer
            mov [ebx+16].token,T_FINAL
            mov buffer[2],NULLC
            mov Token_Count,1
            .if ( B[esi] == '!' )
                lodsb
                mov buffer[0],al
                mov al,[esi]
                mov buffer[1],al
                .if ( B[esi] == NULLC ) ;; ensure the macro won't go beyond the 00
                    dec esi
                .endif
                mov [ebx].stringlen,2
                mov [ebx+16].tokpos,&buffer[2]
            .elseif ( islspace( B[esi] ) )
                mov buffer[0],'!'
                mov buffer[1],B[esi]
                mov [ebx].stringlen,2
                mov [ebx+16].tokpos,&buffer[2]
            .else
                mov buffer[0],B[esi]
                mov [ebx].stringlen,1
                mov [ebx+16].tokpos,&buffer[1]
                mov buffer[1],NULLC
            .endif
            RunMacro( edi, 0, ebx, NULL, MF_NOSAVE, &is_exitm )
            .endc .if ( is_exitm )
        .endf
        .endc
    .default ;; T_FOR, T_IRP
        mov esi,Token_Count
        inc esi
        mov Token_Count,Tokenize( parmstring, esi, tokenarray, TOK_RESCAN or TOK_NOCURLBRACES )

        imul ebx,eax,16
        add ebx,tokenarray

        ;; v2.09: if a trailing comma is followed by white space(s), add a blank token

        mov edx,[ebx-16].tokpos
        .if ( esi != Token_Count && [ebx-16].token == T_COMMA && ( B[edx+1] ) )
            mov [ebx].token,T_STRING
            mov [ebx].string_delim,NULLC
            mov [ebx].stringlen,strlen( [ebx].tokpos )
            mov ecx,[ebx].tokpos
            add ecx,[ebx].stringlen
            add ebx,16
            mov [ebx].tokpos,ecx
            inc Token_Count
            mov [ebx].token,T_FINAL
        .endif

        ;; a FOR/IRP parameter can be a macro function call
        ;; that's why the macro calls must be run synchronously
        ;; v2.05: reset an optional VARARG attribute for the macro
        ;; parameter.
        ;; take care of a trailing comma, this is to make another
        ;; RunMacro() call with a "blank" argument.

        and [edi].asym.mac_flag,not M_ISVARARG
        ;; v2.09: flag MF_IGNARGS introduced. This allows RunMacro() to
         ;; parse the full argument and trigger macro expansion if necessary.
         ;; No need anymore to count commas here.
        .for ( : esi < Token_Count : esi++, [edi].asym.value++ )
            mov esi,RunMacro( edi, esi, tokenarray, NULL, MF_IGNARGS, &is_exitm )
            .break .ifs ( esi < 0 || is_exitm )
        .endf
    .endsw
    .endif
    ReleaseMacroData( edi )
    .return( NOT_ERROR )
LoopDirective endp

    end
