; STRING.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; string macro processing routines.
;

include asmc.inc
include memalloc.inc
include parser.inc
include tokenize.inc
include macro.inc
include fastpass.inc
include listing.inc
include segment.inc
include qfloat.inc
include reswords.inc
include proc.inc
include lqueue.inc
include typeid.inc

externdef list_pos:DWORD

   .code

define HEXOFFS ('A'-'9'-1)

; Returns end-pointer of string: "( "ab\x0102" )" = " )"
; - binary is bytes: "ab\x0102" =  4 bytes -> string stack
; - data is text: <"ab",0x0101> = 11 bytes -> code to emit

ExpandCString proc __ccall uses rsi rdi rbx data:string_t, binary:string_t, string:string_t, Unicode:int_t

   .new hex_count:char_t
   .new digits:char_t
   .new inside_quote:char_t = 1
   .new char_count:int_t = 1

    ldr rsi,string
    ldr rdi,data
    ldr rdx,binary

    xor ebx,ebx
    mov [rdx],rbx
    movsb

    .while byte ptr [rsi]
        mov al,[rsi]
        .if ( al == BSLASH )

            ; escape char \\

            inc rsi
            movzx eax,byte ptr [rsi]
            .switch eax
            .case 'a'             ; Alert (Beep, Bell)
                mov al,0x07
                jmp case_format
            .case 'b'             ; Backspace
                mov al,0x08
                jmp case_format
            .case 'e'             ; Escape character
                mov al,0x1B
                jmp case_format
            .case 'f'             ; Formfeed Page Break
                mov al,0x0C
                jmp case_format
            .case 'n'             ; Newline (Line Feed)
                mov al,0x0A
                jmp case_format
            .case 'r'             ; Carriage Return
                mov al,0x0D
                jmp case_format
            .case 't'             ; Horizontal Tab
                mov al,0x09
                jmp case_format
            .case 'v'             ; Vertical Tab
                mov al,0x0B
                jmp case_format
            .case 27h             ; Apostrophe or single quotation mark
                mov al,0x27
                jmp case_format
            .case '?'             ; Question mark (used to avoid trigraphs)
                mov al,0x3F
             case_format:
                mov [rdx],al
                inc rdx
                mov cl,al
                .if ( inside_quote )
                    mov inside_quote,0
                    .if ( char_count == 1 )
                        dec rdi
                        mov char_count,0
                    .else
                        mov al,'"'
                        stosb
                        inc char_count
                    .endif
                .endif
                .if ( char_count )
                    mov al,','
                    stosb
                    inc char_count
                .endif
                mov eax,'x0'
                stosw
                mov al,cl
                shr al,4
                add al,'0'
                .if ( al > '9' )
                    add al,HEXOFFS
                .endif
                stosb
                mov al,cl
                and al,0x0F
                add al,'0'
                .if ( al > '9' )
                    add al,HEXOFFS
                .endif
                stosb
                add char_count,4
               .endc
            .case 'U'
                mov hex_count,8 ; takes 8 hexadecimal digits
                jmp common_hex
            .case 'u'
                mov hex_count,4
                jmp common_hex
            .case 'x'
                mov hex_count,2
                .if ( Unicode )
                    mov hex_count,4
                .endif
             common_hex:
                .if ( islxdigit( [rsi+1] ) )
                    .if ( inside_quote )
                        mov inside_quote,0
                        .if ( char_count == 1 )
                            dec rdi
                            mov char_count,0
                        .else
                            mov al,'"'
                            stosb
                            inc char_count
                        .endif
                    .endif
                    .if ( char_count )
                        mov al,','
                        stosb
                        inc char_count
                    .endif
                    mov eax,'x0'
                    stosw
                    inc rsi
                    ;
                    ; digits may be less than count: "\x7"
                    ;
                    .for ( ecx = 0 : islxdigit([rsi+rcx]) : ecx++ )
                        .break .if ( cl >= hex_count )
                    .endf
                    mov digits,cl
                    .if ( hex_count == 8 && ecx > 4 )
                        sub ecx,4
                        add rsi,rcx
                        mov ecx,4
                    .endif
                    .for ( ebx = 0 : ebx < ecx : ebx++ )
                        mov al,[rsi+rbx]
                        stosb
                        inc char_count
                    .endf
                    .if ( hex_count == 8 )
                        mov al,','
                        stosb
                        mov eax,'x0'
                        stosw
                        add char_count,3
                        mov cl,digits
                        .if ( ecx <= 4 ) ; "\U1"
                            mov al,'0'
                            stosb
                            inc char_count
                        .else
                            sub ecx,4
                            .for ( rsi -= rcx, ebx = 0 : ebx < ecx : ebx++ )
                                mov al,[rsi+rbx]
                                stosb
                                inc char_count
                            .endf
                        .endif
                    .endif

                    .for ( ecx = 0, eax = 0 : digits : digits-- )
                        lodsb
                        shl ecx,4
                        and al,not 30h
                        bt  eax,6
                        sbb ebx,ebx
                        and bl,55
                        sub al,bl
                        add ecx,eax
                    .endf
                    dec rsi
                    mov [rdx],cl
                    inc rdx
                    movzx ebx,hex_count
                    shr ebx,1 ; fixed byte count
                    dec ebx
                    shr ecx,8
                    .while ebx
                        mov [rdx],cl
                        inc rdx
                        shr ecx,8
                        dec ebx
                    .endw
                .else
                    .if ( !inside_quote )
                        inc inside_quote
                        mov ecx,'",'
                        mov [rdi],cx
                        add rdi,2
                        add char_count,2
                    .endif
                    mov al,[rsi]
                    stosb
                    mov [rdx],al
                    inc rdx
                    inc char_count
                .endif
                .endc
            .case '0'
                .if ( !isldigit( [rsi+1] ) )
                    xor eax,eax
                    mov [rdx],al
                    inc rdx
                    .if ( inside_quote )
                        mov inside_quote,0
                        .if ( char_count == 1 )
                            dec rdi
                            mov char_count,0
                        .else
                            mov al,'"'
                            stosb
                            inc char_count
                        .endif
                    .endif
                    .if ( char_count )
                        mov al,','
                        stosb
                        inc char_count
                    .endif
                    mov al,'0'
                    stosb
                    inc char_count
                   .endc
                .endif
                mov eax,'0'

                ; added v2.34.25 -- Octal escape sequence

            .case '1' ; \000 to \172
                sub eax,'0'
                mov ecx,eax
                .if ( inside_quote )
                    mov inside_quote,0
                    .if ( char_count == 1 )
                        dec rdi
                        mov char_count,0
                    .else
                        mov al,'"'
                        stosb
                        inc char_count
                    .endif
                .endif
                .if ( char_count )
                    mov al,','
                    stosb
                    inc char_count
                .endif
                mov eax,'x0'
                stosw
                mov digits,0
                .while ( isldigit( [rsi+1] ) && digits < 3 )
                    inc rsi
                    sub eax,'0'
                    shl ecx,3
                    add ecx,eax
                    inc digits
                .endw
                mov al,cl
                shr al,4
                add al,'0'
                .if ( al > '9' )
                    add al,HEXOFFS
                .endif
                stosb
                mov al,cl
                and al,0x0F
                add al,'0'
                .if ( al > '9' )
                    add al,HEXOFFS
                .endif
                stosb
                add char_count,4
                mov [rdx],cl
                inc rdx
               .endc
            .case '"'
                .if ( inside_quote )
                    mov inside_quote,0
                    .if ( char_count == 1 )
                        dec rdi
                        mov char_count,0
                    .else
                        mov al,'"'
                        stosb
                        inc char_count
                    .endif
                .endif
                .if ( char_count )
                    mov al,','
                    stosb
                    inc char_count
                .endif
                mov eax,'22x0'
                stosd
                add char_count,4
                mov al,0x22
                mov [rdx],al
                inc rdx
               .endc
            .default
                .if ( !inside_quote )
                    inc inside_quote
                    mov ecx,'",'
                    mov [rdi],cx
                    add rdi,2
                    add char_count,2
                .endif
                stosb
                mov [rdx],al
                inc rdx
                inc char_count
               .endc
            .endsw
        .elseif ( al == '"' )
            add rsi,1
            .for ( rcx = rsi, al = [rcx] : al == ' ' || al == 9 : rcx++, al = [rcx] )
            .endf
            .if ( al == 'L' && byte ptr [rcx+1] == '"' )
                inc rcx
                mov al,'"'
            .endif
            .if ( al == '"' ) ; "string1" "string2"
                mov rsi,rcx
            .else
                .if ( inside_quote )
                    mov eax,'"'
                    stosb
                    inc char_count
                .endif
                .break
            .endif
        .else
            .if ( !inside_quote )
                inc inside_quote
                mov ecx,'",'
                mov [rdi],cx
                add rdi,2
                add char_count,2
            .endif
            stosb
            mov [rdx],al
            inc rdx
            inc char_count
        .endif
        .if ( byte ptr [rsi] )
            inc rsi
        .endif
    .endw
    xor eax,eax
    mov [rdi],al
    mov [rdx],al
    mov rax,rsi
    mov rcx,binary
    sub rdx,rcx
    ret
    endp


