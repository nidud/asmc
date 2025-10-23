; FOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; .for <initialization>: <condition>: <increment/decrement>
;

include asmc.inc
include memalloc.inc
include tokenize.inc
include listing.inc
include segment.inc
include hll.inc
include parser.inc
include lqueue.inc

    .code

tstrtrim proc fastcall private uses rbx string:string_t

    mov rbx,rcx
    .if tstrlen( rcx )

        mov ecx,eax
        add rcx,rbx
        .while 1
            dec rcx
            .break .if byte ptr [rcx] > ' '
             mov byte ptr [rcx],0
             dec eax
            .break .ifz
        .endw
    .endif
    ret

tstrtrim endp


GetCondition proc fastcall private uses rbx string:ptr sbyte

    mov al,[rcx]

    .while al == ' ' || al == 9
        inc rcx
        mov al,[rcx]
    .endw

    mov rbx,rcx
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
            .if ( al == ' ' || al == 9 )

                mov [rcx-1],dl
            .endif
            inc rcx
            mov al,[rcx]
            .while ( al == ' ' || al == 9 )
                inc rcx
                mov al,[rcx]
            .endw
            mov rdx,rbx
            .if ( BYTE PTR [rdx] == 0 && al )

                mov rbx,rcx
                xor edx,edx
                .continue(0)
            .endif
            .break
        .endsw

        inc rcx
    .endw

    mov rdx,rbx
    movzx eax,BYTE PTR [rdx]
    ret

GetCondition ENDP


