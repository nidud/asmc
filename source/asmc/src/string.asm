; STRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; string macro processing routines.
;

include malloc.inc
include asmc.inc
include memalloc.inc
include parser.inc
include expreval.inc
include equate.inc
include input.inc
include tokenize.inc
include macro.inc
include condasm.inc
include fastpass.inc
include listing.inc
include segment.inc
include lqueue.inc
include qfloat.inc

externdef list_pos:DWORD

GetTypeId proto :string_t, :ptr asm_tok

;; Stact for "quoted strings" and floats

str_item    struc byte
string      string_t ?
count       dd ?
next        dd ?
index       dw ?
unicode     db ?
flags       db ?
str_item    ends

flt_item    struc
string      string_t ?
count       int_t ?
next        ptr_t ?
index       int_t ?
flt_item    ends

    .code

    B equ <byte ptr>
    W equ <word ptr>
    D equ <dword ptr>

ParseCString proc private uses esi edi ebx lbuf:string_t, buffer:string_t, string:string_t,
        pStringOffset:string_t, pUnicode:ptr byte

  local sbuf:ptr char_t,   ; "binary" string
        Unicode:char_t

    mov sbuf,alloca(ModuleInfo.max_line_len)
    mov esi,string
    mov edi,buffer
    mov edx,sbuf
    xor ebx,ebx
    mov [edx],ebx

    xor eax,eax
    .if ModuleInfo.xflag & OPT_WSTRING

        mov eax,1
    .endif
    .if W[esi] == '"L'

        or  ModuleInfo.xflag,OPT_LSTRING
        mov eax,1
        add esi,1
    .endif
    mov ecx,pUnicode
    mov [ecx],al
    mov Unicode,al
    movsb

    .while B[esi]

        mov al,[esi]
        .if al == '\'

            ; escape char \\

            add esi,1
            mov al,[esi]
            sub al,'A'
            cmp al,'Z' - 'A' + 1
            sbb ah,ah
            and ah,'a' - 'A'
            add al,ah
            add al,'A'
            movzx eax,al

            .switch eax
              .case 'a'
                mov B[edx],7
                mov eax,20372C22h   ; <",7 >
                jmp case_format
              .case 'b'
                mov B[edx],8
                mov eax,20382C22h   ; <",8 >
                jmp case_format
              .case 'f'
                mov B[edx],12
                mov eax,32312C22h   ; <",12>
                jmp case_format
              .case 'n'
                mov B[edx],10
                mov eax,30312C22h   ; <",10>
                jmp case_format
              .case 't'
                mov B[edx],9
                mov eax,20392C22h   ; <",9 >
               case_format:

                mov ecx,buffer
                add ecx,1
                .if ( ecx == edi && al == [edi-1] ) \
                    || ( al == [edi-1] && ah == [edi-2] )
                    shr eax,16
                    sub edi,1
                    stosw
                .else
                    stosd
                .endif
                mov eax,222Ch
                .if BYTE PTR [edi-1] == ' '
                    sub edi,1
                .endif
                stosb
                mov [edi],ah
                .endc

              .case 'r'
                mov B[edx],13
                mov eax,33312C22h   ; <",13>
                jmp case_format
              .case 'v'
                mov B[edx],11
                mov eax,31312C22h   ; <",11>
                jmp case_format
              .case 27h
                mov B[edx],39
                mov eax,39332C22h   ; <",39>
                jmp case_format

              .case 'x'
                .if islxdigit( [esi+1] )

                    add esi,1
                    and eax,not 30h
                    bt  eax,6
                    sbb ecx,ecx
                    and ecx,55
                    sub eax,ecx
                    movzx ecx,B[esi+1]

                    .if _ltype[ecx+1] & _HEX

                        add esi,1
                        shl eax,4
                        and ecx,not 30h
                        bt  ecx,6
                        sbb ebx,ebx
                        and ebx,55
                        sub ecx,ebx
                        add eax,ecx
                    .endif
                    mov [edi],al
                    mov [edx],al
                .else
                    mov B[edi],'x'
                    mov B[edx],'x'
                .endif
                .endc

              .case '0'
                lea eax,[edi-1]
                .if eax == buffer
                    dec edi
                    mov eax,',0'
                    stosw
                .else
                    mov eax,',0,"'
                    stosd
                .endif
                mov B[edi],'"'
                mov B[edx],0
                .endc

              .case '"'         ; <",'"',">
                mov ah,','
                mov ecx,buffer
                add ecx,1

                ; db '"',xx",'"',0

                .if ( ecx == edi && al == [edi-1] ) \
                    || ( al == [edi-1] && ah == [edi-2] )

                    sub edi,1
                .else
                    stosw
                .endif
                mov eax,2C272227h
                stosd
                mov al,'"'

              .default
                mov [edi],al
                mov [edx],al
                .endc
            .endsw

        .elseif al == '"'

            add esi,1
            .for ecx = esi,
                 al = [ecx]: al == ' ' || al == 9: ecx++, al = [ecx]
            .endf
            .if al == 'L' && B[ecx+1] == '"'
                inc ecx
                mov al,'"'
            .endif
            .if al == '"' ; "string1" "string2"
                mov esi,ecx
                dec edi
                dec edx
            .else
                mov eax,'"'
                stosb
                .break
            .endif
        .else
            mov [edi],al
            mov [edx],al
        .endif
        add edi,1
        add edx,1
        .if B[esi]

            add esi,1
        .endif
    .endw

    xor eax,eax
    mov [edi],al
    mov [edx],al
    .if D[edi-3] == 22222Ch
        mov B[edi-3],0
    .endif

    mov eax,pStringOffset
    mov [eax],esi

    assume esi:ptr str_item
    mov eax,sbuf
    sub edx,eax
    .for ebx = edx, edi = 0,
         esi = ModuleInfo.StrStack : esi : edi++, esi = [esi].next

        mov cl,[esi].unicode
        mov eax,[esi].count

        .if eax >= ebx && cl == Unicode

            mov edx,[esi].string

            .if eax > ebx

                add edx,eax ; to end of string
                sub edx,ebx
            .endif

            .if !memcmp( sbuf, edx, ebx )

                movzx eax,[esi].index
                sub edx,[esi].string
                .if edx
                    .if Unicode
                        add edx,edx
                    .endif
                    tsprintf( lbuf, "DS%04X[%d]", eax, edx )
                .else
                    tsprintf( lbuf, "DS%04X", eax )
                .endif
                .return 0
            .endif
        .endif
    .endf

    tsprintf(lbuf, "DS%04X", edi)
    LclAlloc(&[ebx+str_item+1])
    mov [eax].str_item.count,ebx
    mov [eax].str_item.index,di
    mov cl,Unicode
    mov [eax].str_item.unicode,cl
    mov [eax].str_item.flags,0
    mov ecx,ModuleInfo.StrStack
    mov [eax].str_item.next,ecx
    mov ModuleInfo.StrStack,eax
    lea ecx,[eax+str_item]
    mov [eax].str_item.string,ecx
    memcpy(ecx, sbuf, &[ebx+1])
    ret

