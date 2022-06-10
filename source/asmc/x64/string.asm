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

GetTypeId proto __ccall :string_t, :ptr asm_tok

; Stact for "quoted strings" and floats

str_item    struc byte
string      string_t ?
count       dd ?
next        ptr str_item ?
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

ParseCString proc __ccall private uses rsi rdi rbx r12 r13 r14 lbuf:string_t, buffer:string_t, string:string_t,
        pStringOffset:string_t, pUnicode:ptr byte

   .new Unicode:char_t
    mov r14,rdx
    mov rsi,r8

    ; "binary" string
    mov r13,alloca(ModuleInfo.max_line_len)
    mov r12,r13
    mov rdi,r14
    xor ebx,ebx
    mov [r12],rbx

    xor eax,eax
    .if ModuleInfo.xflag & OPT_WSTRING

        mov eax,1
    .endif
    .if W[rsi] == '"L'

        or  ModuleInfo.xflag,OPT_LSTRING
        mov eax,1
        add rsi,1
    .endif
    mov rcx,pUnicode
    mov [rcx],al
    mov Unicode,al
    movsb

    .while B[rsi]

        mov al,[rsi]
        .if al == '\'

            ; escape char \\

            add rsi,1
            mov al,[rsi]
            sub al,'A'
            cmp al,'Z' - 'A' + 1
            sbb ah,ah
            and ah,'a' - 'A'
            add al,ah
            add al,'A'
            movzx eax,al

            .switch eax
              .case 'a'
                mov B[r12],7
                mov eax,20372C22h   ; <",7 >
                jmp case_format
              .case 'b'
                mov B[r12],8
                mov eax,20382C22h   ; <",8 >
                jmp case_format
              .case 'f'
                mov B[r12],12
                mov eax,32312C22h   ; <",12>
                jmp case_format
              .case 'n'
                mov B[r12],10
                mov eax,30312C22h   ; <",10>
                jmp case_format
              .case 't'
                mov B[r12],9
                mov eax,20392C22h   ; <",9 >
               case_format:

                mov rcx,r14
                add rcx,1
                .if ( rcx == rdi && al == [rdi-1] ) \
                    || ( al == [rdi-1] && ah == [rdi-2] )
                    shr eax,16
                    sub rdi,1
                    stosw
                .else
                    stosd
                .endif
                mov eax,222Ch
                .if BYTE PTR [rdi-1] == ' '
                    sub rdi,1
                .endif
                stosb
                mov [rdi],ah
                .endc

              .case 'r'
                mov B[r12],13
                mov eax,33312C22h   ; <",13>
                jmp case_format
              .case 'v'
                mov B[r12],11
                mov eax,31312C22h   ; <",11>
                jmp case_format
              .case 27h
                mov B[r12],39
                mov eax,39332C22h   ; <",39>
                jmp case_format

              .case 'x'
                .if islxdigit( [rsi+1] )

                    add rsi,1
                    and eax,not 30h
                    bt  eax,6
                    sbb ecx,ecx
                    and ecx,55
                    sub eax,ecx
                    movzx ecx,B[rsi+1]

                    .if byte ptr [r15+rcx+1] & _HEX

                        add rsi,1
                        shl eax,4
                        and ecx,not 30h
                        bt  ecx,6
                        sbb ebx,ebx
                        and ebx,55
                        sub ecx,ebx
                        add eax,ecx
                    .endif
                    mov [rdi],al
                    mov [r12],al
                .else
                    mov B[rdi],'x'
                    mov B[r12],'x'
                .endif
                .endc

              .case '0'
                lea rax,[rdi-1]
                .if rax == r14
                    dec rdi
                    mov eax,',0'
                    stosw
                .else
                    mov eax,',0,"'
                    stosd
                .endif
                mov B[rdi],'"'
                mov B[r12],0
                .endc

              .case '"'         ; <",'"',">
                mov ah,','
                mov rcx,r14
                add rcx,1

                ; db '"',xx",'"',0

                .if ( rcx == rdi && al == [rdi-1] ) \
                    || ( al == [rdi-1] && ah == [rdi-2] )

                    sub rdi,1
                .else
                    stosw
                .endif
                mov eax,2C272227h
                stosd
                mov al,'"'

              .default
                mov [rdi],al
                mov [r12],al
                .endc
            .endsw

        .elseif al == '"'

            add rsi,1
            .for rcx = rsi,
                 al = [rcx]: al == ' ' || al == 9: rcx++, al = [rcx]
            .endf
            .if al == 'L' && B[rcx+1] == '"'
                inc rcx
                mov al,'"'
            .endif
            .if al == '"' ; "string1" "string2"
                mov rsi,rcx
                dec rdi
                dec r12
            .else
                mov eax,'"'
                stosb
                .break
            .endif
        .else
            mov [rdi],al
            mov [r12],al
        .endif
        add rdi,1
        add r12,1
        .if B[rsi]

            add rsi,1
        .endif
    .endw

    xor eax,eax
    mov [rdi],al
    mov [r12],al
    .if D[rdi-3] == 22222Ch
        mov B[rdi-3],0
    .endif

    mov rax,pStringOffset
    mov [rax],rsi

    assume rsi:ptr str_item
    mov rbx,r12
    sub rbx,r13
    .for edi = 0,
         rsi = ModuleInfo.StrStack : rsi : edi++, rsi = [rsi].next

        mov cl,[rsi].unicode
        mov eax,[rsi].count

        .if eax >= ebx && cl == Unicode

            mov r12,[rsi].string
            .if eax > ebx

                add r12,rax ; to end of string
                sub r12,rbx
            .endif
            tmemcmp( r13, r12, ebx )

            .if !eax
                movzx eax,[rsi].index
                sub r12,[rsi].string
                .if r12
                    .if Unicode
                        add r12,r12
                    .endif
                    tsprintf( lbuf, "DS%04X[%d]", eax, r12d )
                .else
                    tsprintf( lbuf, "DS%04X", eax )
                .endif
                .return 0
            .endif
        .endif
    .endf

    tsprintf(lbuf, "DS%04X", edi)
    LclAlloc(&[rbx+str_item+1])
    mov [rax].str_item.count,ebx
    mov [rax].str_item.index,di
    mov cl,Unicode
    mov [rax].str_item.unicode,cl
    mov [rax].str_item.flags,0
    mov rcx,ModuleInfo.StrStack
    mov [rax].str_item.next,rcx
    mov ModuleInfo.StrStack,rax
    lea rcx,[rax+str_item]
    mov [rax].str_item.string,rcx
    tmemcpy(rcx, r13, &[rbx+1])
    ret

