include malloc.inc
include asmc.inc
include symbols.inc
include parser.inc
include input.inc
include tokenize.inc
include memalloc.inc
include fastpass.inc
include expreval.inc
include quadmath.inc
include lqueue.inc
include listing.inc
include segment.inc

MACRO_CSTRING   equ 1
TOK_DEFAULT     equ 0

externdef       list_pos:DWORD

str_item    struc byte
string      string_t ?
count       dd ?
next        dd ?
index       dw ?
unicode     db ?
flags       db ?
str_item    ends
LPSSTR      typedef ptr str_item

    .code

ParseCString PROC PRIVATE USES esi edi ebx lbuf:string_t, buffer:string_t, string:string_t,
        pStringOffset:string_t, pUnicode:ptr byte

  local sbuf[MAX_LINE_LEN]:char_t,   ; "binary" string
        Unicode:char_t

    mov esi,string
    mov edi,buffer
    lea edx,sbuf
    xor ebx,ebx
    mov [edx],ebx

    xor eax,eax
    .if ModuleInfo.xflag & OPT_WSTRING

        mov eax,1
    .endif
    .if WORD PTR [esi] == '"L'

        or  ModuleInfo.xflag,OPT_LSTRING
        mov eax,1
        add esi,1
    .endif
    mov ecx,pUnicode
    mov [ecx],al
    mov Unicode,al

    movsb
    .while BYTE PTR [esi]

        mov al,[esi]
        .if al == '\'
            ;
            ; escape char \\
            ;
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
                mov BYTE PTR [edx],7
                mov eax,20372C22h   ; <",7 >
                jmp case_format
              .case 'b'
                mov BYTE PTR [edx],8
                mov eax,20382C22h   ; <",8 >
                jmp case_format
              .case 'f'
                mov BYTE PTR [edx],12
                mov eax,32312C22h   ; <",12>
                jmp case_format
              .case 'n'
                mov BYTE PTR [edx],10
                mov eax,30312C22h   ; <",10>
                jmp case_format
              .case 't'
                mov BYTE PTR [edx],9
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
                mov BYTE PTR [edx],13
                mov eax,33312C22h   ; <",13>
                jmp case_format
              .case 'v'
                mov BYTE PTR [edx],11
                mov eax,31312C22h   ; <",11>
                jmp case_format
              .case 27h
                mov BYTE PTR [edx],39
                mov eax,39332C22h   ; <",39>
                jmp case_format

              .case 'x'
                movzx eax,BYTE PTR [esi+1]
                .if BYTE PTR _ltype[eax+1] & _HEX

                    add esi,1
                    and eax,not 30h
                    bt  eax,6
                    sbb ecx,ecx
                    and ecx,55
                    sub eax,ecx
                    movzx ecx,BYTE PTR [esi+1]

                    .if BYTE PTR _ltype[ecx+1] & _HEX

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
                    mov BYTE PTR [edi],'x'
                    mov BYTE PTR [edx],'x'
                .endif
                .endc

              .case '0'
                mov eax,',0,"'
                stosd
                mov BYTE PTR [edi],'"'
                mov BYTE PTR [edx],0
                .endc

              .case '"'         ; <",'"',">
                mov ah,','
                mov ecx,buffer
                add ecx,1
                ;
                ; db '"',xx",'"',0
                ;
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
            .if al == 'L' && byte ptr [ecx+1] == '"'
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
        .if BYTE PTR [esi]

            add esi,1
        .endif
    .endw

    xor eax,eax
    mov [edi],al
    mov [edx],al
    .if DWORD PTR [edi-3] == 22222Ch

        mov BYTE PTR [edi-3],0
    .endif

    mov eax,pStringOffset
    mov [eax],esi

    assume esi:ptr str_item
    lea eax,sbuf
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

            .if !memcmp( &sbuf, edx, ebx )

                movzx eax,[esi].index
                sub edx,[esi].string
                .if edx
                    .if Unicode
                        add edx,edx
                    .endif
                    sprintf( lbuf, "DS%04X[%d]", eax, edx )
                .else
                    sprintf( lbuf, "DS%04X", eax )
                .endif
                .return 0
            .endif
        .endif
    .endf

    sprintf(lbuf, "DS%04X", edi)
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
    memcpy(ecx, &sbuf, &[ebx+1])
    ret