ParseCString proc __ccall private uses rsi rdi rbx lbuf:string_t, buffer:string_t, string:string_t,
        pStringOffset:string_t, pUnicode:ptr byte

   .new Unicode:char_t
   .new hash:dword
    ldr rsi,string

    ; "binary" string
   .new sbuf:string_t = alloc_line()
    mov rdi,buffer
    mov rdx,rax
    xor eax,eax
    .if ( MODULE.wstring )
        mov eax,1
    .endif
    .if ( word ptr [rsi] == '"L' )
        mov MODULE.LStringUsed,1
        mov eax,1
        add rsi,1
    .endif
    mov rcx,pUnicode
    mov [rcx],al
    mov Unicode,al
    ExpandCString(rdi, rdx, rsi, eax)
    mov rsi,pStringOffset
    mov [rsi],rax
    mov rbx,rdx
    .for ( eax = FNVBASE, edx = 0 : edx < ebx : edx++ )
        imul eax,eax,FNVPRIME
        xor  al,[rcx+rdx]
    .endf
    mov hash,eax
    assume rsi:ptr str_item
    .for ( edi = 0, rsi = MODULE.StrStack : rsi : edi++, rsi = [rsi].next )
        mov cl,[rsi].unicode
        mov eax,[rsi].count
        .if ( eax >= ebx && cl == Unicode )
            mov rdx,[rsi].string
            .if ( eax > ebx )
                add rdx,rax ; to end of string
                sub rdx,rbx
            .endif
            .new tmp:string_t = rdx
            tmemcmp( sbuf, rdx, ebx )
            mov rdx,tmp
            .if ( eax == 0 )
                mov eax,[rsi].hash
                sub rdx,[rsi].string
                mov ecx,'A'
                .if Unicode
                    mov ecx,'W'
                    add edx,edx
                .endif
                .if ( edx )
                    tsprintf( lbuf, "D$%08X%c[%d]", eax, ecx, edx )
                .else
                    tsprintf( lbuf, "D$%08X%c", eax, ecx )
                .endif
                 free_line(sbuf)
                .return 0
            .endif
        .endif
    .endf
    mov ecx,'A'
    .if Unicode
        mov ecx,'W'
    .endif
    tsprintf(lbuf, "D$%08X%c", hash, ecx)
    LclAlloc(&[rbx+str_item+1])
    mov [rax].str_item.count,ebx
    mov [rax].str_item.index,edi
    mov ecx,hash
    mov [rax].str_item.hash,ecx
    mov cl,Unicode
    mov [rax].str_item.unicode,cl
    mov rcx,MODULE.StrStack
    mov [rax].str_item.next,rcx
    mov MODULE.StrStack,rax
    lea rcx,[rax+str_item]
    mov [rax].str_item.string,rcx
    tmemcpy(rcx, sbuf, &[rbx+1])
    free_line(sbuf)
    .return 1
    endp


    assume rsi:nothing