ParseCString endp

    assume rsi:nothing

GetCurrentSegment proc __ccall private buffer:string_t

    mov rax,ModuleInfo.currseg
    .if rax
        mov rdx,[rax].asym.name
        tstrcat( tstrcpy( rcx, rdx ), " segment" )
    .else
        tstrcpy( rcx, ".code" )
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

GenerateCString proc __ccall uses rsi rdi rbx r12 r13 r14 i:int_t, tokenarray:ptr asm_tok

  local rc:             int_t,
        equal:          int_t,
        NewString:      int_t,
        b_label:        string_t,
        b_seg:          string_t,
        b_line:         string_t,
        b_data:         string_t,
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
    mov rsi,rdx
    imul ebx,ecx,asm_tok
    add rbx,rsi
    mov brackets,al
    mov edx,eax
    ;
    ; proc( "", ( ... ), "" )
    ;
    .while [rbx].asm_tok.token != T_FINAL

        mov rcx,[rbx].asm_tok.string_ptr
        movzx ecx,W[rcx]

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
        add rbx,asm_tok
    .endw

    .return .if !eax
    xor eax,eax
    .return .if !edx

    inc eax
    mov rc,eax

    mov edi,ModuleInfo.max_line_len
    lea eax,[rdi+rdi*2+64*2]
    mov r14,alloca(eax)
    add rax,rdi
    mov b_data,rax
    add rax,rdi
    mov b_line,rax
    add rax,rdi
    mov b_seg,rax
    add rax,64
    mov b_label,rax

    mov edi,line_item.line
    add rdi,LineStoreCurr
    tstrcpy(b_line, rdi)
    .if ( Parse_Pass == PASS_1 )
        mov B[rdi],';'
        tstrcmp(rax, [rsi].asm_tok.tokpos)
    .else
        xor eax,eax
    .endif
    mov equal,eax
    mov al,ModuleInfo.line_flags
    mov lineflags,al

    .while ( [rbx].asm_tok.token != T_FINAL )

        mov rcx,[rbx].asm_tok.tokpos
        mov ax,[rcx]
        .if al == '"' || ax == '"L'

            mov rdi,rcx
            mov rsi,rcx
            mov r12,rbx
            ;
            ; v2.28 -- token behind may be 'L'
            ;
            .if [rbx-asm_tok].asm_tok.token == T_ID
                mov rax,[rbx-asm_tok].asm_tok.string_ptr
                mov eax,[rax]
                .if ax == 'L'
                    sub r12,asm_tok
                    dec rsi
                .endif
            .endif
            ParseCString( b_label, r14, rsi, &StringOffset, &Unicode )

            mov NewString,eax
            mov rsi,StringOffset

            .if equal
                ;
                ; strip "string" from LineStoreCurr
                ;
                mov r13,rsi
                sub r13,rdi
                tmemcpy( b_data, rdi, r13d )
                mov B[rax+r13],0
                .if tstrstr( b_line, rax )
                    mov rdi,rax
                    lea rax,[rdi+r13]
                    tstrstart(rax)
                    .if ecx != ',' && ecx != ')'
                        .if tstrrchr( &[rdi+1], '"' )
                            add rax,1
                        .endif
                    .endif
                    .if rax
                        tstrcpy( b_data, rax )
                        tstrcpy( rdi, "addr " )
                        tstrcat( rdi, b_label )
                        tstrcat( rdi, b_data )
                    .endif
                .endif
            .endif

            .if NewString
                mov eax,[r14]
                and eax,0x00FFFFFF
                .if eax != '""'
                    .if Unicode
                        lea rcx,@CStr(" %s dw %s,0")
                    .else
                        lea rcx,@CStr(" %s sbyte %s,0")
                    .endif
                    tsprintf(b_data, rcx, b_label, r14)
                .else
                    .if Unicode
                        lea rcx,@CStr(" %s dw 0")
                    .else
                        lea rcx,@CStr(" %s sbyte 0")
                    .endif
                    tsprintf(b_data, rcx, b_label)
                .endif
            .elseif ModuleInfo.list
                and ModuleInfo.line_flags,NOT LOF_LISTED
            .endif

            mov rax,[r12].asm_tok.tokpos
            mov BYTE PTR [rax],0

            mov rax,tokenarray
            mov r13,tstrcat(tstrcat(tstrcpy(r14, [rax].asm_tok.tokpos), "addr "), b_label)
            mov rsi,ltokstart(rsi)
            .if ecx
                tstrcat(tstrcat(r13, " " ), rsi)
            .endif

            .if NewString
                GetCurrentSegment(b_seg)
                AddLineQueue( ".data" )
                AddLineQueue( b_data )
                AddLineQueue( "_DATA ends" )
                AddLineQueue( b_seg )
                InsertLineQueue()
            .endif

            tstrcpy( ModuleInfo.currsource, r14 )
            Tokenize( ModuleInfo.currsource, 0, tokenarray, TOK_DEFAULT )

            mov ModuleInfo.token_count,eax

            mov rcx,ModuleInfo.tokenarray
            sub rbx,tokenarray
            add rbx,rcx
            mov tokenarray,rcx

            imul eax,i,asm_tok
            add rax,rcx
            mov r12,rax

        .elseif ( al == ')' )

            .break .if !brackets
            dec brackets
            .break .ifz
        .elseif ( al == '(' )
            inc brackets
        .endif
        add rbx,asm_tok
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
   .return( rc )

