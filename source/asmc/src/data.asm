; DATA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Description: data definition. handles
;       - directives DB,DW,DD,...
;       - predefined types (BYTE, WORD, DWORD, ...)
;       - arbitrary types
;

include malloc.inc
include float.inc
include crtl.inc

include asmc.inc
include memalloc.inc
include parser.inc
include expreval.inc
include input.inc
include fixup.inc
include listing.inc
include segment.inc
include types.inc
include fastpass.inc
include tokenize.inc
include macro.inc
include omf.inc
include atofloat.inc

segm_override proto :ptr expr, :ptr code_info
extern SegOverride:ptr asym
extern szNull:char_t

data_item proto :ptr int_t, :ptr asm_tok, :ptr asym, :uint_32, :ptr asym,
    :uint_32, :int_t, :int_t, :int_t, :int_t

OutputDataBytes macro x, y
    exitm<OutputBytes( x, y, NULL )>
    endm

; initialize an array inside a structure
; if there are no brackets, the next comma, '>' or '}' will terminate
;
; valid initialization are:
; - an expression, might contain DUP or a string enclosed in quotes.
; - a literal enclosed in <> or {} which then is supposed to contain
;   single items.

    .code

    option proc:private

AsmerrSymName proc fastcall error:int_t, sym:ptr asym

    lea eax,@CStr("")
    .if sym
        mov eax,[sym].asym.name
    .endif
    asmerr( error, eax )
    ret

AsmerrSymName endp

    assume ebx:ptr asm_tok
    assume edi:ptr sfield

InitializeArray proc uses esi edi ebx f:ptr sfield, pi:ptr int_t, tokenarray:ptr asm_tok

  local oldofs:uint_32
  local no_of_bytes:uint_32
  local i:int_t
  local j:int_t
  local lvl:int_t
  local old_tokencount:int_t
  local bArray:char_t
  local rc:int_t

    mov ecx,pi
    mov i,[ecx]
    imul ebx,eax,asm_tok
    add ebx,tokenarray
    mov edi,f

    mov oldofs,GetCurrOffset()
    mov no_of_bytes,SizeFromMemtype( [edi].mem_type, USE_EMPTY, [edi].type )

    ; If current item is a literal enclosed in <> or {}, just use this
    ; item. Else, use all items until a comma or EOL is found.

    .if ( [ebx].token != T_STRING || \
        ( [ebx].string_delim != '<' &&  [ebx].string_delim != '{' ) )

        ; scan for comma or final. Ignore commas inside DUP argument

        .for( edx = i,
              esi = ebx,
              ecx = 0,
              bArray = FALSE : [ebx].token != T_FINAL: edx++, ebx += 16 )
            .if ( [ebx].token == T_OP_BRACKET )
                inc ecx
            .elseif ( [ebx].token == T_CL_BRACKET )
                dec ecx
            .elseif ( ecx == 0 && [ebx].token == T_COMMA )
                .break
            .elseif ( [ebx].token == T_RES_ID && [ebx].tokval == T_DUP )
                mov bArray,TRUE
            .elseif ( no_of_bytes == 1 && [ebx].token == T_STRING && \
                     ( [ebx].string_delim == '"' || [ebx].string_delim == "'" ) )
                mov bArray,TRUE
            .endif
        .endf
        mov ecx,pi
        mov [ecx],edx
        .if ( bArray == FALSE )
            mov ebx,esi
            .return( asmerr( 2181, [ebx].tokpos ) )
        .endif

        mov ecx,[ebx].tokpos
        mov ebx,esi
        sub ecx,[ebx].tokpos
        mov esi,f

        ; v2.07: accept an "empty" quoted string as array initializer for byte arrays

        .if ( ecx == 2 && \
            [edi].total_size == [edi].total_length && \
            ( [ebx].string_delim == '"' || [ebx].string_delim == "'" ) )
            mov rc,NOT_ERROR
        .else
            mov lvl,i ;; i must remain the start index
            movzx ecx,[edi].mem_type
            and ecx,MT_FLOAT
            mov rc,data_item( &lvl, tokenarray, NULL, no_of_bytes,
                    [edi].type, 1, FALSE, ecx, FALSE, edx )
        .endif

    .else

        ; initializer is a literal

        mov ecx,pi
        inc dword ptr [ecx]
        mov old_tokencount,Token_Count
        inc eax
        mov j,eax

        ; if the string is empty, use the default initializer

        .if ( [ebx].stringlen == 0 )
            mov Token_Count,Tokenize( &[edi].ivalue, j, tokenarray, TOK_RESCAN )
        .else
            mov Token_Count,Tokenize( [ebx].string_ptr, j, tokenarray, TOK_RESCAN )
        .endif
        movzx ecx,[edi].mem_type
        and ecx,MT_FLOAT
        mov rc,data_item( &j, tokenarray, NULL, no_of_bytes, [edi].type, 1,
                FALSE, ecx, FALSE, Token_Count )
        mov Token_Count,old_tokencount
    .endif

    ; get size of array items

    GetCurrOffset()
    sub eax,oldofs
    mov no_of_bytes,eax

    .if ( eax > [edi].total_size )
        mov rc,asmerr( 2036, [ebx].tokpos )
    .elseif ( eax < [edi].total_size )
        .new filler:char_t = 0
        mov ecx,CurrSeg
        .if ecx
            mov ecx,[ecx].dsym.seginfo
        .endif
        .if ( ecx && [ecx].seg_info.segtype == SEGTYPE_BSS )

            mov eax,[edi].total_size
            sub eax,no_of_bytes
            SetCurrOffset( CurrSeg, eax, TRUE, TRUE )
        .else

            ; v2.07: if element size is 1 and a string is used as initial value,
            ; pad array with spaces!

            .if ( [edi].total_size == [edi].total_length && \
                ( [edi].ivalue[0] == '"' || [edi].ivalue[0] == "'" ) )
                mov filler,' '
            .endif
            mov eax,[edi].total_size
            sub eax,no_of_bytes
            FillDataBytes( filler, eax )
        .endif
    .endif
    .return( rc )

InitializeArray endp

; initialize a STRUCT/UNION/RECORD data item
; index:    index of initializer literal
; symtype:  type of data item
; embedded: is != NULL if proc is called recursively
;
; up to v2.08, this proc did emit ASM lines with simple types
; to actually "fill" the structure.
; since v2.09, it calls data_item() directly.
;
; Since this function may be reentered, it's necessary to save/restore
; global variable Token_Count.