ParseCString endp

    assume esi:nothing

GetCurrentSegment proc private buffer:string_t

    mov eax,ModuleInfo.currseg
    .if eax
        mov ecx,[eax].asym.name
        strcat( strcpy( buffer, ecx ), " segment" )
    .else
        strcpy( buffer, ".code" )
    .endif
    .if ModuleInfo.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
        and ModuleInfo.line_flags,NOT LOF_LISTED
    .endif
    ret

GetCurrentSegment endp

    option cstack:on

GenerateCString proc uses esi edi ebx i, tokenarray:ptr asm_tok

  local rc:             int_t,
        q:              string_t,
        e:              int_t,
        equal:          int_t,
        NewString:      int_t,
        b_label:        string_t,
        b_seg:          string_t,
        b_line:         string_t,
        b_data:         string_t,
        buffer:         string_t,
        StringOffset:   string_t,
        lineflags:      BYTE,
        brackets:       BYTE,
        Unicode:        BYTE

    xor eax,eax
    mov rc,eax

    .return .if ( ModuleInfo.strict_masm_compat )

    ;
    ; need "quote"
    ;
    mov ebx,i
    mov esi,tokenarray
    shl ebx,4
    add ebx,esi
    mov brackets,al
    mov edx,eax
    ;
    ; proc( "", ( ... ), "" )
    ;
    .while [ebx].asm_tok.token != T_FINAL

        mov ecx,[ebx].asm_tok.string_ptr
        movzx ecx,W[ecx]

        .switch cl
        .case 'L'
            .endc .if ch != '"'
        .case '"'
            mov eax,1
            .break
        .case ')'
            .break .if !brackets
            sub brackets,1
            .endc
        .case '('
            add brackets,1
            ;
            ; need one open bracket
            ;
            add edx,1
            .endc
        .endsw
        add ebx,16
    .endw

    .return .if !eax
    xor eax,eax
    .return .if !edx

    inc eax
    mov rc,eax

    mov edi,ModuleInfo.max_line_len
    lea eax,[edi+edi*2+64*2]
    mov buffer,alloca(eax)
    add eax,edi
    mov b_data,eax
    add eax,edi
    mov b_line,eax
    add eax,edi
    mov b_seg,eax
    add eax,64
    mov b_label,eax

    mov edi,LineStoreCurr
    add edi,line_item.line
    strcpy(b_line, edi)
    .if ( Parse_Pass == PASS_1 )
        mov B[edi],';'
        strcmp(eax, [esi].asm_tok.tokpos)
    .else
        xor eax,eax
    .endif
    mov equal,eax
    mov al,ModuleInfo.line_flags
    mov lineflags,al

    .while ( [ebx].asm_tok.token != T_FINAL )

        mov ecx,[ebx].asm_tok.tokpos
        mov ax,[ecx]
        .if al == '"' || ax == '"L'

            mov edi,ecx
            mov esi,ecx
            mov q,ebx
            ;
            ; v2.28 -- token behind may be 'L'
            ;
            .if [ebx-16].asm_tok.token == T_ID
                mov eax,[ebx-16].asm_tok.string_ptr
                mov eax,[eax]
                .if ax == 'L'
                    sub q,16
                    dec esi
                .endif
            .endif
            lea eax,[ebx+16]
            mov e,eax
            ParseCString( b_label, buffer, esi, &StringOffset, &Unicode )

            mov NewString,eax
            mov esi,StringOffset

            .if equal
                ;
                ; strip "string" from LineStoreCurr
                ;
                push esi
                sub esi,edi
                memcpy( b_data, edi, esi )
                mov B[eax+esi],0
                .if strstr( b_line, eax )
                    mov edi,eax
                    lea eax,[edi+esi]
                    SkipSpace(ecx, eax)
                    .if ecx != ',' && ecx != ')'
                        .if strrchr( &[edi+1], '"' )
                            add eax,1
                        .endif
                    .endif
                    .if eax
                        strcpy( b_data, eax )
                        strcpy( edi, "addr " )
                        strcat( edi, b_label )
                        strcat( edi, b_data )
                    .endif
                .endif
                pop esi
            .endif

            .if NewString
                mov eax,buffer
                mov eax,[eax]
                and eax,0x00FFFFFF
                .if eax != '""'
                    .if Unicode
                        lea ecx,@CStr(" %s dw %s,0")
                    .else
                        lea ecx,@CStr(" %s sbyte %s,0")
                    .endif
                    tsprintf(b_data, ecx, b_label, buffer)
                .else
                    .if Unicode
                        lea ecx,@CStr(" %s dw 0")
                    .else
                        lea ecx,@CStr(" %s sbyte 0")
                    .endif
                    tsprintf(b_data, ecx, b_label)
                .endif
            .elseif ModuleInfo.list
                and ModuleInfo.line_flags,NOT LOF_LISTED
            .endif

            mov eax,q
            mov eax,[eax].asm_tok.tokpos
            mov BYTE PTR [eax],0
            mov eax,tokenarray
            mov ecx,[eax].asm_tok.tokpos
            strcat(strcpy( buffer, ecx), "addr ")
            strcat(eax, b_label)
            SkipSpace(ecx, esi)

            .if ecx
                strcat(strcat(eax, " " ), esi)
            .endif

            .if NewString
                GetCurrentSegment(b_seg)
                AddLineQueue( ".data" )
                AddLineQueue( b_data )
                AddLineQueue( "_DATA ends" )
                AddLineQueue( b_seg )
                InsertLineQueue()
            .endif

            strcpy( ModuleInfo.currsource, buffer )
            Tokenize( ModuleInfo.currsource, 0, tokenarray, TOK_DEFAULT )

            mov ModuleInfo.token_count,eax

            mov ecx,ModuleInfo.tokenarray
            sub ebx,tokenarray
            add ebx,ecx
            mov tokenarray,ecx

            imul eax,i,asm_tok
            add eax,ecx
            mov q,eax

        .elseif ( al == ')' )

            .break .if !brackets
            dec brackets
            .break .ifz
        .elseif ( al == '(' )
            inc brackets
        .endif
        add ebx,16
    .endw

    .if ( equal == 0 )
        StoreLine( ModuleInfo.currsource, list_pos, 0 )
    .else
        mov ebx,ModuleInfo.GeneratedCode
        mov ModuleInfo.GeneratedCode,0
        StoreLine( b_line, list_pos, 0 )
        mov ModuleInfo.GeneratedCode,ebx
    .endif
    mov ModuleInfo.line_flags,lineflags
    mov eax,rc
    ret