ParseAssignment proc __ccall private uses rsi rdi rbx buffer:ptr sbyte, tokenarray:token_t

  local bracket:byte ; assign value: [rdx+8]=rax - @v2.28.15

    ldr rdi,buffer
    ldr rbx,tokenarray

    assume rbx:token_t, rsi:token_t

    mov rdx,[rbx].string_ptr
    mov cl,[rbx].token
    mov ch,[rbx+asm_tok].token
    mov eax,[rdx]

    mov bracket,0
    .if ( cl == T_OP_SQ_BRACKET )
        inc bracket
    .endif

    .repeat

        xor esi,esi
        .switch
        .case ( al == '~' )
            inc rdx
            mov esi,T_NOT
           .endc
        .case ( cl == '-' && ch == '-' )
            mov rdx,[rbx+asm_tok*2].tokpos
            mov esi,T_DEC
           .endc
        .case ( cl == '+' && ch == '+' )
            mov rdx,[rbx+asm_tok*2].tokpos
            mov esi,T_INC
           .endc
        .endsw
        .if ( esi )
            tsprintf( rdi, "%r %s", esi, rdx )
           .break
        .endif

        .for ( eax = 0, ecx = 1: ecx < TokenCount: ecx++ )

            imul esi,ecx,asm_tok
            add rsi,rbx
            mov dl,[rsi].token

            .switch
            .case dl == T_OP_SQ_BRACKET
                inc bracket
               .endc
            .case dl == T_CL_SQ_BRACKET
                dec bracket
            .case bracket
               .endc

            .case dl == '+'
            .case dl == '-'
            .case dl == '&'
            .case [rsi].tokval == T_EQU && [rsi].dirtype == DRT_EQUALSGN

                mov rax,[rsi].tokpos
                mov dl,[rax]
                mov dh,[rsi+asm_tok].token
                mov rcx,[rsi+asm_tok].tokpos
               .break

            .case dl == T_STRING

                mov rdx,[rsi].string_ptr
                mov edx,[rdx]

                .switch dl
                .case 0 ; <>
                    mov rax,[rsi].tokpos
                    mov rcx,[rsi+asm_tok].tokpos
                   .break
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

        .if ( !eax )
            asmerr( 2008, [rbx].tokpos )
            xor eax,eax
           .break
        .endif

        .switch dl

        .case 0 ; reg <> val
            mov eax,MODULE.curr_cpu
            and eax,P_CPU_MASK
            mov edx,[rbx].tokval
            .if ( eax >= P_686 )
                tsprintf( rdi, "%r %r, %r\n%r %r, %s", T_TEST, edx, edx, T_CMOVNZ, edx, rcx )
            .else
                tsprintf( rdi, "%r %r\n%r %r, %s\n%r", T_DOT_IF, edx, T_MOV, edx, rcx, T_DOT_ENDIF )
            .endif
           .break

        .case '='
            mov byte ptr [rax],0
            .if dh == '&'
                tsprintf( rdi, "%r %r, %s", T_LEA, [rbx].tokval, [rsi+asm_tok*2].tokpos )
            .elseif byte ptr [rcx] == '~'
                inc rcx
                tsprintf( rdi, "%r %s, %s\n%r %s", T_MOV, [rbx].tokpos, rcx, T_NOT, [rbx].tokpos )
            .else
                ;
                ; mov reg,0 --> xor reg,reg
                ;
                mov rsi,[rsi+asm_tok].string_ptr
                movzx esi,word ptr [rsi]
                mov eax,[rbx].tokval
                .if ( dh == T_NUM && esi == '0' && ( ( eax >= T_AL && eax <= T_EDI ) ||
                      ( MODULE.Ofssize == USE64 && eax >= T_R8B && eax <= T_R15 ) ) )
                    tsprintf( rdi, "%r %r, %r", T_XOR, eax, eax )
                .else
                    tsprintf( rdi, "%r %s, %s", T_MOV, [rbx].tokpos, rcx )
                .endif
            .endif
            .break

        .case '|'
            .endc .if dh != '='
            mov byte ptr [rax],0
            tsprintf( rdi, "%r %s, %s", T_OR, [rbx].tokpos, rcx )
           .break
        .case '~'
            .endc .if dh != '='
            mov byte ptr [rax],0
            tsprintf( rdi, "%r %s, %s\n%r %s", T_MOV, [rbx].tokpos, rcx, T_NOT, [rbx].tokpos )
           .break
        .case '^'
            .endc .if dh != '='
            mov byte ptr [rax],0
            tsprintf( rdi, "%r %s, %s", T_XOR, [rbx].tokpos, rcx )
           .break
        .case '&'
            .endc .if [rsi+asm_tok].dirtype != DRT_EQUALSGN
            mov byte ptr [rax],0
            tsprintf( rdi, "%r %s, %s", T_AND, [rbx].tokpos, [rsi+asm_tok*2].tokpos )
           .break
        .case '>'
            shr edx,8
            .endc .if !( dl == '>' && dh == '=' )
            mov byte ptr [rax],0
            tsprintf( rdi, "%r %s, %s", T_SHR, [rbx].tokpos, rcx )
           .break
        .case '<'
            shr edx,8
            .endc .if !( dl == '<' && dh == '=' )
            mov byte ptr [rax],0
            tsprintf( rdi, "%r %s, %s", T_SHL, [rbx].tokpos, rcx )
           .break

        .case '+'
            .if dh == '+'
                mov byte ptr [rax],0
                tsprintf( rdi, "%r %s", T_INC, [rbx].tokpos )
               .break
            .elseif [rsi+asm_tok].dirtype == DRT_EQUALSGN
                mov byte ptr [rax],0
                tsprintf( rdi, "%r %s, %s", T_ADD, [rbx].tokpos, [rsi+asm_tok*2].tokpos )
               .break
            .endif
            .endc
        .case '-'
            .if dh == '-'
                mov byte ptr [rax],0
                tsprintf( rdi, "%r %s", T_DEC, [rbx].tokpos )
               .break
            .elseif [rsi+asm_tok].dirtype == DRT_EQUALSGN
                mov byte ptr [rax],0
                tsprintf( rdi, "%r %s, %s", T_SUB, [rbx].tokpos, [rsi+asm_tok*2].tokpos )
               .break
            .endif
            .endc
        .endsw
        asmerr( 2008, [rsi].tokpos )
        xor eax,eax
    .until 1
    ret

    assume rbx:nothing, rsi:nothing