InitStructuredVar proc uses esi edi ebx index:int_t, tokenarray:ptr asm_tok,
        symtype:ptr dsym, embedded:ptr asym

   .new nextofs:int_32
   .new i:int_t
   .new j:int_t
   .new no_of_bytes:int_t
   .new old_tokencount:int_t = Token_Count
   .new old_stringbufferend:string_t = StringBufferEnd
   .new dwRecInit:uint_64
   .new is_record_set:int_t
   .new opndx:expr

    imul ebx,index,asm_tok
    add ebx,tokenarray
    mov esi,embedded

    .if ( [ebx].token == T_STRING )
        ;; v2.08: no special handling of {}-literals anymore
        .if ( [ebx].string_delim != '<' && [ebx].string_delim != '{' )
            .return( asmerr( 2045 ) )
        .endif
        mov eax,Token_Count
        inc eax
        mov i,eax

        mov Token_Count,Tokenize( [ebx].string_ptr, i, tokenarray, TOK_RESCAN )

        ; once Token_Count has been modified, don't exit without
        ; restoring this value!

    .elseif ( esi && ( [ebx].token == T_COMMA || [ebx].token == T_FINAL ) )
        mov i,Token_Count
    .else
        .return( AsmerrSymName( 2181, esi ) )
    .endif
    imul ebx,i,asm_tok
    add ebx,tokenarray

    mov esi,symtype
    .if ( [esi].asym.typekind == TYPE_RECORD )
        xor eax,eax
        mov dword ptr dwRecInit,eax
        mov dword ptr dwRecInit[4],eax
        mov is_record_set,eax
    .endif

    ;; scan the STRUCT/UNION/RECORD's members

    mov edx,[esi].dsym.structinfo
    .for ( edi = [edx].struct_info.head: edi: edi = [edi].next )

        ; is it a RECORD field?

        .if ( [edi].mem_type == MT_BITS )
            .if ( [ebx].token == T_COMMA || [ebx].token == T_FINAL )
                .if ( [edi].ivalue[0] )
                    mov j,Token_Count
                    inc j
                    mov ecx,Tokenize( &[edi].ivalue, j, tokenarray, TOK_RESCAN )
                    EvalOperand( &j, tokenarray, ecx, &opndx, 0 )
                    mov is_record_set,TRUE
                .else
                    mov opndx.value,0
                    mov opndx.kind,EXPR_CONST
                    mov opndx.quoted_string,NULL
                .endif
            .else
                EvalOperand( &i, tokenarray, Token_Count, &opndx, 0 )
                mov is_record_set,TRUE
            .endif
            .if ( opndx.kind != EXPR_CONST || opndx.quoted_string != NULL )
                asmerr( 2026 )
            .endif

            ; fixme: max bits in 64-bit is 64 - see MAXRECBITS!

            mov ecx,[edi].total_size
            .if ( ecx < 32 )
                mov eax,1
                shl eax,cl
                .if ( opndx.uvalue >= eax )
                    asmerr( 2071, [edi].name )
                .endif
            .endif
            mov eax,dword ptr opndx.llvalue
            mov edx,dword ptr opndx.llvalue[4]
            mov ecx,[edi].offs
            call __llshl
            or dword ptr dwRecInit,eax
            or dword ptr dwRecInit[4],edx

        .elseif ( [edi].ivalue[0] == 0 )  ;; embedded struct?

            InitStructuredVar( i, tokenarray, [edi].type, edi )
            .if ( [ebx].token == T_STRING )
                inc i
            .endif

        .elseif ( [edi].flag1 & S_ISARRAY && \
                  [ebx].token != T_FINAL && [ebx].token != T_COMMA )

            .if ( InitializeArray( edi, &i, tokenarray ) == ERROR )

                imul ebx,i,asm_tok
                add ebx,tokenarray
                .break
            .endif

        .elseif ( [edi].total_size == [edi].total_length && \
                  [ebx].token == T_STRING && [ebx].stringlen > 1 && \
                  ( [ebx].string_delim == '"' || [ebx].string_delim == "'" ) )

            ; v2.07: it's a byte type, but no array, string initializer must have true length 1

            asmerr( 2041 )
            inc i

        .else

            mov no_of_bytes,SizeFromMemtype( [edi].mem_type, USE_EMPTY, [edi].type )

            .if ( [ebx].token == T_FINAL || [ebx].token == T_COMMA )

                mov eax,Token_Count
                push eax
                inc eax
                mov j,eax
                mov Token_Count,Tokenize( &[edi].ivalue, eax, tokenarray, TOK_RESCAN )
                mov cl,[edi].mem_type
                and ecx,MT_FLOAT
                data_item( &j, tokenarray, NULL, no_of_bytes, [edi].type, 1,
                    FALSE, ecx, FALSE, Token_Count )
                pop Token_Count

            .else

                ; ignore commas enclosed in () ( might occur inside DUP argument! ).

                .for ( j = i,
                      eax = ebx,
                      edx = 0,
                      ecx = 0: [ebx].token != T_FINAL: ebx += 16, i++ )
                    .if ( [ebx].token == T_OP_BRACKET )
                        inc edx
                    .elseif ( [ebx].token == T_CL_BRACKET )
                        dec edx
                    .elseif ( edx == 0 && [ebx].token == T_COMMA )
                        .break
                    .elseif ( [ebx].token == T_RES_ID && [ebx].tokval == T_DUP )
                        inc ecx ;; v2.08: check added
                    .endif
                .endf

                .if ( ecx )
                    asmerr( 2181, [eax].asm_tok.tokpos )
                .else
                    mov cl,[edi].mem_type
                    and ecx,MT_FLOAT
                    .if ( data_item( &j, tokenarray, NULL, no_of_bytes,
                            [edi].type, 1, FALSE, ecx, FALSE, i ) == ERROR )
                        asmerr( 2104, [edi].name )
                    .endif
                .endif
            .endif
        .endif
        imul ebx,i,asm_tok
        add ebx,tokenarray

        ; Add padding bytes if necessary (never inside RECORDS!).
        ; f->next == NULL : it's the last field of the struct/union/record

        .if ( [esi].asym.typekind != TYPE_RECORD )
            .if ( [edi].next == NULL || [esi].asym.typekind == TYPE_UNION )
                mov nextofs,[esi].asym.total_size
            .else
                mov ecx,[edi].next
                mov nextofs,[ecx].sfield.offs
            .endif
            mov ecx,[edi].offs
            add ecx,[edi].total_size
            .if ( ecx < eax )
                sub eax,ecx
                SetCurrOffset( CurrSeg, eax, TRUE, TRUE )
            .endif
        .endif

        ; for a union, just the first field is initialized

        .break .if ( [esi].asym.typekind == TYPE_UNION )

        .if ( [edi].next != NULL )

            .if ( [ebx].token != T_FINAL )
                .if ( [ebx].token == T_COMMA )
                    inc i
                    add ebx,16
                .else
                    asmerr(2008, [ebx].tokpos )
                    .while ( [ebx].token != T_FINAL && [ebx].token != T_COMMA )
                        inc i
                        add ebx,16
                    .endw
                .endif
            .endif
        .endif
    .endf

    .if ( [esi].asym.typekind == TYPE_RECORD )

        mov al,[esi].asym.mem_type
        mov ecx,4
        .switch pascal al
        .case MT_BYTE : mov ecx,1
        .case MT_WORD : mov ecx,2
        .case MT_QWORD: mov ecx,8
        .endsw
        .if ( is_record_set )
            OutputDataBytes( &dwRecInit, ecx )
        .else
            SetCurrOffset( CurrSeg, ecx, TRUE, TRUE )
        .endif
    .endif

    .if ( [ebx].token != T_FINAL )
        asmerr( 2036, [ebx].tokpos )
    .endif

    ; restore token status

    mov Token_Count,old_tokencount
    mov StringBufferEnd,old_stringbufferend
    .return( NOT_ERROR )

