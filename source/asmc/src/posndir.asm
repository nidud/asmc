; POSNDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: ALIGN, EVEN, ORG directives
;

include asmc.inc
include parser.inc
include segment.inc
include expreval.inc
include types.inc
include listing.inc
include posndir.inc
include fastpass.inc
include fixup.inc

.data

NopList16 db \
    3,                  ; objlen of first NOP pattern
    0x2E, 0x8b, 0xc0,   ; MOV AX,AX
    ; v2.11: Masm v6+ uses 8B CO; Masm v5 uses 87 DB (xchg bx, bx)
    0x8b, 0xc0,         ; MOV AX,AX
    0x90                ; NOP


; 32bit alignment fillers.
; For 5 bytes, Masm uses "add eax,dword ptr 0",
; which modifies the flags!


NopList32 db \
    7,
    0x8d,0xa4,0x24,0,0,0,0,         ; lea     esp,[esp+00000000]
    0x8d,0x80,0,0,0,0,              ; lea     eax,[eax+00000000]
    0x2e,0x8d,0x44,0x20,0x00,       ; lea     eax,cs:[eax+no_index_reg+00H]
    0x8d,0x44,0x20,0x00,            ; lea     eax,[eax+no_index_reg+00H]
    0x8d,0x40,0x00,                 ; lea     eax,[eax+00H]
    0x8b,0xff,                      ; mov     edi,edi
    0x90                            ; nop


NopList64 db \
    7,
    0x0f,0x1f,0x80,0,0,0,0,         ; nop dword ptr [rax+0]
    0x66,0x0f,0x1f,0x44,0,0,        ; nop word ptr [rax+rax]
    0x0f,0x1f,0x44,0,0,             ; nop dword ptr [rax+rax]
    0x0f,0x1f,0x40,0,               ; nop dword ptr [rax]
    0x0f,0x1f,0,                    ; nop dword ptr [rax]
    0x66,0x90,                      ; xchg ax,ax
    0x90                            ; nop


; just use the 32bit nops for 64bit
NopLists ptr byte NopList16, NopList32, NopList64

    .code

OrgDirective proc __ccall i:int_t, tokenarray:ptr asm_tok

  local opndx:expr

    inc i
    xor ecx,ecx
    .if ( ModuleInfo.masm_compat_gencode )
        mov ecx,EXPF_NOUNDEF
    .endif
    .return .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, cl ) == ERROR )

    imul ecx,i,asm_tok
    add rcx,tokenarray
    .if ( [rcx].asm_tok.token != T_FINAL )
        .return( asmerr( 2008, [rcx].asm_tok.string_ptr ) )
    .endif
    .if ( CurrStruct )
        .if ( opndx.kind == EXPR_CONST )
            .return( SetStructCurrentOffset( opndx.value ) )
        .endif
    .else
        .if( CurrSeg == NULL )
            .return( asmerr( 2034 ) )
        .endif
        .if ( StoreState == FALSE )
            FStoreLine(0)
        .endif
        ; v2.04: added
        mov rcx,CurrSeg
        mov rcx,[rcx].dsym.seginfo
        .if ( Parse_Pass == PASS_1 && [rcx].seg_info.head )
            mov rdx,[rcx].seg_info.head
            or [rdx].fixup.fx_flag,FX_ORGOCCURED
        .endif

        .if ( opndx.kind == EXPR_CONST )
            .return( SetCurrOffset( CurrSeg, opndx.value, FALSE, FALSE ) )
        .elseif ( opndx.kind == EXPR_ADDR && !( opndx.flags & E_INDIRECT ) )
            mov rcx,opndx.sym
            mov edx,[rcx].asym.offs
            add edx,opndx.value
            .return( SetCurrOffset( CurrSeg, edx, FALSE, FALSE ) )
        .endif
    .endif
    .return( asmerr( 2132 ) )

OrgDirective endp


