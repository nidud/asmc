; FOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; .for <initialization>: <condition>: <increment/decrement>
;

include string.inc
include asmc.inc
include tokenize.inc
include hll.inc
include parser.inc
include hllext.inc

    .code

strtrim proc private string:string_t

    .if tstrlen( string )

        mov ecx,eax
        add rcx,string
        .while 1
            dec rcx
            .break .if byte ptr [rcx] > ' '
            mov byte ptr [rcx],0
            dec eax
            .break .ifz
        .endw
    .endif
    ret

strtrim endp

GetCondition proc private string:ptr sbyte

    mov rcx,string
    mov al,[rcx]

    .while al == ' ' || al == 9
        inc rcx
        mov al,[rcx]
    .endw

    mov string,rcx
    xor edx,edx

    .while 1

        mov al,[rcx]
        .switch al
          .case 0   : .break
          .case '(' : inc edx : .endc
          .case ')' : dec edx : .endc
          .case ',' : .endc .if edx

            mov [rcx],dl
            mov al,[rcx-1]
            .if al == ' ' || al == 9

                mov [rcx-1],dl
            .endif
            inc rcx
            mov al,[rcx]
            .while  al == ' ' || al == 9
                inc rcx
                mov al,[rcx]
            .endw
            mov rdx,string
            .if BYTE PTR [rdx] == 0 && al

                mov string,rcx
                xor edx,edx
                .continue(0)
            .endif
            .break
        .endsw

        inc rcx
    .endw

    mov rdx,string
    movzx eax,BYTE PTR [rdx]
    ret

GetCondition ENDP

Assignopc proc private uses rdi buffer:string_t, opc1:string_t, opc2:string_t, string:string_t

    mov rdi,buffer

    .if ( opc1 )
        strcat( rdi, opc1 )
        strtrim( rdi )
        strcat( rdi, " " )
    .endif
    .if ( opc2 )
        strcat( rdi, opc2 )
        strtrim( rdi );
        .if ( opc1 && string )
            strcat( rdi, "," )
        .endif
        .if ( string )
            strcat( rdi, " " )
        .endif
    .endif
    .if ( string )
        strcat( rdi, string )
        strtrim( rdi )
    .endif
    strcat( rdi, "\n" )
    mov eax,1
    ret

Assignopc endp