GenerateCString endp


; @CStr() macro

CString proc __ccall private uses rsi rdi rbx r12 r13 r14 buffer:string_t, tokenarray:token_t

  local StringOffset:   string_t,
        retval:         int_t,
        Unicode:        byte

    mov rbx,rdx
    mov edi,ModuleInfo.max_line_len
    lea eax,[rdi*2+32]
    mov r13,alloca(eax)
    lea r12,[rax+rdi]
    lea r14,[rax+rdi*2]

    assume rbx:ptr asm_tok

    ; find first instance of macro in line

    mov edi,tstricmp([rbx].string_ptr, "@CStr")

    .if edi

        .while [rbx].token != T_FINAL

            .if [rbx].token == T_ID

                .break .ifd !tstricmp([rbx].string_ptr, "@CStr")
            .endif
            add rbx,asm_tok
        .endw

        .if [rbx].token == T_FINAL && [rbx+asm_tok].token == T_OP_BRACKET
            add rbx,asm_tok
        .elseif [rbx].token != T_FINAL
            add rbx,asm_tok
        .else
            mov rbx,tokenarray
        .endif
    .endif

    .if ( [rbx].token == T_OP_BRACKET && \
          ( [rbx+asm_tok].token == T_NUM && [rbx+asm_tok*2].token == T_CL_BRACKET ) || \
          ( [rbx+asm_tok].token == '-' && [rbx+asm_tok*2].token == T_NUM && \
            [rbx+asm_tok*3].token == T_CL_BRACKET ) )


        ; return label[-value]

        .new opnd:expr

        .if ( [rbx+asm_tok].token == '-' )
            add rbx,asm_tok
        .endif
        add rbx,asm_tok

        _atoow( &opnd, [rbx].string_ptr, [rbx].numbase, [rbx].itemlen )

        ; the number must be 32-bit

        .if dword ptr opnd.hlvalue || dword ptr opnd.hlvalue[4]

            asmerr( 2156 )
            .return 0
        .endif
        ;
        ; allow @CStr(-1) --> last index + 1
        ;
        mov ecx,opnd.value
        mov rdx,ModuleInfo.StrStack

        .if ( [rbx-asm_tok].token == '-' )
            xor eax,eax
            .if ( rdx )
                movzx eax,[rdx].str_item.index
            .endif
            add eax,ecx
        .else
            .for ( eax = ecx : eax && rdx : eax--, rdx=[rdx].str_item.next )
            .endf
            .if ( rdx == NULL )
                asmerr( 2156 )
                .return 0
            .endif
            movzx eax,[rdx].str_item.index
        .endif
        tsprintf(buffer, "DS%04X", eax)
        .return 1
    .endif

    .for : [rbx].token != T_FINAL : rbx += asm_tok

        mov rsi,[rbx].tokpos

        ; v2.28 - .data --> .const
        ;
        ; - dq @CStr(L"CONST")
        ; - dq @CStr(ID)

        .if [rbx].token == T_ID && [rbx-asm_tok].token == T_OP_BRACKET

            .if SymFind( [rbx].string_ptr )

                mov rax,[rax].asym.string_ptr
                .if BYTE PTR [rax] == '"' || WORD PTR [rax] == '"L'
                    mov rsi,rax
                .endif
            .endif
        .endif

        .if BYTE PTR [rsi] == '"' || WORD PTR [rsi] == '"L'

            ParseCString(r14, r12, rsi, &StringOffset, &Unicode)

            mov esi,eax
            .if edi
                ;.if ( ModuleInfo.Ofssize != USE64 )
                ;    tstrcpy( buffer, "offset " )
                ;.endif
                tstrcat( buffer, r14 )
            .else
                ;
                ; v2.24 skip return value if @CStr is first token
                ;
                mov W[r14],' '
            .endif

            .if esi

                mov eax,[r12]
                and eax,0x00FFFFFF
                .if eax != '""'
                    .if Unicode
                        lea rdx,@CStr(" %s dw %s,0")
                    .else
                        lea rdx,@CStr(" %s sbyte %s,0")
                    .endif
                    tsprintf(r13, rdx, r14, r12)
                .else
                    .if Unicode
                        lea rdx,@CStr(" %s dw 0")
                    .else
                        lea rdx,@CStr(" %s sbyte 0")
                    .endif
                    tsprintf(r13, rdx, r14)
                .endif

                ; v2.24 skip .data/.code if already in .data segment

                .if ModuleInfo.line_queue.head
                    RunLineQueue()
                .endif

                assume rbx:ptr asym

                xor esi,esi
                mov rbx,ModuleInfo.currseg
                .if rbx
                    .ifd tstricmp( [rbx].name, "_DATA" )
                        inc esi
                        AddLineQueue( ".data" )
                    .endif
                .endif
                .if edi && !esi
                    mov esi,2
                    AddLineQueue( ".const" )
                .endif
                AddLineQueue( r13 )
                .if esi
                    .ifd !tstricmp( [rbx].name, "CONST" )
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
    .return( 0 )