GenerateCString endp


;; @CStr() macro

CString proc private uses esi edi ebx buffer:string_t, tokenarray:token_t

  local string:         string_t,
        cursrc:         string_t,
        dlabel:         string_t,
        StringOffset:   string_t,
        retval:         int_t,
        Unicode:        byte

    mov ebx,ModuleInfo.max_line_len
    lea eax,[ebx*2+32]
    mov cursrc,alloca(eax)
    add eax,ebx
    mov string,eax
    add eax,ebx
    mov dlabel,eax

    assume ebx:ptr asm_tok

    mov ebx,tokenarray

    ; find first instance of macro in line

    mov edi,tstricmp([ebx].string_ptr, "@CStr")

    .if edi

        .while [ebx].token != T_FINAL

            .if [ebx].token == T_ID

                .break .if !tstricmp([ebx].string_ptr, "@CStr")
            .endif
            add ebx,16
        .endw

        .if [ebx].token == T_FINAL && [ebx+16].token == T_OP_BRACKET
            add ebx,16
        .elseif [ebx].token != T_FINAL
            add ebx,16
        .else
            mov ebx,tokenarray
        .endif
    .endif

    .if ( [ebx].token == T_OP_BRACKET && \
          ( [ebx+asm_tok].token == T_NUM && [ebx+asm_tok*2].token == T_CL_BRACKET ) || \
          ( [ebx+asm_tok].token == '-' && [ebx+asm_tok*2].token == T_NUM && \
            [ebx+asm_tok*3].token == T_CL_BRACKET ) )


        ; return label[-value]

        .new opnd:expr

        .if ( [ebx+asm_tok].token == '-' )
            add ebx,16
        .endif
        add ebx,16

        _atoow( &opnd, [ebx].string_ptr, [ebx].numbase, [ebx].itemlen )

        ; the number must be 32-bit

        .if dword ptr opnd.hlvalue || dword ptr opnd.hlvalue[4]

            asmerr( 2156 )
            .return 0
        .endif
        ;
        ; allow @CStr(-1) --> last index + 1
        ;
        mov ecx,opnd.value
        mov edx,ModuleInfo.StrStack

        .if ( [ebx-asm_tok].token == '-' )
            xor eax,eax
            .if ( edx )
                movzx eax,[edx].str_item.index
            .endif
            add eax,ecx
        .else
            .for ( eax = ecx : eax && edx : eax--, edx=[edx].str_item.next )
            .endf
            .if ( edx == NULL )
                asmerr( 2156 )
                .return 0
            .endif
            movzx eax,[edx].str_item.index
        .endif
        tsprintf(buffer, "DS%04X", eax)
        .return 1
    .endif

    .for : [ebx].token != T_FINAL : ebx += asm_tok

        mov esi,[ebx].tokpos

        ; v2.28 - .data --> .const
        ;
        ; - dq @CStr(L"CONST")
        ; - dq @CStr(ID)

        .if [ebx].token == T_ID && [ebx-16].token == T_OP_BRACKET

            .if SymFind( [ebx].string_ptr )

                mov eax,[eax].asym.string_ptr
                .if BYTE PTR [eax] == '"' || WORD PTR [eax] == '"L'
                    mov esi,eax
                .endif
            .endif
        .endif

        .if BYTE PTR [esi] == '"' || WORD PTR [esi] == '"L'

            ParseCString(dlabel, string, esi, &StringOffset, &Unicode)

            mov esi,eax
            .if edi
                ;.if ( ModuleInfo.Ofssize != USE64 )
                ;    strcpy( buffer, "offset " )
                ;.endif
                strcat( buffer, dlabel )
            .else
                ;
                ; v2.24 skip return value if @CStr is first token
                ;
                mov eax,dlabel
                mov W[eax],' '
            .endif

            .if esi

                mov eax,string
                mov eax,[eax]
                and eax,0x00FFFFFF
                .if eax != '""'
                    .if Unicode
                        lea ecx,@CStr(" %s dw %s,0")
                    .else
                        lea ecx,@CStr(" %s sbyte %s,0")
                    .endif
                    tsprintf(cursrc, ecx, dlabel, string)
                .else
                    .if Unicode
                        lea ecx,@CStr(" %s dw 0")
                    .else
                        lea ecx,@CStr(" %s sbyte 0")
                    .endif
                    tsprintf(cursrc, ecx, dlabel)
                .endif

                ; v2.24 skip .data/.code if already in .data segment

                .if ModuleInfo.line_queue.head
                    RunLineQueue()
                .endif

                assume ebx:ptr asym

                xor esi,esi
                mov ebx,ModuleInfo.currseg
                .if ebx
                    .if tstricmp( [ebx].name, "_DATA" )
                        inc esi
                        AddLineQueue( ".data" )
                    .endif
                .endif
                .if edi && !esi
                    mov esi,2
                    AddLineQueue( ".const" )
                .endif
                AddLineQueue( cursrc )
                .if esi
                    .if !tstricmp( [ebx].name, "CONST" )
                        AddLineQueue( ".const" )
                    .elseif esi == 2
                        AddLineQueue( ".data" )
                    .else
                        AddLineQueue( ".code" )
                    .endif
                .endif
                InsertLineQueue()
            .endif
            .return 1
        .endif
    .endf
    xor eax,eax
    ret

