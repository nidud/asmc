; PREPROC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include stdlib.inc
include string.inc

include asmc.inc
include parser.inc
include listing.inc
include tokenize.inc
include fastpass.inc
include equate.inc
include condasm.inc
include macro.inc

REMOVECOMENT    equ 0 ; 1=remove comments from source
TF3_ISCONCAT    equ 1 ; line was concatenated
TF3_EXPANSION   equ 2 ; expansion operator % at pos 0

CCALLBACK(fpDirective, :int_t, :token_t)

externdef directive_tab: fpDirective

    .code

    assume rbx:token_t

; preprocessor directive or macro procedure is preceded
; by a code label.

WriteCodeLabel proc uses rsi rdi rbx r12 r13 line:string_t, tokenarray:token_t

    mov rbx,tokenarray
    .return asmerr(2008, [rbx].string_ptr) .if ( [rbx].token != T_ID )

    ;
    ; ensure the listing is written with the FULL source line
    ;
    .if ModuleInfo.curr_file[LST*8]

        LstWrite(LSTTYPE_LABEL, 0, 0)
    .endif
    ;
    ; v2.04: call ParseLine() to parse the "label" part of the line
    ;
    movzx esi,[rbx+2*asm_tok].asm_tok.token
    mov [rbx+2*asm_tok].asm_tok.token,T_FINAL
    mov rdi,[rbx+2*asm_tok].asm_tok.tokpos
    mov r13b,[rdi]
    mov byte ptr [rdi],0
    mov r12d,ModuleInfo.token_count
    mov ModuleInfo.token_count,2
    ParseLine(rbx)
    .if ( Options.preprocessor_stdout )
        WritePreprocessedLine(line)
    .endif
    mov [rdi],r13b
    mov ModuleInfo.token_count,r12d
    mov [rbx+2*asm_tok].asm_tok.token,sil
    mov eax,NOT_ERROR
    ret

WriteCodeLabel endp


    assume rcx:token_t

DelayExpand proc fastcall uses rbx tokenarray:token_t

    xor eax,eax
    .if ( !( [rcx].hll_flags & T_HLL_DELAY ) ||
           al != ModuleInfo.strict_masm_compat ||
          eax != Parse_Pass ||
          eax != NoLineStore )
        .return
    .endif

    .repeat

        .repeat
            .ifs ( eax >= ModuleInfo.token_count )
                or [rcx].hll_flags,T_HLL_DELAYED
                .return 1
            .endif
            lea rdx,[rax*8]
            test [rcx+rdx*2].hll_flags,T_HLL_MACRO
            lea rax,[rax+1]
            .continue(0) .ifz
        .until ( [rcx+rdx*2].token == T_OP_BRACKET )

        mov edx,1   ; one open bracket found
        .while 1

            .ifs ( eax >= ModuleInfo.token_count )
                or [rcx].hll_flags,T_HLL_DELAYED
                .return 1
            .endif

            imul ebx,eax,asm_tok
            .switch [rcx+rbx].token
              .case T_OP_BRACKET
                inc edx
                .endc
              .case T_CL_BRACKET
                dec edx
                .endc .ifnz
                inc eax
                .continue(01)
              .case T_STRING
                mov r8,[rcx+rbx].string_ptr
                .if ( byte ptr [r8] != '<' )
                    mov r8,[rcx+rbx].tokpos
                    .if ( byte ptr [r8] == '<' )
                        asmerr(7008, r8)
                       .break
                    .endif
                .endif
            .endsw
            inc eax
        .endw
    .until 1
    xor eax,eax
    ret

DelayExpand endp

    assume rcx:nothing


; PreprocessLine() is the "preprocessor".
; 1. the line is tokenized with Tokenize(), Token_Count set
; 2. (text) macros are expanded by ExpandLine()
; 3. "preprocessor" directives are executed

PreprocessLine proc uses rsi rbx tokenarray:token_t

    ;
    ; v2.11: GetTextLine() removed - this is now done in ProcessFile()
    ; v2.08: moved here from GetTextLine()
    ;
    mov ModuleInfo.CurrComment,NULL
    ;
    ; v2.06: moved here from Tokenize()
    ;
    mov ModuleInfo.line_flags,0
    ;
    ; Token_Count is the number of tokens scanned
    ;
    mov Token_Count,Tokenize( ModuleInfo.currsource, 0, tokenarray, TOK_DEFAULT )
    mov rbx,ModuleInfo.tokenarray

if REMOVECOMENT eq 0
    .if ( ( Token_Count == 0 ) && ( CurrIfState == BLOCK_ACTIVE || ModuleInfo.listif ) )

        LstWriteSrcLine()
    .endif