CString endp

    ;option cstack:off
    assume rbx:ptr expr, rsi:ptr flt_item

CreateFloat proc __ccall uses rsi rdi rbx size:int_t, opnd:expr_t, buffer:string_t

  local segm[64]:char_t
  local opc:expr

    mov rbx,rdx
    mov opc.llvalue,[rbx].llvalue
    mov opc.hlvalue,[rbx].hlvalue
    .switch ecx
    .case 4
        .endc .if [rbx].mem_type == MT_REAL4
        mov opc.flags,0
        .if ( [rbx].chararray[15] & 0x80 )
            mov opc.flags,E_NEGATIVE
            and opc.chararray[15],0x7F
        .endif
        __cvtq_ss(&opc, rbx)
        .if ( opc.flags == E_NEGATIVE )
            or opc.chararray[3],0x80
        .endif
        .endc
    .case 8
        .endc .if [rbx].mem_type == MT_REAL8
        mov opc.flags,0
        .if ( [rbx].chararray[15] & 0x80 )
            mov opc.flags,E_NEGATIVE
            and opc.chararray[15],0x7F
        .endif
        __cvtq_sd(&opc, rbx)
        .if ( opc.flags == E_NEGATIVE )
            or opc.chararray[7],0x80
        .endif
        .endc
    .case 10
        __cvtq_ld(&opc, rbx)
        mov dword ptr opc.hlvalue[4],0
        mov word ptr opc.hlvalue[2],0
    .case 16
        .endc
    .endsw

    .for edi = 0, rsi = ModuleInfo.FltStack : rsi : edi++, rsi = [rsi].next

        .if size == [rsi].count

            mov rax,[rsi].string
            mov edx,dword ptr opc.hlvalue[0]
            mov ecx,dword ptr opc.hlvalue[4]

            .if edx == [rax+0x08] && ecx == [rax+0x0C]

                mov edx,opc.value
                mov ecx,opc.hvalue

                .if edx == [rax] && ecx == [rax+0x04]

                    mov eax,[rsi].index
                    tsprintf( buffer, "F%04X", eax )
                    .return 1
                .endif
            .endif
        .endif
    .endf

    tsprintf( buffer, "F%04X", edi )
    .if Parse_Pass == PASS_1

        LclAlloc( flt_item+16 )
        mov [rax].flt_item.index,edi
        mov ecx,size
        mov [rax].flt_item.count,ecx
        mov rcx,ModuleInfo.FltStack
        mov [rax].flt_item.next,rcx
        mov ModuleInfo.FltStack,rax
        lea rcx,[rax+flt_item]
        mov [rax].flt_item.string,rcx
        tmemcpy(rcx, &opc, 16)

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
            AddLineQueueX( "oword 0x%p%p", opc.hlvalue, opc.llvalue )
            .endc
        .endsw
        AddLineQueue( "_DATA ends" )
        AddLineQueue( &segm )
        InsertLineQueue()
    .endif
    .return( 0 )

CreateFloat ENDP

    assume rsi:nothing, rbx:ptr asm_tok

TextItemError proc __ccall uses rbx item:ptr asm_tok

    mov rbx,rcx
    mov rax,[rbx].string_ptr

    .if ( [rbx].token == T_STRING && B[rax] == '<' )

        .return( asmerr( 2045 ) )
    .endif

    .if ( [rbx].token == T_ID )

        SymSearch( [rbx].string_ptr )

        .if ( rax == NULL || [rax].asym.state == SYM_UNDEFINED )

            .return( asmerr( 2006, [rbx].string_ptr ) )
        .endif
    .endif
    .return( asmerr( 2051 ) )

TextItemError endp


; CATSTR directive.
; defines a text equate
; syntax <name> CATSTR [<string>,...]
; TEXTEQU is an alias for CATSTR

CatStrDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local sym:ptr asym

    lea  edi,[rcx+1] ; go past CATSTR/TEXTEQU
    imul ebx,edi,asm_tok
    add  rbx,rdx

    ; v2.08: don't copy to temp buffer
    ; check correct syntax and length of items

    .for ( esi = 0 : edi < Token_Count : )

        .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
            .return( TextItemError( rbx ) )
        .endif

        ; v2.08: using tokenarray.stringlen is not quite correct, since some
        ; chars are stored in 2 bytes (!)

        add esi,[rbx].stringlen
        .if ( esi >= MAX_LINE_LEN )
            .return( asmerr( 2041 ) )
        .endif

        ; v2.08: don't copy to temp buffer

        inc edi
        add rbx,asm_tok
        .if ( [rbx].token != T_COMMA && [rbx].token != T_FINAL )
            .return asmerr(2008, [rbx].string_ptr )
        .endif
        inc edi
        add rbx,asm_tok
    .endf

    mov rbx,tokenarray
    mov rdi,SymSearch( [rbx].string_ptr )
    .if ( rdi == NULL )
        mov rdi,SymCreate( [rbx].string_ptr )
    .elseif( [rdi].asym.state == SYM_UNDEFINED )

        ; v2.01: symbol has been used already. Using
        ; a textmacro before it has been defined is
        ; somewhat problematic.

        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rdi )
        SkipSavedState() ;; further passes must be FULL!

        ; v2.21: changed from 8016 to 6005

        asmerr( 6005, [rdi].asym.name )
    .elseif( [rdi].asym.state != SYM_TMACRO )

        ; it is defined as something else, get out

        .return( asmerr( 2005, [rdi].asym.name ) )
    .endif


    mov [rdi].asym.state,SYM_TMACRO
    or  [rdi].asym.flags,S_ISDEFINED

    ; v2.08: reuse string space if fastmem is on

    inc esi
    .if ( [rdi].asym.total_size < esi )

        mov [rdi].asym.total_size,esi
        mov [rdi].asym.string_ptr,LclAlloc( esi )
    .endif

    ; v2.08: don't use temp buffer

    mov sym,rdi
    add rbx,2*asm_tok
    .for ( edx = 2, rdi = [rdi].asym.string_ptr: edx < Token_Count: edx += 2, rbx += 2*asm_tok )

        mov ecx,[rbx].stringlen
        mov rsi,[rbx].string_ptr
        rep movsb
    .endf
    mov B[rdi],0

    .if ( ModuleInfo.list )
        LstWrite( LSTTYPE_TMACRO, 0, sym )
    .endif
    .return( NOT_ERROR )

