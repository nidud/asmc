; PREPROC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

include asmc.inc
include parser.inc
include listing.inc
include tokenize.inc
include fastpass.inc
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

WriteCodeLabel proc __ccall uses rsi rdi rbx line:string_t, tokenarray:token_t

    ldr rbx,tokenarray

    .if ( [rbx].token != T_ID )
        .return asmerr( 2008, [rbx].string_ptr )
    .endif

    ;
    ; ensure the listing is written with the FULL source line
    ;
    .if ( MODULE.curr_file[LST*size_t] )

        LstWrite(LSTTYPE_LABEL, 0, 0)
    .endif
    ;
    ; v2.04: call ParseLine() to parse the "label" part of the line
    ;
    mov cl,[rbx+2*asm_tok].asm_tok.token
    mov [rbx+2*asm_tok].asm_tok.token,T_FINAL
    mov rdi,[rbx+2*asm_tok].asm_tok.tokpos
    mov bl,[rdi]
    mov bh,cl
    mov byte ptr [rdi],0
    mov esi,TokenCount
    mov TokenCount,2

    ParseLine( tokenarray )
    .if ( Options.preprocessor_stdout )
        WritePreprocessedLine( line )
    .endif

    mov [rdi],bl
    mov TokenCount,esi
    mov [rbx+2*asm_tok].asm_tok.token,bh

   .return( NOT_ERROR )

WriteCodeLabel endp


    assume rcx:token_t

DelayExpand proc fastcall uses rsi rbx tokenarray:token_t

    xor eax,eax
    .if ( [rcx].HllCode == 0 || MODULE.masm_compat_gencode || eax != Parse_Pass || eax != NoLineStore )
        .return
    .endif

    .repeat

        .repeat
            .ifs ( eax >= TokenCount )
                mov [rcx].Delayed,1
               .return 1
            .endif
            imul edx,eax,asm_tok
            inc  eax
           .continue( 0 ) .if ( [rcx+rdx].IsFunc == 0 )
        .until ( [rcx+rdx].token == T_OP_BRACKET )

        mov edx,1 ; one open bracket found
        .while 1

            .ifs ( eax >= TokenCount )
                mov [rcx].Delayed,1
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
                mov rsi,[rcx+rbx].string_ptr
                .if ( byte ptr [rsi] != '<' )

                    mov rsi,[rcx+rbx].tokpos
                    .if ( byte ptr [rsi] == '<' )

                        asmerr( 7008, rsi ) ; cannot delay macro function
                       .break
                    .endif
                .endif
            .endsw
            inc eax
        .endw
    .until 1
    .return( 0 )

DelayExpand endp

    assume rcx:nothing

; PreprocessLine() is the "preprocessor".
; 1. the line is tokenized with Tokenize(), TokenCount set
; 2. (text) macros are expanded by ExpandLine()
; 3. "preprocessor" directives are executed

PreprocessLine proc __ccall uses rsi rbx tokenarray:token_t

    ;
    ; v2.11: GetTextLine() removed - this is now done in ProcessFile()
    ; v2.08: moved here from GetTextLine()
    ;
    mov CurrComment,NULL
    ;
    ; v2.06: moved here from Tokenize()
    ;
    mov MODULE.line_flags,0
    ;
    ; TokenCount is the number of tokens scanned
    ;
    mov TokenCount,Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT )
    mov rbx,TokenArray

if REMOVECOMENT eq 0
    .if ( eax == 0 && ( CurrIfState == BLOCK_ACTIVE || MODULE.listif ) )

        LstWriteSrcLine()
    .endif
endif

    mov eax,TokenCount
    .return .if ( eax == 0 )
    ;
    ; CurrIfState != BLOCK_ACTIVE && TokenCount == 1 | 3 may happen
    ; if a conditional assembly directive has been detected by Tokenize().
    ; However, it's important NOT to expand then
    ;
    .if ( CurrIfState == BLOCK_ACTIVE )

        xor esi,esi
        imul eax,eax,asm_tok
        .if ( [rbx+rax].bytval & TF3_EXPANSION )
            mov esi,ExpandText(CurrSource, rbx, 1)
        .elseifd ( DelayExpand( rbx ) == 0 )
            mov esi,ExpandLine( CurrSource, rbx )
        .elseif ( Parse_Pass == PASS_1 )
            ExpandLineItems( CurrSource, 0, rbx, 0, 1 )
        .endif
        .return 0 .ifs ( esi < NOT_ERROR )
    .endif

    mov rbx,TokenArray
    xor esi,esi
    .if ( TokenCount > 2 &&
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
            .ifd ( WriteCodeLabel( CurrSource, rbx ) == ERROR )
                .return 0
            .endif
        .endif

        movzx ebx,[rbx+rsi].dirtype
        xor edx,edx
        mov ecx,asm_tok
        mov eax,esi
        div ecx
        mov esi,eax
        lea rcx,directive_tab
        mov rax,[rcx+rbx*size_t]

        assume rax:fpDirective
        rax( esi, TokenArray )
        assume rax:nothing
       .return 0
    .endif

    ;
    ; handle preprocessor directives which need a label
    ;
    mov rbx,TokenArray
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
                    .if StoreState
                        FStoreLine(0)
                    .endif
                    .if Options.preprocessor_stdout
                        WritePreprocessedLine( CurrSource )
                    .endif
                .endif
                ;
                ; v2.03: LstWrite() must be called AFTER StoreLine()!
                ;
                .if MODULE.list
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
            mov rax,[rcx+rax*size_t]
            assume rax:fpDirective
            rax(1, rbx)
            assume rax:nothing
           .return 0
        .endsw
    .endif
    .return( TokenCount )

PreprocessLine endp

    end
