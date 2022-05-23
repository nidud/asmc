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

    assume ebx:ptr asm_tok
    assume esi:ptr asym

EnumDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local name:string_t
  local opndx:expr
  local rc:int_t
  local cmd:int_t
  local type:int_t
  local buffer[128]:char_t

    .return NOT_ERROR .if ( Parse_Pass > PASS_1 )

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    mov esi,CurrEnum
    mov eax,[ebx].tokval

    .switch eax
    .case T_DOT_ENUM
    .case T_DOT_ENUMT

        mov edi,esi
        mov esi,LclAlloc(asym)
        mov CurrEnum,eax
        mov [esi].nextitem,edi
        mov [esi].name,0
        mov [esi].value,0
        mov [esi].total_size,4
        mov [esi].mem_type,MT_SDWORD
        mov [esi].total_length,0
        .if [ebx].tokval == T_DOT_ENUMT
            inc [esi].total_length
        .endif

        add ebx,16
        inc i

        .if ( [ebx].token != T_FINAL )

            .if ( [ebx].token == T_STRING )

                mov [esi].name,[ebx].string_ptr
                mov eax,[ebx].tokpos
                add ebx,16
                inc i
                .if ( byte ptr [eax] == '{' && byte ptr [eax+1] )
                    inc eax
                    Tokenize( eax, 0, ebx, TOK_DEFAULT )
                    add Token_Count,eax
                .endif

            .else

                mov type,T_SDWORD
                mov name,NameSpace([ebx].string_ptr, [ebx].string_ptr)
                add ebx,16
                inc i

                .if ( [ebx].token == T_COLON )

                    add ebx,16
                    inc i
                    mov ecx,i
                    inc ecx
                    mov rc,EvalOperand( &i, tokenarray, ecx, &opndx, 0 )
                    .if eax != ERROR
                        mov [esi].total_size,opndx.value
                        add ebx,16
                        .if ( [esi].total_length == 0 )
                            .if ( opndx.mem_type & MT_SIGNED )
                                .switch pascal eax
                                .case 2: mov type,T_SWORD  : mov [esi].mem_type,MT_SWORD
                                .case 1: mov type,T_SBYTE  : mov [esi].mem_type,MT_SBYTE
                                .endsw
                            .else
                                .switch pascal eax
                                .case 4: mov type,T_DWORD : mov [esi].mem_type,MT_DWORD
                                .case 2: mov type,T_WORD  : mov [esi].mem_type,MT_WORD
                                .case 1: mov type,T_BYTE  : mov [esi].mem_type,MT_BYTE
                                .endsw
                            .endif
                        .endif
                    .endif
                .endif
                AddLineQueueX( "%s typedef %r", name, type )
            .endif

            .if ( [ebx].token == T_STRING )

                mov [esi].name,[ebx].string_ptr
                mov eax,[ebx].tokpos
                add ebx,16
                inc i
                .if ( byte ptr [eax] == '{' && byte ptr [eax+1] )
                    inc eax
                    Tokenize( eax, 0, ebx, TOK_DEFAULT )
                    add Token_Count,eax
                .endif
            .endif
        .endif
        .if ModuleInfo.list
            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif
    .endsw

    .while [ebx].token != T_FINAL

        mov ecx,[ebx].string_ptr
        add ebx,16
        .if ( [ebx-16].token == T_STRING && word ptr [ecx] == '}' )
            mov CurrEnum,[esi].nextitem
            .break
        .endif
        mov name,ecx
        inc i
        mov opndx.value,[esi].value
        add [esi].value,1

        mov edi,1

        .if ( [ebx].token == T_DIRECTIVE && [ebx].tokval == T_EQU )

            add ebx,16
            inc i

            .for ( ecx = i, edx = ebx : ecx < Token_Count : ecx++, edx += 16 )
                .break .if [edx].asm_tok.token == T_COMMA
                .break .if [edx].asm_tok.token == T_FINAL
                .if [edx].asm_tok.token == T_STRING
                    ; added v2.33.56
                    mov eax,[edx].asm_tok.string_ptr
                   .break .if word ptr [eax] == '}'
                .endif
            .endf
            .break .if edx == ebx
            mov rc,EvalOperand( &i, tokenarray, ecx, &opndx, 0 )
            .break .if eax == ERROR
            .if opndx.kind != EXPR_CONST
                mov rc,asmerr(2026)
                .break
            .endif
            .if ( [ebx].token =='-' && [ebx+16].token == T_NUM && [ebx+16].numbase == 10 )
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
            .if ( edx || ecx > [esi].total_size )
                .if ( edx == -1 )
                    or opndx.value,0x80000000
                .else
                    mov rc,asmerr(2071)
                    .break
                .endif
            .endif
            add eax,1
            mov [esi].value,eax
            imul ebx,i,asm_tok
            add ebx,tokenarray
        .endif
        .if ( [ebx].token == T_COMMA )
            add ebx,16
            inc i
        .elseif ( [ebx].token == T_FINAL && [esi].name == NULL )
            mov CurrEnum,[esi].nextitem
        .endif
        mov eax,opndx.value
        .if ( [esi].total_length )
            mul [esi].total_size
        .endif
        .if edi
            lea edx,@CStr("%s equ 0x%x")
        .else
            lea edx,@CStr("%s equ %d")
        .endif
        AddLineQueueX(edx, name, eax)
    .endw

    .if ( [ebx].token != T_FINAL )
        .return asmerr( 2008, [ebx].tokpos )
    .endif

    .if ( ModuleInfo.line_queue.head )

        mov esi,CurrEnum
        mov CurrEnum,NULL
        RunLineQueue()
        mov CurrEnum,esi
    .endif
    mov eax,rc
    ret

EnumDirective endp

    end