CatStrDir endp

; used by EQU if the value to be assigned to a symbol is text.
; - sym:   text macro name, may be NULL
; - name:  identifer ( if sym == NULL )
; - value: value of text macro ( original line, BEFORE expansion )

SetTextMacro proc __ccall uses rsi rdi rbx tokenarray:ptr asm_tok, sym:ptr asym, name:string_t, value:string_t

    mov rdi,rdx
    .if ( rdi == NULL )
        mov rdi,SymCreate( r8 )
    .elseif ( [rdi].asym.state == SYM_UNDEFINED )
        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rdi )

        ; the text macro was referenced before being defined.
        ; this is valid usage, but it requires a full second pass.
        ; just simply deactivate the fastpass feature for this module!

        SkipSavedState()

        ; v2.21: changed from 8016 to 6005

        asmerr( 6005, [rdi].asym.name )
    .elseif ( [rdi].asym.state != SYM_TMACRO )
        asmerr( 2005, r8 )
       .return( NULL )
    .endif

    mov [rdi].asym.state,SYM_TMACRO
    or  [rdi].asym.flags,S_ISDEFINED

    mov rbx,tokenarray
    .if ( [rbx+2*asm_tok].token == T_STRING && [rbx+2*asm_tok].string_delim == '<' )

        ; the simplest case: value is a literal. define a text macro!
        ; just ONE literal is allowed

        .if ( [rbx+3*asm_tok].token != T_FINAL )
            asmerr(2008, [rbx+3*asm_tok].tokpos )
            .return( NULL )
        .endif
        mov value,[rbx+2*asm_tok].string_ptr
        mov esi,[rbx+2*asm_tok].stringlen
    .else

        ; the original source is used, since the tokenizer has
        ; deleted some information.

        mov esi,tstrlen( value )
        mov rdx,value

        ; skip trailing spaces

        .for ( : esi : esi-- )
            .break .if !islspace( [rdx+rsi-1] )
        .endf
    .endif
    lea ecx,[rsi+1]
    .if ( [rdi].asym.total_size < ecx )
        mov [rdi].asym.total_size,ecx
        mov [rdi].asym.string_ptr,LclAlloc( ecx )
    .endif
    tmemcpy( [rdi].asym.string_ptr, value, esi )
    mov rdx,[rdi].asym.string_ptr
    mov B[rdx+rsi],0
    .return( rdi )

SetTextMacro endp

; create a (predefined) text macro.
; used to create @code, @data, ...
; there are 2 more locations where predefined text macros may be defined:
; - assemble.c, add_cmdline_tmacros()
; - symbols.c, SymInit()
; this should be changed eventually.

AddPredefinedText proc __ccall name:string_t, value:string_t

    ; v2.08: ignore previous setting

    .if !SymSearch( rcx )
        SymCreate( name )
    .endif

    mov [rax].asym.state,SYM_TMACRO
    or  [rax].asym.flags,S_ISDEFINED or S_PREDEFINED
    mov rcx,value
    mov [rax].asym.string_ptr,rcx

    ; to ensure that a new buffer is used if the string is modified

    mov [rax].asym.total_size,0
    ret

AddPredefinedText endp

; SubStr()
; defines a text equate.
; syntax: name SUBSTR <string>, pos [, size]