GetCurrentSegment proc __ccall private buffer:string_t
    mov rax,MODULE.currseg
    .if ( rax )
        mov rdx,[rax].asym.name
        tstrcat( tstrcpy( buffer, rdx ), " segment" )
    .else
        tstrcpy( buffer, ".code" )
    .endif
    .if ( MODULE.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ( MODULE.line_queue.head )
        RunLineQueue()
        and MODULE.line_flags,NOT LOF_LISTED
    .endif
    ret
    endp


StringComdat proc __ccall uses rsi rdi string:string_t, curseg:string_t

    ldr rsi,string
    ldr rdi,curseg

    tstrcpy(rdi, "_DATA")
    .if ( MODULE.comdata && !MODULE.nocdata )
        AddLineQueueX( " %s %r", rdi, T_ENDS )
        .if ( Options.output_format == OFORMAT_COFF && MODULE._model == MODEL_FLAT )
            tsprintf(rdi, "__str@%s", &[rsi+2])
            AddLineQueueX( "%s %r %r %r(\".rdata\") comdat(2) %r 'CONST'",
                    rdi, T_SEGMENT, T_FLAT, T_ALIAS, T_WORD )
       .elseif ( Options.output_format == OFORMAT_ELF )
            tsprintf(rdi, "`.gnu.linkonce.r.%s`", &[rsi+2])
            AddLineQueueX("%s %r %r 'CONST'", rdi, T_SEGMENT, T_WORD )
        .endif
        AddLineQueueX( " %r %s", T_PUBLIC, rsi )
    .endif
    ret
    endp


FloatComdat proc __ccall uses rsi rdi rbx string:string_t, curseg:string_t, size:int_t

   .new prefix[16]:char_t

    ldr rsi,string
    ldr rbx,curseg
    ldr edi,size

    tstrcpy(rbx, "@CurSeg")
    .if ( MODULE.comdata && !MODULE.nocdata )
        AddLineQueueX( " %s %r", rbx, T_ENDS )
        .for ( ecx = 0 : byte ptr [rsi+rcx] != '@' : ecx++ )
            mov al,[rsi+rcx]
            mov prefix[rcx],al
        .endf
        mov prefix[rcx],ch
        .for ( ecx = FNVBASE, rax = rsi : byte ptr [rax] : rax++ )
            imul ecx,ecx,FNVPRIME
            xor  cl,[rax]
        .endf
        .if ( Options.output_format == OFORMAT_COFF && MODULE._model == MODEL_FLAT )
            AddLineQueueX( "%s@%08X %r %r %r(%d) %r(\".rdata\") comdat(2) 'CONST'",
                    &prefix, ecx, T_SEGMENT, T_FLAT, T_ALIGN, edi, T_ALIAS )
        .elseif ( Options.output_format == OFORMAT_ELF )
            tsprintf(rbx, "`.gnu.linkonce.r.%08X`", ecx)
            AddLineQueueX( "%s %r %r(%d) 'CONST'", rbx, T_SEGMENT, T_ALIGN, edi )
        .endif
        AddLineQueueX( " %r %s", T_PUBLIC, rsi )
    .else
        .if ( edi > 16 )
            mov edi,16
        .endif
        AddLineQueueX( " %r", T_DOT_CONST )
        AddLineQueueX( " %r %d", T_ALIGN, edi )
    .endif
    ret
    endp


GenerateCString proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

   .new rc:             int_t
   .new equal:          int_t
   .new b_label:        string_t
   .new b_seg:          string_t
   .new b_line:         string_t
   .new b_data:         string_t
   .new StringOffset:   string_t
   .new buffer:         string_t
   .new q:              string_t
   .new NewString:      int_t
   .new size:           int_t
   .new brackets:       byte
   .new Unicode:        byte
   .new merged:         byte
   .new lineflags:      byte
   .new mem_alloc:      uchar_t = 0
   .new curseg[64]:     char_t

    xor eax,eax
    mov rc,eax
    mov merged,al

    .return .if ( Options.strict_masm_compat )

    ;
    ; need "quote"
    ;
    ldr  rsi,tokenarray
    imul ebx,i,asm_tok
    add  rbx,rsi
    mov  brackets,al
    mov  edx,eax
    ;
    ; proc( "", ( ... ), "", [..+""] )
    ;
    .while ( [rbx].asm_tok.token != T_FINAL )
        mov rcx,[rbx].asm_tok.string_ptr
        movzx ecx,word ptr [rcx]
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
    mov edi,MaxLineLength
    lea ecx,[rdi*4+64*2]
    .if ( edi > MAX_LINE_LEN )
        inc mem_alloc
        MemAlloc(ecx)
    .else
        alloca(ecx)
    .endif

    ; v2.34.52 - extended buffer size..
    mov ecx,edi
    shr ecx,2
    add edi,ecx
    mov buffer,rax
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
    tstrcpy( b_line, rdi )
    .if ( Parse_Pass == PASS_1 )
        mov byte ptr [rdi],';'
        tstrcmp( rax, [rsi].asm_tok.tokpos )
    .else
        xor eax,eax
    .endif
    mov equal,eax
    mov lineflags,MODULE.line_flags

    .while ( [rbx].asm_tok.token != T_FINAL )
        mov rcx,[rbx].asm_tok.tokpos
        mov ax,[rcx]
        .if ( al == '"' || ax == '"L' )
            mov rdi,rcx
            mov rsi,rcx
            mov q,rbx
            ;
            ; v2.28 -- token behind may be 'L'
            ;
            .if ( [rbx-asm_tok].asm_tok.token == T_ID )
                mov rax,[rbx-asm_tok].asm_tok.string_ptr
                mov eax,[rax]
                .if ( ax == 'L' )
                    sub q,asm_tok
                    dec rsi
                .endif
            .endif
            .if ParseCString( b_label, buffer, rsi, &StringOffset, &Unicode )
                mov eax,1
            .endif
            mov NewString,eax
            mov rsi,StringOffset

            .if ( equal )
                ;
                ; strip "string" from LineStoreCurr
                ;
                mov rcx,rsi
                sub rcx,rdi
                mov size,ecx
                tmemcpy( b_data, rdi, ecx )
                mov ecx,size
                mov byte ptr [rax+rcx],0
                ;
                ; if the string is split the compare will fail..
                ;
                ; spanning of lines and spaces are already handled
                ; so the string will be ("1""2""3") --> ("123")
                ;
                .if ( !merged )
                    inc merged
                    .if tstrchr(b_line, '"')
                        mov esi,1
                        lea rdi,[rax+1]
                        .while 1
                            mov al,[rdi]
                            .break .if !al
                            .if ( al == '"' )
                                .if ( byte ptr [rdi-1] == BSLASH )
                                .elseif ( esi == 0 )
                                    inc esi
                                .elseif ( byte ptr [rdi-1] == '"' )
                                    xor esi,esi
                                .elseif ( byte ptr [rdi+1] == '"' )
                                    tstrcpy(rdi, &[rdi+2])
                                    dec rdi
                                .else
                                    xor esi,esi
                                .endif
                            .endif
                            inc rdi
                        .endw
                        mov rsi,StringOffset
                    .endif
                .endif
                .if tstrstr( b_line, b_data )
                    mov rdi,rax
                    mov ecx,size
                    tstrstart( &[rdi+rcx] )
                    .if ( ecx != ',' && ecx != ')' )
                        .if tstrrchr( &[rdi+1], '"' )
                            add rax,1
                        .endif
                    .endif
                    .if ( rax )
                        tstrcpy( b_data, rax )
                        tstrcpy( rdi, "addr " )
                        tstrcat( rdi, b_label )
                        tstrcat( rdi, b_data )
                    .endif
                .endif
            .endif
            .if ( NewString )
                mov rdx,buffer
                mov eax,[rdx]
                and eax,0x00FFFFFF
                mov ecx,T_SBYTE
                .if Unicode
                    mov ecx,T_DW
                .endif
                .if ( eax != '""' )
                    tsprintf( b_data, " %s %r %s,0", b_label, ecx, rdx )
                .else
                    tsprintf(b_data, " %s %r 0", b_label, ecx)
                .endif
            .endif
            mov rax,q
            mov rax,[rax].asm_tok.tokpos
            mov di,[rax]
            mov byte ptr [rax],0
            mov rax,tokenarray
            tstrcat( tstrcat( tstrcpy( buffer, [rax].asm_tok.tokpos ), "addr " ), b_label )
            mov rax,q
            mov rax,[rax].asm_tok.tokpos
            mov [rax],di
            mov rsi,ltokstart( rsi )
            .if ecx
                .if ( ecx != ')' )
                    tstrcat( buffer, " " )
                .endif
                tstrcat( buffer, rsi )
            .endif
            .if ( NewString )
                GetCurrentSegment( b_seg )
                AddLineQueueX( " %r", T_DOT_DATA )
                StringComdat( b_label, &curseg )
                .if Unicode
                    AddLineQueueX( " %r 2", T_ALIGN )
                .endif
                AddLineQueue( b_data )
                AddLineQueueX( " %s %r", &curseg, T_ENDS )
                AddLineQueue( b_seg )
                InsertLineQueue()
            .endif
            tstrcpy( CurrSource, buffer )
            Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT )
            mov TokenCount,eax
            mov rcx,TokenArray
            sub rbx,tokenarray
            add rbx,rcx
            mov tokenarray,rcx
            imul eax,i,asm_tok
            add rax,rcx
            mov q,rax
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
        StoreLine( CurrSource )
    .else
        mov ebx,MODULE.GeneratedCode
        mov MODULE.GeneratedCode,0
        StoreLine( b_line )
        mov MODULE.GeneratedCode,ebx
        mov rcx,CurrSource
    .endif
    mov MODULE.line_flags,lineflags
    free_line(buffer)
    .return( rc )
    endp


