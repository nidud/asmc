;
; .for <initialization>: <condition>: <increment/decrement>
;
include string.inc
include asmc.inc
include token.inc
include hll.inc

    .code

strtrim PROC string:LPSTR

    .if strlen( string )

        mov ecx,eax
        add ecx,string
        .while 1
            dec ecx
            .break .if byte ptr [ecx] > ' '
            mov byte ptr [ecx],0
            dec eax
            .break .if ZERO?
        .endw
    .endif
    ret

strtrim ENDP

GetCondition proc private string:ptr sbyte

    mov ecx,string
    mov al,[ecx]

    .while al == ' ' || al == 9
        add ecx,1
        mov al,[ecx]
    .endw

    mov string,ecx
    xor edx,edx

    .while 1

        mov al,[ecx]
        .switch al
          .case 0   : .break
          .case '(' : inc edx : .endc
          .case ')' : dec edx : .endc
          .case ',' : .endc .if edx

            mov [ecx],dl
            mov al,[ecx-1]
            .if al == ' ' || al == 9

                mov [ecx-1],dl
            .endif
            inc ecx
            mov al,[ecx]
            .while  al == ' ' || al == 9
                inc ecx
                mov al,[ecx]
            .endw
            mov edx,string
            .if BYTE PTR [edx] == 0 && al

                mov string,ecx
                xor edx,edx
                .continue(0)
            .endif
            .break
        .endsw

        add ecx,1
    .endw

    mov edx,string
    movzx eax,BYTE PTR [edx]
    ret

GetCondition ENDP

Assignopc proc private uses edi buffer:LPSTR, opc1:LPSTR, opc2:LPSTR, string:LPSTR

    mov edi,buffer

    .if ( opc1 )
        strcat( edi, opc1 )
        strtrim( edi )
        strcat( edi, " " )
    .endif
    .if ( opc2 )
        strcat( edi, opc2 )
        strtrim( edi );
        .if ( opc1 && string )
            strcat( edi, "," )
        .endif
        .if ( string )
            strcat( edi, " " )
        .endif
    .endif
    .if ( string )
        strcat( edi, string )
        strtrim( edi )
    .endif
    strcat( edi, "\n" )
    mov eax,1
    ret

Assignopc endp