InitStructuredVar endp

;
; convert a string into little endian format - ( LSB 1st, LSW 1st ... etc ).
; <len> is the TYPE, may be 2,4,6,8,10?,16
;

little_endian proc fastcall uses ebx src:string_t, len:dword

    ; v2.06: input and output buffer must be different!

    mov ebx,StringBufferEnd
    .for ( : edx > 1 : ebx++, ecx++, edx-- )
        dec edx
        mov al,[ecx+edx]
        mov [ebx],al
        mov al,[ecx]
        mov [ebx+edx],al
    .endf
    .if ( edx )
        mov al,[ecx]
        mov [ebx],al
    .endif
    .return( StringBufferEnd )

little_endian endp

output_float proc uses esi opnd:ptr expr, size:dword

  ; v2.07: buffer extended to max size of a data item (=32).
  ; test case: XMMWORD REAL10 ptr 1.0

  local i:int_t
  local buffer[32]:char_t

    assume esi:ptr expr
    mov esi,opnd

    .if ( [esi].mem_type != MT_REAL16 )

        memset( &buffer, 0, sizeof( buffer ) )
        SizeFromMemtype( [esi].mem_type, USE_EMPTY, NULL )
        .if ( eax > size )
            asmerr( 2156 )
        .else
            quad_resize( esi, eax )
        .endif
        OutputDataBytes( &[esi].chararray, size )
    .else
         .if ( size != 16 )
            quad_resize( esi, size )
         .endif
        OutputDataBytes( &[esi].chararray, size )
    .endif
    ret

output_float endp

;
; initialize a data item or struct member;
; - start_pos: contains tokenarray[] index [in/out]
; - tokenarray[]: token array
;
; - sym:
;   for data item:     label (may be NULL)
;   for struct member: field/member (is never NULL)
;
; - no_of_bytes: size of item in bytes
; - type_sym:
;   for data item:     if != NULL, item is a STRUCT/UNION/RECORD.
;   for struct member: if != NULL, item is a STRUCT/UNION/RECORD/TYPEDEF.
;
; - dup: array size if called by DUP operator, otherwise 1
; - inside_struct: TRUE=inside a STRUCT declaration
; - is_float: TRUE=item is float
; - first: TRUE=first item in a line
;
; the symbol will have its 'isarray' flag set if any of the following is true:
; 1. at least 2 items separated by a comma are used for initialization
; 2. the DUP operator occures
; 3. item size is 1 and a quoted string with len > 1 is used as initializer
;

ifndef __UNIX__
MultiByteToWideChar proto WINAPI :int_t, :int_t, :string_t, :int_t, :ptr word, :int_t
endif

    assume esi:nothing
    assume edi:nothing

data_item proc uses esi edi ebx start_pos:ptr int_t, tokenarray:ptr asm_tok, sym:ptr asym,
        no_of_bytes:uint_32, type_sym:ptr asym, _dup:uint_32,
        inside_struct:int_t, is_float:int_t, first:int_t, _end:int_t

    .new i:int_t
    .new string_len:int_t
    .new total:uint_32 = 0;
    .new initwarn:int_t = FALSE
    .new pchar:string_t
    .new tmp:char_t
    .new fixup_type:fixup_types
    .new fixp:ptr fixup
    .new opndx:expr

    .for ( : _dup : _dup-- )

    mov ecx,start_pos
    mov i,[ecx]
    imul ebx,eax,asm_tok
    add ebx,tokenarray