; @CStr() macro

CString proc __ccall private uses rsi rdi rbx buffer:string_t, tokenarray:token_t

   .new string:         string_t
   .new cursrc:         string_t
   .new dlabel:         string_t
   .new StringOffset:   string_t
   .new retval:         int_t
   .new Unicode:        byte
   .new mem_alloc:      uchar_t = 0
   .new rsrc:           byte = 0 ; v2.39.12: @CStr() in .rsrc segment
   .new curseg[64]:     char_t = 0

    ldr rbx,tokenarray
    mov edi,MaxLineLength
    lea ecx,[rdi+rdi+32]
    .if ( edi > MAX_LINE_LEN )
        inc mem_alloc
        MemAlloc(ecx)
    .else
        alloca(ecx)
    .endif
    mov cursrc,rax
    lea rcx,[rax+rdi]
    lea rdx,[rax+rdi*2]
    mov string,rcx
    mov dlabel,rdx

    assume rbx:token_t

    ; find first instance of macro in line

    xor edi,edi
    .if ( [rbx].hash1 != HASH(@CStr) )
        inc edi
        .while ( [rbx].token != T_FINAL )
            .if ( [rbx].token == T_ID )
                .break .if ( [rbx].hash1 == HASH(@CStr) )
            .endif
            add rbx,asm_tok
        .endw
        .if ( [rbx].token == T_FINAL && [rbx+asm_tok].token == T_OP_BRACKET )
            add rbx,asm_tok
        .elseif ( [rbx].token != T_FINAL )
            add rbx,asm_tok
        .else
            mov rbx,tokenarray
        .endif
    .endif

    .if ( [rbx].token == T_OP_BRACKET &&
          ( [rbx+asm_tok].token == T_NUM && [rbx+asm_tok*2].token == T_CL_BRACKET ) )

        ; return label[-value]

       .new opnd:expr
        free_line(cursrc)
        add rbx,asm_tok
        _atoow( &opnd, [rbx].string_ptr, [rbx].numbase, [rbx].itemlen )

        ; the number must be 32-bit

        .if ( opnd.h64_l || opnd.h64_h )
            asmerr( 2156 )
           .return 0
        .endif
        ;
        ; allow @CStr(-1) --> last index + 1
        ;
        ; The strings are now named D$<hash><A|W>, so peeking the
        ; next label is no longer possible
        ;
        mov ecx,opnd.value
        mov rdx,MODULE.StrStack
        .for ( eax = ecx : eax && rdx : eax--, rdx=[rdx].str_item.next )
        .endf
        .if ( rdx == NULL )
            asmerr( 2156 )
           .return( 0 )
        .endif
        mov eax,[rdx].str_item.index
        .for ( rdx = MODULE.StrStack : rdx : rdx = [rdx].str_item.next )
            .break .if ( eax == [rdx].str_item.index )
        .endf
        .if ( rdx == NULL )
            asmerr( 2156 )
           .return 0
        .endif
        mov eax,[rdx].str_item.hash
        mov ecx,'A'
        .if ( [rdx].str_item.unicode )
            mov ecx,'W'
        .endif
        tsprintf( buffer, "D$%08X%c", eax, ecx )
       .return 1
    .endif

    .for ( : [rbx].token != T_FINAL : rbx += asm_tok )

        mov rsi,[rbx].tokpos

        ; v2.28 - .data --> .const
        ;
        ; - dq @CStr(L"CONST")
        ; - dq @CStr(ID)

        .if ( [rbx].token == T_ID && [rbx-asm_tok].token == T_OP_BRACKET )
            .if SymFindID( rbx )
                mov rax,[rax].asym.string_ptr
            .endif
            .if ( rax == NULL ) ; v2.39: added
                .if ( Parse_Pass > PASS_1 )
                    asmerr( 2006, [rbx].string_ptr )
                .endif
                .return( 0 )
            .endif
            .if ( byte ptr [rax] == '"' || word ptr [rax] == '"L' )
                mov rsi,rax
            .endif
        .endif
        .if ( byte ptr [rsi] == '"' || word ptr [rsi] == '"L' )
            ParseCString( dlabel, string, rsi, &StringOffset, &Unicode )
            mov esi,eax
            .if edi
                ;.if ( MODULE.Ofssize != USE64 )
                ;    tstrcpy( buffer, "offset " )
                ;.endif
                tstrcat( buffer, dlabel )
            .else
                ;
                ; v2.24 skip return value if @CStr is first token
                ;
                mov rax,dlabel
                mov word ptr [rax],' '
            .endif
            .if ( esi )
                mov rax,string
                mov eax,[rax]
                and eax,0x00FFFFFF
                mov ecx,T_SBYTE
                .if Unicode
                    mov ecx,T_DW
                .endif
                .if ( eax != '""' )
                    tsprintf( cursrc, " %s %r %s,0", dlabel, ecx, string )
                .else
                    tsprintf( cursrc, " %s %r 0", dlabel, ecx )
                .endif

                ; v2.24 skip .data/.code if already in .data segment

                .if ( MODULE.line_queue.head )
                    RunLineQueue()
                .endif
                assume rbx:asym_t
                xor esi,esi
                mov rbx,MODULE.currseg
                .if rbx
                    .ifd tstricmp( [rbx].name, "_DATA" )
                        .ifd !tstricmp( [rbx].name, ".rsrc" )
                            inc rsrc
                        .endif
                    .endif
                    .if ( eax )
                        inc esi
                        AddLineQueueX( " %r", T_DOT_DATA )
                        StringComdat( dlabel, &curseg )
                    .endif
                .endif
                .if ( edi && !esi )
                    mov esi,2
                    AddLineQueueX( " %r", T_DOT_CONST )
                .endif
                .if ( Unicode && !rsrc )
                    AddLineQueueX( " %r 2", T_ALIGN )
                .endif
                AddLineQueue( cursrc )
                .if esi
                    .if ( curseg )
                        AddLineQueueX( " %s %r", &curseg, T_ENDS )
                    .endif
                    .ifd !tstricmp( [rbx].name, "CONST" )
                        mov ecx,T_DOT_CONST
                    .elseif ( esi == 2 )
                        mov ecx,T_DOT_DATA
                    .else
                        mov ecx,T_DOT_CODE
                    .endif
                    AddLineQueueX( " %r", ecx )
                .endif
                InsertLineQueue()
            .endif
             free_line(cursrc)
            .return( 1 )
        .endif
    .endf
     free_line(cursrc)
    .return( 0 )
    endp


    assume rbx:expr_t, rsi:stritem_t