SubStrDir proc __ccall uses rsi rdi rbx r12 r13 r14 i:int_t, tokenarray:ptr asm_tok

  local cnt:int_t
  local chksize:int_t
  local opndx:expr

    ; at least 5 items are needed
    ; 0  1      2      3 4    5   6
    ; ID SUBSTR SRC_ID , POS [, LENGTH]

    mov rbx,rdx
    mov r12,[rbx].string_ptr

    inc i ; go past SUBSTR
    imul eax,i,asm_tok
    add rbx,rax

    ; third item must be a string

    .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
        .return( TextItemError( rbx ) )
    .endif
    mov r13,[rbx].string_ptr
    mov cnt,[rbx].stringlen

    inc i
    add rbx,asm_tok

    .if ( [rbx].token != T_COMMA )
        .return( asmerr( 2008, [rbx].tokpos ) )
    .endif
    inc i

    ;; get pos, must be a numeric value and > 0
    ;; v2.11: flag NOUNDEF added - no forward ref possible

    .ifd ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
        .return( ERROR )
    .endif

    ;; v2.04: "string" constant allowed as second argument
    .if ( opndx.kind != EXPR_CONST )
        .return( asmerr( 2026 ) )
    .endif

    ; pos is expected to be 1-based

    imul ebx,i,asm_tok
    add rbx,tokenarray
    mov r14d,opndx.value

    .ifs ( r14d <= 0 )
        .return( asmerr( 2090 ) )
    .endif
    .if ( [rbx].token != T_FINAL )
        .if ( [rbx].token != T_COMMA )
            .return( asmerr( 2008, [rbx].tokpos ) )
        .endif
        inc i
        .ifd ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
            .return( ERROR )
        .endif
        .if ( opndx.kind != EXPR_CONST )
            .return( asmerr( 2026 ) )
        .endif
        imul ebx,i,asm_tok
        add rbx,tokenarray

        mov edi,opndx.value
        .if ( [rbx].token != T_FINAL )
            .return( asmerr(2008, [rbx].string_ptr ) )
        .endif
        .ifs ( edi < 0 )
            .return( asmerr( 2092 ) )
        .endif
        mov chksize,TRUE
    .else
        mov edi,-1
        mov chksize,FALSE
    .endif
    mov ebx,r14d
    .if ( ebx > cnt )
        .return( asmerr( 2091, ebx ) )
    .endif
    lea eax,[rbx+rdi-1]
    .if ( chksize && eax > cnt )
        .return( asmerr( 2093 ) )
    .endif
    lea rax,[rbx-1]
    add r13,rax
    .if ( edi == -1 )
        mov eax,cnt
        sub eax,ebx
        lea edi,[rax+1]
    .endif

    mov rsi,SymSearch( r12 )

    ; if we've never seen it before, put it in

    .if ( rsi == NULL )

        mov rsi,SymCreate( r12 )

    .elseif( [rsi].asym.state == SYM_UNDEFINED )

        ; it was referenced before being defined. This is
        ; a bad idea for preprocessor text items, because it
        ; will require a full second pass!

        sym_remove_table( &SymTables[TAB_UNDEF*symbol_queue], rsi )
        SkipSavedState()

        ; v2.21: changed from 8016 to 6005

        asmerr( 6005, [rsi].asym.name )

    .elseif( [rsi].asym.state != SYM_TMACRO )

        ;; it is defined as something incompatible, get out

        .return( asmerr( 2005, [rsi].asym.name ) )
    .endif

    mov [rsi].asym.state,SYM_TMACRO
    or  [rsi].asym.flags,S_ISDEFINED
    inc edi
    .if ( [rsi].asym.total_size < edi )
        mov [rsi].asym.total_size,edi
        mov [rsi].asym.string_ptr,LclAlloc(edi)
    .endif
    dec edi
    mov ecx,edi
    mov rdi,[rsi].asym.string_ptr
    mov r8,rsi
    mov rsi,r13
    rep movsb
    mov B[rdi],0
    LstWrite( LSTTYPE_TMACRO, 0, r8 )
   .return( NOT_ERROR )

SubStrDir endp

; SizeStr()
; defines a numeric variable which contains size of a string

SizeStrDir proc __ccall uses rbx i:int_t, tokenarray:ptr asm_tok

    .if ( ecx != 1 )

        imul ebx,ecx,asm_tok
        add  rbx,rdx
       .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif
    mov rbx,rdx
    .if ( [rbx+2*asm_tok].token != T_STRING || [rbx+2*asm_tok].string_delim != '<' )
        .return( TextItemError( &[rbx+2*asm_tok] ) )
    .endif
    .if ( Token_Count > 3 )
        .return( asmerr(2008, [rbx+3*asm_tok].string_ptr ) )
    .endif

    .if ( CreateVariable( [rbx].string_ptr, [rbx+2*asm_tok].stringlen ) )

        LstWrite( LSTTYPE_EQUATE, 0, rax )
       .return( NOT_ERROR )
    .endif
    .return( ERROR )

SizeStrDir endp

; InStr()
; defines a numeric variable which contains position of substring.
; syntax:
; name INSTR [pos,]string, substr

InStrDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local opndx:expr
  local start:int_t

    mov start,1

    imul ebx,ecx,asm_tok
    add rbx,rdx

    .if ( ecx != 1 )
        .return( asmerr(2008, [rbx].string_ptr ) )
    .endif

    inc i ;; go past INSTR
    add rbx,asm_tok

    .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )

        ; v2.11: flag NOUNDEF added - no forward reference accepted

        .ifd ( EvalOperand( &i, tokenarray, Token_Count, &opndx, EXPF_NOUNDEF ) == ERROR )
            .return( ERROR )
        .endif
        .if ( opndx.kind != EXPR_CONST )
            .return( asmerr( 2026 ) )
        .endif
        mov start,opndx.value
        imul ebx,i,asm_tok
        add rbx,tokenarray

        .if ( start <= 0 )

            ;; v2.05: don't change the value. if it's invalid, the result
            ;; is to be 0. Emit a level 3 warning instead.

            asmerr( 7001 )
        .endif

        .if ( [rbx].token != T_COMMA )
            .return( asmerr( 2008, [rbx].tokpos ) )
        .endif
        add rbx,asm_tok ;; skip comma
    .endif

    .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
        .return( TextItemError( rbx ) )
    .endif

    ; to compare the strings, the "visible" format is needed, since
    ; the possible '!' operators inside the strings is optional and
    ; must be ignored.

    mov rsi,[rbx].string_ptr
    mov edi,[rbx].stringlen

    .if ( start > edi )
        .return( asmerr( 2091, start ) )
    .endif

    add rbx,asm_tok
    .if ( [rbx].token != T_COMMA )
        .return( asmerr( 2008, [rbx].tokpos ) )
    .endif
    add rbx,asm_tok
    .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
        .return( TextItemError( rbx ) )
    .endif
    .if ( [rbx+asm_tok].token != T_FINAL )
        .return( asmerr(2008, [rbx+asm_tok].string_ptr ) )
    .endif

    mov edx,[rbx].stringlen
    xor eax,eax
    .if ( start > 0 && edi >= edx && edx )
        mov ecx,start
        lea rax,[rsi-1]
        add rcx,rax

        .if tstrstr( rcx, [rbx].string_ptr )
            sub rax,rsi
            add rax,1
        .endif
    .endif
    mov rbx,tokenarray
    .if ( CreateVariable( [rbx].string_ptr, eax ) )
        LstWrite( LSTTYPE_EQUATE, 0, rax )
        .return ( NOT_ERROR )
    .endif
    .return( ERROR )