ParseAssignment proc private uses esi edi ebx buffer:ptr sbyte, tokenarray:ptr asmtok

    mov edi,buffer
    mov ebx,tokenarray

    assume ebx:ptr asmtok
    assume esi:ptr asmtok

    mov edx,[ebx].string_ptr
    mov cl,[ebx].token
    mov ch,[ebx+16].token
    mov eax,[edx]

    .repeat

        .switch
        .case ( al == '~' )
            Assignopc( edi, "not", &[edx+1], NULL )
            .break
        .case ( cl == '-' && ch == '-' )
            Assignopc( edi, "dec", [ebx+16*2].tokpos, NULL )
            .break
        .case ( cl == '+' && ch == '+' )
            Assignopc( edi, "inc", [ebx+16*2].tokpos, NULL )
            .break
        .endsw

        .for ( eax = 0, ecx = 1: ecx < Token_Count: ecx++ )

            lea esi,[ecx*4]
            lea esi,[ebx+esi*4]
            mov edx,[esi].string_ptr
            mov edx,[edx]

            .if ( [esi].tokval == T_EQU && [esi].dirtype == DRT_EQUALSGN ) || \
                [esi].token == '+' || [esi].token == '-' || [esi].token == '&'

                mov eax,[esi].tokpos
                mov dl,[eax]
                mov dh,[esi+16].token
                mov ecx,[esi+16].tokpos
                .break

            .elseif [esi].token == T_STRING

                .if dl == '>' || dl == '<'

                    mov eax,[esi].tokpos
                    lea ecx,[eax+3]
                    .if byte ptr [ecx] == 0
                        mov ecx,[esi+16].tokpos
                    .endif
                    .break

                .elseif dl == '|' || dl == '~' || dl == '^'

                    mov eax,[esi].tokpos
                    lea ecx,[eax+2]
                    .if byte ptr [ecx] == 0
                        mov ecx,[esi+16].tokpos
                    .endif
                    .break
                .endif
            .endif
        .endf

        .if !eax

            asmerr( 2008, [ebx].tokpos )
            xor eax,eax
            .break
        .endif

        .switch dl

        .case '='
            mov byte ptr [eax],0
            .if dh == '&'
                Assignopc( edi, "lea", [ebx].tokpos, [esi+32].tokpos )
            .elseif byte ptr [ecx] == '~'
                Assignopc( edi, "mov", [ebx].tokpos, &[ecx+1] )
                Assignopc( edi, "not", [ebx].tokpos, NULL )
            .else
                ;;
                ;; mov reg,0 --> xor reg,reg
                ;;
                mov eax,[esi+16].string_ptr
                mov ax,[eax]
                .if ( dh == T_NUM && ax == '0' && \
                    ( ( [ebx].tokval >= T_AL && [ebx].tokval <= T_EDI ) || \
                    ( ModuleInfo.Ofssize == USE64 && [ebx].tokval >= T_R8B && [ebx].tokval <= T_R15 ) ) )
                    Assignopc( edi, "xor", [ebx].string_ptr, [ebx].string_ptr )
                .else
                    Assignopc( edi, "mov", [ebx].tokpos, ecx )
                .endif
            .endif
            .break

        .case '|'
            .endc .if dh != '='
            mov byte ptr [eax],0
            Assignopc( edi, "or ", [ebx].tokpos, ecx )
            .break
        .case '~'
            .endc .if dh != '='
            mov byte ptr [eax],0
            Assignopc( edi, "mov", [ebx].tokpos, ecx )
            Assignopc( edi, "not", [ebx].tokpos, NULL )
            .break
        .case '^'
            .endc .if dh != '='
            mov byte ptr [eax],0
            Assignopc( edi, "xor", [ebx].tokpos, ecx )
            .break
        .case '&'
            .endc .if [esi+16].dirtype != DRT_EQUALSGN
            mov byte ptr [eax],0
            Assignopc( edi, "and", [ebx].tokpos, [esi+32].tokpos )
            .break
        .case '>'
            shr edx,8
            .endc .if !( dl == '>' && dh == '=' )
            mov byte ptr [eax],0
            Assignopc( edi, "shr", [ebx].tokpos, ecx )
            .break
        .case '<'
            shr edx,8
            .endc .if !( dl == '<' && dh == '=' )
            mov byte ptr [eax],0
            Assignopc( edi, "shl", [ebx].tokpos, ecx )
            .break

        .case '+'
            .if dh == '+'
                mov byte ptr [eax],0
                Assignopc( edi, "inc", [ebx].tokpos, NULL )
                .break
            .elseif [esi+16].dirtype == DRT_EQUALSGN
                mov byte ptr [eax],0
                Assignopc( edi, "add", [ebx].tokpos, [esi+32].tokpos )
                .break
            .endif
            .endc
        .case '-'
            .if dh == '-'
                mov byte ptr [eax],0
                Assignopc( edi, "dec", [ebx].tokpos, NULL )
                .break
            .elseif [esi+16].dirtype == DRT_EQUALSGN
                mov byte ptr [eax],0
                Assignopc( edi, "sub", [ebx].tokpos, [esi+32].tokpos )
                .break
            .endif
            .endc
        .endsw

        asmerr( 2008, [esi].tokpos )
        xor eax,eax
    .until 1
    ret

    assume ebx:nothing
    assume esi:nothing

ParseAssignment endp

RenderAssignment proc private uses esi edi ebx dest:ptr sbyte,
    source:ptr sbyte, tokenarray:ptr asmtok

  local buffer[MAX_LINE_LEN]:SBYTE
  local tokbuf[MAX_LINE_LEN]:SBYTE

    mov edi,source
    lea esi,buffer
    ;
    ; <expression1>, <expression2>, ..., [: | 0]
    ;
    .while GetCondition(edi)

        mov ebx,ecx ; next expression
        mov edi,edx ; this expression
        Tokenize( strcpy( &tokbuf, edi ), 0, tokenarray, TOK_DEFAULT )
        mov Token_Count,eax

        .break .if ExpandHllProc( esi, 0, tokenarray ) == ERROR

        .if byte ptr [esi] ; function calls expanded

            strcat( strcat( dest, esi ), "\n" )
            mov byte ptr [esi],0
        .endif

        .break .if !ParseAssignment( esi, tokenarray )
        strcat( strcat( dest, esi ), "\n" )
        mov edi,ebx
    .endw
    mov eax,dest
    movzx eax,byte ptr [eax]
    ret

RenderAssignment endp

    assume  ebx:ptr asmtok
    assume  esi:ptr hll_item

ForDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asmtok