ParseAssignment endp


RenderAssignment proc __ccall private uses rsi rdi rbx dest:string_t, source:string_t, tokenarray:token_t

  local buffer[MAX_LINE_LEN]:char_t
  local tokbuf[MAX_LINE_LEN]:char_t

    ldr rdi,source
    lea rsi,buffer
    ;
    ; <expression1>, <expression2>, ..., [: | 0]
    ;
    .while GetCondition( rdi )

        mov rbx,rcx ; next expression
        mov rdi,rdx ; this expression
        Tokenize( tstrcpy( &tokbuf, rdi ), 0, tokenarray, TOK_DEFAULT )
        mov TokenCount,eax

        .break .ifd ExpandHllProc( rsi, 0, tokenarray ) == ERROR

        .if ( byte ptr [rsi] ) ; function calls expanded

            tstrcat( tstrcat( dest, rsi ), "\n" )
            mov byte ptr [rsi],0
        .endif

        .break .if !ParseAssignment( rsi, tokenarray )
        tstrcat( tstrcat( dest, rsi ), "\n" )
        mov rdi,rbx
    .endw
    mov rax,dest
    movzx eax,byte ptr [rax]
    ret

RenderAssignment endp


    assume  rbx:token_t, rsi:ptr hll_item

ForDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

   .new rc:int_t = NOT_ERROR
   .new cmd:uint_t
   .new p:string_t
   .new q:string_t
   .new buff[16]:char_t
   .new buffer[MAX_LINE_LEN]:char_t
   .new cmdstr[MAX_LINE_LEN]:char_t
   .new tokbuf[MAX_LINE_LEN]:char_t

    ldr rbx,tokenarray
    lea rdi,buffer

    imul eax,i,asm_tok
    mov  eax,[rbx+rax].tokval
    mov  cmd,eax
    inc  i

    .if ( eax == T_DOT_ENDF )

        mov rsi,MODULE.HllStack
        .if !rsi
            .return asmerr( 1011 )
        .endif

        mov rdx,[rsi].next
        mov rcx,MODULE.HllFree
        mov MODULE.HllStack,rdx
        mov [rsi].next,rcx
        mov MODULE.HllFree,rsi

        .if ( [rsi].cmd != HLL_FOR )
            .return asmerr( 1011 )
        .endif

        mov eax,[rsi].labels[LTEST*4]
        .if eax
            AddLineQueueX( "%s%s", GetLabelStr( eax, rdi ), LABELQUAL )
        .endif
        .if ( [rsi].condlines )
            QueueTestLines( [rsi].condlines )
        .endif
        AddLineQueueX( "jmp %s", GetLabelStr( [rsi].labels[LSTART*4], rdi ) )
        mov eax,[rsi].labels[LEXIT*4]
        .if eax
            AddLineQueueX( "%s%s", GetLabelStr( eax, rdi ), LABELQUAL )
        .endif
        imul eax,i,asm_tok
        add rbx,rax
        .if ( [rbx].token != T_FINAL && rc == NOT_ERROR )
            mov rc,asmerr( 2008, [rbx].tokpos )
        .endif

    .else

        mov rsi,MODULE.HllFree
        .if !rsi
            mov rsi,LclAlloc(hll_item)
        .endif
        ExpandCStrings( tokenarray )

        xor eax,eax
        mov [rsi].flags,eax
        mov [rsi].labels[LEXIT*4],eax
        .if ( cmd == T_DOT_FORS )
            mov [rsi].Signed,1
        .endif

        mov [rsi].cmd,HLL_FOR

        ; create the loop labels

        mov [rsi].labels[LSTART*4],GetHllLabel()
        mov [rsi].labels[LTEST*4],GetHllLabel()
        mov [rsi].labels[LEXIT*4],GetHllLabel()

        imul eax,i,asm_tok
        add rbx,rax
        .if ( [rbx].token == T_OP_BRACKET )
            inc i
            add rbx,asm_tok
        .endif

        ; v2.37.10 - added for segments:[] ::

        tstrcpy( rdi, [rbx].tokpos )
        .for ( ecx = 0, rdx = rbx : [rbx].token != T_FINAL : rbx += asm_tok )

            .if ( [rbx].token == T_COLON || [rbx].token == T_DBL_COLON )

                .if ( [rbx].token != T_DBL_COLON && [rbx-asm_tok].token == T_REG )
                    .if ( GetValueSp([rbx-asm_tok].tokval) & OP_SR )
                        .continue .if ( [rbx+asm_tok].token == T_OP_SQ_BRACKET || [rbx+asm_tok].token == T_ID )
                    .endif
                .endif
                mov rcx,[rbx].tokpos
                sub rcx,[rdx].asm_tok.tokpos
                add rcx,rdi
                mov byte ptr [rcx],0
                .if ( [rbx].token == T_DBL_COLON )
                    mov p,rcx
                    inc rcx
                    jmp dbl_colon
                .endif
                add rbx,asm_tok
                mov rax,[rbx].tokpos
                sub rax,[rdx].asm_tok.tokpos
                add rax,rdi
                mov p,rax
                inc ecx
               .break
            .endif
        .endf
        .if ( ecx == 0 )
            .return asmerr( 2206 )
        .endif
        .for ( ecx = 0 : [rbx].token != T_FINAL : rbx += asm_tok )
            .if ( [rbx].token == T_COLON )
                .if ( [rbx-asm_tok].token == T_REG )
                    .if ( GetValueSp([rbx-asm_tok].tokval) & OP_SR )
                        .continue .if ( [rbx+asm_tok].token == T_OP_SQ_BRACKET || [rbx+asm_tok].token == T_ID )
                    .endif
                .endif
                mov rcx,[rbx].tokpos
               .break
            .endif
        .endf
        .if ( rcx == NULL )
            .return asmerr( 2206 )
        .endif
        sub rcx,[rdx].asm_tok.tokpos
        add rcx,rdi