ParseAssignment proc private uses rsi rdi rbx buffer:ptr sbyte, tokenarray:ptr asm_tok

  local bracket:byte ; assign value: [rdx+8]=rax - @v2.28.15

    mov rdi,buffer
    mov rbx,tokenarray

    assume rbx:ptr asm_tok
    assume rsi:ptr asm_tok

    mov rdx,[rbx].string_ptr
    mov cl,[rbx].token
    mov ch,[rbx+asm_tok].token
    mov eax,[rdx]

    mov bracket,0
    .if ( cl == T_OP_SQ_BRACKET )
        inc bracket
    .endif

    .repeat

        .switch
        .case ( al == '~' )
            Assignopc( rdi, "not", &[rdx+1], NULL )
            .break
        .case ( cl == '-' && ch == '-' )
            Assignopc( rdi, "dec", [rbx+asm_tok*2].tokpos, NULL )
            .break
        .case ( cl == '+' && ch == '+' )
            Assignopc( rdi, "inc", [rbx+asm_tok*2].tokpos, NULL )
            .break
        .endsw

        .for ( eax = 0, ecx = 1: ecx < Token_Count: ecx++ )

            imul esi,ecx,asm_tok
            add rsi,rbx
            mov rdx,[rsi].string_ptr
            mov edx,[rdx]

            .switch

            .case [rsi].token == T_OP_SQ_BRACKET
                inc bracket
                .endc
            .case [rsi].token == T_CL_SQ_BRACKET
                dec bracket
            .case bracket
                .endc

            .case [rsi].token == '+'
            .case [rsi].token == '-'
            .case [rsi].token == '&'
            .case [rsi].tokval == T_EQU && [rsi].dirtype == DRT_EQUALSGN

                mov rax,[rsi].tokpos
                mov dl,[rax]
                mov dh,[rsi+asm_tok].token
                mov rcx,[rsi+asm_tok].tokpos
                .break

            .case [rsi].token == T_STRING

                .switch dl

                .case '>'
                .case '<'

                    mov rax,[rsi].tokpos
                    lea rcx,[rax+3]
                    .if byte ptr [rcx] == 0
                        mov rcx,[rsi+asm_tok].tokpos
                    .endif
                    .break

                .case '|'
                .case '~'
                .case '^'

                    mov rax,[rsi].tokpos
                    lea rcx,[rax+2]
                    .if byte ptr [rcx] == 0
                        mov rcx,[rsi+asm_tok].tokpos
                    .endif
                    .break
                .endsw
            .endsw
        .endf

        .if !eax

            asmerr( 2008, [rbx].tokpos )
            xor eax,eax
            .break
        .endif

        .switch dl

        .case '='
            mov byte ptr [rax],0
            .if dh == '&'
                Assignopc( rdi, "lea", [rbx].tokpos, [rsi+asm_tok*2].tokpos )
            .elseif byte ptr [rcx] == '~'
                Assignopc( rdi, "mov", [rbx].tokpos, &[rcx+1] )
                Assignopc( rdi, "not", [rbx].tokpos, NULL )
            .else
                ;
                ; mov reg,0 --> xor reg,reg
                ;
                mov rax,[rsi+asm_tok].string_ptr
                mov ax,[rax]
                .if ( dh == T_NUM && ax == '0' && \
                    ( ( [rbx].tokval >= T_AL && [rbx].tokval <= T_EDI ) || \
                    ( ModuleInfo.Ofssize == USE64 && [rbx].tokval >= T_R8B && [rbx].tokval <= T_R15 ) ) )
                    Assignopc( rdi, "xor", [rbx].string_ptr, [rbx].string_ptr )
                .else
                    Assignopc( rdi, "mov", [rbx].tokpos, rcx )
                .endif
            .endif
            .break

        .case '|'
            .endc .if dh != '='
            mov byte ptr [rax],0
            Assignopc( rdi, "or ", [rbx].tokpos, rcx )
            .break
        .case '~'
            .endc .if dh != '='
            mov byte ptr [rax],0
            Assignopc( rdi, "mov", [rbx].tokpos, rcx )
            Assignopc( rdi, "not", [rbx].tokpos, NULL )
            .break
        .case '^'
            .endc .if dh != '='
            mov byte ptr [rax],0
            Assignopc( rdi, "xor", [rbx].tokpos, rcx )
            .break
        .case '&'
            .endc .if [rsi+asm_tok].dirtype != DRT_EQUALSGN
            mov byte ptr [rax],0
            Assignopc( rdi, "and", [rbx].tokpos, [rsi+asm_tok*2].tokpos )
            .break
        .case '>'
            shr edx,8
            .endc .if !( dl == '>' && dh == '=' )
            mov byte ptr [rax],0
            Assignopc( rdi, "shr", [rbx].tokpos, rcx )
            .break
        .case '<'
            shr edx,8
            .endc .if !( dl == '<' && dh == '=' )
            mov byte ptr [rax],0
            Assignopc( rdi, "shl", [rbx].tokpos, rcx )
            .break

        .case '+'
            .if dh == '+'
                mov byte ptr [rax],0
                Assignopc( rdi, "inc", [rbx].tokpos, NULL )
                .break
            .elseif [rsi+asm_tok].dirtype == DRT_EQUALSGN
                mov byte ptr [rax],0
                Assignopc( rdi, "add", [rbx].tokpos, [rsi+asm_tok*2].tokpos )
                .break
            .endif
            .endc
        .case '-'
            .if dh == '-'
                mov byte ptr [rax],0
                Assignopc( rdi, "dec", [rbx].tokpos, NULL )
                .break
            .elseif [rsi+asm_tok].dirtype == DRT_EQUALSGN
                mov byte ptr [rax],0
                Assignopc( rdi, "sub", [rbx].tokpos, [rsi+asm_tok*2].tokpos )
                .break
            .endif
            .endc
        .endsw

        asmerr( 2008, [rsi].tokpos )
        xor eax,eax
    .until 1
    ret

    assume rbx:nothing
    assume rsi:nothing

ParseAssignment endp

RenderAssignment proc private uses rsi rdi rbx dest:ptr sbyte,
    source:ptr sbyte, tokenarray:ptr asm_tok

  local buffer[MAX_LINE_LEN]:char_t
  local tokbuf[MAX_LINE_LEN]:char_t

    mov rdi,source
    lea rsi,buffer
    ;
    ; <expression1>, <expression2>, ..., [: | 0]
    ;
    .while GetCondition(rdi)

        mov rbx,rcx ; next expression
        mov rdi,rdx ; this expression
        Tokenize( strcpy( &tokbuf, rdi ), 0, tokenarray, TOK_DEFAULT )
        mov Token_Count,eax

        .break .ifd ExpandHllProc( rsi, 0, tokenarray ) == ERROR

        .if byte ptr [rsi] ; function calls expanded

            strcat( strcat( dest, rsi ), "\n" )
            mov byte ptr [rsi],0
        .endif

        .break .if !ParseAssignment( rsi, tokenarray )
        strcat( strcat( dest, rsi ), "\n" )
        mov rdi,rbx
    .endw
    mov rax,dest
    movzx eax,byte ptr [rax]
    ret

RenderAssignment endp

    assume  rbx:ptr asm_tok
    assume  rsi:ptr hll_item

