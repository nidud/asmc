; ENUM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; .enum [name][:type] [{]
; .enumt [name][:type] [{]
;

include stdio.inc
include string.inc
include asmc.inc
include proc.inc
include hllext.inc
include parser.inc

public CurrEnum

    .data
    CurrEnum ptr asym 0
    .code

    assume rbx:ptr asm_tok
    assume rsi:ptr asym

EnumDirective proc uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local name:string_t
  local opndx:expr
  local rc:int_t
  local cmd:int_t
  local type:int_t
  local buffer[128]:char_t

    .return NOT_ERROR .if ( Parse_Pass > PASS_1 )

    mov rc,NOT_ERROR
    mov rbx,tokenarray
    mov rsi,CurrEnum
    mov eax,[rbx].tokval

    .switch eax
    .case T_DOT_ENUM
    .case T_DOT_ENUMT

        mov rdi,rsi
        mov rsi,LclAlloc(asym)
        mov CurrEnum,rax
        mov [rsi].nextitem,rdi
        mov [rsi].name,0
        mov [rsi].value,0
        mov [rsi].total_size,4
        mov [rsi].mem_type,MT_SDWORD
        mov [rsi].total_length,0
        .if [rbx].tokval == T_DOT_ENUMT
            inc [rsi].total_length
        .endif

        add rbx,asm_tok
        inc i

        .if ( [rbx].token != T_FINAL )

            .if ( [rbx].token == T_STRING )

                mov [rsi].name,[rbx].string_ptr
                mov rax,[rbx].tokpos
                add rbx,asm_tok
                inc i
                .if ( byte ptr [rax] == '{' && byte ptr [rax+1] )
                    inc rax
                    Tokenize( rax, 0, rbx, TOK_DEFAULT )
                    add Token_Count,eax
                .endif

            .else

                mov type,T_SDWORD
                mov name,NameSpace([rbx].string_ptr, [rbx].string_ptr)
                add rbx,asm_tok
                inc i

                .if ( [rbx].token == T_COLON )

                    add rbx,asm_tok
                    inc i
                    mov ecx,i
                    inc ecx
                    mov rc,EvalOperand( &i, tokenarray, ecx, &opndx, 0 )
                    .if eax != ERROR
                        mov [rsi].total_size,opndx.value
                        add rbx,asm_tok
                        .if ( [rsi].total_length == 0 )
                            .if ( opndx.mem_type & MT_SIGNED )
                                .switch pascal eax
                                .case 2: mov type,T_SWORD  : mov [rsi].mem_type,MT_SWORD
                                .case 1: mov type,T_SBYTE  : mov [rsi].mem_type,MT_SBYTE
                                .endsw
                            .else
                                .switch pascal eax
                                .case 4: mov type,T_DWORD : mov [rsi].mem_type,MT_DWORD
                                .case 2: mov type,T_WORD  : mov [rsi].mem_type,MT_WORD
                                .case 1: mov type,T_BYTE  : mov [rsi].mem_type,MT_BYTE
                                .endsw
                            .endif
                        .endif
                    .endif
                .endif
                AddLineQueueX( "%s typedef %r", name, type )
            .endif

            .if ( [rbx].token == T_STRING )

                mov [rsi].name,[rbx].string_ptr
                mov rax,[rbx].tokpos
                add rbx,asm_tok
                inc i
                .if ( byte ptr [rax] == '{' && byte ptr [rax+1] )
                    inc rax
                    Tokenize( rax, 0, rbx, TOK_DEFAULT )
                    add Token_Count,eax
                .endif
            .endif
        .endif
        .if ModuleInfo.list
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
    .endsw

    .while [rbx].token != T_FINAL

        mov rcx,[rbx].string_ptr
        add rbx,asm_tok
        .if ( [rbx-asm_tok].token == T_STRING && word ptr [rcx] == '}' )
            mov CurrEnum,[rsi].nextitem
            .break
        .endif
        mov name,rcx
        inc i
        mov opndx.value,[rsi].value
        add [rsi].value,1

        mov edi,1

        .if ( [rbx].token == T_DIRECTIVE && [rbx].tokval == T_EQU )

            add rbx,asm_tok
            inc i

            .for ( ecx = i, rdx = rbx : ecx < Token_Count : ecx++, rdx += asm_tok )
                .break .if [rdx].asm_tok.token == T_COMMA
                .break .if [rdx].asm_tok.token == T_FINAL
                .break .if [rdx].asm_tok.token == T_STRING
            .endf
            .break .if rdx == rbx
            mov rc,EvalOperand( &i, tokenarray, ecx, &opndx, 0 )
            .break .if eax == ERROR
            .if opndx.kind != EXPR_CONST
                mov rc,asmerr(2026)
                .break
            .endif
            .if ( [rbx].token =='-' && [rbx+asm_tok].token == T_NUM && [rbx+asm_tok].numbase == 10 )
                xor edi,edi
            .endif
            mov ecx,1
            mov eax,opndx.value
            .if eax & 0xFFFF0000
                mov ecx,4
            .elseif eax & 0xFF00
                mov ecx,2
            .endif
            mov edx,opndx.hvalue
            .if ( edx || ecx > [rsi].total_size )
                .if ( edx == -1 )
                    or opndx.value,0x80000000
                .else
                    mov rc,asmerr(2071)
                    .break
                .endif
            .endif
            add eax,1
            mov [rsi].value,eax
            imul ebx,i,asm_tok
            add rbx,tokenarray
        .endif
        .if ( [rbx].token == T_COMMA )
            add rbx,asm_tok
            inc i
        .elseif ( [rbx].token == T_FINAL && [rsi].name == NULL )
            mov CurrEnum,[rsi].nextitem
        .endif
        mov eax,opndx.value
        .if ( [rsi].total_length )
            mul [rsi].total_size
        .endif
        .if edi
            lea rcx,@CStr("%s equ 0x%x")
        .else
            lea rcx,@CStr("%s equ %d")
        .endif
        AddLineQueueX(rcx, name, eax)
    .endw

    .if ( [rbx].token != T_FINAL )
        .return asmerr( 2008, [rbx].tokpos )
    .endif

    .if ( ModuleInfo.line_queue.head )

        mov rsi,CurrEnum
        mov CurrEnum,NULL
        RunLineQueue()
        mov CurrEnum,rsi
    .endif
    mov eax,rc
    ret

EnumDirective endp

    end