CString ENDP

    option cstack:off

    assume ebx:ptr expr
    assume esi:ptr flt_item

CreateFloat proc uses esi edi ebx size:int_t, opnd:expr_t, buffer:string_t

  local segm[64]:char_t
  local opc:expr

    mov ebx,opnd
    mov opc.llvalue,[ebx].llvalue
    mov opc.hlvalue,[ebx].hlvalue
    .switch size
    .case 4
        .endc .if [ebx].mem_type == MT_REAL4
        mov opc.flags,0
        .if ( [ebx].chararray[15] & 0x80 )
            mov opc.flags,E_NEGATIVE
            and opc.chararray[15],0x7F
        .endif
        __cvtq_ss(&opc, ebx)
        .if ( opc.flags == E_NEGATIVE )
            or opc.chararray[3],0x80
        .endif
        .endc
    .case 8
        .endc .if [ebx].mem_type == MT_REAL8
        mov opc.flags,0
        .if ( [ebx].chararray[15] & 0x80 )
            mov opc.flags,E_NEGATIVE
            and opc.chararray[15],0x7F
        .endif
        __cvtq_sd(&opc, ebx)
        .if ( opc.flags == E_NEGATIVE )
            or opc.chararray[7],0x80
        .endif
        .endc
    .case 10
        __cvtq_ld(&opc, ebx)
        mov dword ptr opc.hlvalue[4],0
        mov word ptr opc.hlvalue[2],0
    .case 16
        .endc
    .endsw

    .for edi = 0, esi = ModuleInfo.FltStack : esi : edi++, esi = [esi].next

        .if size == [esi].count

            mov eax,[esi].string
            mov edx,dword ptr opc.hlvalue[0]
            mov ecx,dword ptr opc.hlvalue[4]

            .if edx == [eax+0x08] && ecx == [eax+0x0C]

                mov edx,opc.value
                mov ecx,opc.hvalue

                .if edx == [eax] && ecx == [eax+0x04]

                    mov eax,[esi].index
                    tsprintf( buffer, "F%04X", eax )
                    .return 1
                .endif
            .endif
        .endif
    .endf

    tsprintf( buffer, "F%04X", edi )
    .if Parse_Pass == PASS_1

        LclAlloc( flt_item+16 )
        mov [eax].flt_item.index,edi
        mov ecx,size
        mov [eax].flt_item.count,ecx
        mov ecx,ModuleInfo.FltStack
        mov [eax].flt_item.next,ecx
        mov ModuleInfo.FltStack,eax
        lea ecx,[eax+flt_item]
        mov [eax].flt_item.string,ecx
        memcpy(ecx, &opc, 16)

        GetCurrentSegment( &segm )

        AddLineQueue( ".data" )
        mov ecx,size
        .if ecx == 10
            mov ecx,16
        .endif
        AddLineQueueX( "align %d", ecx )
        .switch size
        .case 4
            AddLineQueueX( "%s dd 0x%x", buffer, opc.value )
            .endc
        .case 8
            AddLineQueueX( "%s dq 0x%lx", buffer, opc.llvalue )
            .endc
        .case 10
        .case 16
            AddLineQueueX( "%s label real%d", buffer, size )
            AddLineQueueX( "oword 0x%016lx%016lx", opc.hlvalue, opc.llvalue )
            .endc
        .endsw
        AddLineQueue( "_DATA ends" )
        AddLineQueue( &segm )
        InsertLineQueue()
    .endif
    xor eax,eax
    ret

CreateFloat ENDP

    assume esi:nothing
    assume ebx:ptr asm_tok

TextItemError proc uses ebx item:ptr asm_tok

    mov ebx,item
    mov eax,[ebx].string_ptr

    .if ( [ebx].token == T_STRING && B[eax] == '<' )

        .return( asmerr( 2045 ) )
    .endif

    .if ( [ebx].token == T_ID )

        SymSearch( [ebx].string_ptr )

        .if ( eax == NULL || [eax].asym.state == SYM_UNDEFINED )

            .return( asmerr( 2006, [ebx].string_ptr ) )
        .endif
    .endif
    .return( asmerr( 2051 ) )

TextItemError endp


;; CATSTR directive.
;; defines a text equate
;; syntax <name> CATSTR [<string>,...]
;; TEXTEQU is an alias for CATSTR