CreateFloat proc __ccall uses rsi rdi rbx size:int_t, opnd:expr_t, buffer:string_t

   .new segm[64]:char_t
   .new curseg[64]:char_t
   .new opc:expr
   .new ftype:int_t = T_XMMWORD
   .new negative:byte = 0

    ldr edi,size
    mov rbx,tmemcpy(&opc, ldr(opnd), expr)

    lea rsi,@CStr("__xmm@")
    .switch edi
    .case 4
        mov ftype,T_REAL4
        lea rsi,@CStr("__real@")
        .endc .if ( opc.mem_type == MT_REAL4 )
        .if ( opc.chararray[15] & 0x80 )
            mov negative,1
            and opc.chararray[15],0x7F
        .endif
        __cvtq_ss(rbx, rbx)
        .if ( negative )
            or opc.chararray[3],0x80
        .endif
        .endc
    .case 8
        mov ftype,T_REAL8
        lea rsi,@CStr("__real@")
        .endc .if ( opc.mem_type == MT_REAL8 )
        .if ( opc.chararray[15] & 0x80 )
            mov negative,1
            and opc.chararray[15],0x7F
        .endif
        __cvtq_sd(rbx, rbx)
        .if ( negative )
            or opc.chararray[7],0x80
        .endif
        .endc
    .case 10
        mov edi,16
        .if ( opc.mem_type != MT_REAL10 )
            __cvtq_ld(rbx, rbx)
        .endif
        .endc
    .case 32
        mov ftype,T_YMMWORD
        lea rsi,@CStr("__ymm@")
       .endc
    .case 64
        mov ftype,T_ZMMWORD
        lea rsi,@CStr("__zmm@")
    .endsw
    mov rsi,tstrcpy(buffer, rsi)
    add rsi,6
    .if ( byte ptr [rsi] )
        inc rsi
    .endif
    .for ( rdi = &[rbx+rdi-4] : rdi >= rbx : rdi-=4, rsi+=8 )
        mov edx,[rdi]
        tsprintf( rsi, "%08x", edx )
    .endf
    mov rsi,buffer
    .if SymFind( rsi )
        .return( 1 )
    .endif
    .if ( Parse_Pass > PASS_1 )
        .return( 0 )
    .endif
    GetCurrentSegment( &segm )
    mov edi,size
    .if ( edi == 10 )
        mov edi,16
    .endif
    FloatComdat(rsi, &curseg, edi)
    AddLineQueueX( "%s label %r", rsi, ftype )
    mov ecx,size
    .if ( ecx == 10 )
        mov ecx,16
    .endif
    .for ( rdi = &[rbx+rcx] : rbx < rdi : rbx += 4 )
        mov edx,[rbx]
        AddLineQueueX( " dd 0x%08X", edx )
    .endf
    AddLineQueueX( "%s %r", &curseg, T_ENDS )
    AddLineQueue( &segm )
    InsertLineQueue()
    .return( 0 )
    endp


    assume rsi:nothing, rbx:token_t

TextItemError proc __ccall uses rbx item:token_t
    ldr rbx,item
    mov rax,[rbx].string_ptr
    .if ( [rbx].token == T_STRING && byte ptr [rax] == '<' )
        .return( asmerr( 2045 ) )
    .endif
    .if ( [rbx].token == T_ID )
        SymFindID( rbx )
        .if ( rax == NULL || [rax].asym.state == SYM_UNDEFINED )
            .return( asmerr( 2006, [rbx].string_ptr ) )
        .endif
    .endif
    .return( asmerr( 2051 ) )
    endp


; CATSTR directive.
; defines a text equate
; syntax <name> CATSTR [<string>,...]
; TEXTEQU is an alias for CATSTR

CatStrDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local sym:asym_t

    ldr  edi,i
    ldr  rdx,tokenarray

    inc  edi   ; go past CATSTR/TEXTEQU
    imul ebx,edi,asm_tok
    add  rbx,rdx

    ; v2.08: don't copy to temp buffer
    ; check correct syntax and length of items

    .for ( esi = 0 : edi < TokenCount : )

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
            .return asmerr( 2008, [rbx].string_ptr )
        .endif
        inc edi
        add rbx,asm_tok
    .endf

    mov rbx,tokenarray
    mov rdi,SymFind( [rbx].string_ptr )
    .if ( rdi == NULL )
        mov rdi,SymGCreate( [rbx].string_ptr )
    .elseif( [rdi].asym.state == SYM_UNDEFINED )

        ; v2.01: symbol has been used already. Using
        ; a textmacro before it has been defined is
        ; somewhat problematic.

        sym_remove_table( &SymTables[TAB_UNDEF], rdi )
        SkipSavedState() ;; further passes must be FULL!

        ; v2.21: changed from 8016 to 6005

        asmerr( 6005, [rdi].asym.name )
    .elseif( [rdi].asym.state != SYM_TMACRO )

        ; it is defined as something else, get out

        .return( asmerr( 2005, [rdi].asym.name ) )
    .endif
    mov [rdi].asym.state,SYM_TMACRO
    mov [rdi].asym.isdefined,1

    ; v2.08: reuse string space if fastmem is on

    inc esi
    .if ( [rdi].asym.total_size < esi )
        mov [rdi].asym.total_size,esi
        mov [rdi].asym.string_ptr,LclAlloc( esi )
    .endif

    ; v2.08: don't use temp buffer

    mov sym,rdi
    add rbx,2*asm_tok
    .for ( edx = 2, rdi = [rdi].asym.string_ptr: edx < TokenCount: edx += 2, rbx += 2*asm_tok )
        mov ecx,[rbx].stringlen
        mov rsi,[rbx].string_ptr
        rep movsb
    .endf
    mov byte ptr [rdi],0
    .if ( MODULE.list )
        LstWrite( LSTTYPE_TMACRO, 0, sym )
    .endif
    .return( NOT_ERROR )
    endp


; used by EQU if the value to be assigned to a symbol is text.
; - sym:   text macro name, may be NULL
; - name:  identifer ( if sym == NULL )
; - value: value of text macro ( original line, BEFORE expansion )

SetTextMacro proc __ccall uses rsi rdi rbx tokenarray:token_t, sym:asym_t, name:string_t, value:string_t

    ldr rdi,sym

    .if ( rdi == NULL )
        mov rdi,SymCreate( name )
    .elseif ( [rdi].asym.state == SYM_UNDEFINED )
        sym_remove_table( &SymTables[TAB_UNDEF], rdi )

        ; the text macro was referenced before being defined.
        ; this is valid usage, but it requires a full second pass.
        ; just simply deactivate the fastpass feature for this module!

        SkipSavedState()

        ; v2.21: changed from 8016 to 6005

        asmerr( 6005, [rdi].asym.name )
    .elseif ( [rdi].asym.state != SYM_TMACRO )
        asmerr( 2005, name )
       .return( NULL )
    .endif
    mov [rdi].asym.state,SYM_TMACRO
    mov [rdi].asym.isdefined,1
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
    mov byte ptr [rdx+rsi],0
    .return( rdi )
    endp


; create a (predefined) text macro.
; used to create @code, @data, ...
; there are 2 more locations where predefined text macros may be defined:
; - assemble.c, add_cmdline_tmacros()
; - symbols.c, SymInit()
; this should be changed eventually.

AddPredefinedText proc __ccall name:string_t, value:string_t

    ; v2.08: ignore previous setting

    .if !SymFind( name )
        SymGCreate( name )
    .endif
    mov [rax].asym.state,SYM_TMACRO
    mov [rax].asym.isdefined,1
    mov [rax].asym.predefined,1
    mov rcx,value
    mov [rax].asym.string_ptr,rcx

    ; to ensure that a new buffer is used if the string is modified

    mov [rax].asym.total_size,0
    ret
    endp


; SubStr()
; defines a text equate.
; syntax: name SUBSTR <string>, pos [, size]

SubStrDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

   .new name:string_t
   .new p:string_t
   .new pos:int_t
   .new cnt:int_t
   .new chksize:int_t
   .new opndx:expr

    ; at least 5 items are needed
    ; 0  1      2      3 4    5   6
    ; ID SUBSTR SRC_ID , POS [, LENGTH]

    ldr rbx,tokenarray
    mov name,[rbx].string_ptr

    inc i ; go past SUBSTR
    imul eax,i,asm_tok
    add rbx,rax

    ; third item must be a string

    .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )
        .return( TextItemError( rbx ) )
    .endif
    mov p,[rbx].string_ptr
    mov cnt,[rbx].stringlen

    inc i
    add rbx,asm_tok

    .if ( [rbx].token != T_COMMA )
        .return( asmerr( 2008, [rbx].tokpos ) )
    .endif
    inc i

    ; get pos, must be a numeric value and > 0
    ; v2.11: flag NOUNDEF added - no forward ref possible

    .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF ) == ERROR )
        .return( ERROR )
    .endif

    ; v2.04: "string" constant allowed as second argument
    .if ( opndx.kind != EXPR_CONST )
        .return( asmerr( 2026 ) )
    .endif

    ; pos is expected to be 1-based

    imul ebx,i,asm_tok
    add  rbx,tokenarray
    mov  pos,opndx.value

    .ifs ( pos <= 0 )
        .return( asmerr( 2090 ) )
    .endif
    .if ( [rbx].token != T_FINAL )
        .if ( [rbx].token != T_COMMA )
            .return( asmerr( 2008, [rbx].tokpos ) )
        .endif
        inc i
        .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF ) == ERROR )
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
    mov ebx,pos
    .if ( ebx > cnt )
        .return( asmerr( 2091, ebx ) )
    .endif
    lea eax,[rbx+rdi-1]
    .if ( chksize && eax > cnt )
        .return( asmerr( 2093 ) )
    .endif
    lea rax,[rbx-1]
    add p,rax
    .if ( edi == -1 )
        mov eax,cnt
        sub eax,ebx
        lea edi,[rax+1]
    .endif
    mov rsi,SymFind( name )

    ; if we've never seen it before, put it in

    .if ( rsi == NULL )
        mov rsi,SymGCreate( name )
    .elseif( [rsi].asym.state == SYM_UNDEFINED )

        ; it was referenced before being defined. This is
        ; a bad idea for preprocessor text items, because it
        ; will require a full second pass!

        sym_remove_table( &SymTables[TAB_UNDEF], rsi )
        SkipSavedState()

        ; v2.21: changed from 8016 to 6005

        asmerr( 6005, [rsi].asym.name )

    .elseif ( [rsi].asym.state != SYM_TMACRO )

        ;; it is defined as something incompatible, get out

        .return( asmerr( 2005, [rsi].asym.name ) )
    .endif

    mov [rsi].asym.state,SYM_TMACRO
    mov [rsi].asym.isdefined,1
    inc edi
    .if ( [rsi].asym.total_size < edi )
        mov [rsi].asym.total_size,edi
        mov [rsi].asym.string_ptr,LclAlloc(edi)
    .endif
    dec edi
    tmemcpy( [rsi].asym.string_ptr, p, edi )
    mov byte ptr [rax+rdi],0
    LstWrite( LSTTYPE_TMACRO, 0, rsi )
    .return( NOT_ERROR )
    endp