ParseCString ENDP

    assume esi:nothing

    option cstack:on

GenerateCString PROC USES esi edi ebx i, tokenarray:tok_t

local   rc:                     int_t,
        q:                      string_t,
        e:                      int_t,
        equal:                  int_t,
        NewString:              int_t,
        b_label:                string_t,
        b_seg:                  string_t,
        b_line:                 string_t,
        b_data:                 string_t,
        buffer:                 string_t,
        StringOffset:           string_t,
        lineflags:              BYTE,
        brackets:               BYTE,
        Unicode:                BYTE

    mov buffer,alloca(MAX_LINE_LEN*3+64*2)
    add eax,MAX_LINE_LEN
    mov b_data,eax
    add eax,MAX_LINE_LEN
    mov b_line,eax
    add eax,MAX_LINE_LEN
    mov b_seg,eax
    add eax,64
    mov b_label,eax

    xor eax,eax
    mov rc,eax

    .if ModuleInfo.strict_masm_compat == 0 && Parse_Pass == PASS_1
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
            movzx ecx,WORD PTR [ecx]

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
        mov edi,LineStoreCurr
        add edi,line_item.line
        strcpy(b_line, edi)
        mov BYTE PTR [edi],';'
        mov equal,strcmp(eax, [esi].asm_tok.tokpos)
        mov al,ModuleInfo.line_flags
        mov lineflags,al

        .while [ebx].asm_tok.token != T_FINAL

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
                    mov BYTE PTR [eax+esi],0

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
                        sprintf(b_data, ecx, b_label, buffer)
                    .else
                        .if Unicode
                            lea ecx,@CStr(" %s dw 0")
                        .else
                            lea ecx,@CStr(" %s sbyte 0")
                        .endif
                        sprintf(b_data, ecx, b_label)
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

                    mov eax,ModuleInfo.currseg
                    .if eax
                        mov ecx,[eax].asym.name
                        strcat( strcpy( b_seg, ecx ), " segment" )
                    .else
                        strcpy( b_seg, ".code" )
                    .endif

                    .if ModuleInfo.line_queue.head
                        RunLineQueue()
                    .endif
                    AddLineQueue( ".data" )
                    AddLineQueue( b_data )
                    AddLineQueue( "_DATA ends" )
                    AddLineQueue( b_seg )
                    InsertLineQueue()
                .endif
                strcpy( ModuleInfo.currsource, buffer )
                Tokenize( ModuleInfo.currsource, 0, tokenarray, TOK_DEFAULT )
                mov ModuleInfo.token_count,eax
                mov eax,i
                shl eax,4
                add eax,tokenarray
                mov q,eax
            .elseif al == ')'
                .break .if !brackets
                sub brackets,1
                .break .if ZERO?
            .elseif al == '('
                add brackets,1
            .endif
            add ebx,16
        .endw

        .if equal == 0

            StoreLine( ModuleInfo.currsource, list_pos, 0 )
        .else
            mov ebx,ModuleInfo.GeneratedCode
            mov ModuleInfo.GeneratedCode,0
            StoreLine( b_line, list_pos, 0 )
            mov ModuleInfo.GeneratedCode,ebx
        .endif
        mov ModuleInfo.line_flags,lineflags
    .endif
    mov eax,rc
    ret

GenerateCString ENDP

ifdef MACRO_CSTRING