next_item:

    ; <--- continue scan if a comma has been detected
    ; since v1.94, the expression evaluator won't handle strings
    ; enclosed in <> or {}. That is, in previous versions syntax
    ; "mov eax,<1>" was accepted, now it's rejected.

    .if ( [ebx].token == T_STRING && \
        ( [ebx].string_delim == '<' || [ebx].string_delim == '{' ) )

        mov esi,type_sym
        .if ( esi )

            ; it's either a real data item - then inside_struct is FALSE -
            ; or a structure FIELD of arbitrary type.
            ;
            ; v2.10: regression in v2.09: alias types weren't skipped for
            ; InitStructuredVar()

            .while ( [esi].asym.type )
                mov esi,[esi].asym.type
            .endw
            mov type_sym,esi
            .if ( inside_struct == FALSE )
                .if ( InitStructuredVar( i, tokenarray, esi, NULL ) == ERROR )
                    .return
                .endif
            .else

                ; v2.09: emit a warning if a TYPEDEF member is a simple type,
                ; but is initialized with a literal.
                ; Note: Masm complains about such literals only if the struct
                ; is instanced OR -Fl is set.
                ; fixme: the best solution is to always set type_sym to NULL if
                ; the type is a TYPEDEF. if the item is a struct member, then
                ; sym is ALWAYS != NULL and the symbol's type can be gained from
                ; there.
                ; v2.10: aliases are now already skipped here ( see above ).

                .if( [esi].asym.typekind == TYPE_TYPEDEF && Parse_Pass == PASS_1 )
                    asmerr( 8001, [ebx].tokpos )
                .endif
            .endif

            inc total
            inc i
            jmp item_done
        .endif
    .endif

    .if ( [ebx].token == T_QUESTION_MARK )
        mov opndx.kind,EXPR_EMPTY
    .else
        .if ( EvalOperand( &i, tokenarray, _end, &opndx, 0 ) == ERROR )
            .return( ERROR )
        .endif
        imul ebx,i,asm_tok
        add ebx,tokenarray
    .endif

    ; handle DUP operator

    .if ( [ebx].token == T_RES_ID && [ebx].tokval == T_DUP )
        .if ( opndx.kind != EXPR_CONST )
            mov ecx,opndx.sym
            .if ( ecx && [ecx].asym.state == SYM_UNDEFINED )
                asmerr( 2006, [ecx].asym.name )
            .else
                asmerr( 2026 )
            .endif
            .return( ERROR )
        .endif

        ; max dup is 0x7fffffff

        .if ( opndx.value < 0 )
            .return( asmerr( 2092 ) )
        .endif
        inc i
        add ebx,16
        .if( [ebx].token != T_OP_BRACKET )
            .return( asmerr( 2065, "(" ) )
        .endif
        inc i
        add ebx,16

        mov eax,sym
        .if ( eax )
            or [eax].asym.flag1,S_ISARRAY
        .endif

        .if ( opndx.value == 0 )
            mov ecx,1
            .for ( : [ebx].token != T_FINAL : i++, ebx += 16 )
                .if ( [ebx].token == T_OP_BRACKET )
                    inc ecx;
                .elseif ( [ebx].token == T_CL_BRACKET )
                    dec ecx
                .endif
                 .break .if ( ecx == 0 )
            .endf
        .else
            .if ( data_item( &i, tokenarray, sym, no_of_bytes, type_sym,
                    opndx.uvalue, inside_struct, is_float, first, _end ) == ERROR )
                .return
            .endif
            imul ebx,i,asm_tok
            add ebx,tokenarray
        .endif
        .if( [ebx].token != T_CL_BRACKET )
            .return( asmerr( 2065, ")" ) )
        .endif

        ; v2.09: SIZE and LENGTH actually don't return values for
        ; "first initializer, but the "first dimension" values
        ; v2.11: fixme: if the first dimension is 0 ( opndx.value == 0),
        ; Masm ignores the expression - may be a Masm bug!

        mov ecx,sym
        .if ( ecx && first && Parse_Pass == PASS_1 )

            mov eax,opndx.value
            mov [ecx].asym.first_length,eax
            mul no_of_bytes
            mov [ecx].asym.first_size,eax
            mov first,FALSE
        .endif

        inc i
        jmp item_done
    .endif

    ; a STRUCT/UNION/RECORD data item needs a literal as initializer

    mov ecx,type_sym
    .if( ecx )
        .while ( [ecx].asym.type )
            mov ecx,[ecx].asym.type
        .endw
        .if ( [ecx].asym.typekind != TYPE_TYPEDEF )
            .return( asmerr( 2179, [ecx].asym.name ) )
        .endif
    .endif

    ; handle '?'

    .if ( opndx.kind == EXPR_EMPTY && [ebx].token == T_QUESTION_MARK )
        mov opndx.uvalue,no_of_bytes

        ; tiny optimization for uninitialized arrays

        mov ecx,start_pos
        mov edx,i
        .if ( [ebx+16].token != T_COMMA && edx == [ecx] )
            mul _dup
            mov opndx.uvalue,eax
            add total,_dup
            mov _dup,1 ;; force loop exit
        .else
            inc total
        .endif
        .if( !inside_struct )
            SetCurrOffset( CurrSeg, opndx.uvalue, TRUE, TRUE )
        .endif
        inc i
        jmp item_done
    .endif

    ; warn about initialized data in BSS/AT segments

    .if ( Parse_Pass == PASS_2 && inside_struct == FALSE && \
          initwarn == FALSE )

        mov ecx,CurrSeg
        mov ecx,[ecx].dsym.seginfo
        .if ( [ecx].seg_info.segtype == SEGTYPE_BSS || \
              [ecx].seg_info.segtype == SEGTYPE_ABS )

            lea eax,@CStr("AT")
            .if ( [ecx].seg_info.segtype == SEGTYPE_BSS )
                lea eax,@CStr("BSS")
            .endif
            asmerr( 8006, eax )
            mov initwarn,TRUE
        .endif
    .endif

    mov eax,opndx.kind
    .switch( eax )
    .case EXPR_EMPTY
        .if ( [ebx].token != T_FINAL )
            asmerr( 2008, [ebx].tokpos )
        .else
            asmerr( 2008, "" )
        .endif
        .return
    .case EXPR_FLOAT
        .if ( !inside_struct )
            output_float( &opndx, no_of_bytes )
        .endif
        inc total
        .endc
    .case EXPR_CONST
        .if ( is_float )
            .return( asmerr( 2187 ) )
        .endif

        ; a string returned by the evaluator (enclosed in quotes!)?

        .if ( opndx.quoted_string )

            mov ecx,opndx.quoted_string
            mov esi,[ecx].asm_tok.string_ptr
            inc esi
            mov edi,sym

            mov string_len,[ecx].asm_tok.stringlen ;; this is the length without quotes

            ; v2.07: check for empty string for ALL types

            .if ( eax == 0 )
                .if ( inside_struct )

                    ; when the struct is declared, it's no error -
                    ; but won't be accepted when the struct is instanced.
                    ; v2.07: don't modify string_len! Instead
                    ; mark field as array!

                    or [edi].asym.flag1,S_ISARRAY
                .else
                    .return( asmerr( 2047 ) ) ;; MASM doesn't like ""
                .endif
            .endif

            ; a string is only regarded as an array if item size is 1
            ; else it is regarded as ONE item

            .if ( no_of_bytes != 1 )
                .if ( eax > no_of_bytes )

                    ; v2.22 - unicode
                    ; v2.23 - use L"Unicode"

                    .if ( inside_struct || !( ( ModuleInfo.strict_masm_compat == 0 ) && \
                           ( ModuleInfo.xflag & ( OPT_WSTRING or OPT_LSTRING ) ) && \
                         no_of_bytes == 2 ) )

                        .return( asmerr( 2071 ) )
                    .endif
                .endif
            .endif

            .if ( edi && Parse_Pass == PASS_1 && eax > 0 )
                inc total
                xor ecx,ecx
                .if ( no_of_bytes == 1 && eax > 1 )
                    inc ecx
                .elseif ( ( ModuleInfo.strict_masm_compat == 0 ) \
                        && ( ModuleInfo.xflag & ( OPT_WSTRING or OPT_LSTRING ) ) \
                        && no_of_bytes == 2 && eax > 1 )
                    mov ecx,2
                .endif
                .if ecx
                    dec eax
                    add total,eax
                    or [edi].asym.flag1,S_ISARRAY ; v2.07: added
                    .if ( first )
                        mov [edi].asym.first_length,1
                        mov [edi].asym.first_size,ecx
                        mov first,FALSE ; avoid to touch first_xxx fields below
                    .endif
                .endif
            .endif

            .if ( !inside_struct )

                ; anything bigger than a byte must be stored in little-endian
                ; format -- LSB first
                ; v2.22 - unicode
                ; v2.23 - use L"Unicode"

                .if ( ( ModuleInfo.strict_masm_compat == 0 ) && \
                      ( ModuleInfo.xflag & ( OPT_WSTRING or OPT_LSTRING ) ) && \
                        string_len > 1 && no_of_bytes == 2 )