CatStrDir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local sym:ptr asym

    mov edi,i
    inc edi ;; go past CATSTR/TEXTEQU

    imul ebx,edi,16
    add ebx,tokenarray

    ;; v2.08: don't copy to temp buffer
    ;; check correct syntax and length of items

    .for ( esi = 0 : edi < Token_Count : )

        .if ( [ebx].token != T_STRING || [ebx].string_delim != '<' )
            .return( TextItemError( ebx ) )
        .endif

        ;; v2.08: using tokenarray.stringlen is not quite correct, since some
        ;; chars are stored in 2 bytes (!)

        add esi,[ebx].stringlen
        .if ( esi >= MAX_LINE_LEN )
            .return( asmerr( 2041 ) )
        .endif
        ;; v2.08: don't copy to temp buffer

        inc edi
        add ebx,16
        .if ( [ebx].token != T_COMMA && [ebx].token != T_FINAL )
            .return asmerr(2008, [ebx].string_ptr )
        .endif
        inc edi
        add ebx,16
    .endf

    mov ebx,tokenarray
    mov edi,SymSearch( [ebx].string_ptr )
    .if ( edi == NULL )
        mov edi,SymCreate( [ebx].string_ptr )
    .elseif( [edi].asym.state == SYM_UNDEFINED )

        ;; v2.01: symbol has been used already. Using
        ;; a textmacro before it has been defined is
        ;; somewhat problematic.

        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], edi )
        SkipSavedState() ;; further passes must be FULL!

        ;; v2.21: changed from 8016 to 6005

        asmerr( 6005, [edi].asym.name )
    .elseif( [edi].asym.state != SYM_TMACRO )

        ;; it is defined as something else, get out

        .return( asmerr( 2005, [edi].asym.name ) )
    .endif


    mov [edi].asym.state,SYM_TMACRO
    or  [edi].asym.flags,S_ISDEFINED

    ;; v2.08: reuse string space if fastmem is on

    inc esi
    .if ( [edi].asym.total_size < esi )

        mov [edi].asym.total_size,esi
        mov [edi].asym.string_ptr,LclAlloc( esi )
    .endif

    ;; v2.08: don't use temp buffer

    mov sym,edi
    add ebx,32
    .for ( edx = 2, edi = [edi].asym.string_ptr: edx < Token_Count: edx += 2, ebx += 32 )

        mov ecx,[ebx].stringlen
        mov esi,[ebx].string_ptr
        rep movsb
    .endf
    mov B[edi],0

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_TMACRO, 0, sym )
    .endif
    .return( NOT_ERROR )

CatStrDir endp

;; used by EQU if the value to be assigned to a symbol is text.
;; - sym:   text macro name, may be NULL
;; - name:  identifer ( if sym == NULL )
;; - value: value of text macro ( original line, BEFORE expansion )

SetTextMacro proc uses esi edi ebx tokenarray:ptr asm_tok, sym:ptr asym, name:string_t, value:string_t

    mov edi,sym
    .if ( edi == NULL )
        mov edi,SymCreate( name )
    .elseif ( [edi].asym.state == SYM_UNDEFINED )
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], edi )

        ;; the text macro was referenced before being defined.
        ;; this is valid usage, but it requires a full second pass.
        ;; just simply deactivate the fastpass feature for this module!

        SkipSavedState()

        ;; v2.21: changed from 8016 to 6005

        asmerr( 6005, [edi].asym.name )
    .elseif ( [edi].asym.state != SYM_TMACRO )
        asmerr( 2005, name )
        .return( NULL )
    .endif

    mov [edi].asym.state,SYM_TMACRO
    or  [edi].asym.flags,S_ISDEFINED

    mov ebx,tokenarray
    .if ( [ebx+32].token == T_STRING && [ebx+32].string_delim == '<' )

        ;; the simplest case: value is a literal. define a text macro!
        ;; just ONE literal is allowed

        .if ( [ebx+48].token != T_FINAL )
            asmerr(2008, [ebx+48].tokpos )
            .return( NULL )
        .endif
        mov value,[ebx+32].string_ptr
        mov esi,[ebx+32].stringlen
    .else

        ;; the original source is used, since the tokenizer has
        ;; deleted some information.

        mov esi,strlen( value )
        mov edx,value

        ;; skip trailing spaces

        .for ( : esi : esi-- )
            .break .if !islspace( [edx+esi-1] )
        .endf
    .endif
    lea ecx,[esi+1]
    .if ( [edi].asym.total_size < ecx )
        mov [edi].asym.total_size,ecx
        mov [edi].asym.string_ptr,LclAlloc( ecx )
    .endif
    memcpy( [edi].asym.string_ptr, value, esi )
    mov edx,[edi].asym.string_ptr
    mov B[edx+esi],0
    .return( edi )

SetTextMacro endp

;; create a (predefined) text macro.
;; used to create @code, @data, ...
;; there are 2 more locations where predefined text macros may be defined:
;; - assemble.c, add_cmdline_tmacros()
;; - symbols.c, SymInit()
;; this should be changed eventually.

AddPredefinedText proc name:string_t, value:string_t

    ;; v2.08: ignore previous setting

    .if !SymSearch( name )

        SymCreate( name )
    .endif

    mov [eax].asym.state,SYM_TMACRO
    or  [eax].asym.flags,S_ISDEFINED or S_PREDEFINED
    mov ecx,value
    mov [eax].asym.string_ptr,ecx

    ;; to ensure that a new buffer is used if the string is modified

    mov [eax].asym.total_size,0
    ret

AddPredefinedText endp

;; SubStr()
;; defines a text equate.
;; syntax: name SUBSTR <string>, pos [, size]