endif

    mov eax,ModuleInfo.token_count
    .return .if ( eax == 0 )
    ;
    ; CurrIfState != BLOCK_ACTIVE && Token_Count == 1 | 3 may happen
    ; if a conditional assembly directive has been detected by Tokenize().
    ; However, it's important NOT to expand then
    ;
    .if ( CurrIfState == BLOCK_ACTIVE )

        imul eax,eax,asm_tok
        .if ( [rbx+rax].bytval & TF3_EXPANSION )

            mov esi,ExpandText(CurrSource, rbx, 1)

        .else

            xor esi,esi

            .if ( DelayExpand( rbx ) == 0 )

                mov esi,ExpandLine( CurrSource, rbx )

            .elseif ( Parse_Pass == PASS_1 )

                ExpandLineItems( CurrSource, 0, rbx, 0, 1 )
            .endif
        .endif
        .return 0 .ifs ( esi < NOT_ERROR )
    .endif

    mov rbx,ModuleInfo.tokenarray
    xor esi,esi
    .if ( ModuleInfo.token_count > 2 && \
        ( [rbx+asm_tok].asm_tok.token == T_COLON || [rbx+asm_tok].asm_tok.token == T_DBL_COLON ) )

        mov esi,2*asm_tok
    .endif

    ;
    ; handle "preprocessor" directives:
    ; IF, ELSE, ENDIF, ...
    ; FOR, REPEAT, WHILE, ...
    ; PURGE
    ; INCLUDE
    ; since v2.05, error directives are no longer handled here!
    ;
    .if ( [rbx+rsi].token == T_DIRECTIVE && [rbx+rsi].dirtype <= DRT_INCLUDE )

        ;
        ; if i != 0, then a code label is located before the directive
        ;
        .if ( esi > asm_tok )
            .return 0 .ifd WriteCodeLabel( CurrSource, rbx ) == ERROR
        .endif
        movzx r8d,[rbx+rsi].dirtype
        xor edx,edx
        mov ecx,asm_tok
        mov eax,esi
        div ecx
        mov esi,eax
        lea rcx,directive_tab
        mov rax,[rcx+r8*8]
        assume rax:fpDirective
        rax(esi, rbx)
        assume rax:nothing
       .return 0
    .endif

    ;
    ; handle preprocessor directives which need a label
    ;
    mov rbx,ModuleInfo.tokenarray
    xor eax,eax
    .if ( [rbx].token == T_ID && [rbx+asm_tok].token == T_DIRECTIVE )
        movzx eax,[rbx+asm_tok].dirtype
    .elseif ( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_DEFINE &&
              [rbx+asm_tok].token == T_ID )
        movzx eax,[rbx].dirtype
    .endif

    .if ( eax )

        .switch eax
          .case DRT_EQU
            ;
            ; EQU is a special case:
            ; If an EQU directive defines a text equate
            ; it MUST be handled HERE and 0 must be returned to the caller.
            ; This will prevent further processing, nothing will be stored
            ; if FASTPASS is on.
            ; Since one cannot decide whether EQU defines a text equate or
            ; a number before it has scanned its argument, we'll have to
            ; handle it in ANY case and if it defines a number, the line
            ; must be stored and, if -EP is set, written to stdout.
            ;
            .if CreateConstant( rbx )
                mov rsi,rax
                .if [rax].asym.state != SYM_TMACRO
                    .if StoreState && Parse_Pass == PASS_1
                        StoreLine( ModuleInfo.currsource, 0, 0 )
                    .endif
                    .if Options.preprocessor_stdout
                        WritePreprocessedLine( CurrSource )
                    .endif
                .endif
                ;
                ; v2.03: LstWrite() must be called AFTER StoreLine()!
                ;
                .if ModuleInfo.list
                    mov eax,LSTTYPE_TMACRO
                    .if [rsi].asym.state == SYM_INTERNAL
                        mov eax,LSTTYPE_EQUATE
                    .endif
                    LstWrite( eax, 0, rsi )
                .endif
            .endif
            .return 0
          .case DRT_MACRO
          .case DRT_CATSTR ; CATSTR + TEXTEQU directives
          .case DRT_SUBSTR
            movzx eax,[rbx+asm_tok].dirtype
            lea rcx,directive_tab
            mov rax,[rcx+rax*8]
            assume rax:fpDirective
            rax(1, rbx)
            assume rax:nothing
           .return 0
        .endsw
    .endif
    mov eax,ModuleInfo.token_count
    ret

PreprocessLine endp

    end