ifndef __UNIX__
                    mov ecx,string_len
                    lea ecx,[ecx*2+8]
                    mov edi,alloca(ecx)
                    ;; v2.24 - Unicode CodePage
                    .if ( MultiByteToWideChar( ModuleInfo.codepage, 0,
                            esi, string_len, edi, string_len ) )
                        add eax,eax
                        OutputBytes( edi, eax, NULL )
                    .else
                        xor edi,edi
                    .endif
endif
                    .if ( edi == NULL )
                        mov edi,string_len
                        .while ( edi )
                            OutputBytes( esi, 1, NULL )
                            FillDataBytes( 0, 1 )
                            inc esi
                            dec edi
                        .endw
                    .endif
                .else
                    .if ( string_len > 1 && no_of_bytes > 1 )
                        mov esi,little_endian( esi, string_len )
                    .endif
                    OutputDataBytes( esi, string_len )
                .endif
                .if ( no_of_bytes > string_len )
                    mov eax,no_of_bytes
                    sub eax,string_len
                    FillDataBytes( 0, eax )
                .endif
            .endif
        .else

            ; it's NOT a string

            .if ( !inside_struct )

                ; the evaluator cannot handle types with size > 16.
                ; so if a (simple) type is larger ( YMMWORD? ),
                ; clear anything which is above.

                .if ( no_of_bytes > 16 )
                    OutputDataBytes( &opndx.chararray, 16 )
                    mov ecx,0xFF
                    .if ( opndx.chararray[15] < 0x80 )
                        xor ecx,ecx
                    .endif
                    mov edx,no_of_bytes
                    sub edx,16
                    FillDataBytes( cl, edx )
                .else
                    .if ( no_of_bytes > sizeof( int_64 ) )
                        ;; set __int128 to negative
                        xor eax,eax
                        .if ( opndx.flags & E_NEGATIVE && \
                              opndx.chararray[7] & 0x80 && \
                              opndx.h64_l == eax && opndx.h64_h == eax )
                            dec eax
                            mov opndx.h64_l,eax
                            mov opndx.h64_h,eax
                        .endif
                    .endif
                    OutputDataBytes( &opndx.chararray, no_of_bytes )

                    ; check that there's no significant data left
                    ; which hasn't been emitted.

                    .if ( no_of_bytes <= sizeof( int_64 ) )
                        mov eax,0xFF
                        .if ( opndx.chararray[7] < 0x80 )
                            xor eax,eax
                        .endif
                        lea edi,opndx.chararray
                        mov ecx,no_of_bytes
                        rep stosb
                        mov eax,opndx.l64_l
                        mov edx,opndx.l64_h
                        .if ( ( eax || edx ) && eax != -1 && edx != -1 )
                            .return( AsmerrSymName( 2071, opndx.sym ) )
                        .endif
                    .elseif ( no_of_bytes == 10 )
                        .if ( ( opndx.h64_h != 0 || opndx.h64_l > 0xffff ) && \
                              opndx.h64_h <= -1 && opndx.h64_l < -0xffff )
                            .return( AsmerrSymName( 2071, opndx.sym ) )
                        .endif
                    .endif
                .endif
            .endif
            inc total
        .endif
        .endc
    .case EXPR_ADDR

        ; since a fixup will be created, 8 bytes is max.
        ; there's no way to define an initialized tbyte "far64" address,
        ; because there's no fixup available for the selector part.

        .if ( no_of_bytes > sizeof(uint_64) )
            AsmerrSymName( 2104, sym )
            .endc
        .endif

        ; indirect addressing (incl. stack variables) is invalid

        .if ( opndx.flags & E_INDIRECT )
            asmerr( 2032 )
            .endc
        .endif
        .if ( ModuleInfo.Ofssize != USE64 )
            .if ( opndx.hvalue && ( opndx.hvalue != -1 || opndx.value >= 0 ) )
                .return( EmitConstError( &opndx ) )
            .endif
        .endif

        .if ( is_float )
            asmerr( 2187 )
            .endc
        .endif

        inc total

        ; for STRUCT fields, don't emit anything!

        .endc .if ( inside_struct )

        ; determine what type of fixup is to be created

        mov eax,opndx.inst
        xor edi,edi
        mov esi,opndx.sym
        .switch ( eax )
        .case T_SEG
            .if ( no_of_bytes < 2 )
                asmerr( 2071 )
            .endif
            mov edi,FIX_SEG
            .endc
        .case T_OFFSET
            mov eax,no_of_bytes
            .switch ( eax )
            .case 1
                ; forward reference?
                .if ( Parse_Pass == PASS_1 && esi && [esi].asym.state == SYM_UNDEFINED )
                    mov edi,FIX_VOID ; v2.10: was regression in v2.09
                .else
                    asmerr( 2071 )
                    mov edi,FIX_OFF8
                .endif
                .endc
            .case 2
                mov edi,FIX_OFF16
                .endc
            .case 8
                .if ( ModuleInfo.Ofssize == USE64 )
                    mov edi,FIX_OFF64
                    .endc
                .endif
            .default
                mov edi,FIX_OFF32
                .if ( esi )
                    .if ( GetSymOfssize(esi) == USE16 )
                        mov edi,FIX_OFF16
                    .endif
                .endif
                .endc
            .endsw
            .endc
        .case T_IMAGEREL
            .if ( no_of_bytes < sizeof(uint_32) )
                asmerr( 2071 )
            .endif
            mov edi,FIX_OFF32_IMGREL
            .endc
        .case T_SECTIONREL
            .if ( no_of_bytes < sizeof(uint_32) )
                asmerr( 2071 )
            .endif
            mov edi,FIX_OFF32_SECREL
            .endc
        .case T_DOT_LOW
            mov edi,FIX_OFF8    ; OMF, BIN + GNU-ELF only
            .endc
        .case T_DOT_HIGH
            mov edi,FIX_HIBYTE  ; OMF only
            .endc
        .case T_LOWWORD
            mov edi,FIX_OFF16
            .if ( no_of_bytes < 2 )
                asmerr( 2071 )
            .endif
            .endc
        .case T_HIGH32
            ; no break
        .case T_HIGHWORD
            mov edi,FIX_VOID
            asmerr( 2026 )
            .endc
        .case T_LOW32
            mov edi,FIX_OFF32
            .if ( no_of_bytes < 4 )
                asmerr( 2071 )
            .endif
            .endc
        .default
            ; size < 2 can work with T_LOW|T_HIGH operator only
            .if ( no_of_bytes < 2 )
                ; forward reference?
                .if ( Parse_Pass == PASS_1 && esi && [esi].asym.state == SYM_UNDEFINED )
                    ;
                .else
                    .if ( esi && [esi].asym.state == SYM_EXTERNAL && opndx.flags & E_IS_ABS )
                    .else
                        asmerr( 2071 )
                    .endif
                    mov edi,FIX_OFF8
                    .endc
                .endif
            .endif

            ; if the symbol references a segment or group,
            ; then generate a segment fixup.

            .if ( esi && ( [esi].asym.state == SYM_SEG || [esi].asym.state == SYM_GRP ) )
                mov edi,FIX_SEG
                .endc
            .endif
            .switch ( no_of_bytes )
            .case 2

                ; accept "near16" override, else complain
                ; if symbol's offset is 32bit

                .if ( opndx.flags & E_EXPLICIT )
                    .if ( SizeFromMemtype( opndx.mem_type, opndx.Ofssize,
                            opndx.type ) > no_of_bytes )
                        AsmerrSymName( 2071, esi )
                    .endif
                .elseif ( esi && [esi].asym.state == SYM_EXTERNAL && opndx.flags & E_IS_ABS )
                .elseif ( esi && [esi].asym.state != SYM_UNDEFINED )
                    .if ( GetSymOfssize( esi ) > USE16 )
                        AsmerrSymName( 2071, esi )
                    .endif
                .endif
                mov edi,FIX_OFF16
                .endc
            .case 4

                ; masm generates:
                ; off32 if curr segment is 32bit,
                ; ptr16 if curr segment is 16bit,
                ; and ignores type overrides.
                ; if it's a NEAR external, size is 16, and
                ; format isn't OMF, error 'symbol type conflict'
                ; is displayed

                .if ( opndx.flags & E_EXPLICIT )
                    .if ( opndx.mem_type == MT_FAR )
                        .if ( opndx.Ofssize != USE_EMPTY && opndx.Ofssize != USE16 )
                            AsmerrSymName( 2071, esi )
                        .endif
                        mov edi,FIX_PTR16
                    .elseif ( opndx.mem_type == MT_NEAR )
                        mov edi,FIX_OFF32
                        .if ( opndx.Ofssize == USE16 )
                            mov edi,FIX_OFF16
                        .elseif ( esi )
                            .if ( GetSymOfssize( esi ) == USE16 )
                                mov edi,FIX_OFF16
                            .endif
                        .endif
                    .endif
                .else

                    ; what's done if code size is 16 is Masm-compatible.
                    ; It's not very smart, however.
                    ; A better strategy is to choose fixup type depending
                    ; on the symbol's offset size.

                    .if ( ModuleInfo.Ofssize == USE16 )
                        .if ( opndx.mem_type == MT_NEAR && \
                            ( Options.output_format == OFORMAT_COFF || \
                              Options.output_format == OFORMAT_ELF ) )
                            mov edi,FIX_OFF16
                            AsmerrSymName( 2004, sym )
                        .else
                            mov edi,FIX_PTR16
                        .endif
                    .else
                        mov edi,FIX_OFF32
                    .endif
                .endif
                .endc
            .case 6

                ; Masm generates a PTR32 fixup in OMF!
                ; and a DIR32 fixup in COFF.

                ; COFF/ELF has no far fixups

                .if ( Options.output_format == OFORMAT_COFF || \
                      Options.output_format == OFORMAT_ELF )
                    mov edi,FIX_OFF32
                .else
                    mov edi,FIX_PTR32
                .endif
                .endc
            .default

                ; Masm generates
                ; off32 if curr segment is 32bit
                ; ptr16 if curr segment is 16bit
                ; JWasm additionally accepts a FAR32 PTR override
                ; and generates a ptr32 fixup then

                .if ( opndx.flags & E_EXPLICIT && opndx.mem_type == MT_FAR && \
                      opndx.Ofssize == USE32 )
                    mov edi,FIX_PTR32
                .elseif( ModuleInfo.Ofssize == USE32 )
                    mov edi,FIX_OFF32
                .elseif( ModuleInfo.Ofssize == USE64 )
                    mov edi,FIX_OFF64
                .else
                    mov edi,FIX_PTR16
                .endif
            .endsw
            .endc
        .endsw
        mov fixup_type,edi

        ; v2.07: fixup type check moved here

        mov eax,1
        mov ecx,edi
        shl eax,cl
        mov ecx,ModuleInfo.fmtopt
        movzx edx,[ecx].format_options.invalid_fixup_type
        .if ( eax & edx )
             lea edx,@CStr("")
             .if esi
                mov edx,[esi].asym.name
             .endif
            .return( asmerr( 3001, &[ecx].format_options.formatname, edx ) )
        .endif
        mov fixp,NULL
        .if ( write_to_file )

            ; there might be a segment override:
            ; a segment, a group or a segment register.
            ; Init var SegOverride, it's used inside set_frame()

            mov SegOverride,NULL
            segm_override( &opndx, NULL )

            ; set global vars Frame and Frame_Datum
            ; opndx.sym may be NULL, then SegOverride is set.

            .if ( ModuleInfo.offsettype == OT_SEGMENT && \
                ( opndx.inst == T_OFFSET || opndx.inst == T_SEG ))
                set_frame2( opndx.sym )
            .else
                set_frame( opndx.sym )
            .endif
            ; uses Frame and Frame_Datum
            mov fixp,CreateFixup( opndx.sym, fixup_type, OPTJ_NONE )
        .endif
        OutputBytes( &opndx.value, no_of_bytes, fixp )
        .endc
    .case EXPR_REG
        asmerr( 2032 )
        .endc
    .default ; unknown opndx.kind, shouldn't happen
        .return( asmerr( 2008, "" ) )
    .endsw