; SizeStr()
; defines a numeric variable which contains size of a string

SizeStrDir proc __ccall uses rbx i:int_t, tokenarray:token_t

    ldr ecx,i
    ldr rdx,tokenarray
    .if ( ecx != 1 )
        imul ebx,ecx,asm_tok
        add  rbx,rdx
       .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif
    mov rbx,rdx
    .if ( [rbx+2*asm_tok].token != T_STRING || [rbx+2*asm_tok].string_delim != '<' )
        .return( TextItemError( &[rbx+2*asm_tok] ) )
    .endif
    .if ( TokenCount > 3 )
        .return( asmerr(2008, [rbx+3*asm_tok].string_ptr ) )
    .endif
    .if ( CreateVariable( [rbx].string_ptr, [rbx+2*asm_tok].stringlen ) )
        LstWrite( LSTTYPE_EQUATE, 0, rax )
       .return( NOT_ERROR )
    .endif
    .return( ERROR )
    endp


; InStr()
; defines a numeric variable which contains position of substring.
; syntax:
; name INSTR [pos,]string, substr

InStrDir proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local opndx:expr
  local start:int_t

    ldr ecx,i
    ldr rdx,tokenarray

    mov start,1
    imul ebx,ecx,asm_tok
    add rbx,rdx
    .if ( ecx != 1 )
        .return( asmerr( 2008, [rbx].string_ptr ) )
    .endif

    inc i ;; go past INSTR
    add rbx,asm_tok
    .if ( [rbx].token != T_STRING || [rbx].string_delim != '<' )

        ; v2.11: flag NOUNDEF added - no forward reference accepted

        .ifd ( EvalOperand( &i, tokenarray, TokenCount, &opndx, EXPF_NOUNDEF ) == ERROR )
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
        .return( asmerr( 2008, [rbx+asm_tok].string_ptr ) )
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
    endp


; internal @CatStr macro function
; syntax: @CatStr( literal [, literal ...] )

CatStrFunc proc __ccall private uses rsi rdi rbx mi:ptr macro_instance, buffer:string_t, tokenarray:token_t

    ldr rdi,mi
    .for ( rsi = [rdi].macro_instance.parm_array,
           rsi = [rsi]: [rdi].macro_instance.parmcnt: [rdi].macro_instance.parmcnt-- )
        mov ebx,tstrlen( rsi )
        tmemcpy( buffer, rsi, ebx )
        mov rsi,GetAlignedPointer( rsi, ebx )
        add buffer,rbx
    .endf
    mov rdx,buffer
    mov byte ptr [rdx],0
    .return( NOT_ERROR )
    endp


ifdef USE_COMALLOC
ComAlloc proto __ccall :string_t, :token_t
ComAllocFunc proc __ccall private mi:ptr macro_instance, buffer:string_t, tokenarray:token_t
    .if ( ComAlloc( buffer, tokenarray ) == 0 )
        mov rdx,mi
        mov rdx,[rdx].macro_instance.parm_array
        tstrcpy( buffer, [rdx] )
    .endif
    .return( NOT_ERROR )
    endp
endif


TypeIdFunc proc __ccall private mi:ptr macro_instance, buffer:string_t, tokenarray:token_t
    .if ( GetTypeId( buffer, tokenarray ) == 0 )
        mov rdx,mi
        mov rdx,[rdx].macro_instance.parm_array
        tstrcpy( buffer, [rdx] )
    .endif
    .return( NOT_ERROR )
    endp


; internal @CStr macro function
; syntax:  @CStr( "\tstring\n" )

CStringFunc proc __ccall private mi:ptr macro_instance, buffer:string_t, tokenarray:token_t
    .if ( CString( buffer, tokenarray ) == 0 )
        mov rdx,mi
        mov rdx,[rdx].macro_instance.parm_array
        tstrcpy( buffer, [rdx] )
    .endif
    .return( NOT_ERROR )
    endp

; convert register to reg8/16/32/64.
;
; @Reg( reg )
; @Reg( reg, size )

RegFunc proc __ccall private uses rbx mi:ptr macro_instance, buffer:string_t, tokenarray:token_t

   .new opnd:expr
   .new i:int_t
   .new size:int_t = 4 ; default size
   .new reg:int_t

    ldr rcx,mi
    mov rbx,[rcx].macro_instance.parm_array
    mov rcx,[rbx]
    .if ( rcx == NULL )
        .return( NOT_ERROR )
    .endif
    mov eax,TokenCount
    inc eax
    mov i,eax
    mov reg,eax
    mov ecx,Tokenize( rcx, eax, tokenarray, TOK_RESCAN )
    .ifd ( EvalOperand( &reg, tokenarray, ecx, &opnd, EXPF_NOUNDEF ) == ERROR )
        .return
    .endif
    .if ( opnd.kind != EXPR_REG )
        imul ecx,reg,asm_tok
        add rcx,tokenarray
       .return( asmerr(2008, [rcx-asm_tok].asm_tok.string_ptr ) )
    .endif
    mov rcx,opnd.base_reg
    mov reg,[rcx].asm_tok.tokval
    mov rcx,[rbx+string_t]
    .if ( rcx != NULL )
        mov ecx,Tokenize( rcx, i, tokenarray, TOK_RESCAN )
        .ifd ( EvalOperand( &i, tokenarray, ecx, &opnd, EXPF_NOUNDEF ) == ERROR )
            .return
        .endif
        mov size,opnd.value
        .if ( opnd.kind != EXPR_CONST || eax < 1 || eax > 8 )

            imul ecx,i,asm_tok
            add rcx,tokenarray
           .return( asmerr(2008, [rcx-asm_tok].asm_tok.string_ptr ) )
        .endif
    .endif
    mov ecx,get_register( reg, size )
    GetResWName( ecx, buffer )
    .return( NOT_ERROR )
    endp