SubStrDir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local name:string_t
  local p:string_t
  local pos:int_t
  local cnt:int_t
  local chksize:int_t
  local opndx:expr

    ;; at least 5 items are needed
    ;; 0  1      2      3 4    5   6
    ;; ID SUBSTR SRC_ID , POS [, LENGTH]

    mov ebx,tokenarray
    mov name,[ebx].string_ptr

    inc i ;; go past SUBSTR
    imul eax,i,16
    add ebx,eax

    ;; third item must be a string

    .if ( [ebx].token != T_STRING || [ebx].string_delim != '<' )
        .return( TextItemError( ebx ) )
    .endif
    mov p,[ebx].string_ptr
    mov cnt,[ebx].stringlen

    inc i
    add ebx,16

    .if ( [ebx].token != T_COMMA )
        .return( asmerr( 2008, [ebx].tokpos ) )
    .endif
    inc i

    ;; get pos, must be a numeric value and > 0
    ;; v2.11: flag NOUNDEF added - no forward ref possible

    .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
        .return( ERROR )
    .endif

    ;; v2.04: "string" constant allowed as second argument
    .if ( opndx.kind != EXPR_CONST )
        .return( asmerr( 2026 ) )
    .endif

    ;; pos is expected to be 1-based
    imul ebx,i,16
    add ebx,tokenarray
    mov pos,opndx.value
    .if ( pos <= 0 )
        .return( asmerr( 2090 ) )
    .endif
    .if ( [ebx].token != T_FINAL )
        .if ( [ebx].token != T_COMMA )
            .return( asmerr( 2008, [ebx].tokpos ) )
        .endif
        inc i
        .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
            .return( ERROR )
        .endif
        .if ( opndx.kind != EXPR_CONST )
            .return( asmerr( 2026 ) )
        .endif
        imul ebx,i,16
        add ebx,tokenarray

        mov edi,opndx.value
        .if ( [ebx].token != T_FINAL )
            .return( asmerr(2008, [ebx].string_ptr ) )
        .endif
        .ifs ( edi < 0 )
            .return( asmerr( 2092 ) )
        .endif
        mov chksize,TRUE
    .else
        mov edi,-1
        mov chksize,FALSE
    .endif
    mov ebx,pos
    .if ( ebx > cnt )
        .return( asmerr( 2091, ebx ) )
    .endif
    lea eax,[ebx+edi-1]
    .if ( chksize && eax > cnt )
        .return( asmerr( 2093 ) )
    .endif
    lea eax,[ebx-1]
    add p,eax
    .if ( edi == -1 )
        mov eax,cnt
        sub eax,ebx
        lea edi,[eax+1]
    .endif

    mov esi,SymSearch( name )

    ;; if we've never seen it before, put it in

    .if ( esi == NULL )

        mov esi,SymCreate( name )

    .elseif( [esi].asym.state == SYM_UNDEFINED )

        ;; it was referenced before being defined. This is
        ;; a bad idea for preprocessor text items, because it
        ;; will require a full second pass!

        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], esi )
        SkipSavedState()

        ;; v2.21: changed from 8016 to 6005

        asmerr( 6005, [esi].asym.name )

    .elseif( [esi].asym.state != SYM_TMACRO )

        ;; it is defined as something incompatible, get out

        .return( asmerr( 2005, [esi].asym.name ) )
    .endif

    mov [esi].asym.state,SYM_TMACRO
    or  [esi].asym.flags,S_ISDEFINED
    inc edi
    .if ( [esi].asym.total_size < edi )
        mov [esi].asym.total_size,edi
        mov [esi].asym.string_ptr,LclAlloc(edi)
    .endif
    dec edi
    memcpy( [esi].asym.string_ptr, p, edi )
    mov B[eax+edi],0

    LstWrite( LSTTYPE_TMACRO, 0, esi )
    .return( NOT_ERROR )

SubStrDir endp

;; SizeStr()
;; defines a numeric variable which contains size of a string
;;

SizeStrDir proc uses ebx i:int_t, tokenarray:ptr asm_tok

    .if ( i != 1 )

        imul ebx,i,16
        add  ebx,tokenarray

        .return( asmerr(2008, [ebx].string_ptr ) )
    .endif

    mov ebx,tokenarray
    .if ( [ebx+32].token != T_STRING || [ebx+32].string_delim != '<' )
        .return( TextItemError( &[ebx+32] ) )
    .endif
    .if ( Token_Count > 3 )
        .return( asmerr(2008, [ebx+3*16].string_ptr ) )
    .endif

    .if ( CreateVariable( [ebx].string_ptr, [ebx+32].stringlen ) )
        LstWrite( LSTTYPE_EQUATE, 0, eax )
        .return( NOT_ERROR )
    .endif
    .return( ERROR )

SizeStrDir endp

;; InStr()
;; defines a numeric variable which contains position of substring.
;; syntax:
;; name INSTR [pos,]string, substr

InStrDir proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local opndx:expr
  local start:int_t

    mov start,1

    imul ebx,i,16
    add ebx,tokenarray

    .if ( i != 1)
        .return( asmerr(2008, [ebx].string_ptr ) )
    .endif

    inc i ;; go past INSTR
    add ebx,16

    .if ( [ebx].token != T_STRING || [ebx].string_delim != '<' )
        ;; v2.11: flag NOUNDEF added - no forward reference accepted
        .if ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
            .return( ERROR )
        .endif
        .if ( opndx.kind != EXPR_CONST )
            .return( asmerr( 2026 ) )
        .endif
        mov start,opndx.value
        imul ebx,i,16
        add ebx,tokenarray

        .if ( start <= 0 )

            ;; v2.05: don't change the value. if it's invalid, the result
            ;; is to be 0. Emit a level 3 warning instead.

            asmerr( 7001 )
        .endif

        .if ( [ebx].token != T_COMMA )
            .return( asmerr( 2008, [ebx].tokpos ) )
        .endif
        add ebx,16 ;; skip comma
    .endif

    .if ( [ebx].token != T_STRING || [ebx].string_delim != '<' )
        .return( TextItemError( ebx ) )
    .endif

    ;; to compare the strings, the "visible" format is needed, since
    ;; the possible '!' operators inside the strings is optional and
    ;; must be ignored.

    mov esi,[ebx].string_ptr
    mov edi,[ebx].stringlen

    .if ( start > edi )
        .return( asmerr( 2091, start ) )
    .endif

    add ebx,16
    .if ( [ebx].token != T_COMMA )
        .return( asmerr( 2008, [ebx].tokpos ) )
    .endif
    add ebx,16
    .if ( [ebx].token != T_STRING || [ebx].string_delim != '<' )
        .return( TextItemError( ebx ) )
    .endif
    .if ( [ebx+16].token != T_FINAL )
        .return( asmerr(2008, [ebx+16].string_ptr ) )
    .endif

    mov edx,[ebx].stringlen
    xor eax,eax
    .if ( start > 0 && edi >= edx && edx )
        lea ecx,[esi-1]
        add ecx,start
        .if strstr( ecx, [ebx].string_ptr )
            sub eax,esi
            add eax,1
        .endif
    .endif
    mov ebx,tokenarray
    .if ( CreateVariable( [ebx].string_ptr, eax ) )
        LstWrite( LSTTYPE_EQUATE, 0, eax )
        .return ( NOT_ERROR )
    .endif
    .return( ERROR )