CString PROC USES esi edi ebx buffer:string_t, tokenarray:tok_t

  local string:         string_t,
        cursrc:         string_t,
        dlabel:         string_t,
        StringOffset:   string_t,
        retval:         int_t,
        Unicode:        byte

    mov cursrc,alloca(MAX_LINE_LEN*2+32)
    add eax,MAX_LINE_LEN
    mov string,eax
    add eax,MAX_LINE_LEN
    mov dlabel,eax

    assume ebx:ptr asm_tok

    mov ebx,tokenarray

    ; find first instance of macro in line

    mov edi,_stricmp([ebx].string_ptr, "@CStr")

    .if edi

        .while [ebx].token != T_FINAL

            .if [ebx].token == T_ID

                .break .if !_stricmp([ebx].string_ptr, "@CStr")
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

    .if [ebx].token == T_OP_BRACKET && [ebx+asm_tok].token == T_NUM && \
        [ebx+asm_tok*2].token == T_CL_BRACKET

        ; return label[-value]

        .new opnd:expr

        add ebx,16

        _atoow( &opnd, [ebx].string_ptr, [ebx].numbase, [ebx].itemlen )

        ; the number must be 32-bit

        .if dword ptr opnd.hlvalue || dword ptr opnd.hlvalue[4]

            asmerr( 2156 )
            .return 0
        .endif

        .for eax = opnd.value,
             edx = ModuleInfo.StrStack : eax && edx : eax--, edx=[edx].str_item.next
        .endf

        .if edx == NULL

            asmerr( 2156 )
            .return 0
        .endif

        movzx eax,[edx].str_item.index
        sprintf(buffer, "DS%04X", eax)
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
                mov word ptr [eax],' '
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
                    sprintf(cursrc, ecx, dlabel, string)
                .else
                    .if Unicode

                        lea ecx,@CStr(" %s dw 0")
                    .else
                        lea ecx,@CStr(" %s sbyte 0")
                    .endif
                    sprintf(cursrc, ecx, dlabel)
                .endif

                ; v2.24 skip .data/.code if already in .data segment

                .if ModuleInfo.line_queue.head
                    RunLineQueue()
                .endif

                assume ebx:ptr asym

                xor esi,esi
                mov ebx,ModuleInfo.currseg
                .if _stricmp( [ebx].name, "_DATA" )
                    inc esi
                    AddLineQueue( ".data" )
                .elseif edi
                    mov esi,2
                    AddLineQueue( ".const" )
                .endif
                AddLineQueue( cursrc )

                .if esi
                    .if !_stricmp( [ebx].name, "CONST" )
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

endif

flt_item    struc
string      string_t ?
count       int_t ?
next        ptr_t ?
index       int_t ?
flt_item    ends

    assume ebx:ptr expr
    assume esi:ptr flt_item

CreateFloat proc uses esi edi ebx size:int_t, opnd:expr_t, buffer:string_t

  local segm[64]:char_t
  local temp[128]:char_t
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
                    sprintf( buffer, "F%04X", eax )
                    .return 1
                .endif
            .endif
        .endif
    .endf

    sprintf( buffer, "F%04X", edi )
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

        lea esi,temp
        mov eax,ModuleInfo.currseg
        .if eax
            mov ecx,[eax].asym.name
            strcat( strcpy( &segm, ecx ), " segment" )
        .else
            strcpy( &segm, ".code" )
        .endif

        .if ModuleInfo.line_queue.head
            RunLineQueue()
        .endif
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
            AddLineQueueX( "%s dq 0x%q", buffer, opc.llvalue )
            .endc
        .case 10
        .case 16
            AddLineQueueX( "%s label real%d", buffer, size )
            AddLineQueueX( "oword 0x%q%q", opc.hlvalue, opc.llvalue )
            .endc
        .endsw
        AddLineQueue( "_DATA ends" )
        AddLineQueue( &segm )
        InsertLineQueue()
    .endif
    xor eax,eax
    ret

CreateFloat ENDP

    END