ForDirective proc uses rsi rdi rbx i:int_t, tokenarray:ptr asm_tok

  local rc:int_t,
        cmd:uint_t,
        p:string_t,
        q:string_t,
        buff[16]:char_t,
        buffer[MAX_LINE_LEN]:char_t,
        cmdstr[MAX_LINE_LEN]:char_t,
        tokbuf[MAX_LINE_LEN]:char_t

    mov rc,NOT_ERROR
    mov rbx,tokenarray
    lea rdi,buffer

    imul eax,i,asm_tok
    mov eax,[rbx+rax].tokval
    mov cmd,eax
    inc i

    .if eax == T_DOT_ENDF

        mov rsi,ModuleInfo.HllStack
        .if !rsi
            .return asmerr(1011)
        .endif

        mov rdx,[rsi].next
        mov rcx,ModuleInfo.HllFree
        mov ModuleInfo.HllStack,rdx
        mov [rsi].next,rcx
        mov ModuleInfo.HllFree,rsi

        .if [rsi].cmd != HLL_FOR
            .return asmerr(1011)
        .endif

        mov eax,[rsi].labels[LTEST*4]
        .if eax

            AddLineQueueX( "%s%s", GetLabelStr( eax, rdi ), LABELQUAL )
        .endif

        .if [rsi].condlines

            QueueTestLines( [rsi].condlines )
        .endif

        AddLineQueueX( "jmp %s", GetLabelStr( [rsi].labels[LSTART*4], rdi ) )

        mov eax,[rsi].labels[LEXIT*4]
        .if eax

            AddLineQueueX( "%s%s", GetLabelStr( eax, rdi ), LABELQUAL )
        .endif
        imul eax,i,asm_tok
        add rbx,rax
        .if [rbx].token != T_FINAL && rc == NOT_ERROR

            mov rc,asmerr( 2008, [rbx].tokpos )
        .endif

    .else

        mov rsi,ModuleInfo.HllFree
        .if !rsi

            mov rsi,LclAlloc(hll_item)
        .endif
        ExpandCStrings(tokenarray)

        xor eax,eax
        mov [rsi].labels[LEXIT*4],eax
        .if cmd == T_DOT_FORS

            or eax,HLLF_IFS
        .endif
        mov [rsi].flags,eax
        mov [rsi].cmd,HLL_FOR

        ; create the loop labels

        mov [rsi].labels[LSTART*4],GetHllLabel()
        mov [rsi].labels[LTEST*4],GetHllLabel()
        mov [rsi].labels[LEXIT*4],GetHllLabel()

        imul eax,i,asm_tok
        add rbx,rax
        .if [rbx].token == T_OP_BRACKET

            inc i
            add rbx,asm_tok
        .endif

        .if !strchr(strcpy(rdi, [rbx].tokpos), ':')

            .return asmerr(2206)
        .endif
        .if BYTE PTR [rax+1] == "'"
            .return asmerr(2206) .if !strchr(&[rax+1], ':')
        .endif

        mov BYTE PTR [rax],0
        inc rax
        mov p,tstrstart(rax)
        .if !strchr(rax, ':')

            .return asmerr( 2206 )
        .endif

        mov BYTE PTR [rax],0
        inc rax
        mov q,tstrstart(rax)
        strtrim(rax)
        mov rdi,tstrstart(rdi)
        strtrim(rdi)
        strtrim(p)

        .if [rbx-asm_tok].token == T_OP_BRACKET

            .if strrchr(q, ')')

                mov BYTE PTR [rax],0
                strtrim(q)
            .endif
        .endif

        lea rbx,cmdstr
        mov BYTE PTR [rbx],0
        .if RenderAssignment(rbx, rdi, tokenarray)

            QueueTestLines(rbx)
        .endif
        AddLineQueueX("%s%s",
                GetLabelStr( [rsi].labels[LSTART*4], &buff ), LABELQUAL )

        mov BYTE PTR [rbx],0
        mov [rsi].condlines,0

        .if RenderAssignment(rbx, q, tokenarray)

            mov edi,tstrlen(rbx)
            inc edi
            LclAlloc(edi)
            mov [rsi].condlines,rax
            tmemcpy(rax, rbx, ecx)
        .endif

        mov rdi,p
        mov BYTE PTR [rbx],0
        .while GetCondition(rdi)

            mov q,rcx
            mov rdi,rdx
            Tokenize(strcat(strcpy(&tokbuf, ".if "), rdi), 0, tokenarray, TOK_DEFAULT)
            mov ModuleInfo.token_count,eax

            mov i,1
            EvaluateHllExpression(rsi, &i, tokenarray, LEXIT, 0, rbx)
            mov rc,eax

            .if eax == NOT_ERROR

                QueueTestLines(rbx)
            .endif
            mov rdi,q
        .endw

        .if rsi == ModuleInfo.HllFree

            mov rax,[rsi].next
            mov ModuleInfo.HllFree,rax
        .endif

        mov rax,ModuleInfo.HllStack
        mov [rsi].next,rax
        mov ModuleInfo.HllStack,rsi

    .endif

    .if ModuleInfo.list

        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif

    .if ModuleInfo.line_queue.head

        RunLineQueue()
    .endif
    mov eax,rc
    ret

ForDirective endp

    END