InStrDir endp

;; internal @CatStr macro function
;; syntax: @CatStr( literal [, literal ...] )

CatStrFunc proc private uses esi edi ebx mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok
    mov edi,mi
    .for ( esi = [edi].macro_instance.parm_array,
           esi = [esi]: [edi].macro_instance.parmcnt: [edi].macro_instance.parmcnt-- )
        mov ebx,strlen( esi )
        memcpy( buffer, esi, ebx )
        mov esi,GetAlignedPointer( esi, ebx )
        add buffer,ebx
    .endf
    mov edx,buffer
    mov B[edx],0
    .return( NOT_ERROR )
CatStrFunc endp

ifdef USE_COMALLOC

ComAlloc proto :string_t, :token_t

ComAllocFunc proc private mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok
    .if ( ComAlloc( buffer, tokenarray ) == 0 )
        mov edx,mi
        mov edx,[edx].macro_instance.parm_array
        strcpy( buffer, [edx] )
    .endif
    .return( NOT_ERROR )
ComAllocFunc endp

endif

TypeIdFunc proc private mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok
    .if ( GetTypeId( buffer, tokenarray ) == 0 )
        mov edx,mi
        mov edx,[edx].macro_instance.parm_array
        strcpy( buffer, [edx] )
    .endif
    .return( NOT_ERROR )
TypeIdFunc endp

;; internal @CStr macro function
;; syntax:  @CStr( "\tstring\n" )

CStringFunc proc private mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok
    .if ( CString( buffer, tokenarray ) == 0 )
        mov edx,mi
        mov edx,[edx].macro_instance.parm_array
        strcpy( buffer, [edx] )
    .endif
    .return( NOT_ERROR )
CStringFunc endp

;; convert string to a number.
;; used by @SubStr() for arguments 2 and 3 (start and size),
;; and by @InStr() for argument 1 ( start )

GetNumber proc private string:string_t, pi:ptr int_t, tokenarray:ptr asm_tok

  local opndx:expr
  local i:int_t

    mov ecx,Token_Count
    inc ecx
    mov i,ecx
    mov edx,Tokenize( string, ecx, tokenarray, TOK_RESCAN )
    .if( EvalOperand( &i, tokenarray, edx, &opndx, EXPF_NOUNDEF ) == ERROR )
        .return( ERROR )
    .endif
    imul ecx,i,16
    add ecx,tokenarray
    .if( opndx.kind != EXPR_CONST || [ecx].asm_tok.token != T_FINAL )
        .return( asmerr(2008, string ) )
    .endif
    mov ecx,pi
    mov eax,opndx.value
    mov [ecx],eax
    .return( NOT_ERROR )
GetNumber endp

;; internal @InStr macro function
;; syntax: @InStr( [num], literal, literal )
;; the result is returned as string in current radix

InStrFunc proc private uses esi edi ebx mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok

  local pos:int_t
  local p:string_t
  local found:uint_32

    mov pos,1

    ;; init buffer with "0"

    mov edi,buffer
    mov eax,'0'
    mov [edi],ax

    mov edx,mi
    mov esi,[edx].macro_instance.parm_array
    mov ebx,[esi]

    .if ( ebx )
        .if ( GetNumber( ebx, &pos, tokenarray ) == ERROR )
            .return( ERROR )
        .endif
        .if ( pos == 0 )

            ;; adjust index 0. Masm also accepts 0 (and any negative index),
            ;; but the result will always be 0 then
            inc pos
        .endif
    .endif
    mov ebx,[esi+4]
    .if ( pos > strlen( ebx ) )
        .return( asmerr( 2091, pos ) )
    .endif

    ;; v2.08: if() added, empty searchstr is to return 0
    mov edx,[esi+8]
    .if ( B[edx] != 0 )

        mov ecx,pos
        add ecx,ebx
        dec ecx

        .if strstr( ecx, edx )
            sub eax,ebx
            lea ecx,[eax+1]
            xor edx,edx
            myltoa( edx::ecx, buffer, ModuleInfo.radix, FALSE, TRUE )
        .endif
    .endif

    .return( NOT_ERROR )

InStrFunc endp

;; internal @SizeStr macro function
;; syntax: @SizeStr( literal )
;; the result is returned as string in current radix

SizeStrFunc proc private mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok

    mov eax,mi
    mov edx,[eax].macro_instance.parm_array
    mov ecx,[edx]

    .if ( ecx )
        mov ecx,strlen( ecx )
        xor edx,edx
        myltoa( edx::ecx, buffer, ModuleInfo.radix, FALSE, TRUE )
    .else
        mov edx,buffer
        mov eax,'0'
        mov [edx],ax
    .endif
    .return( NOT_ERROR )

SizeStrFunc endp


;; internal @SubStr macro function
;; syntax: @SubStr( literal, num [, num ] )