InStrDir endp

; internal @CatStr macro function
; syntax: @CatStr( literal [, literal ...] )

CatStrFunc proc __ccall private uses rsi rdi rbx mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok

    mov rdi,rcx
    .for ( rsi = [rdi].macro_instance.parm_array,
           rsi = [rsi]: [rdi].macro_instance.parmcnt: [rdi].macro_instance.parmcnt-- )

        mov ebx,tstrlen( rsi )
        tmemcpy( buffer, rsi, ebx )
        mov rsi,GetAlignedPointer( rsi, ebx )
        add buffer,rbx
    .endf
    mov rdx,buffer
    mov B[rdx],0
   .return( NOT_ERROR )

CatStrFunc endp

ifdef USE_COMALLOC

ComAlloc proto __ccall :string_t, :token_t

ComAllocFunc proc __ccall private mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok

    .if ( ComAlloc( buffer, r8 ) == 0 )

        mov rdx,mi
        mov rdx,[rdx].macro_instance.parm_array
        tstrcpy( buffer, [rdx] )
    .endif
    .return( NOT_ERROR )

ComAllocFunc endp

endif

TypeIdFunc proc __ccall private mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok

    .if ( GetTypeId( buffer, r8 ) == 0 )

        mov rdx,mi
        mov rdx,[rdx].macro_instance.parm_array
        tstrcpy( buffer, [rdx] )
    .endif
    .return( NOT_ERROR )

TypeIdFunc endp

; internal @CStr macro function
; syntax:  @CStr( "\tstring\n" )

CStringFunc proc __ccall private mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok

    .if ( CString( buffer, r8 ) == 0 )

        mov rdx,mi
        mov rdx,[rdx].macro_instance.parm_array
        tstrcpy( buffer, [rdx] )
    .endif
    .return( NOT_ERROR )

CStringFunc endp

; convert string to a number.
; used by @SubStr() for arguments 2 and 3 (start and size),
; and by @InStr() for argument 1 ( start )

GetNumber proc __ccall private string:string_t, pi:ptr int_t, tokenarray:ptr asm_tok

  local opndx:expr
  local i:int_t

    mov eax,Token_Count
    inc eax
    mov i,eax
    mov edx,Tokenize( rcx, eax, r8, TOK_RESCAN )
    .ifd ( EvalOperand( &i, tokenarray, edx, &opndx, EXPF_NOUNDEF ) == ERROR )
        .return( ERROR )
    .endif
    imul ecx,i,asm_tok
    add rcx,tokenarray
    .if( opndx.kind != EXPR_CONST || [rcx].asm_tok.token != T_FINAL )
        .return( asmerr(2008, string ) )
    .endif
    mov rcx,pi
    mov eax,opndx.value
    mov [rcx],eax
   .return( NOT_ERROR )

GetNumber endp

; internal @InStr macro function
; syntax: @InStr( [num], literal, literal )
; the result is returned as string in current radix

InStrFunc proc __ccall private uses rsi rdi rbx mi:ptr macro_instance,
        buffer:string_t, tokenarray:ptr asm_tok

   .new pos:int_t = 1

    ; init buffer with "0"

    mov rdi,rdx
    mov eax,'0'
    mov [rdi],ax
    mov rsi,[rcx].macro_instance.parm_array
    mov rbx,[rsi]

    .if ( rbx )
        .ifd ( GetNumber( rbx, &pos, r8 ) == ERROR )
            .return( ERROR )
        .endif
        .if ( pos == 0 )

            ; adjust index 0. Masm also accepts 0 (and any negative index),
            ; but the result will always be 0 then
            inc pos
        .endif
    .endif
    mov rbx,[rsi+8]
    tstrlen(rbx)
    .if ( pos > eax )
        .return( asmerr( 2091, pos ) )
    .endif

    ; v2.08: if() added, empty searchstr is to return 0
    mov rdx,[rsi+16]
    .if ( B[rdx] != 0 )

        mov ecx,pos
        add rcx,rbx
        dec rcx
        .if tstrstr( rcx, rdx )
            sub rax,rbx
            lea rcx,[rax+1]
            myltoa( rcx, buffer, ModuleInfo.radix, FALSE, TRUE )
        .endif
    .endif
    .return( NOT_ERROR )

InStrFunc endp

; internal @SizeStr macro function
; syntax: @SizeStr( literal )
; the result is returned as string in current radix

SizeStrFunc proc __ccall private mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok

    mov rdx,[rcx].macro_instance.parm_array
    mov rcx,[rdx]

    .if ( rcx )
        mov ecx,tstrlen( rcx )
        myltoa( rcx, buffer, ModuleInfo.radix, FALSE, TRUE )
    .else
        mov rdx,buffer
        mov eax,'0'
        mov [rdx],ax
    .endif
    .return( NOT_ERROR )

SizeStrFunc endp


; internal @SubStr macro function
; syntax: @SubStr( literal, num [, num ] )