; convert string to a number.
; used by @SubStr() for arguments 2 and 3 (start and size),
; and by @InStr() for argument 1 ( start )

GetNumber2 proc __ccall private string:string_t, pi:ptr int_t, tokenarray:token_t

  local opndx:expr
  local i:int_t

    mov eax,TokenCount
    inc eax
    mov i,eax
    mov edx,Tokenize( string, eax, tokenarray, TOK_RESCAN )
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
    endp


; internal @InStr macro function
; syntax: @InStr( [num], literal, literal )
; the result is returned as string in current radix

InStrFunc proc __ccall private uses rsi rdi rbx mi:ptr macro_instance,
        buffer:string_t, tokenarray:token_t

   .new pos:int_t = 1

    ; init buffer with "0"

    ldr rcx,mi
    ldr rdi,buffer
    mov eax,'0'
    mov [rdi],ax
    mov rsi,[rcx].macro_instance.parm_array
    mov rbx,[rsi]
    .if ( rbx )
        .ifd ( GetNumber2( rbx, &pos, tokenarray ) == ERROR )
            .return( ERROR )
        .endif
        .if ( pos == 0 )

            ; adjust index 0. Masm also accepts 0 (and any negative index),
            ; but the result will always be 0 then
            inc pos
        .endif
    .endif
    mov rbx,[rsi+size_t]
    tstrlen(rbx)
    .if ( pos > eax )
        .return( asmerr( 2091, pos ) )
    .endif

    ; v2.08: if() added, empty searchstr is to return 0
    mov rdx,[rsi+size_t*2]
    .if ( byte ptr [rdx] != 0 )
        mov ecx,pos
        add rcx,rbx
        dec rcx
        .if tstrstr( rcx, rdx )
            sub rax,rbx
            lea rcx,[rax+1]
ifdef _WIN64
            myltoa( rcx, buffer, MODULE.radix, FALSE, TRUE )
else
            xor edx,edx
            myltoa( edx::ecx, buffer, MODULE.radix, FALSE, TRUE )
endif
        .endif
    .endif
    .return( NOT_ERROR )
    endp


; internal @SizeStr macro function
; syntax: @SizeStr( literal )
; the result is returned as string in current radix

SizeStrFunc proc __ccall private mi:ptr macro_instance, buffer:string_t, tokenarray:token_t

    ldr rcx,mi
    mov rdx,[rcx].macro_instance.parm_array
    mov rcx,[rdx]
    .if ( rcx )
        mov ecx,tstrlen( rcx )
ifdef _WIN64
        myltoa( rcx, buffer, MODULE.radix, FALSE, TRUE )
else
        xor edx,edx
        myltoa( edx::ecx, buffer, MODULE.radix, FALSE, TRUE )
endif
    .else
        mov rdx,buffer
        mov eax,'0'
        mov [rdx],ax
    .endif
    .return( NOT_ERROR )
    endp


; internal @SubStr macro function
; syntax: @SubStr( literal, num [, num ] )

SubStrFunc proc __ccall private uses rsi rdi rbx mi:ptr macro_instance, buffer:string_t, tokenarray:token_t

  local pos:int_t
  local size:int_t

    ldr rcx,mi
    mov rsi,[rcx].macro_instance.parm_array
    mov rdi,[rsi]
    .return .ifd ( GetNumber2( [rsi+size_t], &pos, tokenarray ) == ERROR )
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
    mov rdi,[rsi+size_t*2]
    .if ( rdi )
        .new sizereq:int_t
        .return .ifd ( GetNumber2( rdi, &sizereq, tokenarray ) == ERROR )
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
    mov byte ptr [rdi],0
    .return( NOT_ERROR )
    endp


; string macro initialization
; this proc is called once per module

    assume rdi:asym_t, rsi:macro_t

StringInit proc __ccall uses rsi rdi
ifdef USE_COMALLOC
    mov rdi,CreateMacro( "@ComAlloc" )
    mov [rdi].isdefined,1
    mov [rdi].predefined,1
    mov [rdi].func_ptr,&ComAllocFunc
    mov [rdi].isfunc,1
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,3
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) * 3 )
    mov [rax].mparm_list.required,TRUE
endif

    mov rdi,CreateMacro( "typeid" )
    mov [rdi].isdefined,1
    mov [rdi].predefined,1
    mov [rdi].func_ptr,&TypeIdFunc
    mov [rdi].isfunc,1
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,2
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) * 2 )

    mov rdi,CreateMacro( "@CStr" )
    mov [rdi].isdefined,1
    mov [rdi].predefined,1
    mov [rdi].func_ptr,&CStringFunc
    mov [rdi].isfunc,1
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,1
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) )
    mov [rax].mparm_list.required,TRUE

    mov rdi,CreateMacro( "@Reg" )
    mov [rdi].isdefined,1
    mov [rdi].predefined,1
    mov [rdi].func_ptr,&RegFunc
    mov [rdi].isfunc,1
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,2
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) * 2 )
    mov [rax].mparm_list.required,TRUE

    mov rdi,CreateMacro( "@CatStr" )
    mov [rdi].isdefined,1
    mov [rdi].predefined,1
    mov [rdi].func_ptr,&CatStrFunc
    mov [rdi].mac_vararg,1
    mov [rdi].isfunc,1
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,1
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) )

    mov rdi,CreateMacro( "@InStr" )
    mov [rdi].isdefined,1
    mov [rdi].predefined,1
    mov [rdi].func_ptr,&InStrFunc
    mov [rdi].isfunc,1
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,3
    mov [rsi].autoexp,1
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) * 3 )
    mov [rax].mparm_list[mparm_list].required,TRUE
    mov [rax].mparm_list[mparm_list*2].required,TRUE

    mov rdi,CreateMacro( "@SizeStr" )
    mov [rdi].isdefined,1
    mov [rdi].predefined,1
    mov [rdi].func_ptr,&SizeStrFunc
    mov [rdi].isfunc,1
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,1
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) )

    mov rdi,CreateMacro( "@SubStr" )
    mov [rdi].isdefined,1
    mov [rdi].predefined,1
    mov [rdi].func_ptr,&SubStrFunc
    mov [rdi].isfunc,1
    mov rsi,[rdi].macroinfo
    mov [rsi].parmcnt,3
    mov [rsi].autoexp,2 + 4 ;; param 2 (pos) and 3 (size) are expanded
    mov [rsi].parmlist,LclAlloc( sizeof( mparm_list ) * 3 )
    mov [rax].mparm_list.required,TRUE
    mov [rax].mparm_list[mparm_list].required,TRUE
    ret
    endp

    end