SubStrFunc proc private uses esi edi ebx mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok

  local pos:int_t
  local size:int_t

    mov eax,mi
    mov esi,[eax].macro_instance.parm_array
    mov edi,[esi]

    .return( ERROR ) .if ( GetNumber( [esi+4], &pos, tokenarray ) == ERROR )

    .if ( pos <= 0 )

        ;; Masm doesn't check if index is < 0;
        ;; might cause an "internal assembler error".
        ;; v2.09: negative index no longer silently changed to 1.

        .return( asmerr( 2091, pos ) ) .if ( pos )
        mov pos,1
    .endif

    mov ebx,strlen( edi )
    .return( asmerr( 2091, pos ) ) .if ( pos > ebx )

    sub ebx,pos
    inc ebx
    mov edi,[esi+8]

    .if ( edi )

        .new sizereq:int_t
        .return .if ( GetNumber( edi, &sizereq, tokenarray ) == ERROR )
        .return( asmerr( 2092 ) ) .if ( sizereq < 0 )
        .return( asmerr( 2093 ) ) .if ( sizereq > ebx )
        mov ebx,sizereq
    .endif

    mov ecx,[esi]
    add ecx,pos
    sub ecx,1
    memcpy( buffer, ecx, ebx )
    mov B[eax+ebx],0
    .return( NOT_ERROR )

SubStrFunc endp

;; string macro initialization
;; this proc is called once per module

StringInit proc uses esi edi

    assume edi:ptr dsym
    assume esi:ptr macro_info

ifdef USE_COMALLOC

    ; add @ComAlloc() macro func

    mov edi,CreateMacro( "@ComAlloc" )
    mov [edi].flags,S_ISDEFINED or S_PREDEFINED
    mov [edi].func_ptr,ComAllocFunc
    mov [edi].mac_flag,M_ISFUNC
    mov esi,[edi].macroinfo
    mov [esi].parmcnt,1
    mov [esi].parmlist,LclAlloc( sizeof( mparm_list ) )
    mov [eax].mparm_list.deflt,NULL
    mov [eax].mparm_list.required,TRUE

endif

    ; add @TypeId() macro func

    mov edi,CreateMacro( "typeid" )
    mov [edi].flags,S_ISDEFINED or S_PREDEFINED
    mov [edi].func_ptr,TypeIdFunc
    mov [edi].mac_flag,M_ISFUNC
    mov esi,[edi].macroinfo
    mov [esi].parmcnt,2
    mov [esi].parmlist,LclAlloc( sizeof( mparm_list ) * 2 )
    mov [eax].mparm_list.deflt,NULL
    mov [eax].mparm_list.required,FALSE
    mov [eax].mparm_list[mparm_list].deflt,NULL
    mov [eax].mparm_list[mparm_list].required,FALSE

    ;; add @CStr() macro func

    mov edi,CreateMacro( "@CStr" )
    mov [edi].flags,S_ISDEFINED or S_PREDEFINED
    mov [edi].func_ptr,CStringFunc
    mov [edi].mac_flag,M_ISFUNC
    mov esi,[edi].macroinfo
    mov [esi].parmcnt,1
    mov [esi].parmlist,LclAlloc( sizeof( mparm_list ) )
    mov [eax].mparm_list.deflt,NULL
    mov [eax].mparm_list.required,TRUE

    ;; add @CatStr() macro func

    mov edi,CreateMacro( "@CatStr" )
    mov [edi].flags,S_ISDEFINED or S_PREDEFINED
    mov [edi].func_ptr,CatStrFunc
    mov [edi].mac_flag,M_ISFUNC or M_ISVARARG
    mov esi,[edi].macroinfo
    mov [esi].parmcnt,1
    mov [esi].parmlist,LclAlloc( sizeof( mparm_list ) )
    mov [eax].mparm_list.deflt,NULL
    mov [eax].mparm_list.required,FALSE

    ;; add @InStr() macro func

    mov edi,CreateMacro( "@InStr" )
    mov [edi].flags,S_ISDEFINED or S_PREDEFINED
    mov [edi].func_ptr,InStrFunc
    mov [edi].mac_flag,M_ISFUNC
    mov esi,[edi].macroinfo
    mov [esi].parmcnt,3
    mov [esi].autoexp,1
    mov [esi].parmlist,LclAlloc( sizeof( mparm_list ) * 3 )
    mov [eax].mparm_list.deflt,NULL
    mov [eax].mparm_list.required,FALSE
    mov [eax].mparm_list[mparm_list].deflt,NULL
    mov [eax].mparm_list[mparm_list].required,TRUE
    mov [eax].mparm_list[mparm_list*2].deflt,NULL
    mov [eax].mparm_list[mparm_list*2].required,TRUE

    ;; add @SizeStr() macro func

    mov edi,CreateMacro( "@SizeStr" )
    mov [edi].flags,S_ISDEFINED or S_PREDEFINED
    mov [edi].func_ptr,SizeStrFunc
    mov [edi].mac_flag,M_ISFUNC
    mov esi,[edi].macroinfo
    mov [esi].parmcnt,1
    mov [esi].parmlist,LclAlloc( sizeof( mparm_list ) )
    mov [eax].mparm_list.deflt,NULL
    mov [eax].mparm_list.required,FALSE

    ;; add @SubStr() macro func

    mov edi,CreateMacro( "@SubStr" )
    mov [edi].flags,S_ISDEFINED or S_PREDEFINED
    mov [edi].func_ptr,SubStrFunc
    mov [edi].mac_flag,M_ISFUNC
    mov esi,[edi].macroinfo
    mov [esi].parmcnt,3
    mov [esi].autoexp,2 + 4 ;; param 2 (pos) and 3 (size) are expanded
    mov [esi].parmlist,LclAlloc( sizeof( mparm_list ) * 3 )
    mov [eax].mparm_list.deflt,NULL
    mov [eax].mparm_list.required,TRUE
    mov [eax].mparm_list[mparm_list].deflt,NULL
    mov [eax].mparm_list[mparm_list].required,TRUE
    mov [eax].mparm_list[mparm_list*2].deflt,NULL
    mov [eax].mparm_list[mparm_list*2].required,FALSE
    ret

StringInit endp

    end