item_done:

    mov ecx,sym
    .if( ecx && first && Parse_Pass == PASS_1 )
        mov eax,total
        mov [ecx].asym.first_length,eax
        mul no_of_bytes
        mov [ecx].asym.first_size,eax
    .endif
    imul ebx,i,asm_tok
    add ebx,tokenarray

    .if ( i < _end && [ebx].token == T_COMMA )
        inc i
        add ebx,16
        .if ( [ebx].token != T_FINAL && [ebx].token != T_CL_BRACKET )
            mov first,FALSE
            .if ( ecx )
                or [ecx].asym.flag1,S_ISARRAY
            .endif
            jmp next_item
        .endif
    .endif

    .endf

    mov ecx,sym
    .if ( ecx && Parse_Pass == PASS_1 )
        mov eax,total
        add [ecx].asym.total_length,eax
        mul no_of_bytes
        add [ecx].asym.total_size,eax
    .endif

    mov ecx,start_pos
    mov [ecx],i
    .return( NOT_ERROR )

data_item endp

checktypes proc sym:ptr asym, mem_type:byte, type_sym:ptr asym

    ; for EXTERNDEF, check type changes

    mov ecx,sym
    mov al,[ecx].asym.mem_type
    .if ( al != MT_EMPTY )

        ; skip alias types

        mov edx,type_sym
        mov ah,mem_type
        .while ( ah == MT_TYPE )
            mov ah,[edx].asym.mem_type
            mov edx,[edx].asym.type
        .endw
        mov edx,ecx
        .while ( al == MT_TYPE )
            mov al,[edx].asym.mem_type
            mov edx,[edx].asym.type
        .endw
        .if ( al != ah )
            .return( asmerr( 2004, [ecx].asym.name ) )
        .endif
    .endif
    .return( NOT_ERROR )