fill_in_objfile_space proc __ccall private uses rsi rdi rbx size:dword

    ; emit
    ; - nothing ... for BSS
    ; - x'00'   ... for DATA
    ; - nops    ... for CODE

    ; v2.04: no output if nothing has been written yet
    mov rdi,CurrSeg
    mov rsi,[rdi].dsym.seginfo
    .if ( [rsi].seg_info.written == FALSE )

        SetCurrOffset( rdi, size, TRUE, TRUE )

    .elseif ( [rsi].seg_info.segtype != SEGTYPE_CODE )

        FillDataBytes( 0x00, size ) ; just output nulls

    .else
        ; output appropriate NOP type instructions to fill in the gap
        movzx   ebx,ModuleInfo.Ofssize
        lea     rcx,NopLists
        mov     rsi,[rcx+rbx*size_t]
        movzx   ebx,byte ptr [rsi]
        .while ( size > ebx )
            .for ( edi = 1: edi <= ebx: edi++ )
                OutputByte( [rsi+rdi] )
            .endf
            sub size,ebx
        .endw
        .return .if ( size == 0 )
        inc rsi ; here i is the index into the NOP table
        .fors ( edi = ebx : edi > size : edi-- )
            add rsi,rdi
        .endf
        ; i now is the index of the 1st part of the NOP that we want
        .fors ( : edi > 0 : edi--, rsi++ )
            OutputByte( [rsi] )
        .endf
    .endif
    ret

fill_in_objfile_space endp


; align current offset to value ( alignment is 2^value )

AlignCurrOffset proc __ccall value:int_t

    GetCurrOffset()

    mov ecx,value
    mov edx,1
    shl edx,cl
    mov ecx,edx
    cdq
    div ecx
    .if ( edx )
        sub ecx,edx
        fill_in_objfile_space( ecx )
    .endif
    ret

AlignCurrOffset endp


define align_value <opndx.value>

AlignDirective proc __ccall i:int_t, tokenarray:ptr asm_tok

  local opndx:expr
  local CurrAddr:uint_t

    imul ecx,i,asm_tok
    add rcx,tokenarray

    .switch( [rcx].asm_tok.tokval )
    .case T_ALIGN
        inc i
        .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF ) == ERROR )
            .return
        .endif
        .if ( opndx.kind == EXPR_CONST )
            ;int_32 power
            ; check that the parm is a power of 2
            .fors ( ecx = 1: ecx < align_value: ecx <<= 1 )
            .endf
            .if ( ecx != align_value )
                .return( asmerr( 2063, align_value ) )
            .endif
        .elseif ( opndx.kind == EXPR_EMPTY )  ; ALIGN without argument?
            ; v2.03: special STRUCT handling was missing
            .if ( CurrStruct )
                mov rcx,CurrStruct
                mov rcx,[rcx].dsym.structinfo
                mov align_value,[rcx].struct_info.alignment
            .else
                mov align_value,GetCurrSegAlign()
            .endif
        .else
            .return( asmerr( 2026 ) )
        .endif
        .endc
    .case T_EVEN
        mov align_value,2
        inc i
        .endc
    .endsw

    imul ecx,i,asm_tok
    add rcx,tokenarray
    .if ( [rcx].asm_tok.token != T_FINAL )
        .return( asmerr(2008, [rcx].asm_tok.string_ptr ) )
    .endif

    ; ALIGN/EVEN inside a STRUCT definition?
    .if ( CurrStruct )
        .return( AlignInStruct( align_value ))
    .endif

    .if ( StoreState == FALSE )
        FStoreLine(0)
    .endif
    GetCurrSegAlign(); ; # of bytes
    .ifs ( eax <= 0 )
        .return( asmerr( 2034 ) )
    .endif
    .if ( align_value > eax )
        .if ( Parse_Pass == PASS_1 )
            asmerr( 2189, align_value )
        .endif
    .endif
    ; v2.04: added, Skip backpatching after ALIGN occured
    .if ( Parse_Pass == PASS_1 && CurrSeg )

        mov rcx,CurrSeg
        mov rcx,[rcx].dsym.seginfo
        mov rcx,[rcx].seg_info.head
        .if rcx
            or  [rcx].fixup.fx_flag,FX_ORGOCCURED
        .endif
    .endif
    ; find out how many bytes past alignment we are & add the remainder
    ; store temp. value
    mov CurrAddr,GetCurrOffset()
    cdq
    div align_value
    .if( edx )
        sub align_value,edx
        fill_in_objfile_space( align_value )
    .endif
    .if ( CurrFile[LST*size_t] )
        LstWrite( LSTTYPE_DATA, CurrAddr, NULL )
    .endif
    .return( NOT_ERROR )

AlignDirective endp

    end
