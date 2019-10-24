; ENUM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; .enum [name][:type] [{]
;

include stdio.inc
include string.inc
include asmc.inc
include proc.inc
include hllext.inc
include parser.inc

public CurrEnum

    .data
    CurrEnum asym_t 0
    .code

    assume ebx:tok_t
    assume esi:asym_t

EnumDirective proc uses esi edi ebx i:int_t, tokenarray:tok_t

  local name:string_t
  local opndx:expr
  local rc:int_t
  local type:int_t
  local buffer[64]:char_t

    .return NOT_ERROR .if ( Parse_Pass > PASS_1 )

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    mov esi,CurrEnum

    .if !esi

        mov esi,LclAlloc(asym)
        mov CurrEnum,eax
        mov [esi].name,0
        mov [esi].value,0
        mov [esi].total_size,4
        mov [esi].mem_type,MT_SDWORD
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
                mov name,[ebx].string_ptr
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
                        .if opndx.mem_type & MT_SIGNED
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
    .endif

    .while [ebx].token != T_FINAL

        mov name,[ebx].string_ptr
        add ebx,16
        .if [ebx-16].token == T_STRING && word ptr [eax] == '}'
            mov CurrEnum,NULL
            .break
        .endif
        inc i
        mov opndx.value,[esi].value
        add [esi].value,1
        .if [ebx].token == T_DIRECTIVE && [ebx].tokval == T_EQU
            add ebx,16
            inc i
            .for ( ecx = i, edx = ebx : ecx < Token_Count : ecx++, edx += 16 )
                .break .if [edx].asm_tok.token == T_COMMA
                .break .if [edx].asm_tok.token == T_FINAL
                .break .if [edx].asm_tok.token == T_STRING
            .endf
            .break .if edx == ebx
            mov rc,EvalOperand( &i, tokenarray, ecx, &opndx, 0 )
            .break .if eax == ERROR
            .if opndx.kind != EXPR_CONST
                mov rc,asmerr(2026)
                .break
            .endif
            mov ecx,1
            mov eax,opndx.value
            .if eax & 0xFFFF0000
                mov ecx,4
            .elseif eax & 0xFF00
                mov ecx,2
            .endif
            mov edx,opndx.hvalue
            .if edx || ecx > [esi].total_size
                .if edx == -1
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
        .if [ebx].token == T_COMMA
            add ebx,16
            inc i
        .elseif [ebx].token == T_FINAL && [esi].name == NULL
            mov CurrEnum,NULL
        .endif
        .if [esi].mem_type & MT_SIGNED
            lea edx,@CStr("%s equ %d")
        .else
            lea edx,@CStr("%s equ %u")
        .endif
        AddLineQueueX(edx, name, opndx.value)
    .endw
    .return asmerr(2008, [ebx].tokpos) .if [ebx].token != T_FINAL
    .if ModuleInfo.line_queue.head
        mov esi,CurrEnum
        mov CurrEnum,NULL
        RunLineQueue()
        mov CurrEnum,esi
    .endif
    mov eax,rc
    ret

EnumDirective endp

    end