checktypes endp

;
; parse data definition line. Syntax:
; [label] directive|simple type|arbitrary type initializer [,...]
; - directive: DB, DW, ...
; - simple type: BYTE, WORD, ...
; - arbitrary type: struct, union, typedef or record name
; arguments:
; i: index of directive or type
; type_sym: userdef type or NULL
;

    option proc:public

data_dir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok, type_sym:ptr asym

   .new no_of_bytes:uint_32
   .new old_offset:uint_32
   .new currofs:uint_32 ;; for LST output
   .new mem_type:byte
   .new is_float:int_t = FALSE
   .new o:int_t, idx:int_t
   .new name:string_t
   .new type[128]:char_t

    imul ebx,i,asm_tok
    add ebx,tokenarray

    ; v2.05: the previous test in parser.c wasn't fool-proved

    .if ( i > 1 && ModuleInfo.m510 == FALSE )
        .return( asmerr( 2008, [ebx].string_ptr ) )
    .endif
    .if ( [ebx+16].token == T_FINAL )
        .return( asmerr( 2008, [ebx].tokpos ) )
    .endif

    mov o,1
    .if ( [ebx].token == T_BINARY_OPERATOR )

        mov esi,i
        strcpy( &type, "ptr?" )
        .if ( [ebx+16].token != T_QUESTION_MARK && [ebx+16].token != T_NUM )
            inc o
            inc i
            add ebx,16
            .if ( [ebx].token == T_BINARY_OPERATOR )
                strcat( &type, "ptr?" )
                .if ( [ebx+16].token != T_QUESTION_MARK && \
                      [ebx+16].token != T_NUM )
                    inc i
                    inc o
                    add ebx,16
                .endif
            .endif
            .if ( [ebx].token != T_QUESTION_MARK && \
                  [ebx].token != T_NUM )
                strcat( &type, [ebx].string_ptr )
            .endif
        .endif
        .if ( CreateType( esi, tokenarray, &type, &type_sym ) == ERROR )
            .return
        .endif
    .endif

    ; set values for mem_type and no_of_bytes

    mov esi,type_sym
    .if ( esi )

        ; if the parser found a TYPE id, type_sym is != NULL

        mov mem_type,MT_TYPE
        mov edi,[esi].dsym.structinfo
        .if ( [esi].asym.typekind != TYPE_TYPEDEF && \
             ( [esi].asym.total_size == 0 || [edi].struct_info.flags & SI_ORGINSIDE ) )
            .return( asmerr( 2159 ) )
        .endif

        ; v2.09: expand literals inside <> or {}.
        ; Previously this was done inside InitStructuredVar()

        .if ( Parse_Pass == PASS_1 || UseSavedState == FALSE )

            mov ecx,i
            inc ecx
            ExpandLiterals( ecx, tokenarray )
        .endif

        mov no_of_bytes,[esi].asym.total_size
        .if ( no_of_bytes == 0 )

            ; a void type is not valid

            .if ( [esi].asym.typekind == TYPE_TYPEDEF )
                .return( asmerr( 2004, [esi].asym.name ) )
            .endif
        .endif

    .else

        ; it's either a predefined type or a data directive. For types, the index
        ; into the simpletype table is in <bytval>, for data directives
        ; the index is found in <sflags>.
        ; v2.06: SimpleType is obsolete. Use token index directly!

        mov eax,[ebx].tokval
        .if ( [ebx].token == T_STYPE )
        .elseif ( [ebx].token == T_DIRECTIVE && ( [ebx].dirtype == DRT_DATADIR ) )
            mov eax,GetSflagsSp( eax )
        .else
            .return( asmerr( 2004, [ebx].string_ptr ) )
        .endif
        mov mem_type,GetMemtypeSp( eax )

        ; types NEAR[16|32], FAR[16|32] and PROC are invalid here

        mov ecx,eax
        and ecx,MT_SPECIAL_MASK
        .if ( cl == MT_ADDRESS )
            .return( asmerr( 2008, [ebx].string_ptr ) )
        .endif
        .if ( eax & MT_FLOAT )
            mov is_float,TRUE
        .endif
        and eax,MT_SIZE_MASK
        inc eax
        mov no_of_bytes,eax
    .endif

    ; if i == 1, there's a (data) label at pos 0.
    ; note: if -Zm is set, a code label may be at pos 0, and i is 2 then.

    mov edx,tokenarray
    mov ecx,[edx].asm_tok.string_ptr
    .if ( i != o )
        xor ecx,ecx
    .endif
    mov name,ecx
    xor esi,esi

    ; in a struct declaration?

    .if ( CurrStruct )

        ; structure parsing is done in the first pass only

        .if ( Parse_Pass == PASS_1 )

            mov esi,CreateStructField( i, tokenarray, name, mem_type, type_sym, no_of_bytes )
            .if ( eax == NULL )
                .return( ERROR )
            .endif
            .if ( StoreState )
                FStoreLine(0)
            .endif
            mov currofs,[esi].asym.offs
            or [esi].asym.flag1,S_ISDATA ; 'first_size' is valid

        .else ; v2.04: else branch added

            mov edx,CurrStruct
            mov edi,[edx].dsym.structinfo
            mov esi,[edi].struct_info.tail
            mov currofs,[esi].asym.offs
            mov [edi].struct_info.tail,[esi].sfield.next
        .endif

    .else

        .if ( CurrSeg == NULL )
            .return( asmerr( 2034 ) )
        .endif

        FStoreLine(0)

        .if ( ModuleInfo.CommentDataInCode )
            omf_OutSelect( TRUE )
        .endif

        .if ( ModuleInfo.list )
            mov currofs,GetCurrOffset()
        .endif

        ; is a label accociated with the data definition?

        .if ( name )

            ; get/create the label.

            mov name,NameSpace(name, name)
            mov esi,SymLookup( name )
            .if ( Parse_Pass == PASS_1 )

                .if ( [esi].asym.state == SYM_EXTERNAL && \
                      [esi].asym.sflags & S_WEAK && \
                      !( [esi].asym.flag1 & S_ISPROC ) ) ;; EXTERNDEF?
                    checktypes( esi, mem_type, type_sym )
                    sym_ext2int( esi )
                    mov [esi].asym.total_size,0
                    mov [esi].asym.total_length,0
                    mov [esi].asym.first_length,0

                .elseif ( [esi].asym.state == SYM_UNDEFINED )

                    sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], esi )
                    mov [esi].asym.state,SYM_INTERNAL

                    ; v2.11: Set the symbol's langtype. It may have been set
                    ; by a PUBLIC directive, so take care not to overwrite it.
                    ; Problem: Masm doesn't do this - might be a bug.

                    .if ( [esi].asym.langtype == LANG_NONE )
                        mov [esi].asym.langtype,ModuleInfo.langtype
                    .endif
                .elseif ( [esi].asym.state == SYM_INTERNAL)

                    ; accept a symbol "redefinition" if addresses and types
                    ; do match.

                    mov ecx,GetCurrOffset()
                    .if ( [esi].asym.segm != CurrSeg || \
                          [esi].asym.offs != ecx )
                        .return( asmerr(2005, name ) )
                    .endif

                    ; check for symbol type conflict

                    .if ( checktypes( esi, mem_type, type_sym ) == ERROR )
                        .return( ERROR )
                    .endif

                    ; v2.09: reset size and length ( might have been set by LABEL directive )

                    mov [esi].asym.total_size,0
                    mov [esi].asym.total_length,0
                    jmp label_defined ; don't relink the label

                .else
                    .return( asmerr( 2005, [esi].asym.name ) )
                .endif

                ; add the label to the linked list attached to curr segment
                ; this allows to reduce the number of passes (see Fixup.c)

                mov ecx,CurrSeg
                mov edx,[ecx].dsym.seginfo
                mov eax,[edx].seg_info.label_list
                mov [esi].dsym.next,eax
                mov [edx].seg_info.label_list,esi
            .else
                mov old_offset,[esi].asym.offs
            .endif

        label_defined:

            SetSymSegOfs( esi )
            .if( Parse_Pass != PASS_1 && [esi].asym.offs != old_offset )
                mov ModuleInfo.PhaseError,TRUE
            .endif
            or  [esi].asym.flags,S_ISDEFINED
            or  [esi].asym.flag1,S_ISDATA
            mov [esi].asym.mem_type,mem_type
            mov [esi].asym.type,type_sym

            ; backpatch for data items? Yes, if the item is defined
            ; in a code segment then its offset may change!

            BackPatch( esi )
        .endif

        mov edi,type_sym
        .if ( edi )
            .while ( [edi].asym.mem_type == MT_TYPE )
                mov edi,[edi].asym.type
            .endw

            ; if it is just a type alias, skip the arbitrary type

            .if ( [edi].asym.typekind == TYPE_TYPEDEF )
                mov type_sym,NULL
            .endif
        .endif
    .endif
    inc i
    xor ecx,ecx
    cmp ecx,CurrStruct
    setnz cl
    .if ( data_item( &i, tokenarray, esi, no_of_bytes, type_sym, 1, ecx,
            is_float, TRUE, Token_Count ) == ERROR )
        .return
    .endif

    imul ebx,i,asm_tok
    add ebx,tokenarray
    .if ( [ebx].token != T_FINAL )
        .return( asmerr(2008, [ebx].tokpos ) )
    .endif

    ; v2.06: update struct size after ALL items have been processed

    .if ( CurrStruct )
        UpdateStructSize( esi )
    .endif

    .if ( ModuleInfo.list )
        mov ecx,LSTTYPE_DATA
        .if ( CurrStruct )
            mov ecx,LSTTYPE_STRUCT
        .endif
        LstWrite( ecx, currofs, esi )
    .endif
    .return( NOT_ERROR )

data_dir endp

    end