dbl_colon:
        mov byte ptr [rcx],0
        mov rax,[rbx+asm_tok].tokpos
        sub rax,[rdx].asm_tok.tokpos
        add rax,rdi
        mov q,rax
        mov rbx,rdx
        tstrtrim( rax )
        tstrtrim( p )

        .if ( [rbx-asm_tok].token == T_OP_BRACKET )

            .if tstrrchr( q, ')' )

                mov BYTE PTR [rax],0
                tstrtrim(q)
            .endif
        .endif

        lea rbx,cmdstr
        mov BYTE PTR [rbx],0
        .if RenderAssignment( rbx, rdi, tokenarray )
            QueueTestLines( rbx )
        .endif
        AddLineQueueX("%s%s",
                GetLabelStr( [rsi].labels[LSTART*4], &buff ), LABELQUAL )

        mov BYTE PTR [rbx],0
        mov [rsi].condlines,0

        .if ( RenderAssignment(rbx, q, tokenarray) )
            mov [rsi].condlines,LclDup(rbx)
        .endif

        mov rdi,p
        mov BYTE PTR [rbx],0
        .while GetCondition(rdi)

            mov q,rcx
            mov rdi,rdx
            Tokenize( tstrcat( tstrcpy(&tokbuf, ".if " ), rdi ), 0, tokenarray, TOK_DEFAULT )
            mov TokenCount,eax

            mov i,1
            EvaluateHllExpression( rsi, &i, tokenarray, LEXIT, 0, rbx )
            mov rc,eax
            .if ( eax == NOT_ERROR )
                QueueTestLines( rbx )
            .endif
            mov rdi,q
        .endw

        .if ( rsi == MODULE.HllFree )
            mov rax,[rsi].next
            mov MODULE.HllFree,rax
        .endif
        mov rax,MODULE.HllStack
        mov [rsi].next,rax
        mov MODULE.HllStack,rsi
    .endif

    .if ( MODULE.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ( MODULE.line_queue.head )
        RunLineQueue()
    .endif
    .return( rc )

ForDirective endp

    END