SubStrFunc proc __ccall private uses rsi rdi rbx mi:ptr macro_instance, buffer:string_t, tokenarray:ptr asm_tok

  local pos:int_t
  local size:int_t

    mov rsi,[rcx].macro_instance.parm_array
    mov rdi,[rsi]

    .return .ifd ( GetNumber( [rsi+8], &pos, r8 ) == ERROR )

    .if ( pos <= 0 )

        ; Masm doesn't check if index is < 0;
        ; might cause an "internal assembler error".
        ; v2.09: negative index no longer silently changed to 1.

        .return( asmerr( 2091, pos ) ) .if ( pos )
        mov pos,1
    .endif

    mov ebx,tstrlen( rdi )
    .return( asmerr( 2091, pos ) ) .if ( pos > ebx )

    sub ebx,pos
    inc ebx
    mov rdi,[rsi+16]

    .if ( rdi )

        .new sizereq:int_t
        .return .ifd ( GetNumber( rdi, &sizereq, tokenarray ) == ERROR )
        .return( asmerr( 2092 ) ) .if ( sizereq < 0 )
        .return( asmerr( 2093 ) ) .if ( sizereq > ebx )
        mov ebx,sizereq
    .endif

    mov rdi,buffer
    mov ecx,ebx
    mov eax,pos
    add rax,[rsi]
    lea rsi,[rax-1]
    rep movsb
    mov B[rdi],0

   .return( NOT_ERROR )

SubStrFunc endp

; string macro initialization
; this proc is called once per module

    assume rdi:ptr dsym, rsi:ptr macro_info

StringInit proc __ccall uses rsi rdi

ifdef USE_COMALLOC

    ; add @ComAlloc() macro func

    mov rdi,CreateMacro( "@ComAlloc" )
    mov [rdi].flags,S_ISDEFINED or S_PREDEFINED
    mov [rdi].func_ptr,&ComAllocFunc
    mov [rdi].mac_flag,M_ISFUNC
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,2
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) * 2 )
    mov [rax].mparm_list.deflt,NULL
    mov [rax].mparm_list.required,TRUE
    mov [rax].mparm_list[mparm_list].deflt,NULL
    mov [rax].mparm_list[mparm_list].required,FALSE

endif

    ; add typeid() macro func

    mov rdi,CreateMacro( "typeid" )
    mov [rdi].flags,S_ISDEFINED or S_PREDEFINED
    mov [rdi].func_ptr,&TypeIdFunc
    mov [rdi].mac_flag,M_ISFUNC
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,2
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) * 2 )
    mov [rax].mparm_list.deflt,NULL
    mov [rax].mparm_list.required,FALSE
    mov [rax].mparm_list[mparm_list].deflt,NULL
    mov [rax].mparm_list[mparm_list].required,FALSE

    ;; add @CStr() macro func

    mov rdi,CreateMacro( "@CStr" )
    mov [rdi].flags,S_ISDEFINED or S_PREDEFINED
    mov [rdi].func_ptr,&CStringFunc
    mov [rdi].mac_flag,M_ISFUNC
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,1
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) )
    mov [rax].mparm_list.deflt,NULL
    mov [rax].mparm_list.required,TRUE

    ;; add @CatStr() macro func

    mov rdi,CreateMacro( "@CatStr" )
    mov [rdi].flags,S_ISDEFINED or S_PREDEFINED
    mov [rdi].func_ptr,&CatStrFunc
    mov [rdi].mac_flag,M_ISFUNC or M_ISVARARG
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,1
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) )
    mov [rax].mparm_list.deflt,NULL
    mov [rax].mparm_list.required,FALSE

    ;; add @InStr() macro func

    mov rdi,CreateMacro( "@InStr" )
    mov [rdi].flags,S_ISDEFINED or S_PREDEFINED
    mov [rdi].func_ptr,&InStrFunc
    mov [rdi].mac_flag,M_ISFUNC
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,3
    mov [rsi].autoexp,1
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) * 3 )
    mov [rax].mparm_list.deflt,NULL
    mov [rax].mparm_list.required,FALSE
    mov [rax].mparm_list[mparm_list].deflt,NULL
    mov [rax].mparm_list[mparm_list].required,TRUE
    mov [rax].mparm_list[mparm_list*2].deflt,NULL
    mov [rax].mparm_list[mparm_list*2].required,TRUE

    ;; add @SizeStr() macro func

    mov rdi,CreateMacro( "@SizeStr" )
    mov [rdi].flags,S_ISDEFINED or S_PREDEFINED
    mov [rdi].func_ptr,&SizeStrFunc
    mov [rdi].mac_flag,M_ISFUNC
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,1
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) )
    mov [rax].mparm_list.deflt,NULL
    mov [rax].mparm_list.required,FALSE

    ;; add @SubStr() macro func

    mov rdi,CreateMacro( "@SubStr" )
    mov [rdi].flags,S_ISDEFINED or S_PREDEFINED
    mov [rdi].func_ptr,&SubStrFunc
    mov [rdi].mac_flag,M_ISFUNC
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,3
    mov [rsi].autoexp,2 + 4 ;; param 2 (pos) and 3 (size) are expanded
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) * 3 )
    mov [rax].mparm_list.deflt,NULL
    mov [rax].mparm_list.required,TRUE
    mov [rax].mparm_list[mparm_list].deflt,NULL
    mov [rax].mparm_list[mparm_list].required,TRUE
    mov [rax].mparm_list[mparm_list*2].deflt,NULL
    mov [rax].mparm_list[mparm_list*2].required,FALSE
    ret

StringInit endp

    end