local   rc:SINT,
        cmd:UINT,
        p:LPSTR,
        q:LPSTR,
        buff[16]:SBYTE,
        buffer[MAX_LINE_LEN]:SBYTE,
        cmdstr[MAX_LINE_LEN]:SBYTE,
        tokbuf[MAX_LINE_LEN]:SBYTE

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,buffer

    mov eax,i
    shl eax,4
    mov eax,[ebx+eax].tokval
    mov cmd,eax
    inc i

    .repeat
        .if eax == T_DOT_ENDF

            mov esi,ModuleInfo.HllStack
            .if !esi

                asmerr(1011)
                .break
            .endif

            mov edx,[esi].next
            mov ecx,ModuleInfo.HllFree
            mov ModuleInfo.HllStack,edx
            mov [esi].next,ecx
            mov ModuleInfo.HllFree,esi

            .if [esi].cmd != HLL_WHILE

                asmerr( 1011 )
                .break
            .endif

            mov eax,[esi].labels[LTEST*4]
            .if eax

                AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), LABELQUAL )
            .endif

            .if [esi].condlines

                QueueTestLines( [esi].condlines )
            .endif

            AddLineQueueX( "jmp %s", GetLabelStr( [esi].labels[LSTART*4], edi ) )

            mov eax,[esi].labels[LEXIT*4]
            .if eax

                AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), LABELQUAL )
            .endif
            mov eax,i
            shl eax,4
            add ebx,eax
            .if [ebx].token != T_FINAL && rc == NOT_ERROR

                mov rc,asmerr( 2008, [ebx].tokpos )
            .endif
        .else

            mov esi,ModuleInfo.HllFree
            .if !esi

                mov esi,LclAlloc( sizeof( hll_item ) )
            .endif
            ExpandCStrings(tokenarray)

            xor eax,eax
            mov [esi].labels[LEXIT*4],eax
            .if cmd == T_DOT_FORS

                or eax,HLLF_IFS
            .endif
            mov [esi].flags,eax
            mov [esi].cmd,HLL_WHILE

            ; create the loop labels

            mov [esi].labels[LSTART*4],GetHllLabel()
            mov [esi].labels[LTEST*4],GetHllLabel()
            mov [esi].labels[LEXIT*4],GetHllLabel()

            mov eax,i
            shl eax,4
            add ebx,eax
            .if [ebx].token == T_OP_BRACKET

                inc i
                add ebx,16
            .endif

            .if !strchr(strcpy(edi, [ebx].tokpos), ':')

                asmerr( 2206 )
                .break
            .endif

            mov BYTE PTR [eax],0
            inc eax
            M_SKIP_SPACE ecx, eax
            mov p,eax
            .if !strchr(eax, ':')

                asmerr( 2206 )
                .break
            .endif

            mov BYTE PTR [eax],0
            inc eax
            M_SKIP_SPACE ecx, eax
            mov q,eax
            strtrim(eax)
            M_SKIP_SPACE ecx, edi
            strtrim(edi)
            strtrim(p)

            .if [ebx-16].token == T_OP_BRACKET

                .if strrchr(q, ')')

                    mov BYTE PTR [eax],0
                    strtrim(q)
                .endif
            .endif

            lea ebx,cmdstr
            mov BYTE PTR [ebx],0
            .if RenderAssignment(ebx, edi, tokenarray)

                QueueTestLines( ebx )
            .endif
            AddLineQueueX( "%s%s",
                GetLabelStr( [esi].labels[LSTART*4], &buff ), LABELQUAL )

            mov BYTE PTR [ebx],0
            mov [esi].condlines,0

            .if RenderAssignment(ebx, q, tokenarray)

                strlen( ebx )
                inc eax
                push    eax
                LclAlloc( eax )
                pop ecx
                mov [esi].condlines,eax
                memcpy( eax, ebx, ecx )
            .endif

            mov edi,p
            mov BYTE PTR [ebx],0
            .while GetCondition(edi)

                push ecx
                mov edi,edx

                lea edx,tokbuf
                Tokenize( strcat( strcpy( edx, ".if " ), edi ),
                    0, tokenarray, TOK_DEFAULT )
                mov ModuleInfo.token_count,eax

                mov i,1
                EvaluateHllExpression( esi, &i, tokenarray,
                    LEXIT, 0, ebx )
                mov rc,eax

                .if eax == NOT_ERROR

                    QueueTestLines( ebx )
                .endif
                pop edi
            .endw

            .if esi == ModuleInfo.HllFree

                mov eax,[esi].next
                mov ModuleInfo.HllFree,eax
            .endif

            mov eax,ModuleInfo.HllStack
            mov [esi].next,eax
            mov ModuleInfo.HllStack,esi

        .endif

        .if ModuleInfo.list

            LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
        .endif

        .if ModuleInfo.line_queue.head

            RunLineQueue()
        .endif

        mov eax,rc

    .until  1
    ret

ForDirective endp

    END
